#include <vector>
#include <fstream>
#include <iostream>
//#include <filesystem>
#include <TTree.h>
#include <TMath.h>
#include <TStopwatch.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TList.h>
#include <TPaveStats.h>
#include <TChain.h>
#include <TH1.h>
#include <TH2.h>
#include <TF1.h>
#include <TFile.h>
#include <TLine.h>
#include <TList.h>
#include <TObject.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TProfile.h>

void trd_HistMerge(){
	
  bool makeTimeDistributions=true;
  
	TString rootFilesGEM[] = {"RootOutput/cern24/merged/Run_005284_2012810Entries_Output.root", "RootOutput/cern24/merged/Run_005256_129038Entries_Output.root", "RootOutput/cern24/merged/Run_005254_88047Entries_Output.root", "RootOutput/cern24/Run_005257_Output.root", "RootOutput/cern24/merged/Run_005306_559615Entries_Output.root", "RootOutput/ps25/Run_006268_Output.root", "RootOutput/fermiMerged/Run_003202_513789Entries_Output.root"};
	TString rootFilesMMG[] = {"RootOutput/cern24/merged/Run_005284_2012810Entries_Output.root", "RootOutput/cern24/merged/Run_005256_129038Entries_Output.root", "RootOutput/cern24/merged/Run_005254_88047Entries_Output.root", "RootOutput/cern24/Run_005257_Output.root", "RootOutput/cern24/merged/Run_005306_559615Entries_Output.root", "RootOutput/ps25/Run_006268_Output.root", "RootOutput/fermiMerged/Run_003202_513789Entries_Output.root"};
  
  
  TList *histListGEM = new TList;
  TList *histListGEM2 = new TList;
  TList *histListMMG = new TList;
  TList *histListMMG2 = new TList;
	TString name1 = "f125_el";
	TString name2 = "mmg1_f125_el";
	TString name3 = "f125_el_amp2d";
  TString name4 = "mmg1_f125_el_amp2d";
	
	int colorList[] = {94,2,209,6,7,1,4,51};
	TString legendListGEM[] = {"CERN 6400V/3380V Xe(1st Bottle)","CERN 6350V/3350V Xe(1st Bottle)","CERN 6300V/3300V Xe(1st Bottle)","CERN 6400V/3400V Xe(1st Bottle)","CERN 6400V/3380V Xe (2nd Bottle)","PS25 6300V/3300V Xe (100CCPM)","FERMI 6200V/3200V Xe"};
  TString legendListMMG[] = {"CERN 5100V/1630V Xe(1st Bottle)","CERN 5000V/1580V Xe(1st Bottle)","CERN 5000V/1560V Xe(1st Bottle)","CERN 5000V/1580V Xe(1st Bottle)","CERN 5100V/1630V Xe (2nd Bottle)","PS25 5000V/1550V Xe (100CCPM)","FERMI 4825V/625V Xe"};
  
	TLegend *l1 = new TLegend(0.7, 0.65, 0.9, 0.9);
  TLegend *l2 = new TLegend(0.7, 0.65, 0.9, 0.9);
  
  //-- Triple GEM-TRD
	for (int i=0; i<sizeof(rootFilesGEM)/sizeof(rootFilesGEM[0]); i++) {
		const TString& rootFile = rootFilesGEM[i];
		TFile *file = TFile::Open(rootFile, "READ");
		TList *HistDQM = (TList *)file->Get("HistDQM");
		TIter next(HistDQM);
		
		while (TH1 *readObject = dynamic_cast<TH1*>(next())) {
			TString histName = readObject->GetName();
			if (histName == name1) {
				readObject->SetLineColor(colorList[i]);
				readObject->SetLineWidth(2);
				double elScaleFactor = 1./readObject->GetEntries();
				readObject->Scale(elScaleFactor);
				histListGEM->Add(readObject);
				l1->AddEntry(readObject, legendListGEM[i], "lp");
			}
    }
		file->Close();
	}
  
  //-- MMG1-TRD
  for (int i=0; i<sizeof(rootFilesMMG)/sizeof(rootFilesMMG[0]); i++) {
    const TString& rootFile = rootFilesMMG[i];
    TFile *file = TFile::Open(rootFile, "READ");
    TList *HistDQM = (TList *)file->Get("HistDQM");
    TIter next(HistDQM);
    
    while (TH1 *readObject = dynamic_cast<TH1*>(next())) {
      TString histName = readObject->GetName();
      if (histName == name2) {
        readObject->SetLineColor(colorList[i]);
        readObject->SetLineWidth(2);
        double elScaleFactor = 1./readObject->GetEntries();
        readObject->Scale(elScaleFactor);
        histListMMG->Add(readObject);
        l2->AddEntry(readObject, legendListMMG[i], "lp");
      } 
    }
    file->Close();
  }
	
	TCanvas *c1 = new TCanvas("c1","GEMTRD ADC Distributions at Varied HV in Xe", 1600, 1000);
	gStyle->SetOptStat(00000);
	c1->cd();
	gPad->SetLogy();
	gPad->SetGridx();
 	gPad->SetGridy();
	TH1 *firstHist1 = (TH1 *)histListGEM->First();
  if (firstHist1) {
    firstHist1->GetXaxis()->SetTitle("ADC amplitude");
    firstHist1->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist1->SetMaximum(1);
    firstHist1->SetTitle("GEMTRD ADC Distributions in XeCO2");
  }
	histListGEM->Draw("same");
  l1->Draw();
	c1->SaveAs("GEMTRD_ADC_Xe_Comparison_v1.png");
  
  TCanvas *c2 = new TCanvas("c2","MMG1-TRD ADC Distributions at Varied HV in Xe", 1600, 1000);
  c2->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  TH1 *firstHist2 = (TH1 *)histListMMG->First();
  if (firstHist2) {
    firstHist2->GetXaxis()->SetTitle("ADC amplitude");
    firstHist2->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist2->SetMaximum(1);
    firstHist2->SetTitle("MMG1-TRD ADC Distributions in XeCO2");
  }
  histListMMG->Draw("same");
  l2->Draw();
  c2->SaveAs("MMG1TRD_ADC_Xe_Comparison_v1.png");
  
  if (makeTimeDistributions)
 {
  
  TList *HistDQM;
	double TFScaleFactor = -1.;
  
  //TFile *file0 = TFile::Open("RootOutput/ps25/Run_006269_Output.root");
  TFile *file0 = TFile::Open(rootFilesGEM[0]);
	HistDQM = (TList *)file0->Get("HistDQM");
  
  TObject *objg0 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g0 = (TH2 *)objg0;
  TFScaleFactor = 1./g0->GetEntries();
  g0->Scale(TFScaleFactor);
  g0->RebinX(4);
  TH1D *g_0 = g0->ProjectionX(legendListGEM[0],80,160);
  g_0->SetLineColor(94);
  g_0->SetMarkerStyle(20); //filled circle
  g_0->SetMarkerColor(94);
  g_0->SetDirectory(0);
  
  TObject *objm0 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m0 = (TH2 *)objm0;
  TFScaleFactor = 1./m0->GetEntries();
  m0->Scale(TFScaleFactor);
  m0->RebinX(4);
  TH1D *m_0 = m0->ProjectionX(legendListMMG[0],80,160);
  m_0->SetLineColor(94);
  m_0->SetMarkerStyle(20); //filled circle
  m_0->SetMarkerColor(94);
  m_0->SetDirectory(0);
  
  
  TFile *file1 = TFile::Open(rootFilesGEM[1]);
	HistDQM = (TList *)file1->Get("HistDQM");
  
  TObject *objg1 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g1 = (TH2 *)objg1;
  TFScaleFactor = 1./g1->GetEntries();
  g1->Scale(TFScaleFactor);
  g1->RebinX(4);
  TH1D *g_1 = g1->ProjectionX(legendListGEM[1],80,160);
  g_1->SetLineColor(2);
  g_1->SetMarkerStyle(20); //filled circle
  g_1->SetMarkerColor(2);
  g_1->SetDirectory(0);

  TObject *objm1 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m1 = (TH2 *)objm1;
  TFScaleFactor = 1./m1->GetEntries();
  m1->Scale(TFScaleFactor);
  m1->RebinX(4);
  TH1D *m_1 = m1->ProjectionX(legendListMMG[1],80,160);
  m_1->SetLineColor(2);
  m_1->SetMarkerStyle(20); //filled circle
  m_1->SetMarkerColor(2);
  m_1->SetDirectory(0);
  
  
  TFile *file2 = TFile::Open(rootFilesGEM[2]);
	HistDQM = (TList *)file2->Get("HistDQM");
  
  TObject *objg2 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g2 = (TH2 *)objg2;
  TFScaleFactor = 1./g2->GetEntries();
  g2->Scale(TFScaleFactor);
  g2->RebinX(4);
  TH1D *g_2 = g2->ProjectionX(legendListGEM[2],80,160);
  g_2->SetLineColor(209);
  g_2->SetMarkerStyle(20); //filled circle
  g_2->SetMarkerColor(209);
  g_2->SetDirectory(0);

  TObject *objm2 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m2 = (TH2 *)objm2;
  TFScaleFactor = 1./m2->GetEntries();
  m2->Scale(TFScaleFactor);
  m2->RebinX(4);
  TH1D *m_2 = m2->ProjectionX(legendListMMG[2],80,160);
  m_2->SetLineColor(209);
  m_2->SetMarkerStyle(20); //filled circle
  m_2->SetMarkerColor(209);
  m_2->SetDirectory(0);
  
  
  TFile *file3 = TFile::Open(rootFilesGEM[3]);
	HistDQM = (TList *)file3->Get("HistDQM");
  
  TObject *objg3 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g3 = (TH2 *)objg3;
  TFScaleFactor = 1./g3->GetEntries();
  g3->Scale(TFScaleFactor);
  g3->RebinX(4);
  TH1D *g_3 = g3->ProjectionX(legendListGEM[3],80,160);
  g_3->SetLineColor(6);
  g_3->SetMarkerStyle(20); //filled circle
  g_3->SetMarkerColor(6);
  g_3->SetDirectory(0);
  
  TObject *objm3 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m3 = (TH2 *)objm3;
  TFScaleFactor = 1./m3->GetEntries();
  m3->Scale(TFScaleFactor);
  m3->RebinX(4);
  TH1D *m_3 = m3->ProjectionX(legendListMMG[3],80,160);
  m_3->SetLineColor(6);
  m_3->SetMarkerStyle(20); //filled circle
  m_3->SetMarkerColor(6);
  m_3->SetDirectory(0);
  
  
  TFile *file4 = TFile::Open(rootFilesGEM[4]);
	HistDQM = (TList *)file4->Get("HistDQM");
  
  TObject *objg4 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g4 = (TH2 *)objg4;
  TFScaleFactor = 1./g4->GetEntries();
  g4->Scale(TFScaleFactor);
  g4->RebinX(4);
  TH1D *g_4 = g4->ProjectionX(legendListGEM[4],80,160);
  g_4->SetLineColor(7);
  g_4->SetMarkerStyle(20); //filled circle
  g_4->SetMarkerColor(7);
  g_4->SetDirectory(0);
  
  TObject *objm4 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m4 = (TH2 *)objm4;
  TFScaleFactor = 1./m4->GetEntries();
  m4->Scale(TFScaleFactor);
  m4->RebinX(4);
  TH1D *m_4 = m4->ProjectionX(legendListMMG[4],80,160);
  m_4->SetLineColor(7);
  m_4->SetMarkerStyle(20); //filled circle
  m_4->SetMarkerColor(7);
  m_4->SetDirectory(0);
  
  
  TFile *file5 = TFile::Open(rootFilesGEM[5]);
	HistDQM = (TList *)file5->Get("HistDQM");
  
  TObject *objg5 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g5 = (TH2 *)objg5;
  TFScaleFactor = 1./g5->GetEntries();
  g5->Scale(TFScaleFactor);
  g5->RebinX(4);
  TH1D *g_5 = g5->ProjectionX(legendListGEM[5],60,180);
  g_5->SetLineColor(1);
  g_5->SetMarkerStyle(20); //filled circle
  g_5->SetMarkerColor(1);
  g_5->SetDirectory(0);

  TObject *objm5 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m5 = (TH2 *)objm5;
  TFScaleFactor = 1./m5->GetEntries();
  m5->Scale(TFScaleFactor);
  m5->RebinX(4);
  TH1D *m_5 = m5->ProjectionX(legendListMMG[5],60,180);
  m_5->SetLineColor(1);
  m_5->SetMarkerStyle(20); //filled circle
  m_5->SetMarkerColor(1);
  m_5->SetDirectory(0);
  
  
  TFile *file6 = TFile::Open(rootFilesGEM[6]);
	HistDQM = (TList *)file6->Get("HistDQM");
  
  TObject *objg6 = HistDQM->FindObject("f125_el_amp2ds");
  TH2 *g6 = (TH2 *)objg6;
  TFScaleFactor = 1./g6->GetEntries();
  g6->Scale(TFScaleFactor);
  g6->RebinX(4);
  TH1D *g_6 = g6->ProjectionX(legendListGEM[6],60,180);
  g_6->SetLineColor(4);
  g_6->SetMarkerStyle(20); //filled circle
  g_6->SetMarkerColor(4);
  g_6->SetDirectory(0);

  TObject *objm6 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TH2 *m6 = (TH2 *)objm6;
  TFScaleFactor = 1./m6->GetEntries();
  m6->Scale(TFScaleFactor);
  m6->RebinX(4);
  TH1D *m_6 = m6->ProjectionX(legendListMMG[6],60,180);
  m_6->SetLineColor(4);
  m_6->SetMarkerStyle(20); //filled circle
  m_6->SetMarkerColor(4);
  m_6->SetDirectory(0);
  
  
  TLegend *l3 = new TLegend(0.7, 0.65, 0.9, 0.9);
  TLegend *l4 = new TLegend(0.7, 0.65, 0.9, 0.9);
  TCanvas *c3 = new TCanvas("c3","GEMTRD Timing Distributions at Varied HV in Xe", 1600, 1000);
  c3->cd();
  gPad->SetGridy();
  l3->AddEntry(g_0,legendListGEM[0],"lp");
  l3->AddEntry(g_1,legendListGEM[1],"lp");
  l3->AddEntry(g_2,legendListGEM[2],"lp");
  l3->AddEntry(g_3,legendListGEM[3],"lp");
  l3->AddEntry(g_4,legendListGEM[4],"lp");
  l3->AddEntry(g_5,legendListGEM[5],"lp");
  l3->AddEntry(g_6,legendListGEM[6],"lp");
  g_0->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
  g_0->GetYaxis()->SetNdivisions(520);
  g_0->GetXaxis()->SetRangeUser(20,300);
  g_0->SetMaximum(g_0->GetMaximum()+15.);
  g_0->SetTitle("Triple GEM-TRD ADC Response in Time in XeCO2");
  g_0->Draw("");
  g_1->Draw("same");
  g_2->Draw("same");
  g_3->Draw("same");
  g_4->Draw("same");
  g_5->Draw("same");
  g_6->Draw("same");
  l3->Draw();
  c3->SaveAs("GEMTRD_Time_Xe_Comparison_v1.png");
  
  TCanvas *c4 = new TCanvas("c4","MMG1-TRD Timing Distributions at Varied HV in Xe", 1600, 1000);
  c4->cd();
  gPad->SetGridy();
  l4->AddEntry(m_0,legendListMMG[0],"lp");
  l4->AddEntry(m_1,legendListMMG[1],"lp");
  l4->AddEntry(m_2,legendListMMG[2],"lp");
  l4->AddEntry(m_3,legendListMMG[3],"lp");
  l4->AddEntry(m_4,legendListMMG[4],"lp");
  l4->AddEntry(m_5,legendListMMG[5],"lp");
  l4->AddEntry(m_6,legendListMMG[6],"lp");
  
  m_0->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
  m_0->GetYaxis()->SetNdivisions(520);
  m_0->GetXaxis()->SetRangeUser(20,300);
  m_0->SetMaximum(m_0->GetMaximum()+15.);
  m_0->SetTitle("MMG1-TRD ADC Response in Time in XeCO2");
  m_0->Draw("");
  m_1->Draw("same");
  m_2->Draw("same");
  m_3->Draw("same");
  m_4->Draw("same");
  m_5->Draw("same");
  m_6->Draw("same");
  l4->Draw();
  c4->SaveAs("MMG1TRD_Time_Xe_Comparison_v1.png");
  
  
  }  
}
