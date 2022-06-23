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
void mesonAcc(){
StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or

//gStyle->SetOptStat(0);
//gStyle->SetLineWidth(2);
//gStyle->SetPadLeftMargin(0.15);
//gStyle->SetPadBottomMargin(0.15);
//gStyle->SetPadTopMargin(0.05);
//gStyle->SetPadRightMargin(0.05);
//gStyle->SetTitleSize(0.06);
//gStyle->SetTitleSize(0.06,"Y");
//gStyle->SetTitleOffset(1,"Y");
//gStyle->SetTitleOffset(1,"X");
//gStyle->SetLabelSize(0.05);
//gStyle->SetLabelSize(0.05,"Y");
//gStyle->SetFrameLineWidth(2);
//gStyle->SetNdivisions(505,"X");
//gStyle->SetNdivisions(505,"Y");
//gStyle->SetPadTickX(1);
//gStyle->SetPadTickY(1);

/*
gStyle->SetOptTitle(0);
//gStyle->SetOptStat(0);
gStyle->SetLineWidth(2);
gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadBottomMargin(0.15);
gStyle->SetPadTopMargin(0.05);
gStyle->SetPadRightMargin(0.05);
gStyle->SetTitleSize(0.06);
gStyle->SetTitleSize(0.06,"Y");
gStyle->SetTitleOffset(1,"Y");
gStyle->SetTitleOffset(1,"X");
gStyle->SetLabelSize(0.05);
gStyle->SetLabelSize(0.05,"Y");
gStyle->SetFrameLineWidth(2);
gStyle->SetNdivisions(505,"X");
gStyle->SetNdivisions(505,"Y");
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);
*/
//   TO MOVE STATBOX
//gStyle->SetStatX(.44);
//gStyle->SetStatY(.83);

//   TO VANISH STAT BOX 
                                                ////////////////FORWARD///////////////


Int_t collisionSystem = 0 ;//  pp = 0 || PbPb = 1; 

TFile * fileRec;
TLatex *lt_mesonAcc_F_b;
TLatex *lt_mesonAcc_B_b;
Int_t ScaleFactor_Pi0;
Int_t ScaleFactor_Eta;

switch(collisionSystem){
    case 0:{
    cout << "pp system"<< endl;    
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/output/ana_pTcut_withft3.root");
    lt_mesonAcc_F_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    lt_mesonAcc_B_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    ScaleFactor_Pi0 = 1;
    ScaleFactor_Eta = 10;
    gSystem->Exec("mkdir mesonAcc/pp");
    gSystem->cd("./mesonAcc/pp");

        break;
    }
    case 1:{
    cout << "PbPb system"<< endl;
        //TFile * fileRec = new TFile("./ana_withft3.root");
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3_PbPb.root");
    lt_mesonAcc_F_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 14 TeV}");
    lt_mesonAcc_B_b = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 14 TeV}");
    ScaleFactor_Pi0 = 10;
    ScaleFactor_Eta = 100;
    gSystem->Exec("mkdir mesonAcc/PbPb");
    gSystem->cd("./mesonAcc/PbPb");

        break;
    }
}

double fMaxPt=10.0;
Int_t Font=42;
Double_t TextSize=0.025;
Double_t TextSize_lable=0.03;
Double_t TextSize_title=0.04;
Double_t TextSize_latex=20;
Double_t LabelOffsetLog=-0.015;

//const int nBinsPt=100;

Double_t pt_bin_proj[]={0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6,2.7,2.8,2.9,3.0,3.1,3.2,3.3,3.4,3.5,3.6,3.7,3.8,3.9,4.0,4.1,4.2,4.3,4.4,4.5,4.6,4.7,4.8,4.9,5.0};
Int_t nbinspt_proj  = sizeof(pt_bin_proj)/sizeof(*pt_bin_proj) -1;

//Double_t pt_bin_proj_fine[]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
//Int_t nbinspt_proj_fine  = (sizeof(pt_bin_proj)/sizeof(*pt_bin_proj)) -1;


Double_t pt_bin_proj_fine[15]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,2.5,3.0,4.0,6.0,8.0,10.0 };
Int_t nbinspt_proj_fine  = 14;


Double_t etaF_low1 = 1.75;
Double_t etaF_low2 = 3;
Double_t etaF_high1 = 3.0;
Double_t etaF_high2 = 4.0;
Double_t etaF_mid1 = 1.75;
Double_t etaF_mid2 = 4.0;


Double_t etaB_low1   = 0.0;
Double_t etaB_low2   = 0.8;
Double_t etaB_high1  = 0.;
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
TH2D * histRapPt_ALL_Pi0_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH2D * histRapPt_ALL_Eta_F          = (TH2D*) fileRec->Get("hRapidityPt_Eta_F");
TH2D * histRapPt_ALL_Eta_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");

TH2D * histRapPt_ALL_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B");
TH2D * histRapPt_ALL_Pi0_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH2D * histRapPt_ALL_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B");
TH2D * histRapPt_ALL_Eta_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");



///////////////  Acceptance at different rapidity PLOT    ///////////////


histRapPt_ALL_Pi0_F->Sumw2();
histRapPt_ALL_Pi0_F_GG->Sumw2();
histRapPt_ALL_Eta_F->Sumw2();
histRapPt_ALL_Eta_F_GG->Sumw2();
histRapPt_ALL_Pi0_B->Sumw2();
histRapPt_ALL_Pi0_B_GG->Sumw2();
histRapPt_ALL_Eta_B->Sumw2();
histRapPt_ALL_Eta_B_GG->Sumw2();

