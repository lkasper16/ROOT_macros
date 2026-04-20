#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void timeResponse_halld_recon() {
	
	double elScaleFactor = -1.;
	double piScaleFactor = -1.;
	double elScaleFactor_ar = -1.;
	
	TCanvas *c0 = new TCanvas("c0","", 1200, 800);
	gStyle->SetOptStat(0);
	c0->cd();
 	gPad->SetGridy();
 	TLegend *l1 = new TLegend(0.7,0.7,0.9,0.9);
 	
	//=======================================
	//Large GEMTRD, electron samples with Kr
	TFile *file0 = TFile::Open("hd_root_TRD_online_outputText_dalitzKrypton_v2.root");
	TObject *obj0 = file0->Get("TRD/Point/Point_Time");
      TH1 *point_time_dk = (TH1*)obj0;
      elScaleFactor = 1./point_time_dk->GetEntries();
      point_time_dk->Scale(elScaleFactor);
      point_time_dk->RebinX(8);
      point_time_dk->SetLineColor(3);
      point_time_dk->SetMarkerColor(3);
      point_time_dk->SetLineWidth(2);
      point_time_dk->SetDirectory(0);
      l1->AddEntry(point_time_dk, "e^{+ / -} in Kr:CO_{2}", "lp");
	
	//Large GEMTRD, electron samples with Ar
	TFile *file1 = TFile::Open("hd_root_TRD_online_outputText_dalitzArgon.root");
	TObject *obj1 = file1->Get("TRD/Point/Point_Time");
      TH1 *point_time_da = (TH1*)obj1;
      elScaleFactor_ar = 1./point_time_da->GetEntries();
      point_time_da->Scale(elScaleFactor_ar);
      point_time_da->RebinX(8);
      point_time_da->SetLineColor(2);
      point_time_da->SetMarkerColor(2);
      point_time_da->SetLineWidth(2);
      point_time_da->SetDirectory(0);
      l1->AddEntry(point_time_da, "e^{+ / -} in Ar:CO_{2}", "lp");
	
	//Large GEMTRD, all particles with Kr
	TFile *file2 = TFile::Open("hd_root_maxHistos_800K.root");
	TObject *obj2 = file2->Get("TRD/Point/Point_Time");
      TH1 *point_time_pk = (TH1*)obj2;
      piScaleFactor = 1./point_time_pk->GetEntries();
      point_time_pk->Scale(piScaleFactor);
      point_time_pk->RebinX(8);
      point_time_pk->SetLineColor(4);
      point_time_pk->SetMarkerColor(4);
      point_time_pk->SetLineWidth(2);
      point_time_pk->SetDirectory(0);
      l1->AddEntry(point_time_pk, "#pi^{+ / -} in Kr:CO_{2}", "lp");
	
	
	point_time_dk->GetYaxis()->SetTitle("ADC Amplitude (Counts / Events)");
	point_time_dk->GetYaxis()->SetNdivisions(520);
	point_time_dk->GetXaxis()->SetTitle("Drift Time [ns]");
	point_time_dk->GetXaxis()->SetRangeUser(200,1050);
	point_time_dk->SetTitle("GEM-TRD Prototype ADC Response vs Drift Time");
	point_time_dk->Draw("");
	point_time_da->Draw("same");
	point_time_pk->Draw("same");
	l1->Draw();
	//c0->SaveAs("largeGem_driftTimes_inAcceptance.pdf");
	
	//=======================================
}