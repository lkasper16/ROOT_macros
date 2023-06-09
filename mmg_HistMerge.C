#include <vector>
#include <fstream>
#include <string>
#include <TTree.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TRandom2.h>
#include <TRandom.h>
#include <TStopwatch.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TList.h>
#include <TPaveStats.h>
#include <TChain.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TLine.h>
#include <TBox.h>
#include <TObject.h>
#include <TLegend.h>
#include <TProfile.h>
using namespace ROOT;

void mmg_HistMerge(){
	
	TFile *_file0 = TFile::Open("eventsTree_Run003202_Output_513789Entries.root");
	TFile *_file1 = TFile::Open("Run_003275_Output.root");
	TFile *_file2 = TFile::Open("Run_003276_Output.root");
	TFile *_file3 = TFile::Open("Run_003277_Output.root");
	TFile *_file4 = TFile::Open("Run_003286_Output.root");
	TFile *_file5 = TFile::Open("eventsTree_Run003288_Output_211417Entries.root");
	
	//Electron distributions
	TH1F *mmg1_f125_el_625 = (TH1F*)_file0->Get("mmg1_f125_el");
	TH1F *mmg1_f125_el_635 = (TH1F*)_file1->Get("mmg1_f125_el");
	TH1F *mmg1_f125_el_645 = (TH1F*)_file2->Get("mmg1_f125_el");
	TH1F *mmg1_f125_el_655 = (TH1F*)_file3->Get("mmg1_f125_el");
	TH1F *mmg1_f125_el_670 = (TH1F*)_file4->Get("mmg1_f125_el");
	TH1F *mmg1_f125_el_675 = (TH1F*)_file5->Get("mmg1_f125_el");
	
	//Pion distributions
	TH1F *mmg1_f125_pi_625 = (TH1F*)_file0->Get("mmg1_f125_pi");
	TH1F *mmg1_f125_pi_635 = (TH1F*)_file1->Get("mmg1_f125_pi");
	TH1F *mmg1_f125_pi_645 = (TH1F*)_file2->Get("mmg1_f125_pi");
	TH1F *mmg1_f125_pi_655 = (TH1F*)_file3->Get("mmg1_f125_pi");
	TH1F *mmg1_f125_pi_670 = (TH1F*)_file4->Get("mmg1_f125_pi");
	TH1F *mmg1_f125_pi_675 = (TH1F*)_file5->Get("mmg1_f125_pi");
	
	_file0->cd();
	
	////////Plot Electron distributions/////////
	TCanvas *c1 = new TCanvas("c1","Electron ADC Distributions", 1200, 800);
	gStyle->SetOptStat(00000);
	c1->cd();
	gPad->SetLogy();
	
	mmg1_f125_el_675->GetXaxis()->SetTitle("ADC Amplitude");
	mmg1_f125_el_675->GetYaxis()->SetTitle("Counts");
	mmg1_f125_el_675->SetTitle("MMG1-TRD Electron ADC Distributions in XeCO2 for Varied HV");
	mmg1_f125_el_675->SetLineWidth(2);
	mmg1_f125_el_675->Scale(211417/513789.);
	mmg1_f125_el_675->Draw();
	
	mmg1_f125_el_670->SetLineColor(209);
	mmg1_f125_el_670->SetLineWidth(2);
	mmg1_f125_el_670->Scale(19742/513789.);
	mmg1_f125_el_670->Draw("same");
	
	mmg1_f125_el_655->SetLineColor(51);
	mmg1_f125_el_655->SetLineWidth(2);
	mmg1_f125_el_655->Scale(35304/513789.);
	mmg1_f125_el_655->Draw("same");
	
	mmg1_f125_el_645->SetLineColor(7);
	mmg1_f125_el_645->SetLineWidth(2);
	mmg1_f125_el_645->Scale(14987/513789.);
	mmg1_f125_el_645->Draw("same");
	
	mmg1_f125_el_635->SetLineColor(2);
	mmg1_f125_el_635->SetLineWidth(2);
	mmg1_f125_el_635->Scale(23473/513789.);
	mmg1_f125_el_635->Draw("same");
	
	mmg1_f125_el_625->SetLineColor(94);
	mmg1_f125_el_625->SetLineWidth(2);
	mmg1_f125_el_625->Draw("same");
	mmg1_f125_el_625->Scale(513789/513789.);

	TLegend *l1 = new TLegend(0.75, 0.65, 0.9, 0.9);
	l1->AddEntry(mmg1_f125_el_675, "4800V/675V", "L");
	l1->AddEntry(mmg1_f125_el_670, "4800V/670V", "L");
	l1->AddEntry(mmg1_f125_el_655, "4850V/655V", "L");
	l1->AddEntry(mmg1_f125_el_645, "4850V/645V", "L");
	l1->AddEntry(mmg1_f125_el_635, "4850V/635V", "L");
	l1->AddEntry(mmg1_f125_el_625, "4825V/625V", "L");
	l1->Draw();
	
	//////Plot Pion Distributions////////
	TCanvas *c2 = new TCanvas("c2","Pion ADC Distributions", 1200, 800);
	gStyle->SetOptStat(00000);
	c2->cd();
	gPad->SetLogy();
	
	mmg1_f125_pi_675->GetXaxis()->SetTitle("ADC Amplitude");
	mmg1_f125_pi_675->GetYaxis()->SetTitle("Counts");
	mmg1_f125_pi_675->SetTitle("MMG1-TRD Pion ADC Distributions in XeCO2 for Varied HV");
	mmg1_f125_pi_675->SetLineWidth(2);
	mmg1_f125_pi_675->Scale(211417/513789.);
	mmg1_f125_pi_675->Draw();
	
	mmg1_f125_pi_670->SetLineColor(209);
	mmg1_f125_pi_670->SetLineWidth(2);
	mmg1_f125_pi_670->Scale(19742/513789.);
	mmg1_f125_pi_670->Draw("same");
	
	mmg1_f125_pi_655->SetLineColor(51);
	mmg1_f125_pi_655->SetLineWidth(2);
	mmg1_f125_pi_655->Scale(35304/513789.);
	mmg1_f125_pi_655->Draw("same");
	
	mmg1_f125_pi_645->SetLineColor(7);
	mmg1_f125_pi_645->SetLineWidth(2);
	mmg1_f125_pi_645->Scale(14987/513789.);
	mmg1_f125_pi_645->Draw("same");
	
	mmg1_f125_pi_635->SetLineColor(2);
	mmg1_f125_pi_635->SetLineWidth(2);
	mmg1_f125_pi_635->Scale(23473/513789.);
	mmg1_f125_pi_635->Draw("same");
	
	mmg1_f125_pi_625->SetLineColor(94);
	mmg1_f125_pi_625->SetLineWidth(2);
	mmg1_f125_pi_625->Scale(513789/513789.);
	mmg1_f125_pi_625->Draw("same");
	
	TLegend *l2 = new TLegend(0.75, 0.65, 0.9, 0.9);
	l2->AddEntry(mmg1_f125_pi_675, "4800V/675V", "L");
	l2->AddEntry(mmg1_f125_pi_670, "4800V/670V", "L");
	l2->AddEntry(mmg1_f125_pi_655, "4850V/655V", "L");
	l2->AddEntry(mmg1_f125_pi_645, "4850V/645V", "L");
	l2->AddEntry(mmg1_f125_pi_635, "4850V/635V", "L");
	l2->AddEntry(mmg1_f125_pi_625, "4825V/625V", "L");
	l2->Draw();

}
