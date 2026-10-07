#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TGaxis.h>
#include <TStyle.h>
#include <TH1F.h>
#include <TLatex.h>
#include <TString.h>
#include <vector>
#include <string>
#include <algorithm>

using std::vector;

static TGraphErrors* makeGraph(const vector<double>& x, const vector<double>& y,
                               const vector<double>& ey, Color_t color,
                               Style_t marker, const char* name) {
  const int n = (int)x.size();
  vector<double> ex(n, 0.0);
  auto *g = new TGraphErrors(n, x.data(), y.data(), ex.data(), ey.data());
  g->SetName(name);
  g->SetMarkerColor(color);
  g->SetLineColor(color);
  g->SetMarkerStyle(marker);
  g->SetMarkerSize(1.15);
  g->SetLineWidth(2);
  return g;
}

static void drawGraphs(const char* cname, const char* title,
                       const char* xtitle, const vector<TGraphErrors*>& graphs,
                       const vector<TString>& labels, const char* outfile,
                       double ymin = -1.0, double ymax = -1.0) {
  auto *c = new TCanvas(cname, title, 900, 650);
  c->SetGrid(1,1);
  c->SetLeftMargin(0.12);
  c->SetBottomMargin(0.12);
  c->SetTopMargin(0.12);

  double xmin =  1e99, xmax = -1e99;
  double autoMin = 1e99, autoMax = -1e99;
  for (auto *g : graphs) {
    for (int i=0; i<g->GetN(); ++i) {
      double x,y; g->GetPoint(i,x,y);
      xmin = std::min(xmin,x); xmax = std::max(xmax,x);
      autoMin = std::min(autoMin, y-g->GetErrorY(i));
      autoMax = std::max(autoMax, y+g->GetErrorY(i));
    }
  }
  double xpad = (xmax > xmin) ? 0.08*(xmax-xmin) : 0.5;
  if (ymin < 0 || ymax < 0) {
    double ypad = std::max(0.005, 0.15*(autoMax-autoMin));
    ymin = std::max(0.0, autoMin-ypad);
    ymax = std::min(1.01, autoMax+ypad);
  }

  auto *frame = c->DrawFrame(xmin-xpad, ymin, xmax+xpad, ymax);
  frame->SetTitle(title);
  frame->GetXaxis()->SetTitle(xtitle);
  frame->GetYaxis()->SetTitle("Efficiency");
  frame->GetYaxis()->SetTitleSize(0.045);
  frame->GetXaxis()->SetTitleSize(0.045);
  frame->GetYaxis()->SetLabelSize(0.04);
  frame->GetYaxis()->SetTitleOffset(0.95);
  frame->GetXaxis()->SetLabelSize(0.039);
  //frame->GetXaxis()->CenterTitle();
  //frame->GetYaxis()->CenterTitle();

  auto *leg = new TLegend(0.56,0.17,0.88,0.17+0.055*graphs.size());
  //leg->SetBorderSize(0); leg->SetFillStyle(0);
  for (size_t i=0; i<graphs.size(); ++i) {
    graphs[i]->Draw("P L SAME");
    leg->AddEntry(graphs[i], labels[i], "lp");
  }
  leg->Draw();
  c->SaveAs(outfile);
}

static void drawCategorical(const char* cname, const char* title,
                            const vector<TGraphErrors*>& graphs,
                            const vector<TString>& labels,
                            const vector<TString>& categories,
                            const char* outfile, double ymin, double ymax) {
  auto *c = new TCanvas(cname, title, 900, 650);
  c->SetGrid(1,1); c->SetLeftMargin(0.12); c->SetBottomMargin(0.15);
  const int ncat = (int)categories.size();
  auto *frame = c->DrawFrame(0.5, ymin, ncat+0.5, ymax);
  frame->SetTitle(title);
  frame->GetXaxis()->SetTitle(TString(cname).Contains("tgem_amp") ? "GEM dVs (Top-Down) [V]" : "Run Settings");
  frame->GetYaxis()->SetTitle("Efficiency");
  frame->GetYaxis()->SetTitleSize(0.045);
  frame->GetXaxis()->SetTitleSize(0.042);
  frame->GetXaxis()->SetLabelSize(0.039);
  frame->GetYaxis()->SetTitleOffset(0.95);
  frame->GetYaxis()->SetLabelSize(0.04);
  frame->GetXaxis()->SetNdivisions(ncat, false);
  for (int i=0; i<ncat; ++i) frame->GetXaxis()->SetBinLabel(frame->GetXaxis()->FindBin(i+1), categories[i]);
  frame->GetXaxis()->LabelsOption("h");
  auto *leg = new TLegend(0.56,0.17,0.88,0.17+0.055*graphs.size());
  //leg->SetBorderSize(0); leg->SetFillStyle(0);
  for (size_t i=0; i<graphs.size(); ++i) { graphs[i]->Draw("P L SAME"); leg->AddEntry(graphs[i],labels[i],"lp"); }
  leg->Draw();
  c->SaveAs(outfile);
}

