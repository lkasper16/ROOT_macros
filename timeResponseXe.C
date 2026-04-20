#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void timeResponseXe() {
	
	TList *HistDQM;
	double TFScaleFactor = -1.;
	double DFScaleFactor = -1.;
	double dVScaleFactor = -1.;
  double IFScaleFactor = -1.;
	int colorList[] = {94,2,209,4,7,1,6,51};
  
	//=======================================
	//uRWell-TRD Varied TF
	
	TFile *file0 = TFile::Open("RootOutput/ps25/Run_006296_Output.root");
	HistDQM = (TList *)file0->Get("HistDQM");
	TObject *obj0 = HistDQM->FindObject("urw_f125_x_amp2d");
	TH2 *tf0 = (TH2 *)obj0;
	TFScaleFactor = 1./tf0->GetEntries();
  tf0->Scale(TFScaleFactor);
	tf0->RebinX(4);
	TH1D *tf_0 = tf0->ProjectionX("LG RAD",45,105);
  tf_0->SetLineColor(colorList[0]);
  tf_0->SetMarkerStyle(20); //filled circle
  tf_0->SetMarkerSize(2);
  tf_0->SetMarkerColor(colorList[0]);
  tf_0->SetDirectory(0);
  
  TObject *objg0 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g0 = (TH2 *)objg0;
  TFScaleFactor = 1./g0->GetEntries();
  g0->Scale(TFScaleFactor);
  g0->RebinX(4);
  TH1D *g_0 = g0->ProjectionX("LG CU RAD",55,180);
  g_0->SetLineColor(colorList[0]);
  g_0->SetMarkerStyle(20); //filled circle
  g_0->SetMarkerSize(2);
  g_0->SetMarkerColor(colorList[0]);
  g_0->SetDirectory(0);
  
  TObject *objm0 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m0 = (TH2 *)objm0;
  TFScaleFactor = 1./m0->GetEntries();
  m0->Scale(TFScaleFactor);
  m0->RebinX(4);
  TH1D *m_0 = m0->ProjectionX("LG CU RAD",30,130);
  m_0->SetLineColor(colorList[0]);
  m_0->SetMarkerStyle(20); //filled circle
  m_0->SetMarkerColor(colorList[0]);
  m_0->SetMarkerSize(2);
  m_0->SetDirectory(0);
  
  
  TFile *file1 = TFile::Open("RootOutput/ps25/Run_006317_Output.root");
  HistDQM = (TList *)file1->Get("HistDQM");
  TObject *obj1 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *tf1 = (TH2 *)obj1;
  TFScaleFactor = 1./tf1->GetEntries();
  tf1->Scale(TFScaleFactor);
  tf1->RebinX(4);
  TH1D *tf_1 = tf1->ProjectionX("LG NORAD",45,105);
  tf_1->SetLineColor(colorList[1]);
  tf_1->SetMarkerStyle(20); //filled circle
  tf_1->SetMarkerColor(colorList[1]);
  tf_1->SetMarkerSize(2);
  tf_1->SetDirectory(0);
  
  TObject *objg1 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g1 = (TH2 *)objg1;
  TFScaleFactor = 1./g1->GetEntries();
  g1->Scale(TFScaleFactor);
  g1->RebinX(4);
  TH1D *g_1 = g1->ProjectionX("LG CU NORAD",55,180);
  g_1->SetLineColor(colorList[1]);
  g_1->SetMarkerStyle(20); //filled circle
  g_1->SetMarkerColor(colorList[1]);
  g_1->SetMarkerSize(2);
  g_1->SetDirectory(0);

  TObject *objm1 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m1 = (TH2 *)objm1;
  TFScaleFactor = 1./m1->GetEntries();
  m1->Scale(TFScaleFactor);
  m1->RebinX(4);
  TH1D *m_1 = m1->ProjectionX("LG CU NORAD",30,130);
  m_1->SetLineColor(colorList[1]);
  m_1->SetMarkerStyle(20); //filled circle
  m_1->SetMarkerColor(colorList[1]);
  m_1->SetMarkerSize(2);
  m_1->SetDirectory(0);
  
  
  TFile *file2 = TFile::Open("RootOutput/ps25/Run_006303_Output.root");
  //TFile *file2 = TFile::Open("RootOutput/ps25/Run_006304_Output.root");
  HistDQM = (TList *)file2->Get("HistDQM");
  TObject *obj2 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *tf2 = (TH2 *)obj2;
  TFScaleFactor = 1./tf2->GetEntries();
  tf2->Scale(TFScaleFactor);
  tf2->RebinX(4);
  TH1D *tf_2 = tf2->ProjectionX("HG RAD",45,105);
  tf_2->SetLineColor(colorList[2]);
  tf_2->SetMarkerStyle(20); //filled circle
  tf_2->SetMarkerColor(colorList[2]);
  tf_2->SetMarkerSize(2);
  tf_2->SetDirectory(0);
  
  TObject *objg2 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g2 = (TH2 *)objg2;
  TFScaleFactor = 1./g2->GetEntries();
  g2->Scale(TFScaleFactor);
  g2->RebinX(4);
  TH1D *g_2 = g2->ProjectionX("HG CU RAD",55,180);
  g_2->SetLineColor(colorList[2]);
  g_2->SetMarkerStyle(20); //filled circle
  g_2->SetMarkerColor(colorList[2]);
  g_2->SetMarkerSize(2);
  g_2->SetDirectory(0);
  
  TObject *objm2 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m2 = (TH2 *)objm2;
  TFScaleFactor = 1./m2->GetEntries();
  m2->Scale(TFScaleFactor);
  m2->RebinX(4);
  TH1D *m_2 = m2->ProjectionX("HG CU RAD",30,130);
  m_2->SetLineColor(colorList[2]);
  m_2->SetMarkerStyle(20); //filled circle
  m_2->SetMarkerColor(colorList[2]);
  m_2->SetMarkerSize(2);
  m_2->SetDirectory(0);
  
  
  TFile *file3 = TFile::Open("RootOutput/ps25/Run_006320_Output.root");
  //TFile *file3 = TFile::Open("RootOutput/ps25/Run_006319_Output.root");
  HistDQM = (TList *)file3->Get("HistDQM");
  TObject *obj3 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *tf3 = (TH2 *)obj3;
  TFScaleFactor = 1./tf3->GetEntries();
  tf3->Scale(TFScaleFactor);
  tf3->RebinX(4);
  TH1D *tf_3 = tf3->ProjectionX("HG NORAD",45,105);
  tf_3->SetLineColor(colorList[3]);
  tf_3->SetMarkerStyle(20); //filled circle
  tf_3->SetMarkerColor(colorList[3]);
  tf_3->SetMarkerSize(2);
  tf_3->SetDirectory(0);
  
  TObject *objg3 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g3 = (TH2 *)objg3;
  TFScaleFactor = 1./g3->GetEntries();
  g3->Scale(TFScaleFactor);
  g3->RebinX(4);
  TH1D *g_3 = g3->ProjectionX("HG CU NORAD",55,180);
  g_3->SetLineColor(colorList[3]);
  g_3->SetMarkerStyle(20); //filled circle
  g_3->SetMarkerColor(colorList[3]);
  g_3->SetMarkerSize(2);
  g_3->SetDirectory(0);
  
  TObject *objm3 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m3 = (TH2 *)objm3;
  TFScaleFactor = 1./m3->GetEntries();
  m3->Scale(TFScaleFactor);
  m3->RebinX(4);
  TH1D *m_3 = m3->ProjectionX("HG CU NORAD",30,130);
  m_3->SetLineColor(colorList[3]);
  m_3->SetMarkerStyle(20); //filled circle
  m_3->SetMarkerColor(colorList[3]);
  m_3->SetMarkerSize(2);
  m_3->SetDirectory(0);
  
  
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
  
  //===============================================================================
  //    Make Plots
  //===============================================================================
  
  //=========== uRWELL Plot =================
	TCanvas *c0 = new TCanvas("c0","uRWell-TRD ADC Response in Time for XeCO2", 1400, 1000);
	gStyle->SetOptStat(0);
	c0->cd();
 	gPad->SetGridy();
	
	TLegend *l0 = new TLegend(0.42,0.685,0.9,0.9);
	//l0->AddEntry(tf_0,"Low TF, 'Low Gain' 20cm Fleece Rad","lp");
  //l0->AddEntry(tf_1,"Low TF, 'Low Gain' No Rad","lp");
  l0->AddEntry(tf_2,"'Low TF High Gain' With Rad","lp");
	l0->AddEntry(tf_3,"'Low TF High Gain' No Rad","lp");
  //l0->AddEntry(tf_4,"High TF, 'Low Gain' 20cm Fleece Rad","lp");
  l0->AddEntry(tf_5,"'High TF High Gain' With Rad","lp");
  l0->AddEntry(tf_6,"'High TF High Gain' No Rad","lp");
  //l0->AddEntry(tf_7,"High TF, 'Low Gain' No Rad","lp");
  l0->SetTextSize(0.042);
  
	tf_5->GetYaxis()->SetTitle("ADC Amplitude (Pulses / nEvents)");
	tf_5->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  //tf_5->GetYaxis()->SetNdivisions(520);
	tf_5->GetXaxis()->SetRangeUser(40,160);
  tf_5->SetMaximum(tf_5->GetMaximum()+15.);
	tf_5->SetTitle("#muRWell+GEM-TRD ADC Response in Time for Xe:CO_{2} 90:10");
  tf_5->GetYaxis()->SetTitleSize(0.052);
  tf_5->GetYaxis()->SetLabelSize(0.043);
  tf_5->GetYaxis()->SetTitleOffset(0.85);
  tf_5->GetXaxis()->SetTitleSize(0.052);
  tf_5->GetXaxis()->SetLabelSize(0.043);
	tf_5->Draw("");
	//tf_1->Draw("same");
  tf_2->Draw("same");
  tf_3->Draw("same");
  //tf_4->Draw("same");
  //tf_0->Draw("same");
  tf_6->Draw("same");
  //tf_7->Draw("same");
  
	l0->Draw();
	c0->SaveAs("urw_time_Xe_Comparison_Feb26.png");
  
  //=========== uRWELL Ratio Plot =================
  TCanvas *c0_r = new TCanvas("c0_r","c0_r", 1400, 1000);
	gStyle->SetOptStat(0);
	c0_r->cd();
 	gPad->SetGridy();
 	gPad->SetLeftMargin(0.135); //0.18
 	gPad->SetBottomMargin(0.135);
 	
 	TLegend *l0r = new TLegend(0.25,0.7,0.6,0.9);
	//l0r->SetNColumns(2);
	
	tf_2->Divide(tf_3);
  tf_5->Divide(tf_6);
  tf_2->GetYaxis()->SetTitle("#splitline{(ADC Response, Radiator) /}{ (ADC Response, No Radiator)}");
  tf_2->GetYaxis()->SetLabelSize(0.044);
  tf_2->GetYaxis()->SetTitleSize(0.047);
	tf_2->GetXaxis()->SetLabelSize(0.044);
  tf_2->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  tf_2->GetXaxis()->SetTitleSize(0.05);
	tf_2->SetTitle("#muRWELL+GEM (Radiator) / (No Radiator) ADC Response Ratio in Time");
	tf_2->SetMaximum(4.);
	tf_2->SetMinimum(0.5);	
	tf_2->GetXaxis()->SetRangeUser(50,140);
	tf_2->GetYaxis()->SetNdivisions(520);
  l0r->AddEntry(tf_2,"Electrons with Low TF","lp");
	l0r->AddEntry(tf_5,"Electrons with High TF","lp");
	tf_2->Draw();
	tf_5->Draw("same");
	l0r->SetTextSize(0.041);
	l0r->Draw();
	c0_r->SaveAs("urw_time_Xe_ratios_Feb26.png");
  
  //=========== GEM Plot =================
  TCanvas *c1 = new TCanvas("c1","Triple GEM-TRD ADC Response in Time for XeCO2", 1400, 1000);
  gStyle->SetOptStat(0);
  c1->cd();
  gPad->SetGridy();
  
  TLegend *l1 = new TLegend(0.45,0.685,0.9,0.9);
  //l1->AddEntry(g_0,"'Low Gain' 5um Cu, 20cm Fleece Rad","lp");
  //l1->AddEntry(g_1,"'Low Gain' 5um Cu, No Rad","lp");
  l1->AddEntry(g_2,"'High Gain' Cu, With Rad","lp");
  l1->AddEntry(g_3,"'High Gain' Cu, No Rad","lp");
  //l1->AddEntry(g_4,"'Low Gain' 0.1um Al, 20cm Fleece Rad","lp");
  l1->AddEntry(g_5,"'High Gain' Al, With Rad","lp");
  l1->AddEntry(g_6,"'High Gain' Al, No Rad","lp");
  //l1->AddEntry(g_7,"'Low Gain' 0.1um Al, No Rad","lp");
  l1->SetTextSize(0.042);
  
  g_5->GetYaxis()->SetTitle("ADC Amplitude (Pulses / nEvents)");
  g_5->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  //g_5->GetYaxis()->SetNdivisions(520);
  g_5->GetXaxis()->SetRangeUser(50,160);
  g_5->SetMaximum(g_5->GetMaximum()+21.);
  g_5->SetTitle("Triple GEM-TRD ADC Response in Time for Xe:CO_{2} 90:10");
  g_5->GetYaxis()->SetTitleSize(0.052);
  g_5->GetYaxis()->SetLabelSize(0.043);
  g_5->GetYaxis()->SetTitleOffset(0.85);
  g_5->GetXaxis()->SetTitleSize(0.052);
  g_5->GetXaxis()->SetLabelSize(0.043);
  g_5->Draw("");
  g_2->Draw("same");
  g_3->Draw("same");
  g_6->Draw("same");
  
  l1->Draw();
  c1->SaveAs("gem_time_Xe_Comparison_Feb26.png");
  
  
  //=========== GEM Ratio Plot =================
  TCanvas *c1_r = new TCanvas("c1_r","c1_r", 1400, 1000);
	gStyle->SetOptStat(0);
	c1_r->cd();
 	gPad->SetGridy();
 	gPad->SetLeftMargin(0.135); //0.18
 	gPad->SetBottomMargin(0.135);
 	
 	TLegend *l1r = new TLegend(0.3,0.7,0.6,0.9);
	//l1r->SetNColumns(2);
	
	g_2->Divide(g_3);
  g_5->Divide(g_6);
  g_2->GetYaxis()->SetTitle("#splitline{(ADC Response, Radiator) /}{ (ADC Response, No Radiator)}");
  g_2->GetYaxis()->SetLabelSize(0.044);
  g_2->GetYaxis()->SetTitleSize(0.047);
	g_2->GetXaxis()->SetLabelSize(0.044);
	g_2->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  g_2->GetXaxis()->SetTitleSize(0.05);
	g_2->SetTitle("Triple-GEM (Radiator) / (No Radiator) ADC Response Ratio in Time");
	g_2->SetMaximum(4.);
	g_2->SetMinimum(0.5);	
	g_2->GetXaxis()->SetRangeUser(65,145);
	g_2->GetYaxis()->SetNdivisions(520);
  l1r->AddEntry(g_2,"Electrons with Cu","lp");
	l1r->AddEntry(g_5,"Electrons with Al","lp");
	g_2->Draw();
	g_5->Draw("same");
	l1r->SetTextSize(0.041);
	l1r->Draw();
	c1_r->SaveAs("gem_time_Xe_ratios_Feb26.png");
	
	
  
  //=========== MMG Plot =================
  TCanvas *c2 = new TCanvas("c2","MMG1-TRD ADC Response in Time for XeCO2", 1400, 1000);
  gStyle->SetOptStat(0);
  c2->cd();
  gPad->SetGridy();
  
  TLegend *l2 = new TLegend(0.45,0.685,0.9,0.9);
  //l2->AddEntry(m_0,"'Low Gain' 5um Cu, 20cm Fleece Rad","lp");
  //l2->AddEntry(m_1,"'Low Gain' 5um Cu, No Rad","lp");
  l2->AddEntry(m_2,"'High Gain' Cu, With Rad","lp");
  l2->AddEntry(m_3,"'High Gain' Cu, No Rad","lp");
  //l2->AddEntry(m_4,"'Low Gain' 0.1um Al, 20cm Fleece Rad","lp");
  l2->AddEntry(m_5,"'High Gain' Al, With Rad","lp");
  l2->AddEntry(m_6,"'High Gain' Al, No Rad","lp");
  //l2->AddEntry(m_7,"'Low Gain' 0.1um Al, No Rad","lp");
  l2->SetTextSize(0.042);
  
  m_5->GetYaxis()->SetTitle("ADC Amplitude (Pulses / nEvents)");
  m_5->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  //m_5->GetYaxis()->SetNdivisions(520);
  m_5->GetXaxis()->SetRangeUser(45,170);
  m_5->SetMaximum(m_5->GetMaximum()+15.);
  m_5->SetTitle("MMG+GEM-TRD ADC Response in Time for Xe:CO_{2} 90:10");
  m_5->GetYaxis()->SetTitleSize(0.052);
  m_5->GetYaxis()->SetLabelSize(0.043);
  m_5->GetYaxis()->SetTitleOffset(0.85);
  m_5->GetXaxis()->SetTitleSize(0.052);
  m_5->GetXaxis()->SetLabelSize(0.043);
  m_5->Draw("");
  //m_1->Draw("same");
  m_2->Draw("same");
  m_3->Draw("same");
  //m_4->Draw("same");
  //m_0->Draw("same");
  m_6->Draw("same");
  //m_7->Draw("same");
  
  l2->Draw();
  c2->SaveAs("mmg_time_Xe_Comparison_Feb26.png");
  
  //=========== MMG Ratio Plot =================
  TCanvas *c2_r = new TCanvas("c2_r","c2_r", 1400, 1000);
	gStyle->SetOptStat(0);
	c2_r->cd();
 	gPad->SetGridy();
 	gPad->SetLeftMargin(0.135); //0.18
 	gPad->SetBottomMargin(0.135);
 	
 	TLegend *l2r = new TLegend(0.3,0.7,0.6,0.9);
	//l2r->SetNColumns(2);
	
	m_2->Divide(m_3);
  m_5->Divide(m_6);
  m_2->GetYaxis()->SetTitle("#splitline{(ADC Response, Radiator) /}{ (ADC Response, No Radiator)}");
  m_2->GetYaxis()->SetLabelSize(0.044);
  m_2->GetYaxis()->SetTitleSize(0.047);
	m_2->GetXaxis()->SetLabelSize(0.044);
	m_2->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  m_2->GetXaxis()->SetTitleSize(0.05);
	m_2->SetTitle("MMG+GEM (Radiator) / (No Radiator) ADC Response Ratio in Time");
	m_2->SetMaximum(4.);
	m_2->SetMinimum(0.5);	
	m_2->GetXaxis()->SetRangeUser(54,160);
	m_2->GetYaxis()->SetNdivisions(520);
  l2r->AddEntry(m_2,"Electrons with Cu","lp");
	l2r->AddEntry(m_5,"Electrons with Al","lp");
	m_2->Draw();
	m_5->Draw("same");
	l2r->SetTextSize(0.041);
	l2r->Draw();
	c2_r->SaveAs("mmg_time_Xe_ratios_Feb26.png");
}
