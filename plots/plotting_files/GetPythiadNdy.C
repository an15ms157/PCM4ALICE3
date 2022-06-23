#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingMeson.h"
void GetPythiadNdy(){
StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms o


Int_t collisionSystem = 1 ;//  pp = 0 || PbPb = 1; 

TFile * fileRec;
TLatex *lt_dNdy_Pythia_F_b;
TLatex *lt_dNdy_Pythia_B_b;
Int_t ScaleFactor_Pi0;
Int_t ScaleFactor_Eta;
TString colli_Sys; 

switch(collisionSystem){
    case 0:{
    cout << "pp system"<< endl;    
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3_pp_check.root");
    lt_dNdy_Pythia_F_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    lt_dNdy_Pythia_B_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    gSystem->Exec("mkdir dNdy_Pythia/pp");
    gSystem->cd("./dNdy_Pythia/pp");
    colli_Sys = "pp";
        break;
    }
    case 1:{
    cout << "PbPb system"<< endl;
        //TFile * fileRec = new TFile("./ana_withft3.root");
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3_PbPb.root");
    lt_dNdy_Pythia_F_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 14 TeV}");
    lt_dNdy_Pythia_B_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec("mkdir dNdy_Pythia/PbPb");
    gSystem->cd("./dNdy_Pythia/PbPb");
    colli_Sys = "PbPb";

        break;
    }
}

double fMaxPt=10.0;
Int_t Font=42;
Double_t TextSize=0.025;
Double_t TextSize_lable=0.025;
Double_t TextSize_title=0.03;
Double_t TextSize_latex=20;
Double_t LabelOffsetLog=-0.03;

Double_t pt_bin_proj_fine[13]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_fine  = 12;

Double_t etaF_low1 = 1.75;
Double_t etaF_low2 = 3;
Double_t etaF_high1 = 3.0;
Double_t etaF_high2 = 4.0;
Double_t etaF_mid1 = 1.75;
Double_t etaF_mid2 = 4.0;


Double_t etaB_low1   = 0.0;
Double_t etaB_low2   = 0.8;
Double_t etaB_high1  = 0.0;
Double_t etaB_high2  = 1.3;
Double_t etaB_mid1  = 0.8;
Double_t etaB_mid2  = 1.3;





/*
double pt_bin_proj[nBinsPt+1];
for(int i=0; i<nBinsPt+1; i++){
      if (i < 10) pt_bin_proj[i]            =  0.1*i;
      else if(i<20) pt_bin_proj[i]          = 1.0 + 0.2*(i-10);
      else if(i<22) pt_bin_proj[i]          = 3.0 + 0.5*(i-20);
      else pt_bin_proj[i]                   = fMaxPt;
}
*/

TH2D * histRapPt_ALL_Pi0_F          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F");
TH2D * histRapPt_ALL_Eta_F          = (TH2D*) fileRec->Get("hRapidityPt_Eta_F");

TH2D * histRapPt_ALL_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B");
TH2D * histRapPt_ALL_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B");

TH1D * hNPrimChPiP = (TH1D*) fileRec->Get("hNPrimChPiP");
int NEvents = hNPrimChPiP->GetEntries();


histRapPt_ALL_Pi0_F->Sumw2();
histRapPt_ALL_Eta_F->Sumw2();
histRapPt_ALL_Pi0_B->Sumw2();
histRapPt_ALL_Eta_B->Sumw2();



TCanvas* c_dNdy_Pythia = new TCanvas("c_dNdy_Pythia","c_dNdy_Pythia",0,0,800,800);  // gives the page size
DrawGammaCanvasSettings( c_dNdy_Pythia, 0.1, 0.02, 0.02, 0.1);
c_dNdy_Pythia->SetLogy();  
c_dNdy_Pythia->SetLogx();  


////////////////////////     Forward       //////////////////////////

    ///////////      Dividing in rapidity     ///////////
TAxis *xaxis_F_Pi0 = histRapPt_ALL_Pi0_F->GetXaxis();

Int_t bin_etaF_mid1 = xaxis_F_Pi0->FindBin(etaF_mid1 + 0.01);
Int_t bin_etaF_mid2 = xaxis_F_Pi0->FindBin(etaF_mid2 - 0.01);

TH1 * histPt_ALL_rap_F_mid1_to_mid2_Pi0 = histRapPt_ALL_Pi0_F->ProjectionY("histPt_ALL_rap_F_mid1_to_mid2_Pi0",bin_etaF_mid1,bin_etaF_mid2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Eta = histRapPt_ALL_Eta_F->ProjectionY("histPt_ALL_rap_F_mid1_to_mid2_Eta",bin_etaF_mid1,bin_etaF_mid2); 


histPt_ALL_rap_F_mid1_to_mid2_Pi0->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta->Sumw2();



//REBINNING
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Sumw2();

//SCALING

DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin);


