#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TString.h"

#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingMeson.h"
void massResol(){

//SET THIS VARIABLES: 
Int_t collisionSystem = 0 ;//  pp = 0 || PbPb = 1; 

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

TFile * fileRec;
TLatex *ltl_invMass_pi0_F_b;
TLatex *ltl_invMass_pi0_B_b;
Int_t ScaleFactor_Pi0;
Int_t ScaleFactor_Eta;

switch(collisionSystem){
    case 0:{
    cout << "pp system"<< endl;    
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/output/ana_pTcut_withft3.root");
    ltl_invMass_pi0_F_b = new TLatex(0.2,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    ltl_invMass_pi0_B_b = new TLatex(0.2,0.8,"#splitline{ALICE 3 Study}{pp, #sqrt{#it{s}_{NN}} = 14 TeV}");
    ScaleFactor_Pi0 = 1;
    ScaleFactor_Eta = 10;
    gSystem->Exec("mkdir massResol/pp");
    gSystem->cd("./massResol/pp");

        break;
    }
    case 1:{
    cout << "PbPb system"<< endl;
        //TFile * fileRec = new TFile("./ana_withft3.root");
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3_PbPb.root");
    ltl_invMass_pi0_F_b = new TLatex(0.2,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 14 TeV}");
    ltl_invMass_pi0_B_b = new TLatex(0.2,0.8,"#splitline{ALICE 3 Study}{PbPb, #sqrt{#it{s}_{NN}} = 14 TeV}");
    ScaleFactor_Pi0 = 10;
    ScaleFactor_Eta = 100;
    gSystem->Exec("mkdir massResol/PbPb");
    gSystem->cd("./massResol/PbPb");

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


Double_t pt_bin_proj_fine[13]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_fine  = 12;






///////////////  Pi0 InVmass FIT PLOT    ///////////////

/////  Pi0  Barrel /////

TCanvas c_invMass_pi0("c_invMass_pi0", "c_invMass_pi0", 1600, 1600);
c_invMass_pi0.Divide(2,1);
c_invMass_pi0.cd(1);

TH1D * hInvMassGGB_SmearedP = (TH1D*) fileRec->Get("hInvMassGGB_SmearedP");
TH1D * hInvMassGGPi0B_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0B_SmearedP");
hInvMassGGB_SmearedP->Sumw2();
hInvMassGGPi0B_SmearedP->Sumw2();

SetStyleHistoTH1ForGraphs(hInvMassGGB_SmearedP, "M_{#gamma#gamma} (GeV/c^{2})", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGGB_SmearedP,20,0.8, kBlack , kBlack);
DrawGammaSetMarker(hInvMassGGPi0B_SmearedP,20,0.8, kRed+2 , kRed+2);


hInvMassGGPi0B_SmearedP->Scale(ScaleFactor_Pi0);
TF1 *gs_invMass_pi0_B = new TF1("gs_invMass_pi0_B", "gaus", 0.1, 0.2);
gs_invMass_pi0_B->SetParameters(.10, 0.547, 0.01);
hInvMassGGPi0B_SmearedP->Fit(gs_invMass_pi0_B,"RME+");
gs_invMass_pi0_B->SetLineColor(kAzure+2);
gs_invMass_pi0_B->SetLineWidth(2);


hInvMassGGB_SmearedP->GetXaxis()->SetRangeUser(0.1,0.18); 
hInvMassGGB_SmearedP->SetMinimum(0); 
hInvMassGGB_SmearedP->DrawCopy();
hInvMassGGPi0B_SmearedP->Draw("E1,SAME");
gs_invMass_pi0_B->Draw("SAME");


auto l_invMass_pi0_B = new TLegend(0.5, 0.3, 0.8, 0.5);
l_invMass_pi0_B->SetHeader("#pi^{0} Barrel", "C");
l_invMass_pi0_B->SetBorderSize(0);
l_invMass_pi0_B->SetFillStyle(0);
l_invMass_pi0_B->SetTextSize(TextSize);
l_invMass_pi0_B->AddEntry(hInvMassGGB_SmearedP,"Invariant Mass","l");
l_invMass_pi0_B->AddEntry(hInvMassGGPi0B_SmearedP,"#splitline{Invariant Mass Histogram}{: With Smeared Momentum}","p");
l_invMass_pi0_B->AddEntry(gs_invMass_pi0_B,"Gaussian Fit","l");
l_invMass_pi0_B->Draw("SAME");


TLatex *ltl_invMass_pi0_B_a = new TLatex(0.6,0.7,"#splitline{#mu: 134.9474 MeV/c^{2}}{#sigma: 3.01 MeV/c^{2}} ");
SetStyleTLatex( ltl_invMass_pi0_B_a, 0.025,4);
ltl_invMass_pi0_B_a->Draw("SAME");

SetStyleTLatex( ltl_invMass_pi0_B_b, 0.025,4);
ltl_invMass_pi0_B_b->Draw("SAME");


/////  Pi0  Forward /////

c_invMass_pi0.cd(2);

TH1D * hInvMassGGF_SmearedP = (TH1D*) fileRec->Get("hInvMassGGF_SmearedP");
TH1D * hInvMassGGPi0F_SmearedP = (TH1D*) fileRec->Get("hInvMassGGPi0F_SmearedP");

hInvMassGGF_SmearedP->Sumw2();
hInvMassGGPi0F_SmearedP->Sumw2();

SetStyleHistoTH1ForGraphs(hInvMassGGF_SmearedP, "M_{#gamma#gamma} (GeV/c^{2})", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGGF_SmearedP,20,0.8, kBlack , kBlack);
DrawGammaSetMarker(hInvMassGGPi0F_SmearedP,20,0.8, kRed+2 , kRed+2);

hInvMassGGPi0F_SmearedP->Scale(ScaleFactor_Pi0);
TF1 *gs_invMass_pi0_F = new TF1("gs_invMass_pi0_F", "gaus", 0.1, 0.2);
gs_invMass_pi0_F->SetParameters(.10, 0.547, 0.01);
hInvMassGGPi0F_SmearedP->Fit(gs_invMass_pi0_F,"RME+");
gs_invMass_pi0_F->SetLineColor(kAzure+2);
gs_invMass_pi0_F->SetLineWidth(2);


hInvMassGGF_SmearedP->GetXaxis()->SetRangeUser(0.1,0.18); 
hInvMassGGF_SmearedP->SetMinimum(0); 
hInvMassGGF_SmearedP->DrawCopy();
hInvMassGGPi0F_SmearedP->Draw("E1,SAME");
gs_invMass_pi0_F->Draw("SAME");


auto l_invMass_pi0_F = new TLegend(0.5, 0.3, 0.8, 0.5);
l_invMass_pi0_F->SetHeader("#pi^{0} Forward", "C");
l_invMass_pi0_F->SetBorderSize(0);
l_invMass_pi0_F->SetFillStyle(0);
l_invMass_pi0_F->SetTextSize(TextSize);
l_invMass_pi0_F->AddEntry(hInvMassGGF_SmearedP,"Invariant Mass","l");
l_invMass_pi0_F->AddEntry(hInvMassGGPi0F_SmearedP,"#splitline{Invariant Mass Histogram}{: With Smeared Momentum}","p");
l_invMass_pi0_F->AddEntry(gs_invMass_pi0_F,"Gaussian Fit","l");
l_invMass_pi0_F->Draw("SAME");

TLatex *ltl_invMass_pi0_F_a = new TLatex(0.6,0.7,"#splitline{#mu: 134.926e MeV/c^{2}}{#sigma: 3.90737 MeV/c^{2}} ");
SetStyleTLatex( ltl_invMass_pi0_F_a, 0.025,4);
ltl_invMass_pi0_F_a->Draw("SAME");

SetStyleTLatex( ltl_invMass_pi0_F_b, 0.025,4);
ltl_invMass_pi0_F_b->Draw("SAME");



c_invMass_pi0.SaveAs("./hInvMassGG_Pi0_FIT.png");





///////////////  Eta InVmass FIT PLOT    ///////////////

/////  Eta  Barrel /////

TCanvas c_invMass_Eta("c_invMass_Eta", "c_invMass_Eta", 1600, 1600);
c_invMass_Eta.Divide(2,1);
c_invMass_Eta.cd(1);

TH1D * hInvMassGGEtaB_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaB_SmearedP");
hInvMassGGEtaB_SmearedP->Sumw2();

SetStyleHistoTH1ForGraphs(hInvMassGGB_SmearedP, "M_{#gamma#gamma} (GeV/c^{2})", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGGB_SmearedP,20,0.8, kBlack , kBlack);
DrawGammaSetMarker(hInvMassGGEtaB_SmearedP,20,0.8, kRed+2 , kRed+2);

hInvMassGGEtaB_SmearedP->Scale(ScaleFactor_Eta);

TF1 *gs_invMass_Eta_B = new TF1("gs_invMass_Eta_B", "gaus", 0.45, 0.65);
gs_invMass_Eta_B->SetParameters(.10, 0.547, 0.01);
hInvMassGGEtaB_SmearedP->Fit(gs_invMass_Eta_B,"RME+");
gs_invMass_Eta_B->SetLineColor(kAzure+2);
gs_invMass_Eta_B->SetLineWidth(2);


hInvMassGGB_SmearedP->GetXaxis()->SetRangeUser(0.45,0.65); 
hInvMassGGB_SmearedP->SetMinimum(0); 
hInvMassGGB_SmearedP->DrawCopy();
hInvMassGGEtaB_SmearedP->Draw("E1,SAME");
gs_invMass_Eta_B->Draw("SAME");


auto l_invMass_Eta_B = new TLegend(0.5, 0.3, 0.8, 0.5);
l_invMass_Eta_B->SetHeader("#eta Barrel", "C");
l_invMass_Eta_B->SetBorderSize(0);
l_invMass_Eta_B->SetFillStyle(0);
l_invMass_Eta_B->SetTextSize(TextSize);
l_invMass_Eta_B->AddEntry(hInvMassGGB_SmearedP,"Invariant Mass","l");
l_invMass_Eta_B->AddEntry(hInvMassGGEtaB_SmearedP,"#splitline{Invariant Mass Histogram}{: With Smeared Momentum}","p");
l_invMass_Eta_B->AddEntry(gs_invMass_Eta_B,"Gaussian Fit","l");
l_invMass_Eta_B->Draw("SAME");

TLatex *ltl_invMass_Eta_B_a = new TLatex(0.15,0.6,"#splitline{#mu: 547.719 MeV/c^{2}}{#sigma: 12.2268 MeV/c^{2}} ");
SetStyleTLatex( ltl_invMass_Eta_B_a, 0.025,4);
ltl_invMass_Eta_B_a->Draw("SAME");

TLatex *ltl_invMass_Eta_B_b = new TLatex(0.6,0.83,"#splitline{ALICE 3 Study}{PbPb, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( ltl_invMass_Eta_B_b, 0.025,4);
ltl_invMass_Eta_B_b->Draw("SAME");


/////  Eta  Forward /////

c_invMass_Eta.cd(2);

TH1D * hInvMassGGEtaF_SmearedP = (TH1D*) fileRec->Get("hInvMassGGEtaF_SmearedP");
hInvMassGGEtaF_SmearedP->Sumw2();

SetStyleHistoTH1ForGraphs(hInvMassGGF_SmearedP, "M_{#gamma#gamma} (GeV/c^{2})", "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hInvMassGGF_SmearedP,20,0.8, kBlack , kBlack);
DrawGammaSetMarker(hInvMassGGEtaF_SmearedP,20,0.8, kRed+2 , kRed+2);

hInvMassGGEtaF_SmearedP->Scale(ScaleFactor_Eta);

TF1 *gs_invMass_Eta_F = new TF1("gs_invMass_Eta_F", "gaus", 0.45, 0.65);
gs_invMass_Eta_F->SetParameters(.10, 0.547, 0.01);
hInvMassGGEtaF_SmearedP->Fit(gs_invMass_Eta_F,"RME+");
gs_invMass_Eta_F->SetLineColor(kAzure+2);
gs_invMass_Eta_F->SetLineWidth(2);


hInvMassGGF_SmearedP->GetXaxis()->SetRangeUser(0.45,0.65); 
hInvMassGGF_SmearedP->SetMinimum(0); 
hInvMassGGF_SmearedP->DrawCopy();
hInvMassGGEtaF_SmearedP->Draw("E1,SAME");
gs_invMass_Eta_F->Draw("SAME");


auto l_invMass_Eta_F = new TLegend(0.5, 0.3, 0.8, 0.5);
l_invMass_Eta_F->SetHeader("#eta Forward", "C");
l_invMass_Eta_F->SetBorderSize(0);
l_invMass_Eta_F->SetFillStyle(0);
l_invMass_Eta_F->SetTextSize(TextSize);
l_invMass_Eta_F->AddEntry(hInvMassGGF_SmearedP,"Invariant Mass","l");
l_invMass_Eta_F->AddEntry(hInvMassGGEtaF_SmearedP,"#splitline{Invariant Mass Histogram}{: With Smeared Momentum}","p");
l_invMass_Eta_F->AddEntry(gs_invMass_Eta_F,"Gaussian Fit","l");
l_invMass_Eta_F->Draw("SAME");

TLatex *ltl_invMass_Eta_F_a = new TLatex(0.15,0.6,"#splitline{#mu: 547.64 MeV/c^{2}}{#sigma: 15.78 MeV/c^{2}} ");
SetStyleTLatex( ltl_invMass_Eta_F_a, 0.025,4);
ltl_invMass_Eta_F_a->Draw("SAME");

TLatex *ltl_invMass_Eta_F_b = new TLatex(0.6,0.83,"#splitline{ALICE 3 Study}{PbPb, #sqrt{#it{s}_{NN}} = 14 TeV}");
SetStyleTLatex( ltl_invMass_Eta_F_b, 0.025,4);
ltl_invMass_Eta_F_b->Draw("SAME");



c_invMass_Eta.SaveAs("./hInvMassGG_Eta_FIT.png");



}