////////////////////////     Forward       //////////////////////////
TCanvas* c_mesonAcc = new TCanvas("c_mesonAcc","c_mesonAcc",0,0,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c_mesonAcc, 0.1, 0.02, 0.02, 0.1);
c_mesonAcc->Divide(2,1);
c_mesonAcc->cd(1)->SetLogy();  
c_mesonAcc->cd(1);

///////////      Dividing in rapidity     ///////////
TAxis *xaxis_F_Pi0 = histRapPt_ALL_Pi0_F->GetXaxis();
Int_t bin_etaF_low1 = xaxis_F_Pi0->FindBin(etaF_low1 + 0.0001);
Int_t bin_etaF_low2 = xaxis_F_Pi0->FindBin(etaF_low2 - 0.0001);
Int_t bin_etaF_high1 = xaxis_F_Pi0->FindBin(etaF_high1 + 0.0001);
Int_t bin_etaF_high2 = xaxis_F_Pi0->FindBin(etaF_high2 - 0.0001);
Int_t bin_etaF_mid1 = xaxis_F_Pi0->FindBin(etaF_mid1 + 0.0001);
Int_t bin_etaF_mid2 = xaxis_F_Pi0->FindBin(etaF_mid2 - 0.0001);

TH1 * histPt_ALL_rap_F_low1_to_low2_Pi0 = histRapPt_ALL_Pi0_F->ProjectionY("histPt_ALL_rap_F_low1_to_low2_Pi0",bin_etaF_low1,bin_etaF_low2); 
TH1 * histPt_ALL_rap_F_high1_to_high2_Pi0 = histRapPt_ALL_Pi0_F->ProjectionY("histPt_ALL_rap_F_high1_to_high2_Pi0",bin_etaF_high1,bin_etaF_high2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Pi0 = histRapPt_ALL_Pi0_F->ProjectionY("histPt_ALL_rap_F_mid1_to_mid2_Pi0",bin_etaF_mid1,bin_etaF_mid2); 

TH1 * histPt_ALL_GG_rap_F_low1_to_low2_Pi0 = histRapPt_ALL_Pi0_F_GG->ProjectionY("histPt_ALL_GG_rap_F_low1_to_low2_Pi0",bin_etaF_low1,bin_etaF_low2); 
TH1 * histPt_ALL_GG_rap_F_high1_to_high2_Pi0 = histRapPt_ALL_Pi0_F_GG->ProjectionY("histPt_ALL_GG_rap_F_high1_to_high2_Pi0",bin_etaF_high1,bin_etaF_high2); 
TH1 * histPt_ALL_GG_rap_F_mid1_to_mid2_Pi0 = histRapPt_ALL_Pi0_F_GG->ProjectionY("histPt_ALL_GG_rap_F_mid1_to_mid2_Pi0",bin_etaF_mid1,bin_etaF_mid2); 

TH1 * histPt_ALL_rap_F_low1_to_low2_Eta = histRapPt_ALL_Eta_F->ProjectionY("histPt_ALL_rap_F_low1_to_low2_Eta",bin_etaF_low1,bin_etaF_low2); 
TH1 * histPt_ALL_rap_F_high1_to_high2_Eta = histRapPt_ALL_Eta_F->ProjectionY("histPt_ALL_rap_F_high1_to_high2_Eta",bin_etaF_high1,bin_etaF_high2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Eta = histRapPt_ALL_Eta_F->ProjectionY("histPt_ALL_rap_F_mid1_to_mid2_Eta",bin_etaF_mid1,bin_etaF_mid2); 

TH1 * histPt_ALL_GG_rap_F_low1_to_low2_Eta = histRapPt_ALL_Eta_F_GG->ProjectionY("histPt_ALL_GG_rap_F_low1_to_low2_Eta",bin_etaF_low1,bin_etaF_low2); 
TH1 * histPt_ALL_GG_rap_F_high1_to_high2_Eta = histRapPt_ALL_Eta_F_GG->ProjectionY("histPt_ALL_GG_rap_F_high1_to_high2_Eta",bin_etaF_high1,bin_etaF_high2); 
TH1 * histPt_ALL_GG_rap_F_mid1_to_mid2_Eta = histRapPt_ALL_Eta_F_GG->ProjectionY("histPt_ALL_GG_rap_F_mid1_to_mid2_Eta",bin_etaF_mid1,bin_etaF_mid2); 

histPt_ALL_rap_F_low1_to_low2_Pi0->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Pi0->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Pi0->Sumw2();
histPt_ALL_GG_rap_F_low1_to_low2_Pi0->Sumw2();
histPt_ALL_GG_rap_F_high1_to_high2_Pi0->Sumw2();
histPt_ALL_GG_rap_F_mid1_to_mid2_Pi0->Sumw2();
histPt_ALL_rap_F_low1_to_low2_Eta->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Eta->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta->Sumw2();
histPt_ALL_GG_rap_F_low1_to_low2_Eta->Sumw2();
histPt_ALL_GG_rap_F_high1_to_high2_Eta->Sumw2();
histPt_ALL_GG_rap_F_mid1_to_mid2_Eta->Sumw2();

//REBINNING
TH1F* histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin        = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_GG_rap_F_low1_to_low2_Pi0_Rebin     = (TH1F*) histPt_ALL_GG_rap_F_low1_to_low2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_GG_rap_F_low1_to_low2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_GG_rap_F_high1_to_high2_Pi0_Rebin        = (TH1F*) histPt_ALL_GG_rap_F_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_GG_rap_F_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_GG_rap_F_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_ALL_GG_rap_F_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);


TH1F* histPt_ALL_rap_F_low1_to_low2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_low1_to_low2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_high1_to_high2_Eta_Rebin        = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_GG_rap_F_low1_to_low2_Eta_Rebin     = (TH1F*) histPt_ALL_GG_rap_F_low1_to_low2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_GG_rap_F_low1_to_low2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_GG_rap_F_high1_to_high2_Eta_Rebin        = (TH1F*) histPt_ALL_GG_rap_F_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_GG_rap_F_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_GG_rap_F_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_ALL_GG_rap_F_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Sumw2();
histPt_ALL_GG_rap_F_low1_to_low2_Pi0_Rebin->Sumw2();
histPt_ALL_GG_rap_F_high1_to_high2_Pi0_Rebin->Sumw2();
histPt_ALL_GG_rap_F_mid1_to_mid2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_F_low1_to_low2_Eta_Rebin->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Eta_Rebin->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Sumw2();
histPt_ALL_GG_rap_F_low1_to_low2_Eta_Rebin->Sumw2();
histPt_ALL_GG_rap_F_high1_to_high2_Eta_Rebin->Sumw2();
histPt_ALL_GG_rap_F_mid1_to_mid2_Eta_Rebin->Sumw2();

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin);

