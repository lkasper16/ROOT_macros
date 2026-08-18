#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>


int FindLeadingEdge(TH1 *h, double frac=0.05) {
  double thresh = frac*h->GetMaximum();
  for (int i=1;i<=h->GetNbinsX();i++) {
    if (h->GetBinContent(i) >= thresh) return i;
  }
  return 1;
}
void ShiftHistogram(TH1 *h, int shift) {
  int nx = h->GetNbinsX();
  std::vector<double> content(nx+2,0.);
  std::vector<double> error(nx+2,0.);
  for (int x=1;x<=nx;x++) {
    int j = x-shift;
    if (j>=1 && j<=nx) {
      content[j]=h->GetBinContent(x);
      error[j]=h->GetBinError(x);
    }
  }
  for (int x=1;x<=nx;x++) {
    h->SetBinContent(x,content[x]);
    h->SetBinError(x,error[x]);
  }
}

void AlignLeadingEdge(TH1 *reference, TH1 *h) {
  int ref = FindLeadingEdge(reference);
  int cur = FindLeadingEdge(h);
  ShiftHistogram(h, cur-ref);
}

void timeResponseXe() {
	
	TList *HistDQM;
	double TFScaleFactor = -1.;
	int colorList[] = {1,2,209,6,4,94,7,51,28};
  int markerList[] = {3,4,25,27,46,42,30,44,35};
  
	//=======================================
	//PS25 With Radiator (Highest HV Settings)
	
	TFile *file0 = TFile::Open("RootOutput/ps25/Run_006385_Output.root");
	HistDQM = (TList *)file0->Get("HistDQM");
	TObject *obju0 = HistDQM->FindObject("urw_f125_x_amp2d");
	TH2 *u0 = (TH2 *)obju0;
	TFScaleFactor = 1./u0->GetEntries();
  u0->Scale(TFScaleFactor);
	u0->RebinX(4);
	//TH1D *u_0 = u0->ProjectionX("u_0",30,110);
	TH1D *u_0 = u0->ProjectionX("u_0");
  u_0->SetLineColor(colorList[0]);
  u_0->SetMarkerStyle(markerList[0]);
  u_0->SetMarkerSize(2);
  u_0->SetMarkerColor(colorList[0]);
  u_0->SetDirectory(0);
  
  TObject *objg0 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g0 = (TH2 *)objg0;
  TFScaleFactor = 1./g0->GetEntries();
  g0->Scale(TFScaleFactor);
  g0->RebinX(4);
  //TH1D *g_0 = g0->ProjectionX("g_0",70,200);
  TH1D *g_0 = g0->ProjectionX("g_0");
  g_0->SetLineColor(colorList[0]);
  g_0->SetMarkerStyle(markerList[0]);
  g_0->SetMarkerSize(2);
  g_0->SetMarkerColor(colorList[0]);
  g_0->SetDirectory(0);
  
  TObject *objm0 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m0 = (TH2 *)objm0;
  TFScaleFactor = 1./m0->GetEntries();
  m0->Scale(TFScaleFactor);
  m0->RebinX(4);
  //TH1D *m_0 = m0->ProjectionX("m_0",30,160);
  TH1D *m_0 = m0->ProjectionX("m_0");
  m_0->SetLineColor(colorList[0]);
  m_0->SetMarkerStyle(markerList[0]);
  m_0->SetMarkerColor(colorList[0]);
  m_0->SetMarkerSize(2);
  m_0->SetDirectory(0);
  
  //PS25 Without Radiator (Highest HV Settings)
  TFile *file1 = TFile::Open("RootOutput/ps25/Run_006392_Output.root");
  HistDQM = (TList *)file1->Get("HistDQM");
  TObject *obju1 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *u1 = (TH2 *)obju1;
  TFScaleFactor = 1./u1->GetEntries();
  u1->Scale(TFScaleFactor);
  u1->RebinX(4);
  //TH1D *u_1 = u1->ProjectionX("u_1",30,110);
  TH1D *u_1 = u1->ProjectionX("u_1");
  u_1->SetLineColor(colorList[1]);
  u_1->SetMarkerStyle(markerList[1]);
  u_1->SetMarkerColor(colorList[1]);
  u_1->SetMarkerSize(2);
  u_1->SetDirectory(0);
  
  TObject *objg1 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g1 = (TH2 *)objg1;
  TFScaleFactor = 1./g1->GetEntries();
  g1->Scale(TFScaleFactor);
  g1->RebinX(4);
  //TH1D *g_1 = g1->ProjectionX("g_1",70,200);
  TH1D *g_1 = g1->ProjectionX("g_1");
  g_1->SetLineColor(colorList[1]);
  g_1->SetMarkerStyle(markerList[1]);
  g_1->SetMarkerColor(colorList[1]);
  g_1->SetMarkerSize(2);
  g_1->SetDirectory(0);

  TObject *objm1 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m1 = (TH2 *)objm1;
  TFScaleFactor = 1./m1->GetEntries();
  m1->Scale(TFScaleFactor);
  m1->RebinX(4);
  //TH1D *m_1 = m1->ProjectionX("m_1",30,160);
  TH1D *m_1 = m1->ProjectionX("m_1");
  m_1->SetLineColor(colorList[1]);
  m_1->SetMarkerStyle(markerList[1]);
  m_1->SetMarkerColor(colorList[1]);
  m_1->SetMarkerSize(2);
  m_1->SetDirectory(0);
  
  //PS26 With Radiator (Highest HV Settings)
  TFile *file2 = TFile::Open("RootOutput/ps26/Run_008257_Output.root");
  HistDQM = (TList *)file2->Get("HistDQM");
  TObject *obju2 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *u2 = (TH2 *)obju2;
  TFScaleFactor = 1./u2->GetEntries();
  u2->Scale(TFScaleFactor);
  u2->RebinX(4);
  TH1D *u_2 = u2->ProjectionX("u_2");
  u_2->SetLineColor(colorList[2]);
  u_2->SetMarkerStyle(markerList[2]);
  u_2->SetMarkerColor(colorList[2]);
  u_2->SetMarkerSize(2);
  u_2->SetDirectory(0);
  
  TObject *objg2 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g2 = (TH2 *)objg2;
  TFScaleFactor = 1./g2->GetEntries();
  g2->Scale(TFScaleFactor);
  g2->RebinX(4);
  TH1D *g_2 = g2->ProjectionX("g_2");
  g_2->SetLineColor(colorList[2]);
  g_2->SetMarkerStyle(markerList[2]);
  g_2->SetMarkerColor(colorList[2]);
  g_2->SetMarkerSize(2);
  g_2->SetDirectory(0);
  
  TObject *objm2 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m2 = (TH2 *)objm2;
  TFScaleFactor = 1./m2->GetEntries();
  m2->Scale(TFScaleFactor);
  m2->RebinX(4);
  TH1D *m_2 = m2->ProjectionX("m_2");
  m_2->SetLineColor(colorList[2]);
  m_2->SetMarkerStyle(markerList[2]);
  m_2->SetMarkerColor(colorList[2]);
  m_2->SetMarkerSize(2);
  m_2->SetDirectory(0);
  
  //PS26 Without Radiator (Highest HV Settings)
  TFile *file3 = TFile::Open("RootOutput/ps26/Run_008266_Output.root");
  HistDQM = (TList *)file3->Get("HistDQM");
  TObject *obju3 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *u3 = (TH2 *)obju3;
  TFScaleFactor = 1./u3->GetEntries();
  u3->Scale(TFScaleFactor);
  u3->RebinX(4);
  TH1D *u_3 = u3->ProjectionX("u_3");
  u_3->SetLineColor(colorList[3]);
  u_3->SetMarkerStyle(markerList[3]);
  u_3->SetMarkerColor(colorList[3]);
  u_3->SetMarkerSize(2);
  u_3->SetDirectory(0);
  
  TObject *objg3 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g3 = (TH2 *)objg3;
  TFScaleFactor = 1./g3->GetEntries();
  g3->Scale(TFScaleFactor);
  g3->RebinX(4);
  TH1D *g_3 = g3->ProjectionX("g_3");
  g_3->SetLineColor(colorList[3]);
  g_3->SetMarkerStyle(markerList[3]);
  g_3->SetMarkerColor(colorList[3]);
  g_3->SetMarkerSize(2);
  g_3->SetDirectory(0);
  
  TObject *objm3 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m3 = (TH2 *)objm3;
  TFScaleFactor = 1./m3->GetEntries();
  m3->Scale(TFScaleFactor);
  m3->RebinX(4);
  TH1D *m_3 = m3->ProjectionX("m_3");
  m_3->SetLineColor(colorList[3]);
  m_3->SetMarkerStyle(markerList[3]);
  m_3->SetMarkerColor(colorList[3]);
  m_3->SetMarkerSize(2);
  m_3->SetDirectory(0);
  
  /*
  TFile *file4 = TFile::Open("RootOutput/ps25/Run_006382_Output.root");
  HistDQM = (TList *)file4->Get("HistDQM");
  TObject *obj4 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *tf4 = (TH2 *)obj4;
  TFScaleFactor = 1./tf4->GetEntries();
  tf4->Scale(TFScaleFactor);
  tf4->RebinX(4);
  TH1D *tf_4 = tf4->ProjectionX("LG HTF RAD",45,105);
  tf_4->SetLineColor(colorList[4]);
  tf_4->SetMarkerStyle(20); //filled circle
  tf_4->SetMarkerColor(colorList[4]);
  tf_4->SetMarkerSize(2);
  tf_4->SetDirectory(0);
  
  TObject *objg4 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g4 = (TH2 *)objg4;
  TFScaleFactor = 1./g4->GetEntries();
  g4->Scale(TFScaleFactor);
  g4->RebinX(4);
  TH1D *g_4 = g4->ProjectionX("LG AL RAD",55,180);
  g_4->SetLineColor(colorList[4]);
  g_4->SetMarkerStyle(20); //filled circle
  g_4->SetMarkerColor(colorList[4]);
  g_4->SetMarkerSize(2);
  g_4->SetDirectory(0);

  TObject *objm4 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m4 = (TH2 *)objm4;
  TFScaleFactor = 1./m4->GetEntries();
  m4->Scale(TFScaleFactor);
  m4->RebinX(4);
  TH1D *m_4 = m4->ProjectionX("LG AL RAD",30,130);
  m_4->SetLineColor(colorList[4]);
  m_4->SetMarkerStyle(20); //filled circle
  m_4->SetMarkerColor(colorList[4]);
  m_4->SetMarkerSize(2);
  m_4->SetDirectory(0);
  
  
  TFile *file5 = TFile::Open("RootOutput/ps25/Run_006385_Output.root");
  //TFile *file5 = TFile::Open("RootOutput/ps25/Run_006388_Output.root");
  HistDQM = (TList *)file5->Get("HistDQM");
  TObject *obj5 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *tf5 = (TH2 *)obj5;
  TFScaleFactor = 1./tf5->GetEntries();
  tf5->Scale(TFScaleFactor);
  tf5->RebinX(4);
  TH1D *tf_5 = tf5->ProjectionX("HG HTF RAD",45,105);
  tf_5->SetLineColor(colorList[5]);
  tf_5->SetMarkerStyle(20); //filled circle
  tf_5->SetMarkerColor(colorList[5]);
  tf_5->SetMarkerSize(2);
  tf_5->SetDirectory(0);

  TObject *objg5 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g5 = (TH2 *)objg5;
  TFScaleFactor = 1./g5->GetEntries();
  g5->Scale(TFScaleFactor);
  g5->RebinX(4);
  TH1D *g_5 = g5->ProjectionX("HG AL RAD",55,180);
  g_5->SetLineColor(colorList[5]);
  g_5->SetMarkerStyle(20); //filled circle
  g_5->SetMarkerColor(colorList[5]);
  g_5->SetMarkerSize(2);
  g_5->SetDirectory(0);

  TObject *objm5 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m5 = (TH2 *)objm5;
  TFScaleFactor = 1./m5->GetEntries();
  m5->Scale(TFScaleFactor);
  m5->RebinX(4);
  TH1D *m_5 = m5->ProjectionX("HG AL RAD",30,130);
  m_5->SetLineColor(colorList[5]);
  m_5->SetMarkerStyle(20); //filled circle
  m_5->SetMarkerColor(colorList[5]);
  m_5->SetMarkerSize(2);
  m_5->SetDirectory(0);
  
  
  TFile *file6 = TFile::Open("RootOutput/ps25/Run_006390_Output.root");
  //TFile *file6 = TFile::Open("RootOutput/ps25/Run_006391_Output.root");
  HistDQM = (TList *)file6->Get("HistDQM");
  TObject *obj6 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *tf6 = (TH2 *)obj6;
  TFScaleFactor = 1./tf6->GetEntries();
  tf6->Scale(TFScaleFactor);
  tf6->RebinX(4);
  TH1D *tf_6 = tf6->ProjectionX("HG HTF NORAD",45,105);
  tf_6->SetLineColor(colorList[6]);
  tf_6->SetMarkerStyle(20); //filled circle
  tf_6->SetMarkerColor(colorList[6]);
  tf_6->SetMarkerSize(2);
  tf_6->SetDirectory(0);
  
  TObject *objg6 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g6 = (TH2 *)objg6;
  TFScaleFactor = 1./g6->GetEntries();
  g6->Scale(TFScaleFactor);
  g6->RebinX(4);
  TH1D *g_6 = g6->ProjectionX("HG AL NORAD",55,180);
  g_6->SetLineColor(colorList[6]);
  g_6->SetMarkerStyle(20); //filled circle
  g_6->SetMarkerColor(colorList[6]);
  g_6->SetMarkerSize(2);
  g_6->SetDirectory(0);

  TObject *objm6 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m6 = (TH2 *)objm6;
  TFScaleFactor = 1./m6->GetEntries();
  m6->Scale(TFScaleFactor);
  m6->RebinX(4);
  TH1D *m_6 = m6->ProjectionX("HG AL NORAD",30,130);
  m_6->SetLineColor(colorList[6]);
  m_6->SetMarkerStyle(20); //filled circle
  m_6->SetMarkerColor(colorList[6]);
  m_6->SetMarkerSize(2);
  m_6->SetDirectory(0);
  
  
  TFile *file7 = TFile::Open("RootOutput/ps25/Run_006393_Output.root");
  HistDQM = (TList *)file7->Get("HistDQM");
  TObject *obj7 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *tf7 = (TH2 *)obj7;
  TFScaleFactor = 1./tf7->GetEntries();
  tf7->Scale(TFScaleFactor);
  tf7->RebinX(4);
  TH1D *tf_7 = tf7->ProjectionX("LG HTF NORAD",45,105);
  tf_7->SetLineColor(colorList[7]);
  tf_7->SetMarkerStyle(20); //filled circle
  tf_7->SetMarkerColor(colorList[7]);
  tf_7->SetMarkerSize(2);
  tf_7->SetDirectory(0);
  
  TObject *objg7 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g7 = (TH2 *)objg7;
  TFScaleFactor = 1./g7->GetEntries();
  g7->Scale(TFScaleFactor);
  g7->RebinX(4);
  TH1D *g_7 = g7->ProjectionX("LG AL NORAD",55,180);
  g_7->SetLineColor(colorList[7]);
  g_7->SetMarkerStyle(20); //filled circle
  g_7->SetMarkerColor(colorList[7]);
  g_7->SetMarkerSize(2);
  g_7->SetDirectory(0);
  
  TObject *objm7 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m7 = (TH2 *)objm7;
  TFScaleFactor = 1./m7->GetEntries();
  m7->Scale(TFScaleFactor);
  m7->RebinX(4);
  TH1D *m_7 = m7->ProjectionX("LG AL NORAD",30,130);
  m_7->SetLineColor(colorList[7]);
  m_7->SetMarkerStyle(20); //filled circle
  m_7->SetMarkerColor(colorList[7]);
  m_7->SetMarkerSize(2);
  m_7->SetDirectory(0);
  */
  //===============================================================================
  //    Make Plots
  //===============================================================================
  
  //==== Artificially set leading edges to the same place in time, for all data sets
  AlignLeadingEdge(u_0, u_1);
  AlignLeadingEdge(u_0, u_2);
  AlignLeadingEdge(u_0, u_3);
  
  AlignLeadingEdge(g_0, g_1);
  AlignLeadingEdge(g_0, g_2);
  AlignLeadingEdge(g_0, g_3);
  
  AlignLeadingEdge(m_0, m_1);
  AlignLeadingEdge(m_0, m_2);
  AlignLeadingEdge(m_0, m_3);
  
  //=========== uRWELL Plot =================
	TCanvas *c0 = new TCanvas("c0","uRWell-TRD ADC Response in Time", 1400, 1000);
	gStyle->SetOptStat(0);
	c0->cd();
 	gPad->SetGridy();
	TLegend *l0 = new TLegend(0.38,0.685,0.9,0.9);
	l0->AddEntry(u_0,"2025 Xe:CO_{2}, 20cm Fleece Rad","lp");
  l0->AddEntry(u_1,"2025 Xe:CO_{2}, No Rad","lp");
  l0->AddEntry(u_2,"2026 Xe:ISO, 20cm Fleece Rad","lp");
	l0->AddEntry(u_3,"2026 Xe:ISO, No Rad","lp");
  
	u_0->GetYaxis()->SetTitle("ADC Amplitude (Pulses / numEvents)");
	u_0->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  //u_0->GetYaxis()->SetNdivisions(520);
	u_0->GetXaxis()->SetRangeUser(45,155);
  u_0->SetMaximum(u_0->GetMaximum()+20.);
	u_0->SetTitle("Hybrid #muRWell-TRD ADC Response in Time");
  u_0->GetYaxis()->SetTitleSize(0.052);
  u_0->GetYaxis()->SetLabelSize(0.043);
  u_0->GetYaxis()->SetTitleOffset(0.85);
  u_0->GetXaxis()->SetTitleSize(0.052);
  u_0->GetXaxis()->SetLabelSize(0.043);
	u_0->Draw("");
	u_1->Draw("same");
  u_2->Draw("same");
  u_3->Draw("same");
  l0->SetTextSize(0.042);
	l0->Draw();
	gPad->Modified();
	gPad->Update();
	c0->SaveAs("urw_time_Comparison_v1.pdf");
  
  //=========== uRWELL-TRD Ratio Plot =================
  TCanvas *c0_r = new TCanvas("c0_r","c0_r", 1400, 1000);
	gStyle->SetOptStat(0);
	c0_r->cd();
 	gPad->SetGridy();
 	gPad->SetLeftMargin(0.135);
 	gPad->SetBottomMargin(0.135);
 	gPad->SetTopMargin(0.135);

 	TLegend *l0r = new TLegend(0.25,0.7,0.6,0.865);
	//l0r->SetNColumns(2);
	
	u_0->Divide(u_1);
  u_2->Divide(u_3);
  u_2->GetYaxis()->SetTitle("#splitline{(ADC Response, Radiator) /}{ (ADC Response, No Radiator)}");
  u_2->GetYaxis()->SetLabelSize(0.044);
  u_2->GetYaxis()->SetTitleSize(0.047);
	u_2->GetXaxis()->SetLabelSize(0.044);
  u_2->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  u_2->GetXaxis()->SetTitleSize(0.05);
	u_2->SetTitle("Hybrid #muRWELL-TRD (Radiator) / (No Radiator) ADC Response Ratio in Time");
	u_2->SetMaximum(5.);
	u_2->SetMinimum(0.8);
	u_2->GetXaxis()->SetRangeUser(45,155);
	//u_2->GetYaxis()->SetNdivisions(520);
  l0r->AddEntry(u_0,"2025 Xe:CO_{2}","lp");
	l0r->AddEntry(u_2,"2026 Xe:ISO","lp");
	u_2->Draw();
	u_0->Draw("same");
	l0r->SetTextSize(0.042);
	l0r->Draw();
	gPad->Modified();
	gPad->Update();
	c0_r->SaveAs("urw_Xe_ratios_v1.pdf");
  
  //=========== GEM Plot =================
  TCanvas *c1 = new TCanvas("c1","Triple GEM-TRD ADC Response in Time", 1400, 1000);
  gStyle->SetOptStat(0);
  c1->cd();
  gPad->SetGridy();
  TLegend *l1 = new TLegend(0.38,0.685,0.9,0.9);
  l1->AddEntry(g_0,"2025 Xe:CO_{2}, 20cm Fleece Rad","lp");
  l1->AddEntry(g_1,"2025 Xe:CO_{2}, No Rad","lp");
  l1->AddEntry(g_2,"2026 Xe:ISO, 20cm Fleece Rad","lp");
  l1->AddEntry(g_3,"2026 Xe:ISO, No Rad","lp");
  
  g_0->GetYaxis()->SetTitle("ADC Amplitude (Pulses / nEvents)");
  g_0->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  //g_0->GetYaxis()->SetNdivisions(520);
  g_0->GetXaxis()->SetRangeUser(60,150);
  g_0->SetMaximum(g_0->GetMaximum()+25.);
  g_0->SetTitle("Triple GEM-TRD ADC Response in Time");
  g_0->GetYaxis()->SetTitleSize(0.052);
  g_0->GetYaxis()->SetLabelSize(0.043);
  g_0->GetYaxis()->SetTitleOffset(0.85);
  g_0->GetXaxis()->SetTitleSize(0.052);
  g_0->GetXaxis()->SetLabelSize(0.043);
  g_0->Draw("");
  g_1->Draw("same");
  g_2->Draw("same");
  g_3->Draw("same");
  l1->SetTextSize(0.042);
  l1->Draw();
  gPad->Modified();
	gPad->Update();
  c1->SaveAs("gem_time_Comparison_v1.pdf");
  
  
  //=========== GEM Ratio Plot =================
  TCanvas *c1_r = new TCanvas("c1_r","c1_r", 1400, 1000);
	gStyle->SetOptStat(0);
	c1_r->cd();
 	gPad->SetGridy();
 	gPad->SetLeftMargin(0.135);
 	gPad->SetBottomMargin(0.135);
 	gPad->SetTopMargin(0.135);
 	TLegend *l1r = new TLegend(0.3,0.7,0.6,0.865);
	//l1r->SetNColumns(2);
	
	g_0->Divide(g_1);
  g_2->Divide(g_3);
  g_2->GetYaxis()->SetTitle("#splitline{(ADC Response, Radiator) /}{ (ADC Response, No Radiator)}");
  g_2->GetYaxis()->SetLabelSize(0.044);
  g_2->GetYaxis()->SetTitleSize(0.047);
	g_2->GetXaxis()->SetLabelSize(0.044);
	g_2->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  g_2->GetXaxis()->SetTitleSize(0.05);
	g_2->SetTitle("Triple-GEM (Radiator) / (No Radiator) ADC Response Ratio in Time");
	g_2->SetMaximum(5.);
	g_2->SetMinimum(0.8);
	g_2->GetXaxis()->SetRangeUser(60,150);
	//g_2->GetYaxis()->SetNdivisions(520);
  l1r->AddEntry(g_0,"2025 Xe:CO_{2}","lp");
	l1r->AddEntry(g_2,"2026 Xe:ISO","lp");
	g_2->Draw();
	g_0->Draw("same");
	l1r->SetTextSize(0.042);
	l1r->Draw();
	gPad->Modified();
	gPad->Update();
	c1_r->SaveAs("gem_Xe_ratios_v1.pdf");
	
	
  
  //=========== MMG Plot =================
  TCanvas *c2 = new TCanvas("c2","MMG1-TRD ADC Response in Time for XeCO2", 1400, 1000);
  gStyle->SetOptStat(0);
  c2->cd();
  gPad->SetGridy();
  TLegend *l2 = new TLegend(0.38,0.685,0.9,0.9);
  l2->AddEntry(m_0,"2025 Xe:CO_{2}, 20cm Fleece Rad","lp");
  l2->AddEntry(m_1,"2025 Xe:CO_{2}, No Rad","lp");
  l2->AddEntry(m_2,"2026 Xe:ISO, 20cm Fleece Rad","lp");
  l2->AddEntry(m_3,"2026 Xe:ISO, No Rad","lp");
  
  m_0->GetYaxis()->SetTitle("ADC Amplitude (Pulses / nEvents)");
  m_0->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  //m_0->GetYaxis()->SetNdivisions(520);
  m_0->GetXaxis()->SetRangeUser(50,170);
  m_0->SetMaximum(m_0->GetMaximum()+25.);
  m_0->SetTitle("Hybrid MMG-TRD ADC Response in Time");
  m_0->GetYaxis()->SetTitleSize(0.052);
  m_0->GetYaxis()->SetLabelSize(0.043);
  m_0->GetYaxis()->SetTitleOffset(0.85);
  m_0->GetXaxis()->SetTitleSize(0.052);
  m_0->GetXaxis()->SetLabelSize(0.043);
  m_0->Draw("");
  m_1->Draw("same");
  m_2->Draw("same");
  m_3->Draw("same");
  l2->SetTextSize(0.042);
  l2->Draw();
  gPad->Modified();
	gPad->Update();
  c2->SaveAs("mmg_time_Comparison_v1.pdf");
  
  //=========== MMG Ratio Plot =================
  TCanvas *c2_r = new TCanvas("c2_r","c2_r", 1400, 1000);
	gStyle->SetOptStat(0);
	c2_r->cd();
 	gPad->SetGridy();
 	gPad->SetLeftMargin(0.135);
 	gPad->SetBottomMargin(0.135);
 	gPad->SetTopMargin(0.135);
 	TLegend *l2r = new TLegend(0.3,0.7,0.6,0.865);
	//l2r->SetNColumns(2);
	
	m_0->Divide(m_1);
  m_2->Divide(m_3);
  m_2->GetYaxis()->SetTitle("#splitline{(ADC Response, Radiator) /}{ (ADC Response, No Radiator)}");
  m_2->GetYaxis()->SetLabelSize(0.044);
  m_2->GetYaxis()->SetTitleSize(0.047);
	m_2->GetXaxis()->SetLabelSize(0.044);
	m_2->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  m_2->GetXaxis()->SetTitleSize(0.05);
	m_2->SetTitle("Hybrid MMG-TRD (Radiator) / (No Radiator) ADC Response Ratio in Time");
	m_2->SetMaximum(5.);
	m_2->SetMinimum(0.8);
	m_2->GetXaxis()->SetRangeUser(50,170);
	//m_2->GetYaxis()->SetNdivisions(520);
  l2r->AddEntry(m_0,"2025 Xe:CO_{2}","lp");
	l2r->AddEntry(m_2,"2026 Xe:ISO","lp");
	m_2->Draw();
	m_0->Draw("same");
	l2r->SetTextSize(0.042);
	l2r->Draw();
	gPad->Modified();
	gPad->Update();
	c2_r->SaveAs("mmg_Xe_ratios_v1.pdf");
}
