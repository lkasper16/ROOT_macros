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
	int colorList[] = {94,2,209,4,7,1,6,51,28};
  
	//=======================================
	//uRWell-TRD Varied TF
	
	TFile *file0 = TFile::Open("RootOutput/ps25/Run_006296_Output.root");
	HistDQM = (TList *)file0->Get("HistDQM");
	TObject *obj0 = HistDQM->FindObject("urw_f125_x_amp2d");
	TH2 *tf0 = (TH2 *)obj0;
	TFScaleFactor = 1./tf0->GetEntries();
  tf0->Scale(TFScaleFactor);
	tf0->RebinX(4);
	TH1D *tf_0 = tf0->ProjectionX("LG RAD",30,110);
  tf_0->SetLineColor(colorList[0]);
  tf_0->SetMarkerStyle(20); //filled circle
  tf_0->SetMarkerColor(colorList[0]);
  tf_0->SetDirectory(0);
  
  TObject *objg0 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g0 = (TH2 *)objg0;
  TFScaleFactor = 1./g0->GetEntries();
  g0->Scale(TFScaleFactor);
  g0->RebinX(4);
  TH1D *g_0 = g0->ProjectionX("LG CU RAD",30,190);
  g_0->SetLineColor(colorList[0]);
  g_0->SetMarkerStyle(20); //filled circle
  g_0->SetMarkerColor(colorList[0]);
  g_0->SetDirectory(0);
  
  TObject *objm0 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TH2 *m0 = (TH2 *)objm0;
  TFScaleFactor = 1./m0->GetEntries();
  m0->Scale(TFScaleFactor);
  m0->RebinX(4);
  TH1D *m_0 = m0->ProjectionX("LG CU RAD",10,160);
  m_0->SetLineColor(colorList[0]);
  m_0->SetMarkerStyle(20); //filled circle
  m_0->SetMarkerColor(colorList[0]);
  m_0->SetDirectory(0);
  
  
  TFile *file1 = TFile::Open("RootOutput/ps25/Run_006317_Output.root");
  HistDQM = (TList *)file1->Get("HistDQM");
  TObject *obj1 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf1 = (TH2 *)obj1;
  TFScaleFactor = 1./tf1->GetEntries();
  tf1->Scale(TFScaleFactor);
  tf1->RebinX(4);
  TH1D *tf_1 = tf1->ProjectionX("LG NORAD",30,110);
  tf_1->SetLineColor(colorList[1]);
  tf_1->SetMarkerStyle(20); //filled circle
  tf_1->SetMarkerColor(colorList[1]);
  tf_1->SetDirectory(0);
  
  TObject *objg1 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g1 = (TH2 *)objg1;
  TFScaleFactor = 1./g1->GetEntries();
  g1->Scale(TFScaleFactor);
  g1->RebinX(4);
  TH1D *g_1 = g1->ProjectionX("LG CU NORAD",30,190);
  g_1->SetLineColor(colorList[1]);
  g_1->SetMarkerStyle(20); //filled circle
  g_1->SetMarkerColor(colorList[1]);
  g_1->SetDirectory(0);

  TObject *objm1 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TH2 *m1 = (TH2 *)objm1;
  TFScaleFactor = 1./m1->GetEntries();
  m1->Scale(TFScaleFactor);
  m1->RebinX(4);
  TH1D *m_1 = m1->ProjectionX("LG CU NORAD",10,160);
  m_1->SetLineColor(colorList[1]);
  m_1->SetMarkerStyle(20); //filled circle
  m_1->SetMarkerColor(colorList[1]);
  m_1->SetDirectory(0);
  
  
  TFile *file2 = TFile::Open("RootOutput/ps25/Run_006301_Output.root");
  HistDQM = (TList *)file2->Get("HistDQM");
  TObject *obj2 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf2 = (TH2 *)obj2;
  TFScaleFactor = 1./tf2->GetEntries();
  tf2->Scale(TFScaleFactor);
  tf2->RebinX(4);
  TH1D *tf_2 = tf2->ProjectionX("HG RAD",30,110);
  tf_2->SetLineColor(colorList[2]);
  tf_2->SetMarkerStyle(20); //filled circle
  tf_2->SetMarkerColor(colorList[2]);
  tf_2->SetDirectory(0);
  
  TObject *objg2 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g2 = (TH2 *)objg2;
  TFScaleFactor = 1./g2->GetEntries();
  g2->Scale(TFScaleFactor);
  g2->RebinX(4);
  TH1D *g_2 = g2->ProjectionX("HG CU RAD",30,190);
  g_2->SetLineColor(colorList[2]);
  g_2->SetMarkerStyle(20); //filled circle
  g_2->SetMarkerColor(colorList[2]);
  g_2->SetDirectory(0);
  
  TObject *objm2 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TH2 *m2 = (TH2 *)objm2;
  TFScaleFactor = 1./m2->GetEntries();
  m2->Scale(TFScaleFactor);
  m2->RebinX(4);
  TH1D *m_2 = m2->ProjectionX("HG CU RAD",10,160);
  m_2->SetLineColor(colorList[2]);
  m_2->SetMarkerStyle(20); //filled circle
  m_2->SetMarkerColor(colorList[2]);
  m_2->SetDirectory(0);
  
  
  TFile *file3 = TFile::Open("RootOutput/ps25/Run_006320_Output.root");
  HistDQM = (TList *)file3->Get("HistDQM");
  TObject *obj3 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf3 = (TH2 *)obj3;
  TFScaleFactor = 1./tf3->GetEntries();
  tf3->Scale(TFScaleFactor);
  tf3->RebinX(4);
  TH1D *tf_3 = tf3->ProjectionX("HG NORAD",30,110);
  tf_3->SetLineColor(colorList[3]);
  tf_3->SetMarkerStyle(20); //filled circle
  tf_3->SetMarkerColor(colorList[3]);
  tf_3->SetDirectory(0);
  
  TObject *objg3 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g3 = (TH2 *)objg3;
  TFScaleFactor = 1./g3->GetEntries();
  g3->Scale(TFScaleFactor);
  g3->RebinX(4);
  TH1D *g_3 = g3->ProjectionX("HG CU NORAD",30,190);
  g_3->SetLineColor(colorList[3]);
  g_3->SetMarkerStyle(20); //filled circle
  g_3->SetMarkerColor(colorList[3]);
  g_3->SetDirectory(0);
  
  TObject *objm3 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TH2 *m3 = (TH2 *)objm3;
  TFScaleFactor = 1./m3->GetEntries();
  m3->Scale(TFScaleFactor);
  m3->RebinX(4);
  TH1D *m_3 = m3->ProjectionX("HG CU NORAD",10,160);
  m_3->SetLineColor(colorList[3]);
  m_3->SetMarkerStyle(20); //filled circle
  m_3->SetMarkerColor(colorList[3]);
  m_3->SetDirectory(0);
  
  
  TFile *file4 = TFile::Open("RootOutput/ps25/Run_006382_Output.root");
  HistDQM = (TList *)file4->Get("HistDQM");
  TObject *obj4 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf4 = (TH2 *)obj4;
  TFScaleFactor = 1./tf4->GetEntries();
  tf4->Scale(TFScaleFactor);
  tf4->RebinX(4);
  TH1D *tf_4 = tf4->ProjectionX("HTF RAD",10,110);
  tf_4->SetLineColor(colorList[4]);
  tf_4->SetMarkerStyle(20); //filled circle
  tf_4->SetMarkerColor(colorList[4]);
  tf_4->SetDirectory(0);
  
  TObject *objg4 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g4 = (TH2 *)objg4;
  TFScaleFactor = 1./g4->GetEntries();
  g4->Scale(TFScaleFactor);
  g4->RebinX(4);
  TH1D *g_4 = g4->ProjectionX("LG AL RAD",10,110);
  g_4->SetLineColor(colorList[4]);
  g_4->SetMarkerStyle(20); //filled circle
  g_4->SetMarkerColor(colorList[4]);
  g_4->SetDirectory(0);

  TObject *objm4 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TH2 *m4 = (TH2 *)objm4;
  TFScaleFactor = 1./m4->GetEntries();
  m4->Scale(TFScaleFactor);
  m4->RebinX(4);
  TH1D *m_4 = m4->ProjectionX("LG AL RAD",10,110);
  m_4->SetLineColor(colorList[4]);
  m_4->SetMarkerStyle(20); //filled circle
  m_4->SetMarkerColor(colorList[4]);
  m_4->SetDirectory(0);
  
  /*
  TFile *file5 = TFile::Open("RootOutput/ps25/Run_006274_Output.root");
  HistDQM = (TList *)file5->Get("HistDQM");
  TObject *obj5 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf5 = (TH2 *)obj5;
  TFScaleFactor = 1./tf5->GetEntries();
  tf5->Scale(TFScaleFactor);
  tf5->RebinX(4);
  TH1D *tf_5 = tf5->ProjectionX("6 - 100CCPM",10,110);
  tf_5->SetLineColor(1);
  tf_5->SetMarkerStyle(20); //filled circle
  tf_5->SetMarkerColor(1);
  tf_5->SetDirectory(0);

  TObject *objg5 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g5 = (TH2 *)objg5;
  TFScaleFactor = 1./g5->GetEntries();
  g5->Scale(TFScaleFactor);
  g5->RebinX(4);
  TH1D *g_5 = g5->ProjectionX("6 - 100CCPM",10,110);
  g_5->SetLineColor(1);
  g_5->SetMarkerStyle(20); //filled circle
  g_5->SetMarkerColor(1);
  g_5->SetDirectory(0);

  TObject *objm5 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TH2 *m5 = (TH2 *)objm5;
  TFScaleFactor = 1./m5->GetEntries();
  m5->Scale(TFScaleFactor);
  m5->RebinX(4);
  TH1D *m_5 = m5->ProjectionX("6 - 100CCPM",10,110);
  m_5->SetLineColor(1);
  m_5->SetMarkerStyle(20); //filled circle
  m_5->SetMarkerColor(1);
  m_5->SetDirectory(0);
  
  
  TFile *file6 = TFile::Open("RootOutput/ps25/Run_006275_Output.root");
  HistDQM = (TList *)file6->Get("HistDQM");
  TObject *obj6 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf6 = (TH2 *)obj6;
  TFScaleFactor = 1./tf6->GetEntries();
  tf6->Scale(TFScaleFactor);
  tf6->RebinX(4);
  TH1D *tf_6 = tf6->ProjectionX("7 - 100CCPM",10,110);
  tf_6->SetLineColor(4);
  tf_6->SetMarkerStyle(20); //filled circle
  tf_6->SetMarkerColor(4);
  tf_6->SetDirectory(0);
  
  TObject *objg6 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g6 = (TH2 *)objg6;
  TFScaleFactor = 1./g6->GetEntries();
  g6->Scale(TFScaleFactor);
  g6->RebinX(4);
  TH1D *g_6 = g6->ProjectionX("7 - 100CCPM",10,110);
  g_6->SetLineColor(4);
  g_6->SetMarkerStyle(20); //filled circle
  g_6->SetMarkerColor(4);
  g_6->SetDirectory(0);

  TObject *objm6 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TH2 *m6 = (TH2 *)objm6;
  TFScaleFactor = 1./m6->GetEntries();
  m6->Scale(TFScaleFactor);
  m6->RebinX(4);
  TH1D *m_6 = m6->ProjectionX("7 - 100CCPM",10,110);
  m_6->SetLineColor(4);
  m_6->SetMarkerStyle(20); //filled circle
  m_6->SetMarkerColor(4);
  m_6->SetDirectory(0);
  
*/
  
	TCanvas *c0 = new TCanvas("c0","uRWell-TRD ADC Response in Time for XeCO2", 1600, 1000);
	gStyle->SetOptStat(0);
	c0->cd();
 	gPad->SetGridy();
	
	TLegend *l0 = new TLegend(0.59,0.7,0.9,0.9);
	l0->AddEntry(tf_0,"'Low Gain' 20cm Fleece Rad","lp");
  l0->AddEntry(tf_1,"'Low Gain' No Rad","lp");
  l0->AddEntry(tf_2,"'High Gain' 20cm Fleece Rad","lp");
	l0->AddEntry(tf_3,"'High Gain' No Rad","lp");
  l0->AddEntry(tf_4,"'High TF' 20cm Fleece Rad","lp");
  //l0->AddEntry(tf_5,"6 - 100CCPM","lp");
  //l0->AddEntry(tf_6,"7 - 100CCPM","lp");
  
	tf_0->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	tf_0->GetYaxis()->SetNdivisions(520);
	tf_0->GetXaxis()->SetRangeUser(20,200);
  tf_0->SetMaximum(tf_2->GetMaximum()+10.);
	tf_0->SetTitle("uRWell-TRD ADC Response in Time for Xe:CO2 90:10");
	tf_0->Draw("");
	tf_1->Draw("same");
  tf_2->Draw("same");
  tf_3->Draw("same");
  tf_4->Draw("same");
  //tf_5->Draw("same");
  //tf_6->Draw("same");
  
	l0->Draw();
	c0->SaveAs("urw_time_Xe_Comparison_v2.png");
  
  
  TCanvas *c1 = new TCanvas("c1","Triple GEM-TRD ADC Response in Time for XeCO2", 1600, 1000);
  gStyle->SetOptStat(0);
  c1->cd();
  gPad->SetGridy();
  
  TLegend *l1 = new TLegend(0.59,0.7,0.9,0.9);
  l1->AddEntry(g_0,"'Low Gain' 5um Cu, 20cm Fleece Rad","lp");
  l1->AddEntry(g_1,"'Low Gain' 5um Cu, No Rad","lp");
  l1->AddEntry(g_2,"'High Gain' 5um Cu, 20cm Fleece Rad","lp");
  l1->AddEntry(g_3,"'High Gain' 5um Cu, No Rad","lp");
  l1->AddEntry(g_4,"'Low Gain' 0.1um Al, 20cm Fleece Rad","lp");
  //l1->AddEntry(g_5,"6 - 100CCPM","lp");
  //l1->AddEntry(g_6,"7 - 100CCPM","lp");

  g_0->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
  g_0->GetYaxis()->SetNdivisions(520);
  g_0->GetXaxis()->SetRangeUser(20,200);
  g_0->SetMaximum(g_2->GetMaximum()+10.);
  g_0->SetTitle("Triple GEM-TRD ADC Response in Time for Xe:CO2 90:10");
  g_0->Draw("");
  g_1->Draw("same");
  g_2->Draw("same");
  g_3->Draw("same");
  g_4->Draw("same");
  //g_5->Draw("same");
  //g_6->Draw("same");

  l1->Draw();
  c1->SaveAs("gem_time_Xe_Comparison_v2.png");
  
  
  TCanvas *c2 = new TCanvas("c2","MMG1-TRD ADC Response in Time for XeCO2", 1600, 1000);
  gStyle->SetOptStat(0);
  c2->cd();
  gPad->SetGridy();
  
  TLegend *l2 = new TLegend(0.59,0.7,0.9,0.9);
  l2->AddEntry(m_0,"'Low Gain' 5um Cu, 20cm Fleece Rad","lp");
  l2->AddEntry(m_1,"'Low Gain' 5um Cu, No Rad","lp");
  l2->AddEntry(m_2,"'High Gain' 5um Cu, 20cm Fleece Rad","lp");
  l2->AddEntry(m_3,"'High Gain' 5um Cu, No Rad","lp");
  l2->AddEntry(m_4,"'Low Gain' 0.1um Al, 20cm Fleece Rad","lp");
  //l2->AddEntry(m_5,"6 - 100CCPM","lp");
  //l2->AddEntry(m_6,"7 - 100CCPM","lp");

  m_0->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
  m_0->GetYaxis()->SetNdivisions(520);
  m_0->GetXaxis()->SetRangeUser(20,200);
  m_0->SetMaximum(m_2->GetMaximum()+10.);
  m_0->SetTitle("MMG1-TRD ADC Response in Time for Xe:CO2 90:10");
  m_0->Draw("");
  m_1->Draw("same");
  m_2->Draw("same");
  m_3->Draw("same");
  m_4->Draw("same");
  //m_5->Draw("same");
  //m_6->Draw("same");

  l2->Draw();
  c2->SaveAs("mmg_time_Xe_Comparison_v2.png");
  	
   
}
