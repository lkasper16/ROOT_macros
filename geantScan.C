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
//TFile *refFile;
TH1D *escapeSubtract1g;
TH1D *hAbsorb;
TH1D *hDiff;

void geantScan(){
  
  hDiff = new TH1D("hDiff","Difference; TR Photon Energy [keV]; Count",100,0.,50.);
  hAbsorb = new TH1D("hAbsorb","newAbsorb; TR Photon Energy [keV]; Count",100,0.,50.);
  
	//TString rootFilesRegularR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_10.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_12.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_15.0Al.root"};
	TString rootFilesRegularR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.5Al.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al.root"};
  //TString rootFilesTransparentR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_10.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_12.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_15.0Al_TR.root"};
  //TString rootFilesTransparentR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.5Al_TR.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al_TR.root"};
  //NEW September 2026
  TString rootFilesTransparentR[] = {"../largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1.root","../largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_TR.root","../largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.5Al_TR.root","../largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al_TR.root"};
  //TString rootFilesGammaR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_5.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_10.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_12.0Al_G.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_15.0Al_G.root"};
  TString rootFilesGammaR[] = {"fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al_GM_2M.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.0Al_GM_2M.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.5Al_GM_2M.root","fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_2.0Al_GM_2M.root"};
  TString rootFilesMaterialScan[] = {"../largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_1.5Al_TR.root","../largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.5Cu_TR.root","../largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.2Cr_TR.root","../largeGemSim/transparentR/fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.085Au_TR.root"};
  
  TList *histListRegularR = new TList;
  TList *histListTransparentR = new TList;
  TList *histListGammaR = new TList;
  TList *histListDiff = new TList;
	double scale = 1.;
	int colorList[] = {2,209,4,1,7,6,94,51,28};
  TString nameList[] = {"hist31","hist32","hist33","hist26"};
  //TString titleList[] = {"50um Kapton 0.1um Al","50um Kapton 0.5um Al","50um Kapton 1.0um Al","50um Kapton 2.0um Al","50um Kapton 5.0um Al","50um Kapton 10.0um Al","50um Kapton 12.0um Al","50um Kapton 15.0um Al"};
  TString titleList[] = {"0.1 #mum Al","1.0 #mum Al","1.5 #mum Al","2.0 #mum Al"};
  TString materialScanTitleList[] = {"1.5 #mum Al","0.5 #mum Cu","0.2 #mum Cr","0.085 #mum Au"};
  
  //TString ratioTitleList[] = {"Spectra Absorbed in Xe: 0.1um Al / 0.1um Al","Spectra Absorbed in Xe: 0.5um Al / 0.1um Al","Spectra Absorbed in Xe: 1.0um Al / 0.1um Al","Spectra Absorbed in Xe: 2.0um Al / 0.1um Al","Spectra Absorbed in Xe: 5.0um Al / 0.1um Al","Spectra Absorbed in Xe: 10.0um Al / 0.1um Al","Spectra Absorbed in Xe: 12.0um Al / 0.1um Al","Spectra Absorbed in Xe: 15.0um Al / 0.1um Al"};
  TString ratioTitleList[] = {"Spectra Absorbed in Xe: 0.1 #mum Al / 0.1 #mum Al","Spectra Absorbed in Xe: 1.0 #mum Al / 0.1 #mum Al","Spectra Absorbed in Xe: 1.5 #mum Al / 0.1 #mum Al","Spectra Absorbed in Xe: 2.0 #mum Al / 0.1 #mum Al"};
  TString legendList[] = {"Exit Radiator","Exit Kapton Window","Exit Cathode","Exit Drift Region"};
  
	TLegend *l1 = new TLegend(0.46, 0.65, 0.93, 0.9);
  TLegend *l2 = new TLegend(0.46, 0.55, 0.97, 0.78);
  TLegend *l3 = new TLegend(0.43, 0.65, 0.93, 0.9);
  
  
  TCanvas *c0 = new TCanvas("c0","Difference Plots", 1900, 650);
  gStyle->SetOptStat(00000);
  gStyle->SetTitleFontSize(0.1);
  c0->Divide(4,1);
  
  TCanvas *c1 = new TCanvas("c1","125K e-, 20cm RegularR Rad, 3cm Xe:CO2 90:10", 1900, 650);
  gStyle->SetOptStat(00000);
  gStyle->SetTitleFontSize(0.1);
  c1->Divide(4,1);
  
  TCanvas *c1r = new TCanvas("c1r","RegularR Model Ratio Plots", 1900, 650);
	c1r->Divide(4,1);
  c1r->SetTicks(0,1);
  
  TCanvas *c2 = new TCanvas("c2","125K e-, 20cm TransparentR Rad, 3cm Xe:CO2 90:10", 1900, 600);
  gStyle->SetOptStat(00000);
  c2->Divide(4,1);
  
  TCanvas *c2r = new TCanvas("c2r","TransparentR Model Ratio Plots", 1900, 650);
	c2r->Divide(4,1);
  c2r->SetTicks(0,1);
  
  TCanvas *c2d = new TCanvas("c2d","TransparentR Model Integral Plots", 1900, 600);
	c2d->Divide(4,1);
  
  TCanvas *c3 = new TCanvas("c3","125K e-, 20cm GammaR Rad, 3cm Xe:CO2 90:10", 1900, 650);
  gStyle->SetOptStat(00000);
  c3->Divide(4,1);
  
  TCanvas *c3r = new TCanvas("c3r","GammaR Model Ratio Plots", 1900, 650);
	c3r->Divide(4,1);
  c3r->SetTicks(0,1);
  
  TCanvas *c4 = new TCanvas("c4","150K e-, 20cm TransparentR Rad, 3cm Xe:CO2 90:10", 1900, 600);
  gStyle->SetOptStat(00000);
  c4->Divide(4,1);
  
  TCanvas *c4d = new TCanvas("c4d","TransparentR Model Integral Plots", 1900, 600);
	c4d->Divide(4,1);
  
  //TCanvas *c3gs = new TCanvas("c3gs","GammaR Model Ratio Plots", 1600, 800);
  //c3gs->Divide(2,1);
  //c3gs->SetTicks(0,1);
  //TPad *pad1 = new TPad("pad1","",0.0,0.5,1.0,1.0);
  //TPad *pad2 = new TPad("pad2","",0.0,0.5,1.0,1.0);
  
  TFile *file_r = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al.root");
	if (!file_r || file_r->IsZombie()) {
    std::cerr << "Error: Could not open file " << file_r << std::endl;
  }
	TObject *objcr = file_r->Get("hist33");
  TH1 *exitCath_r = (TH1*)objcr;
  TObject *objdr = file_r->Get("hist26");
  TH1 *exitDet_r = (TH1*)objdr;
  TH1D *escapeSubtract1r = new TH1D("escapeSubtract1r","Absorbed Spectra: 50 #mum Kapton, 0.1 #mum Al; TR Photon Energy [keV]; Count",100,0.,50.);
	escapeSubtract1r->Add(exitCath_r,exitDet_r,1,-1);
  escapeSubtract1r->SetDirectory(0);
  
  TFile *file_t = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al_TR.root");
	if (!file_t || file_t->IsZombie()) {
    std::cerr << "Error: Could not open file " << file_t << std::endl;
  }
	TObject *objct = file_t->Get("hist33");
  TH1 *exitCath_t = (TH1*)objct;
  TObject *objdt = file_t->Get("hist26");
  TH1 *exitDet_t = (TH1*)objdt;
  TH1D *escapeSubtract1t = new TH1D("escapeSubtract1t","Absorbed Spectra: 50 #mum Kapton, 0.1 #mum Al; TR Photon Energy [keV]; Count",100,0.,50.);
	escapeSubtract1t->Add(exitCath_t,exitDet_t,1,-1);
  escapeSubtract1t->SetDirectory(0);
  
  TFile *file_g = TFile::Open("fdc15_e-10000MeV_Xe10CO2_d30:1.5mm_r20cm_m1_0.1Al_GM_2M.root");
	if (!file_g || file_g->IsZombie()) {
    std::cerr << "Error: Could not open file " << file_g << std::endl;
  }
  TObject *objcg = file_g->Get("hist33");
  TH1 *exitCath_g = (TH1*)objcg;
  TObject *objdg = file_g->Get("hist26");
  TH1 *exitDet_g = (TH1*)objdg;
  escapeSubtract1g = new TH1D("escapeSubtract1g","Absorbed Spectra: 50 #mum Kapton, 0.1 #mum Al; TR Photon Energy [keV]; Count",100,0.,50.);
	escapeSubtract1g->Add(exitCath_g,exitDet_g,1,-1);
  //scale = 1./escapeSubtract1g->Integral();
  //escapeSubtract1g->Scale(scale);
  escapeSubtract1g->SetDirectory(0);
  
  /*
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
      //histListRegularR->Add(exitWin);
      //if(i==0) l1->AddEntry(exitWin, legendList[1], "l");
		}
    TObject *obj3 = file->Get(nameList[2]);
    if (obj3) {
			TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(colorList[2]);
      exitCath->SetLineWidth(2);
      exitCath->SetFillColor(colorList[2]);
      exitCath->SetFillStyle(3003);
      exitCath->SetDirectory(0);
      histListRegularR->Add(exitCath);
      if(i==0) l1->AddEntry(exitCath, legendList[2], "l");
		}
    TObject *obj4 = file->Get(nameList[3]);
    if (obj4) {
			TH1 *exitDet = (TH1*)obj4;
      exitDet->SetLineColor(colorList[3]);
      exitDet->SetLineWidth(2);
      exitDet->SetFillColor(10);
      exitDet->SetFillStyle(1001);
      exitDet->SetDirectory(0);
      histListRegularR->Add(exitDet);
      if(i==0) l1->AddEntry(exitDet, legendList[3], "l");
		}
  
    c1->cd(i+1);
    TH1 *firstHist = (TH1 *)histListRegularR->First();
    if (firstHist) {
      firstHist->GetXaxis()->SetTitle("TR Photon Energy [keV]");
      firstHist->GetXaxis()->SetLabelSize(0.05);
      firstHist->GetXaxis()->SetTitleSize(0.05);
      firstHist->GetYaxis()->SetTitle("Count");
      firstHist->GetYaxis()->SetLabelSize(0.045);
      firstHist->GetYaxis()->SetTitleSize(0.045);
      firstHist->SetTitle(titleList[i]);
    }
    histListRegularR->Draw("same");
    gPad->RedrawAxis();
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    l1->SetTextSize(0.044);
	  l1->SetHeader("#splitline{#gamma Spectrum}{(RegularR Model)}", "C");
    l1->Draw();
    
    c1r->cd(i+1);
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    TH1 *catHist = (TH1 *)histListRegularR->FindObject(obj3);
    TH1 *detHist = (TH1 *)histListRegularR->FindObject(obj4);
    TH1D *escapeSubtract2r = new TH1D("escapeSubtract2r"," ; TR Photon Energy [keV]; ",100,0.,50.);
	  escapeSubtract2r->Add(catHist,detHist,1,-1);
    escapeSubtract2r->SetTitle(ratioTitleList[i]);
    escapeSubtract2r->SetDirectory(0);
    escapeSubtract2r->GetXaxis()->SetLabelSize(0.05);
    escapeSubtract2r->GetXaxis()->SetTitleSize(0.05);
    escapeSubtract2r->GetYaxis()->SetLabelSize(0.045);
    escapeSubtract2r->GetYaxis()->SetTitleSize(0.045);
	  auto rp1r = new TRatioPlot(escapeSubtract2r, escapeSubtract1r);
    rp1r->Draw();
    //rp1r->SetRightMargin(0.07);
    //rp1r->SetLeftMargin(0.18);
    rp1r->GetUpperRefYaxis()->SetRangeUser(0., escapeSubtract1r->GetMaximum()+700.);
    rp1r->GetLowYaxis()->SetNdivisions(505);
    rp1r->GetLowerRefGraph()->SetMinimum(0.);
    rp1r->GetLowerRefGraph()->SetMaximum(1.2);
    
    file->Close();
    histListRegularR->Clear();
  } //--END RegularR Model loop
  */
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
      //histListTransparentR->Add(exitWin);
      //if(i==0) l2->AddEntry(exitWin, legendList[1], "l");
		}
    TObject *obj3 = file->Get(nameList[2]);
    if (obj3) {
			TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(colorList[2]);
      exitCath->SetLineWidth(2);
      exitCath->SetFillColor(colorList[2]);
      exitCath->SetFillStyle(3003);
      exitCath->SetDirectory(0);
      histListTransparentR->Add(exitCath);
      if(i==0) l2->AddEntry(exitCath, legendList[2], "l");
		}
    TObject *obj4 = file->Get(nameList[3]);
    if (obj4) {
			TH1 *exitDet = (TH1*)obj4;
      exitDet->SetLineColor(colorList[3]);
      exitDet->SetLineWidth(2);
      exitDet->SetLineStyle(4);
      exitDet->SetFillColor(10);
      exitDet->SetFillStyle(1001);
      exitDet->SetDirectory(0);
      histListTransparentR->Add(exitDet);
      if(i==0) l2->AddEntry(exitDet, legendList[3], "l");
		}
  
    c2->cd(i+1);
    gStyle->SetOptStat(0000);
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.18);
    TH1 *firstHist = (TH1 *)histListTransparentR->First();
    if (firstHist) {
      firstHist->GetXaxis()->SetTitle("TR Photon Energy [keV]");
      firstHist->GetXaxis()->SetLabelSize(0.045);
      firstHist->GetXaxis()->SetTitleSize(0.05);
      firstHist->GetYaxis()->SetTitle("Count");
      firstHist->GetYaxis()->SetLabelSize(0.045);
      firstHist->GetYaxis()->SetTitleSize(0.05);
      firstHist->GetYaxis()->SetTitleOffset(1.8);
      firstHist->GetXaxis()->SetTitleOffset(0.8);
      firstHist->SetMinimum(0.);
      firstHist->SetMaximum(20000.);
      firstHist->SetTitle(titleList[i]);
    }
    histListTransparentR->Draw("same");
    gPad->RedrawAxis();
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.18);
    l2->SetTextSize(0.052);
	  //l2->SetHeader("#splitline{#gamma Spectrum}{(TransparentR Model)}", "C");
	  l2->SetHeader("#gamma Spectrum","C");
    l2->Draw();
    
    
    c2d->cd(i+1);
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.18);
    gStyle->SetOptStat("mi");
	  gStyle->SetStatFormat("6.6g");
	  gStyle->SetStatX(0.7);
	  gStyle->SetStatY(0.7);
    
    TH1 *catHist = (TH1 *)histListTransparentR->FindObject(obj3);
    TH1 *detHist = (TH1 *)histListTransparentR->FindObject(obj4);
    TH1D *escapeSubtract2t = new TH1D("escapeSubtract2t"," ; TR Photon Energy [keV]; Count",100,0.,50.);
	  escapeSubtract2t->Add(catHist,detHist,1,-1);
    escapeSubtract2t->SetTitle(titleList[i]);
    escapeSubtract2t->SetDirectory(0);
    escapeSubtract2t->GetXaxis()->SetLabelSize(0.045);
    escapeSubtract2t->GetXaxis()->SetTitleSize(0.05);
    escapeSubtract2t->GetYaxis()->SetLabelSize(0.045);
    escapeSubtract2t->GetYaxis()->SetTitleSize(0.05);
    escapeSubtract2t->GetYaxis()->SetTitleOffset(1.8);
    escapeSubtract2t->GetXaxis()->SetTitleOffset(0.8);
    escapeSubtract2t->SetMinimum(0.);
    escapeSubtract2t->SetMaximum(18000.);
    escapeSubtract2t->SetFillColor(colorList[2]);
    escapeSubtract2t->SetFillStyle(3003);
    escapeSubtract2t->SetLineWidth(2);
    escapeSubtract2t->SetLineColor(colorList[2]);
    escapeSubtract2t->Draw();
    
    /*
    c2r->cd(i+1);
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    gStyle->SetOptStat(0000);
    TH1 *catHist1 = (TH1 *)histListTransparentR->FindObject(obj3);
    TH1 *detHist1 = (TH1 *)histListTransparentR->FindObject(obj4);
    TH1D *escapeSubtract2t1 = new TH1D("escapeSubtract2t1"," ; TR Photon Energy [keV]; Count",100,0.,50.);
	  escapeSubtract2t1->Add(catHist1,detHist1,1,-1);
    escapeSubtract2t1->SetTitle(ratioTitleList[i]);
    escapeSubtract2t1->SetDirectory(0);
    escapeSubtract2t1->GetXaxis()->SetLabelSize(0.05);
    escapeSubtract2t1->GetXaxis()->SetTitleSize(0.05);
    escapeSubtract2t1->GetYaxis()->SetLabelSize(0.045);
    escapeSubtract2t1->GetYaxis()->SetTitleSize(0.045);
	  auto rp1t1 = new TRatioPlot(escapeSubtract2t1, escapeSubtract1t);
    rp1t1->Draw();
    //rp1t1->SetRightMargin(0.07);
    //rp1t1->SetLeftMargin(0.18);
    rp1t1->GetUpperRefYaxis()->SetRangeUser(0., escapeSubtract1t->GetMaximum()+700.);
    rp1t1->GetLowYaxis()->SetNdivisions(505);
    rp1t1->GetLowerRefGraph()->SetMinimum(0.);
    rp1t1->GetLowerRefGraph()->SetMaximum(1.2);
    */
    file->Close();
    histListTransparentR->Clear();
  } //--END TransparentR Model Loop
  
  
  
  
  //-- Material Scan
	for (int i=0; i<sizeof(rootFilesMaterialScan)/sizeof(rootFilesMaterialScan[0]); i++) {
		const TString& rootFile = rootFilesMaterialScan[i];
		TFile *file = TFile::Open(rootFile, "READ");
    
    TObject *obj1 = file->Get(nameList[0]);
    if (obj1) {
			TH1 *exitRad = (TH1*)obj1;
      exitRad->SetLineColor(colorList[0]);
      exitRad->SetLineWidth(2);
      exitRad->SetDirectory(0);
      histListTransparentR->Add(exitRad);
      //if(i==0) l2->AddEntry(exitRad, legendList[0], "l");
		}
    TObject *obj2 = file->Get(nameList[1]);
    if (obj2) {
			TH1 *exitWin = (TH1*)obj2;
      exitWin->SetLineColor(colorList[1]);
      exitWin->SetLineWidth(2);
      exitWin->SetDirectory(0);
		}
    TObject *obj3 = file->Get(nameList[2]);
    if (obj3) {
			TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(colorList[2]);
      exitCath->SetLineWidth(2);
      exitCath->SetFillColor(colorList[2]);
      exitCath->SetFillStyle(3003);
      exitCath->SetDirectory(0);
      histListTransparentR->Add(exitCath);
      //if(i==0) l2->AddEntry(exitCath, legendList[2], "l");
		}
    TObject *obj4 = file->Get(nameList[3]);
    if (obj4) {
			TH1 *exitDet = (TH1*)obj4;
      exitDet->SetLineColor(colorList[3]);
      exitDet->SetLineWidth(2);
      exitDet->SetLineStyle(4);
      exitDet->SetFillColor(10);
      exitDet->SetFillStyle(1001);
      exitDet->SetDirectory(0);
      histListTransparentR->Add(exitDet);
      //if(i==0) l2->AddEntry(exitDet, legendList[3], "l");
		}
  
    c4->cd(i+1);
    gStyle->SetOptStat(0000);
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.18);
    TH1 *firstHist = (TH1 *)histListTransparentR->First();
    if (firstHist) {
      firstHist->GetXaxis()->SetTitle("TR Photon Energy [keV]");
      firstHist->GetXaxis()->SetLabelSize(0.045);
      firstHist->GetXaxis()->SetTitleSize(0.05);
      firstHist->GetYaxis()->SetTitle("Count");
      firstHist->GetYaxis()->SetLabelSize(0.045);
      firstHist->GetYaxis()->SetTitleSize(0.05);
      firstHist->GetYaxis()->SetTitleOffset(1.8);
      firstHist->GetXaxis()->SetTitleOffset(0.8);
      firstHist->SetMinimum(0.);
      firstHist->SetMaximum(20000.);
      firstHist->SetTitle(materialScanTitleList[i]);
    }
    histListTransparentR->Draw("same");
    gPad->RedrawAxis();
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.18);
    l2->SetTextSize(0.052);
	  l2->SetHeader("#gamma Spectrum","C");
    l2->Draw();
    
    
    c4d->cd(i+1);
    gPad->SetRightMargin(0.03);
    gPad->SetLeftMargin(0.18);
    gStyle->SetOptStat("mi");
	  gStyle->SetStatFormat("6.6g");
	  gStyle->SetStatX(0.7);
	  gStyle->SetStatY(0.7);
    
    TH1 *catHist = (TH1 *)histListTransparentR->FindObject(obj3);
    TH1 *detHist = (TH1 *)histListTransparentR->FindObject(obj4);
    TH1D *escapeSubtract2t = new TH1D("escapeSubtract2t"," ; TR Photon Energy [keV]; Count",100,0.,50.);
	  escapeSubtract2t->Add(catHist,detHist,1,-1);
    escapeSubtract2t->SetTitle(materialScanTitleList[i]);
    escapeSubtract2t->SetDirectory(0);
    escapeSubtract2t->GetXaxis()->SetLabelSize(0.045);
    escapeSubtract2t->GetXaxis()->SetTitleSize(0.05);
    escapeSubtract2t->GetYaxis()->SetLabelSize(0.045);
    escapeSubtract2t->GetYaxis()->SetTitleSize(0.05);
    escapeSubtract2t->GetYaxis()->SetTitleOffset(1.8);
    escapeSubtract2t->GetXaxis()->SetTitleOffset(0.8);
    escapeSubtract2t->SetMinimum(0.);
    escapeSubtract2t->SetMaximum(18000.);
    escapeSubtract2t->SetFillColor(colorList[2]);
    escapeSubtract2t->SetFillStyle(3003);
    escapeSubtract2t->SetLineWidth(2);
    escapeSubtract2t->SetLineColor(colorList[2]);
    escapeSubtract2t->Draw();
    file->Close();
    histListTransparentR->Clear();
  } //--END Material Scan Loop
  
  
  /*
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
      //histListGammaR->Add(exitWin);
      //if(i==0) l3->AddEntry(exitWin, legendList[1], "l");
		}
    TObject *obj3 = file->Get(nameList[2]);
    if (obj3) {
			TH1 *exitCath = (TH1*)obj3;
      exitCath->SetLineColor(colorList[2]);
      exitCath->SetLineWidth(2);
      exitCath->SetDirectory(0);
      exitCath->SetFillColor(colorList[2]);
      exitCath->SetFillStyle(3003);
      histListGammaR->Add(exitCath);
      if(i==0) l3->AddEntry(exitCath, legendList[2], "l");
		}
    TObject *obj4 = file->Get(nameList[3]);
    if (obj4) {
			TH1 *exitDet = (TH1*)obj4;
      exitDet->SetLineColor(colorList[3]);
      exitDet->SetLineWidth(2);
      exitDet->SetFillColor(10);
      exitDet->SetFillStyle(1001);
      exitDet->SetDirectory(0);
      histListGammaR->Add(exitDet);
      if(i==0) l3->AddEntry(exitDet, legendList[3], "l");
		}
    
    c3->cd(i+1);
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    TH1 *firstHist = (TH1 *)histListGammaR->First();
    if (firstHist) {
      firstHist->GetXaxis()->SetTitle("TR Photon Energy [keV]");
      firstHist->GetXaxis()->SetLabelSize(0.05);
      firstHist->GetXaxis()->SetTitleSize(0.05);
      firstHist->GetYaxis()->SetTitle("Count");
      firstHist->GetYaxis()->SetLabelSize(0.045);
      firstHist->GetYaxis()->SetTitleSize(0.045);
      firstHist->SetTitle(titleList[i]);
    }
    histListGammaR->Draw("same");
    gPad->RedrawAxis();
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    l3->SetTextSize(0.044);
	  l3->SetHeader("#splitline{#gamma Spectrum}{(GammaM Model)}", "C");
    l3->Draw();
    
    c3r->cd(i+1);
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    TH1 *catHist = (TH1 *)histListGammaR->FindObject(obj3);
    TH1 *detHist = (TH1 *)histListGammaR->FindObject(obj4);
    TH1D *escapeSubtract2g = new TH1D("escapeSubtract2g"," ; TR Photon Energy [keV]; ",100,0.,50.);
	  escapeSubtract2g->Add(catHist,detHist,1,-1);
    escapeSubtract2g->SetTitle(ratioTitleList[i]);
    escapeSubtract2g->SetDirectory(0);
    escapeSubtract2g->GetXaxis()->SetLabelSize(0.05);
    escapeSubtract2g->GetXaxis()->SetTitleSize(0.05);
    escapeSubtract2g->GetYaxis()->SetLabelSize(0.045);
    escapeSubtract2g->GetYaxis()->SetTitleSize(0.045);
	  auto rp1g = new TRatioPlot(escapeSubtract2g, escapeSubtract1g);
    //if (i==2) auto rp1gs = new TRatioPlot(escapeSubtract2g, escapeSubtract1g);
    //if (i==3) auto rp2gs = new TRatioPlot(escapeSubtract2g, escapeSubtract1g);
    rp1g->Draw();
    //rp1g->SetRightMargin(0.07);
    //rp1g->SetLeftMargin(0.18);
    //cout<<<<<<endl;
    rp1g->GetUpperRefYaxis()->SetRangeUser(0., escapeSubtract1g->GetMaximum()+700.);
    rp1g->GetLowYaxis()->SetNdivisions(505);
    rp1g->GetLowerRefGraph()->SetMinimum(0.);
    rp1g->GetLowerRefGraph()->SetMaximum(1.2);
    
    //=====Difference Plots
    cout<<"======== START NEW DIFF PLOT, i="<<i<<" ========= "<<endl;
    c0->cd(i+1);
    gPad->SetRightMargin(0.07);
    gPad->SetLeftMargin(0.18);
    TH1 *catHist1 = (TH1 *)histListGammaR->FindObject(obj3);
    TH1 *detHist1 = (TH1 *)histListGammaR->FindObject(obj4);
    hAbsorb->Add(catHist1,detHist1,1,-1);
    hAbsorb->Scale(scale);
    //escapeSubtract1g->Scale(scale);
    hDiff->Add(hAbsorb,escapeSubtract1g,1,-1);
    hDiff->SetTitle(titleList[i]);
    gStyle->SetOptStat(1000000);
    hDiff->SetStats(1);
    hDiff->Draw("");

    cout<<"======== END DIFF PLOT FOR i="<<i<<" ========= "<<endl;
    
    file->Close();
    histListGammaR->Clear();
  } //--END GammaR Model Loop
  */
  ////////c1->SaveAs("GEMTRDAluminumScanRegularR.pdf");
  /////////c1r->SaveAs("GEMTRDAluminumScanRegularRRatios.pdf");
  //c1r->SaveAs("GEMTRDAluminumScanRegularRRatios.C");
  //////c2->SaveAs("GEMTRDAluminumScanTransparentR_v3.pdf");
  //////c2d->SaveAs("GEMTRDAluminumScanTransparentRDiffIntegrals_v3.pdf");
  //////////c2->SaveAs("GEMTRDAluminumScanTransparentR.C");
  //c2r->SaveAs("GEMTRDAluminumScanTransparentRRatios.C");
  //////////c3->SaveAs("GEMTRDAluminumScanGammaR.pdf");
  ///////////c3r->SaveAs("GEMTRDAluminumScanGammaRRatios.pdf");
  //c3r->SaveAs("GEMTRDAluminumScanGammaRRatios.C");
  //c3gs->SaveAs("GEMTRDRatios.C");
  c4->SaveAs("GeantMaterialScanTransparentR_v1.pdf");
  c4d->SaveAs("GeantMaterialScanTransparentRDiffIntegrals_v1.pdf");
}
