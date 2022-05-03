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
void mesonEff(){
gSystem->Exec("mkdir mesonEff");

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

//TFile * fileRec = new TFile("./ana_withft3.root");
//TFile * fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3.root");
TFile * fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3_PbPb.root");
//TFile * fileRec = new TFile("./output/pp/pcut_0.1/ana_pTcut_withft3.root");

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


Double_t pt_bin_proj_fine[13]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_fine  = 12;

Double_t etaF_low1 = 1.75;
Double_t etaF_low2 = 3.0;
Double_t etaF_high1 = 3.0;
Double_t etaF_high2 = 4.0;
Double_t etaF_mid1 = 1.75;
Double_t etaF_mid2 = 4.0;


Double_t etaB_low1   = 0.0;
Double_t etaB_low2   = 0.8;
Double_t etaB_high1  = 0.0;
Double_t etaB_high2  = 1.3;
Double_t etaB_mid1   = 0.8;
Double_t etaB_mid2   = 1.3;





///////////////  Pi0 Effiiency at different Forward rapidity PLOT    ///////////////

TCanvas* c_eff_Pi0 = new TCanvas("c_eff_Pi0","c_eff_Pi0",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c_eff_Pi0, 0.3, 0.02, 0.02, 0.16);
c_eff_Pi0->Divide(2,1);
c_eff_Pi0->cd(1)->SetLogy();  
c_eff_Pi0->cd(1);


TH2D * histRapPt_ALL_Pi0_F = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH2D * histRapPt_REC_Pi0_F = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec");
histRapPt_ALL_Pi0_F->Sumw2();
histRapPt_REC_Pi0_F->Sumw2();

TAxis *xaxis_Pi0 = histRapPt_ALL_Pi0_F->GetXaxis();
Int_t bin_etaF_low1 = xaxis_Pi0->FindBin(etaF_low1 + 0.0001);
Int_t bin_etaF_low2 = xaxis_Pi0->FindBin(etaF_low2 - 0.0001);
Int_t bin_etaF_high1 = xaxis_Pi0->FindBin(etaF_high1 + 0.0001);
Int_t bin_etaF_high2 = xaxis_Pi0->FindBin(etaF_high2 - 0.0001);
Int_t bin_etaF_mid1 = xaxis_Pi0->FindBin(etaF_mid1 + 0.0001);
Int_t bin_etaF_mid2 = xaxis_Pi0->FindBin(etaF_mid2 - 0.0001);

cout<<  "Forward"<< endl<< bin_etaF_low1<< endl<< bin_etaF_low2<< endl<< bin_etaF_mid1<< endl<< bin_etaF_mid2<< endl<<bin_etaF_high1<< endl<< bin_etaF_high2<< endl<< '\n';


/*
TH1 * histPt_ALL_rap_F_low1_to_low2_Pi0 = histRapPt_ALL_Pi0_F->ProjectionY("histPt_MC_rap_F_low1_to_low2",bin_etaF_low1,bin_etaF_high1); 
TH1 * histPt_ALL_rap_F_high1_to_high2_Pi0 = histRapPt_ALL_Pi0_F->ProjectionY("histPt_MC_rap_F_high1_to_high2",bin_etaF_low2,bin_etaF_high2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Pi0 = histRapPt_ALL_Pi0_F->ProjectionY("histPt_MC_rap_F_mid1_to_mid2",bin_etaF_mid1,bin_etaF_mid2); 

TH1 * histPt_REC_rap_F_low1_to_low2_Pi0 = histRapPt_REC_Pi0_F->ProjectionY("histPt_REC_rap_F_low1_to_low2_Pi0",bin_etaF_low1,bin_etaF_high1); 
TH1 * histPt_REC_rap_F_high1_to_high2_Pi0 = histRapPt_REC_Pi0_F->ProjectionY("histPt_REC_rap_F_high1_to_high2_Pi0",bin_etaF_low2,bin_etaF_high2); 
TH1 * histPt_REC_rap_F_mid1_to_mid2_Pi0 = histRapPt_REC_Pi0_F->ProjectionY("histPt_REC_rap_F_mid1_to_mid2_Pi0",bin_etaF_mid1,bin_etaF_mid2); 

//REBINNING
TH1F* histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin        = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_F_low1_to_low2_Pi0_Rebin     = (TH1F*) histPt_REC_rap_F_low1_to_low2_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_low1_to_low2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_high1_to_high2_Pi0_Rebin        = (TH1F*) histPt_REC_rap_F_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);


//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_low1_to_low2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_mid1_to_mid2_Pi0_Rebin);

//RATIO
TH1F* histPt_RATIO_rap_F_low1_to_low2_Pi0  = (TH1F*) histPt_REC_rap_F_low1_to_low2_Pi0_Rebin->Clone("histPt_RATIO_rap_F_low1_to_low2_Pi0");
histPt_RATIO_rap_F_low1_to_low2_Pi0->Divide(histPt_REC_rap_F_low1_to_low2_Pi0_Rebin, histPt_ALL_rap_F_low1_to_low2_Pi0_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_F_high1_to_high2_Pi0  = (TH1F*) histPt_REC_rap_F_high1_to_high2_Pi0_Rebin->Clone("histPt_RATIO_rap_F_high1_to_high2_Pi0");
histPt_RATIO_rap_F_high1_to_high2_Pi0->Divide(histPt_REC_rap_F_high1_to_high2_Pi0_Rebin, histPt_ALL_rap_F_high1_to_high2_Pi0_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_F_mid1_to_mid2_Pi0  = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Pi0_Rebin->Clone("histPt_RATIO_rap_F_mid1_to_mid2_Pi0");
histPt_RATIO_rap_F_mid1_to_mid2_Pi0->Divide(histPt_REC_rap_F_mid1_to_mid2_Pi0_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Pi0_Rebin, 1,1,"B");


//histPt_RATIO_rap_F_low1_to_low2_Pi0->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap_F_low1_to_low2_Pi0->Draw("P"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_low1_to_low2_Pi0,8,0.9, kBlue , kBlue);
histPt_RATIO_rap_F_high1_to_high2_Pi0->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_high1_to_high2_Pi0,8,0.9, kRed+2 , kRed+2);
histPt_RATIO_rap_F_mid1_to_mid2_Pi0->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_mid1_to_mid2_Pi0,8,0.9, kGreen+4 , kGreen+4);


//CHECKER
TH1D * hPtGGPi0F = (TH1D*) fileRec->Get("hPtGGPi0F");
TH1D * hPtGGPi0F_rec = (TH1D*) fileRec->Get("hPtGGPi0F_rec");
hPtGGPi0F->Rebin(20);
hPtGGPi0F_rec->Rebin(20);
TH1F* histPt_RATIO_CheckerF_Pi0  = (TH1F*) hPtGGPi0F_rec->Clone("histPt_RATIO_CheckerF_Pi0");
histPt_RATIO_CheckerF_Pi0->Divide(hPtGGPi0F_rec, hPtGGPi0F, 1,1,"B");
DrawGammaSetMarker(histPt_RATIO_CheckerF_Pi0,8,0.5, kCyan , kCyan);
histPt_RATIO_CheckerF_Pi0->Draw("SAME");


//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_F_low1_to_low2_Pi0, "pT (GeV)", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap_F_low1_to_low2_Pi0->GetXaxis()->SetRangeUser(0.0,7.0);
*/

//WITH MOMENTUM SMEARING

TH2D * histRapPt_ALL_Pi0_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_SmearedP");
TH2D * histRapPt_REC_Pi0_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec_SmearedP");
histRapPt_ALL_Pi0_F_SmearedP->Sumw2();
histRapPt_REC_Pi0_F_SmearedP->Sumw2();

TH1 * histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP = histRapPt_ALL_Pi0_F_SmearedP->ProjectionY("histPt_MC_rap_F_low1_to_low2",bin_etaF_low1,bin_etaF_low2); 
TH1 * histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP = histRapPt_ALL_Pi0_F_SmearedP->ProjectionY("histPt_MC_rap_F_high1_to_high2",bin_etaF_high1,bin_etaF_high2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP = histRapPt_ALL_Pi0_F_SmearedP->ProjectionY("histPt_MC_rap_F_mid1_to_mid2",bin_etaF_mid1,bin_etaF_mid2); 

TH1 * histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP = histRapPt_REC_Pi0_F_SmearedP->ProjectionY("histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP",bin_etaF_low1,bin_etaF_low2); 
TH1 * histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP = histRapPt_REC_Pi0_F_SmearedP->ProjectionY("histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP",bin_etaF_high1,bin_etaF_high2); 
TH1 * histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP = histRapPt_REC_Pi0_F_SmearedP->ProjectionY("histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP",bin_etaF_mid1,bin_etaF_mid2); 

histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP->Sumw2();

//REBINNING
TH1F* histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin->Sumw2();

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap_F_low1_to_low2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap_F_low1_to_low2_Pi0_SmearedP");
histPt_RATIO_rap_F_low1_to_low2_Pi0_SmearedP->Divide(histPt_REC_rap_F_low1_to_low2_Pi0_SmearedP_Rebin, histPt_ALL_rap_F_low1_to_low2_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_F_high1_to_high2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap_F_high1_to_high2_Pi0_SmearedP");
histPt_RATIO_rap_F_high1_to_high2_Pi0_SmearedP->Divide(histPt_REC_rap_F_high1_to_high2_Pi0_SmearedP_Rebin, histPt_ALL_rap_F_high1_to_high2_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP");
histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP->Divide(histPt_REC_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Pi0_SmearedP_Rebin, 1,1,"B");

histPt_RATIO_rap_F_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_RATIO_rap_F_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP->Sumw2();

//histPt_RATIO_rap_F_low1_to_low2_Pi0->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap_F_low1_to_low2_Pi0_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_low1_to_low2_Pi0_SmearedP,25,1.0, kBlue , kBlue);
histPt_RATIO_rap_F_high1_to_high2_Pi0_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_high1_to_high2_Pi0_SmearedP,25,1.0, kRed+2 , kRed+2);
histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP,25,1.0, kGreen+4 , kGreen+4);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_F_low1_to_low2_Pi0_SmearedP, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

auto l_eff_Pi0_F = new TLegend(0.55, 0.15, 0.7, 0.35);
l_eff_Pi0_F->SetHeader("Forward","C");
l_eff_Pi0_F->SetBorderSize(0);
l_eff_Pi0_F->SetFillStyle(0);
l_eff_Pi0_F->SetTextSize(TextSize);
l_eff_Pi0_F->AddEntry(histPt_RATIO_rap_F_low1_to_low2_Pi0_SmearedP,Form("%.2f < y < %.2f",etaF_low1,etaF_low2));
l_eff_Pi0_F->AddEntry(histPt_RATIO_rap_F_high1_to_high2_Pi0_SmearedP,Form("%.2f < y < %.2f",etaF_high1,etaF_high2));
l_eff_Pi0_F->AddEntry(histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP,Form("%.2f < y < %.2f",etaF_mid1,etaF_mid2));
//l_eff_Pi0_F->AddEntry(histPt_RATIO_rap_F_low1_to_low2_Pi0, Form("%.2f < y < %.2f",etaF_low1,etaF_low2));
//l_eff_Pi0_F->AddEntry(histPt_RATIO_rap_F_high1_to_high2_Pi0,Form("%.2f < y < %.2f",etaF_high1,etaF_high2));
//l_eff_Pi0_F->AddEntry(histPt_RATIO_rap_F_mid1_to_mid2_Pi0, Form("%.2f < y < %.2f",etaF_mid1,etaF_mid2));
l_eff_Pi0_F->Draw("SAME");

TLatex *lta_eff_Pi0_F = new TLatex(0.2,0.8,"#splitline{Pi0 Effiiency at different rapidity}{with momentum smearing} ");
SetStyleTLatex( lta_eff_Pi0_F, 0.03,4);
lta_eff_Pi0_F->Draw("SAME");

TLatex *ltb_eff_Pi0_F = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{PbPb, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( ltb_eff_Pi0_F, 0.03,4);
ltb_eff_Pi0_F->Draw("SAME");

//TLatex *ltc_eff_Pi0_F = new TLatex(.15,.04,"Smeared momentum are represented by openbox");
//SetStyleTLatex( ltc_eff_Pi0_F, 0.02,4);
//ltc_eff_Pi0_F->Draw("SAME");








///////////////  Pi0 Effiiency at different Barrel rapidity PLOT    ///////////////

c_eff_Pi0->cd(2);
c_eff_Pi0->cd(2)->SetLogy();  

TH2D * histRapPt_ALL_Pi0_B = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH2D * histRapPt_REC_Pi0 = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec");

histRapPt_ALL_Pi0_B->Sumw2();
histRapPt_REC_Pi0->Sumw2();

TAxis *XAXIS_Pi0 = histRapPt_ALL_Pi0_B->GetXaxis();
Int_t bin_etaB_low1     = XAXIS_Pi0->FindBin(etaB_low1 + 0.0001);
Int_t bin_etaB_low2     = XAXIS_Pi0->FindBin(etaB_low2 - 0.0001);
Int_t bin_etaB_high1    = XAXIS_Pi0->FindBin(etaB_high1+ 0.0001);
Int_t bin_etaB_high2    = XAXIS_Pi0->FindBin(etaB_high2-0.0001);
Int_t bin_etaB_mid1    = XAXIS_Pi0->FindBin(etaB_mid1+ 0.0001);
Int_t bin_etaB_mid2    = XAXIS_Pi0->FindBin(etaB_mid2-0.0001);

cout<< "Barrel:"<< endl<< bin_etaB_low1<< endl<< bin_etaB_low2<< endl<< bin_etaB_mid1<< endl<< bin_etaB_mid2<< endl<<bin_etaB_high1<< endl<< bin_etaB_high2<< endl<< '\n';

/*
TH1 * histPt_ALL_rap_B_low1_to_low2_Pi0 = histRapPt_ALL_Pi0_B->ProjectionY("histPt_MC_rap_B_low1_to_low2",bin_etaB_low1,bin_etaB_high1); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Pi0 = histRapPt_ALL_Pi0_B->ProjectionY("histPt_MC_rap_B_high1_to_high2",bin_etaB_low2,bin_etaB_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Pi0 = histRapPt_ALL_Pi0_B->ProjectionY("histPt_MC_rap_B_mid1_to_mid2",bin_etaB_mid1,bin_etaB_mid2); 

TH1 * histPt_REC_rap_B_low1_to_low2_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap_B_low1_to_low2_Pi0",bin_etaB_low1,bin_etaB_high1); 
TH1 * histPt_REC_rap_B_high1_to_high2_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap_B_high1_to_high2_Pi0",bin_etaB_low2,bin_etaB_high2); 
TH1 * histPt_REC_rap_B_mid1_to_mid2_Pi0 = histRapPt_REC_Pi0->ProjectionY("histPt_REC_rap_B_mid1_to_mid2_Pi0",bin_etaB_mid1,bin_etaB_mid2); 

//REBINNING
TH1F* histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_B_low1_to_low2_Pi0_Rebin     = (TH1F*) histPt_REC_rap_B_low1_to_low2_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_low1_to_low2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_high1_to_high2_Pi0_Rebin        = (TH1F*) histPt_REC_rap_B_high1_to_high2_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_high1_to_high2_Pi0_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_mid1_to_mid2_Pi0_Rebin     = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Pi0->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_mid1_to_mid2_Pi0_Rebin",&pt_bin_proj_fine[0]);


//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_low1_to_low2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_high1_to_high2_Pi0_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_mid1_to_mid2_Pi0_Rebin);

//RATIO
TH1F* histPt_RATIO_rap_B_low1_to_low2_Pi0  = (TH1F*) histPt_REC_rap_B_low1_to_low2_Pi0_Rebin->Clone("histPt_RATIO_rap_B_low1_to_low2_Pi0");
histPt_RATIO_rap_B_low1_to_low2_Pi0->Divide(histPt_REC_rap_B_low1_to_low2_Pi0_Rebin, histPt_ALL_rap_B_low1_to_low2_Pi0_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_B_high1_to_high2_Pi0  = (TH1F*) histPt_REC_rap_B_high1_to_high2_Pi0_Rebin->Clone("histPt_RATIO_rap_B_high1_to_high2_Pi0");
histPt_RATIO_rap_B_high1_to_high2_Pi0->Divide(histPt_REC_rap_B_high1_to_high2_Pi0_Rebin, histPt_ALL_rap_B_high1_to_high2_Pi0_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_B_mid1_to_mid2_Pi0  = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Pi0_Rebin->Clone("histPt_RATIO_rap_B_mid1_to_mid2_Pi0");
histPt_RATIO_rap_B_mid1_to_mid2_Pi0->Divide(histPt_REC_rap_B_mid1_to_mid2_Pi0_Rebin, histPt_ALL_rap_B_mid1_to_mid2_Pi0_Rebin, 1,1,"B");


//histPt_RATIO_rap_B_low1_to_low2_Pi0->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap_B_low1_to_low2_Pi0->Draw("P"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_low1_to_low2_Pi0,8,0.9, kBlue , kBlue);
histPt_RATIO_rap_B_high1_to_high2_Pi0->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_high1_to_high2_Pi0,8,0.9, kRed+2 , kRed+2);
histPt_RATIO_rap_B_mid1_to_mid2_Pi0->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_mid1_to_mid2_Pi0,8,0.9, kGreen+4 , kGreen+4);


//CHECKER
TH1D * hPtGGPi0F = (TH1D*) fileRec->Get("hPtGGPi0F");
TH1D * hPtGGPi0F_rec = (TH1D*) fileRec->Get("hPtGGPi0F_rec");
hPtGGPi0F->Rebin(20);
hPtGGPi0F_rec->Rebin(20);
TH1F* histPt_RATIO_CheckerF_Pi0  = (TH1F*) hPtGGPi0F_rec->Clone("histPt_RATIO_CheckerF_Pi0");
histPt_RATIO_CheckerF_Pi0->Divide(hPtGGPi0F_rec, hPtGGPi0F, 1,1,"B");
DrawGammaSetMarker(histPt_RATIO_CheckerF_Pi0,8,0.5, kCyan , kCyan);
histPt_RATIO_CheckerF_Pi0->Draw("SAME");


//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_B_low1_to_low2_Pi0, "pT (GeV)", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap_B_low1_to_low2_Pi0->GetXaxis()->SetRangeUser(0.0,7.0);
//histPt_RATIO_rap_B_low1_to_low2_Pi0->GetXaxis()->SetRangeUser(10^-5,10^-2);

*/

//WITH MOMENTUM SMEARING

TH2D * histRapPt_ALL_Pi0_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_SmearedP");
TH2D * histRapPt_REC_Pi0_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec_SmearedP");

histRapPt_ALL_Pi0_B_SmearedP->Sumw2();
histRapPt_REC_Pi0_SmearedP->Sumw2();

TH1 * histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_MC_rap_B_low1_to_low2",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_MC_rap_B_high1_to_high2",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_MC_rap_B_mid1_to_mid2",bin_etaB_mid1,bin_etaB_mid2); 

TH1 * histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP = histRapPt_REC_Pi0_SmearedP->ProjectionY("histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP",bin_etaB_mid1,bin_etaB_mid2); 

histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP->Sumw2();

//REBINNING
TH1F* histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin->Sumw2();

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap_B_low1_to_low2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_low1_to_low2_Pi0_SmearedP");
histPt_RATIO_rap_B_low1_to_low2_Pi0_SmearedP->Divide(histPt_REC_rap_B_low1_to_low2_Pi0_SmearedP_Rebin, histPt_ALL_rap_B_low1_to_low2_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_B_high1_to_high2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_high1_to_high2_Pi0_SmearedP");
histPt_RATIO_rap_B_high1_to_high2_Pi0_SmearedP->Divide(histPt_REC_rap_B_high1_to_high2_Pi0_SmearedP_Rebin, histPt_ALL_rap_B_high1_to_high2_Pi0_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP  = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP");
histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP->Divide(histPt_REC_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin, histPt_ALL_rap_B_mid1_to_mid2_Pi0_SmearedP_Rebin, 1,1,"B");

histPt_RATIO_rap_B_low1_to_low2_Pi0_SmearedP->Sumw2();
histPt_RATIO_rap_B_high1_to_high2_Pi0_SmearedP->Sumw2();
histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP->Sumw2();

//histPt_RATIO_rap_B_low1_to_low2_Pi0->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap_B_low1_to_low2_Pi0_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_low1_to_low2_Pi0_SmearedP,25,1.0, kBlue , kBlue);
histPt_RATIO_rap_B_high1_to_high2_Pi0_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_high1_to_high2_Pi0_SmearedP,25,1.0, kRed+2 , kRed+2);
histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP,25,1.0, kGreen+4 , kGreen+4);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_B_low1_to_low2_Pi0_SmearedP, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

auto l_eff_Pi0_B = new TLegend(0.55, 0.15, 0.7, 0.35);
l_eff_Pi0_B->SetHeader("Barrel","C");
l_eff_Pi0_B->SetBorderSize(0);
l_eff_Pi0_B->SetFillStyle(0);
l_eff_Pi0_B->SetTextSize(TextSize);
l_eff_Pi0_B->AddEntry(histPt_RATIO_rap_B_low1_to_low2_Pi0_SmearedP,Form("%.2f < y < %.2f",etaB_low1,etaB_low2));
l_eff_Pi0_B->AddEntry(histPt_RATIO_rap_B_high1_to_high2_Pi0_SmearedP,Form("%.2f < y < %.2f",etaB_high1,etaB_high2));
l_eff_Pi0_B->AddEntry(histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP,Form("%.2f < y < %.2f",etaB_mid1,etaB_mid2));
//l_eff_Pi0_B->AddEntry(histPt_RATIO_rap_B_low1_to_low2_Pi0,Form("%.2f < y < %.2f",etaB_low1,etaB_low2));
//l_eff_Pi0_B->AddEntry(histPt_RATIO_rap_B_high1_to_high2_Pi0,Form("%.2f < y < %.2f",etaB_high1,etaB_high2));
//l_eff_Pi0_B->AddEntry(histPt_RATIO_rap_B_mid1_to_mid2_Pi0,Form("%.2f < y < %.2f",etaB_low1,etaB_high2));
l_eff_Pi0_B->Draw("SAME");

TLatex *lta_eff_Pi0_B = new TLatex(0.2,0.8,"#splitline{Pi0 Effiiency at different rapidity}{with momentum smearing} ");
SetStyleTLatex( lta_eff_Pi0_B, 0.03,4);
lta_eff_Pi0_B->Draw("SAME");

TLatex *ltb_eff_Pi0_B = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{PbPb, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( ltb_eff_Pi0_B, 0.03,4);
ltb_eff_Pi0_B->Draw("SAME");

TLatex *ltc_eff_Pi0_B = new TLatex(.15,.04,"Smeared momentum are represented by openbox");
SetStyleTLatex( ltc_eff_Pi0_B, 0.02,4);
ltc_eff_Pi0_B->Draw("SAME");


c_eff_Pi0->Update();

c_eff_Pi0->SaveAs("mesonEff/hDiffRap_ratio_Pi0.png");

c_eff_Pi0->Close();














///////////////  Eta Effiiency at different Forward rapidity PLOT    ///////////////

TCanvas* c_eff_Eta = new TCanvas("c_eff_Eta","c_eff_Eta",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c_eff_Eta, 0.3, 0.02, 0.02, 0.16);
c_eff_Eta->Divide(2,1);
c_eff_Eta->cd(1)->SetLogy();  
c_eff_Eta->cd(1);


TH2D * histRapPt_ALL_Eta_F = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");
TH2D * histRapPt_REC_Eta_F = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec");
histRapPt_ALL_Eta_F->Sumw2();
histRapPt_REC_Eta_F->Sumw2();

/*
TH1 * histPt_ALL_rap_F_low1_to_low2_Eta = histRapPt_ALL_Eta_F->ProjectionY("histPt_MC_rap_F_low1_to_low2",bin_etaF_low1,bin_etaF_high1); 
TH1 * histPt_ALL_rap_F_high1_to_high2_Eta = histRapPt_ALL_Eta_F->ProjectionY("histPt_MC_rap_F_high1_to_high2",bin_etaF_low2,bin_etaF_high2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Eta = histRapPt_ALL_Eta_F->ProjectionY("histPt_MC_rap_F_mid1_to_mid2",bin_etaF_mid1,bin_etaF_mid2); 

TH1 * histPt_REC_rap_F_low1_to_low2_Eta = histRapPt_REC_Eta_F->ProjectionY("histPt_REC_rap_F_low1_to_low2_Eta",bin_etaF_low1,bin_etaF_high1); 
TH1 * histPt_REC_rap_F_high1_to_high2_Eta = histRapPt_REC_Eta_F->ProjectionY("histPt_REC_rap_F_high1_to_high2_Eta",bin_etaF_low2,bin_etaF_high2); 
TH1 * histPt_REC_rap_F_mid1_to_mid2_Eta = histRapPt_REC_Eta_F->ProjectionY("histPt_REC_rap_F_mid1_to_mid2_Eta",bin_etaF_mid1,bin_etaF_mid2); 

//REBINNING
TH1F* histPt_ALL_rap_F_low1_to_low2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_low1_to_low2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_high1_to_high2_Eta_Rebin        = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_F_low1_to_low2_Eta_Rebin     = (TH1F*) histPt_REC_rap_F_low1_to_low2_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_low1_to_low2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_high1_to_high2_Eta_Rebin        = (TH1F*) histPt_REC_rap_F_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);


//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_F_low1_to_low2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_high1_to_high2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_low1_to_low2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_high1_to_high2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_mid1_to_mid2_Eta_Rebin);

//RATIO
TH1F* histPt_RATIO_rap_F_low1_to_low2_Eta  = (TH1F*) histPt_REC_rap_F_low1_to_low2_Eta_Rebin->Clone("histPt_RATIO_rap_F_low1_to_low2_Eta");
histPt_RATIO_rap_F_low1_to_low2_Eta->Divide(histPt_REC_rap_F_low1_to_low2_Eta_Rebin, histPt_ALL_rap_F_low1_to_low2_Eta_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_F_high1_to_high2_Eta  = (TH1F*) histPt_REC_rap_F_high1_to_high2_Eta_Rebin->Clone("histPt_RATIO_rap_F_high1_to_high2_Eta");
histPt_RATIO_rap_F_high1_to_high2_Eta->Divide(histPt_REC_rap_F_high1_to_high2_Eta_Rebin, histPt_ALL_rap_F_high1_to_high2_Eta_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_F_mid1_to_mid2_Eta  = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Eta_Rebin->Clone("histPt_RATIO_rap_F_mid1_to_mid2_Eta");
histPt_RATIO_rap_F_mid1_to_mid2_Eta->Divide(histPt_REC_rap_F_mid1_to_mid2_Eta_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Eta_Rebin, 1,1,"B");


//histPt_RATIO_rap_F_low1_to_low2_Eta->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap_F_low1_to_low2_Eta->Draw("P"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_low1_to_low2_Eta,8,0.9, kBlue , kBlue);
histPt_RATIO_rap_F_high1_to_high2_Eta->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_high1_to_high2_Eta,8,0.9, kRed+2 , kRed+2);
histPt_RATIO_rap_F_mid1_to_mid2_Eta->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_mid1_to_mid2_Eta,8,0.9, kGreen+4 , kGreen+4);


//CHECKER
TH1D * hPtGGEtaF = (TH1D*) fileRec->Get("hPtGGEtaF");
TH1D * hPtGGEtaF_rec = (TH1D*) fileRec->Get("hPtGGEtaF_rec");
hPtGGEtaF->Rebin(20);
hPtGGEtaF_rec->Rebin(20);
TH1F* histPt_RATIO_CheckerF_Eta  = (TH1F*) hPtGGEtaF_rec->Clone("histPt_RATIO_CheckerF_Eta");
histPt_RATIO_CheckerF_Eta->Divide(hPtGGEtaF_rec, hPtGGEtaF, 1,1,"B");
DrawGammaSetMarker(histPt_RATIO_CheckerF_Eta,8,0.5, kCyan , kCyan);
histPt_RATIO_CheckerF_Eta->Draw("SAME");


//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_F_low1_to_low2_Eta, "pT (GeV)", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap_F_low1_to_low2_Eta->GetXaxis()->SetRangeUser(0.0,7.0);
*/

//WITH MOMENTUM SMEARING

TH2D * histRapPt_ALL_Eta_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_SmearedP");
TH2D * histRapPt_REC_Eta_F_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec_SmearedP");

histRapPt_ALL_Eta_F_SmearedP->Sumw2();
histRapPt_REC_Eta_F_SmearedP->Sumw2();

TH1 * histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP = histRapPt_ALL_Eta_F_SmearedP->ProjectionY("histPt_MC_rap_F_low1_to_low2",bin_etaF_low1,bin_etaF_low2); 
TH1 * histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP = histRapPt_ALL_Eta_F_SmearedP->ProjectionY("histPt_MC_rap_F_high1_to_high2",bin_etaF_high1,bin_etaF_high2); 
TH1 * histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP = histRapPt_ALL_Eta_F_SmearedP->ProjectionY("histPt_MC_rap_F_mid1_to_mid2",bin_etaF_mid1,bin_etaF_mid2); 

TH1 * histPt_REC_rap_F_low1_to_low2_Eta_SmearedP = histRapPt_REC_Eta_F_SmearedP->ProjectionY("histPt_REC_rap_F_low1_to_low2_Eta_SmearedP",bin_etaF_low1,bin_etaF_low2); 
TH1 * histPt_REC_rap_F_high1_to_high2_Eta_SmearedP = histRapPt_REC_Eta_F_SmearedP->ProjectionY("histPt_REC_rap_F_high1_to_high2_Eta_SmearedP",bin_etaF_high1,bin_etaF_high2); 
TH1 * histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP = histRapPt_REC_Eta_F_SmearedP->ProjectionY("histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP",bin_etaF_mid1,bin_etaF_mid2); 

histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP->Sumw2();
histPt_REC_rap_F_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_REC_rap_F_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP->Sumw2();

//REBINNING
TH1F* histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_F_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin->Sumw2();

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap_F_low1_to_low2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_F_low1_to_low2_Eta_SmearedP");
histPt_RATIO_rap_F_low1_to_low2_Eta_SmearedP->Divide(histPt_REC_rap_F_low1_to_low2_Eta_SmearedP_Rebin, histPt_ALL_rap_F_low1_to_low2_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_F_high1_to_high2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_F_high1_to_high2_Eta_SmearedP");
histPt_RATIO_rap_F_high1_to_high2_Eta_SmearedP->Divide(histPt_REC_rap_F_high1_to_high2_Eta_SmearedP_Rebin, histPt_ALL_rap_F_high1_to_high2_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP");
histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP->Divide(histPt_REC_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin, histPt_ALL_rap_F_mid1_to_mid2_Eta_SmearedP_Rebin, 1,1,"B");

histPt_RATIO_rap_F_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_RATIO_rap_F_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP->Sumw2();

//histPt_RATIO_rap_F_low1_to_low2_Eta->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap_F_low1_to_low2_Eta_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_low1_to_low2_Eta_SmearedP,25,1.0, kBlue , kBlue);
histPt_RATIO_rap_F_high1_to_high2_Eta_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_high1_to_high2_Eta_SmearedP,25,1.0, kRed+2 , kRed+2);
histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP,25,1.0, kGreen+4 , kGreen+4);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_F_low1_to_low2_Eta_SmearedP, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

auto l_eff_Eta_F = new TLegend(0.55, 0.15, 0.7, 0.35);
l_eff_Eta_F->SetHeader("Forward","C");
l_eff_Eta_F->SetBorderSize(0);
l_eff_Eta_F->SetFillStyle(0);
l_eff_Eta_F->SetTextSize(TextSize);
l_eff_Eta_F->AddEntry(histPt_RATIO_rap_F_low1_to_low2_Eta_SmearedP,Form("%.2f < y < %.2f",etaF_low1,etaF_low2));
l_eff_Eta_F->AddEntry(histPt_RATIO_rap_F_high1_to_high2_Eta_SmearedP,Form("%.2f < y < %.2f",etaF_high1,etaF_high2));
l_eff_Eta_F->AddEntry(histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP,Form("%.2f < y < %.2f",etaF_mid1,etaF_mid2));
//l_eff_Eta_F->AddEntry(histPt_RATIO_rap_F_low1_to_low2_Eta, Form("%.2f < y < %.2f",etaF_low1,etaF_low2));
//l_eff_Eta_F->AddEntry(histPt_RATIO_rap_F_high1_to_high2_Eta,Form("%.2f < y < %.2f",etaF_high1,etaF_high2));
//l_eff_Eta_F->AddEntry(histPt_RATIO_rap_F_mid1_to_mid2_Eta, Form("%.2f < y < %.2f",etaF_mid1,etaF_mid2));
l_eff_Eta_F->Draw("SAME");

TLatex *lta_eff_Eta_F = new TLatex(0.2,0.8,"#splitline{Eta Effiiency at different rapidity}{with momentum smearing} ");
SetStyleTLatex( lta_eff_Eta_F, 0.03,4);
lta_eff_Eta_F->Draw("SAME");

TLatex *ltb_eff_Eta_F = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{PbPb, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( ltb_eff_Eta_F, 0.03,4);
ltb_eff_Eta_F->Draw("SAME");

TLatex *ltc_eff_Eta_F = new TLatex(.15,.04,"Smeared momentum are represented by openbox");
SetStyleTLatex( ltc_eff_Eta_F, 0.02,4);
ltc_eff_Eta_F->Draw("SAME");








///////////////  Eta Effiiency at different Barrel rapidity PLOT    ///////////////

c_eff_Eta->cd(2);
c_eff_Eta->cd(2)->SetLogy();  
/*
TH2D * histRapPt_ALL_Eta_B = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");
TH2D * histRapPt_REC_Eta = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec");

TH1 * histPt_ALL_rap_B_low1_to_low2_Eta = histRapPt_ALL_Eta_B->ProjectionY("histPt_MC_rap_B_low1_to_low2",bin_etaB_low1,bin_etaB_high1); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Eta = histRapPt_ALL_Eta_B->ProjectionY("histPt_MC_rap_B_high1_to_high2",bin_etaB_low2,bin_etaB_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Eta = histRapPt_ALL_Eta_B->ProjectionY("histPt_MC_rap_B_mid1_to_mid2",bin_etaB_mid1,bin_etaB_mid2); 

TH1 * histPt_REC_rap_B_low1_to_low2_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap_B_low1_to_low2_Eta",bin_etaB_low1,bin_etaB_high1); 
TH1 * histPt_REC_rap_B_high1_to_high2_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap_B_high1_to_high2_Eta",bin_etaB_low2,bin_etaB_high2); 
TH1 * histPt_REC_rap_B_mid1_to_mid2_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap_B_mid1_to_mid2_Eta",bin_etaB_mid1,bin_etaB_mid2); 

//REBINNING
TH1F* histPt_ALL_rap_B_low1_to_low2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Eta_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_B_low1_to_low2_Eta_Rebin     = (TH1F*) histPt_REC_rap_B_low1_to_low2_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_low1_to_low2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_high1_to_high2_Eta_Rebin        = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_high1_to_high2_Eta_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_mid1_to_mid2_Eta_Rebin     = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Eta->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_mid1_to_mid2_Eta_Rebin",&pt_bin_proj_fine[0]);


//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_B_low1_to_low2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_low1_to_low2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_high1_to_high2_Eta_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_mid1_to_mid2_Eta_Rebin);

//RATIO
TH1F* histPt_RATIO_rap_B_low1_to_low2_Eta  = (TH1F*) histPt_REC_rap_B_low1_to_low2_Eta_Rebin->Clone("histPt_RATIO_rap_B_low1_to_low2_Eta");
histPt_RATIO_rap_B_low1_to_low2_Eta->Divide(histPt_REC_rap_B_low1_to_low2_Eta_Rebin, histPt_ALL_rap_B_low1_to_low2_Eta_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_B_high1_to_high2_Eta  = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta_Rebin->Clone("histPt_RATIO_rap_B_high1_to_high2_Eta");
histPt_RATIO_rap_B_high1_to_high2_Eta->Divide(histPt_REC_rap_B_high1_to_high2_Eta_Rebin, histPt_ALL_rap_B_high1_to_high2_Eta_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_B_mid1_to_mid2_Eta  = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Eta_Rebin->Clone("histPt_RATIO_rap_B_mid1_to_mid2_Eta");
histPt_RATIO_rap_B_mid1_to_mid2_Eta->Divide(histPt_REC_rap_B_mid1_to_mid2_Eta_Rebin, histPt_ALL_rap_B_mid1_to_mid2_Eta_Rebin, 1,1,"B");


//histPt_RATIO_rap_B_low1_to_low2_Eta->GetXaxis()->SetLabelOffset(LabelOffsetLog);
histPt_RATIO_rap_B_low1_to_low2_Eta->Draw("P"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_low1_to_low2_Eta,8,0.9, kBlue , kBlue);
histPt_RATIO_rap_B_high1_to_high2_Eta->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_high1_to_high2_Eta,8,0.9, kRed+2 , kRed+2);
histPt_RATIO_rap_B_mid1_to_mid2_Eta->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_mid1_to_mid2_Eta,8,0.9, kGreen+4 , kGreen+4);


//CHECKER
TH1D * hPtGGEtaF = (TH1D*) fileRec->Get("hPtGGEtaF");
TH1D * hPtGGEtaF_rec = (TH1D*) fileRec->Get("hPtGGEtaF_rec");
hPtGGEtaF->Rebin(20);
hPtGGEtaF_rec->Rebin(20);
TH1F* histPt_RATIO_CheckerF_Eta  = (TH1F*) hPtGGEtaF_rec->Clone("histPt_RATIO_CheckerF_Eta");
histPt_RATIO_CheckerF_Eta->Divide(hPtGGEtaF_rec, hPtGGEtaF, 1,1,"B");
DrawGammaSetMarker(histPt_RATIO_CheckerF_Eta,8,0.5, kCyan , kCyan);
histPt_RATIO_CheckerF_Eta->Draw("SAME");
*/


//WITH MOMENTUM SMEARING


TH2D * histRapPt_ALL_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_SmearedP");
TH2D * histRapPt_REC_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec_SmearedP");

histRapPt_ALL_Eta_B_SmearedP->Sumw2();
histRapPt_REC_Eta_B_SmearedP->Sumw2();

TH1 * histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP",bin_etaB_mid1,bin_etaB_mid2); 

TH1 * histPt_REC_rap_B_low1_to_low2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_low1_to_low2_Eta_SmearedP",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_REC_rap_B_high1_to_high2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_high1_to_high2_Eta_SmearedP",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP",bin_etaB_mid1,bin_etaB_mid2); 

histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP->Sumw2();
histPt_REC_rap_B_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_REC_rap_B_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP->Sumw2();

//REBINNING
TH1F* histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin->Sumw2();
histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin->Sumw2();
histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin->Sumw2();

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP");
histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP->Divide(histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP");
histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP->Divide(histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin, 1,1,"B");
TH1F* histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP");
histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP->Divide(histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin, 1,1,"B");

histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP->Sumw2();
histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP->Sumw2();
histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP->Sumw2();

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP,25,1.0, kBlue , kBlue);
histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP,25,1.0, kRed+2 , kRed+2);
histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP,25,1.0, kGreen+4 , kGreen+4);



//histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP->GetXaxis()->SetRangeUser(0.0,7.0);
//histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP->GetYaxis()->SetRangeUser(10^-5,10^-2);

auto l_eff_Eta_B = new TLegend(0.55, 0.15, 0.7, 0.35);
l_eff_Eta_B->SetHeader("Barrel","C");
l_eff_Eta_B->SetBorderSize(0);
l_eff_Eta_B->SetFillStyle(0);
l_eff_Eta_B->SetTextSize(TextSize);
l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP,Form("%.2f < y < %.2f",etaB_low1,etaB_low2));
l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP,Form("%.2f < y < %.2f",etaB_high1,etaB_high2));
l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP,Form("%.2f < y < %.2f",etaB_mid1,etaB_mid2));
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_low1_to_low2_Eta,Form("%.2f < y < %.2f",etaB_low1,etaB_low2));
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_high1_to_high2_Eta,Form("%.2f < y < %.2f",etaB_high1,etaB_high2));
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_mid1_to_mid2_Eta,Form("%.2f < y < %.2f",etaB_low1,etaB_high2));
l_eff_Eta_B->Draw("SAME");

