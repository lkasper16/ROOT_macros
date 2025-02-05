#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void geantConstructionCompare() {
	
	TString legendList[] = {"Exit Radiator","Exit Kapton Window","Exit Dead Xe","Exit Cathode (Cr)","Exit Xe Drift Gap","Exit Kapton Base Layer"};
	TLegend *l1 = new TLegend(0.75, 0.65, 0.9, 0.9);
	TLegend *l2 = new TLegend(0.75, 0.65, 0.9, 0.9);
	TLegend *l3 = new TLegend(0.75, 0.65, 0.9, 0.9);
	
	//=======================================
	//Sergey's Construction
	
	TFile *file0 = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d21:1.1mm_r15cm_m1_SingleKapton.root");
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
    
    TObject *obj3 = file0->Get("hist33");
      TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(4);
      exitCath->SetLineWidth(2);
      exitCath->SetDirectory(0);
      l1->AddEntry(exitCath, legendList[3], "l");
    
    TObject *obj4 = file0->Get("hist34");
      TH1 *exitDeadA = (TH1*)obj4;
      exitDeadA->SetLineColor(7);
      exitDeadA->SetLineWidth(2);
      exitDeadA->SetDirectory(0);
      l1->AddEntry(exitDeadA, legendList[2], "l");
    
    TObject *obj5 = file0->Get("hist26");
      TH1 *exitDet = (TH1*)obj5;
      exitDet->SetLineColor(6);
      exitDet->SetLineWidth(2);
      exitDet->SetDirectory(0);
      l1->AddEntry(exitDet, legendList[4], "l");
    
    TCanvas *c1 = new TCanvas("c1","150K e- with Rad, XeCO2 90:10", 1200, 800);
	gStyle->SetOptStat(00000);
	c1->Divide(2,1);
	c1->cd(1);
	
    exitRad->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad->GetYaxis()->SetTitle("Count");
    exitRad->SetTitle("No Dead Xe Gap, Cr=1um");
    exitRad->Draw();
	exitWin->Draw("same");
	exitDeadA->Draw("same");
	exitCath->Draw("same");
	exitDet->Draw("same");
	l1->SetHeader("#gamma Energy", "C");
  	l1->Draw();
	//c1->SaveAs("sergeyFermiConstruction.png");
	
	//=======================================
	//Fermi Construction w/o Second Kapton Layer
	
