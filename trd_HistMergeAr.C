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

void trd_HistMergeAr(){
	
	TString rootFilesGEM[] = {"RootOutput/ps25/Run_006274_Output.root", "RootOutput/ps25/Run_006326_Output.root", "RootOutput/ps25/Run_006357_Output.root"};
  //TString rootFilesGEM[] = {"RootOutput/ps25/Run_006290_Output.root", "RootOutput/ps25/Run_006291_Output.root", "RootOutput/ps25/Run_006295_Output.root"};
	//TString rootFilesMMG[] = {"RootOutput/cern24/merged/Run_005284_2012810Entries_Output.root", "RootOutput/cern24/merged/Run_005256_129038Entries_Output.root", "RootOutput/cern24/merged/Run_005254_88047Entries_Output.root", "RootOutput/cern24/Run_005257_Output.root", "RootOutput/cern24/merged/Run_005306_559615Entries_Output.root", "RootOutput/ps25/Run_006268_Output.root", "RootOutput/fermiMerged/Run_003202_513789Entries_Output.root"};
  
  
  TList *histListGEM = new TList;
  //TList *histListGEM2 = new TList;
  TList *histListMMG = new TList;
  //TList *histListMMG2 = new TList;
  TList *histListURW = new TList;
  //TList *histListURW2 = new TList;
  
	TString name1 = "f125_el";
	TString name2 = "mmg1_f125_el";
	TString name3 = "f125_el_amp2d";
  TString name4 = "mmg1_f125_el_amp2d";
  TString name5 = "urw_f125_el_x";
	
	int colorList[] = {94,2,209,4,7,1,6,51};
  TString legendListGEM[] = {"5um Copper, 100CCPM, Low LV With Rad","5um Copper, 100CCPM, High LV No Rad","0.1um Aluminum, 100CCPM, High LV With Rad","0.1um Aluminum, 100CCPM, Low LV With Rad","","","",""};
	//TString legendListGEM[] = {"Lower LV, Old Pedestal","Higher LV, Old Pedestal","Higher LV, New Pedestal","","","","",""};
  //TString legendListMMG[] = {"CERN 5100V/1630V Xe(1st Bottle)","CERN 5000V/1580V Xe(1st Bottle)","CERN 5000V/1560V Xe(1st Bottle)","CERN 5000V/1580V Xe(1st Bottle)","CERN 5100V/1630V Xe (2nd Bottle)","PS25 5000V/1550V Xe (100CCPM)","FERMI 4825V/625V Xe"};
  
	TLegend *l1 = new TLegend(0.59, 0.7, 0.9, 0.9);
  TLegend *l2 = new TLegend(0.59, 0.7, 0.9, 0.9);
	TLegend *l3 = new TLegend(0.7, 0.65, 0.9, 0.9);
  TLegend *l4 = new TLegend(0.7, 0.65, 0.9, 0.9);
  TLegend *l5 = new TLegend(0.7, 0.65, 0.9, 0.9);
  
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
      else if (histName == name2) {
        readObject->SetLineColor(colorList[i]);
        readObject->SetLineWidth(2);
        double elScaleFactor = 1./readObject->GetEntries();
        readObject->Scale(elScaleFactor);
        histListMMG->Add(readObject);
        l2->AddEntry(readObject, legendListGEM[i], "lp");
      }
      else if (histName == name5) {
        readObject->SetLineColor(colorList[i]);
        readObject->SetLineWidth(2);
        double elScaleFactor = 1./readObject->GetEntries();
        readObject->Scale(elScaleFactor);
        histListURW->Add(readObject);
        l5->AddEntry(readObject, legendListGEM[i], "lp");
      }
    }
    
    /*
    while (TH2 *readObject = dynamic_cast<TH2*>(next())) {
      TString histName = readObject->GetName();
      if (histName == name3) {
        cout<<"NAME3 = "<<readObject->GetName()<<endl;
        double amp2dScaleFactor = 1./readObject->GetEntries();
        readObject->Scale(amp2dScaleFactor);
        readObject->RebinX(4);
        char gemName[80]; sprintf(gemName,"amp2d_%i",i);
        TH1D *amp2d = readObject->ProjectionX(gemName,80,160);
        amp2d->SetLineColor(colorList[i]);
        amp2d->SetMarkerStyle(20); //filled circle
        amp2d->SetMarkerColor(colorList[i]);
        //tf_1->SetDirectory(0);
        histListGEM2->Add(amp2d);
        l3->AddEntry(amp2d, legendListGEM[i], "lp");
      }
		}
    */
		file->Close();
	}
  
	TCanvas *c1 = new TCanvas("c1","GEMTRD ADC Distributions", 1600, 1000);
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
    //firstHist1->SetTitle("GEMTRD ADC Distributions in XeCO2, 6400V/3380V");
    firstHist1->SetTitle("GEMTRD ADC Distributions in Ar:CO2 80:20, 6100V/3100V");
  }
	histListGEM->Draw("same");
  l1->Draw();
	c1->SaveAs("GEMTRD_ADC_CAT_Comparison_v1.png");
  
  TCanvas *c2 = new TCanvas("c2","MMG1-TRD ADC Distributions", 1600, 1000);
  c2->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  TH1 *firstHist2 = (TH1 *)histListMMG->First();
  if (firstHist2) {
    firstHist2->GetXaxis()->SetTitle("ADC amplitude");
    firstHist2->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist2->SetMaximum(1);
    //firstHist2->SetTitle("MMG1-TRD ADC Distributions in XeCO2, 5100V/1630V");
    firstHist2->SetTitle("MMG1-TRD ADC Distributions in Ar:CO2 80:20, 4750V/1450V");
  }
  histListMMG->Draw("same");
  l2->Draw();
  c2->SaveAs("MMG1TRD_ADC_CAT_Comparison_v1.png");
  /*
  TCanvas *c3 = new TCanvas("c3","GEMTRD Timing Distributions at Varied HV in Xe", 1600, 1000);
  c3->cd();
  gPad->SetGridy();
  TH1 *firstHist3 = (TH1 *)histListGEM2->First();
  if (firstHist3) {
    firstHist3->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
    firstHist3->GetYaxis()->SetNdivisions(520);
    firstHist3->GetXaxis()->SetRangeUser(20,200);
    firstHist3->SetTitle("GEM-TRD ADC Response in Time in XeCO2");
  }
  histListGEM2->Draw("same");
  l3->Draw();
  c3->SaveAs("GEMTRD_Time_Xe_Comparison_v1.png");
  
  TCanvas *c4 = new TCanvas("c4","MMG1-TRD Timing Distributions at Varied HV in Xe", 1600, 1000);
  c4->cd();
  gPad->SetGridy();
  TH1 *firstHist4 = (TH1 *)histListMMG2->First();
  if (firstHist4) {
    firstHist4->GetYaxis()->SetTitle("ADC Amplitude (Counts / numEntries)");
    firstHist4->GetYaxis()->SetNdivisions(520);
    firstHist4->GetXaxis()->SetRangeUser(20,200);
    firstHist4->SetTitle("MMG1-TRD ADC Response in Time in XeCO2");
  }
  histListMMG2->Draw("same");
  l4->Draw();
  c4->SaveAs("MMG1TRD_Time_Xe_Comparison_v1.png");
 */
  /*
  TCanvas *c5 = new TCanvas("c5","uRWell-TRD ADC Distributions for LV / Pedestal Changes", 1600, 1000);
  c5->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  TH1 *firstHist5 = (TH1 *)histListURW->First();
  if (firstHist5) {
    firstHist5->GetXaxis()->SetTitle("ADC amplitude");
    firstHist5->GetYaxis()->SetTitle("Counts / numEntries");
    firstHist5->SetMaximum(1);
    firstHist5->SetTitle("uRWell-TRD ADC Distributions in XeCO2, 4455V/1300V/920V/520V");
  }
  histListURW->Draw("same");
  l5->Draw();
  c5->SaveAs("URWTRD_ADC_LV_Comparison_v1.png");
 */ 
}