TLatex *lta_eff_Eta_B = new TLatex(0.2,0.8,"#splitline{Eta Effiiency at different rapidity}{with momentum smearing} ");
SetStyleTLatex( lta_eff_Eta_B, 0.03,4);
lta_eff_Eta_B->Draw("SAME");

TLatex *ltb_eff_Eta_B = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{PbPb, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( ltb_eff_Eta_B, 0.03,4);
ltb_eff_Eta_B->Draw("SAME");

TLatex *ltc_eff_Eta_B = new TLatex(.15,.04,"Smeared momentum are represented by openbox");
SetStyleTLatex( ltc_eff_Eta_B, 0.02,4);
ltc_eff_Eta_B->Draw("SAME");


//c_eff_Eta->Update();



c_eff_Eta->SaveAs("mesonEff/hDiffRap_ratio_Eta.png");

c_eff_Eta->Close();








/*

/////////////////      Meson efficiency Combined plot    ///////////
StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or

TCanvas* c_eff_combined = new TCanvas("c_eff_combined","c_eff_combined",0,0,700,700);
DrawGammaCanvasSettings( c_eff_combined, 0.1, 0.02, 0.02, 0.1);

c_eff_combined->SetLogy();  


histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP->Draw("P"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP,8,0.9, kRed , kRed);
histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP,8,0.9, kGreen+3 , kGreen+3);
histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP,25,0.9, kGreen+3 , kGreen+3);
histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP->Draw("SAME,P"); 
DrawGammaSetMarker(histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP,25,0.9, kRed , kRed);

SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP, "pT (GeV)", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP->GetYaxis()->SetRangeUser(10^-5,10^-2);

auto l_eff_combined = new TLegend(0.35, 0.15, 0.7, 0.35);
//l_eff_combined->SetHeader("Barrel","C");
l_eff_combined->SetBorderSize(0);
l_eff_combined->SetFillStyle(0);
l_eff_combined->SetTextSize(TextSize);
l_eff_combined->AddEntry(histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP,Form("#eta : %.2f < y < %.2f",etaB_low1,etaB_low2));
l_eff_combined->AddEntry(histPt_RATIO_rap_B_mid1_to_mid2_Pi0_SmearedP,Form("#pi^{0} : %.2f < y < %.2f",etaB_high1,etaB_high2));
l_eff_combined->AddEntry(histPt_RATIO_rap_F_mid1_to_mid2_Eta_SmearedP,Form("#eta : %.2f < y < %.2f",etaF_mid1,etaF_mid2));
l_eff_combined->AddEntry(histPt_RATIO_rap_F_mid1_to_mid2_Pi0_SmearedP,Form("#pi^{0} : %.2f < y < %.2f",etaF_mid1,etaF_mid2));
l_eff_combined->Draw("SAME");

TLatex *lta_eff_combined = new TLatex(0.6,0.9,"#splitline{Effiiency at different rapidity}{} ");
SetStyleTLatex( lta_eff_combined, 0.03,4);
lta_eff_combined->Draw("SAME");

TLatex *ltb_eff_combined = new TLatex(0.2,0.9,"#splitline{ALICE 3 Study}{PbPb, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( ltb_eff_combined, 0.03,4);
ltb_eff_combined->Draw("SAME");


c_eff_combined->Update();

c_eff_combined->SaveAs("mesonEff/hDiffRap_ratio_combined.png");

c_eff_combined->Close();
*/

}