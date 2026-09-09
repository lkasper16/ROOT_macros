#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void geantGasCompare() {
	
	TString legendList[] = {"Exit Radiator","Exit Window","Exit Dead Xe","Exit Kapton Layer","Exit Cathode","Exit Drift Area"};
	TLegend *l1 = new TLegend(0.47, 0.58, 0.97, 0.9);
	TLegend *l2 = new TLegend(0.47, 0.58, 0.97, 0.9);
	TLegend *l3 = new TLegend(0.47, 0.58, 0.97, 0.9);
	TLegend *l4 = new TLegend(0.47, 0.58, 0.97, 0.9);
	
	//=======================================
	//Quarter-Scale GEM-TRD Xe:CO2 90:10
	
	TFile *file0 = TFile::Open("largeGemSim/transparentR/6GeV/fdc15_e-6000MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root");
	if (!file0 || file0->IsZombie()) {
      std::cerr << "Error: Could not open file " << file0 << std::endl;
    }
    
	TObject *obj1 = file0->Get("hist31");
      TH1 *exitRad = (TH1*)obj1;
      exitRad->SetLineColor(2);
      exitRad->SetLineWidth(2);
      exitRad->SetDirectory(0);
      l1->AddEntry(exitRad, legendList[0], "l");

    TObject *obj3 = file0->Get("hist33");
      TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(4);
      exitCath->SetLineStyle(9);
      exitCath->SetLineWidth(2);
      exitCath->SetFillColor(4);
      exitCath->SetFillStyle(3003);
      exitCath->SetDirectory(0);
      l1->AddEntry(exitCath, legendList[4], "l");
        
    TObject *obj5 = file0->Get("hist26");
      TH1 *exitDet = (TH1*)obj5;
      exitDet->SetLineColor(1);
      exitDet->SetLineStyle(4);
      exitDet->SetLineWidth(2);
      exitDet->SetFillColor(10);
      exitDet->SetFillStyle(1001);
      exitDet->SetDirectory(0);
      l1->AddEntry(exitDet, legendList[5], "l");
    
    TCanvas *c1 = new TCanvas("c1","150K e- with 20cm transparentR XTR, XeCO2 90:10", 2000, 1200);
	gStyle->SetOptStat(00000);
	gStyle->SetTitleFontSize(0.08);
	c1->Divide(3,1);
	c1->cd(1);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
    exitRad->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad->GetXaxis()->SetLabelSize(0.043);
    exitRad->GetXaxis()->SetTitleSize(0.05);
    exitRad->GetYaxis()->SetTitle("Count");
    exitRad->GetYaxis()->SetLabelSize(0.043);
    exitRad->GetYaxis()->SetTitleSize(0.05);
    exitRad->GetYaxis()->SetTitleOffset(1.65);
    exitRad->GetYaxis()->SetNdivisions(505);
    //exitRad->SetTitle("25um Kapton, 400um Xe, 50um Kapton, 0.2um Cr, 21mm Xe");
    exitRad->SetTitle("Xe:CO_{2} 90:10");
    exitRad->SetMaximum(22500);
    exitRad->Draw();
	exitCath->Draw("same");
	exitDet->Draw("same");
	l1->SetHeader("#gamma Spectrum", "C");
	l1->SetTextSize(0.055);
	gPad->RedrawAxis();
  	l1->Draw();
	
	//=======================================
	//Quarter-scale GEM-TRD Kr:CO2 90:10
	
	TFile *file2 = TFile::Open("largeGemSim/transparentR/6GeV/fdc15_e-6000MeV_Kr10CO2_d30:1.5mm_r20cm_m1.root");
	if (!file2 || file2->IsZombie()) {
      std::cerr << "Error: Could not open file " << file2 << std::endl;
    }
	
	TObject *obj11 = file2->Get("hist31");
      TH1 *exitRad1 = (TH1*)obj11;
      exitRad1->SetLineColor(2);
      exitRad1->SetLineWidth(2);
      exitRad1->SetDirectory(0);
      l3->AddEntry(exitRad1, legendList[0], "l");

    TObject *obj15 = file2->Get("hist33");
      TH1 *exitCath1 = (TH1*)obj15;
      exitCath1->SetLineColor(4);
      exitCath1->SetLineStyle(9);
      exitCath1->SetLineWidth(2);
      exitCath1->SetFillColor(4);
      exitCath1->SetFillStyle(3003);
      exitCath1->SetDirectory(0);
      l3->AddEntry(exitCath1, legendList[4], "l");
    
    TObject *obj16 = file2->Get("hist26");
      TH1 *exitDet1 = (TH1*)obj16;
      exitDet1->SetLineColor(1);
      exitDet1->SetLineStyle(4);
      exitDet1->SetLineWidth(2);
      exitDet1->SetFillColor(10);
      exitDet1->SetFillStyle(1001);
      exitDet1->SetDirectory(0);
      l3->AddEntry(exitDet1, legendList[5], "l");
    
	c1->cd(2);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
    exitRad1->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad1->GetXaxis()->SetLabelSize(0.043);
    exitRad1->GetXaxis()->SetTitleSize(0.05);
    exitRad1->GetYaxis()->SetTitle("Count");
    exitRad1->GetYaxis()->SetLabelSize(0.043);
    exitRad1->GetYaxis()->SetTitleSize(0.05);
    exitRad1->GetYaxis()->SetTitleOffset(1.65);
    exitRad1->GetYaxis()->SetNdivisions(505);
    exitRad1->SetTitle("Kr:CO_{2} 90:10");
    exitRad1->SetMaximum(22500);
    exitRad1->Draw();
	exitCath1->Draw("same");
	exitDet1->Draw("same");
	l3->SetHeader("#gamma Spectrum", "C");
	l3->SetTextSize(0.055);
	gPad->RedrawAxis();
  	l3->Draw();
  	
	//==================================================
	//GEM-TRD 2mm Dead Gas Gap
	
	TFile *file3 = TFile::Open("largeGemSim/transparentR/6GeV/fdc15_e-6000MeV_Xe10isoC4H10_d30:1.5mm_r20cm_m1.root");
	if (!file3 || file3->IsZombie()) {
      std::cerr << "Error: Could not open file " << file3 << std::endl;
    }
    
	TObject *obj17 = file3->Get("hist31");
      TH1 *exitRad2 = (TH1*)obj17;
      exitRad2->SetLineColor(2);
      exitRad2->SetLineWidth(2);
      exitRad2->SetDirectory(0);
      l2->AddEntry(exitRad2, legendList[0], "l");
        
    TObject *obj19 = file3->Get("hist33");
      TH1 *exitCath2 = (TH1*)obj19;
      exitCath2->SetLineColor(4);
      exitCath2->SetLineStyle(9);
      exitCath2->SetLineWidth(2);
      exitCath2->SetFillColor(4);
      exitCath2->SetFillStyle(3003);
      exitCath2->SetDirectory(0);
      l2->AddEntry(exitCath2, legendList[4], "l");
    
    TObject *obj20 = file3->Get("hist26");
      TH1 *exitDet2 = (TH1*)obj20;
      exitDet2->SetLineColor(1);
      exitDet2->SetLineStyle(4);
      exitDet2->SetLineWidth(2);
      exitDet2->SetFillColor(10);
      exitDet2->SetFillStyle(1001);
      exitDet2->SetDirectory(0);
      l2->AddEntry(exitDet2, legendList[5], "l");
    
	gStyle->SetOptStat(00000);
	c1->cd(3);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
    exitRad2->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad2->GetXaxis()->SetLabelSize(0.043);
    exitRad2->GetXaxis()->SetTitleSize(0.05);
    exitRad2->GetYaxis()->SetTitle("Count");
    exitRad2->GetYaxis()->SetLabelSize(0.043);
    exitRad2->GetYaxis()->SetTitleSize(0.05);
    exitRad2->GetYaxis()->SetTitleOffset(1.65);
    exitRad2->GetYaxis()->SetNdivisions(505);
   	//exitRad2->SetTitle("25um Mylar, 1mm Xe, 18um Steel, 28mm Xe");
    exitRad2->SetTitle("Xe:C_{4}H_{10} 90:10");
    exitRad2->SetMaximum(22500);
    exitRad2->Draw();
	exitCath2->Draw("same");
	exitDet2->Draw("same");
	l2->SetHeader("#gamma Spectrum", "C");
	l2->SetTextSize(0.055);
	gPad->RedrawAxis();
  	l2->Draw();
  	
	c1->SaveAs("largeGemSim/gasMixtureComparison.pdf");
  	
  	
  	//=======================================
  	// Ratio Plots
	
	TCanvas *c3 = new TCanvas("c3","c3", 2000, 1200);
	c3->Divide(3,1);
	//gStyle->SetOptStat(1111);
	c3->cd(1);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	TH1D *cathodeSubtract1 = new TH1D("cathodeSubtract1","Xe:CO_{2} 90:10 Absorbed Spectrum; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract1->Add(exitCath,exitDet,1,-1);
	cathodeSubtract1->SetDirectory(0);
	cathodeSubtract1->SetMinimum(0);
	cathodeSubtract1->SetMaximum(20000);
	cathodeSubtract1->SetLineWidth(2);
	cathodeSubtract1->SetLineColor(4);
	cathodeSubtract1->SetFillColor(4);
    cathodeSubtract1->SetFillStyle(3003);
    cathodeSubtract1->GetXaxis()->SetLabelSize(0.043);
    cathodeSubtract1->GetXaxis()->SetTitleSize(0.05);
    cathodeSubtract1->GetYaxis()->SetTitle("Count");
    cathodeSubtract1->GetYaxis()->SetLabelSize(0.043);
    cathodeSubtract1->GetYaxis()->SetTitleSize(0.05);
    cathodeSubtract1->GetYaxis()->SetTitleOffset(1.65);
	cathodeSubtract1->Draw();
	
	c3->cd(2);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	TH1D *cathodeSubtract2 = new TH1D("cathodeSubtract2","Kr:CO_{2} 90:10 Absorbed Spectrum; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract2->Add(exitCath1,exitDet1,1,-1);
	cathodeSubtract2->SetDirectory(0);
	cathodeSubtract2->SetMinimum(0);
	cathodeSubtract2->SetMaximum(20000);
	cathodeSubtract2->SetLineWidth(2);
	cathodeSubtract2->SetLineColor(4);
	cathodeSubtract2->SetFillColor(4);
    cathodeSubtract2->SetFillStyle(3003);
    cathodeSubtract2->GetXaxis()->SetLabelSize(0.043);
    cathodeSubtract2->GetXaxis()->SetTitleSize(0.05);
    cathodeSubtract2->GetYaxis()->SetTitle("Count");
    cathodeSubtract2->GetYaxis()->SetLabelSize(0.043);
    cathodeSubtract2->GetYaxis()->SetTitleSize(0.05);
    cathodeSubtract2->GetYaxis()->SetTitleOffset(1.65);
	cathodeSubtract2->Draw();
	
	c3->cd(3);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	TH1D *cathodeSubtract3 = new TH1D("cathodeSubtract3","Xe:C_{4}H_{10} 90:10 Absorbed Spectrum; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract3->Add(exitCath2,exitDet2,1,-1);
	cathodeSubtract3->SetDirectory(0);
	cathodeSubtract3->SetMinimum(0);
	cathodeSubtract3->SetMaximum(20000);
	cathodeSubtract3->SetLineWidth(2);
	cathodeSubtract3->SetLineColor(4);
	cathodeSubtract3->SetFillColor(4);
    cathodeSubtract3->SetFillStyle(3003);
	cathodeSubtract3->GetXaxis()->SetLabelSize(0.043);
    cathodeSubtract3->GetXaxis()->SetTitleSize(0.05);
    cathodeSubtract3->GetYaxis()->SetTitle("Count");
    cathodeSubtract3->GetYaxis()->SetLabelSize(0.043);
    cathodeSubtract3->GetYaxis()->SetTitleSize(0.05);
    cathodeSubtract3->GetYaxis()->SetTitleOffset(1.65);
	cathodeSubtract3->Draw();
	
	c3->SaveAs("largeGemSim/gasMixtureAbsorbedComparison.pdf");
	
	//=======================================
  	// Ratio Plots
  	
  	TCanvas *c4 = new TCanvas("c4","c4", 2000, 1200);
	c4->Divide(2,1);
	c4->SetTicks(0,1);
	
	c4->cd(1);
	auto rp1 = new TRatioPlot(cathodeSubtract1, cathodeSubtract3);
	//rp1->SetRightMargin(0.09);
	rp1->SetLeftMargin(0.13);
	cathodeSubtract1->SetLineColor(96);
	cathodeSubtract1->SetFillColor(96);
    cathodeSubtract1->SetFillStyle(3004);
	cathodeSubtract3->SetFillStyle(3005);
	rp1->SetH1DrawOpt("HIST");
	rp1->SetH2DrawOpt("HIST");
    rp1->Draw();
    rp1->GetLowYaxis()->SetNdivisions(505);
    cathodeSubtract1->SetTitle("");
    rp1->GetUpperRefYaxis()->SetLabelSize(0.03);
    rp1->GetUpperRefYaxis()->SetTitleSize(0.038);
    rp1->GetUpperRefYaxis()->SetTitleOffset(1.85);
    rp1->GetLowerRefGraph()->SetMinimum(0.45);
   	rp1->GetLowerRefGraph()->SetMaximum(1.55);
   	rp1->GetUpperPad()->cd();
   	TLegend *lr1 = new TLegend(0.5, 0.6, 0.9, 0.9);
   	lr1->SetHeader("'Absorbed' Spectrum", "C");
   	lr1->AddEntry("cathodeSubtract1", "Xe:CO_{2}", "lf");
   	lr1->AddEntry("cathodeSubtract3", "Xe:C_{4}H_{10}", "lf");
   	lr1->SetTextSize(0.045);
   	lr1->Draw();
   	
   	c4->cd(2);
	auto rp2 = new TRatioPlot(cathodeSubtract2, cathodeSubtract3);
	//rp2->SetRightMargin(0.09);
	rp2->SetLeftMargin(0.13);
	cathodeSubtract2->SetLineColor(6);
	cathodeSubtract2->SetFillColor(6);
    cathodeSubtract2->SetFillStyle(3004);
	cathodeSubtract3->SetFillStyle(3005);
	rp2->SetH1DrawOpt("HIST");
	rp2->SetH2DrawOpt("HIST");
    rp2->Draw();
    rp2->GetLowYaxis()->SetNdivisions(505);
    cathodeSubtract2->SetTitle("");
    rp2->GetUpperRefYaxis()->SetLabelSize(0.03);
    rp2->GetUpperRefYaxis()->SetTitleSize(0.038);
    rp2->GetUpperRefYaxis()->SetTitleOffset(1.85);
    rp2->GetLowerRefGraph()->SetMinimum(-0.);
   	rp2->GetLowerRefGraph()->SetMaximum(1.75);
   	rp2->GetUpperPad()->cd();
   	TLegend *lr2 = new TLegend(0.5, 0.6, 0.9, 0.9);
   	lr2->SetHeader("'Absorbed' Spectrum", "C");
   	lr2->AddEntry("cathodeSubtract2", "Kr:CO_{2}", "lf");
   	lr2->AddEntry("cathodeSubtract3", "Xe:C_{4}H_{10}", "lf");
   	lr2->SetTextSize(0.045);
   	lr2->Draw();
   	
	c4->SaveAs("largeGemSim/gasMixtureRatios.pdf");
	
}