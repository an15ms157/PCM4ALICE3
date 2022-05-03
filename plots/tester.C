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
//gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or

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


///////////////  Acceptance at different rapidity PLOT    ///////////////

TCanvas* c119 = new TCanvas("c119","c119",0,0,700,700);  // gives the page size
DrawGammaCanvasSettings( c119, 0.1, 0.02, 0.02, 0.1);
//c119->Divide(2,1);
//c119->SetLogy();  

c119->cd(1);
//Barrel
TH2D * histRapPt_All_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B");
TH2D * histRapPt_All_Pi0_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");

TH1 * histPt_All_rap0to1_3_Pi0_B    = histRapPt_All_Pi0_B->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B"); 
TH1 * histPt_All_rap0to1_3_Pi0_B_GG    = histRapPt_All_Pi0_B_GG->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B_GG"); 

TH2D * histRapPt_All_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B");
TH2D * histRapPt_All_Eta_B_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");

TH1 * histPt_All_rap0to1_3_Eta_B    = histRapPt_All_Eta_B->ProjectionY("histPt_ALL_rap0to1_3_Eta_B"); 
TH1 * histPt_All_rap0to1_3_Eta_B_GG    = histRapPt_All_Eta_B_GG->ProjectionY("histPt_ALL_rap0to1_3_Eta_B_GG");

//Forward
TH2D * histRapPt_All_Pi0_F          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F");
TH2D * histRapPt_All_Pi0_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");

TH1 * histPt_All_rap0to1_3_Pi0_F    = histRapPt_All_Pi0_F->ProjectionY("histPt_ALL_rap0to1_3_Pi0_F"); 
TH1 * histPt_All_rap0to1_3_Pi0_F_GG    = histRapPt_All_Pi0_F_GG->ProjectionY("histPt_ALL_rap0to1_3_Pi0_F_GG"); 

TH2D * histRapPt_All_Eta_F          = (TH2D*) fileRec->Get("hRapidityPt_Eta_F");
TH2D * histRapPt_All_Eta_F_GG       = (TH2D*) fileRec->Get("hRapidityPt_Eta_F_GG");

TH1 * histPt_All_rap0to1_3_Eta_F    = histRapPt_All_Eta_F->ProjectionY("histPt_ALL_rap0to1_3_Eta_F"); 
TH1 * histPt_All_rap0to1_3_Eta_F_GG    = histRapPt_All_Eta_F_GG->ProjectionY("histPt_ALL_rap0to1_3_Eta_F_GG");





