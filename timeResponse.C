#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void timeResponse() {
	
	TList *HistDQM;
	double TFScaleFactor = -1.;
	double DFScaleFactor = -1.;
	double dVScaleFactor = -1.;
  double IFScaleFactor = -1.;
	
	//=======================================
	//uRWell-TRD Varied TF
	
	TFile *file0 = TFile::Open("Run_006247_Output.root");
	HistDQM = (TList *)file0->Get("HistDQM");
	TObject *obj0 = HistDQM->FindObject("urw_f125_x_amp2ds");
	TH2 *tf0 = (TH2 *)obj0;
	TFScaleFactor = 1./tf0->GetEntries();
  tf0->Scale(TFScaleFactor);
	tf0->RebinX(4);
	TH1D *tf_0 = tf0->ProjectionX("TF=1.925 kV/cm",10,110);
  tf_0->SetLineColor(94);
  tf_0->SetMarkerStyle(20); //filled circle
  tf_0->SetMarkerColor(94);
  tf_0->SetDirectory(0);
  
  TFile *file1 = TFile::Open("Run_006245_Output.root");
  HistDQM = (TList *)file1->Get("HistDQM");
  TObject *obj1 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf1 = (TH2 *)obj1;
  TFScaleFactor = 1./tf1->GetEntries();
  tf1->Scale(TFScaleFactor);
  tf1->RebinX(4);
  TH1D *tf_1 = tf1->ProjectionX("TF=1.95 kV/cm",10,110);
  tf_1->SetLineColor(2);
  tf_1->SetMarkerStyle(20); //filled circle
  tf_1->SetMarkerColor(2);
  tf_1->SetDirectory(0);
  
  TFile *file2 = TFile::Open("Run_006244_Output.root");
  HistDQM = (TList *)file2->Get("HistDQM");
  TObject *obj2 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf2 = (TH2 *)obj2;
  TFScaleFactor = 1./tf2->GetEntries();
  tf2->Scale(TFScaleFactor);
  tf2->RebinX(4);
  TH1D *tf_2 = tf2->ProjectionX("TF=1.975 kV/cm",10,110);
  tf_2->SetLineColor(209); 
  tf_2->SetMarkerStyle(20); //filled circle
  tf_2->SetMarkerColor(209);
  tf_2->SetDirectory(0);
  
  TFile *file3 = TFile::Open("Run_006261_Output.root");
  HistDQM = (TList *)file3->Get("HistDQM");
  TObject *obj3 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf3 = (TH2 *)obj3;
  TFScaleFactor = 1./tf3->GetEntries();
  tf3->Scale(TFScaleFactor);
  tf3->RebinX(4);
  TH1D *tf_3 = tf3->ProjectionX("TF=2 kV/cm",10,110);
  tf_3->SetLineColor(6); 
  tf_3->SetMarkerStyle(20); //filled circle
  tf_3->SetMarkerColor(6);
  tf_3->SetDirectory(0);
  
  TFile *file4 = TFile::Open("Run_006246_Output.root");
  HistDQM = (TList *)file4->Get("HistDQM");
  TObject *obj4 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *tf4 = (TH2 *)obj4;
  TFScaleFactor = 1./tf4->GetEntries();
  tf4->Scale(TFScaleFactor);
  tf4->RebinX(4);
  TH1D *tf_4 = tf4->ProjectionX("TF=2.025 kV/cm",10,110);
  tf_4->SetLineColor(7);
  tf_4->SetMarkerStyle(20); //filled circle
  tf_4->SetMarkerColor(7);
  tf_4->SetDirectory(0);
  
	TCanvas *c0 = new TCanvas("c0","uRWell-TRD ADC Response in Time for Varied TF", 1200, 800);
	gStyle->SetOptStat(0);
	c0->cd();
 	gPad->SetGridy();
	
	TLegend *l0 = new TLegend(0.75,0.6,0.9,0.9);
	l0->AddEntry(tf_0,"1.925 kV/cm","lp");
  l0->AddEntry(tf_1,"1.95 kV/cm","lp");
  l0->AddEntry(tf_2,"1.975 kV/cm","lp");
	l0->AddEntry(tf_3,"2 kV/cm","lp");
  l0->AddEntry(tf_4,"2.025 kV/cm","lp");
  
	tf_0->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	tf_0->GetYaxis()->SetNdivisions(520);
	tf_0->GetXaxis()->SetRangeUser(30,130);
	tf_0->SetTitle("uRWell-TRD ADC Response in Time, 1.385kV/cm DF, 385 GEM dV, 490V rWELL");
	tf_0->Draw("");
	tf_1->Draw("same");
  tf_2->Draw("same");
  tf_3->Draw("same");
  tf_4->Draw("same");
  
  l0->SetHeader("Transfer Field","C");
	l0->Draw();
	c0->SaveAs("urw_time_TF_Comparison_v1.png");
	
	//=======================================
	//Varied DF
	
  TFile *filed0 = TFile::Open("Run_006214_Output.root");
  HistDQM = (TList *)filed0->Get("HistDQM");
  TObject *objd0 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *df0 = (TH2 *)objd0;
  DFScaleFactor = 1./df0->GetEntries();
  df0->Scale(DFScaleFactor);
  df0->RebinX(4);
  TH1D *df_0 = df0->ProjectionX("DF=1.365 kV/cm",10,110);
  df_0->SetLineColor(94);
  df_0->SetMarkerStyle(20); //filled circle
  df_0->SetMarkerColor(94);
  df_0->SetDirectory(0);

  TFile *filed1 = TFile::Open("Run_006212_Output.root");
  HistDQM = (TList *)filed1->Get("HistDQM");
  TObject *objd1 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *df1 = (TH2 *)objd1;
  DFScaleFactor = 1./df1->GetEntries();
  df1->Scale(DFScaleFactor);
  df1->RebinX(4);
  TH1D *df_1 = df1->ProjectionX("DF=1.372 kV/cm",10,110);
  df_1->SetLineColor(2);
  df_1->SetMarkerStyle(20); //filled circle
  df_1->SetMarkerColor(2);
  df_1->SetDirectory(0);

  TFile *filed2 = TFile::Open("Run_006211_Output.root");
  HistDQM = (TList *)filed2->Get("HistDQM");
  TObject *objd2 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *df2 = (TH2 *)objd2;
  DFScaleFactor = 1./df2->GetEntries();
  df2->Scale(DFScaleFactor);
  df2->RebinX(4);
  TH1D *df_2 = df2->ProjectionX("DF=1.378 kV/cm",10,110);
  df_2->SetLineColor(209);
  df_2->SetMarkerStyle(20); //filled circle
  df_2->SetMarkerColor(209);
  df_2->SetDirectory(0);

  TFile *filed3 = TFile::Open("Run_006261_Output.root");
  HistDQM = (TList *)filed3->Get("HistDQM");
  TObject *objd3 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *df3 = (TH2 *)objd3;
  DFScaleFactor = 1./df3->GetEntries();
  df3->Scale(DFScaleFactor);
  df3->RebinX(4);
  TH1D *df_3 = df3->ProjectionX("DF=1.385 kV/cm",10,110);
  df_3->SetLineColor(6);
  df_3->SetMarkerStyle(20); //filled circle
  df_3->SetMarkerColor(6);
  df_3->SetDirectory(0);

  TFile *filed4 = TFile::Open("Run_006213_Output.root");
  HistDQM = (TList *)filed4->Get("HistDQM");
  TObject *objd4 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *df4 = (TH2 *)objd4;
  DFScaleFactor = 1./df4->GetEntries();
  df4->Scale(DFScaleFactor);
  df4->RebinX(4);
  TH1D *df_4 = df4->ProjectionX("DF=1.391 kV/cm",10,110);
  df_4->SetLineColor(7);
  df_4->SetMarkerStyle(20); //filled circle
  df_4->SetMarkerColor(7);
  df_4->SetDirectory(0);
  
  TFile *filed5 = TFile::Open("Run_006215_Output.root");
  HistDQM = (TList *)filed5->Get("HistDQM");
  TObject *objd5 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *df5 = (TH2 *)objd5;
  DFScaleFactor = 1./df5->GetEntries();
  df5->Scale(DFScaleFactor);
  df5->RebinX(4);
  TH1D *df_5 = df5->ProjectionX("DF=1.398 kV/cm",10,110);
  df_5->SetLineColor(1);
  df_5->SetMarkerStyle(20); //filled circle
  df_5->SetMarkerColor(1);
  df_5->SetDirectory(0);
  
  TFile *filed6 = TFile::Open("Run_006216_Output.root");
  HistDQM = (TList *)filed6->Get("HistDQM");
  TObject *objd6 = HistDQM->FindObject("urw_f125_x_amp2ds");
  TH2 *df6 = (TH2 *)objd6;
  DFScaleFactor = 1./df6->GetEntries();
  df6->Scale(DFScaleFactor);
  df6->RebinX(4);
  TH1D *df_6 = df6->ProjectionX("DF=1.404 kV/cm",10,110);
  df_6->SetLineColor(4);
  df_6->SetMarkerStyle(20); //filled circle
  df_6->SetMarkerColor(4);
  df_6->SetDirectory(0);
  
  TCanvas *c1 = new TCanvas("c1","uRWell-TRD ADC Response in Time for Varied DF", 1200, 800);
  c1->cd();
  gPad->SetGridy();

  TLegend *l1 = new TLegend(0.75,0.6,0.9,0.9);
  l1->AddEntry(df_0,"1.365 kV/cm","lp");
  l1->AddEntry(df_1,"1.372 kV/cm","lp");
  l1->AddEntry(df_2,"1.378 kV/cm","lp");
  l1->AddEntry(df_3,"1.385 kV/cm","lp");
  l1->AddEntry(df_4,"1.391 kV/cm","lp");
  l1->AddEntry(df_5,"1.398 kV/cm","lp");
  l1->AddEntry(df_6,"1.404 kV/cm","lp");
  
  df_0->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
  df_0->GetYaxis()->SetNdivisions(520);
  df_0->GetXaxis()->SetRangeUser(30,130);
  df_0->SetTitle("uRWell-TRD ADC Response in Time, 2kV/cm TF, 385 GEM dV, 490V rWELL");
  df_0->Draw("");
  df_1->Draw("same");
  df_2->Draw("same");
  df_3->Draw("same");
  df_4->Draw("same");
  df_5->Draw("same");
  df_6->Draw("same");

  l1->SetHeader("Drift Field","C");
  l1->Draw();
  c1->SaveAs("urw_time_DF_Comparison_v1.png");

  //=======================================
  //







}
