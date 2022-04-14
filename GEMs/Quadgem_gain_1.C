#include "TString.h"
#include "TDatime.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TCanvas.h"
#include <sstream>

            
//Channel 8 & 9 for old set of gems g8i, g9i. 8 is cathode, 9 is anode
void Quadgem_gain(){
  cout << "define variables :" << endl;
  const int N = 4;
  TGraph *g_an[N] ;
  TGraph *g_cat[N] ;
  TGraph *gtemp_an[N] ;
  TGraph *gtemp_cat[N] ;
  TString temp_cat;
  TString temp_an;
  TString cat;
  TString an;

  TF1 *fxray_an[N];
  TF1 *fxray_cat[N];
  TF1 *ffe55_an[N];
  TF1 *ffe55_cat[N];

  TString xray_an;
  TString xray_cat;
  TString fe55_an;
  TString fe55_cat;
          
  ifstream ifs[N];
  ostringstream filename[N];
  int N1[N];
  cout << " read files " << endl;
  //Quad gem with reverse bias primary measurement
  filename[0] << "PA_13-50_dvgem340V.txt";
  ifs[0].open(filename[0].str());

  filename[1] << "PA_14-13_dvgem342V.txt";
  ifs[1].open(filename[1].str());
  
  filename[2] << "PA_14-26_dvgem335V.txt";
  ifs[2].open(filename[2].str());

  filename[3] << "PA_13-00_PRIMARY.txt";
  ifs[3].open(filename[3].str());

  cout << "files open" << endl;

  //8 is cathode, 9 is anode
  Double_t t[N], g1i[N] , g2i[N], g3i[N], g4i[N], g5i[N] , g6i[N], g7i[N], g8i[N], g9i[N], g10i[N];
                
  for (int i = 0 ; i < N; i++){
                    
    g_an[i] = new TGraph();
    an = Form("g_an%d", i);
    g_an[i]->SetName(an);
                    
    g_cat[i] = new TGraph();
    cat = Form("g_cat%d", i);
    g_cat[i]->SetName(cat);

    gtemp_an[i] = new TGraph();
    temp_an = Form("gtemp_an%d", i);
    gtemp_an[i]->SetName(temp_an);
                    
    gtemp_cat[i] = new TGraph();
    temp_cat= Form("gtemp_cat%d", i);
    gtemp_cat[i]->SetName(temp_cat);

    // when scanning for different gains ch 8 and 9 
    while(ifs[i] >> t[i] >> g1i[i] >> g2i[i] >> g3i[i] >> g4i[i] >> g5i[i] >> g6i[i] >> g7i[i] >> g8i[i] >> g9i[i] >> g10i[i])
      {              
	gtemp_cat[i]->SetPoint(gtemp_cat[i]->GetN(), t[i] , g8i[i]);
	gtemp_an[i]->SetPoint(gtemp_an[i]->GetN(), t[i] , g9i[i]);
      }
	
/*    // when trying to stabilize detector over long run
    while(ifs[i] >> t[i] >> g1i[i] >> g2i[i] >> g3i[i] >> g4i[i] >> g5i[i] >> g6i[i] >> g7i[i] >> g8i[i] >> g9i[i] >> g10i[i])
      {
	//Channel 8 and 9 were used as cathode and anode for quadgem respectively
	gtemp_cat[i]->SetPoint(gtemp_cat[i]->GetN(), t[i] , g8i[i]);
	gtemp_an[i]->SetPoint(gtemp_an[i]->GetN(), t[i] , g9i[i]);
      }
*/	  
    N1[i] = gtemp_cat[i]->GetN();
    
    cout << "total entries in each graph  :" << i << " " << N1[i] << endl; 

    Double_t temp_t[N1[i]][N];
    Double_t an_i[N1[i]][N];
    Double_t cat_i[N1[i]][N];
    Double_t t_scale[N1[i]][N];
    
    for(int j =0 ; j < N1[i]; j++){
      temp_t[j][i] = gtemp_cat[i]->GetX()[j];
      an_i[j][i] = gtemp_an[i]->GetY()[j];
      cat_i[j][i] = gtemp_cat[i]->GetY()[j];
      t_scale[j][i] = temp_t[j][i]-temp_t[0][i];

      //cout << " " << " t :" << t_scale[j][i] << " anode I: " << an_i[j][i] << " cathode I: " <<  cat_i[j][i] << endl;
	  
      g_an[i]->SetPoint(j, t_scale[j][i], an_i[j][i]);
      g_cat[i]->SetPoint(j, t_scale[j][i], cat_i[j][i]);

      g_an[i]->SetLineColor(2);
      g_cat[i]->SetLineColor(4);
    }
    
    xray_an = Form("fxray_an%d", i);
    fxray_an[i] = new TF1(xray_an, "pol0", 200, 500);
    fxray_an[i]->SetName(xray_an);
    fxray_an[i]->SetLineColor(2);

    xray_cat = Form("fxray_cat%d", i);
    fxray_cat[i] = new TF1(xray_cat, "pol0", 200, 500);
    fxray_cat[i]->SetName(xray_cat);
    fxray_cat[i]->SetLineColor(4);
    
    
    
  }
    
    TCanvas *c0 = new TCanvas("c0","c0", 1200, 800);
    c0->Divide(3,2);
    c0->cd(1);
    TH1D *h1 = new TH1D("h1","h1", 1200, -0.1, 1199.9);
    h1->SetTitle("dV_GEM  =  335 V");
    h1->GetYaxis()->SetRangeUser(-0.3, 2.0);
    h1->GetXaxis()->SetTitle("Time [seconds]");
    h1->GetYaxis()->SetTitle("current [nA]");
    h1->Draw();
    /*
    fxray_an[1] = new TF1("fxray_an[1]", "pol0", 600, 1000);
    fxray_an[1]->SetName("fxray_an[1]");
    fxray_cat[1] = new TF1("fxray_cat[1]", "pol0", 600, 1000);
    fxray_cat[1]->SetName("fxray_cat[1]");
    */
    g_an[0]->Fit("fxray_an0","R");
    g_cat[0]->Fit("fxray_cat0", "R");
    g_an[0]->Draw("sameL");
    g_cat[0]->Draw("sameL");

    TLegend *legend1_0 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_0->SetFillStyle(0);
    legend1_0->SetBorderSize(0);
    legend1_0->SetTextSize(0.05);
    //legend1_0->AddEntry(g_an[1],"dv GEM = 345 V", "");
    legend1_0->AddEntry(g_an[0],"X ray I = 75 uA, V = 40 kV", "");
    legend1_0->AddEntry(g_an[0], "Anode current","L");
    legend1_0->AddEntry(g_cat[0], "Cathode current","L");
    legend1_0->Draw();
    
    c0->cd(2);
    TH1D *h2 = new TH1D("h2","h2", 1000, -0.1, 999.9);
    h2->SetTitle("dV_GEM  =  340 V");
    h2->GetYaxis()->SetRangeUser(-0.5, 2.0);
    h2->GetXaxis()->SetTitle("Time [seconds]");
    h2->GetYaxis()->SetTitle("current [nA]");
    h2->Draw();
    /*
    fxray_an[2] = new TF1("fxray_an[2]", "pol0", 600, 900);
    fxray_cat[2] = new TF1("fxray_cat[2]", "pol0", 600,900);
    fxray_an[2]->SetName("fxray_an[2]");
    fxray_cat[2]->SetName("fxray_cat[2]");
    */
    g_an[1]->Fit("fxray_an1","R");
    g_cat[1]->Fit("fxray_cat1", "R");
    g_an[1]->Draw("sameL");
    g_cat[1]->Draw("sameL");

    TLegend *legend1_1 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_1->SetFillStyle(0);
    legend1_1->SetBorderSize(0);
    legend1_1->SetTextSize(0.05);
    legend1_1->AddEntry(g_an[1],"X ray I = 75 uA, V = 40 kV", "");
    legend1_1->AddEntry(g_an[1], "Anode current","L");
    legend1_1->AddEntry(g_cat[1], "Cathode current","L");
    legend1_1->Draw();

    c0->cd(3);
    TH1D *h3 = new TH1D("h3","h3", 1000, -0.1, 999.9);
    h3->SetTitle("dV_GEM  =  342 V");
    h3->GetYaxis()->SetRangeUser(-0.5, 2.0);
    h3->GetXaxis()->SetTitle("Time [seconds]");
    h3->GetYaxis()->SetTitle("current [nA]");
    h3->Draw();
    /*
    fxray_an[3] = new TF1("fxray_an[3]", "pol0", 200, 700);
    fxray_cat[3] = new TF1("fxray_cat[3]", "pol0", 200, 700);
    fxray_an[3]->SetName("fxray_an[3]");
    fxray_cat[3]->SetName("fxray_cat[3]");
    */
    g_an[2]->Fit("fxray_an2","R");
    g_cat[2]->Fit("fxray_cat2", "R");
    g_an[2]->Draw("sameL");
    g_cat[2]->Draw("sameL");
	
    TLegend *legend1_2 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_2->SetFillStyle(0);
    legend1_2->SetBorderSize(0);
    legend1_2->SetTextSize(0.05);
    legend1_2->AddEntry(g_an[2],"X ray I = 75 uA, V = 40 kV", "");
    legend1_2->AddEntry(g_an[2], "Anode current","L");
    legend1_2->AddEntry(g_cat[2], "Cathode current","L");
    legend1_2->Draw();
    
    c0->cd(4);
    TH1D *h4 = new TH1D("h4","h4", 1000, -0.1, 999.9);
    h4->SetTitle("Primary");
    h4->GetYaxis()->SetRangeUser(-0.5, 3.0);
    h4->GetXaxis()->SetTitle("Time [seconds]");
    h4->GetYaxis()->SetTitle("current [nA]");
    h4->Draw();
    /*
    fxray_an[4] = new TF1("fxray_an[4]", "pol0", 200, 650);
    fxray_cat[4] = new TF1("fxray_cat[4]", "pol0", 200, 650);
    fxray_an[4]->SetName("fxray_an[4]");
    fxray_cat[4]->SetName("fxray_cat[4]");
    */
    g_an[3]->Fit("fxray_an3","R");
    g_cat[3]->Fit("fxray_cat3", "R");
    g_an[3]->Draw("sameL");
    g_cat[3]->Draw("sameL");
    
    TLegend *legend1_3 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_3->SetFillStyle(0);
    legend1_3->SetBorderSize(0);
    legend1_3->SetTextSize(0.05);
    //legend1_3->AddEntry(g_an[1],"dv GEM = 356 V","");
    legend1_3->AddEntry(g_an[3],"X-Ray I = 75 uA, V = 40 kV","");
    legend1_3->AddEntry(g_an[3], "Anode current","L");
    legend1_3->AddEntry(g_cat[3], "Cathode current","L");
    legend1_3->Draw();
    
	
    TCanvas *c0_1 = new TCanvas("c0_1","c0_1", 1200, 800);
    c0_1->cd();
    TH1D *h0_1 = new TH1D("h0_1","h0_1", 5000, -0.1, 4999.9);
    h0_1->SetTitle("dV_GEM  =  335 V");
    h0_1->GetYaxis()->SetRangeUser(-0.5, 0.05);
    h0_1->GetXaxis()->SetRangeUser(0, 1200);
    h0_1->GetXaxis()->SetTitle("Time [seconds]");
    h0_1->GetYaxis()->SetTitle("current [nA]");
    h0_1->Draw();
    g_an[1]->Draw("sameL");
    g_cat[1]->Draw("sameL");

    TLegend *legendancat = new TLegend(0.35,.80,.55,0.93, NULL, "brNDC");
    legendancat->SetFillStyle(0);
    legendancat->SetBorderSize(0);
    legendancat->SetTextSize(0.05);
    legendancat->AddEntry(g_an[1], "Anode current","L");
    legendancat->AddEntry(g_cat[1], "Cathode current","L");
    legendancat->Draw();

    TCanvas *c0_2 = new TCanvas("c0_2","c0_2", 1200, 800);
    c0_2->cd();
    TH1D *h0_2 = new TH1D("h0_2","h0_2", 8000, -0.1, 7999.9);
    h0_2->SetTitle("dV_GEM  =  340 V");
    h0_2->GetYaxis()->SetRangeUser(-10.4, 100.);
    h0_2->GetXaxis()->SetTitle("Time [seconds]");
    h0_2->GetYaxis()->SetTitle("current [nA]");
    h0_2->Draw();
    g_an[2]->Draw("sameL");
    g_cat[2]->Draw("sameL");
    
    Float_t p0_xray_an[N],p0_xray_cat[N], p0_fe55_an[N],p0_fe55_cat[N];
    Float_t IBF[N];
    Float_t xray_an_sc[N],xray_cat_sc[N];
    cout << "calculate IBF : " << endl;
    
    for(int i = 0; i < N; i++ ){

    p0_xray_an[i] = fxray_an[i]->GetParameter(0);
    p0_xray_cat[i] = fxray_cat[i]->GetParameter(0);
    //p0_fe55_an[i] = ffe55_an[i]->GetParameter(0);
    //p0_fe55_cat[i] = ffe55_cat[i]->GetParameter(0);

    IBF[i] = ((p0_xray_cat[i]) / (p0_xray_an[i]))*100.*(-1.0) ;

    cout << " x-ray anode :" << p0_xray_an[i]  << " x ray cathode " << p0_xray_cat[i] << " fe 55 an " << p0_fe55_an[i]  << " fe 55 cat " << p0_fe55_cat[i] << endl;
    cout << " IBF :" << IBF[i] << endl;
    xray_an_sc[i] = 1.0*p0_xray_an[i];
    xray_cat_sc[i] = 1.0*p0_xray_cat[i];
    }
    
    cout  << "voltages " << endl;
    //const int n = 3;
    //drift = 1 kV/cm, transfer = induction = 2 kV/cm
    Float_t V[N] = {335, 340, 342, 0};
    
    cout  << "voltages " << endl;
    TGraph *ibf = new TGraph(N, V, IBF);
    ibf->SetName("ibf");
    ibf->SetMarkerStyle(20);
    ibf->SetMarkerSize(2.0);
    ibf->SetMarkerColor(2);



    TFile *fout = new TFile("quadgem_gain_ibf_arco2_7030.root", "RECREATE");
    //effgain->Write();
    ibf->Write();
    fout->Close();
    
    /*
  TFile *fout = new TFile("test_gr.root", "RECREATE");
  for (int i = 1; i < 7; i++){
    g_cat[i]->Write();
    g_an[i]->Write();
    gtemp_an[i]->Write();
    gtemp_cat[i]->Write();
    
  }
    */
}