/*
//SMEARED P
TH2D * histRapPt_ALL_Pi0_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_SmearedP");
TH1 * histPt_ALL_rap0to1_3_Pi0_B_SmearedP    = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B_SmearedP"); 
TH2D * histRapPt_REC_Pi0_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec_SmearedP");
TH1 * histPt_REC_rap0to1_3_Pi0_B_SmearedP    = histRapPt_REC_Pi0_B_SmearedP->ProjectionY("histPt_REC_rap0to1_3_Pi0_B_SmearedP");

//REBINNING
TH1F* histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin);

*/
TH1F* histPt_All_rap0to1_3_Pi0_B_Rebin     = (TH1F*) histPt_All_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_All_rap0to1_3_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_All_rap0to1_3_Pi0_B_GG_Rebin     = (TH1F*) histPt_All_rap0to1_3_Pi0_B_GG->Rebin(nbinspt_proj_fine,"histPt_All_rap0to1_3_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_All_rap0to1_3_Pi0_B_Rebin);
DivideTH1ByBinWidth(histPt_All_rap0to1_3_Pi0_B_GG_Rebin);

TH1F* histPt_All_rap0to1_3_Eta_B_Rebin     = (TH1F*) histPt_All_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_All_rap0to1_3_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_All_rap0to1_3_Eta_B_GG_Rebin     = (TH1F*) histPt_All_rap0to1_3_Eta_B_GG->Rebin(nbinspt_proj_fine,"histPt_All_rap0to1_3_Eta_B_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_All_rap0to1_3_Eta_B_Rebin);
DivideTH1ByBinWidth(histPt_All_rap0to1_3_Eta_B_GG_Rebin);


TH1F* histPt_All_rap0to1_3_Pi0_F_Rebin     = (TH1F*) histPt_All_rap0to1_3_Pi0_F->Rebin(nbinspt_proj_fine,"histPt_All_rap0to1_3_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_All_rap0to1_3_Pi0_F_GG_Rebin     = (TH1F*) histPt_All_rap0to1_3_Pi0_F_GG->Rebin(nbinspt_proj_fine,"histPt_All_rap0to1_3_Pi0_F_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_All_rap0to1_3_Pi0_F_Rebin);
DivideTH1ByBinWidth(histPt_All_rap0to1_3_Pi0_F_GG_Rebin);

TH1F* histPt_All_rap0to1_3_Eta_F_Rebin     = (TH1F*) histPt_All_rap0to1_3_Eta_F->Rebin(nbinspt_proj_fine,"histPt_All_rap0to1_3_Eta_F_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_All_rap0to1_3_Eta_F_GG_Rebin  = (TH1F*) histPt_All_rap0to1_3_Eta_F_GG->Rebin(nbinspt_proj_fine,"histPt_All_rap0to1_3_Eta_F_Rebin",&pt_bin_proj_fine[0]);
DivideTH1ByBinWidth(histPt_All_rap0to1_3_Eta_F_Rebin);
DivideTH1ByBinWidth(histPt_All_rap0to1_3_Eta_F_GG_Rebin);

//histPt_All_rap0to1_3_Pi0_F_Rebin->GetYaxis()->SetRangeUser(100, 10000000);
//histPt_All_rap0to1_3_Pi0_F_Rebin->Draw("E1");



//RATIO
TH1F* histPt_Acceptance_rap1_75to3_Pi0_B  = (TH1F*) histPt_All_rap0to1_3_Pi0_B_Rebin->Clone("histPt_Acceptance_rap1_75to3_Pi0_B");
histPt_Acceptance_rap1_75to3_Pi0_B->Divide(histPt_All_rap0to1_3_Pi0_B_GG_Rebin, histPt_All_rap0to1_3_Pi0_B_Rebin, 1,1,"B");
histPt_Acceptance_rap1_75to3_Pi0_B->Draw("E1"); 
DrawGammaSetMarker(histPt_Acceptance_rap1_75to3_Pi0_B,25,0.5, kBlack , kBlack);

TH1F* histPt_Acceptance_rap1_75to3_Eta_B  = (TH1F*) histPt_All_rap0to1_3_Eta_B_Rebin->Clone("histPt_Acceptance_rap1_75to3_Eta_B");
histPt_Acceptance_rap1_75to3_Eta_B->Divide(histPt_All_rap0to1_3_Eta_B_GG_Rebin, histPt_All_rap0to1_3_Eta_B_Rebin, 1,1,"B");
histPt_Acceptance_rap1_75to3_Eta_B->Draw("E1, SAME"); 
DrawGammaSetMarker(histPt_Acceptance_rap1_75to3_Eta_B,25,0.5, kBlue , kBlue);


TH1F* histPt_Acceptance_rap1_75to3_Pi0_F  = (TH1F*) histPt_All_rap0to1_3_Pi0_F_Rebin->Clone("histPt_Acceptance_rap1_75to3_Pi0_F");
histPt_Acceptance_rap1_75to3_Pi0_F->Divide(histPt_All_rap0to1_3_Pi0_F_GG_Rebin, histPt_All_rap0to1_3_Pi0_F_Rebin, 1,1,"B");
histPt_Acceptance_rap1_75to3_Pi0_F->Draw("E1, SAME"); 
DrawGammaSetMarker(histPt_Acceptance_rap1_75to3_Pi0_F,21,0.5, kBlack , kBlack);
TH1F* histPt_Acceptance_rap1_75to3_Eta_F  = (TH1F*) histPt_All_rap0to1_3_Eta_F_Rebin->Clone("histPt_Acceptance_rap1_75to3_Eta_F");
histPt_Acceptance_rap1_75to3_Eta_F->Divide(histPt_All_rap0to1_3_Eta_F_GG_Rebin, histPt_All_rap0to1_3_Eta_F_Rebin, 1,1,"B");

histPt_Acceptance_rap1_75to3_Eta_F->Draw("E1, SAME"); 
DrawGammaSetMarker(histPt_Acceptance_rap1_75to3_Eta_F,21,0.5, kBlue , kBlue);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_Acceptance_rap1_75to3_Eta_B, "pT (GeV/c)", "acceptance", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
//histPt_Acceptance_rap1_75to3_Pi0_B->GetXaxis()->SetRangeUser(0.0,10.0);
//histPt_Acceptance_rap1_75to3_Eta_B->GetYaxis()->SetRangeUser(0.01,1.5)
histPt_Acceptance_rap1_75to3_Pi0_B->GetYaxis()->SetRangeUser(0.01, 1.0);
//histPt_Acceptance_rap1_75to3_Eta_B->SetAxisRange(0.1, 1.1, "Y");

auto l119 = new TLegend(0.7, 0.2, 0.9, 0.35);
l119->SetHeader("");
l119->SetBorderSize(0);
l119->SetFillStyle(0);
l119->SetTextSize(TextSize);
l119->AddEntry(histPt_Acceptance_rap1_75to3_Pi0_B,"Pi0:  0<|y|<1.3 ","p");
l119->AddEntry(histPt_Acceptance_rap1_75to3_Eta_B,"Eta:  0<|y|<1.3 ","p");
l119->AddEntry(histPt_Acceptance_rap1_75to3_Pi0_F,"Pi0:  1.75<|y|<4.0 ","p");
l119->AddEntry(histPt_Acceptance_rap1_75to3_Eta_F,"Eta:  1.75<|y|<4.0 ","p");
l119->Draw("SAME");

TLatex *lt119a = new TLatex(0.7,0.85,"Meson Acceptance");
SetStyleTLatex( lt119a, 0.03,4);
lt119a->Draw("SAME");

TLatex *lt119b = new TLatex(0.7,0.75,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt119b, 0.03,4);
lt119b->Draw("SAME");
//c119->Update();
//histPt_Acceptance_rap1_75to3_Pi0_B->Draw("E1, SAME"); 

c119->SaveAs("./hAcceptance_meson.png");

//c119->Close();



///////////////  Pi0 Effiiency at different rapidity PLOT    ///////////////

TCanvas* c114 = new TCanvas("c114","c114",200,10,700,700);  // gives the page size
DrawGammaCanvasSettings( c114, 0.1, 0.02, 0.02, 0.1);
//c114->Divide(2,1);
c114->SetLogy();  

c114->cd(1);
TH2D * histRapPt_ALL_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG");
TH1 * histPt_ALL_rap0to1_3_Pi0_B    = histRapPt_ALL_Pi0_B->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B"); 
TH2D * histRapPt_REC_Pi0_B          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec");
TH1 * histPt_REC_rap0to1_3_Pi0_B    = histRapPt_REC_Pi0_B->ProjectionY("histPt_REC_rap0to1_3_Pi0_B"); 

//SMEARED P
TH2D * histRapPt_ALL_Pi0_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_SmearedP");
TH1 * histPt_ALL_rap0to1_3_Pi0_B_SmearedP    = histRapPt_ALL_Pi0_B_SmearedP->ProjectionY("histPt_ALL_rap0to1_3_Pi0_B_SmearedP"); 
TH2D * histRapPt_REC_Pi0_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Pi0_B_GG_rec_SmearedP");
TH1 * histPt_REC_rap0to1_3_Pi0_B_SmearedP    = histRapPt_REC_Pi0_B_SmearedP->ProjectionY("histPt_REC_rap0to1_3_Pi0_B_SmearedP");

//REBINNING
TH1F* histPt_ALL_rap0to1_3_Pi0_B_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Pi0_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Pi0_B_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Pi0_B_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Pi0_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Pi0_B_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Pi0_B_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap1_75to3_Pi0_B  = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B_Rebin->Clone("histPt_RATIO_rap1_75to3_Pi0_B");
histPt_RATIO_rap1_75to3_Pi0_B->Divide(histPt_REC_rap0to1_3_Pi0_B_Rebin, histPt_ALL_rap0to1_3_Pi0_B_Rebin, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Pi0_B_SmearedP  = (TH1F*) histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin->Clone("histPt_RATIO_rap1_75to3_Pi0_B_SmearedP");
histPt_RATIO_rap1_75to3_Pi0_B_SmearedP->Divide(histPt_REC_rap0to1_3_Pi0_B_SmearedP_Rebin, histPt_ALL_rap0to1_3_Pi0_B_SmearedP_Rebin, 1,1,"B");

//histPt_RATIO_rap1_75to3_Pi0_B->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Pi0_B,25,0.5, kBlack , kBlack);
histPt_RATIO_rap1_75to3_Pi0_B_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Pi0_B_SmearedP,20,0.5, kBlue , kBlue);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap1_75to3_Pi0_B, "pT (GeV/c)", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap1_75to3_Pi0_B_SmearedP->SetAxisRange(0.0,10.0,"X");
histPt_RATIO_rap1_75to3_Pi0_B_SmearedP->GetYaxis()->SetRangeUser(.0000001,0.01);

auto l114 = new TLegend(0.4, 0.2, 0.9, 0.35);
l114->SetHeader("");
l114->SetBorderSize(0);
l114->SetFillStyle(0);
l114->SetTextSize(TextSize);
//l114->AddEntry(histPt_RATIO_rap1_75to3_Pi0_B,"Pi0 efficiency: rapidity: |0-1.3| ","p");
l114->AddEntry(histPt_RATIO_rap1_75to3_Pi0_B_SmearedP,"Pi0 efficiency with smearing: 0<|y|<1.3","p");
l114->Draw("SAME");

TLatex *lt114a = new TLatex(0.2,0.9,"Pi0 Effiiency at Barrel region ");
SetStyleTLatex( lt114a, 0.03,4);
lt114a->Draw("SAME");

TLatex *lt114b = new TLatex(0.7,0.9,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt114b, 0.03,4);
lt114b->Draw("SAME");

c114->SaveAs("./hDiffRap_Pi0_ratio_B.png");

c114->Close();



///////////////  Eta Effiiency at different rapidity PLOT    ///////////////


TCanvas* c115 = new TCanvas("c115","c115",200,10,700,700);  // gives the page size
DrawGammaCanvasSettings( c115, 0.15, 0.02, 0.02, 0.16);
//c115->Divide(2,1);
c115->SetLogy();  

TH2D * histRapPt_ALL_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG");
TH1 * histPt_ALL_rap0to1_3_Eta_B    = histRapPt_ALL_Eta_B->ProjectionY("histPt_ALL_rap0to1_3_Eta_B"); 
TH2D * histRapPt_REC_Eta_B          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec");
TH1 * histPt_REC_rap0to1_3_Eta_B    = histRapPt_REC_Eta_B->ProjectionY("histPt_REC_rap0to1_3_Eta_B"); 

//SMEARED P
TH2D * histRapPt_ALL_Eta_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_SmearedP");
TH1 * histPt_ALL_rap0to1_3_Eta_B_SmearedP    = histRapPt_ALL_Eta_B_SmearedP->ProjectionY("histPt_ALL_rap0to1_3_Eta_B_SmearedP"); 
TH2D * histRapPt_REC_Eta_B_SmearedP          = (TH2D*) fileRec->Get("hRapidityPt_Eta_B_GG_rec_SmearedP");
TH1 * histPt_REC_rap0to1_3_Eta_B_SmearedP    = histRapPt_REC_Eta_B_SmearedP->ProjectionY("histPt_REC_rap0to1_3_Eta_B_SmearedP");

//REBINNING
TH1F* histPt_ALL_rap0to1_3_Eta_B_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Eta_B_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Eta_B_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Eta_B_Rebin",&pt_bin_proj_fine[0]);

TH1F* histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin     = (TH1F*) histPt_ALL_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);
TH1F* histPt_REC_rap0to1_3_Eta_B_SmearedP_Rebin     = (TH1F*) histPt_REC_rap0to1_3_Eta_B->Rebin(nbinspt_proj_fine,"histPt_REC_rap0to1_3_Eta_B_SmearedP_Rebin",&pt_bin_proj_fine[0]);

//SCALING
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Eta_B_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Eta_B_Rebin);
DivideTH1ByBinWidth(histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin);
DivideTH1ByBinWidth(histPt_REC_rap0to1_3_Eta_B_SmearedP_Rebin);

//RATIO
TH1F* histPt_RATIO_rap1_75to3_Eta_B  = (TH1F*) histPt_ALL_rap0to1_3_Eta_B_Rebin->Clone("histPt_RATIO_rap1_75to3_Eta_B");
histPt_RATIO_rap1_75to3_Eta_B->Divide(histPt_REC_rap0to1_3_Eta_B_Rebin, histPt_ALL_rap0to1_3_Eta_B_Rebin, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3_Eta_B_SmearedP  = (TH1F*) histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin->Clone("histPt_RATIO_rap1_75to3_Eta_B_SmearedP");
histPt_RATIO_rap1_75to3_Eta_B_SmearedP->Divide(histPt_REC_rap0to1_3_Eta_B_SmearedP_Rebin, histPt_ALL_rap0to1_3_Eta_B_SmearedP_Rebin, 1,1,"B");

histPt_RATIO_rap1_75to3_Eta_B->Draw("E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Eta_B,25,0.5, kBlack , kBlack);
histPt_RATIO_rap1_75to3_Eta_B_SmearedP->Draw("SAME,E1"); 
DrawGammaSetMarker(histPt_RATIO_rap1_75to3_Eta_B_SmearedP,20,0.5, kBlue , kBlue);

//LABELING
SetStyleHistoTH1ForGraphs(histPt_RATIO_rap1_75to3_Eta_B, "pT", "efficiency", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
histPt_RATIO_rap1_75to3_Eta_B_SmearedP->Draw("SAME,E1"); 

histPt_RATIO_rap1_75to3_Eta_B->GetXaxis()->SetRangeUser(0, 10);
histPt_RATIO_rap1_75to3_Eta_B->GetYaxis()->SetRangeUser(.0000001,0.1);

auto l115 = new TLegend(0.4, 0.2, 0.9, 0.35);
l115->SetHeader("");
l115->SetBorderSize(0);
l115->SetFillStyle(0);
l115->SetTextSize(TextSize);
l115->AddEntry(histPt_RATIO_rap1_75to3_Eta_B,"Eta efficiency: rapidity: |0-1.3| ","p");
l115->AddEntry(histPt_RATIO_rap1_75to3_Eta_B_SmearedP,"Eta efficiency with smearing: 0<|y|<1.3","p");
l115->Draw("SAME");

TLatex *lt115a = new TLatex(0.2,0.9,"Eta Effiiency at Barrel region ");
SetStyleTLatex( lt115a, 0.03,4);
lt115a->Draw("SAME");

TLatex *lt115b = new TLatex(0.7,0.9,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( lt115b, 0.03,4);
lt115b->Draw("SAME");


c115->SaveAs("./hDiffRap_Eta_ratio_B.png");

c115->Close();





}