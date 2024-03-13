#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>

void rejectionFactorsCompare() {
	
	const std::vector<string>& labels = {"Double Foil 10GeV", "Double Foil 10GeV", "Double Foil 10GeV", "Double Foil 10GeV", "Double Foil 10GeV", "Double Fleece 10GeV","Double Fleece 10GeV","No Rad 10GeV","Double Foil 3GeV","Double Fleece 3GeV","VU Foil 3 GeV", "TU Foil 10GeV", "TU Foil 10GeV"};
	TCanvas *c70 = new TCanvas("c70", "Rejection Factor at 70% el Efficiency", 1200, 800);
	TCanvas *c80 = new TCanvas("c80", "Rejection Factor at 80% el Efficiency", 1200, 800);
	TCanvas *c85 = new TCanvas("c85", "Rejection Factor at 85% el Efficiency", 1200, 800);
	TCanvas *c90 = new TCanvas("c90", "Rejection Factor at 90% el Efficiency", 1200, 800);
  
  //With Cal & Cher
  const std::vector<double>& rej70_a = {11.72, 11.17, 11.56, 9., 12.2, 16.9, 23.84, 2., 8.75, 12.08, 6.69, 8.98, 8.36};
  const std::vector<double>& rej70Error_a = {0.0741, 0.0898, 0.1104, 0.0917, 0.1187, 0.1414, 0.0891, 0.0498, 0.2041, 0.1601, 0.1072, 0.106, 0.0962};
  const std::vector<double>& rej80_a = {7.91, 5.79, 6.11, 6.38, 6.73, 9.25, 11.07, 1.64, 5.72, 4.57, 4.22, 5.3, 5.09};
  const std::vector<double>& rej80Error_a = {0.0607, 0.0644, 0.0803, 0.0778, 0.0891, 0.1078, 0.0605, 0.0465, 0.1667, 0.0981, 0.0861, 0.0816, 0.0747};
  const std::vector<double>& rej85_a = {5.19, 4.03, 3.81, 3.87, 5.31, 6.69, 7.87, 1.46, 4.19, 3.24, 2.95, 3.86, 3.21};
  const std::vector<double>& rej85Error_a = {0.0491, 0.0535, 0.0638, 0.0597, 0.0793, 0.0902, 0.0512, 0.043, 0.1414, 0.0833, 0.0705, 0.0693, 0.06};
  const std::vector<double>& rej90_a = {3.26, 2.8, 2.26, 2.21, 3.6, 3.7, 4.88, 1.27, 2.35, 2.2, 2.24, 2.73, 2.1};
  const std::vector<double>& rej90Error_a = {0.0389, 0.0443, 0.0483, 0.0435, 0.0644, 0.067, 0.0395, 0.0408, 0.1043, 0.0685, 0.0623, 0.0585, 0.0468};

  //With 2 Cher
  const std::vector<double>& rej70_b = {10.5, 9.52, 9.81, 9.85, 8.3, 20.28, 16.12, 1.89, 4.58, 5.09, 5.14, 7.63, 7.87};
  const std::vector<double>& rej70Error_b = {0.0688, 0.0803, 0.099, 0.0976, 0.0985, 0.1525, 0.0709, 0.0479, 0.1581, 0.1021, 0.0941, 0.0962, 0.0925};
  const std::vector<double>& rej80_b = {5.4, 5.27, 4.8, 5.51, 4.03, 8.1, 8.46, 1.44, 2.53, 2.67, 2.89, 4.45, 4.29};
  const std::vector<double>& rej80Error_b = {0.0491, 0.0598, 0.0687, 0.0712, 0.0688, 0.0945, 0.052, 0.0429, 0.1104, 0.0727, 0.0707, 0.0731, 0.0667};
  const std::vector<double>& rej85_b = {3.77, 3.86, 3.45, 3.73, 3.01, 5.18, 5.37, 1.3, 1.87, 2.07, 2.19, 3.02, 2.32};
  const std::vector<double>& rej85Error_b = {0.0406, 0.0514, 0.0579, 0.0597, 0.0585, 0.0769, 0.0416, 0.0407, 0.0981, 0.0645, 0.0602, 0.0602, 0.0487};
  const std::vector<double>& rej90_b = {2.47, 2.46, 2.34, 2.41, 1.97, 3.05, 2.81, 1.2, 1.48, 1.59, 1.71, 2.12, 1.73};
  const std::vector<double>& rej90Error_b = {0.0332, 0.0405, 0.0475, 0.0482, 0.0476, 0.059, 0.0294, 0.039, 0.0891, 0.0577, 0.0535, 0.0505, 0.0433};

  TH1D *histogram70 = new TH1D("histogram70", "Rejection Factors with 70% el Efficiency", labels.size(), 0, labels.size());
  
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram70->GetXaxis()->SetBinLabel(i + 1, labels[i].c_str());
    histogram70->SetBinContent(i + 1, rej70_a[i]);
    histogram70->SetBinError(i + 1, rej70Error_a[i]);
  }
  TH1D *histogram70_b = (TH1D*)histogram70->Clone();
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram70_b->SetBinContent(i + 1, rej70_b[i]);
    histogram70_b->SetBinError(i + 1, rej70Error_b[i]);
  }
  
	TH1D *histogram80 = new TH1D("histogram80", "Rejection Factors with 80% el Efficiency", labels.size(), 0, labels.size());
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram80->GetXaxis()->SetBinLabel(i + 1, labels[i].c_str());
    histogram80->SetBinContent(i + 1, rej80_a[i]);
    histogram80->SetBinError(i + 1, rej80Error_a[i]);
  }
  TH1D *histogram80_b = (TH1D*)histogram80->Clone();
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram80_b->SetBinContent(i + 1, rej80_b[i]);
    histogram80_b->SetBinError(i + 1, rej80Error_b[i]);
  }
  
	TH1D *histogram85 = new TH1D("histogram85", "Rejection Factors with 85% el Efficiency", labels.size(), 0, labels.size());
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram85->GetXaxis()->SetBinLabel(i + 1, labels[i].c_str());
    histogram85->SetBinContent(i + 1, rej85_a[i]);
    histogram85->SetBinError(i + 1, rej85Error_a[i]);
  }
  TH1D *histogram85_b = (TH1D*)histogram85->Clone();
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram85_b->SetBinContent(i + 1, rej85_b[i]);
    histogram85_b->SetBinError(i + 1, rej85Error_b[i]);
  }
  
	TH1D *histogram90 = new TH1D("histogram90", "Rejection Factors with 90% el Efficiency", labels.size(), 0, labels.size());
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram90->GetXaxis()->SetBinLabel(i + 1, labels[i].c_str());
    histogram90->SetBinContent(i + 1, rej90_a[i]);
    histogram90->SetBinError(i + 1, rej90Error_a[i]);
  }
  TH1D *histogram90_b = (TH1D*)histogram90->Clone();
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram90_b->SetBinContent(i + 1, rej90_b[i]);
    histogram90_b->SetBinError(i + 1, rej90Error_b[i]);
  }
  
  //--------------------------------------------
  c70->cd();
  c70->SetGridy();
  TLegend *legend1 = new TLegend(0.7, 0.7, 0.9, 0.9);
  //legend->SetHeader("Electron Efficiency", "C");
  
	// Add entries to legend and set marker colors for each series
  histogram70->SetMarkerStyle(21); // Square
  histogram70->SetMarkerColor(kBlue);
  histogram70->SetLineColor(kWhite);
  histogram70->SetStats(0);
  histogram70->GetYaxis()->SetTitle("Rejection Factor");
  histogram70->GetYaxis()->SetRangeUser(0, 30);
  histogram70->GetYaxis()->SetNdivisions(520);
  histogram70->Draw("");
  legend1->AddEntry(histogram70, "Cal. & Cher. PID", "lp");
  
  histogram70_b->SetMarkerStyle(20); // Circle
  histogram70_b->SetMarkerColor(kRed);
  histogram70_b->SetLineColor(kWhite);
  histogram70_b->Draw("SAME");
  legend1->AddEntry(histogram70_b, "Cher. PID", "lp");
  
  // Draw error bars above and below each data point
  for (unsigned int i = 0; i < labels.size(); ++i) {
    double x1 = histogram70->GetXaxis()->GetBinCenter(i + 1);
    double y1 = histogram70->GetBinContent(i + 1);
    double error1 = rej70Error_a[i];
    TLine *line1a = new TLine(x1, y1 + (y1*error1), x1, y1 - (y1*error1));
    line1a->Draw();
    TLine *line1b = new TLine(x1 - 0.1, y1 + (y1*error1), x1 + 0.1, y1 + (y1*error1));
    line1b->Draw("");
    TLine *line1c = new TLine(x1 - 0.1, y1 - (y1*error1), x1 + 0.1, y1 - (y1*error1));
    line1c->Draw("");
    
    double x2 = histogram70_b->GetXaxis()->GetBinCenter(i + 1);
    double y2 = histogram70_b->GetBinContent(i + 1);
    double error2 = rej70Error_b[i];
    TLine *line2a = new TLine(x2, y2 + (y2*error2), x2, y2 - (y2*error2));
    line2a->Draw();
    TLine *line2b = new TLine(x2 - 0.1, y2 + (y2*error2), x2 + 0.1, y2 + (y2*error2));
    line2b->Draw("");
    TLine *line2c = new TLine(x2 - 0.1, y2 - (y2*error2), x2 + 0.1, y2 - (y2*error2));
    line2c->Draw("");
  }
  
  legend1->Draw();
  c70->Draw();
	
	c80->cd();
	c80->SetGridy();
	TLegend *legend2 = new TLegend(0.7, 0.7, 0.9, 0.9);
	
  histogram80->SetMarkerStyle(21); // Square
  histogram80->SetMarkerColor(kBlue);
  histogram80->SetLineColor(kWhite);
  histogram80->SetStats(0);
  histogram80->GetYaxis()->SetTitle("Rejection Factor");
  histogram80->GetYaxis()->SetRangeUser(0, 30);
  histogram80->GetYaxis()->SetNdivisions(520);
  histogram80->Draw("");
  legend2->AddEntry(histogram80, "Cal. & Cher. PID", "lp");
  
  histogram80_b->SetMarkerStyle(20); // Circle
  histogram80_b->SetMarkerColor(kRed);
  histogram80_b->SetLineColor(kWhite);
  histogram80_b->Draw("SAME");
  legend2->AddEntry(histogram80_b, "Cher. PID", "lp");
  
  // Draw error bars above and below each data point
  for (unsigned int i = 0; i < labels.size(); ++i) {
    double x1 = histogram80->GetXaxis()->GetBinCenter(i + 1);
    double y1 = histogram80->GetBinContent(i + 1);
    double error1 = rej80Error_a[i];
    TLine *line1a = new TLine(x1, y1 + (y1*error1), x1, y1 - (y1*error1));
    line1a->Draw();
    TLine *line1b = new TLine(x1 - 0.1, y1 + (y1*error1), x1 + 0.1, y1 + (y1*error1));
    line1b->Draw("");
    TLine *line1c = new TLine(x1 - 0.1, y1 - (y1*error1), x1 + 0.1, y1 - (y1*error1));
    line1c->Draw("");
    
    double x2 = histogram80_b->GetXaxis()->GetBinCenter(i + 1);
    double y2 = histogram80_b->GetBinContent(i + 1);
    double error2 = rej80Error_b[i];
    TLine *line2a = new TLine(x2, y2 + (y2*error2), x2, y2 - (y2*error2));
    line2a->Draw();
    TLine *line2b = new TLine(x2 - 0.1, y2 + (y2*error2), x2 + 0.1, y2 + (y2*error2));
    line2b->Draw("");
    TLine *line2c = new TLine(x2 - 0.1, y2 - (y2*error2), x2 + 0.1, y2 - (y2*error2));
    line2c->Draw("");
  }
  
  legend2->Draw();
  c80->Draw();
	
  c85->cd();
  c85->SetGridy();
	TLegend *legend3 = new TLegend(0.7, 0.7, 0.9, 0.9);
	
  histogram85->SetMarkerStyle(21); // Square
  histogram85->SetMarkerColor(kBlue);
  histogram85->SetLineColor(kWhite);
  histogram85->SetStats(0);
  histogram85->GetYaxis()->SetTitle("Rejection Factor");
  histogram85->GetYaxis()->SetRangeUser(0, 30);
  histogram85->GetYaxis()->SetNdivisions(520);
  histogram85->Draw("");
  legend3->AddEntry(histogram85, "Cal. & Cher. PID", "lp");
  
  histogram85_b->SetMarkerStyle(20); // Circle
  histogram85_b->SetMarkerColor(kRed);
  histogram85_b->SetLineColor(kWhite);
  histogram85_b->Draw("SAME");
  legend3->AddEntry(histogram85_b, "Cher. PID", "lp");
  
  // Draw error bars above and below each data point
  for (unsigned int i = 0; i < labels.size(); ++i) {
    double x1 = histogram85->GetXaxis()->GetBinCenter(i + 1);
    double y1 = histogram85->GetBinContent(i + 1);
    double error1 = rej85Error_a[i];
    TLine *line1a = new TLine(x1, y1 + (y1*error1), x1, y1 - (y1*error1));
    line1a->Draw();
    TLine *line1b = new TLine(x1 - 0.1, y1 + (y1*error1), x1 + 0.1, y1 + (y1*error1));
    line1b->Draw("");
    TLine *line1c = new TLine(x1 - 0.1, y1 - (y1*error1), x1 + 0.1, y1 - (y1*error1));
    line1c->Draw("");
    
    double x2 = histogram85_b->GetXaxis()->GetBinCenter(i + 1);
    double y2 = histogram85_b->GetBinContent(i + 1);
    double error2 = rej85Error_b[i];
    TLine *line2a = new TLine(x2, y2 + (y2*error2), x2, y2 - (y2*error2));
    line2a->Draw();
    TLine *line2b = new TLine(x2 - 0.1, y2 + (y2*error2), x2 + 0.1, y2 + (y2*error2));
    line2b->Draw("");
    TLine *line2c = new TLine(x2 - 0.1, y2 - (y2*error2), x2 + 0.1, y2 - (y2*error2));
    line2c->Draw("");
  }
  
  legend3->Draw();
  c85->Draw();
	
  c90->cd();
  c90->SetGridy();
	TLegend *legend4 = new TLegend(0.7, 0.7, 0.9, 0.9);
	
  histogram90->SetMarkerStyle(21); // Square
  histogram90->SetMarkerColor(kBlue);
  histogram90->SetLineColor(kWhite);
  histogram90->SetStats(0);
  histogram90->GetYaxis()->SetTitle("Rejection Factor");
  histogram90->GetYaxis()->SetRangeUser(0, 30);
  histogram90->GetYaxis()->SetNdivisions(520);
  histogram90->Draw("");
  legend4->AddEntry(histogram90, "Cal. & Cher. PID", "lp");
  
  histogram90_b->SetMarkerStyle(20); // Circle
  histogram90_b->SetMarkerColor(kRed);
  histogram90_b->SetLineColor(kWhite);
  histogram90_b->Draw("SAME");
  legend4->AddEntry(histogram90_b, "Cher. PID", "lp");
  
  // Draw error bars above and below each data point
  for (unsigned int i = 0; i < labels.size(); ++i) {
    double x1 = histogram90->GetXaxis()->GetBinCenter(i + 1);
    double y1 = histogram90->GetBinContent(i + 1);
    double error1 = rej90Error_a[i];
    TLine *line1a = new TLine(x1, y1 + (y1*error1), x1, y1 - (y1*error1));
    line1a->Draw();
    TLine *line1b = new TLine(x1 - 0.1, y1 + (y1*error1), x1 + 0.1, y1 + (y1*error1));
    line1b->Draw("");
    TLine *line1c = new TLine(x1 - 0.1, y1 - (y1*error1), x1 + 0.1, y1 - (y1*error1));
    line1c->Draw("");
    
    double x2 = histogram90_b->GetXaxis()->GetBinCenter(i + 1);
    double y2 = histogram90_b->GetBinContent(i + 1);
    double error2 = rej90Error_b[i];
    TLine *line2a = new TLine(x2, y2 + (y2*error2), x2, y2 - (y2*error2));
    line2a->Draw();
    TLine *line2b = new TLine(x2 - 0.1, y2 + (y2*error2), x2 + 0.1, y2 + (y2*error2));
    line2b->Draw("");
    TLine *line2c = new TLine(x2 - 0.1, y2 - (y2*error2), x2 + 0.1, y2 - (y2*error2));
    line2c->Draw("");
  }
  
  legend4->Draw();
  c90->Draw();
  
  c70->SaveAs("rejectionFactors_70_Compare.png");
  c80->SaveAs("rejectionFactors_80_Compare.png");
  c85->SaveAs("rejectionFactors_85_Compare.png");
  c90->SaveAs("rejectionFactors_90_Compare.png");
}