void draw_combined_efficiency_plots() {
  gStyle->SetOptStat(0);
  /*
  gStyle->SetTitleFontSize(0.040);
  gStyle->SetTitleAlign(23);
  gStyle->SetTitleX(0.05);
  gStyle->SetTitleH(0.075);
  gStyle->SetTitleY(0.995);
  */
  
  // ------------------------------------------------------------------
  // 1) Triple-GEM combined amplification (GEM dV) scan.
  // Use categorical x positions so the axis retains the three individual
  // GEM voltage drops (Top-Down) exactly as listed in the spreadsheet.
  // ------------------------------------------------------------------
  vector<double> tgem_amp_x = {1,2,3,4};
  auto *tg_amp_nocut = makeGraph(tgem_amp_x,
      {0.995,0.998,0.998,0.998}, {0.0007,0.0004,0.0006,0.0005}, kBlack,20,"tg_amp_nocut");
  auto *tg_amp_n8 = makeGraph(tgem_amp_x,
      {0.942,0.966,0.976,0.988}, {0.0022,0.0012,0.0013,0.0010}, kRed+1,21,"tg_amp_n8");
  auto *tg_amp_n6 = makeGraph(tgem_amp_x,
      {0.969,0.984,0.989,0.995}, {0.0017,0.0009,0.0010,0.0008}, kBlue+1,47,"tg_amp_n6");
  drawCategorical("c_tgem_amp", "Triple-GEM_v3: GEM dV Scan",
                  {tg_amp_nocut,tg_amp_n6,tg_amp_n8},
                  {"No nPulse cut","nPulse #geq 6","nPulse #geq 8"},
                  {"448/411/374","450/415/380","450/420/385","450/425/390"},
                  "tgem_combined_gem_dv.pdf", 0.92,1.001);

  // ------------------------------------------------------------------
  // 2) Triple-GEM combined transfer/induction-field scan.
  // ------------------------------------------------------------------
  vector<double> tgem_tf_x = {2.75,3.00,3.25,3.50,3.74};
  auto *tg_tf_nocut = makeGraph(tgem_tf_x,
      {0.996,0.995,0.996,0.996,0.997}, {0.0010,0.0006,0.0007,0.0007,0.0006}, kBlack,20,"tg_tf_nocut");
  auto *tg_tf_n8 = makeGraph(tgem_tf_x,
      {0.944,0.948,0.958,0.968,0.981}, {0.0029,0.0014,0.0014,0.0013,0.0014}, kRed+1,21,"tg_tf_n8");
  auto *tg_tf_n6 = makeGraph(tgem_tf_x,
      {0.972,0.974,0.980,0.984,0.991}, {0.0023,0.0011,0.0011,0.0010,0.0011}, kBlue+1,47,"tg_tf_n6");
  // Custom draw for the TF scan: bottom axis is field [kV/cm], while the
  // top axis carries the corresponding spreadsheet Transfer Field [dV]
  // values: 550, 600, 650, 700, 747 V.
  {
    auto *c = new TCanvas("c_tgem_tf", "Triple-GEM Tracking Efficiency (TF Scan)", 900, 650);
    c->SetGrid(1,1);
    c->SetLeftMargin(0.12);
    c->SetBottomMargin(0.12);
    c->SetTopMargin(0.13);

    const double xmin = 2.65, xmax = 3.84;
    auto *frame = c->DrawFrame(xmin, 0.92, xmax, 1.001);
    frame->SetTitle("Triple-GEM_v3: Transfer Field Scan");
    frame->GetXaxis()->SetTitle("Transfer/Induction Field [kV/cm]");
    frame->GetYaxis()->SetTitle("Efficiency");
    frame->GetYaxis()->SetTitleSize(0.045);
    frame->GetXaxis()->SetTitleSize(0.042);
    frame->GetXaxis()->SetLabelSize(0.039);
    frame->GetYaxis()->SetLabelSize(0.04);
    frame->GetYaxis()->SetTitleOffset(0.95);
    //frame->GetXaxis()->SetNdivisions(520);
    //frame->GetXaxis()->CenterTitle();
    //frame->GetYaxis()->CenterTitle();

    tg_tf_nocut->Draw("P L SAME");
    tg_tf_n6->Draw("P L SAME");
    tg_tf_n8->Draw("P L SAME");

    auto *leg = new TLegend(0.56,0.17,0.88,0.335);
    //leg->SetBorderSize(0); leg->SetFillStyle(0);
    leg->AddEntry(tg_tf_nocut,"No nPulse cut","lp");
    leg->AddEntry(tg_tf_n6,"nPulse #geq 6","lp");
    leg->AddEntry(tg_tf_n8,"nPulse #geq 8","lp");
    leg->Draw();

    // Overlay a label-only top axis at the exact x positions of the five
    // measurements. TGaxis provides the axis line/title; TLatex supplies
    // the non-linear dV labels from the table.
    auto *top = new TGaxis(xmin,1.001,xmax,1.001,xmin,xmax,510,"-");
    top->SetTitle("Transfer/Induction Field [dV]");
    top->SetLabelSize(0);
    top->SetTitleOffset(0.79);
    //top->SetLabelFont(42);
    top->SetTitleFont(42);
    top->SetTitleSize(0.04);
    top->Draw();
    const char *dvLabels[] = {"550","600","650","700","750"};
    TLatex latex;
    latex.SetTextAlign(23);
    latex.SetTextFont(42);
    latex.SetTextSize(0.039);
    for (int i=0; i<5; ++i)
      latex.DrawLatex(tgem_tf_x[i], 1.0044, dvLabels[i]);

    c->SaveAs("tgem_combined_tf.pdf");
  }

  // ------------------------------------------------------------------
  // 3) Triple-GEM productivity/environment comparison at fixed HV.
  // ------------------------------------------------------------------
  vector<double> settings_x = {1,2,3};
  vector<TString> settings = {"No Rad, 25 CCPM","No Rad, 50 CCPM","With Rad, 50 CCPM"};
  auto *tg_env_nocut = makeGraph(settings_x,
      {0.992,0.994,0.996}, {0.0007,0.0004,0.0004}, kBlack,20,"tg_env_nocut");
  auto *tg_env_n6 = makeGraph(settings_x,
      {0.732,0.774,0.982}, {0.0022,0.0006,0.0007}, kBlue+1,47,"tg_env_n6");
  auto *tg_env_n8 = makeGraph(settings_x,
      {0.504,0.567,0.961}, {0.0025,0.0017,0.0010}, kRed+1,21,"tg_env_n8");
  drawCategorical("c_tgem_env", "Triple-GEM_v3: ''Production''' HV Settings",
                  {tg_env_nocut,tg_env_n6,tg_env_n8}, {"No nPulse cut","nPulse #geq 6","nPulse #geq 8"},
                  settings, "tgem_productivity_hv_settings.pdf", 0.45,1.01);

  // ------------------------------------------------------------------
  // 4) Triple-GEM low-flow-over-time productivity plot (nPulse >= 6).
  // ------------------------------------------------------------------
  // Runs 8265-8266 were taken at 50 CCPM; runs 8267-8270 at 25 CCPM.
  // Draw them as separate graph objects so the gas-flow change is explicit.
  auto *tg_time_50 = makeGraph({8265,8266},
      {0.774,0.763}, {0.0006,0.0006}, kBlue+1,20,"tg_time_50");
  auto *tg_time_25 = makeGraph({8267,8268,8269,8270},
      {0.755,0.749,0.743,0.732}, {0.0020,0.0021,0.0023,0.0022}, kRed+1,21,"tg_time_25");
  drawGraphs("c_tgem_time", "Triple-GEM_v3: No Radiator, nPulse #geq 6",
             "Run Number", {tg_time_50,tg_time_25}, {"50 CCPM","25 CCPM"},
             "tgem_productivity_run.pdf", 0.70,1.001);

  // ------------------------------------------------------------------
  // 5) Hybrid Micromegas combined divider V_in (HV) scan.
  // ------------------------------------------------------------------
  vector<double> mmg_hv_x = {1675,1685,1695,1700,1710,1720,1730,1735};
  auto *mmg_nocut = makeGraph(mmg_hv_x,
      {0.997,0.998,0.998,0.998,0.997,0.998,0.998,0.998},
      {0.0007,0.0004,0.0006,0.0005,0.0007,0.0006,0.0006,0.0011}, kBlack,20,"mmg_nocut");
  auto *mmg_n8 = makeGraph(mmg_hv_x,
      {0.971,0.982,0.986,0.987,0.989,0.993,0.995,0.994},
      {0.0015,0.0009,0.0010,0.0010,0.0010,0.0010,0.0008,0.0015}, kRed+1,21,"mmg_n8");
  auto *mmg_n10 = makeGraph(mmg_hv_x,
      {0.939,0.955,0.963,0.972,0.978,0.986,0.991,0.990},
      {0.0020,0.0012,0.0015,0.0013,0.0013,0.0012,0.0011,0.0016}, kGreen+2,47,"mmg_n10");
  drawGraphs("c_mmg_hv", "Hybrid Micromegas_v2: HV Scan",
             "Voltage Divider V_{in} [V]", {mmg_nocut,mmg_n8,mmg_n10},
             {"No nPulse cut","nPulse #geq 8","nPulse #geq 10"}, "mmg_combined_hv.pdf", 0.92,1.001);

  // ------------------------------------------------------------------
  // 6) Hybrid Micromegas productivity/environment comparison at fixed HV.
  // ------------------------------------------------------------------
  auto *mmg_env_nocut = makeGraph(settings_x,
      {0.994,0.995,0.997}, {0.0006,0.0003,0.0004}, kBlack,20,"mmg_env_nocut");
  auto *mmg_env_n8 = makeGraph(settings_x,
      {0.957,0.965,0.991}, {0.0010,0.0006,0.0005}, kRed+1,21,"mmg_env_n8");
  auto *mmg_env_n10 = makeGraph(settings_x,
      {0.897,0.911,0.986}, {0.0014,0.0003,0.0006}, kGreen+2,47,"mmg_env_n10");
  drawCategorical("c_mmg_env", "Hybrid Micromegas_v2: ''Production''' HV Settings",
                  {mmg_env_nocut,mmg_env_n8,mmg_env_n10}, {"No nPulse cut","nPulse #geq 8","nPulse #geq 10"},
                  settings, "mmg_productivity_hv_settings.pdf", 0.86,1.001);

  // ------------------------------------------------------------------
  // 7) Hybrid Micromegas low-flow-over-time productivity plot (nPulse >= 10).
  // ------------------------------------------------------------------
  // Runs 8265-8266 were taken at 50 CCPM; runs 8267-8270 at 25 CCPM.
  auto *mmg_time_50 = makeGraph({8265,8266},
      {0.911,0.907}, {0.0003,0.0003}, kBlue+1,20,"mmg_time_50");
  auto *mmg_time_25 = makeGraph({8267,8268,8269,8270},
      {0.902,0.904,0.904,0.897}, {0.0012,0.0013,0.0014,0.0014}, kRed+1,21,"mmg_time_25");
  drawGraphs("c_mmg_time", "Hybrid Micromegas_v2: No Radiator, nPulse #geq 10",
             "Run Number", {mmg_time_50,mmg_time_25}, {"50 CCPM","25 CCPM"},
             "mmg_productivity_run.pdf", 0.88,1.001);
}
