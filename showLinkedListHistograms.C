#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <TMath.h>
#include <TStopwatch.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TPaveStats.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TLine.h>
#include <TList.h>
#include <TObject.h>
#include <TAxis.h>
#include <TLegend.h>
using namespace ROOT;
using namespace std;

void showLinkedListHistograms() {
	
	TString rootFileList[] = {"Run_003134_Output.root", "Run_003196_Output.root", "Run_003197_Output.root", "Run_003198_Output.root", "Run_003199_Output.root", "Run_003200_Output.root", "Run_003201_Output.root", "Run_003202_Output.root", "Run_003203_Output.root", "Run_003204_Output.root", "Run_003216_Output.root", "Run_003248_Output.root", "Run_003287_Output.root", "Run_003288_Output.root", "Run_003289_Output.root"};
	
	TList *histList_1D = new TList;
	TList *histList_2D = new TList;
	TString name1 = "hNTracks";
	TString name2 = "hNTracks_e";
	TString name3 = "hNTracks_pi";
	TString name4 = "singleTrackIndex";
	TString name5 = "singleTrackIndex_e";
	TString name6 = "singleTrackIndex_pi";
	TString name7 = "multiTrackIndex";
	TString name8 = "multiTrackIndex_e";
	TString name9 = "multiTrackIndex_pi";
	
	for (int i=0; i<sizeof(rootFileList)/sizeof(rootFileList[0]); i++) {
		const TString& rootFile = rootFileList[i];
		TFile *file = TFile::Open(rootFile, "READ");
		TList *HistDQM = (TList *)file->Get("HistDQM");
		TIter next(HistDQM);
		
		while (TH1 *readObject = dynamic_cast<TH1 *>(next())) {
			TString histName = readObject->GetName();
			if (histName == name1 || histName == name2 || histName == name3) {
				cout<<histName<<endl;
				histList_1D->Add(readObject);
				
                int oneTrack = readObject->GetBinContent(2);
				int twoTracks = readObject->GetBinContent(3);
				cout<<"# of single Tracks: "<< oneTrack <<endl;
				cout<<"# of double Tracks: "<< twoTracks <<endl;
/*				for (int bin = 1; bin <= readObject->GetNbinsX(); bin++) {
                    cout << "Bin: " << bin << " content: " << readObject->GetBinContent(bin) << endl;
                }
*/			} else if (histName == name4 || histName == name5 || histName == name6 || histName == name7 || histName == name8 || histName == name9) {
				cout<<histName<<endl;
				histList_2D->Add(readObject);
				
				int zeroHits = readObject->GetBinContent(1,1);
				int oneHit = readObject->GetBinContent(2,2) + (readObject->GetBinContent(1,2) - readObject->GetBinContent(2,1));
				int twoHits = readObject->GetBinContent(3,3) + (readObject->GetBinContent(2,3) - readObject->GetBinContent(3,2));
				cout<<"0:0 Hits: "<< zeroHits <<endl;
				cout<<"1:1 Hits: "<< oneHit <<endl;
				cout<<"2:2 Hits: "<< twoHits <<endl;
/*				for (int binX = 1; binX <= readObject->GetNbinsX(); binX++) {
                    for (int binY = 1; binY <= readObject->GetNbinsY(); binY++) {
                        cout << "Bin (" << binX << ", " << binY << ") content: " << readObject->GetBinContent(binX, binY) << endl;
                    }
                }
*/			}
		}
		file->Close();
	}
	
	int n1DHistograms= histList_1D->GetSize();
	int n2DHistograms= histList_2D->GetSize();
	cout<<"Total # of 1D histograms: "<<n1DHistograms<<endl;
	cout<<"Total # of 2D histograms: "<<n2DHistograms<<endl;
		
	for (int i=0; i<n1DHistograms; i++) {
		TH1* hist = dynamic_cast<TH1 *>(histList_1D->At(i));
        TCanvas canvas(Form("canvas%d", i), Form("Histogram %d", i), 800, 600);
		gPad->SetGridx();
		gPad->SetGridy();
		hist->SetLineWidth(2);
  	    hist->Draw();
		canvas.Draw();
        canvas.SaveAs(Form("PNGs/histogram_1D_%d.png", i));
	}
	for (int i=0; i<n2DHistograms; i++) {
		TH2* hist = dynamic_cast<TH2*>(histList_2D->At(i));
        TCanvas canvas(Form("canvas%d", i), Form("Histogram %d", i), 800, 600);
        hist->Draw("colz text");
		canvas.Draw();
        canvas.SaveAs(Form("PNGs/histogram_2D_%d.png", i));
	}
}
