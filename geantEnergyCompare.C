#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void geantEnergyCompare() {
	
	TString legendList[] = {"Exit Radiator","Exit Window","Exit Dead Xe","Exit Kapton Layer","Exit Cathode","Exit Drift Area"};
	TLegend *l1 = new TLegend(0.47, 0.58, 0.97, 0.9);
	TLegend *l2 = new TLegend(0.47, 0.58, 0.97, 0.9);
	TLegend *l3 = new TLegend(0.47, 0.58, 0.97, 0.9);
	TLegend *l4 = new TLegend(0.47, 0.58, 0.97, 0.9);
	TLegend *l1d = new TLegend(0.55, 0.43, 0.9, 0.9);
	
	TCanvas *c1 = new TCanvas("c1","150K e- with 20cm transparentR XTR, XeCO2 90:10", 2000, 1200);
	gStyle->SetOptStat(00000);
	gStyle->SetTitleFontSize(0.08);
	c1->Divide(3,2);
	
	//=======================================
	//Quarter-Scale GEM-TRD Xe:CO2 90:10, 1.5GeV
	
	TFile *file0 = TFile::Open("largeGemSim/transparentR/fdc15_e-1500MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root");
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
    exitRad->SetTitle("1.5 GeV e^{-}");
    exitRad->SetMaximum(22500);
    exitRad->Draw();
	exitCath->Draw("same");
	exitDet->Draw("same");
	l1->SetHeader("#gamma Spectrum", "C");
	l1->SetTextSize(0.055);
	gPad->RedrawAxis();
  	l1->Draw();
	
	//=======================================
	//Quarter-Scale GEM-TRD Xe:CO2 90:10, 3GeV
	
	TFile *file2 = TFile::Open("largeGemSim/transparentR/fdc15_e-3000MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root");
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
    exitRad1->SetTitle("3 GeV e^{-}");
    exitRad1->SetMaximum(22500);
    exitRad1->Draw();
	exitCath1->Draw("same");
	exitDet1->Draw("same");
	l3->SetHeader("#gamma Spectrum", "C");
	l3->SetTextSize(0.055);
	gPad->RedrawAxis();
  	l3->Draw();
  	
	//==================================================
	//Quarter-Scale GEM-TRD Xe:CO2 90:10, 6GeV
	
	TFile *file3 = TFile::Open("largeGemSim/transparentR/fdc15_e-6000MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root");
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
    exitRad2->SetTitle("6 GeV e^{-}");
    exitRad2->SetMaximum(22500);
    exitRad2->Draw();
	exitCath2->Draw("same");
	exitDet2->Draw("same");
	l2->SetHeader("#gamma Spectrum", "C");
	l2->SetTextSize(0.055);
	gPad->RedrawAxis();
  	l2->Draw();
  	
  	//==================================================
	//Quarter-Scale GEM-TRD Xe:CO2 90:10, 10GeV
  	
  	TFile *file4 = TFile::Open("largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root");
	if (!file4 || file4->IsZombie()) {
      std::cerr << "Error: Could not open file " << file4 << std::endl;
    }
    
	TObject *obj40 = file4->Get("hist31");
      TH1 *exitRad4 = (TH1*)obj40;
      exitRad4->SetLineColor(2);
      exitRad4->SetLineWidth(2);
      exitRad4->SetDirectory(0);
      //l2->AddEntry(exitRad2, legendList[0], "l");
      
    TObject *obj41 = file4->Get("hist33");
      TH1 *exitCath4 = (TH1*)obj41;
      exitCath4->SetLineColor(4);
      exitCath4->SetLineStyle(9);
      exitCath4->SetLineWidth(2);
      exitCath4->SetFillColor(4);
      exitCath4->SetFillStyle(3003);
      exitCath4->SetDirectory(0);
      //l2->AddEntry(exitCath2, legendList[4], "l");
    
    TObject *obj42 = file4->Get("hist26");
      TH1 *exitDet4 = (TH1*)obj42;
      exitDet4->SetLineColor(1);
      exitDet4->SetLineStyle(4);
      exitDet4->SetLineWidth(2);
      exitDet4->SetFillColor(10);
      exitDet4->SetFillStyle(1001);
      exitDet4->SetDirectory(0);
      //l2->AddEntry(exitDet2, legendList[5], "l");
    
	gStyle->SetOptStat(00000);
	c1->cd(4);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
    exitRad4->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad4->GetXaxis()->SetLabelSize(0.043);
    exitRad4->GetXaxis()->SetTitleSize(0.05);
    exitRad4->GetYaxis()->SetTitle("Count");
    exitRad4->GetYaxis()->SetLabelSize(0.043);
    exitRad4->GetYaxis()->SetTitleSize(0.05);
    exitRad4->GetYaxis()->SetTitleOffset(1.65);
    exitRad4->GetYaxis()->SetNdivisions(505);
    exitRad4->SetTitle("10 GeV e^{-}");
    exitRad4->SetMaximum(22500);
    exitRad4->Draw();
	exitCath4->Draw("same");
	exitDet4->Draw("same");
	//l2->SetHeader("#gamma Spectrum", "C");
	//l2->SetTextSize(0.055);
	gPad->RedrawAxis();
  	l2->Draw();
  	
  	//==================================================
	//Quarter-Scale GEM-TRD Xe:CO2 90:10, 20GeV
  	
  	TFile *file5 = TFile::Open("largeGemSim/transparentR/fdc15_e-20000MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root");
	if (!file5 || file5->IsZombie()) {
      std::cerr << "Error: Could not open file " << file5 << std::endl;
    }
    
	TObject *obj50 = file5->Get("hist31");
      TH1 *exitRad5 = (TH1*)obj50;
      exitRad5->SetLineColor(2);
      exitRad5->SetLineWidth(2);
      exitRad5->SetDirectory(0);
      //l2->AddEntry(exitRad2, legendList[0], "l");
      
    TObject *obj51 = file5->Get("hist33");
      TH1 *exitCath5 = (TH1*)obj51;
      exitCath5->SetLineColor(4);
      exitCath5->SetLineStyle(9);
      exitCath5->SetLineWidth(2);
      exitCath5->SetFillColor(4);
      exitCath5->SetFillStyle(3003);
      exitCath5->SetDirectory(0);
      //l2->AddEntry(exitCath2, legendList[4], "l");
    
    TObject *obj52 = file5->Get("hist26");
      TH1 *exitDet5 = (TH1*)obj52;
      exitDet5->SetLineColor(1);
      exitDet5->SetLineStyle(4);
      exitDet5->SetLineWidth(2);
      exitDet5->SetFillColor(10);
      exitDet5->SetFillStyle(1001);
      exitDet5->SetDirectory(0);
      //l2->AddEntry(exitDet2, legendList[5], "l");
    
	gStyle->SetOptStat(00000);
	c1->cd(5);
	gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
    exitRad5->GetXaxis()->SetTitle("TR Photon Energy [keV]");
    exitRad5->GetXaxis()->SetLabelSize(0.043);
    exitRad5->GetXaxis()->SetTitleSize(0.05);
    exitRad5->GetYaxis()->SetTitle("Count");
    exitRad5->GetYaxis()->SetLabelSize(0.043);
    exitRad5->GetYaxis()->SetTitleSize(0.05);
    exitRad5->GetYaxis()->SetTitleOffset(1.65);
    exitRad5->GetYaxis()->SetNdivisions(505);
    exitRad5->SetTitle("20 GeV e^{-}");
    exitRad5->SetMaximum(22500);
    exitRad5->Draw();
	exitCath5->Draw("same");
	exitDet5->Draw("same");
	//l2->SetHeader("#gamma Spectrum", "C");
	//l2->SetTextSize(0.055);
	gPad->RedrawAxis();
  	l2->Draw();
  	
	c1->SaveAs("largeGemSim/transparentR/beamEnergyComparison.pdf");
  	
  	
  	//=======================================
  	// Difference Plots
	
	TCanvas *c3 = new TCanvas("c3","Absorbed Spectra", 2000, 1200);
	//c3->Divide(3,1);
	//gStyle->SetOptStat(1111);
	gStyle->SetTitleFontSize(0.055);
	c3->cd();
	//gPad->SetRightMargin(0.03);
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.125);
	
	TH1D *cathodeSubtract1 = new TH1D("cathodeSubtract1","Absorbed Spectrum in Xe:CO_{2} 90:10; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract1->Add(exitCath,exitDet,1,-1);
	cathodeSubtract1->SetDirectory(0);
	cathodeSubtract1->SetMinimum(0);
	cathodeSubtract1->SetMaximum(20000);
	cathodeSubtract1->SetLineWidth(2);
	cathodeSubtract1->SetLineColor(1);
	cathodeSubtract1->SetFillColor(1);
    cathodeSubtract1->SetFillStyle(3006);
    cathodeSubtract1->GetXaxis()->SetLabelSize(0.043);
    cathodeSubtract1->GetXaxis()->SetTitleSize(0.05);
    cathodeSubtract1->GetYaxis()->SetTitle("Count");
    cathodeSubtract1->GetYaxis()->SetLabelSize(0.043);
    cathodeSubtract1->GetYaxis()->SetTitleSize(0.05);
    cathodeSubtract1->GetYaxis()->SetTitleOffset(1.1);
    cathodeSubtract1->GetYaxis()->SetNdivisions(505);
    l1d->AddEntry(cathodeSubtract1,"1.5 GeV e^{-}","lf");
	cathodeSubtract1->Draw();
	
	//c3->cd(2);
	//gPad->SetRightMargin(0.03);
	//gPad->SetLeftMargin(0.15);
	//gPad->SetBottomMargin(0.125);
	TH1D *cathodeSubtract2 = new TH1D("cathodeSubtract2"," ; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract2->Add(exitCath1,exitDet1,1,-1);
	cathodeSubtract2->SetDirectory(0);
	cathodeSubtract2->SetMinimum(0);
	cathodeSubtract2->SetMaximum(20000);
	cathodeSubtract2->SetLineWidth(2);
	cathodeSubtract2->SetLineColor(4);
	cathodeSubtract2->SetFillColor(4);
    cathodeSubtract2->SetFillStyle(3005);
    cathodeSubtract2->GetXaxis()->SetLabelSize(0.043);
    cathodeSubtract2->GetXaxis()->SetTitleSize(0.05);
    cathodeSubtract2->GetYaxis()->SetTitle("Count");
    cathodeSubtract2->GetYaxis()->SetLabelSize(0.043);
    cathodeSubtract2->GetYaxis()->SetTitleSize(0.05);
    cathodeSubtract2->GetYaxis()->SetTitleOffset(1.1);
    cathodeSubtract2->GetYaxis()->SetNdivisions(505);
    l1d->AddEntry(cathodeSubtract2,"3 GeV e^{-}","lf");
	cathodeSubtract2->Draw("same");
	
	//c3->cd(3);
	//gPad->SetRightMargin(0.03);
	//gPad->SetLeftMargin(0.15);
	//gPad->SetBottomMargin(0.125);
	TH1D *cathodeSubtract3 = new TH1D("cathodeSubtract3"," ; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract3->Add(exitCath2,exitDet2,1,-1);
	cathodeSubtract3->SetDirectory(0);
	cathodeSubtract3->SetMinimum(0);
	cathodeSubtract3->SetMaximum(20000);
	cathodeSubtract3->SetLineWidth(2);
	cathodeSubtract3->SetLineColor(3);
	cathodeSubtract3->SetFillColor(3);
    cathodeSubtract3->SetFillStyle(3016);
	cathodeSubtract3->GetXaxis()->SetLabelSize(0.043);
    cathodeSubtract3->GetXaxis()->SetTitleSize(0.05);
    cathodeSubtract3->GetYaxis()->SetTitle("Count");
    cathodeSubtract3->GetYaxis()->SetLabelSize(0.043);
    cathodeSubtract3->GetYaxis()->SetTitleSize(0.05);
    cathodeSubtract3->GetYaxis()->SetTitleOffset(1.1);
    cathodeSubtract3->GetYaxis()->SetNdivisions(505);
    l1d->AddEntry(cathodeSubtract3,"6 GeV e^{-}","lf");
	cathodeSubtract3->Draw("same");
	
	TH1D *cathodeSubtract4 = new TH1D("cathodeSubtract4"," ; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract4->Add(exitCath4,exitDet4,1,-1);
	cathodeSubtract4->SetDirectory(0);
	cathodeSubtract4->SetMinimum(0);
	cathodeSubtract4->SetMaximum(20000);
	cathodeSubtract4->SetLineWidth(2);
	cathodeSubtract4->SetLineColor(6);
	cathodeSubtract4->SetFillColor(6);
    cathodeSubtract4->SetFillStyle(3004);
	cathodeSubtract4->GetXaxis()->SetLabelSize(0.043);
    cathodeSubtract4->GetXaxis()->SetTitleSize(0.05);
    cathodeSubtract4->GetYaxis()->SetTitle("Count");
    cathodeSubtract4->GetYaxis()->SetLabelSize(0.043);
    cathodeSubtract4->GetYaxis()->SetTitleSize(0.05);
    cathodeSubtract4->GetYaxis()->SetTitleOffset(1.1);
    cathodeSubtract4->GetYaxis()->SetNdivisions(505);
    l1d->AddEntry(cathodeSubtract4,"10 GeV e^{-}","lf");
	cathodeSubtract4->Draw("same");
	
	TH1D *cathodeSubtract5 = new TH1D("cathodeSubtract5"," ; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract5->Add(exitCath5,exitDet5,1,-1);
	cathodeSubtract5->SetDirectory(0);
	cathodeSubtract5->SetMinimum(0);
	cathodeSubtract5->SetMaximum(20000);
	cathodeSubtract5->SetLineWidth(2);
	cathodeSubtract5->SetLineColor(2);
	cathodeSubtract5->SetFillColor(2);
    cathodeSubtract5->SetFillStyle(3003);
	cathodeSubtract5->GetXaxis()->SetLabelSize(0.043);
    cathodeSubtract5->GetXaxis()->SetTitleSize(0.05);
    cathodeSubtract5->GetYaxis()->SetTitle("Count");
    cathodeSubtract5->GetYaxis()->SetLabelSize(0.043);
    cathodeSubtract5->GetYaxis()->SetTitleSize(0.05);
    cathodeSubtract5->GetYaxis()->SetTitleOffset(1.1);
    cathodeSubtract5->GetYaxis()->SetNdivisions(505);
    l1d->AddEntry(cathodeSubtract5,"20 GeV e^{-}","lf");
	cathodeSubtract5->Draw("same");
	l1d->SetHeader("Primary Beam Energy","C");
	l1d->Draw();
	
	c3->SaveAs("largeGemSim/transparentR/beamEnergyAbsorbedComparison.pdf");
	
	//=======================================
  	// Ratio Plots
  	
  	TCanvas *c4 = new TCanvas("c4","Absorbed Ratios", 2000, 1200);
	c4->Divide(2,2);
	c4->SetTicks(0,1);
	
	c4->cd(1);
	gPad->SetRightMargin(0.03);
	auto rp1 = new TRatioPlot(cathodeSubtract1, cathodeSubtract5);
	rp1->SetLeftMargin(0.1);
	rp1->SetH1DrawOpt("HIST");
	rp1->SetH2DrawOpt("HIST");
    rp1->Draw();
    rp1->GetLowYaxis()->SetNdivisions(505);
    rp1->GetUpYaxis()->SetNdivisions(505);
    cathodeSubtract1->SetTitle("");
    rp1->GetUpperRefYaxis()->SetLabelSize(0.033);
    rp1->GetUpperRefYaxis()->SetTitleSize(0.04);
    rp1->GetUpperRefYaxis()->SetTitleOffset(1.25);
    rp1->GetUpperRefXaxis()->SetLabelSize(0.035);
    rp1->GetUpperRefXaxis()->SetTitleSize(0.044);
    rp1->GetLowerRefGraph()->SetMinimum(0.25);
   	rp1->GetLowerRefGraph()->SetMaximum(1.5);
   	rp1->GetUpperPad()->cd();
   	TLegend *lr1 = new TLegend(0.6, 0.55, 0.9, 0.9);
   	lr1->SetHeader("'Absorbed' Spectrum", "C");
   	lr1->AddEntry("cathodeSubtract1", "1.5 GeV e^{-}", "lf");
   	lr1->AddEntry("cathodeSubtract5", "20 GeV e^{-}", "lf");
   	lr1->SetTextSize(0.068);
   	lr1->Draw();
   	
   	c4->cd(2);
   	gPad->SetRightMargin(0.03);
	auto rp2 = new TRatioPlot(cathodeSubtract2, cathodeSubtract5);
	rp2->SetLeftMargin(0.1);
	rp2->SetH1DrawOpt("HIST");
	rp2->SetH2DrawOpt("HIST");
    rp2->Draw();
    rp2->GetLowYaxis()->SetNdivisions(505);
    rp2->GetUpYaxis()->SetNdivisions(505);
    cathodeSubtract2->SetTitle("");
    rp2->GetUpperRefYaxis()->SetLabelSize(0.033);
    rp2->GetUpperRefYaxis()->SetTitleSize(0.04);
    rp2->GetUpperRefYaxis()->SetTitleOffset(1.25);
    rp2->GetUpperRefXaxis()->SetLabelSize(0.035);
    rp2->GetUpperRefXaxis()->SetTitleSize(0.044);
    rp2->GetLowerRefGraph()->SetMinimum(0.25);
   	rp2->GetLowerRefGraph()->SetMaximum(1.5);
   	rp2->GetUpperPad()->cd();
   	TLegend *lr2 = new TLegend(0.6, 0.55, 0.9, 0.9);
   	lr2->SetHeader("'Absorbed' Spectrum", "C");
   	lr2->AddEntry("cathodeSubtract2", "3 GeV e^{-}", "lf");
   	lr2->AddEntry("cathodeSubtract5", "20 GeV e^{-}", "lf");
   	lr2->SetTextSize(0.068);
   	lr2->Draw();
   	
   	c4->cd(3);
   	gPad->SetRightMargin(0.03);
	auto rp3 = new TRatioPlot(cathodeSubtract3, cathodeSubtract5);
	rp3->SetLeftMargin(0.1);
	rp3->SetH1DrawOpt("HIST");
	rp3->SetH2DrawOpt("HIST");
    rp3->Draw();
    rp3->GetLowYaxis()->SetNdivisions(505);
    rp3->GetUpYaxis()->SetNdivisions(505);
    cathodeSubtract3->SetTitle("");
    rp3->GetUpperRefYaxis()->SetLabelSize(0.033);
    rp3->GetUpperRefYaxis()->SetTitleSize(0.04);
    rp3->GetUpperRefYaxis()->SetTitleOffset(1.25);
    rp3->GetUpperRefXaxis()->SetLabelSize(0.035);
    rp3->GetUpperRefXaxis()->SetTitleSize(0.044);
    rp3->GetLowerRefGraph()->SetMinimum(0.25);
   	rp3->GetLowerRefGraph()->SetMaximum(1.5);
   	rp3->GetUpperPad()->cd();
   	TLegend *lr3 = new TLegend(0.6, 0.55, 0.9, 0.9);
   	lr3->SetHeader("'Absorbed' Spectrum", "C");
   	lr3->AddEntry("cathodeSubtract3", "6 GeV e^{-}", "lf");
   	lr3->AddEntry("cathodeSubtract5", "20 GeV e^{-}", "lf");
   	lr3->SetTextSize(0.068);
   	lr3->Draw();
   	
   	c4->cd(4);
   	gPad->SetRightMargin(0.03);
	auto rp4 = new TRatioPlot(cathodeSubtract4, cathodeSubtract5);
	rp4->SetLeftMargin(0.1);
	rp4->SetH1DrawOpt("HIST");
	rp4->SetH2DrawOpt("HIST");
    rp4->Draw();
    rp4->GetLowYaxis()->SetNdivisions(505);
    rp4->GetUpYaxis()->SetNdivisions(505);
    cathodeSubtract4->SetTitle("");
    rp4->GetUpperRefYaxis()->SetLabelSize(0.033);
    rp4->GetUpperRefYaxis()->SetTitleSize(0.04);
    rp4->GetUpperRefYaxis()->SetTitleOffset(1.25);
    rp4->GetUpperRefXaxis()->SetLabelSize(0.035);
    rp4->GetUpperRefXaxis()->SetTitleSize(0.044);
    rp4->GetLowerRefGraph()->SetMinimum(0.25);
   	rp4->GetLowerRefGraph()->SetMaximum(1.5);
   	rp4->GetUpperPad()->cd();
   	TLegend *lr4 = new TLegend(0.6, 0.55, 0.9, 0.9);
   	lr4->SetHeader("'Absorbed' Spectrum", "C");
   	lr4->AddEntry("cathodeSubtract4", "10 GeV e^{-}", "lf");
   	lr4->AddEntry("cathodeSubtract5", "20 GeV e^{-}", "lf");
   	lr4->SetTextSize(0.068);
   	lr4->Draw();
   	
	c4->SaveAs("largeGemSim/transparentR/beamEnergyRatios.pdf");
	
}