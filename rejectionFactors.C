#include <TCanvas.h>
#include <TH1D.h>
#include <TLegend.h>

#define useCal
//#define noCal

void rejectionFactors() {
	
	const std::vector<string>& labels = {"Double Foil 10GeV", "Double Foil 10GeV", "Double Foil 10GeV", "Double Foil 10GeV", "Double Foil 10GeV", "Double Fleece 10GeV","Double Fleece 10GeV","No Rad 10GeV","Double Foil 3GeV","Double Fleece 3GeV","VU Foil 3 GeV", "TU Foil 10GeV", "TU Foil 10GeV"};
	TCanvas *c1 = new TCanvas("c1", "Rejection Factors", 1200, 800);
	c1->SetGridy();
#ifdef useCal
  TH1D *histogram1 = new TH1D("histogram1", "Rejection Factors with Cal. & Cher. PID", labels.size(), 0, labels.size());
  const std::vector<double>& rej70 = {11.72, 11.17, 11.56, 9., 12.2, 16.9, 23.84, 2., 8.75, 12.08, 6.69, 8.98, 8.36};
  const std::vector<double>& rej70Error = {0.0741, 0.0898, 0.1104, 0.0917, 0.1187, 0.1414, 0.0891, 0.0498, 0.2041, 0.1601, 0.1072, 0.106, 0.0962};
  const std::vector<double>& rej80 = {7.91, 5.79, 6.11, 6.38, 6.73, 9.25, 11.07, 1.64, 5.72, 4.57, 4.22, 5.3, 5.09};
  const std::vector<double>& rej80Error = {0.0607, 0.0644, 0.0803, 0.0778, 0.0891, 0.1078, 0.0605, 0.0465, 0.1667, 0.0981, 0.0861, 0.0816, 0.0747};
  const std::vector<double>& rej85 = {5.19, 4.03, 3.81, 3.87, 5.31, 6.69, 7.87, 1.46, 4.19, 3.24, 2.95, 3.86, 3.21};
  const std::vector<double>& rej85Error = {0.0491, 0.0535, 0.0638, 0.0597, 0.0793, 0.0902, 0.0512, 0.043, 0.1414, 0.0833, 0.0705, 0.0693, 0.06};
  const std::vector<double>& rej90 = {3.26, 2.8, 2.26, 2.21, 3.6, 3.7, 4.88, 1.27, 2.35, 2.2, 2.24, 2.73, 2.1};
  const std::vector<double>& rej90Error = {0.0389, 0.0443, 0.0483, 0.0435, 0.0644, 0.067, 0.0395, 0.0408, 0.1043, 0.0685, 0.0623, 0.0585, 0.0468};
#elif noCal
  TH1D *histogram1 = new TH1D("histogram1", "Rejection Factors with Cher. PID", labels.size(), 0, labels.size());
  const std::vector<double>& rej70 = {10.5, 9.52, 9.81, 9.85, 8.3, 20.28, 16.12, 1.89, 4.58, 5.09, 5.14, 7.63, 7.87};
  const std::vector<double>& rej70Error = {0.0688, 0.0803, 0.099, 0.0976, 0.0985, 0.1525, 0.0709, 0.0479, 0.1581, 0.1021, 0.0941, 0.0962, 0.0925};
  const std::vector<double>& rej80 = {5.4, 5.27, 4.8, 5.51, 4.03, 8.1, 8.46, 1.44, 2.53, 2.67, 2.89, 4.45, 4.29};
  const std::vector<double>& rej80Error = {0.0491, 0.0598, 0.0687, 0.0712, 0.0688, 0.0945, 0.052, 0.0429, 0.1104, 0.0727, 0.0707, 0.0731, 0.0667};
  const std::vector<double>& rej85 = {3.77, 3.86, 3.45, 3.73, 3.01, 5.18, 5.37, 1.3, 1.87, 2.07, 2.19, 3.02, 2.32};
  const std::vector<double>& rej85Error = {0.0406, 0.0514, 0.0579, 0.0597, 0.0585, 0.0769, 0.0416, 0.0407, 0.0981, 0.0645, 0.0602, 0.0602, 0.0487};
  const std::vector<double>& rej90 = {2.47, 2.46, 2.34, 2.41, 1.97, 3.05, 2.81, 1.2, 1.48, 1.59, 1.71, 2.12, 1.73};
  const std::vector<double>& rej90Error = {0.0332, 0.0405, 0.0475, 0.0482, 0.0476, 0.059, 0.0294, 0.039, 0.0891, 0.0577, 0.0535, 0.0505, 0.0433};
#endif

	for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram1->GetXaxis()->SetBinLabel(i + 1, labels[i].c_str());
  }
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram1->SetBinContent(i + 1, rej70[i]);
    histogram1->SetBinError(i + 1, rej70Error[i]);
  }
  
	TH1D *histogram2 = (TH1D*)histogram1->Clone();
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram2->SetBinContent(i + 1, rej80[i]);
    histogram2->SetBinError(i + 1, rej80Error[i]);
  }
  
	TH1D *histogram3 = (TH1D*)histogram1->Clone();
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram3->SetBinContent(i + 1, rej85[i]);
    histogram3->SetBinError(i + 1, rej85Error[i]);
  }
	TH1D *histogram4 = (TH1D*)histogram1->Clone();
  for (unsigned int i = 0; i < labels.size(); ++i) {
    histogram4->SetBinContent(i + 1, rej90[i]);
    histogram4->SetBinError(i + 1, rej90Error[i]);
  }
  
  //--------------------------------------------
  // Create legend
  TLegend *legend1 = new TLegend(0.7, 0.7, 0.9, 0.9);
  legend1->SetHeader("Electron Efficiency", "C");
  
	// Add entries to legend and set marker colors for each series
  histogram1->SetMarkerStyle(21); // Square
  histogram1->SetMarkerColor(kBlue);
  histogram1->SetLineColor(kWhite);
  histogram1->SetStats(0);
  histogram1->GetYaxis()->SetTitle("Rejection Factor");
  histogram1->GetYaxis()->SetRangeUser(0, 30);
  histogram1->GetYaxis()->SetNdivisions(520);
  histogram1->Draw("");
  legend1->AddEntry(histogram1, "70%", "p");
	
  histogram2->SetMarkerStyle(21);
  histogram2->SetMarkerColor(kGreen);
  histogram2->SetLineColor(kWhite);
  histogram2->Draw("SAME");
  legend1->AddEntry(histogram2, "80%", "p");
	
  histogram3->SetMarkerStyle(21);
  histogram3->SetMarkerColor(kMagenta);
  histogram3->SetLineColor(kWhite);
  histogram3->Draw("SAME");
  legend1->AddEntry(histogram3, "85%", "p");
	
  histogram4->SetMarkerStyle(21);
  histogram4->SetMarkerColor(kRed);
  histogram4->SetLineColor(kWhite);
  histogram4->Draw("SAME");
  legend1->AddEntry(histogram4, "90%", "p");
  
  // Draw error bars above and below each data point
  for (unsigned int i = 0; i < labels.size(); ++i) {
    double x1 = histogram1->GetXaxis()->GetBinCenter(i + 1);
    double y1 = histogram1->GetBinContent(i + 1);
    double error1 = rej70Error[i];
    TLine *line1a = new TLine(x1, y1 + (y1*error1), x1, y1 - (y1*error1));
    line1a->Draw();
    TLine *line1b = new TLine(x1 - 0.1, y1 + (y1*error1), x1 + 0.1, y1 + (y1*error1));
    line1b->Draw("");
    TLine *line1c = new TLine(x1 - 0.1, y1 - (y1*error1), x1 + 0.1, y1 - (y1*error1));
    line1c->Draw("");
    
    double x2 = histogram2->GetXaxis()->GetBinCenter(i + 1);
    double y2 = histogram2->GetBinContent(i + 1);
    double error2 = rej80Error[i];
    TLine *line2a = new TLine(x2, y2 + (y2*error2), x2, y2 - (y2*error2));
    line2a->Draw();
    TLine *line2b = new TLine(x2 - 0.1, y2 + (y2*error2), x2 + 0.1, y2 + (y2*error2));
    line2b->Draw("");
    TLine *line2c = new TLine(x2 - 0.1, y2 - (y2*error2), x2 + 0.1, y2 - (y2*error2));
    line2c->Draw("");
    
    double x3 = histogram3->GetXaxis()->GetBinCenter(i + 1);
    double y3 = histogram3->GetBinContent(i + 1);
    double error3 = rej85Error[i];
    TLine *line3a = new TLine(x3, y3 + (y3*error3), x3, y3 - (y3*error3));
    line3a->Draw();
    TLine *line3b = new TLine(x3 - 0.1, y3 + (y3*error3), x3 + 0.1, y3 + (y3*error3));
    line3b->Draw("");
    TLine *line3c = new TLine(x3 - 0.1, y3 - (y3*error3), x3 + 0.1, y3 - (y3*error3));
    line3c->Draw("");
    
    double x4 = histogram4->GetXaxis()->GetBinCenter(i + 1);
    double y4 = histogram4->GetBinContent(i + 1);
    double error4 = rej90Error[i];
    TLine *line4a = new TLine(x4, y4 + (y4*error4), x4, y4 - (y4*error4));
    line4a->Draw();
    TLine *line4b = new TLine(x4 - 0.1, y4 + (y4*error4), x4 + 0.1, y4 + (y4*error4));
    line4b->Draw("");
    TLine *line4c = new TLine(x4 - 0.1, y4 - (y4*error4), x4 + 0.1, y4 - (y4*error4));
    line4c->Draw("");
  }
  
  legend1->Draw();
  c1->Draw();
  
#ifdef useCal
  c1->SaveAs("rejectionFactors_Cal_Cher.png");
#elif noCal
  c1->SaveAs("rejectionFactors_Cher.png");
#endif
}
