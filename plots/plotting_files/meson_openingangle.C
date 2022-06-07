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
void meson_openingangle(){

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
TLatex *ltl_OpAngle_F;
TLatex *ltl_OpAngle_B;
Int_t ScaleFactor_Pi0;
Int_t ScaleFactor_Eta;

switch(collisionSystem){
    case 0:{
    cout << "pp system"<< endl;    
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3_check.root");
    ltl_OpAngle_F = new TLatex(0.2,0.8,"momentum and rapidity distribution in Forward}");
    ltl_OpAngle_B = new TLatex(0.2,0.8,"momentum and rapidity distribution in Barrel");
    ScaleFactor_Pi0 = 1;
    ScaleFactor_Eta = 10;
    gSystem->Exec("mkdir meson_openingangle/pp");
    gSystem->cd("./meson_openingangle/pp");

        break;
    }
    case 1:{
    cout << "PbPb system"<< endl;
        //TFile * fileRec = new TFile("./ana_withft3.root");
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3_PbPb.root");
    ltl_OpAngle_F = new TLatex(0.2,0.8,"momentum and rapidity distribution in Forward}");
    ltl_OpAngle_B = new TLatex(0.2,0.8,"momentum and rapidity distribution in Barrel");
    ScaleFactor_Pi0 = 10;
    ScaleFactor_Eta = 100;
    gSystem->Exec("mkdir meson_openingangle/PbPb");
    gSystem->cd("./meson_openingangle/PbPb");

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




///////////////  Pi0 Opening angle PLOTS    ///////////////

TH2D * hOpeningangle_PT_Pi0_F_DaughterPhotons        = (TH2D*) fileRec->Get("hOpeningangle_PT_Pi0_F_DaughterPhotons");
TH2D * hOpeningangle_P_Pi0_B_DaughterPhotons         = (TH2D*) fileRec->Get("hOpeningangle_P_Pi0_B_DaughterPhotons");

TCanvas c_openingangle_Pi0("c_openingangle_Pi0", "c_openingangle_Pi0", 1600, 1600);
c_openingangle_Pi0.Divide(2,2);

TH2D* Mom_OpAngle_F_Pi0   = (TH2D*) hOpeningangle_PT_Pi0_F_DaughterPhotons->Clone("PT vs Photon Opening angle  distribution for Forward");
TH2D* Mom_OpAngle_B_Pi0   = (TH2D*) hOpeningangle_P_Pi0_B_DaughterPhotons->Clone("P vs Photon Opening angle  distribution for Barrel");


Mom_OpAngle_F_Pi0->GetXaxis()->SetTitle("pT (GeV/c)");
Mom_OpAngle_F_Pi0->GetYaxis()->SetTitle("Opening Angle (rad)");
Mom_OpAngle_F_Pi0->GetXaxis()->SetRangeUser(0., 5.);
Mom_OpAngle_F_Pi0->GetYaxis()->SetRangeUser(0., 4.);

Mom_OpAngle_B_Pi0->GetXaxis()->SetTitle("p (GeV/c)");
Mom_OpAngle_B_Pi0->GetYaxis()->SetTitle("Opening Angle (rad)");
Mom_OpAngle_B_Pi0->GetXaxis()->SetRangeUser(0., 5.);
Mom_OpAngle_B_Pi0->GetYaxis()->SetRangeUser(0., 4.);

c_openingangle_Pi0.cd(1);
Mom_OpAngle_F_Pi0->Draw("colz");

c_openingangle_Pi0.cd(2);
Mom_OpAngle_B_Pi0->Draw("colz");


TH2D * hRapidityOpeningangle_Pi0_F_DaughterPhotons        = (TH2D*) fileRec->Get("hRapidityOpeningangle_Pi0_F_DaughterPhotons");
TH2D * hRapidityOpeningangle_Pi0_B_DaughterPhotons        = (TH2D*) fileRec->Get("hRapidityOpeningangle_Pi0_B_DaughterPhotons");


TH2D* Rap_OpAngle_F_Pi0   = (TH2D*) hRapidityOpeningangle_Pi0_F_DaughterPhotons->Clone("Rapidity vs Photon Opening angle  distribution for Forward");
TH2D* Rap_OpAngle_B_Pi0   = (TH2D*) hRapidityOpeningangle_Pi0_B_DaughterPhotons->Clone("Rapidity vs Photon Opening angle  distribution for Barrel");


Rap_OpAngle_F_Pi0->GetXaxis()->SetTitle("Rapidity");
Rap_OpAngle_F_Pi0->GetYaxis()->SetTitle("Opening Angle (rad)");
Rap_OpAngle_F_Pi0->GetXaxis()->SetRangeUser(-5., 5.);
Rap_OpAngle_F_Pi0->GetYaxis()->SetRangeUser(0., 4.);

Rap_OpAngle_B_Pi0->GetXaxis()->SetTitle("Rapidity");
Rap_OpAngle_B_Pi0->GetYaxis()->SetTitle("Opening Angle (rad)");
Rap_OpAngle_B_Pi0->GetXaxis()->SetRangeUser(-5., 5.);
Rap_OpAngle_B_Pi0->GetYaxis()->SetRangeUser(0., 4.);

c_openingangle_Pi0.cd(3);
Rap_OpAngle_F_Pi0->Draw("colz");

c_openingangle_Pi0.cd(4);
Rap_OpAngle_B_Pi0->Draw("colz");

SetStyleTLatex( ltl_OpAngle_F, 0.03,4);
ltl_OpAngle_F->Draw("SAME");

SetStyleTLatex( ltl_OpAngle_B, 0.03,4);
ltl_OpAngle_B->Draw("SAME");

c_openingangle_Pi0.SaveAs("./hOpeningAngle_Pi0.png");





///////////////  Eta Opening angle PLOTS    ///////////////

TH2D * hOpeningangle_PT_Eta_F_DaughterPhotons        = (TH2D*) fileRec->Get("hOpeningangle_PT_Eta_F_DaughterPhotons");
TH2D * hOpeningangle_P_Eta_B_DaughterPhotons         = (TH2D*) fileRec->Get("hOpeningangle_P_Eta_B_DaughterPhotons");

TCanvas c_openingangle_Eta("c_openingangle_Eta", "c_openingangle_Eta", 1600, 1600);
c_openingangle_Eta.Divide(2,2);

TH2D* Mom_OpAngle_F_Eta   = (TH2D*) hOpeningangle_PT_Eta_F_DaughterPhotons->Clone("PT vs Photon Opening angle  distribution for Forward");
TH2D* Mom_OpAngle_B_Eta   = (TH2D*) hOpeningangle_P_Eta_B_DaughterPhotons->Clone("P vs Photon Opening angle  distribution for Barrel");


Mom_OpAngle_F_Eta->GetXaxis()->SetTitle("pT (GeV/c)");
Mom_OpAngle_F_Eta->GetYaxis()->SetTitle("Opening Angle (rad)");
Mom_OpAngle_F_Eta->GetXaxis()->SetRangeUser(0., 5.);
Mom_OpAngle_F_Eta->GetYaxis()->SetRangeUser(0., 4.);

Mom_OpAngle_B_Eta->GetXaxis()->SetTitle("p (GeV/c)");
Mom_OpAngle_B_Eta->GetYaxis()->SetTitle("Opening Angle (rad)");
Mom_OpAngle_B_Eta->GetXaxis()->SetRangeUser(0., 5.);
Mom_OpAngle_B_Eta->GetYaxis()->SetRangeUser(0., 4.);

c_openingangle_Eta.cd(1);
Mom_OpAngle_F_Eta->Draw("colz");

c_openingangle_Eta.cd(2);
Mom_OpAngle_B_Eta->Draw("colz");


TH2D * hRapidityOpeningangle_Eta_F_DaughterPhotons        = (TH2D*) fileRec->Get("hRapidityOpeningangle_Eta_F_DaughterPhotons");
TH2D * hRapidityOpeningangle_Eta_B_DaughterPhotons        = (TH2D*) fileRec->Get("hRapidityOpeningangle_Eta_B_DaughterPhotons");


TH2D* Rap_OpAngle_F_Eta   = (TH2D*) hRapidityOpeningangle_Eta_F_DaughterPhotons->Clone("Rapidity vs Photon Opening angle  distribution for Forward");
TH2D* Rap_OpAngle_B_Eta   = (TH2D*) hRapidityOpeningangle_Eta_B_DaughterPhotons->Clone("Rapidity vs Photon Opening angle  distribution for Barrel");


Rap_OpAngle_F_Eta->GetXaxis()->SetTitle("Rapidity");
Rap_OpAngle_F_Eta->GetYaxis()->SetTitle("Opening Angle (rad)");
Rap_OpAngle_F_Eta->GetXaxis()->SetRangeUser(-5., 5.);
Rap_OpAngle_F_Eta->GetYaxis()->SetRangeUser(0., 4.);

Rap_OpAngle_B_Eta->GetXaxis()->SetTitle("Rapidity");
Rap_OpAngle_B_Eta->GetYaxis()->SetTitle("Opening Angle (rad)");
Rap_OpAngle_B_Eta->GetXaxis()->SetRangeUser(-5., 5.);
Rap_OpAngle_B_Eta->GetYaxis()->SetRangeUser(0., 4.);

c_openingangle_Eta.cd(3);
Rap_OpAngle_F_Eta->Draw("colz");

c_openingangle_Eta.cd(4);
Rap_OpAngle_B_Eta->Draw("colz");

SetStyleTLatex( ltl_OpAngle_F, 0.03,4);
ltl_OpAngle_F->Draw("SAME");

SetStyleTLatex( ltl_OpAngle_B, 0.03,4);
ltl_OpAngle_B->Draw("SAME");

c_openingangle_Eta.SaveAs("./hOpeningAngle_Eta.png");


}