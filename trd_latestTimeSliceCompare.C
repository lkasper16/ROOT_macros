#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void trd_latestTimeSliceCompare(){
	
	TList *HistDQM;
	double TFScaleFactor = -1.;
	double DFScaleFactor = -1.;
	double IFScaleFactor = -1.;
	
	//=======================================
	//GEM-TRD
	
	TFile *file0 = TFile::Open("v3/RootOutput/Run_006304_Output.root");
	HistDQM = (TList *)file0->Get("HistDQM");
	TObject *obj0 = HistDQM->FindObject("f125_timeVSamp_max");
	TH2 *tf0 = (TH2 *)obj0;
	TH1D *tf_0 = tf0->ProjectionY("GEM Cu",124,146);
	tf_0->RebinX(5);
	TFScaleFactor = 1./tf_0->GetEntries();
  tf_0->Scale(TFScaleFactor);
  tf_0->SetLineColor(94);
  tf_0->SetMarkerStyle(34); //filled cross
  tf_0->SetMarkerColor(94);
  tf_0->SetMarkerSize(2);
  tf_0->SetDirectory(0);
  
  TFile *file1 = TFile::Open("v3/RootOutput/Run_006388_Output.root");
  HistDQM = (TList *)file1->Get("HistDQM");
  TObject *obj1 = HistDQM->FindObject("f125_timeVSamp_max");
  TH2 *tf1 = (TH2 *)obj1;
  TH1D *tf_1 = tf1->ProjectionY("GEM Al",124,146);
  tf_1->RebinX(5);
  TFScaleFactor = 1./tf_1->GetEntries();
  tf_1->Scale(TFScaleFactor);
  tf_1->SetLineColor(4);
  tf_1->SetMarkerStyle(21); //filled square
  tf_1->SetMarkerColor(4);
  tf_1->SetMarkerSize(2);
  tf_1->SetDirectory(0);
  
  TFile *file2 = TFile::Open("v3/RootOutput/Run_006320_Output.root");
  HistDQM = (TList *)file2->Get("HistDQM");
  TObject *obj2 = HistDQM->FindObject("f125_timeVSamp_max");
  TH2 *tf2 = (TH2 *)obj2;
  TH1D *tf_2 = tf2->ProjectionY("GEM No Rad",124,146);
  tf_2->RebinX(5);
  TFScaleFactor = 1./tf_2->GetEntries();
  tf_2->Scale(TFScaleFactor);
  tf_2->SetLineColor(1);
  tf_2->SetMarkerStyle(20); //filled circle
  tf_2->SetMarkerColor(1);
  tf_2->SetMarkerSize(2);
  tf_2->SetDirectory(0);
  
	TCanvas *c0 = new TCanvas("c0","GEM-TRD", 1200, 1000);
	gStyle->SetOptStat(0);
	gStyle->SetTitleFontSize(0.075);
	c0->cd();
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
	TLegend *l0 = new TLegend(0.72,0.6,0.97,0.9);
	l0->AddEntry(tf_0,"5#mum Cu","lp");
  l0->AddEntry(tf_1,"0.1#mum Al","lp");
  //l0->AddEntry(tf_2,"No Rad","lp");
  
	tf_0->GetXaxis()->SetTitle("Max ADC Amplitude in Latest Time Slice");
	tf_0->GetYaxis()->SetTitle("Counts / (No. Track)");
	//tf_0->GetYaxis()->SetNdivisions(520);
	tf_0->GetXaxis()->SetRangeUser(210,4100);
	tf_0->GetXaxis()->SetLabelSize(0.043);
  tf_0->GetXaxis()->SetTitleSize(0.05);
  tf_0->GetYaxis()->SetLabelSize(0.043);
  tf_0->GetYaxis()->SetTitleSize(0.05);
  tf_0->GetYaxis()->SetTitleOffset(1.2);
  //tf_0->GetYaxis()->SetRangeUser(0,0.04);
  tf_0->GetYaxis()->SetRangeUser(0,0.025);
	tf_0->SetTitle("GEM-TRD");
	tf_0->Draw("");
	tf_1->Draw("same");
  //tf_2->Draw("same");
  
  l0->SetHeader("Cathode","C");
	l0->Draw();
	c0->SaveAs("GEMTRD_CathodeSlice_v1.pdf");
	
	//=======================================
	//MMG-TRD
	
	//TFile *file0 = TFile::Open("v3/RootOutput/Run_006382_Output.root");
	HistDQM = (TList *)file0->Get("HistDQM");
	TObject *objd0 = HistDQM->FindObject("mmg1_f125_timeVSamp_max");
	TH2 *df0 = (TH2 *)objd0;
	TH1D *df_0 = df0->ProjectionY("MMG Cu",128,150);
	df_0->RebinX(5);
	DFScaleFactor = 1./df_0->GetEntries();
  df_0->Scale(DFScaleFactor);
  df_0->SetLineColor(94);
  df_0->SetMarkerStyle(34); //filled cross
  df_0->SetMarkerColor(94);
  df_0->SetMarkerSize(2);
  df_0->SetDirectory(0);
	
	HistDQM = (TList *)file1->Get("HistDQM");
  TObject *objd1 = HistDQM->FindObject("mmg1_f125_timeVSamp_max");
  TH2 *df1 = (TH2 *)objd1;
  TH1D *df_1 = df1->ProjectionY("MMG Cu",123,145);
  df_1->RebinX(5);
  DFScaleFactor = 1./df_1->GetEntries();
  df_1->Scale(DFScaleFactor);
  df_1->SetLineColor(4);
  df_1->SetMarkerStyle(21); //filled square
  df_1->SetMarkerColor(4);
  df_1->SetMarkerSize(2);
  df_1->SetDirectory(0);
  
  HistDQM = (TList *)file2->Get("HistDQM");
  TObject *objd2 = HistDQM->FindObject("mmg1_f125_timeVSamp_max");
  TH2 *df2 = (TH2 *)objd2;
  TH1D *df_2 = df2->ProjectionY("MMG No Rad",128,150);
  df_2->RebinX(5);
  DFScaleFactor = 1./df_2->GetEntries();
  df_2->Scale(DFScaleFactor);
  df_2->SetLineColor(1);
  df_2->SetMarkerStyle(20); //filled circle
  df_2->SetMarkerColor(1);
  df_2->SetMarkerSize(2);
  df_2->SetDirectory(0);
  
	
	TCanvas *c1 = new TCanvas("c1","MMG-TRD", 1200, 1000);
  c1->cd();
  gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);

  TLegend *l1 = new TLegend(0.72,0.6,0.97,0.9);
  l1->AddEntry(df_0,"5#mum Cu","lp");
  l1->AddEntry(df_1,"0.1#mum Al","lp");
  //l1->AddEntry(df_2,"No Rad","lp");
  
  df_0->GetXaxis()->SetTitle("Max ADC Amplitude in Latest Time Slice");
	df_0->GetYaxis()->SetTitle("Counts / (No. Track)");
	//df_0->GetYaxis()->SetNdivisions(520);
	df_0->GetXaxis()->SetRangeUser(200,4100);
	df_0->GetXaxis()->SetLabelSize(0.043);
  df_0->GetXaxis()->SetTitleSize(0.05);
  df_0->GetYaxis()->SetLabelSize(0.043);
  df_0->GetYaxis()->SetTitleSize(0.05);
  df_0->GetYaxis()->SetTitleOffset(1.2);
  //df_0->GetYaxis()->SetRangeUser(0,0.04);
  df_0->GetYaxis()->SetRangeUser(0,0.03);
	df_0->SetTitle("Hybrid Micromegas-TRD");
  df_0->Draw("");
  df_1->Draw("same");
  //df_2->Draw("same");
  
  l1->SetHeader("Cathode","C");
  l1->Draw();
  c1->SaveAs("MMGTRD_CathodeSlice_v1.pdf");
	
	
	//=======================================
  //uRWELL-TRD
  
  TFile *filei0 = TFile::Open("v3/RootOutput/Run_006391_Output.root");
  HistDQM = (TList *)filei0->Get("HistDQM");
  TObject *obji0 = HistDQM->FindObject("urw_f125_x_timeVSamp_max");
  TH2 *if0 = (TH2 *)obji0;
  TH1D *if_0 = if0->ProjectionY("No Rad",125,140);
  if_0->RebinX(5);
  IFScaleFactor = 1./if_0->GetEntries();
  if_0->Scale(IFScaleFactor);
  if_0->SetLineColor(1);
  if_0->SetMarkerStyle(20); //filled circle
  if_0->SetMarkerColor(1);
  if_0->SetMarkerSize(2);
  if_0->SetDirectory(0);

  TFile *filei1 = TFile::Open("v3/RootOutput/Run_006304_Output.root");
  HistDQM = (TList *)filei1->Get("HistDQM");
  TObject *obji1 = HistDQM->FindObject("urw_f125_x_timeVSamp_max");
  TH2 *if1 = (TH2 *)obji1;
  TH1D *if_1 = if1->ProjectionY("With Rad",125,140);
  if_1->RebinX(5);
  IFScaleFactor = 1./if_1->GetEntries();
  if_1->Scale(IFScaleFactor);
  if_1->SetLineColor(4);
  if_1->SetMarkerStyle(21); //filled square
  if_1->SetMarkerColor(4);
  if_1->SetMarkerSize(2);
  if_1->SetDirectory(0);
  
  TCanvas *c2 = new TCanvas("c2","#muRWell-TRD", 1200, 1000);
  c2->cd();
  gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
	TLegend *l2 = new TLegend(0.72,0.6,0.97,0.9);
  l2->AddEntry(if_0,"No Rad","lp");
  l2->AddEntry(if_1,"With Rad","lp");

  if_0->GetXaxis()->SetTitle("Max ADC Amplitude in Latest Time Slice");
	if_0->GetYaxis()->SetTitle("Counts / (No. Track)");
	//if_0->GetYaxis()->SetNdivisions(520);
	if_0->GetXaxis()->SetRangeUser(0,2800);
	if_0->GetXaxis()->SetLabelSize(0.043);
  if_0->GetXaxis()->SetTitleSize(0.05);
  if_0->GetYaxis()->SetTitleSize(0.05);
  if_0->GetYaxis()->SetTitleOffset(1.1);
  if_0->GetYaxis()->SetLabelSize(0.043);
  if_0->GetYaxis()->SetRangeUser(0,0.22);
  if_0->SetTitle("#muRWell-TRD");
  if_0->Draw("");
  if_1->Draw("same");

  //l2->SetHeader("...","C");
  l2->Draw();
  c2->SaveAs("URWTRD_CathodeSlice_v1.pdf");
	
	
}