DivideTH1ByBinWidth(histPt_ALL_GG_rap_F_low1_to_low2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_GG_rap_F_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_GG_rap_F_mid1_to_mid2_Pi0_Rebin);

DivideTH1ByBinWidth(histPt_ALL_rap_F_low1_to_low2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_high1_to_high2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin);

DivideTH1ByBinWidth(histPt_ALL_GG_rap_F_low1_to_low2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_GG_rap_F_high1_to_high2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_GG_rap_F_mid1_to_mid2_Eta_Rebin);

//  ACCEPTANCE
TH1F* histPt_Acceptance_rap_F_low1_to_low2_Pi0  = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin->Clone("histPt_Acceptance_rap_F_low1_to_low2_Pi0");
histPt_Acceptance_rap_F_low1_to_low2_Pi0->Divide(histPt_ALL_GG_rap_F_low1_to_low2_Pi0_Rebin, histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin, 1,1,"B");
TH1F* histPt_Acceptance_rap_F_high1_to_high2_Pi0  = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin->Clone("histPt_Acceptance_rap_F_high1_to_high2_Pi0");
histPt_Acceptance_rap_F_high1_to_high2_Pi0->Divide(histPt_ALL_GG_rap_F_high1_to_high2_Pi0_Rebin, histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin, 1,1,"B");
TH1F* histPt_Acceptance_rap_F_mid1_to_mid2_Pi0  = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin->Clone("histPt_Acceptance_rap_F_mid1_to_mid2_Pi0");
histPt_Acceptance_rap_F_mid1_to_mid2_Pi0->Divide(histPt_ALL_GG_rap_F_mid1_to_mid2_Pi0_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin, 1,1,"B");

TH1F* histPt_Acceptance_rap_F_low1_to_low2_Eta  = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Eta_Rebin->Clone("histPt_Acceptance_rap_F_low1_to_low2_Eta");
histPt_Acceptance_rap_F_low1_to_low2_Eta->Divide(histPt_ALL_GG_rap_F_low1_to_low2_Eta_Rebin, histPt_ALL_rap_F_low1_to_low2_Eta_Rebin, 1,1,"B");
TH1F* histPt_Acceptance_rap_F_high1_to_high2_Eta  = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Eta_Rebin->Clone("histPt_Acceptance_rap_F_high1_to_high2_Eta");
histPt_Acceptance_rap_F_high1_to_high2_Eta->Divide(histPt_ALL_GG_rap_F_high1_to_high2_Eta_Rebin, histPt_ALL_rap_F_high1_to_high2_Eta_Rebin, 1,1,"B");
TH1F* histPt_Acceptance_rap_F_mid1_to_mid2_Eta  = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin->Clone("histPt_Acceptance_rap_F_mid1_to_mid2_Eta");
histPt_Acceptance_rap_F_mid1_to_mid2_Eta->Divide(histPt_ALL_GG_rap_F_mid1_to_mid2_Eta_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin, 1,1,"B");

histPt_Acceptance_rap_F_low1_to_low2_Pi0->Sumw2();
histPt_Acceptance_rap_F_high1_to_high2_Pi0->Sumw2();
histPt_Acceptance_rap_F_mid1_to_mid2_Pi0->Sumw2();
histPt_Acceptance_rap_F_low1_to_low2_Eta->Sumw2();
histPt_Acceptance_rap_F_high1_to_high2_Eta->Sumw2();
histPt_Acceptance_rap_F_mid1_to_mid2_Eta->Sumw2();

