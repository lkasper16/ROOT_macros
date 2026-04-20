#include <TCanvas.h>
#include <TH1D.h>
#include <TH1F.h>
#include <TH1.h>
#include <TFile.h>
#include <TList.h>
#include <TString.h>
#include <iostream>
#include <TLegend.h>

void TRD2025_AmpCompare() {

	// --- SET FILE NAMES AND LEGEND DESCRIPTIONS ---
	TString rootFiles[] = {"hd_root_131075_2.5mil_TRDOnline.root", "hd_root_131077_2.5mil_TRDOnline.root", "hd_root_131082_2.5mil_TRDOnline.root", "hd_root_131087_2.5mil_TRDOnline.root", "hd_root_131091_2.5mil_TRDOnline.root","hd_root_131095_2.5mil_TRDOnline.root","hd_root_131100_2.5mil_TRDOnline.root"};
	TString legendList[] = {"Run 131075 (ECAL+FCAL+BCAL)","Run 131077 (ECAL+FCAL+BCAL)","Run 131082 (FCAL)","Run 131087 (FCAL)","Run 131091 (FCAL)","Run 131095 (FCAL)","Run 131100 (FCAL)"};
	
	TList *xList = new TList;
    TList *yList = new TList;
    int colorList[] = {1,2,209,4,6,94,7,217};
	TLegend *l1 = new TLegend(0.5, 0.6, 0.9, 0.9);
	TLegend *l2 = new TLegend(0.5, 0.6, 0.9, 0.9);
	int nxList=0, nyList=0;
  
  	for (int i=0; i<sizeof(rootFiles)/sizeof(rootFiles[0]); i++) {
		const TString& rootFile = rootFiles[i];
		TFile *file = TFile::Open(rootFile, "READ");
		if (!file || file->IsZombie()) {
      		std::cerr << "Error: Could not open file " << rootFile << std::endl;
      		continue;
    	}
	
	TObject *objx = file->Get("TRD/Hit/Hit_PulseHeight_Plane0");
	if (objx && objx->InheritsFrom("TH1")) {
    	TH1 *xPlaneAmp = (TH1*)objx;
		xPlaneAmp->Sumw2();
    	xPlaneAmp->SetLineColor(colorList[i]);
      	xPlaneAmp->SetLineWidth(2);
      	xPlaneAmp->SetMarkerStyle(7);
      	xPlaneAmp->SetMarkerColor(colorList[i]);

      	xPlaneAmp->SetDirectory(0);
      	xList->Add(xPlaneAmp);
      	nxList++;
      	l1->AddEntry(xPlaneAmp, legendList[i], "l");
    } else {
      	std::cerr << "Error: Object 'TRD/Hit/Hit_PulseHeight_Plane0' in " << rootFile << " is not a TH1 histogram or is missing." << std::endl;
    }
	
	TObject *objy = file->Get("TRD/Hit/Hit_PulseHeight_Plane1");
    if (objy && objy->InheritsFrom("TH1")) {
        TH1 *yPlaneAmp = (TH1*)objy;
		yPlaneAmp->Sumw2();
        yPlaneAmp->SetLineColor(colorList[i]);
        yPlaneAmp->SetLineWidth(2);
        yPlaneAmp->SetMarkerStyle(7);
        yPlaneAmp->SetMarkerColor(colorList[i]);
        yPlaneAmp->SetDirectory(0);
        yList->Add(yPlaneAmp);
        nyList++;
        l2->AddEntry(yPlaneAmp, legendList[i], "l");
    } else {
        std::cerr << "Error: Object 'TRD/Hit/Hit_PulseHeight_Plane1' in " << rootFile << " is not a TH1 histogram or is missing." << std::endl;
    } 
	
		file->Close();
	}
	
	TCanvas *c1 = new TCanvas("c1","2025 GEMTRD ADC Amplitudes in KRCO2 90:10", 1600, 1200);
	gStyle->SetOptStat(00000);
	c1->Divide(2,1);
	c1->cd(1);
	TH1 *firstXHist = (TH1 *)xList->First();
  	if (firstXHist) {
    	firstXHist->SetMaximum(firstXHist->GetMaximum()+30000.);
    	firstXHist->SetTitle("GEMTRD X Plane ADC Amplitude Distribution");
  	}
	xList->Draw("same");
	l1->SetHeader("Run Number (Trigger)", "C");
    l1->Draw();
	
	c1->cd(2);
    TH1 *firstYHist = (TH1 *)yList->First();
    if (firstYHist) {
        firstYHist->SetMaximum(firstYHist->GetMaximum()+30000.);
        firstYHist->SetTitle("GEMTRD Y Plane ADC Amplitude Distribution");
    }
    yList->Draw("same");
    l2->SetHeader("Run Number (Trigger)", "C");
    l2->Draw();
	
	c1->SaveAs("amplitudeComparison.png");
	
}
