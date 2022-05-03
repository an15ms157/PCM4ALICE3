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
void tester(){
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
TFile * fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3.root");
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







/*
double pt_bin_proj[nBinsPt+1];
for(int i=0; i<nBinsPt+1; i++){
      if (i < 10) pt_bin_proj[i]            =  0.1*i;
      else if(i<20) pt_bin_proj[i]          = 1.0 + 0.2*(i-10);
      else if(i<22) pt_bin_proj[i]          = 3.0 + 0.5*(i-20);
      else pt_bin_proj[i]                   = fMaxPt;
}
*/

TCanvas* c_eff_Eta = new TCanvas("c_eff_Eta","c_eff_Eta",200,10,1600,1600);  // gives the page size
DrawGammaCanvasSettings( c_eff_Eta, 0.3, 0.02, 0.02, 0.16);
c_eff_Eta->Divide(2,1);
//c_eff_Eta->cd(1)->SetLogy();  
c_eff_Eta->cd(1);

Double_t etaB_low1   = 0.0;
Double_t etaB_low2   = 0.8;
Double_t etaB_high1  = 0.0;
Double_t etaB_high2  = 1.3;
Double_t etaB_mid1   = 0.8;
Double_t etaB_mid2   = 1.3;


TH2D * histRapPt_ALL_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_SmearedP");
TH2D * histRapPt_REC_Eta_B_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec_SmearedP");

TH2D * histRapPt_ALL_Pi0_B = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH2D * histRapPt_REC_Pi0 = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec");

TAxis *XAXIS_Pi0 = histRapPt_ALL_Pi0_B->GetXaxis();
Int_t bin_etaB_low1     = XAXIS_Pi0->FindBin(etaB_low1 + 0.0001);
Int_t bin_etaB_low2     = XAXIS_Pi0->FindBin(etaB_low2 - 0.0001);
Int_t bin_etaB_high1    = XAXIS_Pi0->FindBin(etaB_high1+ 0.0001);
Int_t bin_etaB_high2    = XAXIS_Pi0->FindBin(etaB_high2-0.0001);
Int_t bin_etaB_mid1    = XAXIS_Pi0->FindBin(etaB_mid1+ 0.0001);
Int_t bin_etaB_mid2    = XAXIS_Pi0->FindBin(etaB_mid2-0.0001);

cout<< "Barrel:"<< endl<< bin_etaB_low1<< endl<< bin_etaB_low2<< endl<< bin_etaB_mid1<< endl<< bin_etaB_mid2<< endl<<bin_etaB_high1<< endl<< bin_etaB_high2<< endl<< '\n';

TH1 * histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP",bin_etaB_mid1,bin_etaB_mid2); 

TH1 * histPt_REC_rap_B_low1_to_low2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_low1_to_low2_Eta_SmearedP",bin_etaB_low1,bin_etaB_low2); 
TH1 * histPt_REC_rap_B_high1_to_high2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_high1_to_high2_Eta_SmearedP",bin_etaB_high1,bin_etaB_high2); 
TH1 * histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP",bin_etaB_mid1,bin_etaB_mid2); 

//REBINNING
TH1F* histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_low1_to_low2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin        = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin     = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP->Rebin(nbinspt_proj_fine,"histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin",&pt_bin_proj_fine[0]);

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


//LABELING
//SetStyleHistoTH1ForGraphs(histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);

histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP->Draw("SAME,E1"); 
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
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP,Form("%.2f < y < %.2f",etaB_low1,etaB_low2));
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP,Form("%.2f < y < %.2f",etaB_high1,etaB_high2));
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP,Form("%.2f < y < %.2f",etaB_mid1,etaB_mid2));
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_low1_to_low2_Eta,Form("%.2f < y < %.2f",etaB_low1,etaB_low2));
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_high1_to_high2_Eta,Form("%.2f < y < %.2f",etaB_high1,etaB_high2));
//l_eff_Eta_B->AddEntry(histPt_RATIO_rap_B_mid1_to_mid2_Eta,Form("%.2f < y < %.2f",etaB_low1,etaB_high2));
l_eff_Eta_B->Draw("SAME");

TLatex *lta_eff_Eta_B = new TLatex(0.2,0.8,"#splitline{Eta Effiiency at different rapidity}{with momentum smearing} ");
SetStyleTLatex( lta_eff_Eta_B, 0.03,4);
lta_eff_Eta_B->Draw("SAME");

TLatex *ltb_eff_Eta_B = new TLatex(0.65,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( ltb_eff_Eta_B, 0.03,4);
ltb_eff_Eta_B->Draw("SAME");

TLatex *ltc_eff_Eta_B = new TLatex(.15,.04,"Smeared momentum are represented by openbox");
SetStyleTLatex( ltc_eff_Eta_B, 0.02,4);
ltc_eff_Eta_B->Draw("SAME");


c_eff_Eta->Update();

c_eff_Eta->cd(2);
c_eff_Eta->cd(2)->SetLogy();

//TH1F* histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP");
//histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP->Divide(histPt_REC_rap_B_low1_to_low2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_low1_to_low2_Eta_SmearedP_Rebin, 1,1,"B");
//TH1F* histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP");
//histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP->Divide(histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin, 1,1,"B");
//TH1F* histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP  = (TH1F*) histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP");
//histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP->Divide(histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_mid1_to_mid2_Eta_SmearedP_Rebin, 1,1,"B");


histPt_RATIO_rap_B_low1_to_low2_Eta_SmearedP->Draw();
histPt_RATIO_rap_B_high1_to_high2_Eta_SmearedP->Draw("SAME");
histPt_RATIO_rap_B_mid1_to_mid2_Eta_SmearedP->Draw("SAME");
//TH1F* histPt_RATIO_rap_B_high1_to_high2_Eta  = (TH1F*) histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin->Clone("histPt_RATIO_rap_B_high1_to_high2_Eta");
//histPt_RATIO_rap_B_high1_to_high2_Eta->Divide(histPt_REC_rap_B_high1_to_high2_Eta_SmearedP_Rebin, histPt_ALL_rap_B_high1_to_high2_Eta_SmearedP_Rebin, 1,1,"B");
//histPt_RATIO_rap_B_high1_to_high2_Eta->Draw();

//histPt_REC_rap_B_low1_to_low2_Eta_SmearedP->Draw("");
//histPt_REC_rap_B_high1_to_high2_Eta_SmearedP->Draw("SAME");
//histPt_REC_rap_B_mid1_to_mid2_Eta_SmearedP->Draw("SAME, E4");

c_eff_Eta->SaveAs("tester/hDiffRap_ratio_Eta.png");

//c_eff_Eta->Close();
}