/*
	TFile *file1 = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d21:1.1mm_r15cm_m1_SingleKapton_new.root");
	if (!file1 || file1->IsZombie()) {
      std::cerr << "Error: Could not open file " << file1 << std::endl;
    }
    
	TObject *obj6 = file1->Get("hist31");
      exitRad = (TH1*)obj6;
      exitRad->SetLineColor(2);
      exitRad->SetLineWidth(2);
      exitRad->SetDirectory(0);
      l2->AddEntry(exitRad, legendList[0], "l");
    
	TObject *obj7 = file1->Get("hist32");
      exitWin = (TH1*)obj7;
      exitWin->SetLineColor(209);
      exitWin->SetLineWidth(2);
      exitWin->SetDirectory(0);
      l2->AddEntry(exitWin, legendList[1], "l");
	
	TObject *obj8 = file1->Get("hist34");
      exitDeadA = (TH1*)obj8;
      exitDeadA->SetLineColor(7);
      exitDeadA->SetLineWidth(2);
      exitDeadA->SetDirectory(0);
      l2->AddEntry(exitDeadA, legendList[2], "l");
	
	TObject *obj9 = file1->Get("hist33");
      exitCath = (TH1*)obj9;
      exitCath->SetLineColor(4);
      exitCath->SetLineWidth(2);
      exitCath->SetDirectory(0);
      l2->AddEntry(exitCath, legendList[3], "l");
	
	TObject *obj10 = file1->Get("hist26");
      exitDet = (TH1*)obj10;
      exitDet->SetLineColor(6);
      exitDet->SetLineWidth(2);
      exitDet->SetDirectory(0);
      l2->AddEntry(exitDet, legendList[4], "l");
	
	TCanvas *c2 = new TCanvas("c2","Fermi Single Kapton Construction", 1200, 800);
	gStyle->SetOptStat(00000);
	c2->cd();
 	//gPad->SetGridy();
    exitRad->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad->GetYaxis()->SetTitle("Count");
    exitRad->SetTitle("250K e- with Rad, XeCO2 90:10");
    exitRad->Draw();
	exitWin->Draw("same");
	exitDeadA->Draw("same");
	exitCath->Draw("same");
	exitDet->Draw("same");
	l2->SetHeader("#gamma Energy", "C");
  	l2->Draw();
	c2->SaveAs("singleKaptonFermiConstruction.png");
*/
	//=======================================
	//Fermi Construction w Second Kapton Layer
	
	TFile *file2 = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d21:1.1mm_r15cm_m1_DoubleKapton.root");
	if (!file2 || file2->IsZombie()) {
      std::cerr << "Error: Could not open file " << file2 << std::endl;
    }
    
	TObject *obj11 = file2->Get("hist31");
      TH1 *exitRad1 = (TH1*)obj11;
      exitRad1->SetLineColor(2);
      exitRad1->SetLineWidth(2);
      exitRad1->SetDirectory(0);
      l3->AddEntry(exitRad1, legendList[0], "l");
	
	TObject *obj12 = file2->Get("hist32");
      TH1 *exitWin1 = (TH1*)obj12;
      exitWin1->SetLineColor(209);
      exitWin1->SetLineWidth(2);
      exitWin1->SetDirectory(0);
      l3->AddEntry(exitWin1, legendList[1], "l");
    
    TObject *obj13 = file2->Get("hist34");
      TH1 *exitDeadA1 = (TH1*)obj13;
      exitDeadA1->SetLineColor(7);
      exitDeadA1->SetLineWidth(2);
      exitDeadA1->SetDirectory(0);
      l3->AddEntry(exitDeadA1, legendList[2], "l");
    
    TObject *obj14 = file2->Get("hist35");
      TH1 *exitKap = (TH1*)obj14;
      exitKap->SetLineColor(93);
      exitKap->SetLineWidth(2);
      exitKap->SetDirectory(0);
      l3->AddEntry(exitKap, legendList[5], "l");
    
    TObject *obj15 = file2->Get("hist33");
      TH1 *exitCath1 = (TH1*)obj15;
      exitCath1->SetLineColor(4);
      exitCath1->SetLineWidth(2);
      exitCath1->SetDirectory(0);
      l3->AddEntry(exitCath1, legendList[3], "l");
    
    TObject *obj16 = file2->Get("hist26");
      TH1 *exitDet1 = (TH1*)obj16;
      exitDet1->SetLineColor(6);
      exitDet1->SetLineWidth(2);
      exitDet1->SetDirectory(0);
      l3->AddEntry(exitDet1, legendList[4], "l");
    
	//TCanvas *c3 = new TCanvas("c3","Fermi Double Kapton Construction", 1200, 800);
	//gStyle->SetOptStat(00000);
	//c3->cd();
	c1->cd(2);
    exitRad1->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad1->GetYaxis()->SetTitle("Count");
    exitRad1->SetTitle("400um Dead Xe Gap, 50um Kapton, Cr=0.2um");
    exitRad1->Draw();
	exitWin1->Draw("same");
	exitDeadA1->Draw("same");
	exitKap->Draw("same");
	exitCath1->Draw("same");
	exitDet1->Draw("same");
	l3->SetHeader("#gamma Energy", "C");
  	l3->Draw();
	//c3->SaveAs("doubleKaptonFermiConstruction.png");
	c1->SaveAs("fermiConstructionCompare.png");
	
	//==================================================
	// Ratio Plots
	
	TCanvas *c3 = new TCanvas("c3","c3", 1200, 800);
	gStyle->SetOptStat(00000);
	c3->Divide(2,2);
	c3->cd(1);
	
	TH1D *sergeySubtract = new TH1D("sergeySubtract","No Dead Xe Gap, Cr=1um",100,0.,100.);
	sergeySubtract->Add(exitRad,exitCath,1,-1);
	sergeySubtract->Draw();
	
	c3->cd(2);
	TH1D *fermiSubtract = new TH1D("fermiSubtract","400um Dead Xe Gap, 50um Kapton, Cr=0.2um",100,0.,100.);
	fermiSubtract->Add(exitRad1,exitCath1,1,-1);
	fermiSubtract->Draw();
	
	c3->cd(3);
	auto rp1 = new TRatioPlot(sergeySubtract, fermiSubtract);
    c3->SetTicks(0, 1);
    rp1->Draw();
    rp1->GetLowYaxis()->SetNdivisions(505);
	
	/*
	auto rp1 = new TRatioPlot(exitRad, exitRad1);
    c3->SetTicks(0, 1);
    exitRad->SetTitle("#gamma Energy Exit Radiator");
    rp1->Draw();
    rp1->GetLowYaxis()->SetNdivisions(505);
    //rp->GetUpperPad()->cd();
    //TLegend *legend = new TLegend(0.3, 0.7, 0.7, 0.85);
    //legend->AddEntry("h1", "First histogram", "l");
    //legend->AddEntry("h2", "Second histogram", "le");
    //legend->Draw();
    
    c3->cd(2);
	auto rp2 = new TRatioPlot(exitWin, exitWin1);
    exitWin->SetTitle("#gamma Energy Exit Kapton Window");
    rp2->Draw();
    rp2->GetLowYaxis()->SetNdivisions(505);
    //
    c3->cd(3);
	auto rp3 = new TRatioPlot(exitDeadA, exitDeadA1);
    exitDeadA->SetTitle("#gamma Energy Exit Dead Xe");
    rp3->Draw();
    rp3->GetLowYaxis()->SetNdivisions(505);
    //
    c3->cd(4);
	auto rp4 = new TRatioPlot(exitCath, exitCath1);
    exitCath->SetTitle("#gamma Energy Exit Cathode (Cr)");
    rp4->Draw();
    rp4->GetLowYaxis()->SetNdivisions(505);
    //
    c3->cd(5);
	auto rp5 = new TRatioPlot(exitDet, exitDet1);
    exitDet->SetTitle("#gamma Energy Exit Xe Drift Gap");
    rp5->Draw();
    rp5->GetLowYaxis()->SetNdivisions(505);
    */
    
    c3->SaveAs("fermiConstructionCompareRatios.png");
	
}