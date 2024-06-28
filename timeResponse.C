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
/*
	TFile *file0 = TFile::Open("Run_003203_Output.root");
	TList *HistDQM = (TList *)file0->Get("HistDQM");
	TObject *obj0 = HistDQM->FindObject("f125_el_amp2ds");
	TH2 *f125_el_amp2ds = (TH2 *)obj0;
	double elScaleFactor = 1./f125_el_amp2ds->GetEntries();
    f125_el_amp2ds->Scale(elScaleFactor);
	f125_el_amp2ds->RebinX(8);
	f125_el_amp2ds->ProjectionX("No Radiator, electrons",40,200);
	TObject *obj1 = HistDQM->FindObject("f125_pi_amp2ds");
	TH2 *f125_pi_amp2ds = (TH2 *)obj1;
	double piScaleFactor = 1./f125_pi_amp2ds->GetEntries();
    f125_pi_amp2ds->Scale(piScaleFactor);
	f125_pi_amp2ds->RebinX(8);
	f125_pi_amp2ds->ProjectionX("No Radiator, pions",40,200);
*/
	TFile *file1 = TFile::Open("Run_003196_Output.root");
	TList *HistDQM = (TList *)file1->Get("HistDQM");
	TObject *obj2 = HistDQM->FindObject("f125_el_amp2ds");
	TH2 *f125_el_amp2ds_r = (TH2 *)obj2;
	double elScaleFactor = 1./f125_el_amp2ds_r->GetEntries();
    f125_el_amp2ds_r->Scale(elScaleFactor);
	f125_el_amp2ds_r->RebinX(8);
	f125_el_amp2ds_r->ProjectionX("24cm Foil Radiator, electrons",40,200);
	TObject *obj3 = HistDQM->FindObject("f125_pi_amp2ds");
	TH2 *f125_pi_amp2ds_r = (TH2 *)obj3;
	double piScaleFactor = 1./f125_pi_amp2ds_r->GetEntries();
    f125_pi_amp2ds_r->Scale(piScaleFactor);
	f125_pi_amp2ds_r->RebinX(8);
	f125_pi_amp2ds_r->ProjectionX("24cm Foil Radiator, pions",40,200);
	
	TCanvas *c1 = new TCanvas("c1","", 1200, 800);
	gStyle->SetOptStat(0);
	c1->cd();
 	gPad->SetGridy();
	
//	TH1F *gem_n_e = (TH1F*)file0->Get("No Radiator, electrons");
//	TH1F *gem_n_pi = (TH1F*)file0->Get("No Radiator, pions");
	TH1F *gem_rad_e = (TH1F*)file1->Get("24cm Foil Radiator, electrons");
	TH1F *gem_rad_pi = (TH1F*)file1->Get("24cm Foil Radiator, pions");
/*
	gem_n_e->SetLineColor(2); //red
	gem_n_e->SetMarkerStyle(24); //open circle
	gem_n_e->SetMarkerColor(2);
	
	gem_n_pi->SetLineColor(4); //blue
	gem_n_pi->SetMarkerStyle(25); //open square
	gem_n_pi->SetMarkerColor(4);
*/
	gem_rad_e->SetLineColor(2); //red
	gem_rad_e->SetMarkerStyle(20); //filled circle
	gem_rad_e->SetMarkerColor(2);
	
	gem_rad_pi->SetLineColor(4); //blue
	gem_rad_pi->SetMarkerStyle(21); //filled square
	gem_rad_pi->SetMarkerColor(4);
	
	TLegend *l1 = new TLegend(0.7,0.7,0.9,0.9);
//	l1->AddEntry(gem_n_e,"Electrons, 10 GeV","lp");
//	l1->AddEntry(gem_n_pi,"Pions, 10 GeV","lp");
	l1->AddEntry(gem_rad_e,"Electrons, 10 GeV","lp");
	l1->AddEntry(gem_rad_pi,"Pions, 10 GeV","lp");
	
	gem_rad_e->GetYaxis()->SetTitle("ADC Amplitude Response (Counts / numEntries)");
	gem_rad_e->GetYaxis()->SetNdivisions(520);
	gem_rad_e->SetTitle("GEM-TRD ADC Response in Time With 24cm Foil Radiator");
//	gem_n_e->Draw("");
	gem_rad_e->Draw("");
//	gem_n_pi->Draw("same");
	gem_rad_pi->Draw("same");
	l1->Draw();
	
	gem_rad_e->SaveAs("gem_drift_doubleFoilRad.png");
}