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
  tf_1->SetMarkerStyle(33); //filled square
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
	gStyle->SetTitleFontSize(0.065);
	c0->cd();
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
	TLegend *l0 = new TLegend(0.675,0.51,0.97,0.9);
	l0->AddEntry(tf_2,"#splitline{'Pion-like'}{Electrons}","lp");
	l0->AddEntry(tf_0,"#splitline{Electrons}{(5#mum Cu)}","lp");
  l0->AddEntry(tf_1,"#splitline{Electrons}{(0.1#mum Al)}","lp");
  
	tf_0->GetXaxis()->SetTitle("Max ADC Amplitude in Latest Time Slice [ADC units]");
	tf_0->GetYaxis()->SetTitle("Counts / (No. Track)");
	//tf_0->GetYaxis()->SetNdivisions(520);
	tf_0->GetXaxis()->SetRangeUser(210,4100);
	tf_0->GetXaxis()->SetLabelSize(0.043);
  tf_0->GetXaxis()->SetTitleSize(0.048);
  tf_0->GetYaxis()->SetLabelSize(0.043);
  tf_0->GetYaxis()->SetTitleSize(0.05);
  tf_0->GetYaxis()->SetTitleOffset(1.2);
  tf_0->GetYaxis()->SetRangeUser(0,0.04);
  //tf_0->GetYaxis()->SetRangeUser(0,0.025);
	tf_0->SetTitle("GEM-TRD (JLab '25)");
	tf_0->Draw("");
	tf_1->Draw("same");
  tf_2->Draw("same");
  
  //l0->SetHeader("Cathode","C");
  l0->SetTextSize(0.053);
	l0->Draw();
	c0->SaveAs("GEMTRD_CathodeSlice_v3.pdf");
	
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
  df_1->SetMarkerStyle(33); //filled square
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

  TLegend *l1 = new TLegend(0.675,0.51,0.97,0.9);
  l1->AddEntry(df_2,"#splitline{'Pion-like'}{Electrons}","lp");
  l1->AddEntry(df_0,"#splitline{Electrons}{(5#mum Cu)}","lp");
  l1->AddEntry(df_1,"#splitline{Electrons}{(0.1#mum Al)}","lp");
  
  df_0->GetXaxis()->SetTitle("Max ADC Amplitude in Latest Time Slice [ADC units]");
	df_0->GetYaxis()->SetTitle("Counts / (No. Track)");
	//df_0->GetYaxis()->SetNdivisions(520);
	df_0->GetXaxis()->SetRangeUser(200,4100);
	df_0->GetXaxis()->SetLabelSize(0.043);
  df_0->GetXaxis()->SetTitleSize(0.048);
  df_0->GetYaxis()->SetLabelSize(0.043);
  df_0->GetYaxis()->SetTitleSize(0.05);
  df_0->GetYaxis()->SetTitleOffset(1.2);
  df_0->GetYaxis()->SetRangeUser(0,0.04);
  //df_0->GetYaxis()->SetRangeUser(0,0.03);
	df_0->SetTitle("Hybrid Micromegas-TRD (JLab '25)");
  df_0->Draw("");
  df_1->Draw("same");
  df_2->Draw("same");
  
  //l1->SetHeader("Cathode","C");
  l1->SetTextSize(0.053);
  l1->Draw();
  c1->SaveAs("MMGTRD_CathodeSlice_v3.pdf");
	
	
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

  if_0->GetXaxis()->SetTitle("Max ADC Amplitude in Latest Time Slice [ADC units]");
	if_0->GetYaxis()->SetTitle("Counts / (No. Track)");
	//if_0->GetYaxis()->SetNdivisions(520);
	if_0->GetXaxis()->SetRangeUser(0,2800);
	if_0->GetXaxis()->SetLabelSize(0.043);
  if_0->GetXaxis()->SetTitleSize(0.048);
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
  
  
  //====================================================
  //					CERN 2024
  //====================================================
  
  TFile *filec0 = TFile::Open("../cern24DataAnalysis/2025Revisit/v2/RootOutput/Run_005284_3615629Entries_Output.root");
  HistDQM = (TList *)filec0->Get("HistDQM");
  TObject *objc0 = HistDQM->FindObject("f125_pi_max_late");
  TH2 *cf_0 = (TH2 *)objc0;
  //cf_0->RebinX(2);
  IFScaleFactor = 1./cf_0->GetEntries();
  cf_0->Scale(IFScaleFactor);
  cf_0->SetLineColor(1);
  cf_0->SetMarkerStyle(20); //filled circle
  cf_0->SetMarkerColor(1);
  cf_0->SetMarkerSize(2);
  cf_0->SetDirectory(0);
  
  TObject *objc1 = HistDQM->FindObject("f125_el_max_late");
  TH2 *cf_1 = (TH2 *)objc1;
  //cf_1->RebinX(2);
  IFScaleFactor = 1./cf_1->GetEntries();
  cf_1->Scale(IFScaleFactor);
  cf_1->SetLineColor(94);
  cf_1->SetMarkerStyle(34); //filled cross
  cf_1->SetMarkerColor(94);
  cf_1->SetMarkerSize(2);
  cf_1->SetDirectory(0);
  
  
  TCanvas *c3 = new TCanvas("c3","GEM-TRD CERN", 1200, 1000);
	gStyle->SetOptStat(0);
	gStyle->SetTitleFontSize(0.065);
	c3->cd();
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
	TLegend *l3 = new TLegend(0.675,0.6,0.97,0.9);
	l3->AddEntry(cf_0,"Pions","lp");
  l3->AddEntry(cf_1,"#splitline{Electrons}{(5#mum Cu)}","lp");
  
	cf_0->GetXaxis()->SetTitle("Max ADC Amplitude in Latest Time Slice [ADC units]");
	cf_0->GetYaxis()->SetTitle("Counts / (No. Track)");
	//cf_0->GetYaxis()->SetNdivisions(520);
	cf_0->GetXaxis()->SetRangeUser(210,4100);
	cf_0->GetXaxis()->SetLabelSize(0.043);
  cf_0->GetXaxis()->SetTitleSize(0.048);
  cf_0->GetYaxis()->SetLabelSize(0.043);
  cf_0->GetYaxis()->SetTitleSize(0.05);
  cf_0->GetYaxis()->SetTitleOffset(1.2);
  //cf_0->GetYaxis()->SetRangeUser(0,0.04);
  //cf_0->GetYaxis()->SetRangeUser(0,0.025);
	cf_0->SetTitle("GEM-TRD (CERN '24)");
	cf_0->Draw("");
	cf_1->Draw("same");
  
  //l3->SetHeader("Cathode","C");
  l3->SetTextSize(0.055);
	l3->Draw();
	c3->SaveAs("GEMTRD_CathodeSlice_Cern_v1.pdf");
  
  //==================================================================
  
  TObject *objcm0 = HistDQM->FindObject("mmg1_f125_pi_max_late");
  TH2 *cm_0 = (TH2 *)objcm0;
  //cm_0->RebinX(2);
  IFScaleFactor = 1./cm_0->GetEntries();
  cm_0->Scale(IFScaleFactor);
  cm_0->SetLineColor(1);
  cm_0->SetMarkerStyle(20); //filled circle
  cm_0->SetMarkerColor(1);
  cm_0->SetMarkerSize(2);
  cm_0->SetDirectory(0);
  
  TObject *objcm1 = HistDQM->FindObject("mmg1_f125_el_max_late");
  TH2 *cm_1 = (TH2 *)objcm1;
  //cm_1->RebinX(2);
  IFScaleFactor = 1./cm_1->GetEntries();
  cm_1->Scale(IFScaleFactor);
  cm_1->SetLineColor(94);
  cm_1->SetMarkerStyle(34); //filled cross
  cm_1->SetMarkerColor(94);
  cm_1->SetMarkerSize(2);
  cm_1->SetDirectory(0);
  
  
  TCanvas *c4 = new TCanvas("c4","MMG-TRD CERN", 1200, 1000);
	gStyle->SetOptStat(0);
	gStyle->SetTitleFontSize(0.065);
	c4->cd();
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
	TLegend *l4 = new TLegend(0.675,0.6,0.97,0.9);
	l4->AddEntry(cm_0,"Pions","lp");
  l4->AddEntry(cm_1,"#splitline{Electrons}{(5#mum Cu)}","lp");
  
	cm_0->GetXaxis()->SetTitle("Max ADC Amplitude in Latest Time Slice [ADC units]");
	cm_0->GetYaxis()->SetTitle("Counts / (No. Track)");
	//cm_0->GetYaxis()->SetNdivisions(520);
	cm_0->GetXaxis()->SetRangeUser(210,4100);
	cm_0->GetXaxis()->SetLabelSize(0.043);
  cm_0->GetXaxis()->SetTitleSize(0.048);
  cm_0->GetYaxis()->SetLabelSize(0.043);
  cm_0->GetYaxis()->SetTitleSize(0.05);
  cm_0->GetYaxis()->SetTitleOffset(1.2);
  //cm_0->GetYaxis()->SetRangeUser(0,0.04);
  //cm_0->GetYaxis()->SetRangeUser(0,0.025);
	cm_0->SetTitle("Hybrid Micromegas-TRD (CERN '24)");
	cm_0->Draw("");
	cm_1->Draw("same");
  
  //l4->SetHeader("Cathode","C");
  l4->SetTextSize(0.055);
	l4->Draw();
	c4->SaveAs("MMGTRD_CathodeSlice_Cern_v1.pdf");
  
  
  //=================================================================
  //			Combined plots
  //=================================================================
  
  //======================================================
	// GEM-TRD
	
  TCanvas *c5 = new TCanvas("c5","GEM-TRD", 1200, 1000);
	gStyle->SetOptStat(0);
	gStyle->SetTitleFontSize(0.065);
	c5->cd();
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
	TLegend *l5 = new TLegend(0.43,0.59,0.97,0.9);
	
	cf_0->SetMarkerStyle(4); //open circle
	cf_1->SetMarkerStyle(28); //open cross
	
	l5->AddEntry(cf_0,"20#scale[0.85]{GeV} pions","lp");
	l5->AddEntry(cf_1,"#splitline{20#scale[0.85]{GeV} electrons}{(5#scale[0.85]{#mum} Cu)}","lp");
  l5->AddEntry(tf_2,"#splitline{3-6#scale[0.85]{GeV} ''pion-}{like'' electrons}","lp");
  l5->AddEntry(tf_0,"#splitline{3-6#scale[0.85]{GeV} electrons}{(5#scale[0.85]{#mum} Cu)}","lp");
 	l5->AddEntry("","","");
  l5->AddEntry(tf_1,"#splitline{3-6#scale[0.85]{GeV} electrons}{(0.1#scale[0.85]{#mum} Al)}","lp");
	l5->SetNColumns(2);
	
	cf_0->SetTitle("Triple-GEM-TRD");
	cf_0->Draw("");
	tf_2->Draw("same");
	cf_1->Draw("same");
	tf_0->Draw("same");
	tf_1->Draw("same");
	
	l5->SetTextSize(0.041);
	l5->Draw();
	
	c5->SaveAs("GEMTRD_CathodeSlice_Combined_v3.pdf");
	
	//======================================================
	// MMG-TRD
	
	TCanvas *c6 = new TCanvas("c6","MMG-TRD", 1200, 1000);
	gStyle->SetOptStat(0);
	gStyle->SetTitleFontSize(0.065);
	c6->cd();
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
	TLegend *l6 = new TLegend(0.43,0.59,0.97,0.9);
	
	cm_0->SetMarkerStyle(4); //open circle
	cm_1->SetMarkerStyle(28); //open cross
	
	l6->AddEntry(cm_0,"20#scale[0.85]{GeV} pions","lp");
  l6->AddEntry(cm_1,"#splitline{20#scale[0.85]{GeV} electrons}{(5#scale[0.85]{#mum} Cu)}","lp");
  l6->AddEntry(df_2,"#splitline{3-6#scale[0.85]{GeV} ''pion-}{like'' electrons}","lp");
  l6->AddEntry(df_0,"#splitline{3-6#scale[0.85]{GeV} electrons}{(5#scale[0.85]{#mum} Cu)}","lp");
  l6->AddEntry("","","");
  l6->AddEntry(df_1,"#splitline{3-6#scale[0.85]{GeV} electrons}{(0.1#scale[0.85]{#mum} Al)}","lp");
	l6->SetNColumns(2);
	
	cm_0->SetTitle("Hybrid Micromegas-TRD");
	cm_0->Draw("");
	df_2->Draw("same");
	cm_1->Draw("same");
	df_0->Draw("same");
	df_1->Draw("same");
	
	l6->SetTextSize(0.041);
	l6->Draw();
	
	c6->SaveAs("MMGTRD_CathodeSlice_Combined_v3.pdf");
	
	
	
}
