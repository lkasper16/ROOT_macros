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
	double elScaleFactor = -1.;
	double piScaleFactor = -1.;
	double elScaleFactor_mmg1 = -1.;
	double piScaleFactor_mmg1 = -1.;
	double elScaleFactor_urw = -1.;
	double piScaleFactor_urw = -1.;
	
	TFile *file0 = TFile::Open("Run_003203_Output.root");
	HistDQM = (TList *)file0->Get("HistDQM");
	TObject *obj0 = HistDQM->FindObject("f125_el_amp2ds");
	TH2 *f125_el_amp2ds = (TH2 *)obj0;
	elScaleFactor = 1./f125_el_amp2ds->GetEntries();
    f125_el_amp2ds->Scale(elScaleFactor);
	f125_el_amp2ds->RebinX(8);
	f125_el_amp2ds->ProjectionX("No Radiator, electrons",80,170);
	TObject *obj1 = HistDQM->FindObject("f125_pi_amp2ds");
	TH2 *f125_pi_amp2ds = (TH2 *)obj1;
	piScaleFactor = 1./f125_pi_amp2ds->GetEntries();
    f125_pi_amp2ds->Scale(piScaleFactor);
	f125_pi_amp2ds->RebinX(8);
	f125_pi_amp2ds->ProjectionX("No Radiator, pions",80,170);
	
	TCanvas *c0 = new TCanvas("c0","", 1200, 800);
	gStyle->SetOptStat(0);
	c0->cd();
 	gPad->SetGridy();
	
	TH1F *gem_n_e = (TH1F*)file0->Get("No Radiator, electrons");
	TH1F *gem_n_pi = (TH1F*)file0->Get("No Radiator, pions");
	gem_n_e->SetLineColor(2); //red
	//gem_n_e->SetMarkerStyle(24); //open circle
	gem_n_e->SetMarkerStyle(20); //filled circle
	gem_n_e->SetMarkerColor(2);
	gem_n_pi->SetLineColor(4); //blue
	//gem_n_pi->SetMarkerStyle(25); //open square
	gem_n_pi->SetMarkerStyle(21); //filled square
	gem_n_pi->SetMarkerColor(4);
	
	TLegend *l0 = new TLegend(0.7,0.7,0.9,0.9);
	l0->AddEntry(gem_n_e,"Electrons, 10 GeV","lp");
	l0->AddEntry(gem_n_pi,"Pions, 10 GeV","lp");
	
	gem_n_e->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	gem_n_e->GetYaxis()->SetNdivisions(520);
	gem_n_e->GetXaxis()->SetRangeUser(70,220);
	gem_n_e->SetTitle("GEM-TRD ADC Response in Time With No Radiator");
	gem_n_e->Draw("");
	gem_n_pi->Draw("same");
	l0->Draw();
	gem_n_e->SaveAs("gem_drift_noRad.png");
	
	//=======================================
	
	TFile *file1 = TFile::Open("Run_003196_Output.root");
	HistDQM = (TList *)file1->Get("HistDQM");
	TObject *obj2 = HistDQM->FindObject("f125_el_amp2ds");
	TH2 *f125_el_amp2ds_r = (TH2 *)obj2;
	elScaleFactor = 1./f125_el_amp2ds_r->GetEntries();
    f125_el_amp2ds_r->Scale(elScaleFactor);
	f125_el_amp2ds_r->RebinX(8);
	f125_el_amp2ds_r->ProjectionX("24cm Foil Radiator, electrons",80,170);
	TObject *obj3 = HistDQM->FindObject("f125_pi_amp2ds");
	TH2 *f125_pi_amp2ds_r = (TH2 *)obj3;
	piScaleFactor = 1./f125_pi_amp2ds_r->GetEntries();
    f125_pi_amp2ds_r->Scale(piScaleFactor);
	f125_pi_amp2ds_r->RebinX(8);
	f125_pi_amp2ds_r->ProjectionX("24cm Foil Radiator, pions",80,170);
	
	TCanvas *c1 = new TCanvas("c1","", 1200, 800);
	c1->cd();
 	gPad->SetGridy();
	
	TH1F *gem_rad_e = (TH1F*)file1->Get("24cm Foil Radiator, electrons");
	TH1F *gem_rad_pi = (TH1F*)file1->Get("24cm Foil Radiator, pions");
	gem_rad_e->SetLineColor(2); //red
	gem_rad_e->SetMarkerStyle(20); //filled circle
	gem_rad_e->SetMarkerColor(2);
	gem_rad_pi->SetLineColor(4); //blue
	gem_rad_pi->SetMarkerStyle(21); //filled square
	gem_rad_pi->SetMarkerColor(4);
	
	TLegend *l1 = new TLegend(0.7,0.7,0.9,0.9);
	l1->AddEntry(gem_rad_e,"Electrons, 10 GeV","lp");
	l1->AddEntry(gem_rad_pi,"Pions, 10 GeV","lp");
	
	gem_rad_e->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	gem_rad_e->GetYaxis()->SetNdivisions(520);
	gem_rad_e->GetXaxis()->SetRangeUser(70,220);
	gem_rad_e->SetTitle("GEM-TRD ADC Response in Time With 24cm Foil Radiator");
	gem_rad_e->Draw("");
	gem_rad_pi->Draw("same");
	l1->Draw();
	gem_rad_e->SaveAs("gem_drift_doubleFoilRad.png");
	
	//=======================================
	
	TFile *file2 = TFile::Open("Run_003203_Output.root");
	HistDQM = (TList *)file2->Get("HistDQM");
	TObject *obj4 = HistDQM->FindObject("f125_el_amp2ds");
	TH2 *f125_el_amp2ds_n = (TH2 *)obj4;
	elScaleFactor = 1./f125_el_amp2ds_n->GetEntries();
    f125_el_amp2ds_n->Scale(elScaleFactor);
	f125_el_amp2ds_n->RebinX(8);
	f125_el_amp2ds_n->ProjectionX("GEM No Radiator, electrons",80,170);
	TObject *obj5 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
	TH2 *mmg1_f125_el_amp2ds = (TH2 *)obj5;
	elScaleFactor_mmg1 = 1./mmg1_f125_el_amp2ds->GetEntries();
    mmg1_f125_el_amp2ds->Scale(elScaleFactor_mmg1);
	mmg1_f125_el_amp2ds->RebinX(8);
	mmg1_f125_el_amp2ds->ProjectionX("MMG1 No Radiator, electrons",120,210);
	TObject *obj6 = HistDQM->FindObject("urw_f125_el_amp2ds");
	TH2 *urw_f125_el_amp2ds = (TH2 *)obj6;
	elScaleFactor_urw = 1./urw_f125_el_amp2ds->GetEntries();
    urw_f125_el_amp2ds->Scale(elScaleFactor_urw);
	urw_f125_el_amp2ds->RebinX(8);
	urw_f125_el_amp2ds->ProjectionX("URW No Radiator, electrons",30,120);
	
	TCanvas *c2 = new TCanvas("c2","", 1200, 800);
	c2->cd();
 	gPad->SetGridy();
	
	TH1F *gem_e = (TH1F*)file2->Get("GEM No Radiator, electrons");
	TH1F *mmg1_e = (TH1F*)file2->Get("MMG1 No Radiator, electrons");
	TH1F *urw_e = (TH1F*)file2->Get("URW No Radiator, electrons");
	gem_e->SetLineColor(51); //purple
	gem_e->SetMarkerStyle(20); //filled circle
	gem_e->SetMarkerColor(51);
	mmg1_e->SetLineColor(209); //green
	mmg1_e->SetMarkerStyle(20);
	mmg1_e->SetMarkerColor(209);
	urw_e->SetLineColor(94); //orange
	urw_e->SetMarkerStyle(20);
	urw_e->SetMarkerColor(94);
	
	TLegend *l2 = new TLegend(0.7,0.7,0.9,0.9);
	l2->AddEntry(gem_e,"GEM, 1.43 kV/cm DF","lp");
	l2->AddEntry(mmg1_e,"MMG1, 1.5 kV/cm DF","lp");
	l2->AddEntry(urw_e,"uRWELL, 1.6 kV/cm DF","lp");
	
	gem_e->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	gem_e->GetYaxis()->SetNdivisions(520);
	gem_e->GetXaxis()->SetRangeUser(50,220);
	gem_e->SetTitle("Prototype ADC Responses in Time With No Radiator for 10 GeV Electrons");
	gem_e->Draw("");
	mmg1_e->Draw("same");
	urw_e->Draw("same");
	l2->Draw();
	gem_e->SaveAs("all_drift_noRad_e.png");
	
	
	TObject *obj7 = HistDQM->FindObject("f125_pi_amp2ds");
	TH2 *f125_pi_amp2ds_n = (TH2 *)obj7;
	piScaleFactor = 1./f125_pi_amp2ds_n->GetEntries();
    f125_pi_amp2ds_n->Scale(piScaleFactor);
	f125_pi_amp2ds_n->RebinX(8);
	f125_pi_amp2ds_n->ProjectionX("GEM No Radiator, pions",80,170);
	TObject *obj8 = HistDQM->FindObject("mmg1_f125_pi_amp2ds");
	TH2 *mmg1_f125_pi_amp2ds = (TH2 *)obj8;
	piScaleFactor_mmg1 = 1./mmg1_f125_pi_amp2ds->GetEntries();
    mmg1_f125_pi_amp2ds->Scale(piScaleFactor_mmg1);
	mmg1_f125_pi_amp2ds->RebinX(8);
	mmg1_f125_pi_amp2ds->ProjectionX("MMG1 No Radiator, pions",120,210);
	TObject *obj9 = HistDQM->FindObject("urw_f125_pi_amp2ds");
	TH2 *urw_f125_pi_amp2ds = (TH2 *)obj9;
	piScaleFactor_urw = 1./urw_f125_pi_amp2ds->GetEntries();
    urw_f125_pi_amp2ds->Scale(piScaleFactor_urw);
	urw_f125_pi_amp2ds->RebinX(8);
	urw_f125_pi_amp2ds->ProjectionX("URW No Radiator, pions",30,120);
	
	TCanvas *c3 = new TCanvas("c3","", 1200, 800);
	c3->cd();
 	gPad->SetGridy();
	
	TH1F *gem_pi = (TH1F*)file2->Get("GEM No Radiator, pions");
	TH1F *mmg1_pi = (TH1F*)file2->Get("MMG1 No Radiator, pions");
	TH1F *urw_pi = (TH1F*)file2->Get("URW No Radiator, pions");
	gem_pi->SetLineColor(51); //purple
	gem_pi->SetMarkerStyle(21); //filled square
	gem_pi->SetMarkerColor(51);
	mmg1_pi->SetLineColor(209); //green
	mmg1_pi->SetMarkerStyle(21);
	mmg1_pi->SetMarkerColor(209);
	urw_pi->SetLineColor(94); //orange
	urw_pi->SetMarkerStyle(21);
	urw_pi->SetMarkerColor(94);
	
	TLegend *l3 = new TLegend(0.7,0.7,0.9,0.9);
	l3->AddEntry(gem_e,"GEM, 1.43 kV/cm DF","lp");
	l3->AddEntry(mmg1_e,"MMG1, 1.5 kV/cm DF","lp");
	l3->AddEntry(urw_e,"uRWELL, 1.6 kV/cm DF","lp");
	
	gem_pi->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	gem_pi->GetYaxis()->SetNdivisions(520);
	gem_pi->GetXaxis()->SetRangeUser(50,220);
	gem_pi->SetTitle("Prototype ADC Responses in Time With No Radiator for 10 GeV Pions");
	gem_pi->Draw("");
	mmg1_pi->Draw("same");
	urw_pi->Draw("same");
	l3->Draw();
	gem_pi->SaveAs("all_drift_noRad_pi.png");
	
	//=======================================
	
	
}