#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void geantConstructionCompare_Gas() {
	
	TString legendList[] = {"Exit Radiator","Exit Window","Exit Dead Xe","Exit Kapton Base Layer","Exit Cathode","Exit Drift Gap"};
	TString legendList1[] = {"Exit Radiator (M)","Exit Window (M)","Exit Cathode (M)","Exit Drift Gap (M)","Exit Radiator (R)","Exit Window (R)","Exit Cathode (R)","Exit Drift Gap (R)"};
	TString legendList2[] = {"regularM","regularR"};
	TLegend *l1 = new TLegend(0.65, 0.7, 0.9, 0.9);
	TLegend *l2 = new TLegend(0.65, 0.7, 0.9, 0.9);
	TLegend *l3 = new TLegend(0.65, 0.7, 0.9, 0.9);
	TLegend *l4 = new TLegend(0.65, 0.7, 0.9, 0.9);
	TLegend *l5 = new TLegend(0.43, 0.7, 0.9, 0.9);
	TLegend *l6 = new TLegend(0.43, 0.7, 0.9, 0.9);
	TLegend *l7 = new TLegend(0.75, 0.7, 0.9, 0.9);
	TLegend *l8 = new TLegend(0.75, 0.7, 0.9, 0.9);
	TLegend *l9 = new TLegend(0.75, 0.7, 0.9, 0.9);
	TLegend *l10 = new TLegend(0.75, 0.7, 0.9, 0.9);
	TLegend *l11 = new TLegend(0.75, 0.7, 0.9, 0.9);
	TLegend *l12 = new TLegend(0.75, 0.7, 0.9, 0.9);
	TLegend *l13 = new TLegend(0.75, 0.7, 0.9, 0.9);
	TLegend *l14 = new TLegend(0.75, 0.7, 0.9, 0.9);
	
	TCanvas *c1 = new TCanvas("c1","150K e- with 20cm Rad", 1200, 800);
	gStyle->SetOptStat(00000);
	c1->Divide(2,2);
	
	//=======================================
	TFile *file0 = TFile::Open("largeGemSim/regularM/fdc15_e-6000MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root");
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
      exitWin->SetLineColor(3);
      exitWin->SetLineWidth(2);
      exitWin->SetDirectory(0);
      l1->AddEntry(exitWin, legendList[1], "l");
    
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
	
	c1->cd(1);
    exitRad->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad->GetYaxis()->SetTitle("Count");
    exitRad->SetTitle("XeCO2, regularM");
    exitRad->SetMaximum(30000);
    exitRad->Scale(1./exitRad->GetEntries());
    exitWin->Scale(1./exitWin->GetEntries());
    exitCath->Scale(1./exitCath->GetEntries());
    exitDet->Scale(1./exitDet->GetEntries());
    exitRad->Draw();
	exitWin->Draw("same");
	exitCath->Draw("same");
	exitDet->Draw("same");
	l1->SetTextSize(0.025);
	l1->SetHeader("#gamma Energy", "C");
  	l1->Draw();
	
	//=======================================
	TFile *file1 = TFile::Open("largeGemSim/regularM/fdc15_e-6000MeV_Kr10CO2_d30:1.5mm_r20cm_m1.root");
	if (!file1 || file1->IsZombie()) {
      std::cerr << "Error: Could not open file " << file1 << std::endl;
    }
    
	TObject *obj4 = file1->Get("hist31");
      TH1 *exitRad2 = (TH1*)obj4;
      exitRad2->SetLineColor(2);
      exitRad2->SetLineWidth(2);
      exitRad2->SetDirectory(0);
      l2->AddEntry(exitRad2, legendList[0], "l");
	
	TObject *obj6 = file1->Get("hist32");
      TH1 *exitWin2 = (TH1*)obj6;
      exitWin2->SetLineColor(3);
      exitWin2->SetLineWidth(2);
      exitWin2->SetDirectory(0);
      l2->AddEntry(exitWin2, legendList[1], "l");
    
    TObject *obj7 = file1->Get("hist33");
      TH1 *exitCath2 = (TH1*)obj7;
      exitCath2->SetLineColor(4);
      exitCath2->SetLineWidth(2);
      exitCath2->SetDirectory(0);
      l2->AddEntry(exitCath2, legendList[4], "l");
        
    TObject *obj8 = file1->Get("hist26");
      TH1 *exitDet2 = (TH1*)obj8;
      exitDet2->SetLineColor(6);
      exitDet2->SetLineWidth(2);
      exitDet2->SetDirectory(0);
      l2->AddEntry(exitDet2, legendList[5], "l");
	
	c1->cd(2);
	exitRad2->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad2->GetYaxis()->SetTitle("Count");
    exitRad2->SetTitle("KrCO2, regularM");
    exitRad2->SetMaximum(30000);
    exitRad2->Scale(1./exitRad2->GetEntries());
    exitWin2->Scale(1./exitWin2->GetEntries());
    exitCath2->Scale(1./exitCath2->GetEntries());
    exitDet2->Scale(1./exitDet2->GetEntries());
    exitRad2->Draw();
	exitWin2->Draw("same");
	exitCath2->Draw("same");
	exitDet2->Draw("same");
	l2->SetTextSize(0.025);
	l2->SetHeader("#gamma Energy", "C");
  	l2->Draw();
	
	//=======================================
	TFile *file2 = TFile::Open("largeGemSim/regularR/fdc15_e-6000MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root");
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
      exitWin1->SetLineColor(3);
      exitWin1->SetLineWidth(2);
      exitWin1->SetDirectory(0);
      l3->AddEntry(exitWin1, legendList[1], "l");
        
    TObject *obj15 = file2->Get("hist33");
      TH1 *exitCath1 = (TH1*)obj15;
      exitCath1->SetLineColor(4);
      exitCath1->SetLineWidth(2);
      exitCath1->SetDirectory(0);
      l3->AddEntry(exitCath1, legendList[4], "l");
    
    TObject *obj16 = file2->Get("hist26");
      TH1 *exitDet1 = (TH1*)obj16;
      exitDet1->SetLineColor(6);
      exitDet1->SetLineWidth(2);
      exitDet1->SetDirectory(0);
      l3->AddEntry(exitDet1, legendList[5], "l");
    
    c1->cd(3);
    exitRad1->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad1->GetYaxis()->SetTitle("Count");
    exitRad1->SetTitle("XeCO2, regularR");
    exitRad1->SetMaximum(30000);
    exitRad1->Scale(1./exitRad1->GetEntries());
    exitWin1->Scale(1./exitWin1->GetEntries());
    exitCath1->Scale(1./exitCath1->GetEntries());
    exitDet1->Scale(1./exitDet1->GetEntries());
    exitRad1->Draw();
	exitWin1->Draw("same");
	exitCath1->Draw("same");
	exitDet1->Draw("same");
	l3->SetTextSize(0.025);
	l3->SetHeader("#gamma Energy", "C");
  	l3->Draw();
    
    //==================================================
    TFile *file3 = TFile::Open("largeGemSim/regularR/fdc15_e-6000MeV_Kr10CO2_d30:1.5mm_r20cm_m1.root");
    
    if (!file3 || file3->IsZombie()) {
      std::cerr << "Error: Could not open file " << file3 << std::endl;
    }
    
	TObject *obj17 = file3->Get("hist31");
      TH1 *exitRad3 = (TH1*)obj17;
      exitRad3->SetLineColor(2);
      exitRad3->SetLineWidth(2);
      exitRad3->SetDirectory(0);
      l4->AddEntry(exitRad3, legendList[0], "l");
		
	TObject *obj18 = file3->Get("hist32");
      TH1 *exitWin3 = (TH1*)obj18;
      exitWin3->SetLineColor(3);
      exitWin3->SetLineWidth(2);
      exitWin3->SetDirectory(0);
      l4->AddEntry(exitWin3, legendList[1], "l");
        
    TObject *obj19 = file3->Get("hist33");
      TH1 *exitCath3 = (TH1*)obj19;
      exitCath3->SetLineColor(4);
      exitCath3->SetLineWidth(2);
      exitCath3->SetDirectory(0);
      l4->AddEntry(exitCath3, legendList[4], "l");
    
    TObject *obj20 = file3->Get("hist26");
      TH1 *exitDet3 = (TH1*)obj20;
      exitDet3->SetLineColor(6);
      exitDet3->SetLineWidth(2);
      exitDet3->SetDirectory(0);
      l4->AddEntry(exitDet3, legendList[5], "l");
    
    c1->cd(4);
    exitRad3->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad3->GetYaxis()->SetTitle("Count");
    exitRad3->SetTitle("KrCO2, regularR");
    exitRad3->SetMaximum(30000);
    exitRad3->Scale(1./exitRad3->GetEntries());
    exitWin3->Scale(1./exitWin3->GetEntries());
    exitCath3->Scale(1./exitCath3->GetEntries());
    exitDet3->Scale(1./exitDet3->GetEntries());
    exitRad3->Draw();
	exitWin3->Draw("same");
	exitCath3->Draw("same");
	exitDet3->Draw("same");
	l4->SetTextSize(0.025);
	l4->SetHeader("#gamma Energy", "C");
  	l4->Draw();
  	
	
	c1->SaveAs("lgt_simOptionCompare_scaled.png");
	//c1->SaveAs("ConstructionCompare_lgt_gammaM.png");
	
	//==================================================
	
	TCanvas *c3 = new TCanvas("c3","c3", 1400, 1000);
	c3->Divide(2,1);
	
	c3->cd(1);
    exitRad->SetTitle("XeCO2");
    exitRad->SetMarkerStyle(4);
    exitRad->SetMarkerColor(2);
    l5->AddEntry(exitRad, legendList1[0], "lp");
    
    exitRad1->SetMarkerStyle(25);
    exitRad1->SetMarkerColor(2);
    l5->AddEntry(exitRad1, legendList1[4], "lp");
    
    exitWin->SetMarkerStyle(4);
    exitWin->SetMarkerColor(3);
    l5->AddEntry(exitWin, legendList1[1], "lp");
    
    exitWin1->SetMarkerStyle(25);
    exitWin1->SetMarkerColor(3);
    l5->AddEntry(exitWin1, legendList1[5], "lp");
    
    exitCath->SetMarkerStyle(4);
    exitCath->SetMarkerColor(4);
    l5->AddEntry(exitCath, legendList1[2], "lp");
    
    exitCath1->SetMarkerStyle(25);
    exitCath1->SetMarkerColor(4);
    l5->AddEntry(exitCath1, legendList1[6], "lp");
    
    exitDet->SetMarkerStyle(4);
    exitDet->SetMarkerColor(6);
    l5->AddEntry(exitDet, legendList1[3], "lp");
    
    exitDet1->SetMarkerStyle(25);
    exitDet1->SetMarkerColor(6);
    l5->AddEntry(exitDet1, legendList1[7], "lp");
    
    exitRad->Draw();
	exitWin->Draw("same");
	exitCath->Draw("same");
	exitDet->Draw("same");
    
    exitRad1->Draw("same");
	exitWin1->Draw("same");
	exitCath1->Draw("same");
	exitDet1->Draw("same");
	
	l5->SetTextSize(0.025);
	l5->SetHeader("#gamma Energy", "C");
	l5->SetNColumns(2);
  	l5->Draw();
	
	//=============================================
	
	c3->cd(2);
    exitRad2->SetTitle("KrCO2");
    exitRad2->SetMarkerStyle(4);
    exitRad2->SetMarkerColor(2);
    l6->AddEntry(exitRad2, legendList1[0], "lp");
    
    exitRad3->SetMarkerStyle(25);
    exitRad3->SetMarkerColor(2);
    l6->AddEntry(exitRad3, legendList1[4], "lp");
    
    exitWin2->SetMarkerStyle(4);
    exitWin2->SetMarkerColor(3);
    l6->AddEntry(exitWin2, legendList1[1], "lp");
    
    exitWin3->SetMarkerStyle(25);
    exitWin3->SetMarkerColor(3);
    l6->AddEntry(exitWin3, legendList1[5], "lp");
    
    exitCath2->SetMarkerStyle(4);
    exitCath2->SetMarkerColor(4);
    l6->AddEntry(exitCath2, legendList1[2], "lp");
    
    exitCath3->SetMarkerStyle(25);
    exitCath3->SetMarkerColor(4);
    l6->AddEntry(exitCath3, legendList1[6], "lp");
    
    exitDet2->SetMarkerStyle(4);
    exitDet2->SetMarkerColor(6);
    l6->AddEntry(exitDet2, legendList1[3], "lp");
    
    exitDet3->SetMarkerStyle(25);
    exitDet3->SetMarkerColor(6);
    l6->AddEntry(exitDet3, legendList1[7], "lp");
    
    exitRad2->Draw();
	exitWin2->Draw("same");
	exitCath2->Draw("same");
	exitDet2->Draw("same");
    exitRad3->Draw("same");
	exitWin3->Draw("same");
	exitCath3->Draw("same");
	exitDet3->Draw("same");
	
	l6->SetTextSize(0.025);
	l6->SetHeader("#gamma Energy", "C");
	l6->SetNColumns(2);
  	l6->Draw();
	
	c3->SaveAs("lgt_simOptionCompare_scaledMerged.png");
    
    
    //==================================================
	
	TCanvas *c4 = new TCanvas("c4","XeCO2", 1400, 1000);
	c4->Divide(2,2);
    
    c4->cd(1);
    exitRad->SetTitle("Exit Radiator, XeCO2");
    l7->AddEntry(exitRad, legendList2[0], "lp");
    l7->AddEntry(exitRad1, legendList2[1], "lp");
    exitRad->Draw();
	exitRad1->Draw("same");
	l7->SetTextSize(0.025);
	l7->SetHeader("#gamma Energy", "C");
  	l7->Draw();
	
    c4->cd(2);
    exitWin->SetTitle("Exit Window, XeCO2");
    l8->AddEntry(exitWin, legendList2[0], "lp");
    l8->AddEntry(exitWin1, legendList2[1], "lp");
    exitWin->Draw();
	exitWin1->Draw("same");
	l8->SetTextSize(0.025);
	l8->SetHeader("#gamma Energy", "C");
  	l8->Draw();
    
	c4->cd(3);
    exitCath->SetTitle("Exit Cathode, XeCO2");
    l9->AddEntry(exitCath, legendList2[0], "lp");
    l9->AddEntry(exitCath1, legendList2[1], "lp");
    exitCath->Draw();
	exitCath1->Draw("same");
	l9->SetTextSize(0.025);
	l9->SetHeader("#gamma Energy", "C");
  	l9->Draw();
	
	c4->cd(4);
    exitDet->SetTitle("Exit Drift Gap, XeCO2");
    l10->AddEntry(exitDet, legendList2[0], "lp");
    l10->AddEntry(exitDet1, legendList2[1], "lp");
    exitDet->Draw();
	exitDet1->Draw("same");
	l10->SetTextSize(0.025);
	l10->SetHeader("#gamma Energy", "C");
  	l10->Draw();
	
	c4->SaveAs("lgt_simOptionCompare_scaledMergedXe.png");
	
	//===========================================
	
	TCanvas *c5 = new TCanvas("c5","KrCO2", 1400, 1000);
	c5->Divide(2,2);
    
    c5->cd(1);
    exitRad2->SetTitle("Exit Radiator, KrCO2");
    l11->AddEntry(exitRad2, legendList2[0], "lp");
    l11->AddEntry(exitRad3, legendList2[1], "lp");
    exitRad2->Draw();
	exitRad3->Draw("same");
	l11->SetTextSize(0.025);
	l11->SetHeader("#gamma Energy", "C");
  	l11->Draw();
	
    c5->cd(2);
    exitWin2->SetTitle("Exit Window, KrCO2");
    l12->AddEntry(exitWin2, legendList2[0], "lp");
    l12->AddEntry(exitWin3, legendList2[1], "lp");
    exitWin2->Draw();
	exitWin3->Draw("same");
	l12->SetTextSize(0.025);
	l12->SetHeader("#gamma Energy", "C");
  	l12->Draw();
    
	c5->cd(3);
    exitCath2->SetTitle("Exit Cathode, KrCO2");
    l13->AddEntry(exitCath2, legendList2[0], "lp");
    l13->AddEntry(exitCath3, legendList2[1], "lp");
    exitCath2->Draw();
	exitCath3->Draw("same");
	l13->SetTextSize(0.025);
	l13->SetHeader("#gamma Energy", "C");
  	l13->Draw();
	
	c5->cd(4);
    exitDet2->SetTitle("Exit Drift Gap, KrCO2");
    l14->AddEntry(exitDet2, legendList2[0], "lp");
    l14->AddEntry(exitDet3, legendList2[1], "lp");
    exitDet2->Draw();
	exitDet3->Draw("same");
	l14->SetTextSize(0.025);
	l14->SetHeader("#gamma Energy", "C");
  	l14->Draw();
	
	c5->SaveAs("lgt_simOptionCompare_scaledMergedKr.png");
	
	
}