// Labelling //
SetStyleHistoTH1ForGraphs(histPt_Acceptance_rap_F_low1_to_low2_Pi0, "pT (GeV)", "Acceptance*BR", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_Acceptance_rap_F_low1_to_low2_Pi0->GetYaxis()->SetRangeUser(0.1,5.0);

// CHECKER LABELING //
//DrawGammaSetMarker(histPt_Acceptance_rap_F_mid1_to_mid2_Pi0,25,1.0, kRed , kRed);
//histPt_Acceptance_rap_F_mid1_to_mid2_Pi0->Draw("E1");
//DrawGammaSetMarker(histPt_Acceptance_rap_F_mid1_to_mid2_Eta,25,1.0, kGreen+3 , kGreen+3);
//histPt_Acceptance_rap_F_mid1_to_mid2_Eta->Draw("SAME,E1"); 
//DrawGammaSetMarker(histPt_Acceptance_rap_F_low1_to_low2_Pi0,26,1.0, kRed , kRed);
histPt_Acceptance_rap_F_low1_to_low2_Pi0->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_Acceptance_rap_F_low1_to_low2_Eta,26,1.0, kGreen+3 , kGreen+3);
histPt_Acceptance_rap_F_low1_to_low2_Eta->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_Acceptance_rap_F_high1_to_high2_Pi0,20,1.0, kRed+3 , kRed+3);
histPt_Acceptance_rap_F_high1_to_high2_Pi0->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_Acceptance_rap_F_high1_to_high2_Eta,20,1.0, kGreen+3 , kGreen+3);
histPt_Acceptance_rap_F_high1_to_high2_Eta->Draw("SAME,P"); 



//Combined rapidity range in Forward region:
TH1F* histPt_Acceptance_rap_F_low_plus_high_Eta  = (TH1F*) histPt_Acceptance_rap_F_low1_to_low2_Eta->Clone("histPt_Acceptance_rap_F_low_plus_high_Eta");
histPt_Acceptance_rap_F_low_plus_high_Eta->Add(histPt_Acceptance_rap_F_high1_to_high2_Eta);
histPt_Acceptance_rap_F_low_plus_high_Eta->Scale(.5);

TH1F* histPt_Acceptance_rap_F_low_plus_high_Pi0  = (TH1F*) histPt_Acceptance_rap_F_low1_to_low2_Pi0->Clone("histPt_Acceptance_rap_F_low_plus_high_Pi0");
histPt_Acceptance_rap_F_low_plus_high_Pi0->Add(histPt_Acceptance_rap_F_high1_to_high2_Pi0);
histPt_Acceptance_rap_F_low_plus_high_Pi0->Scale(.5);


// Draw //
//DrawGammaSetMarker(histPt_Acceptance_rap_F_low_plus_high_Pi0,25,1.0, kRed , kRed);
//histPt_Acceptance_rap_F_low_plus_high_Pi0->Draw("SAME,E1");
//DrawGammaSetMarker(histPt_Acceptance_rap_F_low_plus_high_Eta,25,1.0, kBlack , kBlack);
//histPt_Acceptance_rap_F_low_plus_high_Eta->Draw("SAME,E1");

auto l_mesonAcc_F = new TLegend(0.6, 0.65, 0.8, 0.8);
l_mesonAcc_F->SetHeader("");
l_mesonAcc_F->SetBorderSize(0);
l_mesonAcc_F->SetFillStyle(0);
l_mesonAcc_F->SetTextSize(TextSize);
l_mesonAcc_F->AddEntry(histPt_Acceptance_rap_F_low1_to_low2_Pi0,Form("#pi^{0} : %.2f < y < %.2f",etaF_low1,etaF_low2));
l_mesonAcc_F->AddEntry(histPt_Acceptance_rap_F_high1_to_high2_Pi0,Form("#pi^{0} : %.2f < y < %.2f",etaF_high1,etaF_high2));
l_mesonAcc_F->AddEntry(histPt_Acceptance_rap_F_low1_to_low2_Eta,Form("#eta : %.2f < y < %.2f",etaF_low1,etaF_low2));
l_mesonAcc_F->AddEntry(histPt_Acceptance_rap_F_high1_to_high2_Eta,Form("#eta : %.2f < y < %.2f",etaF_high1,etaF_high2));
//l_mesonAcc_F->AddEntry(histPt_Acceptance_rap_F_mid1_to_mid2_Pi0,Form("#pi^{0} : %.2f < y < %.2f",etaF_mid1,etaF_mid2));
//l_mesonAcc_F->AddEntry(histPt_Acceptance_rap_F_mid1_to_mid2_Eta,Form("#eta : %.2f < y < %.2f",etaF_mid1,etaF_mid2));

//l_mesonAcc_F->AddEntry(histPt_Acceptance_rap_F_low_plus_high_Pi0,Form("#pi^{0} : %.2f < |y| < %.2f",etaF_high1,etaF_high2));
//l_mesonAcc_F->AddEntry(histPt_Acceptance_rap_F_low_plus_high_Eta,Form("#eta : %.2f < |y| < %.2f",etaF_high1,etaF_high2));
l_mesonAcc_F->Draw("SAME");

TLatex *lt_mesonAcc_F_a = new TLatex(0.45,0.8,"Meson Acceptance at forward region");
SetStyleTLatex( lt_mesonAcc_F_a, 0.03,4);
lt_mesonAcc_F_a->Draw("SAME");

SetStyleTLatex( lt_mesonAcc_F_b, 0.03,4);
lt_mesonAcc_F_b->Draw("SAME");





/////////////////////////     Barrel    //////////////////////////////
c_mesonAcc->cd(2)->SetLogy();  
c_mesonAcc->cd(2);

