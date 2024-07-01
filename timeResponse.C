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
	
	//=======================================
	//GEMTRD No Rad
	
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
	//GEMTRD Double Foil Rad
	
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
	//All Prototypes, No Rad, Electrons
	
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
	
	//All Prototypes, No Rad, Pions
	
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
	//uRWell-TRD, XeCO2
	
	TFile *file3 = TFile::Open("Run_003196_Output.root");
	HistDQM = (TList *)file3->Get("HistDQM");
	TObject *obj10 = HistDQM->FindObject("urw_f125_pi_amp2ds");
	urw_f125_pi_amp2ds = (TH2 *)obj10;
	piScaleFactor_urw = 1./urw_f125_pi_amp2ds->GetEntries();
    urw_f125_pi_amp2ds->Scale(piScaleFactor_urw);
	urw_f125_pi_amp2ds->RebinX(8);
	urw_f125_pi_amp2ds->ProjectionX("URW 490",30,120);
	
	TFile *file4 = TFile::Open("Run_003199_Output.root");
	HistDQM = (TList *)file4->Get("HistDQM");
	TObject *obj11 = HistDQM->FindObject("urw_f125_pi_amp2ds");
	urw_f125_pi_amp2ds = (TH2 *)obj11;
	piScaleFactor_urw = 1./urw_f125_pi_amp2ds->GetEntries();
    urw_f125_pi_amp2ds->Scale(piScaleFactor_urw);
	urw_f125_pi_amp2ds->RebinX(8);
	urw_f125_pi_amp2ds->ProjectionX("URW 495",30,120);
	
	TFile *file5 = TFile::Open("Run_003218_Output.root");
	HistDQM = (TList *)file5->Get("HistDQM");
	TObject *obj12 = HistDQM->FindObject("urw_f125_pi_amp2ds");
	urw_f125_pi_amp2ds = (TH2 *)obj12;
	piScaleFactor_urw = 1./urw_f125_pi_amp2ds->GetEntries();
    urw_f125_pi_amp2ds->Scale(piScaleFactor_urw);
	urw_f125_pi_amp2ds->RebinX(8);
	urw_f125_pi_amp2ds->ProjectionX("URW 540",30,120);
	
	TCanvas *c4 = new TCanvas("c4","", 1200, 800);
	c4->cd();
 	gPad->SetGridy();
 	
 	TH1F *urw_490 = (TH1F*)file3->Get("URW 490");
	TH1F *urw_495 = (TH1F*)file4->Get("URW 495");
	TH1F *urw_540 = (TH1F*)file5->Get("URW 540");
	urw_490->SetLineColor(51); //purple
	urw_490->SetMarkerStyle(21); //filled square
	urw_490->SetMarkerColor(51);
	urw_495->SetLineColor(209); //green
	urw_495->SetMarkerStyle(21);
	urw_495->SetMarkerColor(209);
	urw_540->SetLineColor(94); //orange
	urw_540->SetMarkerStyle(21);
	urw_540->SetMarkerColor(94);
	
 	TLegend *l4 = new TLegend(0.7,0.7,0.9,0.9);
	l4->AddEntry(urw_490,"Pions, 490V amp","lp");
	l4->AddEntry(urw_495,"Pions, 495V amp","lp");
	l4->AddEntry(urw_540,"Pions, 540V amp","lp");
	
	urw_540->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	urw_540->GetYaxis()->SetNdivisions(520);
	urw_540->GetXaxis()->SetRangeUser(50,220);
	urw_540->SetTitle("uRWELL-TRD ADC Responses in Time With 15cm Fleece Radiator for 10 GeV Pions");
	urw_540->Draw("");
	urw_490->Draw("same");
	urw_495->Draw("same");
	l4->Draw();
	urw_540->SaveAs("urwell_drift_pi.png");
	
	//=======================================
	//uRWell-TRD, XeCO2
	
	TFile *file6 = TFile::Open("Run_003196_Output.root");
	HistDQM = (TList *)file6->Get("HistDQM");
	TObject *obj13 = HistDQM->FindObject("urw_f125_el_amp2ds");
	urw_f125_el_amp2ds = (TH2 *)obj13;
	elScaleFactor_urw = 1./urw_f125_el_amp2ds->GetEntries();
    urw_f125_el_amp2ds->Scale(elScaleFactor_urw);
	urw_f125_el_amp2ds->RebinX(8);
	urw_f125_el_amp2ds->ProjectionX("URW 490 e",30,120);
	
	TFile *file7 = TFile::Open("Run_003199_Output.root");
	HistDQM = (TList *)file7->Get("HistDQM");
	TObject *obj14 = HistDQM->FindObject("urw_f125_el_amp2ds");
	urw_f125_el_amp2ds = (TH2 *)obj14;
	elScaleFactor_urw = 1./urw_f125_el_amp2ds->GetEntries();
    urw_f125_el_amp2ds->Scale(elScaleFactor_urw);
	urw_f125_el_amp2ds->RebinX(8);
	urw_f125_el_amp2ds->ProjectionX("URW 495 e",30,120);
	
	TFile *file8 = TFile::Open("Run_003218_Output.root");
	HistDQM = (TList *)file8->Get("HistDQM");
	TObject *obj15 = HistDQM->FindObject("urw_f125_el_amp2ds");
	urw_f125_el_amp2ds = (TH2 *)obj15;
	elScaleFactor_urw = 1./urw_f125_el_amp2ds->GetEntries();
    urw_f125_el_amp2ds->Scale(elScaleFactor_urw);
	urw_f125_el_amp2ds->RebinX(8);
	urw_f125_el_amp2ds->ProjectionX("URW 540 e",30,120);
	
	TCanvas *c5 = new TCanvas("c5","", 1200, 800);
	c5->cd();
 	gPad->SetGridy();
 	
 	TH1F *urw_490_e = (TH1F*)file6->Get("URW 490 e");
	TH1F *urw_495_e = (TH1F*)file7->Get("URW 495 e");
	TH1F *urw_540_e = (TH1F*)file8->Get("URW 540 e");
	urw_490_e->SetLineColor(51); //purple
	urw_490_e->SetMarkerStyle(21); //filled square
	urw_490_e->SetMarkerColor(51);
	urw_495_e->SetLineColor(209); //green
	urw_495_e->SetMarkerStyle(21);
	urw_495_e->SetMarkerColor(209);
	urw_540_e->SetLineColor(94); //orange
	urw_540_e->SetMarkerStyle(21);
	urw_540_e->SetMarkerColor(94);
	
 	TLegend *l5 = new TLegend(0.7,0.7,0.9,0.9);
	l5->AddEntry(urw_490_e,"Electrons, 490V amp","lp");
	l5->AddEntry(urw_495_e,"Electrons, 495V amp","lp");
	l5->AddEntry(urw_540_e,"Electrons, 540V amp","lp");
	
	urw_540_e->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	urw_540_e->GetYaxis()->SetNdivisions(520);
	urw_540_e->GetXaxis()->SetRangeUser(50,220);
	urw_540_e->SetTitle("uRWELL-TRD ADC Responses in Time With 15cm Fleece Radiator for 10 GeV Electrons");
	urw_540_e->Draw("");
	urw_490_e->Draw("same");
	urw_495_e->Draw("same");
	l5->Draw();
	urw_540_e->SaveAs("urwell_drift_el.png");
	
	//=======================================
	//MMG1-TRD, XeCO2
	
	TFile *file9 = TFile::Open("Run_003196_Output.root");
	HistDQM = (TList *)file9->Get("HistDQM");
	TObject *obj16 = HistDQM->FindObject("mmg1_f125_pi_amp2ds");
	mmg1_f125_pi_amp2ds = (TH2 *)obj16;
	piScaleFactor_mmg1 = 1./mmg1_f125_pi_amp2ds->GetEntries();
    mmg1_f125_pi_amp2ds->Scale(piScaleFactor_mmg1);
	mmg1_f125_pi_amp2ds->RebinX(8);
	mmg1_f125_pi_amp2ds->ProjectionX("MMG 595",120,210);
	
	TFile *file10 = TFile::Open("Run_003216_Output.root");
	HistDQM = (TList *)file10->Get("HistDQM");
	TObject *obj17 = HistDQM->FindObject("mmg1_f125_pi_amp2ds");
	mmg1_f125_pi_amp2ds = (TH2 *)obj17;
	piScaleFactor_mmg1 = 1./mmg1_f125_pi_amp2ds->GetEntries();
    mmg1_f125_pi_amp2ds->Scale(piScaleFactor_mmg1);
	mmg1_f125_pi_amp2ds->RebinX(8);
	mmg1_f125_pi_amp2ds->ProjectionX("MMG 625",120,210);
	
	TFile *file11 = TFile::Open("Run_003287_Output.root");
	HistDQM = (TList *)file11->Get("HistDQM");
	TObject *obj18 = HistDQM->FindObject("mmg1_f125_pi_amp2ds");
	mmg1_f125_pi_amp2ds = (TH2 *)obj18;
	piScaleFactor_mmg1 = 1./mmg1_f125_pi_amp2ds->GetEntries();
    mmg1_f125_pi_amp2ds->Scale(piScaleFactor_mmg1);
	mmg1_f125_pi_amp2ds->RebinX(8);
	mmg1_f125_pi_amp2ds->ProjectionX("MMG 675",120,210);
	
	TCanvas *c6 = new TCanvas("c6","", 1200, 800);
	c6->cd();
 	gPad->SetGridy();
 	
 	TH1F *mmg_595 = (TH1F*)file9->Get("MMG 595");
	TH1F *mmg_625 = (TH1F*)file10->Get("MMG 625");
	TH1F *mmg_675 = (TH1F*)file11->Get("MMG 675");
	mmg_595->SetLineColor(51); //purple
	mmg_595->SetMarkerStyle(21); //filled square
	mmg_595->SetMarkerColor(51);
	mmg_625->SetLineColor(209); //green
	mmg_625->SetMarkerStyle(21);
	mmg_625->SetMarkerColor(209);
	mmg_675->SetLineColor(94); //orange
	mmg_675->SetMarkerStyle(21);
	mmg_675->SetMarkerColor(94);
	
 	TLegend *l6 = new TLegend(0.7,0.7,0.9,0.9);
	l6->AddEntry(mmg_595,"Pions, 595V amp","lp");
	l6->AddEntry(mmg_625,"Pions, 625V amp","lp");
	l6->AddEntry(mmg_675,"Pions, 675V amp","lp");
	
	mmg_675->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	mmg_675->GetYaxis()->SetNdivisions(520);
	mmg_675->GetXaxis()->SetRangeUser(50,220);
	mmg_675->SetTitle("MMG1-TRD ADC Responses in Time With Radiator for Pions");
	mmg_675->Draw("");
	mmg_595->Draw("same");
	mmg_625->Draw("same");
	l6->Draw();
	mmg_675->SaveAs("mmg_drift_pi.png");
	
	//=======================================
	//MMG1-TRD, XeCO2
	
	TFile *file12 = TFile::Open("Run_003196_Output.root");
	HistDQM = (TList *)file12->Get("HistDQM");
	TObject *obj19 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
	mmg1_f125_el_amp2ds = (TH2 *)obj19;
	elScaleFactor_mmg1 = 1./mmg1_f125_el_amp2ds->GetEntries();
    mmg1_f125_el_amp2ds->Scale(elScaleFactor_mmg1);
	mmg1_f125_el_amp2ds->RebinX(8);
	mmg1_f125_el_amp2ds->ProjectionX("MMG 595 e",120,210);
	
	TFile *file13 = TFile::Open("Run_003216_Output.root");
	HistDQM = (TList *)file13->Get("HistDQM");
	TObject *obj20 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
	mmg1_f125_el_amp2ds = (TH2 *)obj20;
	elScaleFactor_mmg1 = 1./mmg1_f125_el_amp2ds->GetEntries();
    mmg1_f125_el_amp2ds->Scale(elScaleFactor_mmg1);
	mmg1_f125_el_amp2ds->RebinX(8);
	mmg1_f125_el_amp2ds->ProjectionX("MMG 625 e",120,210);
	
	TFile *file14 = TFile::Open("Run_003287_Output.root");
	HistDQM = (TList *)file14->Get("HistDQM");
	TObject *obj21 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
	mmg1_f125_el_amp2ds = (TH2 *)obj21;
	elScaleFactor_mmg1 = 1./mmg1_f125_el_amp2ds->GetEntries();
    mmg1_f125_el_amp2ds->Scale(elScaleFactor_mmg1);
	mmg1_f125_el_amp2ds->RebinX(8);
	mmg1_f125_el_amp2ds->ProjectionX("MMG 675 e",120,210);
	
	TCanvas *c7 = new TCanvas("c7","", 1200, 800);
	c7->cd();
 	gPad->SetGridy();
 	
 	TH1F *mmg_595_e = (TH1F*)file12->Get("MMG 595 e");
	TH1F *mmg_625_e = (TH1F*)file13->Get("MMG 625 e");
	TH1F *mmg_675_e = (TH1F*)file14->Get("MMG 675 e");
	mmg_595_e->SetLineColor(51); //purple
	mmg_595_e->SetMarkerStyle(21); //filled square
	mmg_595_e->SetMarkerColor(51);
	mmg_625_e->SetLineColor(209); //green
	mmg_625_e->SetMarkerStyle(21);
	mmg_625_e->SetMarkerColor(209);
	mmg_675_e->SetLineColor(94); //orange
	mmg_675_e->SetMarkerStyle(21);
	mmg_675_e->SetMarkerColor(94);
	
 	TLegend *l7 = new TLegend(0.7,0.7,0.9,0.9);
	l7->AddEntry(mmg_595_e,"Electrons, 595V amp","lp");
	l7->AddEntry(mmg_625_e,"Electrons, 625V amp","lp");
	l7->AddEntry(mmg_675_e,"Electrons, 675V amp","lp");
	
	mmg_675_e->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
	mmg_675_e->GetYaxis()->SetNdivisions(520);
	mmg_675_e->GetXaxis()->SetRangeUser(50,220);
	mmg_675_e->SetTitle("MMG1-TRD ADC Responses in Time With Radiator for Electrons");
	mmg_675_e->Draw("");
	mmg_595_e->Draw("same");
	mmg_625_e->Draw("same");
	l7->Draw();
	mmg_675_e->SaveAs("mmg_drift_el.png");
	
	//=======================================

	
	
}
