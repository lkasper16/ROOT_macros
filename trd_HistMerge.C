#include <vector>
#include <fstream>
#include <iostream>
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


int FindLeadingEdge(TH1 *h, double frac=0.18) {
  double thresh = frac*h->GetMaximum();
  for (int i=1;i<=h->GetNbinsX();i++) {
    if (h->GetBinContent(i) >= thresh) return i;
  }
  return 1;
}


void ShiftHistogram(TH1 *h, int shift) {
  int nx = h->GetNbinsX();
  std::vector<double> content(nx+2,0.);
  std::vector<double> error(nx+2,0.);
  for (int x=1;x<=nx;x++) {
    int j = x-shift;
    if (j>=1 && j<=nx) {
      content[j]=h->GetBinContent(x);
      error[j]=h->GetBinError(x);
    }
  }
  for (int x=1;x<=nx;x++) {
    h->SetBinContent(x,content[x]);
    h->SetBinError(x,error[x]);
  }
}

void AlignLeadingEdge(TH1 *reference, TH1 *h) {
  int ref = FindLeadingEdge(reference);
  int cur = FindLeadingEdge(h);
  ShiftHistogram(h, cur-ref);
}



void trd_HistMerge(){
	
  bool makeTimeDistributions=true;
  bool useMax=true;
  
	////TString rootFilesGEM[] = {"RootOutput/cern24/merged/Run_005284_3615629Entries_Output.root", "RootOutput/fermiMerged/Run_003202_513789Entries_Output.root","RootOutput/ps25/Run_006302_Output.root","RootOutput/ps26/Run_008229_Output.root","RootOutput/ps26/Run_008254_Output.root"};
	TString rootFilesGEM[] = {"RootOutput/ps26/Run_008242_Output.root","RootOutput/ps26/Run_008249_Output.root","RootOutput/ps26/Run_008246_Output.root","RootOutput/ps26/Run_008254_Output.root","RootOutput/ps26/Run_008235_Output.root"};
	//TString rootFilesGEM[] = {"RootOutput/ps26/Run_008229_Output.root","RootOutput/ps26/Run_008230_Output.root","RootOutput/ps26/Run_008234_Output.root","RootOutput/ps26/Run_008235_Output.root"};
  ////TString rootFilesMMG[] = {"RootOutput/cern24/merged/Run_005284_3615629Entries_Output.root", "RootOutput/fermiMerged/Run_003202_513789Entries_Output.root","RootOutput/ps25/Run_006302_Output.root","RootOutput/ps26/Run_008229_Output.root","RootOutput/ps26/Run_008254_Output.root"};
  TString rootFilesMMG[] = {"RootOutput/ps26/Run_008229_Output.root","RootOutput/ps26/Run_008230_Output.root","RootOutput/ps26/Run_008234_Output.root","RootOutput/ps26/Run_008235_Output.root","RootOutput/ps26/Run_008236_Output.root","RootOutput/ps26/Run_008237_Output.root","RootOutput/ps26/Run_008239_Output.root","RootOutput/ps26/Run_008242_Output.root"};
  TString rootFilesURW[] = {"RootOutput/ps25/Run_006302_Output.root","RootOutput/ps26/Run_008229_Output.root","RootOutput/ps26/Run_008254_Output.root"};
  //TString rootFilesURW[] = {"RootOutput/ps26/Run_008229_Output.root","RootOutput/ps26/Run_008230_Output.root","RootOutput/ps26/Run_008234_Output.root","RootOutput/ps26/Run_008235_Output.root","RootOutput/ps26/Run_008256_Output.root"};
  ////TString rootFilesURW[] = {"RootOutput/ps26/Run_008235_Output.root","RootOutput/ps26/Run_008236_Output.root","RootOutput/ps26/Run_008237_Output.root"};
  //TString rootFilesURW[] = {"RootOutput/ps26/Run_008257_Output.root","RootOutput/ps26/Run_008256_Output.root","RootOutput/ps26/Run_008254_Output.root","RootOutput/ps26/Run_008253_Output.root"};
  
  TList *histListGEM = new TList;
  TList *histListMMG = new TList;
  TList *histListURW = new TList;
  TString name1;
  TString name2;
  TString name3;
  if (useMax) {
    name1 = "f125_el_max";
    name2 = "mmg1_f125_el_max";
    name3 = "urw_f125_el_xmax";
  } else {
    name1 = "f125_el";
    name2 = "mmg1_f125_el";
    name3 = "urw_f125_el_x";
  }
  
	int colorList[] = {1,2,209,6,4,94,7,51,28};
  int markerList[] = {3,4,25,27,46,42,30,44,35};
  
	////TString legendListGEM[] = {"CERN Xe:CO_{2}, 6400V/3380V","FERMI Xe:CO_{2}, 6200V/3200V","PS25 Xe:CO_{2}, 6400V/3475V", "PS26 Xe:ISO, 6400V/3475V", "PS26 Xe:ISO, 6400V/450/425V/390V"};
	TString legendListGEM[] = {"2.75 kV/cm","3.00 kV/cm","3.25 kV/cm","3.50 kV/cm","3.74 kV/cm"};
  //TString legendListGEM[] = {"448V / 411V / 374V","450V / 415V / 380V","450V / 420V / 385V","450V / 425V / 390V"};
  ////TString legendListMMG[] = {"CERN Xe:CO_{2}, 5100V/1630V","FERMI Xe:CO_{2}, 4825V/625V","PS25 Xe:CO_{2}, 5150V/1675V","PS26 Xe:ISO, 5150V/1675V","PS26 Xe:ISO, 5195V/1735V"};
  TString legendListMMG[] = {"1675V","1685V","1695V","1700V","1710V","1720V","1730V","1735V"};
  TString legendListURW[] = {"PS25 Xe:CO_{2}, 4465V/1310V/925V/525V","PS26 Xe:ISO, 4465V/1310V/925V/525V","PS26 Xe:ISO, 4515V/1410V/1000V/525V"};
  //TString legendListURW[] = {"380V","390V","395V","400V","410V"};
  ////TString legendListURW[] = {"525V","530V","535V"};
  //TString legendListURW[] = {"2.325 kV/cm","2.35 kV/cm","2.375 kV/cm","2.4 kV/cm"};
  
	//TLegend *l1 = new TLegend(0.35, 0.58, 0.9, 0.865);
	//TLegend *l1 = new TLegend(0.63, 0.56, 0.9, 0.865);
  TLegend *l1 = new TLegend(0.5, 0.66, 0.9, 0.865);
  //TLegend *l2 = new TLegend(0.48, 0.61, 0.9, 0.865);
  TLegend *l2 = new TLegend(0.147, 0.75, 0.897, 0.86);
  TLegend *l3 = new TLegend(0.4, 0.7, 0.9, 0.865);
  //TLegend *l3 = new TLegend(0.42, 0.68, 0.9, 0.865);
  //TLegend *l3 = new TLegend(0.67, 0.6, 0.9, 0.865);
  
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
        readObject->SetMarkerStyle(markerList[i]);
        readObject->SetMarkerColor(colorList[i]);
        readObject->SetMarkerSize(2);
				double elScaleFactor = 1./readObject->GetEntries();
				readObject->Scale(elScaleFactor);
        /*if (i>1)*/ readObject->RebinX(5);
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
        readObject->SetMarkerStyle(markerList[i]);
        readObject->SetMarkerColor(colorList[i]);
        readObject->SetMarkerSize(2);
        double elScaleFactor = 1./readObject->GetEntries();
        readObject->Scale(elScaleFactor);
        /*if (i>1)*/ readObject->RebinX(5);
        //if (i!=1){
        histListMMG->Add(readObject);
        l2->AddEntry(readObject, legendListMMG[i], "lp");
        //}
      } 
    }
    file->Close();
  }
  
  //-- uRWell-TRD
  for (int i=0; i<sizeof(rootFilesURW)/sizeof(rootFilesURW[0]); i++) {
    const TString& rootFile = rootFilesURW[i];
    TFile *file = TFile::Open(rootFile, "READ");
    TList *HistDQM = (TList *)file->Get("HistDQM");
    TIter next(HistDQM);
    
    while (TH1 *readObject = dynamic_cast<TH1*>(next())) {
      TString histName = readObject->GetName();
      if (histName == name3) {
        readObject->SetLineColor(colorList[i]);
        readObject->SetLineWidth(2);
        readObject->SetMarkerStyle(markerList[i]);
        readObject->SetMarkerColor(colorList[i]);
        readObject->SetMarkerSize(2);
        double elScaleFactor = 1./readObject->GetEntries();
        readObject->Scale(elScaleFactor);
        readObject->RebinX(5);
        histListURW->Add(readObject);
        l3->AddEntry(readObject, legendListURW[i], "lp");
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
  gPad->SetTopMargin(0.135);
	TH1 *firstHist1 = (TH1 *)histListGEM->First();
  if (firstHist1) {
    if (useMax) {
      firstHist1->GetXaxis()->SetTitle("Maximum Pulse Amplitude [fADC Units]");
      //firstHist1->SetTitle("#splitline{Triple-GEM-TRD Maximum ADC Value}{in Xe Mixtures with Varied HVs}");
      firstHist1->SetTitle("#splitline{Triple-GEM-TRD Maximum ADC Value in Xe:ISO 90:10}{GEM dVs: 450V/425V/390V, Transfer Field Scan}");
      //firstHist1->SetTitle("#splitline{Triple-GEM-TRD Maximum ADC Value in Xe:ISO 90:10}{DF:1.7kV/cm TF:3.74kV/cm, GEM dV Scan}");
    } else {
      firstHist1->GetXaxis()->SetTitle("Pulse Peak Amplitude [fADC Units]");
      //firstHist1->SetTitle("#splitline{Triple-GEM-TRD ADC Distributions}{in Xe Mixtures with Varied HVs}");
      firstHist1->SetTitle("#splitline{Triple-GEM-TRD ADC Distributions in Xe:ISO 90:10}{GEM dVs: 450V/425V/390V, Transfer Field Scan}");
      //firstHist1->SetTitle("#splitline{Triple-GEM-TRD ADC Distributions in Xe:ISO 90:10}{DF:1.7kV/cm TF:3.74kV/cm, GEM dV Scan}");
    }
    firstHist1->GetYaxis()->SetTitle("Pulses / numEvents");
    firstHist1->SetMaximum(1);
    firstHist1->GetXaxis()->SetTitleSize(0.045);
    firstHist1->GetXaxis()->SetLabelSize(0.042);
    firstHist1->GetYaxis()->SetTitleSize(0.045);
    firstHist1->GetYaxis()->SetLabelSize(0.042);
    firstHist1->GetYaxis()->SetTitleOffset(0.85);
  }
	histListGEM->Draw("same");
  l1->SetHeader("Transfer Fields","C");
  l1->SetNColumns(2);
  l1->SetTextSize(0.042);
  l1->Draw();
  gPad->Modified();
  gPad->Update();
  if (useMax) {
    c1->SaveAs("GEMTRD_Max_ADC_Xe_Comparison_v2.C");
    c1->SaveAs("GEMTRD_Max_ADC_Xe_Comparison_v2.pdf");
  } else {
	  c1->SaveAs("GEMTRD_ADC_Xe_Comparison_v2.C");
    c1->SaveAs("GEMTRD_ADC_Xe_Comparison_v2.pdf");
  }
  
  TCanvas *c2 = new TCanvas("c2","MMG1-TRD ADC Distributions at Varied HV in Xe", 1600, 1000);
  c2->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetTopMargin(0.135);
  TH1 *firstHist2 = (TH1 *)histListMMG->First();
  if (firstHist2) {
    if (useMax) {
      firstHist2->GetXaxis()->SetTitle("Maximum Pulse Amplitude [fADC Units]");
      //firstHist2->SetTitle("#splitline{MMG1-TRD Maximum ADC Value}{in Xe Mixtures with Varied HVs}");
      firstHist2->SetTitle("#splitline{MMG1-TRD Maximum ADC Value in Xe:ISO 90:10}{DF:1.35kV/cm, Amplification HV Scan}");
    } else {
      firstHist2->GetXaxis()->SetTitle("Pulse Peak Amplitude [fADC Units]");
      //firstHist2->SetTitle("#splitline{MMG1-TRD ADC Distributions}{in Xe Mixtures with Varied HVs}");
      firstHist2->SetTitle("#splitline{MMG1-TRD ADC Distributions in Xe:ISO 90:10}{DF:1.35kV/cm, Amplification HV Scan}");
    }
    firstHist2->GetYaxis()->SetTitle("Pulses / numEvents");
    firstHist2->SetMaximum(1);
    firstHist2->GetXaxis()->SetTitleSize(0.045);
    firstHist2->GetXaxis()->SetLabelSize(0.042);
    firstHist2->GetYaxis()->SetTitleSize(0.045);
    firstHist2->GetYaxis()->SetLabelSize(0.042);
    firstHist2->GetYaxis()->SetTitleOffset(0.85);
  }
  histListMMG->Draw("same");
  l2->SetTextSize(0.042);
  l2->SetHeader("Divider V_{in}","C");
  l2->SetNColumns(8);
  l2->Draw();
  gPad->Modified();
  gPad->Update();
  if (useMax) {
    c2->SaveAs("MMG1TRD_Max_ADC_Xe_Comparison_v2.C");
    c2->SaveAs("MMG1TRD_Max_ADC_Xe_Comparison_v2.pdf");
  } else {
    c2->SaveAs("MMG1TRD_ADC_Xe_Comparison_v2.C");
    c2->SaveAs("MMG1TRD_ADC_Xe_Comparison_v2.pdf");
  }
  
  TCanvas *c3 = new TCanvas("c3","uRWell-TRD ADC Distributions at Varied HV in Xe", 1600, 1000);
  c3->cd();
  gPad->SetLogy();
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetTopMargin(0.135);
  TH1 *firstHist3 = (TH1 *)histListURW->First();
  if (firstHist3) {
    if (useMax) {
      firstHist3->GetXaxis()->SetTitle("Maximum Pulse Amplitude [fADC Units]");
      //firstHist3->SetTitle("#splitline{Hybrid #muRWELL-TRD Maximum ADC in Xe:ISO 90:10}{DF:1.35kV/cm TF:2.35kV/cm GEM dV:400V, WELL Scan}");
      firstHist3->SetTitle("#splitline{Hybrid #muRWELL-TRD Maximum ADC Value}{in Xe Mixtures with Varied HVs}");
    } else {
      firstHist3->GetXaxis()->SetTitle("Pulse Peak Amplitude [fADC Units]");
      firstHist3->SetTitle("#splitline{Hybrid #muRWELL-TRD ADC Distributions}{in Xe Mixtures with Varied HVs}");
      //firstHist3->SetTitle("#splitline{Hybrid #muRWELL-TRD ADC Distributions in Xe:ISO 90:10}{DF:1.35kV/cm GEM dV:410V, WELL:525V, TF Scan}");
      //firstHist3->SetTitle("#splitline{Hybrid #muRWELL-TRD ADC Distributions in Xe:ISO 90:10}{DF:1.35kV/cm TF:2.35kV/cm GEM dV:400V, WELL Scan}");
    }
    firstHist3->GetYaxis()->SetTitle("Pulses / numEvents");
    firstHist3->SetMaximum(1);
    firstHist3->GetXaxis()->SetTitleSize(0.045);
    firstHist3->GetXaxis()->SetLabelSize(0.042);
    firstHist3->GetYaxis()->SetTitleSize(0.045);
    firstHist3->GetYaxis()->SetLabelSize(0.042);
    firstHist3->GetYaxis()->SetTitleOffset(0.85);
  }
  histListURW->Draw("same");
  l3->SetTextSize(0.042);
  //l3->SetHeader("Resistive WELL","C");
  //l3->SetNColumns(2);
  l3->Draw();
  gPad->Modified();
  gPad->Update();
  if (useMax) {
    c3->SaveAs("URWTRD_Max_ADC_Xe_Comparison_v2.C");
    c3->SaveAs("URWTRD_Max_ADC_Xe_Comparison_v2.pdf");
  } else {
    c3->SaveAs("URWTRD_ADC_Xe_Comparison_v2.C");
    c3->SaveAs("URWTRD_ADC_Xe_Comparison_v2.pdf");
  }
  
//======================================================================================
if (makeTimeDistributions)
 {
  
  TList *HistDQM;
	double TFScaleFactor = -1.;
  
  //TLegend *l31 = new TLegend(0.35, 0.65, 0.9, 0.865);
  TLegend *l31 = new TLegend(0.25, 0.56, 0.53, 0.865);
  //TLegend *l4 = new TLegend(0.48, 0.62, 0.9, 0.865);
  TLegend *l4 = new TLegend(0.14, 0.75, 0.897, 0.86);
  //TLegend *l5 = new TLegend(0.42, 0.69, 0.9, 0.865);
  TLegend *l5 = new TLegend(0.4, 0.69, 0.9, 0.865);
  //TLegend *l5 = new TLegend(0.67, 0.6, 0.9, 0.865);
  
  //================== Triple-GEM =============================
  TFile *file0 = TFile::Open(rootFilesGEM[0]);
	HistDQM = (TList *)file0->Get("HistDQM");
  TObject *objg0 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g0 = (TH2 *)objg0;
  TFScaleFactor = 1./g0->GetEntries();
  g0->Scale(TFScaleFactor);
  g0->RebinX(4);
  //TH1D *g_0 = g0->ProjectionX(legendListGEM[0],80,160);
  TH1D *g_0 = g0->ProjectionX("g_0");
  g_0->SetLineColor(colorList[0]);
  g_0->SetMarkerStyle(markerList[0]);
  g_0->SetMarkerColor(colorList[0]);
  g_0->SetMarkerSize(2);
  
  TFile *file1 = TFile::Open(rootFilesGEM[1]);
  HistDQM = (TList *)file1->Get("HistDQM");
  //TObject *objg1 = HistDQM->FindObject("f125_el_amp2ds");
  TObject *objg1 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g1 = (TH2 *)objg1;
  TFScaleFactor = 1./g1->GetEntries();
  g1->Scale(TFScaleFactor);
  g1->RebinX(4);
  //TH1D *g_1 = g1->ProjectionX(legendListGEM[1],80,160);
  TH1D *g_1 = g1->ProjectionX("g_1");
  g_1->SetLineColor(colorList[1]);
  g_1->SetMarkerStyle(markerList[1]);
  g_1->SetMarkerColor(colorList[1]);
  g_1->SetMarkerSize(2);
  
  TFile *file2 = TFile::Open(rootFilesGEM[2]);
  HistDQM = (TList *)file2->Get("HistDQM");
  TObject *objg2 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g2 = (TH2 *)objg2;
  TFScaleFactor = 1./g2->GetEntries();
  g2->Scale(TFScaleFactor);
  g2->RebinX(4);
  //TH1D *g_2 = g2->ProjectionX(legendListGEM[2],80,160);
  TH1D *g_2 = g2->ProjectionX("g_2");
  g_2->SetLineColor(colorList[2]);
  g_2->SetMarkerStyle(markerList[2]);
  g_2->SetMarkerColor(colorList[2]);
  g_2->SetMarkerSize(2);
  
  TFile *file3 = TFile::Open(rootFilesGEM[3]);
  HistDQM = (TList *)file3->Get("HistDQM");
  TObject *objg3 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g3 = (TH2 *)objg3;
  TFScaleFactor = 1./g3->GetEntries();
  g3->Scale(TFScaleFactor);
  g3->RebinX(4);
  //TH1D *g_3 = g3->ProjectionX(legendListGEM[3],80,160);
  TH1D *g_3 = g3->ProjectionX("g_3");
  g_3->SetLineColor(colorList[3]);
  g_3->SetMarkerStyle(markerList[3]);
  g_3->SetMarkerColor(colorList[3]);
  g_3->SetMarkerSize(2);
  
  TFile *file4 = TFile::Open(rootFilesGEM[4]);
  HistDQM = (TList *)file4->Get("HistDQM");
  TObject *objg4 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g4 = (TH2 *)objg4;
  TFScaleFactor = 1./g4->GetEntries();
  g4->Scale(TFScaleFactor);
  g4->RebinX(4);
  //TH1D *g_4 = g4->ProjectionX(legendListGEM[4],80,160);
  TH1D *g_4 = g4->ProjectionX("g_4");
  g_4->SetLineColor(colorList[4]);
  g_4->SetMarkerStyle(markerList[4]);
  g_4->SetMarkerColor(colorList[4]);
  g_4->SetMarkerSize(2);
  /*
  TFile *file5 = TFile::Open(rootFilesGEM[5]);
  HistDQM = (TList *)file5->Get("HistDQM");
  TObject *objg5 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g5 = (TH2 *)objg5;
  TFScaleFactor = 1./g5->GetEntries();
  g5->Scale(TFScaleFactor);
  g5->RebinX(4);
  //TH1D *g_5 = g5->ProjectionX(legendListGEM[5],80,160);
  TH1D *g_5 = g5->ProjectionX("g_5");
  g_5->SetLineColor(colorList[5]);
  g_5->SetMarkerStyle(markerList[5]);
  g_5->SetMarkerColor(colorList[5]);
  g_5->SetMarkerSize(2);
  
  TFile *file6 = TFile::Open(rootFilesGEM[6]);
  HistDQM = (TList *)file6->Get("HistDQM");
  TObject *objg6 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g6 = (TH2 *)objg6;
  TFScaleFactor = 1./g6->GetEntries();
  g6->Scale(TFScaleFactor);
  g6->RebinX(4);
  //TH1D *g_6 = g6->ProjectionX(legendListGEM[6],80,160);
  TH1D *g_6 = g6->ProjectionX("g_6");
  g_6->SetLineColor(colorList[6]);
  g_6->SetMarkerStyle(markerList[6]);
  g_6->SetMarkerColor(colorList[6]);
  g_6->SetMarkerSize(2);
  
  TFile *file7 = TFile::Open(rootFilesGEM[7]);
  HistDQM = (TList *)file7->Get("HistDQM");
  TObject *objg7 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g7 = (TH2 *)objg7;
  TFScaleFactor = 1./g7->GetEntries();
  g7->Scale(TFScaleFactor);
  g7->RebinX(4);
  //TH1D *g_7 = g7->ProjectionX(legendListGEM[7],80,160);
  TH1D *g_7 = g7->ProjectionX("g_7");
  g_7->SetLineColor(colorList[7]);
  g_7->SetMarkerStyle(markerList[7]);
  g_7->SetMarkerColor(colorList[7]);
  g_7->SetMarkerSize(2);
  
  TFile *file8 = TFile::Open(rootFilesGEM[8]);
  HistDQM = (TList *)file8->Get("HistDQM");
  TObject *objg8 = HistDQM->FindObject("f125_el_amp2d");
  TH2 *g8 = (TH2 *)objg8;
  TFScaleFactor = 1./g8->GetEntries();
  g8->Scale(TFScaleFactor);
  g8->RebinX(4);
  //TH1D *g_8 = g8->ProjectionX(legendListGEM[8],80,160);
  TH1D *g_8 = g8->ProjectionX("g_8");
  g_8->SetLineColor(colorList[8]);
  g_8->SetMarkerStyle(markerList[8]);
  g_8->SetMarkerColor(colorList[8]);
  g_8->SetMarkerSize(2);
  */
  
  //================== MMG1 =============================
  TFile *file0m = TFile::Open(rootFilesMMG[0]);
  HistDQM = (TList *)file0m->Get("HistDQM");
  TObject *objm0 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m0 = (TH2 *)objm0;
  TFScaleFactor = 1./m0->GetEntries();
  m0->Scale(TFScaleFactor);
  m0->RebinX(4);
  //TH1D *m_0 = m0->ProjectionX(legendListMMG[0],80,160);
  TH1D *m_0 = m0->ProjectionX("m_0");
  m_0->SetLineColor(colorList[0]);
  m_0->SetMarkerStyle(markerList[0]);
  m_0->SetMarkerColor(colorList[0]);
  m_0->SetMarkerSize(2);
  
  TFile *file1m = TFile::Open(rootFilesMMG[1]);
  HistDQM = (TList *)file1m->Get("HistDQM");
  //TObject *objm1 = HistDQM->FindObject("mmg1_f125_el_amp2ds");
  TObject *objm1 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m1 = (TH2 *)objm1;
  TFScaleFactor = 1./m1->GetEntries();
  m1->Scale(TFScaleFactor);
  m1->RebinX(4);
  //TH1D *m_1 = m1->ProjectionX(legendListMMG[1],80,160);
  TH1D *m_1 = m0->ProjectionX("m_1");
  m_1->SetLineColor(colorList[1]);
  m_1->SetMarkerStyle(markerList[1]);
  m_1->SetMarkerColor(colorList[1]);
  m_1->SetMarkerSize(2);
  
  TFile *file2m = TFile::Open(rootFilesMMG[2]);
  HistDQM = (TList *)file2m->Get("HistDQM");
  TObject *objm2 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m2 = (TH2 *)objm2;
  TFScaleFactor = 1./m2->GetEntries();
  m2->Scale(TFScaleFactor);
  m2->RebinX(4);
  //TH1D *m_2 = m2->ProjectionX(legendListMMG[2],80,160);
  TH1D *m_2 = m2->ProjectionX("m_2");
  m_2->SetLineColor(colorList[2]);
  m_2->SetMarkerStyle(markerList[2]);
  m_2->SetMarkerColor(colorList[2]);
  m_2->SetMarkerSize(2);
  
  TFile *file3m = TFile::Open(rootFilesMMG[3]);
  HistDQM = (TList *)file3m->Get("HistDQM");
  TObject *objm3 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m3 = (TH2 *)objm3;
  TFScaleFactor = 1./m3->GetEntries();
  m3->Scale(TFScaleFactor);
  m3->RebinX(4);
  //TH1D *m_3 = m3->ProjectionX(legendListMMG[3],80,160);
  TH1D *m_3 = m3->ProjectionX("m_3");
  m_3->SetLineColor(colorList[3]);
  m_3->SetMarkerStyle(markerList[3]);
  m_3->SetMarkerColor(colorList[3]);
  m_3->SetMarkerSize(2);
  
  TFile *file4m = TFile::Open(rootFilesMMG[4]);
  HistDQM = (TList *)file4m->Get("HistDQM");
  TObject *objm4 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m4 = (TH2 *)objm4;
  TFScaleFactor = 1./m4->GetEntries();
  m4->Scale(TFScaleFactor);
  m4->RebinX(4);
  //TH1D *m_4 = m4->ProjectionX(legendListMMG[4],80,160);
  TH1D *m_4 = m4->ProjectionX("m_4");
  m_4->SetLineColor(colorList[4]);
  m_4->SetMarkerStyle(markerList[4]);
  m_4->SetMarkerColor(colorList[4]);
  m_4->SetMarkerSize(2);
  
  TFile *file5m = TFile::Open(rootFilesMMG[5]);
  HistDQM = (TList *)file5m->Get("HistDQM");
  TObject *objm5 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m5 = (TH2 *)objm5;
  TFScaleFactor = 1./m5->GetEntries();
  m5->Scale(TFScaleFactor);
  m5->RebinX(4);
  //TH1D *m_5 = m5->ProjectionX(legendListMMG[5],80,160);
  TH1D *m_5 = m5->ProjectionX("m_5");
  m_5->SetLineColor(colorList[5]);
  m_5->SetMarkerStyle(markerList[5]);
  m_5->SetMarkerColor(colorList[5]);
  m_5->SetMarkerSize(2);
  
  TFile *file6m = TFile::Open(rootFilesMMG[6]);
  HistDQM = (TList *)file6m->Get("HistDQM");
  TObject *objm6 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m6 = (TH2 *)objm6;
  TFScaleFactor = 1./m6->GetEntries();
  m6->Scale(TFScaleFactor);
  m6->RebinX(4);
  //TH1D *m_6 = m6->ProjectionX(legendListMMG[6],80,160);
  TH1D *m_6 = m6->ProjectionX("m_6");
  m_6->SetLineColor(colorList[6]);
  m_6->SetMarkerStyle(markerList[6]);
  m_6->SetMarkerColor(colorList[6]);
  m_6->SetMarkerSize(2);
  
  TFile *file7m = TFile::Open(rootFilesMMG[7]);
  HistDQM = (TList *)file7m->Get("HistDQM");
  TObject *objm7 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m7 = (TH2 *)objm7;
  TFScaleFactor = 1./m7->GetEntries();
  m7->Scale(TFScaleFactor);
  m7->RebinX(4);
  //TH1D *m_7 = m7->ProjectionX(legendListMMG[7],80,160);
  TH1D *m_7 = m7->ProjectionX("m_7");
  m_7->SetLineColor(colorList[7]);
  m_7->SetMarkerStyle(markerList[7]);
  m_7->SetMarkerColor(colorList[7]);
  m_7->SetMarkerSize(2);
  /*
  TFile *file8m = TFile::Open(rootFilesMMG[8]);
  HistDQM = (TList *)file8m->Get("HistDQM");
  TObject *objm8 = HistDQM->FindObject("mmg1_f125_el_amp2d");
  TH2 *m8 = (TH2 *)objm8;
  TFScaleFactor = 1./m8->GetEntries();
  m8->Scale(TFScaleFactor);
  m8->RebinX(4);
  //TH1D *m_8 = m8->ProjectionX(legendListMMG[8],80,160);
  TH1D *m_8 = m8->ProjectionX("m_8");
  m_8->SetLineColor(colorList[8]);
  m_8->SetMarkerStyle(markerList[8]);
  m_8->SetMarkerColor(colorList[8]);
  m_8->SetMarkerSize(2);
  */
  //=================== uRWell-TRD ==========================

  TFile *fileu0 = TFile::Open(rootFilesURW[0]);
  HistDQM = (TList *)fileu0->Get("HistDQM");
  TObject *obju0 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *u0 = (TH2 *)obju0;
  TFScaleFactor = 1./u0->GetEntries();
  u0->Scale(TFScaleFactor);
  u0->RebinX(4);
  //TH1D *u_0 = u0->ProjectionX(legendListURW[0],30,90);
  TH1D *u_0 = u0->ProjectionX("u_0");
  u_0->SetLineColor(colorList[0]);
  u_0->SetMarkerStyle(markerList[0]);
  u_0->SetMarkerColor(colorList[0]);
  u_0->SetMarkerSize(2);
  
  TFile *fileu1 = TFile::Open(rootFilesURW[1]);
  HistDQM = (TList *)fileu1->Get("HistDQM");
  TObject *obju1 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *u1 = (TH2 *)obju1;
  TFScaleFactor = 1./u1->GetEntries();
  u1->Scale(TFScaleFactor);
  u1->RebinX(4);
  //TH1D *u_1 = u1->ProjectionX(legendListURW[1],30,90);
  TH1D *u_1 = u1->ProjectionX("u_1");
  u_1->SetLineColor(colorList[1]);
  u_1->SetMarkerStyle(markerList[1]);
  u_1->SetMarkerColor(colorList[1]);
  u_1->SetMarkerSize(2);
  
  TFile *fileu2 = TFile::Open(rootFilesURW[2]);
  HistDQM = (TList *)fileu2->Get("HistDQM");
  TObject *obju2 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *u2 = (TH2 *)obju2;
  TFScaleFactor = 1./u2->GetEntries();
  u2->Scale(TFScaleFactor);
  u2->RebinX(4);
  //TH1D *u_2 = u2->ProjectionX(legendListURW[2],30,90);
  TH1D *u_2 = u2->ProjectionX("u_2");
  u_2->SetLineColor(colorList[2]);
  u_2->SetMarkerStyle(markerList[2]);
  u_2->SetMarkerColor(colorList[2]);
  u_2->SetMarkerSize(2);
  /*
  TFile *fileu3 = TFile::Open(rootFilesURW[3]);
  HistDQM = (TList *)fileu3->Get("HistDQM");
  TObject *obju3 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *u3 = (TH2 *)obju3;
  TFScaleFactor = 1./u3->GetEntries();
  u3->Scale(TFScaleFactor);
  u3->RebinX(4);
  //TH1D *u_3 = u3->ProjectionX(legendListURW[3],30,90);
  TH1D *u_3 = u3->ProjectionX("u_3");
  u_3->SetLineColor(colorList[3]);
  u_3->SetMarkerStyle(markerList[3]);
  u_3->SetMarkerColor(colorList[3]);
  u_3->SetMarkerSize(2);
  
  TFile *fileu4 = TFile::Open(rootFilesURW[4]);
  HistDQM = (TList *)fileu4->Get("HistDQM");
  TObject *obju4 = HistDQM->FindObject("urw_f125_x_amp2d");
  TH2 *u4 = (TH2 *)obju4;
  TFScaleFactor = 1./u4->GetEntries();
  u4->Scale(TFScaleFactor);
  u4->RebinX(4);
  //TH1D *u_4 = u4->ProjectionX(legendListURW[4],30,90);
  TH1D *u_4 = u4->ProjectionX("u_4");
  u_4->SetLineColor(colorList[4]);
  u_4->SetMarkerStyle(markerList[4]);
  u_4->SetMarkerColor(colorList[4]);
  u_4->SetMarkerSize(2);
  */
  
  AlignLeadingEdge(g_0, g_1);
  AlignLeadingEdge(g_0, g_2);
  //AlignLeadingEdge(g_0, g_3);
  //AlignLeadingEdge(g_0, g_4);
  
  AlignLeadingEdge(m_0, m_1);
  AlignLeadingEdge(m_0, m_2);
  AlignLeadingEdge(m_0, m_3);
  AlignLeadingEdge(m_0, m_4);
  AlignLeadingEdge(m_0, m_5);
  AlignLeadingEdge(m_0, m_6);
  AlignLeadingEdge(m_0, m_7);
  
  AlignLeadingEdge(u_0, u_1);
  AlignLeadingEdge(u_0, u_2);
  //AlignLeadingEdge(u_0, u_3);
  //AlignLeadingEdge(u_0, u_4);
  
  TCanvas *c31 = new TCanvas("c31","GEMTRD Timing Distributions at Varied HV in Xe", 1600, 1000);
  c31->cd();
  gPad->SetGridy();
  l31->AddEntry(g_0,legendListGEM[0],"lp");
  l31->AddEntry(g_1,legendListGEM[1],"lp");
  l31->AddEntry(g_2,legendListGEM[2],"lp");
  l31->AddEntry(g_3,legendListGEM[3],"lp");
  l31->AddEntry(g_4,legendListGEM[4],"lp");
  //l31->AddEntry(g_5,legendListGEM[5],"lp");
  //l31->AddEntry(g_6,legendListGEM[6],"lp");
  //l31->AddEntry(g_7,legendListGEM[7],"lp");
  //l31->AddEntry(g_8,legendListGEM[8],"lp");
  g_0->GetYaxis()->SetTitle("ADC Amplitude (Pulses / numEvents)");
  g_0->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  g_0->GetYaxis()->SetNdivisions(520);
  //g_0->GetXaxis()->SetRangeUser(45.,160.);
  g_0->GetXaxis()->SetRangeUser(30.,135.);
  g_0->SetMaximum(g_0->GetMaximum()+35.);
  //g_0->SetMaximum(g_0->GetMaximum()+30.);
  //g_0->SetTitle("#splitline{Triple-GEM-TRD ADC Response in Time}{for Xe Mixtures with Varied HVs}");
  //g_0->SetTitle("#splitline{Triple-GEM-TRD ADC Response in Time, Xe:ISO 90:10}{DF:1.17kV/cm TF:3.74kV/cm, GEM dV Scan}");
  g_0->SetTitle("#splitline{Triple-GEM-TRD ADC Distributions in Xe:ISO 90:10}{GEM dVs: 450V/425V/390V, Transfer Field Scan}");
  gPad->SetTopMargin(0.135);
  g_0->GetXaxis()->SetTitleSize(0.045);
  g_0->GetXaxis()->SetLabelSize(0.042);
  g_0->GetYaxis()->SetTitleSize(0.044);
  g_0->GetYaxis()->SetLabelSize(0.042);
  g_0->Draw("LP same");
  g_1->Draw("LP same");
  g_2->Draw("LP same");
  g_3->Draw("LP same");
  g_4->Draw("LP same");
  //g_5->Draw("LP same");
  //g_6->Draw("LP same");
  //g_7->Draw("LP same");
  //g_8->Draw("LP same");
  l31->SetHeader("Transfer Fields","C");
  //l31->SetNColumns(2);
  l31->SetTextSize(0.042);
  l31->Draw();
  gPad->Modified();
  gPad->Update();
  c31->SaveAs("GEMTRD_Time_Xe_Comparison_v2.C");
  c31->SaveAs("GEMTRD_Time_Xe_Comparison_v2.pdf");
  
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
  l4->AddEntry(m_7,legendListMMG[7],"lp");
  //l4->AddEntry(m_8,legendListMMG[8],"lp");
  m_0->GetYaxis()->SetTitle("ADC Amplitude (Pulses / numEvents)");
  m_0->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  m_0->GetYaxis()->SetNdivisions(520);
  //m_0->GetXaxis()->SetRangeUser(25.,200.);
  m_0->GetXaxis()->SetRangeUser(15.,155.);
  //m_0->SetMaximum(m_0->GetMaximum()+32.);
  m_0->SetMaximum(m_0->GetMaximum()+25.);
  //m_0->SetTitle("#splitline{MMG1-TRD ADC Response in Time}{for Xe Mixtures with Varied HVs}");
  m_0->SetTitle("#splitline{MMG1-TRD ADC Response in Time, Xe:ISO 90:10}{DF:1.35kV/cm, Amplification HV Scan}");
  gPad->SetTopMargin(0.135);
  m_0->GetXaxis()->SetTitleSize(0.045);
  m_0->GetXaxis()->SetLabelSize(0.042);
  m_0->GetYaxis()->SetTitleSize(0.044);
  m_0->GetYaxis()->SetLabelSize(0.042);
  m_0->Draw("PL");
  m_1->Draw("PL same");
  m_2->Draw("PL same");
  m_3->Draw("PL same");
  m_4->Draw("PL same");
  m_5->Draw("PL same");
  m_6->Draw("PL same");
  m_7->Draw("PL same");
  //m_8->Draw("PL same");
  l4->SetTextSize(0.042);
  l4->SetHeader("Divider V_{in}","C");
  l4->SetNColumns(8);
  l4->Draw();
  gPad->Modified();
  gPad->Update();
  c4->SaveAs("MMG1TRD_Time_Xe_Comparison_v2.C");
  c4->SaveAs("MMG1TRD_Time_Xe_Comparison_v2.pdf");
  
  
  TCanvas *c5 = new TCanvas("c5","uRWell-TRD Timing Distributions at Varied HV in Xe", 1600, 1000);
  c5->cd();
  gPad->SetGridy();
  gPad->SetTopMargin(0.135);
  l5->AddEntry(u_0,legendListURW[0],"lp");
  l5->AddEntry(u_1,legendListURW[1],"lp");
  l5->AddEntry(u_2,legendListURW[2],"lp");
  //l5->AddEntry(u_3,legendListURW[3],"lp");
  //l5->AddEntry(u_4,legendListURW[4],"lp");
  //l5->AddEntry(u_5,legendListURW[5],"lp");
  //l5->AddEntry(u_6,legendListURW[6],"lp");
  //l5->AddEntry(u_7,legendListURW[7],"lp");
  //l5->AddEntry(u_8,legendListURW[8],"lp");
  u_0->GetYaxis()->SetTitle("ADC Amplitude (Pulses / numEvents)");
  u_0->GetXaxis()->SetTitle("Drift Time (8ns/bin)");
  u_0->GetYaxis()->SetNdivisions(520);
  //u_0->GetXaxis()->SetRangeUser(15.,145.);
  u_0->GetXaxis()->SetRangeUser(35.,160.);
  //u_0->SetMaximum(u_0->GetMaximum()+25.);
  u_0->SetMaximum(u_0->GetMaximum()+20.);
  //u_0->SetTitle("#splitline{Hybrid #muRWELL-TRD ADC Response in Time, Xe:ISO 90:10}{DF:1.35kV/cm GEM dV:410V WELL:525V, TF Scan}");
  //u_0->SetTitle("#splitline{Hybrid #muRWELL-TRD ADC Response in Time, Xe:ISO 90:10}{DF:1.35kV/cm TF 2.35kV/cm GEM dV:400V, WELL Scan}");
  u_0->SetTitle("#splitline{Hybrid #muRWELL-TRD ADC Response in Time}{for Xe Mixtures with Varied HVs}");
  u_0->GetXaxis()->SetTitleSize(0.045);
  u_0->GetXaxis()->SetLabelSize(0.042);
  u_0->GetYaxis()->SetTitleSize(0.044);
  u_0->GetYaxis()->SetLabelSize(0.042);
  u_0->Draw("PL");
  u_1->Draw("PL same");
  u_2->Draw("PL same");
  //u_3->Draw("PL same");
  //u_4->Draw("PL same");
  l5->SetTextSize(0.042);
  //l5->SetHeader("Resistive WELL","C");
  //l5->SetNColumns(2);
  l5->Draw();
  gPad->Modified();
  gPad->Update(); 
  c5->SaveAs("URWTRD_Time_Xe_Comparison_v2.C");
  c5->SaveAs("URWTRD_Time_Xe_Comparison_v2.pdf");
  
  }  
}
