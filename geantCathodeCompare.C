#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>

void geantCathodeCompare() {
	
	//TString legendList[] = {"Exit Radiator","Exit Kapton Window","Exit Dead Xe","Exit Kapton Base Layer","Exit Cathode","Exit Xe Drift Gap"};
	TString legendList[] = {"Exit Radiator","Exit Kapton Window","Exit Cathode","Exit Xe Drift Gap"};
	TLegend *l1 = new TLegend(0.6, 0.75, 0.9, 0.9);
	//TLegend *l2 = new TLegend(0.6, 0.75, 0.9, 0.9);
	//TLegend *l3 = new TLegend(0.6, 0.75, 0.9, 0.9);
  TLegend *l4 = new TLegend(0.6, 0.75, 0.9, 0.9);
  //TLegend *l5 = new TLegend(0.6, 0.75, 0.9, 0.9);
  //TLegend *l6 = new TLegend(0.6, 0.75, 0.9, 0.9);
	TLegend *l7 = new TLegend(0.6, 0.75, 0.9, 0.9);
  //TLegend *l8 = new TLegend(0.6, 0.75, 0.9, 0.9);
  //TLegend *l9 = new TLegend(0.6, 0.75, 0.9, 0.9);
  
	//=======================================
	//LGT Construction w Cu as Cathode
	
  TCanvas *c1 = new TCanvas("c1","125K e- with 20cm Reg. Rad, XeCO2 90:10, Cu Cathodes", 1600, 1000);
  gStyle->SetOptStat(00000);
  c1->Divide(4,1);
  
	TFile *file0 = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Cu.root");
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
      l1->AddEntry(exitCath, legendList[2], "l");
        
    TObject *obj4 = file0->Get("hist26");
      TH1 *exitDet = (TH1*)obj4;
      exitDet->SetLineColor(6);
      exitDet->SetLineWidth(2);
      exitDet->SetDirectory(0);
      l1->AddEntry(exitDet, legendList[3], "l");
    
	c1->cd(1);
  exitRad->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad->GetYaxis()->SetTitle("Count");
  exitRad->SetTitle("50um Kapton, 0.1um Cu Cat, 30mm Xe");
  exitRad->Draw();
	exitWin->Draw("same");
	exitCath->Draw("same");
	exitDet->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  l1->SetTextSize(0.027);
	l1->SetHeader("#gamma Energy", "C");
  l1->Draw();
	
	
	TFile *file1 = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Cu.root");
	if (!file1 || file1->IsZombie()) {
      std::cerr << "Error: Could not open file " << file1 << std::endl;
  }
    
	TObject *obj5 = file1->Get("hist31");
      TH1 *exitRad1 = (TH1*)obj5;
      exitRad1->SetLineColor(2);
      exitRad1->SetLineWidth(2);
      exitRad1->SetDirectory(0);
      //l2->AddEntry(exitRad1, legendList[0], "l");
		
	TObject *obj6 = file1->Get("hist32");
      TH1 *exitWin1 = (TH1*)obj6;
      exitWin1->SetLineColor(209);
      exitWin1->SetLineWidth(2);
      exitWin1->SetDirectory(0);
      //l2->AddEntry(exitWin1, legendList[1], "l");
        
    TObject *obj7 = file1->Get("hist33");
      TH1 *exitCath1 = (TH1*)obj7;
      exitCath1->SetLineColor(4);
      exitCath1->SetLineWidth(2);
      exitCath1->SetDirectory(0);
      //l2->AddEntry(exitCath1, legendList[2], "l");
    
    TObject *obj8 = file1->Get("hist26");
      TH1 *exitDet1 = (TH1*)obj8;
      exitDet1->SetLineColor(6);
      exitDet1->SetLineWidth(2);
      exitDet1->SetDirectory(0);
      //l2->AddEntry(exitDet1, legendList[3], "l");
    
	c1->cd(2);
  exitRad1->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad1->GetYaxis()->SetTitle("Count");
  exitRad1->SetTitle("50um Kapton, 0.5um Cu Cat, 30mm Xe");
  exitRad1->Draw();
	exitWin1->Draw("same");
	exitCath1->Draw("same");
	exitDet1->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
	//l2->SetHeader("#gamma Energy", "C");
  l1->Draw();
	
  
  TFile *file2 = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Cu.root");
  if (!file2 || file2->IsZombie()) {
      std::cerr << "Error: Could not open file " << file2 << std::endl;
  }

  TObject *obj9 = file2->Get("hist31");
      TH1 *exitRad2 = (TH1*)obj9;
      exitRad2->SetLineColor(2);
      exitRad2->SetLineWidth(2);
      exitRad2->SetDirectory(0);
      //l3->AddEntry(exitRad2, legendList[0], "l");

  TObject *obj10 = file2->Get("hist32");
      TH1 *exitWin2 = (TH1*)obj10;
      exitWin2->SetLineColor(209);
      exitWin2->SetLineWidth(2);
      exitWin2->SetDirectory(0);
      //l3->AddEntry(exitWin2, legendList[1], "l");
    
  TObject *obj11 = file2->Get("hist33");
      TH1 *exitCath2 = (TH1*)obj11;
      exitCath2->SetLineColor(4);
      exitCath2->SetLineWidth(2);
      exitCath2->SetDirectory(0);
      //l3->AddEntry(exitCath2, legendList[2], "l");

    TObject *obj12 = file2->Get("hist26");
      TH1 *exitDet2 = (TH1*)obj12;
      exitDet2->SetLineColor(6);
      exitDet2->SetLineWidth(2);
      exitDet2->SetDirectory(0);
      //l3->AddEntry(exitDet2, legendList[3], "l");

  c1->cd(3);
  exitRad2->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad2->GetYaxis()->SetTitle("Count");
  exitRad2->SetTitle("50um Kapton, 1.0um Cu Cat, 30mm Xe");
  exitRad2->Draw();
  exitWin2->Draw("same");
  exitCath2->Draw("same");
  exitDet2->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  //l3->SetHeader("#gamma Energy", "C");
  l1->Draw();
  
  
  TFile *file02 = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Cu.root");
  if (!file02 || file02->IsZombie()) {
      std::cerr << "Error: Could not open file " << file02 << std::endl;
  }

  TObject *obj09 = file02->Get("hist31");
      TH1 *exitRad02 = (TH1*)obj09;
      exitRad02->SetLineColor(2);
      exitRad02->SetLineWidth(2);
      exitRad02->SetDirectory(0);
      //l3->AddEntry(exitRad02, legendList[0], "l");

  TObject *obj010 = file02->Get("hist32");
      TH1 *exitWin02 = (TH1*)obj010;
      exitWin02->SetLineColor(209);
      exitWin02->SetLineWidth(2);
      exitWin02->SetDirectory(0);
      //l3->AddEntry(exitWin02, legendList[1], "l");

  TObject *obj011 = file02->Get("hist33");
      TH1 *exitCath02 = (TH1*)obj011;
      exitCath02->SetLineColor(4);
      exitCath02->SetLineWidth(2);
      exitCath02->SetDirectory(0);
      //l3->AddEntry(exitCath02, legendList[2], "l");

    TObject *obj012 = file02->Get("hist26");
      TH1 *exitDet02 = (TH1*)obj012;
      exitDet02->SetLineColor(6);
      exitDet02->SetLineWidth(2);
      exitDet02->SetDirectory(0);
      //l3->AddEntry(exitDet02, legendList[3], "l");
  
  c1->cd(4);
  exitRad02->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad02->GetYaxis()->SetTitle("Count");
  exitRad02->SetTitle("50um Kapton, 5.0um Cu Cat, 30mm Xe");
  exitRad02->Draw();
  exitWin02->Draw("same");
  exitCath02->Draw("same");
  exitDet02->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  //l3->SetHeader("#gamma Energy", "C");
  l1->Draw();
  
  c1->SaveAs("GEMTRDCuCatCompare.png");

  
  //=================================================
  // LGT Construction with Au as Cathode

  TCanvas *c2 = new TCanvas("c2","125K e- with 20cm Reg. Rad, XeCO2 90:10, Au Cathodes", 1600, 1000);
  gStyle->SetOptStat(00000);
  c2->Divide(4,1);
  c2->SetRightMargin(0.05);
  
  TFile *file0au = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Au.root");
  if (!file0au || file0au->IsZombie()) {
      std::cerr << "Error: Could not open file " << file0au << std::endl;
    }

  TObject *obj1au = file0au->Get("hist31");
      TH1 *exitRadau = (TH1*)obj1au;
      exitRadau->SetLineColor(2);
      exitRadau->SetLineWidth(2);
      exitRadau->SetDirectory(0);
      l4->AddEntry(exitRadau, legendList[0], "l");

  TObject *obj2au = file0au->Get("hist32");
      TH1 *exitWinau = (TH1*)obj2au;
      exitWinau->SetLineColor(209);
      exitWinau->SetLineWidth(2);
      exitWinau->SetDirectory(0);
      l4->AddEntry(exitWinau, legendList[1], "l");
  
  TObject *obj3au = file0au->Get("hist33");
      TH1 *exitCathau = (TH1*)obj3au;
      exitCathau->SetLineColor(4);
      exitCathau->SetLineWidth(2);
      exitCathau->SetDirectory(0);
      l4->AddEntry(exitCathau, legendList[2], "l");

    TObject *obj4au = file0au->Get("hist26");
      TH1 *exitDetau = (TH1*)obj4au;
      exitDetau->SetLineColor(6);
      exitDetau->SetLineWidth(2);
      exitDetau->SetDirectory(0);
      l4->AddEntry(exitDetau, legendList[3], "l");

  c2->cd(1);
  exitRadau->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRadau->GetYaxis()->SetTitle("Count");
  exitRadau->SetTitle("50um Kapton, 0.1um Au Cat, 30mm Xe");
  exitRadau->Draw();
  exitWinau->Draw("same");
  exitCathau->Draw("same");
  exitDetau->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  l4->SetTextSize(0.027);
  l4->SetHeader("#gamma Energy", "C");
  l4->Draw();
  
  
  TFile *file1au = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Au.root");
  if (!file1au || file1au->IsZombie()) {
      std::cerr << "Error: Could not open file " << file1au << std::endl;
  }

  TObject *obj5au = file1au->Get("hist31");
      TH1 *exitRad1au = (TH1*)obj5au;
      exitRad1au->SetLineColor(2);
      exitRad1au->SetLineWidth(2);
      exitRad1au->SetDirectory(0);
      //l5->AddEntry(exitRad1au, legendList[0], "l");

  TObject *obj6au = file1au->Get("hist32");
      TH1 *exitWin1au = (TH1*)obj6;
      exitWin1au->SetLineColor(209);
      exitWin1au->SetLineWidth(2);
      exitWin1au->SetDirectory(0);
      //l5->AddEntry(exitWin1au, legendList[1], "l");

    TObject *obj7au = file1au->Get("hist33");
      TH1 *exitCath1au = (TH1*)obj7au;
      exitCath1au->SetLineColor(4);
      exitCath1au->SetLineWidth(2);
      exitCath1au->SetDirectory(0);
      //l5->AddEntry(exitCath1au, legendList[2], "l");
      
    TObject *obj8au = file1au->Get("hist26");
      TH1 *exitDet1au = (TH1*)obj8au;
      exitDet1au->SetLineColor(6);
      exitDet1au->SetLineWidth(2);
      exitDet1au->SetDirectory(0);
      //l5->AddEntry(exitDet1au, legendList[3], "l");

  c2->cd(2);
  exitRad1au->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad1au->GetYaxis()->SetTitle("Count");
  exitRad1au->SetTitle("50um Kapton, 0.5um Au Cat, 30mm Xe");
  exitRad1au->Draw();
  exitWin1au->Draw("same");
  exitCath1au->Draw("same");
  exitDet1au->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  //l5->SetHeader("#gamma Energy", "C");
  l4->Draw();


  TFile *file2au = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Au.root");
  if (!file2au || file2au->IsZombie()) {
      std::cerr << "Error: Could not open file " << file2au << std::endl;
  }
  
  TObject *obj9au = file2au->Get("hist31");
      TH1 *exitRad2au = (TH1*)obj9au;
      exitRad2au->SetLineColor(2);
      exitRad2au->SetLineWidth(2);
      exitRad2au->SetDirectory(0);
      //l6->AddEntry(exitRad2au, legendList[0], "l");

  TObject *obj10au = file2au->Get("hist32");
      TH1 *exitWin2au = (TH1*)obj10au;
      exitWin2au->SetLineColor(209);
      exitWin2au->SetLineWidth(2);
      exitWin2au->SetDirectory(0);
      //l6->AddEntry(exitWin2au, legendList[1], "l");

  TObject *obj11au = file2au->Get("hist33");
      TH1 *exitCath2au = (TH1*)obj11au;
      exitCath2au->SetLineColor(4);
      exitCath2au->SetLineWidth(2);
      exitCath2au->SetDirectory(0);
      //l6->AddEntry(exitCath2au, legendList[2], "l");

    TObject *obj12au = file2au->Get("hist26");
      TH1 *exitDet2au = (TH1*)obj12au;
      exitDet2au->SetLineColor(6);
      exitDet2au->SetLineWidth(2);
      exitDet2au->SetDirectory(0);
      //l6->AddEntry(exitDet2au, legendList[3], "l");
    
  c2->cd(3);
  exitRad2au->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad2au->GetYaxis()->SetTitle("Count");
  exitRad2au->SetTitle("50um Kapton, 1.0um Au Cat, 30mm Xe");
  exitRad2au->Draw();
  exitWin2au->Draw("same");
  exitCath2au->Draw("same");
  exitDet2au->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  //l6->SetHeader("#gamma Energy", "C");
  l4->Draw();
  
  TFile *file02au = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Au.root");
  if (!file02au || file02au->IsZombie()) {
      std::cerr << "Error: Could not open file " << file02au << std::endl;
  }
  
  TObject *obj09au = file02au->Get("hist31");
      TH1 *exitRad02au = (TH1*)obj09au;
      exitRad02au->SetLineColor(2);
      exitRad02au->SetLineWidth(2);
      exitRad02au->SetDirectory(0);
      //l6->AddEntry(exitRad02au, legendList[0], "l");

  TObject *obj010au = file02au->Get("hist32");
      TH1 *exitWin02au = (TH1*)obj010au;
      exitWin02au->SetLineColor(209);
      exitWin02au->SetLineWidth(2);
      exitWin02au->SetDirectory(0);
      //l6->AddEntry(exitWin02au, legendList[1], "l");

  TObject *obj011au = file02au->Get("hist33");
      TH1 *exitCath02au = (TH1*)obj011au;
      exitCath02au->SetLineColor(4);
      exitCath02au->SetLineWidth(2);
      exitCath02au->SetDirectory(0);
      //l6->AddEntry(exitCath02au, legendList[2], "l");

    TObject *obj012au = file02au->Get("hist26");
      TH1 *exitDet02au = (TH1*)obj012au;
      exitDet02au->SetLineColor(6);
      exitDet02au->SetLineWidth(2);
      exitDet02au->SetDirectory(0);
    //l6->AddEntry(exitDet02au, legendList[3], "l");

  c2->cd(4);
  exitRad02au->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad02au->GetYaxis()->SetTitle("Count");
  exitRad02au->SetTitle("50um Kapton, 5.0um Au Cat, 30mm Xe");
  exitRad02au->Draw();
  exitWin02au->Draw("same");
  exitCath02au->Draw("same");
  exitDet02au->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  //l6->SetHeader("#gamma Energy", "C");
  l4->Draw();
  
  c2->SaveAs("GEMTRDAuCatCompare.png");
  
  
  //=================================================
  // LGT Construction with Al as Cathode

  TCanvas *c3 = new TCanvas("c3","125K e- with 20cm Reg. Rad, XeCO2 90:10, Al Cathodes", 1600, 1000);
  gStyle->SetOptStat(00000);
  c3->Divide(4,1);
  c3->SetRightMargin(0.05);
  
  TFile *file0al = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al.root");
  if (!file0al || file0al->IsZombie()) {
      std::cerr << "Error: Could not open file " << file0al << std::endl;
    }

  TObject *obj1al = file0al->Get("hist31");
      TH1 *exitRadal = (TH1*)obj1al;
      exitRadal->SetLineColor(2);
      exitRadal->SetLineWidth(2);
      exitRadal->SetDirectory(0);
      l7->AddEntry(exitRadal, legendList[0], "l");
  
  TObject *obj2al = file0al->Get("hist32");
      TH1 *exitWinal = (TH1*)obj2al;
      exitWinal->SetLineColor(209);
      exitWinal->SetLineWidth(2);
      exitWinal->SetDirectory(0);
      l7->AddEntry(exitWinal, legendList[1], "l");
  
  TObject *obj3al = file0al->Get("hist33");
      TH1 *exitCathal = (TH1*)obj3al;
      exitCathal->SetLineColor(4);
      exitCathal->SetLineWidth(2);
      exitCathal->SetDirectory(0);
      l7->AddEntry(exitCathal, legendList[2], "l");

    TObject *obj4al = file0al->Get("hist26");
      TH1 *exitDetal = (TH1*)obj4al;
      exitDetal->SetLineColor(6);
      exitDetal->SetLineWidth(2);
      exitDetal->SetDirectory(0);
      l7->AddEntry(exitDetal, legendList[3], "l");
  
  c3->cd(1);
  exitRadal->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRadal->GetYaxis()->SetTitle("Count");
  exitRadal->SetTitle("50um Kapton, 0.1um Al Cat, 30mm Xe");
  exitRadal->Draw();
  exitWinal->Draw("same");
  exitCathal->Draw("same");
  exitDetal->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  l7->SetTextSize(0.027);
  l7->SetHeader("#gamma Energy", "C");
  l7->Draw();
  
  
  TFile *file1al = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Al.root");
  if (!file1al || file1al->IsZombie()) {
      std::cerr << "Error: Could not open file " << file1al << std::endl;
  }

  TObject *obj5al = file1al->Get("hist31");
      TH1 *exitRad1al = (TH1*)obj5al;
      exitRad1al->SetLineColor(2);
      exitRad1al->SetLineWidth(2);
      exitRad1al->SetDirectory(0);
      //l8->AddEntry(exitRad1al, legendList[0], "l");

  TObject *obj6al = file1al->Get("hist32");
      TH1 *exitWin1al = (TH1*)obj6;
      exitWin1al->SetLineColor(209);
      exitWin1al->SetLineWidth(2);
      exitWin1al->SetDirectory(0);
      //l8->AddEntry(exitWin1al, legendList[1], "l");

    TObject *obj7al = file1al->Get("hist33");
      TH1 *exitCath1al = (TH1*)obj7al;
      exitCath1al->SetLineColor(4);
      exitCath1al->SetLineWidth(2);
      exitCath1al->SetDirectory(0);
      //l8->AddEntry(exitCath1al, legendList[2], "l");
      
    TObject *obj8al = file1al->Get("hist26");
      TH1 *exitDet1al = (TH1*)obj8al;
      exitDet1al->SetLineColor(6);
      exitDet1al->SetLineWidth(2);
      exitDet1al->SetDirectory(0);
      //l8->AddEntry(exitDet1al, legendList[3], "l");

  c3->cd(2);
  exitRad1al->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad1al->GetYaxis()->SetTitle("Count");
  exitRad1al->SetTitle("50um Kapton, 0.5um Al Cat, 30mm Xe");
  exitRad1al->Draw();
  exitWin1al->Draw("same");
  exitCath1al->Draw("same");
  exitDet1al->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  //l8->SetHeader("#gamma Energy", "C");
  l7->Draw();


  TFile *file2al = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al.root");
  if (!file2al || file2al->IsZombie()) {
      std::cerr << "Error: Could not open file " << file2al << std::endl;
  }
  
  TObject *obj9al = file2al->Get("hist31");
      TH1 *exitRad2al = (TH1*)obj9al;
      exitRad2al->SetLineColor(2);
      exitRad2al->SetLineWidth(2);
      exitRad2al->SetDirectory(0);
      //l9->AddEntry(exitRad2al, legendList[0], "l");

  TObject *obj10al = file2al->Get("hist32");
      TH1 *exitWin2al = (TH1*)obj10al;
      exitWin2al->SetLineColor(209);
      exitWin2al->SetLineWidth(2);
      exitWin2al->SetDirectory(0);
      //l9->AddEntry(exitWin2al, legendList[1], "l");

  TObject *obj11al = file2al->Get("hist33");
      TH1 *exitCath2al = (TH1*)obj11al;
      exitCath2al->SetLineColor(4);
      exitCath2al->SetLineWidth(2);
      exitCath2al->SetDirectory(0);
      //l9->AddEntry(exitCath2al, legendList[2], "l");

    TObject *obj12al = file2al->Get("hist26");
      TH1 *exitDet2al = (TH1*)obj12al;
      exitDet2al->SetLineColor(6);
      exitDet2al->SetLineWidth(2);
      exitDet2al->SetDirectory(0);
      //l9->AddEntry(exitDet2al, legendList[3], "l");
    
  c3->cd(3);
  exitRad2al->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad2al->GetYaxis()->SetTitle("Count");
  exitRad2al->SetTitle("50um Kapton, 1.0um Al Cat, 30mm Xe");
  exitRad2al->Draw();
  exitWin2al->Draw("same");
  exitCath2al->Draw("same");
  exitDet2al->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  //l9->SetHeader("#gamma Energy", "C");
  l7->Draw();
  
  TFile *file02al = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Al.root");
  if (!file02al || file02al->IsZombie()) {
      std::cerr << "Error: Could not open file " << file02al << std::endl;
  }
  
  TObject *obj09al = file02al->Get("hist31");
      TH1 *exitRad02al = (TH1*)obj09al;
      exitRad02al->SetLineColor(2);
      exitRad02al->SetLineWidth(2);
      exitRad02al->SetDirectory(0);
      //l9->AddEntry(exitRad02al, legendList[0], "l");

  TObject *obj010al = file02al->Get("hist32");
      TH1 *exitWin02al = (TH1*)obj010al;
      exitWin02al->SetLineColor(209);
      exitWin02al->SetLineWidth(2);
      exitWin02al->SetDirectory(0);
      //l9->AddEntry(exitWin02al, legendList[1], "l");

  TObject *obj011al = file02al->Get("hist33");
      TH1 *exitCath02al = (TH1*)obj011al;
      exitCath02al->SetLineColor(4);
      exitCath02al->SetLineWidth(2);
      exitCath02al->SetDirectory(0);
      //l9->AddEntry(exitCath02al, legendList[2], "l");

    TObject *obj012al = file02al->Get("hist26");
      TH1 *exitDet02al = (TH1*)obj012al;
      exitDet02al->SetLineColor(6);
      exitDet02al->SetLineWidth(2);
      exitDet02al->SetDirectory(0);
      //l9->AddEntry(exitDet02al, legendList[3], "l");

  c3->cd(4);
  exitRad02al->GetXaxis()->SetTitle("TR Photon Energy [keV]");
  exitRad02al->GetYaxis()->SetTitle("Count");
  exitRad02al->SetTitle("50um Kapton, 5.0um Al Cat, 30mm Xe");
  exitRad02al->Draw();
  exitWin02al->Draw("same");
  exitCath02al->Draw("same");
  exitDet02al->Draw("same");
  gPad->SetRightMargin(0.07);
  gPad->SetLeftMargin(0.18);
  //l9->SetHeader("#gamma Energy", "C");
  l7->Draw();
  
  c3->SaveAs("GEMTRDAlCatCompare.png");
  
	//==================================================
	// Ratio Plots
/*	
	TCanvas *c3 = new TCanvas("c3","c3", 1200, 800);
	//gStyle->SetOptStat(00000);
	c3->Divide(2,2);
	
	c3->cd(1);
	TH1D *cathodeSubtract1 = new TH1D("cathodeSubtract1","25um Kapton, 400um Xe, 50um Kapton, 0.2um Cr, 21mm Xe; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract1->Add(exitRad,exitCath,1,-1);
	TH1D *escapeSubtract1 = new TH1D("escapeSubtract1","25um Kapton, 400um Xe, 50um Kapton, 0.2um Cr, 21mm Xe; TR Photon Energy [keV]; Count",100,0.,50.);
	escapeSubtract1->Add(cathodeSubtract1,exitDet,1,-1);
	escapeSubtract1->SetMinimum(0);
	escapeSubtract1->SetLineWidth(2);
	escapeSubtract1->Draw();
	
	c3->cd(2);
	TH1D *cathodeSubtract2 = new TH1D("cathodeSubtract2","55um Kapton, 5um Cu, 19.9mm Xe; TR Photon Energy [keV]; Count",100,0.,50.);
	cathodeSubtract2->Add(exitRad1,exitCath1,1,-1);
	TH1D *escapeSubtract2 = new TH1D("escapeSubtract2","55um Kapton, 5um Cu, 19.9mm Xe; TR Photon Energy [keV]; Count",100,0.,50.);
	escapeSubtract2->Add(cathodeSubtract2,exitDet1,1,-1);
	escapeSubtract2->SetMinimum(0);
	escapeSubtract2->SetLineWidth(2);
	escapeSubtract2->Draw();
	
	c3->cd(3);
	auto rp1 = new TRatioPlot(escapeSubtract2, escapeSubtract1);
    c3->SetTicks(0, 1);
    rp1->Draw();
    rp1->GetLowYaxis()->SetNdivisions(505);
    rp1->GetLowerRefGraph()->SetMinimum(-3);
   	rp1->GetLowerRefGraph()->SetMaximum(15);
	
    c3->SaveAs("GEMTRDCompareRatios.png");
*/
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
	
}
