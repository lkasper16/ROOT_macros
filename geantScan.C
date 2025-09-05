#include "TNtuple.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TLegend.h"
#include "TStyle.h"
#include "THStack.h"
#include <fstream>
#include <iostream>
#include <TList.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TObject.h>
#include <TAxis.h>

void geantScan(){
  
	TString rootFilesRegularR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_10.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_12.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_15.0Al.root"};
	TString rootFilesTransparentR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_10.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_12.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_15.0Al_TR.root"};
  TString rootFilesGammaR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_10.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_12.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_15.0Al_G.root"};
  
  TList *histListRegularR = new TList;
  TList *histListTransparentR = new TList;
  TList *histListGammaR = new TList;
	
	int colorList[] = {2,209,4,6,7,1,94,51,28};
  TString nameList[] = {"hist31","hist32","hist33","hist26"};
  TString titleList[] = {"50um Kapton 0.1um Al","50um Kapton 0.5um Al","50um Kapton 1.0um Al","50um Kapton 2.0um Al","50um Kapton 5.0um Al","50um Kapton 10.0um Al","50um Kapton 12.0um Al","50um Kapton 15.0um Al"};
  TString ratioTitleList[] = {"Spectra Absorbed in Xe: 0.1um Al / 1.0um Al","Spectra Absorbed in Xe: 0.5um Al / 1.0um Al","Spectra Absorbed in Xe: 1.0um Al / 1.0um Al","Spectra Absorbed in Xe: 2.0um Al / 1.0um Al","Spectra Absorbed in Xe: 5.0um Al / 1.0um Al","Spectra Absorbed in Xe: 10.0um Al / 1.0um Al","Spectra Absorbed in Xe: 12.0um Al / 1.0um Al","Spectra Absorbed in Xe: 15.0um Al / 1.0um Al"};
  TString legendList[] = {"Exit Radiator","Exit Kapton Window","Exit Cathode","Exit Xe Drift Gap"};
  
	TLegend *l1 = new TLegend(0.57, 0.73, 0.93, 0.9);
  TLegend *l2 = new TLegend(0.54, 0.73, 0.93, 0.9);
  TLegend *l3 = new TLegend(0.57, 0.73, 0.93, 0.9);
  
  TCanvas *c1 = new TCanvas("c1","125K e-, 20cm RegularR Rad, 3cm Xe:CO2 90:10", 1600, 1000);
  gStyle->SetOptStat(00000);
  c1->Divide(4,2);
  
  TCanvas *c1r = new TCanvas("c1r","RegularR Model Ratio Plots", 1600, 1000);
	c1r->Divide(4,2);
  c1r->SetTicks(0,1);
  
  TCanvas *c2 = new TCanvas("c2","125K e-, 20cm TransparentR Rad, 3cm Xe:CO2 90:10", 1600, 1000);
  gStyle->SetOptStat(00000);
  c2->Divide(4,2);
  
  TCanvas *c2r = new TCanvas("c2r","TransparentR Model Ratio Plots", 1600, 1000);
	c2r->Divide(4,2);
  c2r->SetTicks(0,1);
  
  TCanvas *c3 = new TCanvas("c3","125K e-, 20cm GammaR Rad, 3cm Xe:CO2 90:10", 1600, 1000);
  gStyle->SetOptStat(00000);
  c3->Divide(4,2);
  
  TCanvas *c3r = new TCanvas("c3r","GammaR Model Ratio Plots", 1600, 1000);
	c3r->Divide(4,2);
  c3r->SetTicks(0,1);
  
  TFile *file_r = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al.root");
	if (!file_r || file_r->IsZombie()) {
    std::cerr << "Error: Could not open file " << file_r << std::endl;
  }
	TObject *objcr = file_r->Get("hist33");
  TH1 *exitCath_r = (TH1*)objcr;
  TObject *objdr = file_r->Get("hist26");
  TH1 *exitDet_r = (TH1*)objdr;
  TH1D *escapeSubtract1r = new TH1D("escapeSubtract1r","Absorbed Spectra: 50um Kapton, 1.0um Al; TR Photon Energy [keV]; Count",100,0.,50.);
	escapeSubtract1r->Add(exitCath_r,exitDet_r,1,-1);
  escapeSubtract1r->SetDirectory(0);
  
  TFile *file_t = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_TR.root");
	if (!file_t || file_t->IsZombie()) {
    std::cerr << "Error: Could not open file " << file_t << std::endl;
  }
	TObject *objct = file_t->Get("hist33");
  TH1 *exitCath_t = (TH1*)objct;
  TObject *objdt = file_t->Get("hist26");
  TH1 *exitDet_t = (TH1*)objdt;
  TH1D *escapeSubtract1t = new TH1D("escapeSubtract1t","Absorbed Spectra: 50um Kapton, 1.0um Al; TR Photon Energy [keV]; Count",100,0.,50.);
	escapeSubtract1t->Add(exitCath_t,exitDet_t,1,-1);
  escapeSubtract1t->SetDirectory(0);
  
  TFile *file_g = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_G.root");
	if (!file_g || file_g->IsZombie()) {
    std::cerr << "Error: Could not open file " << file_g << std::endl;
  }
  TObject *objcg = file_g->Get("hist33");
  TH1 *exitCath_g = (TH1*)objcg;
  TObject *objdg = file_g->Get("hist26");
  TH1 *exitDet_g = (TH1*)objdg;
  TH1D *escapeSubtract1g = new TH1D("escapeSubtract1g","Absorbed Spectra: 50um Kapton, 1.0um Al; TR Photon Energy [keV]; Count",100,0.,50.);
	escapeSubtract1g->Add(exitCath_g,exitDet_g,1,-1);
  escapeSubtract1g->SetDirectory(0);
  
  //-- RegularR Model
	for (int i=0; i<sizeof(rootFilesRegularR)/sizeof(rootFilesRegularR[0]); i++) {
		const TString& rootFile = rootFilesRegularR[i];
		TFile *file = TFile::Open(rootFile, "READ");
    
    TObject *obj1 = file->Get(nameList[0]);
    if (obj1) {
			TH1 *exitRad = (TH1*)obj1;
      exitRad->SetLineColor(colorList[0]);
      exitRad->SetLineWidth(2);
      exitRad->SetDirectory(0);
      histListRegularR->Add(exitRad);
      if(i==0) l1->AddEntry(exitRad, legendList[0], "l");
		}
    TObject *obj2 = file->Get(nameList[1]);
    if (obj2) {
			TH1 *exitWin = (TH1*)obj2;
      exitWin->SetLineColor(colorList[1]);
      exitWin->SetLineWidth(2);
      exitWin->SetDirectory(0);
      histListRegularR->Add(exitWin);
      if(i==0) l1->AddEntry(exitWin, legendList[1], "l");
		}
    TObject *obj3 = file->Get(nameList[2]);
    if (obj3) {
			TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(colorList[2]);
      exitCath->SetLineWidth(2);
      exitCath->SetDirectory(0);
      histListRegularR->Add(exitCath);
      if(i==0) l1->AddEntry(exitCath, legendList[2], "l");
		}
    TObject *obj4 = file->Get(nameList[3]);
    if (obj4) {
			TH1 *exitDet = (TH1*)obj4;
      exitDet->SetLineColor(colorList[3]);
      exitDet->SetLineWidth(2);
      exitDet->SetDirectory(0);
      histListRegularR->Add(exitDet);
      if(i==0) l1->AddEntry(exitDet, legendList[3], "l");
		}
  
    c1->cd(i+1);
    TH1 *firstHist = (TH1 *)histListRegularR->First();
    if (firstHist) {
      firstHist->GetXaxis()->SetTitle("TR Photon Energy [keV]");
      firstHist->GetYaxis()->SetTitle("Count");
      firstHist->SetTitle(titleList[i]);
    }
    histListRegularR->Draw("same");
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    l1->SetTextSize(0.027);
	  l1->SetHeader("#gamma Spectrum (RegularR Model)", "C");
    l1->Draw();
    
    c1r->cd(i+1);
    TH1 *catHist = (TH1 *)histListRegularR->FindObject(obj3);
    TH1 *detHist = (TH1 *)histListRegularR->FindObject(obj4);
    TH1D *escapeSubtract2r = new TH1D("escapeSubtract2r"," ; TR Photon Energy [keV]; ",100,0.,50.);
	  escapeSubtract2r->Add(catHist,detHist,1,-1);
    escapeSubtract2r->SetTitle(ratioTitleList[i]);
    escapeSubtract2r->SetDirectory(0);
	  auto rp1r = new TRatioPlot(escapeSubtract2r, escapeSubtract1r);
    rp1r->Draw();
    //rp1r->SetRightMargin(0.07);
    //rp1r->SetLeftMargin(0.18);
    rp1r->GetUpperRefYaxis()->SetRangeUser(0., escapeSubtract1r->GetMaximum()+700.);
    rp1r->GetLowYaxis()->SetNdivisions(505);
    rp1r->GetLowerRefGraph()->SetMinimum(0.);
    rp1r->GetLowerRefGraph()->SetMaximum(2.);
    
    file->Close();
    histListRegularR->Clear();
  } //--END RegularR Model loop
  
  //-- TransparentR Model
	for (int i=0; i<sizeof(rootFilesTransparentR)/sizeof(rootFilesTransparentR[0]); i++) {
		const TString& rootFile = rootFilesTransparentR[i];
		TFile *file = TFile::Open(rootFile, "READ");
    
    TObject *obj1 = file->Get(nameList[0]);
    if (obj1) {
			TH1 *exitRad = (TH1*)obj1;
      exitRad->SetLineColor(colorList[0]);
      exitRad->SetLineWidth(2);
      exitRad->SetDirectory(0);
      histListTransparentR->Add(exitRad);
      if(i==0) l2->AddEntry(exitRad, legendList[0], "l");
		}
    TObject *obj2 = file->Get(nameList[1]);
    if (obj2) {
			TH1 *exitWin = (TH1*)obj2;
      exitWin->SetLineColor(colorList[1]);
      exitWin->SetLineWidth(2);
      exitWin->SetDirectory(0);
      histListTransparentR->Add(exitWin);
      if(i==0) l2->AddEntry(exitWin, legendList[1], "l");
		}
    TObject *obj3 = file->Get(nameList[2]);
    if (obj3) {
			TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(colorList[2]);
      exitCath->SetLineWidth(2);
      exitCath->SetDirectory(0);
      histListTransparentR->Add(exitCath);
      if(i==0) l2->AddEntry(exitCath, legendList[2], "l");
		}
    TObject *obj4 = file->Get(nameList[3]);
    if (obj4) {
			TH1 *exitDet = (TH1*)obj4;
      exitDet->SetLineColor(colorList[3]);
      exitDet->SetLineWidth(2);
      exitDet->SetDirectory(0);
      histListTransparentR->Add(exitDet);
      if(i==0) l2->AddEntry(exitDet, legendList[3], "l");
		}
  
    c2->cd(i+1);
    TH1 *firstHist = (TH1 *)histListTransparentR->First();
    if (firstHist) {
      firstHist->GetXaxis()->SetTitle("TR Photon Energy [keV]");
      firstHist->GetYaxis()->SetTitle("Count");
      firstHist->SetTitle(titleList[i]);
    }
    histListTransparentR->Draw("same");
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    l2->SetTextSize(0.027);
	  l2->SetHeader("#gamma Spectrum (TransparentR Model)", "C");
    l2->Draw();
    
    c2r->cd(i+1);
    TH1 *catHist = (TH1 *)histListTransparentR->FindObject(obj3);
    TH1 *detHist = (TH1 *)histListTransparentR->FindObject(obj4);
    TH1D *escapeSubtract2t = new TH1D("escapeSubtract2t"," ; TR Photon Energy [keV]; ",100,0.,50.);
	  escapeSubtract2t->Add(catHist,detHist,1,-1);
    escapeSubtract2t->SetTitle(ratioTitleList[i]);
    escapeSubtract2t->SetDirectory(0);
	  auto rp1t = new TRatioPlot(escapeSubtract2t, escapeSubtract1t);
    rp1t->Draw();
    //rp1t->SetRightMargin(0.07);
    //rp1t->SetLeftMargin(0.18);
    rp1t->GetUpperRefYaxis()->SetRangeUser(0., escapeSubtract1t->GetMaximum()+700.);
    rp1t->GetLowYaxis()->SetNdivisions(505);
    rp1t->GetLowerRefGraph()->SetMinimum(0.);
    rp1t->GetLowerRefGraph()->SetMaximum(2.);
    
    file->Close();
    histListTransparentR->Clear();
  } //--END TransparentR Model Loop
  
  //-- GammaR Model
	for (int i=0; i<sizeof(rootFilesGammaR)/sizeof(rootFilesGammaR[0]); i++) {
		const TString& rootFile = rootFilesGammaR[i];
		TFile *file = TFile::Open(rootFile, "READ");
    
    TObject *obj1 = file->Get(nameList[0]);
    if (obj1) {
			TH1 *exitRad = (TH1*)obj1;
      exitRad->SetLineColor(colorList[0]);
      exitRad->SetLineWidth(2);
      exitRad->SetDirectory(0);
      histListGammaR->Add(exitRad);
      if(i==0) l3->AddEntry(exitRad, legendList[0], "l");
		}
    TObject *obj2 = file->Get(nameList[1]);
    if (obj2) {
			TH1 *exitWin = (TH1*)obj2;
      exitWin->SetLineColor(colorList[1]);
      exitWin->SetLineWidth(2);
      exitWin->SetDirectory(0);
      histListGammaR->Add(exitWin);
      if(i==0) l3->AddEntry(exitWin, legendList[1], "l");
		}
    TObject *obj3 = file->Get(nameList[2]);
    if (obj3) {
			TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(colorList[2]);
      exitCath->SetLineWidth(2);
      exitCath->SetDirectory(0);
      histListGammaR->Add(exitCath);
      if(i==0) l3->AddEntry(exitCath, legendList[2], "l");
		}
    TObject *obj4 = file->Get(nameList[3]);
    if (obj4) {
			TH1 *exitDet = (TH1*)obj4;
      exitDet->SetLineColor(colorList[3]);
      exitDet->SetLineWidth(2);
      exitDet->SetDirectory(0);
      histListGammaR->Add(exitDet);
      if(i==0) l3->AddEntry(exitDet, legendList[3], "l");
		}
  
    c3->cd(i+1);
    TH1 *firstHist = (TH1 *)histListGammaR->First();
    if (firstHist) {
      firstHist->GetXaxis()->SetTitle("TR Photon Energy [keV]");
      firstHist->GetYaxis()->SetTitle("Count");
      firstHist->SetTitle(titleList[i]);
    }
    histListGammaR->Draw("same");
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    l3->SetTextSize(0.027);
	  l3->SetHeader("#gamma Spectrum (GammaR Model)", "C");
    l3->Draw();
    
    c3r->cd(i+1);
    TH1 *catHist = (TH1 *)histListGammaR->FindObject(obj3);
    TH1 *detHist = (TH1 *)histListGammaR->FindObject(obj4);
    TH1D *escapeSubtract2g = new TH1D("escapeSubtract2g"," ; TR Photon Energy [keV]; ",100,0.,50.);
	  escapeSubtract2g->Add(catHist,detHist,1,-1);
    escapeSubtract2g->SetTitle(ratioTitleList[i]);
    escapeSubtract2g->SetDirectory(0);
	  auto rp1g = new TRatioPlot(escapeSubtract2g, escapeSubtract1g);
    rp1g->Draw();
    //rp1g->SetRightMargin(0.07);
    //rp1g->SetLeftMargin(0.18);
    rp1g->GetUpperRefYaxis()->SetRangeUser(0., escapeSubtract1g->GetMaximum()+700.);
    rp1g->GetLowYaxis()->SetNdivisions(505);
    rp1g->GetLowerRefGraph()->SetMinimum(0.);
    rp1g->GetLowerRefGraph()->SetMaximum(2.);
    
    file->Close();
    histListGammaR->Clear();
  } //--END GammaR Model Loop
  
  c1->SaveAs("GEMTRDAluminumScanRegularR.pdf");
  c1r->SaveAs("GEMTRDAluminumScanRegularRRatios.pdf");
  c2->SaveAs("GEMTRDAluminumScanTransparentR.pdf");
  c2r->SaveAs("GEMTRDAluminumScanTransparentRRatios.pdf");
  c3->SaveAs("GEMTRDAluminumScanGammaR.pdf");
  c3r->SaveAs("GEMTRDAluminumScanGammaRRatios.pdf");
  
}