TAxis *xaxis_B_Pi0 = histRapPt_ALL_Pi0_B->GetXaxis();
Int_t bin_etaB_low1 = xaxis_B_Pi0->FindBin(etaB_low1 + 0.0001);
Int_t bin_etaB_low2 = xaxis_B_Pi0->FindBin(etaB_low2 - 0.0001);
Int_t bin_etaB_high1 = xaxis_B_Pi0->FindBin(etaB_high1 + 0.0001);
Int_t bin_etaB_high2 = xaxis_B_Pi0->FindBin(etaB_high2 - 0.0001);
Int_t bin_etaB_mid1 = xaxis_B_Pi0->FindBin(etaB_mid1 + 0.0001);
Int_t bin_etaB_mid2 = xaxis_B_Pi0->FindBin(etaB_mid2 - 0.0001);

//Projections
TH1 * histPt_ALL_rap_B_low1_to_low2_Pi0 = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_rap_B_low1_to_low2_Pi0",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Pi0 = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_rap_B_high1_to_high2_Pi0",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Pi0 = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_rap_B_mid1_to_mid2_Pi0",bin_etaB_mid1,bin_etaB_mid2); 

TH1 * histPt_ALL_GG_rap_B_low1_to_low2_Pi0 = histRapPt_ALL_Pi0_B_GG->ProjectionY("histPt_ALL_GG_rap_B_low1_to_low2_Pi0",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_ALL_GG_rap_B_high1_to_high2_Pi0 = histRapPt_ALL_Pi0_B_GG->ProjectionY("histPt_ALL_GG_rap_B_high1_to_high2_Pi0",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_ALL_GG_rap_B_mid1_to_mid2_Pi0 = histRapPt_ALL_Pi0_B_GG->ProjectionY("histPt_ALL_GG_rap_B_mid1_to_mid2_Pi0",bin_etaB_mid1,bin_etaB_mid2); 

TH1 * histPt_ALL_rap_B_low1_to_low2_Eta = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_rap_B_low1_to_low2_Eta",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Eta = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_rap_B_high1_to_high2_Eta",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Eta = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_rap_B_mid1_to_mid2_Eta",bin_etaB_mid1,bin_etaB_mid2); 

TH1 * histPt_ALL_GG_rap_B_low1_to_low2_Eta = histRapPt_ALL_Eta_B_GG->ProjectionY("histPt_ALL_GG_rap_B_low1_to_low2_Eta",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_ALL_GG_rap_B_high1_to_high2_Eta = histRapPt_ALL_Eta_B_GG->ProjectionY("histPt_ALL_GG_rap_B_high1_to_high2_Eta",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_ALL_GG_rap_B_mid1_to_mid2_Eta = histRapPt_ALL_Eta_B_GG->ProjectionY("histPt_ALL_GG_rap_B_mid1_to_mid2_Eta",bin_etaB_mid1,bin_etaB_mid2); 

histPt_ALL_rap_B_low1_to_low2_Pi0->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Pi0->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Pi0->Sumw2();
histPt_ALL_GG_rap_B_low1_to_low2_Pi0->Sumw2();
histPt_ALL_GG_rap_B_high1_to_high2_Pi0->Sumw2();
histPt_ALL_GG_rap_B_mid1_to_mid2_Pi0->Sumw2();
histPt_ALL_rap_B_low1_to_low2_Eta->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Eta->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Eta->Sumw2();
histPt_ALL_GG_rap_B_low1_to_low2_Eta->Sumw2();
histPt_ALL_GG_rap_B_high1_to_high2_Eta->Sumw2();
histPt_ALL_GG_rap_B_mid1_to_mid2_Eta->Sumw2();


// Rebinning //
TH1F* histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_GG_rap_B_low1_to_low2_Pi0_Rebin     = (TH1F*) histPt_ALL_GG_rap_B_low1_to_low2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_GG_rap_B_low1_to_low2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_GG_rap_B_high1_to_high2_Pi0_Rebin        = (TH1F*) histPt_ALL_GG_rap_B_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_GG_rap_B_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_GG_rap_B_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_ALL_GG_rap_B_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_rap_B_low1_to_low2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Eta_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_GG_rap_B_low1_to_low2_Eta_Rebin     = (TH1F*) histPt_ALL_GG_rap_B_low1_to_low2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_GG_rap_B_low1_to_low2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_GG_rap_B_high1_to_high2_Eta_Rebin        = (TH1F*) histPt_ALL_GG_rap_B_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_GG_rap_B_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_GG_rap_B_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_ALL_GG_rap_B_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin->Sumw2();
histPt_ALL_GG_rap_B_low1_to_low2_Pi0_Rebin->Sumw2();
histPt_ALL_GG_rap_B_high1_to_high2_Pi0_Rebin->Sumw2();
histPt_ALL_GG_rap_B_mid1_to_mid2_Pi0_Rebin->Sumw2();
histPt_ALL_rap_B_low1_to_low2_Eta_Rebin->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin->Sumw2();
histPt_ALL_GG_rap_B_low1_to_low2_Eta_Rebin->Sumw2();
histPt_ALL_GG_rap_B_high1_to_high2_Eta_Rebin->Sumw2();
histPt_ALL_GG_rap_B_mid1_to_mid2_Eta_Rebin->Sumw2();


//  Scaling //

DivideTH1ByBinWidth(histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin);

DivideTH1ByBinWidth(histPt_ALL_GG_rap_B_low1_to_low2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_GG_rap_B_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_GG_rap_B_mid1_to_mid2_Pi0_Rebin);

DivideTH1ByBinWidth(histPt_ALL_rap_B_low1_to_low2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin);

DivideTH1ByBinWidth(histPt_ALL_GG_rap_B_low1_to_low2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_GG_rap_B_high1_to_high2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_GG_rap_B_mid1_to_mid2_Eta_Rebin);


//  Acceptance //
TH1F* histPt_Acceptance_rap_B_low1_to_low2_Pi0  = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin->Clone("histPt_Acceptance_rap_B_low1_to_low2_Pi0");
histPt_Acceptance_rap_B_low1_to_low2_Pi0->Divide(histPt_ALL_GG_rap_B_low1_to_low2_Pi0_Rebin, histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin, 1,1,"B");
TH1F* histPt_Acceptance_rap_B_high1_to_high2_Pi0  = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin->Clone("histPt_Acceptance_rap_B_high1_to_high2_Pi0");
histPt_Acceptance_rap_B_high1_to_high2_Pi0->Divide(histPt_ALL_GG_rap_B_high1_to_high2_Pi0_Rebin, histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin, 1,1,"B");
TH1F* histPt_Acceptance_rap_B_mid1_to_mid2_Pi0  = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin->Clone("histPt_Acceptance_rap_B_mid1_to_mid2_Pi0");
histPt_Acceptance_rap_B_mid1_to_mid2_Pi0->Divide(histPt_ALL_GG_rap_B_mid1_to_mid2_Pi0_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin, 1,1,"B");

TH1F* histPt_Acceptance_rap_B_low1_to_low2_Eta  = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Eta_Rebin->Clone("histPt_Acceptance_rap_B_low1_to_low2_Eta");
histPt_Acceptance_rap_B_low1_to_low2_Eta->Divide(histPt_ALL_GG_rap_B_low1_to_low2_Eta_Rebin, histPt_ALL_rap_B_low1_to_low2_Eta_Rebin, 1,1,"B");
TH1F* histPt_Acceptance_rap_B_high1_to_high2_Eta  = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Eta_Rebin->Clone("histPt_Acceptance_rap_B_high1_to_high2_Eta");
histPt_Acceptance_rap_B_high1_to_high2_Eta->Divide(histPt_ALL_GG_rap_B_high1_to_high2_Eta_Rebin, histPt_ALL_rap_B_high1_to_high2_Eta_Rebin, 1,1,"B");
TH1F* histPt_Acceptance_rap_B_mid1_to_mid2_Eta  = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin->Clone("histPt_Acceptance_rap_B_mid1_to_mid2_Eta");
histPt_Acceptance_rap_B_mid1_to_mid2_Eta->Divide(histPt_ALL_GG_rap_B_mid1_to_mid2_Eta_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin, 1,1,"B");

histPt_Acceptance_rap_B_low1_to_low2_Pi0->Sumw2();
histPt_Acceptance_rap_B_high1_to_high2_Pi0->Sumw2();
histPt_Acceptance_rap_B_mid1_to_mid2_Pi0->Sumw2();
histPt_Acceptance_rap_B_low1_to_low2_Eta->Sumw2();
histPt_Acceptance_rap_B_high1_to_high2_Eta->Sumw2();
histPt_Acceptance_rap_B_mid1_to_mid2_Eta->Sumw2();

// Labelling //
SetStyleHistoTH1ForGraphs(histPt_Acceptance_rap_B_low1_to_low2_Pi0, "pT (GeV)", "Acceptance*BR", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_Acceptance_rap_B_low1_to_low2_Pi0->GetYaxis()->SetRangeUser(0.1,5.0);

//  CHECKER Labeling //
//DrawGammaSetMarker(histPt_Acceptance_rap_B_mid1_to_mid2_Pi0,25,1.0, kRed , kRed);
//histPt_Acceptance_rap_B_mid1_to_mid2_Pi0->Draw("E1");
//DrawGammaSetMarker(histPt_Acceptance_rap_B_mid1_to_mid2_Eta,25,1.0, kGreen+3 , kGreen+3);
//histPt_Acceptance_rap_B_mid1_to_mid2_Eta->Draw("SAME,E1");
DrawGammaSetMarker(histPt_Acceptance_rap_B_low1_to_low2_Pi0,26,1.0, kRed, kRed);
histPt_Acceptance_rap_B_low1_to_low2_Pi0->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_Acceptance_rap_B_low1_to_low2_Eta,26,1.0, kGreen+3 , kGreen+3);
histPt_Acceptance_rap_B_low1_to_low2_Eta->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_Acceptance_rap_B_high1_to_high2_Pi0,20,1.0, kRed+3 , kRed+3);
histPt_Acceptance_rap_B_high1_to_high2_Pi0->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_Acceptance_rap_B_high1_to_high2_Eta,20,1.0, kGreen+3 , kGreen+3);
histPt_Acceptance_rap_B_high1_to_high2_Eta->Draw("SAME,E1"); 

//Combined rapidity range in Barrel region:
TH1F* histPt_Acceptance_rap_B_low_plus_high_Eta  = (TH1F*) histPt_Acceptance_rap_B_low1_to_low2_Eta->Clone("histPt_Acceptance_rap_B_low_plus_high_Eta");
histPt_Acceptance_rap_B_low_plus_high_Eta->Add(histPt_Acceptance_rap_B_high1_to_high2_Eta);
histPt_Acceptance_rap_B_low_plus_high_Eta->Scale(.5);

TH1F* histPt_Acceptance_rap_B_low_plus_high_Pi0  = (TH1F*) histPt_Acceptance_rap_B_low1_to_low2_Pi0->Clone("histPt_Acceptance_rap_B_low_plus_high_Pi0");
histPt_Acceptance_rap_B_low_plus_high_Pi0->Add(histPt_Acceptance_rap_B_high1_to_high2_Pi0);
histPt_Acceptance_rap_B_low_plus_high_Pi0->Scale(.5);


//  Draw //
//DrawGammaSetMarker(histPt_Acceptance_rap_B_low_plus_high_Pi0,25,1.0, kRed , kRed);
//histPt_Acceptance_rap_B_low_plus_high_Pi0->Draw("SAME,E1");
//DrawGammaSetMarker(histPt_Acceptance_rap_B_low_plus_high_Eta,25,1.0, kBlack , kBlack);
//histPt_Acceptance_rap_B_low_plus_high_Eta->Draw("SAME,E1");

auto l_mesonAcc_B = new TLegend(0.6, 0.65, 0.8, 0.8);
l_mesonAcc_B->SetHeader("");
l_mesonAcc_B->SetBorderSize(0);
l_mesonAcc_B->SetFillStyle(0);
l_mesonAcc_B->SetTextSize(TextSize);
//l_mesonAcc_B->AddEntry(histPt_Acceptance_rap_B_mid1_to_mid2_Pi0,Form("#pi^{0} : %.2f < y < %.2f",etaB_mid1,etaB_mid2));
//l_mesonAcc_B->AddEntry(histPt_Acceptance_rap_B_mid1_to_mid2_Eta,Form("#eta : %.2f < y < %.2f",etaB_mid1,etaB_mid2));
l_mesonAcc_B->AddEntry(histPt_Acceptance_rap_B_low1_to_low2_Pi0,Form("#pi^{0} : %.2f < y < %.2f",etaB_low1,etaB_low2));
l_mesonAcc_B->AddEntry(histPt_Acceptance_rap_B_high1_to_high2_Pi0,Form("#pi^{0} : %.2f < y < %.2f",etaB_high1,etaB_high2));
l_mesonAcc_B->AddEntry(histPt_Acceptance_rap_B_low1_to_low2_Eta,Form("#eta : %.2f < y < %.2f",etaB_low1,etaB_low2));
l_mesonAcc_B->AddEntry(histPt_Acceptance_rap_B_high1_to_high2_Eta,Form("#eta : %.2f < y < %.2f",etaB_high1,etaB_high2));

//l_mesonAcc_B->AddEntry(histPt_Acceptance_rap_B_low_plus_high_Pi0,Form("#pi^{0} : %.2f < |y| < %.2f",etaB_high1,etaB_high2));
//l_mesonAcc_B->AddEntry(histPt_Acceptance_rap_B_low_plus_high_Eta,Form("#eta : %.2f < |y| < %.2f",etaB_high1,etaB_high2));
l_mesonAcc_B->Draw("SAME");

TLatex *lt_mesonAcc_B_a = new TLatex(0.45,0.8,"Meson Acceptance at barrel region");
SetStyleTLatex( lt_mesonAcc_B_a, 0.03,4);
lt_mesonAcc_B_a->Draw("SAME");

SetStyleTLatex( lt_mesonAcc_B_b, 0.03,4);
lt_mesonAcc_B_b->Draw("SAME");

c_mesonAcc->Update();
c_mesonAcc->SaveAs("./Acceptance_meson.png");
c_mesonAcc->Close();



/////////////////      Meson Acceptance Combined plot    ///////////
StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or

TCanvas* c_eff_combined = new TCanvas("c_eff_combined","c_eff_combined",0,0,700,700);
DrawGammaCanvasSettings( c_eff_combined, 0.1, 0.02, 0.02, 0.1);
c_eff_combined->SetLogy();  

                                                // ProjectionY("histPt_ALL_rap_B_low1_to_low2_Eta",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_ALL_Pi0_F    = histRapPt_ALL_Pi0_F->ProjectionY("histPt_ALL_Pi0_F"); 
TH1 * histPt_ALL_Pi0_F_GG = histRapPt_ALL_Pi0_F_GG->ProjectionY("histPt_ALL_Pi0_F_GG"); 
TH1 * histPt_ALL_Eta_F    = histRapPt_ALL_Eta_F->ProjectionY("histPt_ALL_Eta_F"); 
TH1 * histPt_ALL_Eta_F_GG = histRapPt_ALL_Eta_F_GG->ProjectionY("histPt_ALL_Eta_F_GG");


TH1 * histPt_ALL_Pi0_B    = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_Pi0_B"); 
TH1 * histPt_ALL_Pi0_B_GG    = histRapPt_ALL_Pi0_B_GG->ProjectionY("histPt_ALL_Pi0_B_GG"); 
TH1 * histPt_ALL_Eta_B    = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_Eta_B"); 
TH1 * histPt_ALL_Eta_B_GG = histRapPt_ALL_Eta_B_GG->ProjectionY("histPt_ALL_Eta_B_GG");

TH1F* histPt_ALL_Pi0_B_Rebin     = (TH1F*) histPt_ALL_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_ALL_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Pi0_B_GG_Rebin     = (TH1F*) histPt_ALL_Pi0_B_GG->Rebin(nbinspt_proj_fine,"histPt_ALL_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_ALL_Pi0_B_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Pi0_B_GG_Rebin);

TH1F* histPt_ALL_Eta_B_Rebin     = (TH1F*) histPt_ALL_Eta_B->Rebin(nbinspt_proj_fine,"histPt_ALL_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Eta_B_GG_Rebin     = (TH1F*) histPt_ALL_Eta_B_GG->Rebin(nbinspt_proj_fine,"histPt_ALL_Eta_B_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_ALL_Eta_B_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Eta_B_GG_Rebin);


TH1F* histPt_ALL_Pi0_F_Rebin     = (TH1F*) histPt_ALL_Pi0_F->Rebin(nbinspt_proj_fine,"histPt_ALL_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Pi0_F_GG_Rebin     = (TH1F*) histPt_ALL_Pi0_F_GG->Rebin(nbinspt_proj_fine,"histPt_ALL_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_ALL_Pi0_F_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Pi0_F_GG_Rebin);

TH1F* histPt_ALL_Eta_F_Rebin     = (TH1F*) histPt_ALL_Eta_F->Rebin(nbinspt_proj_fine,"histPt_ALL_Eta_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_Eta_F_GG_Rebin  = (TH1F*) histPt_ALL_Eta_F_GG->Rebin(nbinspt_proj_fine,"histPt_ALL_Eta_F_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_ALL_Eta_F_Rebin);
DivideTH1ByBinWidth(histPt_ALL_Eta_F_GG_Rebin);



//RATIO
TH1F* histPt_Acceptance_Pi0_B  = (TH1F*) histPt_ALL_Pi0_B_Rebin->Clone("histPt_Acceptance_Pi0_B");
histPt_Acceptance_Pi0_B->Divide(histPt_ALL_Pi0_B_GG_Rebin, histPt_ALL_Pi0_B_Rebin, 1,1,"B");
SetStyleHistoTH1ForGraphs(histPt_Acceptance_Pi0_B, "p_{T} (GeV/c)", "acceptance*BR", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_Acceptance_Pi0_B->Draw("E1"); 
DrawGammaSetMarker(histPt_Acceptance_Pi0_B,24,1.0, kRed , kRed);

TH1F* histPt_Acceptance_Eta_B  = (TH1F*) histPt_ALL_Eta_B_Rebin->Clone("histPt_Acceptance_Eta_B");
histPt_Acceptance_Eta_B->Divide(histPt_ALL_Eta_B_GG_Rebin, histPt_ALL_Eta_B_Rebin, 1,1,"B");
histPt_Acceptance_Eta_B->Draw("E1, SAME"); 
DrawGammaSetMarker(histPt_Acceptance_Eta_B,24,1.0, kGreen+3 , kGreen+3);


TH1F* histPt_Acceptance_Pi0_F  = (TH1F*) histPt_ALL_Pi0_F_Rebin->Clone("histPt_Acceptance_Pi0_F");
histPt_Acceptance_Pi0_F->Divide(histPt_ALL_Pi0_F_GG_Rebin, histPt_ALL_Pi0_F_Rebin, 1,1,"B");
histPt_Acceptance_Pi0_F->Draw("E1, SAME"); 
DrawGammaSetMarker(histPt_Acceptance_Pi0_F,8,1.0, kRed , kRed);
TH1F* histPt_Acceptance_Eta_F  = (TH1F*) histPt_ALL_Eta_F_Rebin->Clone("histPt_Acceptance_Eta_F");
histPt_Acceptance_Eta_F->Divide(histPt_ALL_Eta_F_GG_Rebin, histPt_ALL_Eta_F_Rebin, 1,1,"B");

histPt_Acceptance_Eta_F->Draw("E1, SAME"); 
DrawGammaSetMarker(histPt_Acceptance_Eta_F,8,1.0, kGreen+3 , kGreen+3);

//LABELING
histPt_Acceptance_Pi0_B->GetYaxis()->SetRangeUser(0.1, 5);
histPt_Acceptance_Pi0_B->Draw("SAME E1");

auto l_mesonAcc = new TLegend(0.7, 0.65, 0.9, 0.8);
l_mesonAcc->SetHeader("");
l_mesonAcc->SetBorderSize(0);
l_mesonAcc->SetFillStyle(0);
l_mesonAcc->SetTextSize(TextSize);
l_mesonAcc->AddEntry(histPt_Acceptance_Pi0_B,"#pi^{0} :  0<|y|<1.3 ","p");
l_mesonAcc->AddEntry(histPt_Acceptance_Pi0_F,"#pi^{0} :  1.75<|y|<4.0 ","p");
l_mesonAcc->AddEntry(histPt_Acceptance_Eta_B,"#eta  :  0<|y|<1.3 ","p");
l_mesonAcc->AddEntry(histPt_Acceptance_Eta_F,"#eta  :  1.75<|y|<4.0 ","p");
l_mesonAcc->Draw("SAME");

TLatex *lt119a = new TLatex(0.7,0.8,"Meson Acceptance");
SetStyleTLatex( lt119a, 0.03,4);
//lt119a->Draw("SAME");

TLatex *lt119b = new TLatex(0.15,0.9,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt119b, 0.03,4);
lt119b->Draw("SAME");
histPt_Acceptance_Pi0_B->Draw("E1, SAME"); 

c_eff_combined->SaveAs("./Acceptance_meson_ALL.png");
c_eff_combined->Close();

}