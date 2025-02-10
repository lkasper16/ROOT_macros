#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void geantSimCompare() {
	
	TString legendList[] = {"Exit Radiator","Exit Kapton Window","Exit Dead Xe","Exit Kapton Base Layer","Exit Cathode","Exit Xe Drift Gap"};
	//TString legendList[] = {"Exit Radiator","Exit Vacuum Layer","Exit Kapton Window","Exit Cathode (Al)","Exit Xe Drift Gap"};
	TLegend *l1 = new TLegend(0.65, 0.7, 0.9, 0.9);
	TLegend *l2 = new TLegend(0.65, 0.7, 0.9, 0.9);
	
	//=======================================
	//Electrons
	
	TFile *file0 = TFile::Open("fermiSim/regularR/fdc15_e-10000MeV_Xe10CO2_d21:1.1mm_r15cm_m1_DoubleKapton.root");
	if (!file0 || file0->IsZombie()) {
      std::cerr << "Error: Could not open file " << file0 << std::endl;
    }
    
	TObject *obj1 = file0->Get("hist31");
      TH1 *exitRad = (TH1*)obj1;
      exitRad->SetLineColor(2);
      exitRad->SetLineWidth(2);
      exitRad->SetDirectory(0);
      l1->AddEntry(exitRad, legendList[0], "l");
	
	TObject *obj2 = file0->Get("hist32");
      TH1 *exitWin = (TH1*)obj2;
      exitWin->SetLineColor(209);
      exitWin->SetLineWidth(2);
      exitWin->SetDirectory(0);
      l1->AddEntry(exitWin, legendList[1], "l");
      
    TObject *obj4 = file0->Get("hist34");
      TH1 *exitDeadA = (TH1*)obj4;
      exitDeadA->SetLineColor(7);
      exitDeadA->SetLineWidth(2);
      exitDeadA->SetDirectory(0);
      l1->AddEntry(exitDeadA, legendList[2], "l");
      
    TObject *obj6 = file0->Get("hist35");
      TH1 *exitBase = (TH1*)obj6;
      exitBase->SetLineColor(94);
      exitBase->SetLineWidth(2);
      exitBase->SetDirectory(0);
      l1->AddEntry(exitBase, legendList[3], "l");
      
    TObject *obj3 = file0->Get("hist33");
      TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(4);
      exitCath->SetLineWidth(2);
      exitCath->SetDirectory(0);
      l1->AddEntry(exitCath, legendList[4], "l");
        
    TObject *obj5 = file0->Get("hist26");
      TH1 *exitDet = (TH1*)obj5;
      exitDet->SetLineColor(6);
      exitDet->SetLineWidth(2);
      exitDet->SetDirectory(0);
      l1->AddEntry(exitDet, legendList[5], "l");
    
    TCanvas *c1 = new TCanvas("c1","25um Kapton, 400um Xe, 50um Kapton, 0.2um Cr, 21mm Xe", 1200, 800);
	gStyle->SetOptStat(00000);
	c1->Divide(2,1);
	c1->cd(1);
	
    exitRad->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad->GetYaxis()->SetTitle("Count");
    exitRad->SetTitle("150K e-, Regular Radiator");
    exitRad->SetMaximum(16000);
    exitRad->Draw();
	exitWin->Draw("same");
	exitDeadA->Draw("same");
	exitBase->Draw("same");
	exitCath->Draw("same");
	exitDet->Draw("same");
	l1->SetHeader("#gamma Energy", "C");
  	l1->Draw();
	//c1->SaveAs("sergeyFermiConstruction.png");
	
	//=======================================
	//Pions
	
	TFile *file1 = TFile::Open("fermiSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d21:1.1mm_r15cm_m1_transparentR.root");
	if (!file1 || file1->IsZombie()) {
      std::cerr << "Error: Could not open file " << file1 << std::endl;
    }
    
	TObject *obj7 = file1->Get("hist31");
      TH1 *exitRad1 = (TH1*)obj7;
      exitRad1->SetLineColor(2);
      exitRad1->SetLineWidth(2);
      exitRad1->SetDirectory(0);
      l2->AddEntry(exitRad1, legendList[0], "l");
	
	TObject *obj8 = file1->Get("hist32");
      TH1 *exitWin1 = (TH1*)obj8;
      exitWin1->SetLineColor(209);
      exitWin1->SetLineWidth(2);
      exitWin1->SetDirectory(0);
      l2->AddEntry(exitWin1, legendList[1], "l");
      
    TObject *obj9 = file1->Get("hist34");
      TH1 *exitDeadA1 = (TH1*)obj9;
      exitDeadA1->SetLineColor(7);
      exitDeadA1->SetLineWidth(2);
      exitDeadA1->SetDirectory(0);
      l2->AddEntry(exitDeadA1, legendList[2], "l");
      
    TObject *obj10 = file1->Get("hist35");
      TH1 *exitBase1 = (TH1*)obj10;
      exitBase1->SetLineColor(94);
      exitBase1->SetLineWidth(2);
      exitBase1->SetDirectory(0);
      l2->AddEntry(exitBase1, legendList[3], "l");
      
    TObject *obj11 = file1->Get("hist33");
      TH1 *exitCath1 = (TH1*)obj11;
      exitCath1->SetLineColor(4);
      exitCath1->SetLineWidth(2);
      exitCath1->SetDirectory(0);
      l2->AddEntry(exitCath1, legendList[4], "l");
        
    TObject *obj12 = file1->Get("hist26");
      TH1 *exitDet1 = (TH1*)obj12;
      exitDet1->SetLineColor(6);
      exitDet1->SetLineWidth(2);
      exitDet1->SetDirectory(0);
      l2->AddEntry(exitDet1, legendList[5], "l");
    
	//gStyle->SetOptStat(00000);
	c1->cd(2);
    exitRad1->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad1->GetYaxis()->SetTitle("Count");
    exitRad1->SetTitle("150K e-, Transparent Radiator");
    //exitRad1->SetTitle("55um Kapton, 5um Cu, 19.9mm Xe");
    exitRad1->SetMaximum(16000);
    exitRad1->Draw();
	exitWin1->Draw("same");
	exitDeadA1->Draw("same");
	exitBase1->Draw("same");
	exitCath1->Draw("same");
	exitDet1->Draw("same");
	l2->SetHeader("#gamma Energy", "C");
  	l2->Draw();
	c1->SaveAs("fermi_sim_compare.png");
	
	//==================================================
	// Ratio Plots
	
	TCanvas *c3 = new TCanvas("c3","c3", 1200, 800);
	c3->Divide(2,2);
	
	c3->cd(1);
	TH1D *cathodeSubtract1 = new TH1D("cathodeSubtract1","150K e-, Regular Radiator; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract1->Add(exitCath,exitDet,1,-1);
	//TH1D *escapeSubtract1 = new TH1D("escapeSubtract1","25um Kapton, 400um Xe, 50um Kapton, 0.2um Cr, 21mm Xe; TR Photon Energy [keV]; Count",100,0.,50.);
	//escapeSubtract1->Add(cathodeSubtract1,exitDet,1,-1);
	cathodeSubtract1->SetMinimum(0);
	cathodeSubtract1->SetLineWidth(2);
	cathodeSubtract1->Draw();
	
	c3->cd(2);
	TH1D *cathodeSubtract2 = new TH1D("cathodeSubtract2","150K e-, Transparent Radiator; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract2->Add(exitCath1,exitDet1,1,-1);
	//TH1D *escapeSubtract2 = new TH1D("escapeSubtract2","55um Kapton, 5um Cu, 19.9mm Xe; TR Photon Energy [keV]; Count",100,0.,50.);
	//escapeSubtract2->Add(cathodeSubtract2,exitDet1,1,-1);
	cathodeSubtract2->SetMinimum(0);
	cathodeSubtract2->SetLineWidth(2);
	cathodeSubtract2->Draw();
	
	c3->cd(3);
	auto rp1 = new TRatioPlot(cathodeSubtract1, cathodeSubtract2);
    c3->SetTicks(0, 1);
    rp1->Draw();
    rp1->GetLowYaxis()->SetNdivisions(505);
    //rp1->GetLowerRefGraph()->SetMinimum(-1);
   	//rp1->GetLowerRefGraph()->SetMaximum(3.5);
	
    c3->SaveAs("fermi_sim_compare_ratios.png");
	
}