// Labelling //
SetStyleHistoTH1ForGraphs(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin, "p_{T} (GeV/c)", "1/(Bin_width*N_{ev})#frac{dN}{dy}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

// CHECKER LABELING //
DrawGammaSetMarker(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin,24,1.0, kRed , kRed);
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Scale(1./NEvents);
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Scale(1./(etaF_mid2-etaF_mid1));
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Draw("E1");
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->GetXaxis()->SetRangeUser(0.1001,10.0);
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->GetYaxis()->SetRangeUser(0.00001,1000);
DrawGammaSetMarker(histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin,24,1.0, kGreen+3 , kGreen+3);
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Scale(1./NEvents);
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Scale(1./(etaF_mid2-etaF_mid1));
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Draw("SAME,E1");



////////////////////////     Barrel       //////////////////////////

    ///////////      Dividing in rapidity     ///////////
TAxis *xaxis_B_Pi0 = histRapPt_ALL_Pi0_B->GetXaxis();

Int_t bin_etaB_high1 = xaxis_B_Pi0->FindBin(etaB_high1 + 0.01);
Int_t bin_etaB_high2 = xaxis_B_Pi0->FindBin(etaB_high2 - 0.01);

TH1 * histPt_ALL_rap_B_high1_to_high2_Pi0 = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_rap_B_high1_to_high2_Pi0",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Eta = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_rap_B_high1_to_high2_Eta",bin_etaB_high1,bin_etaB_high2); 


histPt_ALL_rap_B_high1_to_high2_Pi0->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Eta->Sumw2();



//REBINNING
TH1F* histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->Sumw2();

//SCALING

DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Eta_Rebin);

// CHECKER LABELING //
DrawGammaSetMarker(histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin,8,1.0, kRed , kRed);
histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->Scale(1./NEvents);
histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->Scale(1./(etaB_high2-etaB_high1));
histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->Draw("SAME,E1");
DrawGammaSetMarker(histPt_ALL_rap_B_high1_to_high2_Eta_Rebin,8,1.0, kGreen+3 , kGreen+3);
histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->Scale(1./NEvents);
histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->Scale(1./(etaB_high2-etaB_high1));
histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->Draw("SAME,E1");


auto l_dNdy_Pythia = new TLegend(0.2, 0.25, 0.5, 0.5);
l_dNdy_Pythia->SetHeader("");
l_dNdy_Pythia->SetBorderSize(0);
l_dNdy_Pythia->SetFillStyle(0);
l_dNdy_Pythia->SetTextSize(TextSize);
l_dNdy_Pythia->AddEntry(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin,Form("#pi^{0} : %.2f < |y| < %.2f",etaF_mid1,etaF_mid2));
l_dNdy_Pythia->AddEntry(histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin,Form("#eta  : %.2f < |y| < %.2f",etaF_mid1,etaF_mid2));
l_dNdy_Pythia->AddEntry(histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin,Form("#pi^{0} : %.2f < |y| < %.2f",etaB_high1,etaB_high2));
l_dNdy_Pythia->AddEntry(histPt_ALL_rap_B_high1_to_high2_Eta_Rebin,Form("#eta  : %.2f < |y| < %.2f",etaB_high1,etaB_high2));
l_dNdy_Pythia->Draw("SAME");

c_dNdy_Pythia->SaveAs("./Pythia_dNdy.png");
c_dNdy_Pythia->Close();

const char *outputFile = "../../ALICE3_significance_input.root"; // merge output files after analysis was run to keep file size moderate
auto fout = TFile::Open(outputFile, "UPDATE");
//TFile *outputfile = TFile::Open("../../ALICE3_significance_input.root","UPDATE");
fout->cd();
fout->mkdir(colli_Sys);
fout->cd(colli_Sys);

histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->GetXaxis()->SetTitle("p_{T} (GeV/c)");
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->GetYaxis()->SetTitle("#frac{1}{Bin_width*N_{event}} #frac{dN}{dy}");
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->SetName(Form("histPt_Signal_dNdy_rap_F_%0.2f_to_%0.2f_Pi0_Rebin",etaF_mid1,etaF_mid2));
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Write();

histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->GetXaxis()->SetTitle("p_{T} (GeV/c)");
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->GetYaxis()->SetTitle("#frac{1}{Bin_width*N_{event}} #frac{dN}{dy}");
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->SetName(Form("histPt_Signal_dNdy_rap_F_%0.2f_to_%0.2f_Eta_Rebin",etaF_mid1,etaF_mid2));
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Write();

histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->GetXaxis()->SetTitle("p_{T} (GeV/c)");
histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->GetYaxis()->SetTitle("#frac{1}{Bin_width*N_{event}} #frac{dN}{dy}");
histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->SetName(Form("histPt_Signal_dNdy_rap_B_%0.2f_to_%0.2f_Pi0_Rebin",etaB_high1,etaB_high2));
histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->Write();

histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->GetXaxis()->SetTitle("p_{T} (GeV/c)");
histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->GetYaxis()->SetTitle("#frac{1}{Bin_width*N_{event}} #frac{dN}{dy}");
histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->SetName(Form("histPt_Signal_dNdy_rap_B_%0.2f_to_%0.2f_Eta_Rebin",etaB_high1,etaB_high2));
histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->Write();

fout->Close();
}