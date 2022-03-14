#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"


void efficiency(){

//   TO MOVE STATBOX
//gStyle->SetStatX(.44);
//gStyle->SetStatY(.83);

//   TO VANISH STAT BOX 
                                                ////////////////FORWARD///////////////

TFile * fileRec1 = new TFile("/home/abhishek/PhD/Work/work_A/photons/anaConv/plots/pp_0.1pTcut/ana_pTcut_withft3.root");
TFile * fileRec2 = new TFile("/home/abhishek/PhD/Work/work_A/photons/anaConv/plots/pp_0.25pTcut/ana_pTcut_withft3.root");
TFile * fileRec3 = new TFile("/home/abhishek/PhD/Work/work_A/photons/anaConv/plots/pp_0.5pTcut/ana_pTcut_withft3.root");

///////////////  Pi0 Effiiency at different rapidity PLOT    ///////////////

TCanvas c14("c14", "c14", 1600, 1600);
c14.Divide(2,1);

c14.cd(1);
TH2D * histRapPt_ALL_Pi0_pT1 = (TH2D*) fileRec1->Get("hRapidityPt_Pi0_F_GG_SpearedP");
TH1 * histPt_ALL_rap1_75to4_Pi0_pT1 = histRapPt_ALL_Pi0_pT1->ProjectionY("histPt_MC_rap1_75to4",1,1000); 
TH2D * histRapPt_REC_Pi0_pT1 = (TH2D*) fileRec1->Get("hRapidityPt_Pi0_F_GG_rec");
TH1 * histPt_REC_rap1_75to4_Pi0_pT1 = histRapPt_REC_Pi0_pT1->ProjectionY("histPt_REC_rap1_75to3_Pi0",1,1000); 
TH1F* histPt_RATIO_rap1_75to4_Pi0_pT1  = (TH1F*) histPt_REC_rap1_75to4_Pi0_pT1->Clone("histPt_RATIO_rap1_75to4_Pi0_pT1");
histPt_RATIO_rap1_75to4_Pi0_pT1->Divide(histPt_REC_rap1_75to4_Pi0_pT1, histPt_ALL_rap1_75to4_Pi0_pT1, 1,1,"B");

TH2D * histRapPt_ALL_Pi0_pT2 = (TH2D*) fileRec2->Get("hRapidityPt_Pi0_F_GG_SpearedP");
TH1 * histPt_ALL_rap1_75to4_Pi0_pT2 = histRapPt_ALL_Pi0_pT2->ProjectionY("histPt_MC_rap1_75to4",1,1000); 
TH2D * histRapPt_REC_Pi0_pT2 = (TH2D*) fileRec1->Get("hRapidityPt_Pi0_F_GG_rec");
TH1 * histPt_REC_rap1_75to4_Pi0_pT2 = histRapPt_REC_Pi0_pT2->ProjectionY("histPt_REC_rap1_75to3_Pi0",1,1000); 
TH1F* histPt_RATIO_rap1_75to4_Pi0_pT2  = (TH1F*) histPt_REC_rap1_75to4_Pi0_pT2->Clone("histPt_RATIO_rap1_75to4_Pi0_pT2");
histPt_RATIO_rap1_75to4_Pi0_pT2->Divide(histPt_REC_rap1_75to4_Pi0_pT2, histPt_ALL_rap1_75to4_Pi0_pT2, 1,1,"B");

TH2D * histRapPt_ALL_Pi0_pT3 = (TH2D*) fileRec3->Get("hRapidityPt_Pi0_F_GG_SpearedP");
TH1 * histPt_ALL_rap1_75to4_Pi0_pT3 = histRapPt_ALL_Pi0_pT3->ProjectionY("histPt_MC_rap1_75to4",1,1000); 
TH2D * histRapPt_REC_Pi0_pT3 = (TH2D*) fileRec1->Get("hRapidityPt_Pi0_F_GG_rec");
TH1 * histPt_REC_rap1_75to4_Pi0_pT3 = histRapPt_REC_Pi0_pT3->ProjectionY("histPt_REC_rap1_75to3_Pi0",1,1000); 
TH1F* histPt_RATIO_rap1_75to4_Pi0_pT3  = (TH1F*) histPt_REC_rap1_75to4_Pi0_pT3->Clone("histPt_RATIO_rap1_75to4_Pi0_pT3");
histPt_RATIO_rap1_75to4_Pi0_pT3->Divide(histPt_REC_rap1_75to4_Pi0_pT3, histPt_ALL_rap1_75to4_Pi0_pT3, 1,1,"B");


histPt_RATIO_rap1_75to4_Pi0_pT3->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap1_75to4_Pi0_pT3->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap1_75to4_Pi0_pT3->GetXaxis()->SetLogy();
histPt_RATIO_rap1_75to4_Pi0_pT3->SetMarkerStyle(3);
histPt_RATIO_rap1_75to4_Pi0_pT3->SetLineColor(kRed);  
histPt_RATIO_rap1_75to4_Pi0_pT2->SetMarkerColor(kBlue);
histPt_RATIO_rap1_75to4_Pi0_pT2->SetMarkerStyle(4);
histPt_RATIO_rap1_75to4_Pi0_pT1->SetMarkerColor(kBlack);
histPt_RATIO_rap1_75to4_Pi0_pT1->SetMarkerStyle(8);
c14.cd(1)->SetLogy();  
histPt_RATIO_rap1_75to4_Pi0_pT3->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap1_75to4_Pi0_pT3->GetYaxis()->SetRangeUser(.0001,1.1);

histPt_RATIO_rap1_75to4_Pi0_pT3->Draw();
histPt_RATIO_rap1_75to4_Pi0_pT2->Draw("SAME");
histPt_RATIO_rap1_75to4_Pi0_pT1->Draw("SAME");

auto leg_Pi0_eff = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Pi0_eff->SetHeader("ALICE 3 Study");
leg_Pi0_eff->SetBorderSize(0);
leg_Pi0_eff->SetFillStyle(0);
leg_Pi0_eff->SetTextSize(0.03);
leg_Pi0_eff->AddEntry(histPt_RATIO_rap1_75to4_Pi0_pT2,"Pi0 efficiency: rapidity: 1.75-3 ","p");
leg_Pi0_eff->AddEntry(histPt_RATIO_rap1_75to4_Pi0_pT3,"Pi0 efficiency: rapidity: 3-4","p");
leg_Pi0_eff->AddEntry(histPt_RATIO_rap1_75to4_Pi0_pT1,"Pi0 efficiency: rapidity: 1.75-4","p");
//leg_Pi0_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Pi0_eff->Draw("SAME");

c14.SaveAs("plots/hDiffRap_ratio_Pi0_F.png");





/*
///////////////  Eta Effiiency at different rapidity PLOT    ///////////////
double fMaxPt=5.0;
const int nBinsPt=1001;
double pt_bin_proj[nBinsPt+1];
for(int i=0; i<nBinsPt+1; i++){
      if (i < 50) pt_bin_proj[i]            =  0.1*i;
      else if(i<60) pt_bin_proj[i]          = 0.5 + 0.2*(i-50);
      else if(i<70) pt_bin_proj[i]          = 2.0 + 0.5*(i-60);
      else if(i<78) pt_bin_proj[i]          = 3.0 + 1.0*(i-70);
      else pt_bin_proj[i]                   = fMaxPt;
}
Int_t nbinspt_proj  = sizeof(pt_bin_proj)/sizeof(*pt_bin_proj) -1;


TCanvas c15("c15", "c15", 1600, 1600);
c15.Divide(2,1);

c15.cd(1);
TH2D * histRapPt_ALL_Eta = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");
TH1 * histPt_ALL_rap1_75to4_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap1_75to4",1,1000); 
TH1 * histPt_ALL_rap3to4_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap3to4",300,400); 
TH1 * histPt_ALL_rap1_75to3_Eta = histRapPt_ALL_Eta->ProjectionY("histPt_MC_rap1_75to3",175,300); 

TH2D * histRapPt_REC_Eta = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec");
TH1 * histPt_REC_rap1_75to4_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap1_75to3_Eta",1,1000); 
TH1 * histPt_REC_rap3to4_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap3to4_Eta",300,400); 
TH1 * histPt_REC_rap1_75to3_Eta = histRapPt_REC_Eta->ProjectionY("histPt_REC_rap1_75to3_Eta",175,300); 

TH1F* histPt_RATIO_rap3to4_Eta  = (TH1F*) histPt_REC_rap3to4_Eta->Clone("histPt_RATIO_rap3to4_Eta");
histPt_RATIO_rap3to4_Eta->Divide(histPt_REC_rap3to4_Eta, histPt_ALL_rap3to4_Eta, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Eta  = (TH1F*) histPt_REC_rap1_75to3_Eta->Clone("histPt_RATIO_rap1_75to3_Eta");
histPt_RATIO_rap1_75to3_Eta->Divide(histPt_REC_rap1_75to3_Eta, histPt_ALL_rap1_75to3_Eta, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to4_Eta  = (TH1F*) histPt_REC_rap1_75to4_Eta->Clone("histPt_RATIO_rap1_75to4_Eta");
histPt_RATIO_rap1_75to4_Eta->Divide(histPt_REC_rap1_75to4_Eta, histPt_ALL_rap1_75to4_Eta, 1,1,"B");

histPt_RATIO_rap3to4_Eta->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap3to4_Eta->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap3to4_Eta->GetXaxis()->SetLogy();
histPt_RATIO_rap3to4_Eta->SetMarkerStyle(3);
histPt_RATIO_rap3to4_Eta->SetLineColor(kRed);  
histPt_RATIO_rap1_75to3_Eta->SetMarkerColor(kBlue);
histPt_RATIO_rap1_75to3_Eta->SetMarkerStyle(4);
histPt_RATIO_rap1_75to4_Eta->SetMarkerColor(kBlack);
histPt_RATIO_rap1_75to4_Eta->SetMarkerStyle(8);
c15.cd(1)->SetLogy();  
histPt_RATIO_rap3to4_Eta->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap3to4_Eta->GetYaxis()->SetRangeUser(.0001,1.1);

TH1F* histPt_RATIO_rap3to4_Eta_Rebin      = (TH1F*) histPt_RATIO_rap3to4_Eta->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
TH1F* histPt_RATIO_rap1_75to3_Eta_Rebin   = (TH1F*) histPt_RATIO_rap1_75to3_Eta->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
TH1F* histPt_RATIO_rap1_75to4_Eta_Rebin   = (TH1F*) histPt_RATIO_rap1_75to4_Eta->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
//histPt_RATIO_rap3to4_Eta_Rebin->Draw();
//histPt_RATIO_rap1_75to3_Eta_Rebin->Draw("SAME");
//histPt_RATIO_rap1_75to4_Eta_Rebin->Draw("SAME");
histPt_RATIO_rap3to4_Eta->Draw();
histPt_RATIO_rap1_75to3_Eta->Draw("SAME");
histPt_RATIO_rap1_75to4_Eta->Draw("SAME");

auto leg_Eta_eff = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Eta_eff->SetHeader("ALICE 3 Study");
leg_Eta_eff->SetBorderSize(0);
leg_Eta_eff->SetFillStyle(0);
leg_Eta_eff->SetTextSize(0.03);
leg_Eta_eff->AddEntry(histPt_RATIO_rap3to4_Eta_Rebin,"Eta efficiency: rapidity: 1.75-3 ","p");
leg_Eta_eff->AddEntry(histPt_RATIO_rap1_75to3_Eta_Rebin,"Eta efficiency: rapidity: 3-4","p");
leg_Eta_eff->AddEntry(histPt_RATIO_rap1_75to4_Eta_Rebin,"Eta efficiency: rapidity: 1.75-4","p");
//leg_Eta_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Eta_eff->Draw("SAME");



c15.cd(2);
TH2D * histRapPt_ALL_Eta_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_SmearedP");
TH1 * histPt_ALL_rap3to4_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap3to4",300,400); 
TH1 * histPt_ALL_rap1_75to3_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap1_75to3",180,300); 
TH1 * histPt_ALL_rap1_75to4_Eta_SmearedP = histRapPt_ALL_Eta_SmearedP->ProjectionY("histPt_MC_rap1_75to4",1,1000); 

TH2D * histRapPt_REC_Eta_SmearedP = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG_rec_SmearedP");
TH1 * histPt_REC_rap3to4_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap3to4_Eta_SmearedP",300,400); 
TH1 * histPt_REC_rap1_75to3_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap1_75to3_Eta_SmearedP",180,300); 
TH1 * histPt_REC_rap1_75to4_Eta_SmearedP = histRapPt_REC_Eta_SmearedP->ProjectionY("histPt_REC_rap1_75to4_Eta_SmearedP",1,1000); 

TH1F* histPt_RATIO_rap3to4_Eta_SmearedP  = (TH1F*) histPt_REC_rap3to4_Eta_SmearedP->Clone("histPt_RATIO_rap3to4_Eta_SmearedP");
histPt_RATIO_rap3to4_Eta_SmearedP->Divide(histPt_REC_rap3to4_Eta_SmearedP, histPt_ALL_rap3to4_Eta_SmearedP, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Eta_SmearedP  = (TH1F*) histPt_REC_rap1_75to3_Eta_SmearedP->Clone("histPt_RATIO_rap1_75to3_Eta_SmearedP");
histPt_RATIO_rap1_75to3_Eta_SmearedP->Divide(histPt_REC_rap1_75to3_Eta_SmearedP, histPt_ALL_rap1_75to3_Eta_SmearedP, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to4_Eta_SmearedP  = (TH1F*) histPt_REC_rap1_75to4_Eta_SmearedP->Clone("histPt_RATIO_rap1_75to4_Eta_SmearedP");
histPt_RATIO_rap1_75to4_Eta_SmearedP->Divide(histPt_REC_rap1_75to4_Eta_SmearedP, histPt_ALL_rap1_75to4_Eta_SmearedP, 1,1,"B");

c15.cd(2)->SetLogy();  

//histPt_REC_rap1_75to3_Eta_SmearedP->Draw();
//histPt_ALL_rap1_75to3_Eta_SmearedP->Draw("SAME");

histPt_RATIO_rap3to4_Eta_SmearedP->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap3to4_Eta_SmearedP->GetXaxis()->SetTitle("pT");
//histPt_RATIO_rap3to4_Eta_SmearedP->GetXaxis()->SetLogy();
histPt_RATIO_rap3to4_Eta_SmearedP->SetMarkerStyle(3);
histPt_RATIO_rap3to4_Eta_SmearedP->SetLineColor(kRed);  
histPt_RATIO_rap1_75to3_Eta_SmearedP->SetMarkerColor(kBlue);
histPt_RATIO_rap1_75to3_Eta_SmearedP->SetMarkerStyle(4);
histPt_RATIO_rap1_75to4_Eta_SmearedP->SetMarkerColor(kBlack);
histPt_RATIO_rap1_75to4_Eta_SmearedP->SetMarkerStyle(8);

c15.cd(2)->SetLogy();  
histPt_RATIO_rap3to4_Eta_SmearedP->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap3to4_Eta_SmearedP->GetYaxis()->SetRangeUser(.0001,1.1);

TH1F* histPt_RATIO_rap3to4_Eta_SmearedP_Rebin      = (TH1F*) histPt_RATIO_rap3to4_Eta_SmearedP->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
TH1F* histPt_RATIO_rap1_75to3_Eta_SmearedP_Rebin   = (TH1F*) histPt_RATIO_rap1_75to3_Eta_SmearedP->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);
TH1F* histPt_RATIO_rap1_75to4_Eta_SmearedP_Rebin   = (TH1F*) histPt_RATIO_rap1_75to4_Eta_SmearedP->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);

//histPt_RATIO_rap3to4_Eta_SmearedP_Rebin->Draw();
//histPt_RATIO_rap1_75to3_Eta_SmearedP_Rebin->Draw("SAME");
//histPt_RATIO_rap1_75to4_Eta_SmearedP_Rebin->Draw("SAME");
histPt_RATIO_rap3to4_Eta_SmearedP->Draw();
histPt_RATIO_rap1_75to3_Eta_SmearedP->Draw("SAME");
histPt_RATIO_rap1_75to4_Eta_SmearedP->Draw("SAME");

auto leg_Eta_SmearedP_eff = new TLegend(0.2, 0.7, 0.4, 0.8);
leg_Eta_SmearedP_eff->SetHeader("ALICE 3 Study");
leg_Eta_SmearedP_eff->SetBorderSize(0);
leg_Eta_SmearedP_eff->SetFillStyle(0);
leg_Eta_SmearedP_eff->SetTextSize(0.03);
leg_Eta_SmearedP_eff->AddEntry(histPt_RATIO_rap1_75to3_Eta_SmearedP,"Eta efficiency: rapidity: 1.75-3 ","p");
leg_Eta_SmearedP_eff->AddEntry(histPt_RATIO_rap3to4_Eta_SmearedP,"Eta efficiency: rapidity: 3-4","p");
leg_Eta_SmearedP_eff->AddEntry(histPt_RATIO_rap1_75to4_Eta_SmearedP,"Eta efficiency: rapidity: 1.75-4","p");
//leg_Eta_SmearedP_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_Eta_SmearedP_eff->Draw("SAME");


c15.SaveAs("plots/hDiffRap_ratio_Eta_F.png");
*/


}

