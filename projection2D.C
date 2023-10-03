#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
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

void projection2D(){
	
	//TString inputDir = "../fermiDataAnalysis/cherDownUpNoBoxOutput/RootOutput";
	TString rootFiles[] = {"Run003202_Output.root","Run003203_Output.root"};
	TList *mmg1List = new TList;
	TList *gemList = new TList;
	TList *mmg2List = new TList;
	TList *urwList = new TList;
	TString legendList[] = {"Foil Radiator (Electrons)","Foil Radiator (Pions)","No Radiator (Electrons)","No Radiator (Pions)"};
	TLegend *l1 = new TLegend(0.75, 0.65, 0.9, 0.9);
	TLegend *l2 = new TLegend(0.75, 0.65, 0.9, 0.9);
	TLegend *l3 = new TLegend(0.75, 0.65, 0.9, 0.9);
	TLegend *l4 = new TLegend(0.75, 0.65, 0.9, 0.9);
	l1->SetNColumns(2);
	l2->SetNColumns(2);
	l3->SetNColumns(2);
	l4->SetNColumns(2);
	
	for (int i=0; i<sizeof(rootFiles)/sizeof(rootFiles[0]); i++) {
		const TString& rootFile = rootFiles[i];
		TFile *file = TFile::Open(rootFile, "READ");
		TList *HistDQM = (TList *)file->Get("HistDQM");
		TIter next(HistDQM);
		
		while (TH1 *readObject = dynamic_cast<TH1*>(next())) {
			TString histName = readObject->GetName();
			//cout<<histName<<endl;
			if (histName == "mmg1_f125_el_amp2d") { //--MMG1 Electrons
				TH1D *Xprojection = ((TH2*)readObject)->ProjectionX();
				TH1D *XprojectionClone = new TH1D(*Xprojection);
				XprojectionClone->SetDirectory(0);
				XprojectionClone->SetLineColor(2);
				XprojectionClone->SetLineWidth(2);
				XprojectionClone->SetMarkerColor(2);
				XprojectionClone->SetMarkerStyle(8);
				if (i==1) XprojectionClone->SetMarkerStyle(4);
				double elScaleFactor = 1./XprojectionClone->GetEntries();
				XprojectionClone->Scale(elScaleFactor);
				mmg1List->Add(XprojectionClone);
				if (i==0) l1->AddEntry(XprojectionClone, legendList[i], "lp"); else if (i==1) l1->AddEntry(XprojectionClone, legendList[i+1], "lp");
				
			} else if (histName == "mmg1_f125_pi_amp2d") { //--MMG1 Pions
				TH1D *Xprojection = ((TH2*)readObject)->ProjectionX();
				TH1D *XprojectionClone = new TH1D(*Xprojection);
          		XprojectionClone->SetDirectory(0);
				XprojectionClone->SetLineColor(4);
          		XprojectionClone->SetLineWidth(2);
				XprojectionClone->SetMarkerColor(4);
				XprojectionClone->SetMarkerStyle(8);
				if (i==1) XprojectionClone->SetMarkerStyle(4);
				double piScaleFactor = 1./XprojectionClone->GetEntries();
          		XprojectionClone->Scale(piScaleFactor);
         		if (i==0) l1->AddEntry(XprojectionClone, legendList[i+1], "lp"); else if (i==1) l1->AddEntry(XprojectionClone, legendList[i+2], "lp");
         		mmg1List->Add(XprojectionClone);
				
			} else if (histName == "f125_el_amp2d") { //--GEMTRD Electrons
				TH1D *Xprojection = ((TH2*)readObject)->ProjectionX();
				TH1D *XprojectionClone = new TH1D(*Xprojection);
                XprojectionClone->SetDirectory(0);
				XprojectionClone->SetLineColor(2);
                XprojectionClone->SetLineWidth(2);
				XprojectionClone->SetMarkerColor(2);
				XprojectionClone->SetMarkerStyle(8);
				if (i==1) XprojectionClone->SetMarkerStyle(4);
                double elScaleFactor = 1./XprojectionClone->GetEntries();
                XprojectionClone->Scale(elScaleFactor);
                if (i==0) l2->AddEntry(XprojectionClone, legendList[i], "lp"); else if (i==1) l2->AddEntry(XprojectionClone, legendList[i+1], "lp");
                gemList->Add(XprojectionClone);
				
            } else if (histName == "f125_pi_amp2d") { //--GEMTRD Pions
                TH1D *Xprojection = ((TH2*)readObject)->ProjectionX();
				TH1D *XprojectionClone = new TH1D(*Xprojection);
                XprojectionClone->SetDirectory(0);
				XprojectionClone->SetLineColor(4);
                XprojectionClone->SetLineWidth(2);
				XprojectionClone->SetMarkerColor(4);
				XprojectionClone->SetMarkerStyle(8);
				if (i==1) XprojectionClone->SetMarkerStyle(4);
                double piScaleFactor = 1./XprojectionClone->GetEntries();
                XprojectionClone->Scale(piScaleFactor);
                if (i==0) l2->AddEntry(XprojectionClone, legendList[i+1], "lp"); else if (i==1) l2->AddEntry(XprojectionClone, legendList[i+2], "lp");
                gemList->Add(XprojectionClone);
				
			} else if (histName == "mmg2_f125_el_amp2d") { //--MMG2 Electrons
                TH1D *Xprojection = ((TH2*)readObject)->ProjectionX();
                TH1D *XprojectionClone = new TH1D(*Xprojection);
                XprojectionClone->SetDirectory(0);
                XprojectionClone->SetLineColor(2);
                XprojectionClone->SetLineWidth(2);
				XprojectionClone->SetMarkerColor(2);
				XprojectionClone->SetMarkerStyle(8);
                double elScaleFactor = 1./XprojectionClone->GetEntries();
                XprojectionClone->Scale(elScaleFactor);
                l3->AddEntry(XprojectionClone, legendList[i], "lp");
                mmg2List->Add(XprojectionClone);

            } else if (histName == "mmg2_f125_pi_amp2d") { //--MMG2 Pions
                TH1D *Xprojection = ((TH2*)readObject)->ProjectionX();
                TH1D *XprojectionClone = new TH1D(*Xprojection);
                XprojectionClone->SetDirectory(0);
                XprojectionClone->SetLineColor(4);
                XprojectionClone->SetLineWidth(2);
				XprojectionClone->SetMarkerColor(4);
				XprojectionClone->SetMarkerStyle(8);
                double piScaleFactor = 1./XprojectionClone->GetEntries();
                XprojectionClone->Scale(piScaleFactor);
                l3->AddEntry(XprojectionClone, legendList[i+1], "lp");
                mmg2List->Add(XprojectionClone);
                
            }
            else if (histName == "urw_f125_el_amp2d") { //--URW Electrons
                TH1D *Xprojection = ((TH2*)readObject)->ProjectionX();
                TH1D *XprojectionClone = new TH1D(*Xprojection);
                XprojectionClone->SetDirectory(0);
                XprojectionClone->SetLineColor(2);
                XprojectionClone->SetLineWidth(2);
				XprojectionClone->SetMarkerColor(2);
				XprojectionClone->SetMarkerStyle(8);
				if (i==1) XprojectionClone->SetMarkerStyle(4);
                double elScaleFactor = 1./XprojectionClone->GetEntries();
                XprojectionClone->Scale(elScaleFactor);
                if (i==0) l4->AddEntry(XprojectionClone, legendList[i], "lp"); else if (i==1) l4->AddEntry(XprojectionClone, legendList[i+1], "lp");
                urwList->Add(XprojectionClone);
				
            } else if (histName == "urw_f125_pi_amp2d") { //--URW Pions
                TH1D *Xprojection = ((TH2*)readObject)->ProjectionX();
                TH1D *XprojectionClone = new TH1D(*Xprojection);
                XprojectionClone->SetDirectory(0);
                XprojectionClone->SetLineColor(4);
                XprojectionClone->SetLineWidth(2);
				XprojectionClone->SetMarkerColor(4);
				XprojectionClone->SetMarkerStyle(8);
				if (i==1) XprojectionClone->SetMarkerStyle(4);
                double piScaleFactor = 1./XprojectionClone->GetEntries();
                XprojectionClone->Scale(piScaleFactor);
                if (i==0) l4->AddEntry(XprojectionClone, legendList[i+1], "lp"); else if (i==1) l4->AddEntry(XprojectionClone, legendList[i+2], "lp");
                urwList->Add(XprojectionClone);
    			
            }
		}
		cout<<"Close root file"<<endl;
		file->Close();
	}
	
	cout<<"Create TCanvases"<<endl;
	TCanvas *c1 = new TCanvas("c1","MMG-1", 1200, 800);
	TCanvas *c2 = new TCanvas("c2","GEMTRD", 1200, 800);
	TCanvas *c3 = new TCanvas("c3","MMG-2", 1200, 800);
	TCanvas *c4 = new TCanvas("c4","uRWell-TRD", 1200, 800);
	gStyle->SetOptStat(0);
	
	//TIter next(mmg1List);
	//while (TObject *listObj = next()) {
	//	cout<<listObj->GetName()<<"\n"<<endl;
	//}
	
	c1->cd();
	if (!mmg1List) {
		std::cerr<<"mmg1List is NULL"<<std::endl;
		return;
	}
	if (mmg1List->IsEmpty()) {
		std::cerr<<"mmg1List is empty"<<std::endl;
		return;
	}
	
	TH1 *firstmmg1Hist = (TH1 *)mmg1List->First();
    if (firstmmg1Hist) {
        firstmmg1Hist->GetXaxis()->SetTitle("Time Response (8ns)");
        firstmmg1Hist->GetYaxis()->SetTitle("numEntries / Total Hits");
        firstmmg1Hist->SetTitle("10GeV XeCO2: MMG1-TRD at 4825V/625V");
    }
	mmg1List->Draw("same");
    l1->Draw();
	c1->SaveAs("PNGs/Run_003202_003203_2DProjection_mmg1.png");
	
    c2->cd();
	if (!gemList) {
        std::cerr<<"gemList is NULL"<<std::endl;
        return;
    }
    if (gemList->IsEmpty()) {
        std::cerr<<"gemList is empty"<<std::endl;
        return;
    }
	
	TH1 *firstgemHist = (TH1 *)gemList->First();
    if (firstgemHist) {
        firstgemHist->GetXaxis()->SetTitle("Time Response (8ns)");
        firstgemHist->GetYaxis()->SetTitle("numEntries / Total Hits");
        firstgemHist->SetTitle("10GeV XeCO2: GEM-TRD at 6200V/3200V");
    }
	gemList->Draw("same");
	l2->Draw();
	c2->SaveAs("PNGs/Run_003202_003203_2DProjection_gem.png");
	
	c3->cd();
	if (!mmg2List) {
        std::cerr<<"mmg2List is NULL"<<std::endl;
        //return;
    }
    if (mmg2List->IsEmpty()) {
        std::cerr<<"mmg2List is empty"<<std::endl;
        //return;
    }
	
	TH1 *firstmmg2Hist = (TH1 *)mmg2List->First();
    if (firstmmg2Hist) {
        firstmmg2Hist->GetXaxis()->SetTitle("Time Response (8ns)");
        firstmmg2Hist->GetYaxis()->SetTitle("numEntries / Total Hits");
        firstmmg2Hist->SetTitle("10GeV XeCO2: MMG2-TRD at 3400V/605V");
    }
    //mmg2List->Draw("same");
    //l3->Draw();
	//c3->SaveAs("PNGs/Run_003288_2DProjection_mmg2.png");
	
	c4->cd();
	if (!urwList) {
        std::cerr<<"urwList is NULL"<<std::endl;
        return;
    }
    if (urwList->IsEmpty()) {
        std::cerr<<"urwList is empty"<<std::endl;
        return;
    }
	
	TH1 *firsturwHist = (TH1 *)urwList->First();
    if (firsturwHist) {
        firsturwHist->GetXaxis()->SetTitle("Time Response (8ns)");
        firsturwHist->GetYaxis()->SetTitle("numEntries / Total Hits");
        firsturwHist->SetTitle("10GeV XeCO2: uRWell-TRD at 4500V/495V");
    }
    urwList->Draw("same");
    l4->Draw();
	c4->SaveAs("PNGs/Run_003202_003203_2DProjection_urw.png");
	
}
