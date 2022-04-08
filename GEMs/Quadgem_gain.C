#include "TString.h"
#include "TDatime.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TCanvas.h"
#include <sstream>

            
//Channel 8 & 9 for old set of gems g8i, g9i. 8 is cathode, 9 is anode
void Quadgem_gain(){

  int N = 4;
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

  //Quad gem with reverse bias primary measurement
  //filename[1] << "quadgem_effgain_IBF/PA_16-14_quadgem_cosmic_vin3300V.txt"; // channel 9 and 10
  filename[1] << "PA_13-50_dvgem340V.txt";
  ifs[1].open(filename[1].str());

  //filename[2] << "quadgem_effgain_IBF/PA_17-01_quadgem_Fe55_Xray_Vin3375V.txt"; //channel 9 and 10
  filename[2] << "PA_14-13_dvgem342V.txt";
  ifs[2].open(filename[2].str());
  
  //filename[3] << "quadgem_effgain_IBF/PA_16-05_Vin3600V_2nditer.txt";
  filename[3] << "PA_14-26_dvgem335V.txt";
  ifs[3].open(filename[3].str());

  //filename[4] << "quadgem_effgain_IBF/PA_18-07_newquadgem_Vin3700V.txt";
  filename[4] << "PA_13-00_PRIMARY.txt";
  ifs[4].open(filename[4].str());

  //8 is cathode, 9 in anode
  Double_t t[N], g1i[N] , g2i[N], g3i[N], g4i[N], g5i[N] , g6i[N], g7i[N], g8i[N], g9i[N], g10i[N];
  
  ////////grname->Form("");
                
  for (int i = 1 ; i < N; i++){
                    
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

    /*
      filename[1] << "quadgem_effgain_IBF/PA_16-03_Vin3350V_quadgem.txt";
      ifs[1].open(filename[1].str());
      filename[2] << "quadgem_effgain_IBF/PA_16-24_Vin3375V_quadgem.txt";
      ifs[2].open(filename[2].str());
      filename[3] << "quadgem_effgain_IBF/PA_16-46_Vin3400V_quadgem.txt" ; 
      ifs[3].open(filename[3].str());
      filename[4] << "quadgem_effgain_IBF/PA_17-03_Vin3450V_quadgem.txt" ;  
      ifs[4].open(filename[4].str());
      filename[5] << "quadgem_effgain_IBF/PA_17-19_Vin3500V_quadgem.txt" ;  
      ifs[5].open(filename[5].str());
      filename[6] << "quadgem_effgain_IBF/PA_17-34_Vin3550V_quadgem.txt" ;  
      ifs[6].open(filename[6].str());
    */
    /*
    ostringstream filename;
    filename << "quadgem_effgain_IBF/PA_16-03_Vin3350V_quadge"<< i << ".txt";
    ifs[i].open(filename.str());
    */
    /* // when scanning for different gains ch 8 and 9 
    while(ifs[i] >> t[i] >> g1i[i] >> g2i[i] >> g3i[i] >> g4i[i] >> g5i[i] >> g6i[i] >> g7i[i] >> g8i[i] >> g9i[i] >> g10i[i])
      {              
	gtemp_cat[i]->SetPoint(gtemp_cat[i]->GetN(), t[i] , g8i[i]);
	gtemp_an[i]->SetPoint(gtemp_an[i]->GetN(), t[i] , g9i[i]);
      }
    */
	
    // when trying to stabilize detector over long run
    while(ifs[i] >> t[i] >> g1i[i] >> g2i[i] >> g3i[i] >> g4i[i] >> g5i[i] >> g6i[i] >> g7i[i] >> g8i[i] >> g9i[i] >> g10i[i])
      {
	//Channel 8 and 9 were used as cathode and anode for quadgem w/o screen. Previously in code was 9 & 10
	//Channel 8 and 9 were used as cathode and anode for quadgem respectively
	gtemp_cat[i]->SetPoint(gtemp_cat[i]->GetN(), t[i] , g8i[i]);
	gtemp_an[i]->SetPoint(gtemp_an[i]->GetN(), t[i] , g9i[i]);
      }
	  
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
    if(i == 1)fxray_an[i] = new TF1(xray_an, "pol0", 200, 500);
    else if(i > 1 && i < 5)fxray_an[i] = new TF1(xray_an, "pol0", 200, 500);
    else fxray_an[i] = new TF1(xray_an, "pol0", 200, 500);
    fxray_an[i]->SetName(xray_an);
    fxray_an[i]->SetLineColor(2);

    xray_cat = Form("fxray_cat%d", i);
    if(i == 1)fxray_cat[i] = new TF1(xray_cat, "pol0", 200, 500);
    else if(i > 1 && i < 5)fxray_cat[i] = new TF1(xray_cat, "pol0", 200, 500);
    else fxray_cat[i] = new TF1(xray_cat, "pol0", 200, 500);
    fxray_cat[i]->SetName(xray_cat);
    fxray_cat[i]->SetLineColor(4);
    
    //fe55_an = Form("ffe55_an%d", i);     
    // ffe55_an[i] = new TF1(fe55_an, "pol0", 0, 50);
    /*
     // For 1st iteration of Quad gem
    if(i== 5 || i==4)   ffe55_an[i] = new TF1(fe55_an, "pol0", 0, 35);
    else ffe55_an[i] = new TF1(fe55_an, "pol0", 0, 60);
    */

    // For new HVPS
    //different channels bias
    //if(i== 5 || i==4)   ffe55_an[i] = new TF1(fe55_an, "pol0", 0, 50);
    //else ffe55_an[i] = new TF1(fe55_an, "pol0", 0, 90);
    //ffe55_an[i]->SetName(fe55_an);
    //ffe55_an[i]->SetLineColor(2);
    
    //fe55_cat = Form("ffe55_cat%d", i);
    /*
    // For 1st iteration of Quad gem
    if(i== 4 || i==5)   ffe55_cat[i] = new TF1(fe55_cat, "pol0", 0, 35);
    else ffe55_cat[i] = new TF1(fe55_cat, "pol0", 0, 60);
    */
    //New HVPS
    //   different channels bias
    //if(i== 4 || i==5)   ffe55_cat[i] = new TF1(fe55_cat, "pol0", 0, 50);
    //else ffe55_cat[i] = new TF1(fe55_cat, "pol0", 0, 90);
    
    /* // For 2nd iteration of Quad gem
    if(i== 5 )   ffe55_cat[i] = new TF1(fe55_cat, "pol0", 55, 120);
    else ffe55_cat[i] = new TF1(fe55_cat, "pol0", 0, 60);
    */
    //ffe55_cat[i]->SetName(fe55_cat);
    //ffe55_cat[i]->SetLineColor(4);
    
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
    g_an[1]->Fit("fxray_an1","R");
    g_cat[1]->Fit("fxray_cat1", "R");
    g_an[1]->Draw("sameL");
    g_cat[1]->Draw("sameL");

    TLegend *legend1_0 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_0->SetFillStyle(0);
    legend1_0->SetBorderSize(0);
    legend1_0->SetTextSize(0.05);
    //legend1_0->AddEntry(g_an[1],"dv GEM = 345 V", "");
    legend1_0->AddEntry(g_an[1],"X ray I = 75 uA, V = 40 kV", "");
    legend1_0->AddEntry(g_an[1], "Anode current","L");
    legend1_0->AddEntry(g_cat[1], "Cathode current","L");
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
    g_an[2]->Fit("fxray_an2","R");
    g_cat[2]->Fit("fxray_cat2", "R");
    g_an[2]->Draw("sameL");
    g_cat[2]->Draw("sameL");

    TLegend *legend1_1 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_1->SetFillStyle(0);
    legend1_1->SetBorderSize(0);
    legend1_1->SetTextSize(0.05);
    //legend1_1->AddEntry(g_an[1],"dv GEM = 348 V", "");
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
    g_an[3]->Fit("fxray_an3","R");
    g_cat[3]->Fit("fxray_cat3", "R");
    g_an[3]->Draw("sameL");
    g_cat[3]->Draw("sameL");
	
    TLegend *legend1_2 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_2->SetFillStyle(0);
    legend1_2->SetBorderSize(0);
    legend1_2->SetTextSize(0.05);
    //legend1_2->AddEntry(g_an[1],"dv GEM = 352 V", "");
    legend1_2->AddEntry(g_an[1],"X ray I = 75 uA, V = 40 kV", "");
	legend1_2->AddEntry(g_an[1], "Anode current","L");
    legend1_2->AddEntry(g_cat[1], "Cathode current","L");
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
    g_an[4]->Fit("fxray_an4","R");
    g_cat[4]->Fit("fxray_cat4", "R");
    g_an[4]->Draw("sameL");
    g_cat[4]->Draw("sameL");
    
    TLegend *legend1_3 = new TLegend(0.55,.30,.75,0.5, NULL, "brNDC");
    legend1_3->SetFillStyle(0);
    legend1_3->SetBorderSize(0);
    legend1_3->SetTextSize(0.05);
    //legend1_3->AddEntry(g_an[1],"dv GEM = 356 V","");
    legend1_3->AddEntry(g_an[1],"X-Ray I = 75 uA, V = 40 kV","");
	legend1_3->AddEntry(g_an[1], "Anode current","L");
    legend1_3->AddEntry(g_cat[1], "Cathode current","L");
    legend1_3->Draw();
    
	
    TCanvas *c0_1 = new TCanvas("c0_1","c0_1", 1200, 800);
    c0_1->cd();
    TH1D *h0_1 = new TH1D("h0_1","h0_1", 5000, -0.1, 4999.9);
    h0_1->SetTitle("dV_GEM  =  355 V");
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
    h0_2->GetYaxis()->SetRangeUser(-1.4, 0.5);
    h0_2->GetXaxis()->SetTitle("Time [seconds]");
    h0_2->GetYaxis()->SetTitle("current [nA]");
    h0_2->Draw();
    g_an[2]->Draw("sameL");
    g_cat[2]->Draw("sameL");
    
    Float_t p0_xray_an[N],p0_xray_cat[N], p0_fe55_an[N],p0_fe55_cat[N];
    Float_t IBF[N];
    Float_t xray_an_sc[N],xray_cat_sc[N];

	/////////////////////TODO: Remove fe55 ?
    for(int i = 0; i < 3; i++ ){

    p0_xray_an[i] = fxray_an[i+1]->GetParameter(0);
    p0_xray_cat[i] = fxray_cat[i+1]->GetParameter(0);
    p0_fe55_an[i] = ffe55_an[i+1]->GetParameter(0);
    p0_fe55_cat[i] = ffe55_cat[i+1]->GetParameter(0);

    IBF[i] = ((p0_xray_cat[i]) / (p0_xray_an[i]))*100.*(-1.0) ;

    cout << " x-ray anode :" << p0_xray_an[i]  << " x ray cathode " << p0_xray_cat[i] << " fe 55 an " << p0_fe55_an[i]  << " fe 55 cat " << p0_fe55_cat[i] << endl;
    cout << " IBF :" << IBF[i] << endl;
    xray_an_sc[i] = 1.0*p0_xray_an[i];
    xray_cat_sc[i] = 1.0*p0_xray_cat[i];
    }
    
    cout  << "voltages " << endl;
    const int n = 3;
    //drift = 1 kV/cm, transfer = induction = 2 kV/cm
    Float_t V[n] = {335, 340, 342};
    
    cout  << "voltages " << endl;
    TGraph *ibf = new TGraph(n, V, IBF);
    ibf->SetName("ibf");
    ibf->SetMarkerStyle(20);
    ibf->SetMarkerSize(2.0);
    ibf->SetMarkerColor(2);

	/////////////////////Why these odd numbers? Also should probably only be 3 of them here...
    Float_t XrayI[n] = {5, 7, 9};
    TGraph *xray_an_cur = new TGraph(n , XrayI, xray_an_sc);
    xray_an_cur->SetName("xray_an_cur");
    xray_an_cur->SetMarkerStyle(20);
    xray_an_cur->SetMarkerSize(2.0);
    xray_an_cur->SetMarkerColor(4);
    xray_an_cur->SetLineColor(4);
    
    TGraph *xray_cat_cur = new TGraph(n , XrayI, xray_cat_sc);
    xray_cat_cur->SetName("xray_cat_cur");
    xray_cat_cur->SetMarkerStyle(20);
    xray_cat_cur->SetMarkerSize(2.0);
    xray_cat_cur->SetMarkerColor(2);
    xray_cat_cur->SetLineColor(2);
    
    TCanvas *c0_3 = new TCanvas("c0_3","c0_3", 1200, 800);
    c0_3->cd();
    TH1F *hist0_1 = new TH1F("hist0_1","",15,0.,15);
    hist0_1->GetYaxis()->SetRangeUser(-1.0, 4.0);
    hist0_1->GetYaxis()->SetTitle("Current [nA]");
    //hist0_1->GetYaxis()->SetTitleColor(4);
    //hist0_1->GetXaxis()->SetTitle("dV GEM [V]");
    hist0_1->GetXaxis()->SetTitle("X-Ray I [uA]");
    hist0_1->Draw();
    xray_an_cur->Draw("samePL");
    xray_cat_cur->Draw("samePL");

    TLegend *legend0_1 = new TLegend(0.25,.65,.45,0.85, NULL, "brNDC");
    legend0_1->SetFillStyle(0);
    legend0_1->SetBorderSize(0);
    legend0_1->SetTextSize(0.03);
    legend0_1->AddEntry(xray_an_cur,"XRay operating at V = 40 kV for various --- setting for various effective Gain","");
    legend0_1->AddEntry(xray_an_cur,"Measured current from Anode","PL");
    legend0_1->AddEntry(xray_cat_cur,"Measured current from Cathode","PL");
    legend0_1->Draw();
      
    // Effective Gain
    const int slope_pA = 3397 ; // charge per mV
    const int primary_arco2_70_30 = 217 ; //  ArCO2 (70:30)
    //const int primary_arco2_80_20 = 223 ; //  ArCO2 (80:20)

	/////////////////////////// Sig ?
    //New HVPS, drift = 1 kV/cm, transfer = induction = 2 kV/cm
    Float_t sig[n] = {228, 360, 480}; // with screen and cathode+screen with HVPS fanout    
    
    //ArCO2 : 80:20
    const int n3 =7;
    //Float_t v2_quad[n3] = { 3300, 3350, 3400, 3450, 3500}; 
    //Float_t sig2_quad[n3] = { 144, 240, 300, 440, 570, 680, 1200 };
          
    Float_t eff_gain[n], eff_gain2[n3];
    
    for (int i =0 ; i < n; i++) {
    eff_gain[i] = (sig[i]*slope_pA )/primary_arco2_70_30;
    }

/*    for (int i =0 ; i < n3; i++) {
    eff_gain2[i] = (sig2_quad[i]*slope_pA )/primary_arco2_80_20;
  }
    
    // GAIN VARIATION WITH TIME FOR 2 DIFFERENT DETECTOR ORIENTATION W.R.T PLANE
    const int n4 = 4;
    Float_t time[n4] = {15, 26, 37, 40};
    Float_t sig_vert[n4] = {390, 286, 220, 200};

    Float_t time2[n4] = {13, 23, 34, 41};
    Float_t sig_hor[n4] = {360, 380, 396, 418};
    

    Float_t eff_gain3[n4], eff_gain4[n4];
    for (int i = 0; i < n4; i++){
      
      eff_gain3[i] = (sig_vert[i]*slope_pA )/primary_arco2_70_30;
      eff_gain4[i] = (sig_hor[i]*slope_pA )/primary_arco2_70_30;
    }
*/
    
    TGraph *effgain =  new TGraph(n, V , eff_gain);
    effgain->SetName("effgain");
    effgain->SetMarkerStyle(20);
    effgain->SetMarkerSize(2.0);
    effgain->SetMarkerColor(4);
/*
    TGraph *effgain2 =  new TGraph(n3, v2_quad , eff_gain2);
    effgain2->SetName("effgain2");
    effgain2->SetMarkerStyle(20);
    effgain2->SetMarkerSize(2.0);
    effgain2->SetMarkerColor(4);

    TGraph *effgain_vs_time =  new TGraph(n4, time , eff_gain3);
    effgain_vs_time->SetName("effgain_vs_time");
    effgain_vs_time->SetMarkerStyle(20);
    effgain_vs_time->SetMarkerSize(2.0);
    effgain_vs_time->SetMarkerColor(6);

    TGraph *effgain_hor_vs_time =  new TGraph(n4, time2 , eff_gain4);
    effgain_hor_vs_time->SetName("effgain_hor_vs_time");
    effgain_hor_vs_time->SetMarkerStyle(20);
    effgain_hor_vs_time->SetMarkerSize(2.0);
    effgain_hor_vs_time->SetMarkerColor(2);
*/
    TCanvas *c1 = new TCanvas("c1","c1", 1200, 800);
    c1->cd();
    gStyle->SetOptStat(0000000);
    //ibf->GetYaxis()->SetTitle("IBF (%)");
    //ibf->GetXaxis()->SetTitle("dV GEM [V]");
    //ibf->GetYaxis()->SetRangeUser(500, 30000);
    //ibf->GetXaxis()->SetRangeUser(300, 400);

    //TH1F *hist1 = new TH1F("hist1","",100,300,400);
    //hist1->GetYaxis()->SetTitle("IBF (%)");
    //hist1->GetXaxis()->SetTitle("dV GEM [V]");
    //hist1->Draw();
    TPad *pad1 = new TPad("pad1","",0,0,1,1);
    TPad *pad2 = new TPad("pad2","",0,0,1,1);
    pad2->SetFillStyle(4000); //will be transparent
    pad2->SetFrameFillStyle(0);
    //Draw the first graph
    pad1->Draw();
    pad1->cd();
    pad1->SetTicky(0);
    
    TH1F *hist0 = new TH1F("hist0","",30,335,365);
    hist0->GetYaxis()->SetRangeUser(0, 16000.);
    hist0->GetYaxis()->SetTitle("Effective Gain");
    hist0->GetYaxis()->SetTitleColor(4);
    hist0->GetXaxis()->SetTitle("dV GEM [V]");
    hist0->Draw("");
    //effgain->Draw("P");
    effgain->Draw("sameP");
    //c1->Update();

    //TH1F *hist2 = new TH1F("hist2","",100,300,400);
    //Float_t rightmax = 1.1*effgain->GetMaximum();
    //cout << "rht max :" << rightmax << " h max :" << effgain->GetMaximum() << endl;
    //Float_t scale = gPad->GetUymax()/rightmax;
    //cout << " Uymax :" << gPad->GetUymax() << endl;
    //cout << " Uyin :" << gPad->GetUymin() << endl;
    //hist2->SetLineColor(kRed);
    //hist2->Scale(scale);
    //hist2->Draw("same");
    //effgain->Draw("same");
    //draw an axis on the right side
    TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
    gPad->GetUxmax(), gPad->GetUymax(),0,50,510,"+L");
    axis->SetTextColor(kRed);
    axis->SetTextColor(kRed);
    axis->Draw();
    //Draw the second graph
    pad2->Draw();
    pad2->cd();
    pad2->SetTicky(0);
    //effgain->GetYaxis()->SetTitle("Effecive Gain");
    //effgain->Draw("APY+");
    //TH1F *hist1 = new TH1F("hist1","",250,3500,3750);
    TH1F *hist1 = new TH1F("hist1","",30,335,365);
    hist1->GetYaxis()->SetRangeUser(5., 25.);
    hist1->GetYaxis()->SetTitle("IBF (%)");
    hist1->GetYaxis()->SetTitleOffset(-0.4);
    hist1->GetYaxis()->SetTitleColor(2);
    hist1->Draw("sameY+");
    
    //ibf->GetYaxis()->SetTitle("IBF (%)");
    //ibf->GetYaxis()->SetTitleOffset(-0.4);
    //ibf->GetYaxis()->SetTitleColor(2);

    //ibf->Draw("APY+");
    ibf->Draw("sameP");

    TCanvas *c2 = new TCanvas("c2","c2", 800, 600);
    c2->cd();
    gStyle->SetOptStat(0000000);
    TH1F *hist2 = new TH1F("hist2","",550,3200,3750);
    hist2->GetYaxis()->SetRangeUser(0, 20000.);
    hist2->GetYaxis()->SetTitle("Effective Gain");    
    hist2->GetXaxis()->SetTitle("Total Voltage [V]");
    hist2->Draw("");
    //effgain->Draw("P");
    effgain->Draw("sameP");
    //effgain2->Draw("sameP");

    TLegend *legend2 = new TLegend(0.35,.80,.55,0.93, NULL, "brNDC");
    legend2->SetFillStyle(0);
    legend2->SetBorderSize(0);
    legend2->SetTextSize(0.05);
    legend2->AddEntry(effgain, "ArCO2(70:30)","P");
    //legend2->AddEntry(effgain2, "ArCO2 (80:20)","p");
    legend2->Draw();

/*    TCanvas *c3 = new TCanvas("c3","c3", 800, 600);
    c3->cd();
    gStyle->SetOptStat(0000000);
    TH1F *hist3 = new TH1F("hist3","",45,-0.1,44.9);
    hist3->GetYaxis()->SetRangeUser(2000, 7000.);
    hist3->GetYaxis()->SetTitle("Effective Gain");    
    hist3->GetXaxis()->SetTitle("Time [minutes]");
    hist3->Draw("");
    effgain_vs_time->Draw("sameP");
    effgain_hor_vs_time->Draw("sameP");

    TLegend *legend3 = new TLegend(0.15,.30,.35,0.43, NULL, "brNDC");
    legend3->SetFillStyle(0);
    legend3->SetBorderSize(0);
    legend3->SetTextSize(0.04);
    legend3->AddEntry(effgain_vs_time, "dV GEM = 360 V, ArCO2 (70:30)"," ");
    legend3->AddEntry(effgain_vs_time, "Verical set up","P");
    legend3->AddEntry(effgain_hor_vs_time, "Horizontal set up","p");
    legend3->Draw();
*/    
  
    //TFile *fout = new TFile("triplegemnew_gain_ibf_arco2_7030.root", "RECREATE");
    TFile *fout = new TFile("quadgem_gain_ibf_arco2_7030.root", "RECREATE");
    // TFile *fout = new TFile("quadgemnew_iter2_xrayconfig4_gain_ibf_arco2_7030.root", "RECREATE");
    effgain->Write();
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

