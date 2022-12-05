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
#include "./headers/ALICE3_setup.h"


void meson_openingangle(){

StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or
gStyle->SetLineWidth(2);
gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadBottomMargin(0.15);
gStyle->SetPadTopMargin(0.05);
gStyle->SetPadRightMargin(0.1);
gStyle->SetTitleSize(0.06);
gStyle->SetTitleSize(0.06,"Y");
gStyle->SetTitleOffset(1,"Y");
gStyle->SetTitleOffset(1,"X");
gStyle->SetLabelSize(0.04);
gStyle->SetLabelSize(0.04,"Y");
gStyle->SetFrameLineWidth(2);
gStyle->SetNdivisions(505,"X");
gStyle->SetNdivisions(505,"Y");
gStyle->SetPadTickX(1);
gStyle->SetPadTickY(1);

//   TO MOVE STATBOX
//gStyle->SetStatX(.44);
//gStyle->SetStatY(.83);

//SET THESE VARIABLES: 

    // INPUT SETUP 

bool SWITCH_write_to_file = TRUE ;

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/no_event_rep/PbPb/PbPb_100event_perfile/ana_pTcut_withft3_check.root";
gSystem->Exec("mkdir ./meson_openingangle");
gSystem->cd("./meson_openingangle");


switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.6,0.85,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
    case 1:{

    fcollisionSystem = "PbPb";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.6,0.85,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
}

    // INPUT CONDITIONS:
plot_minPt = 0.01;
plot_maxPt = 5.0;
plot_minY = 0.01;
plot_maxY = 100000.0;


///////////////  Pi0 Opening angle PLOTS    ///////////////

TH2D * hOpeningangle_P_Pi0_B_DaughterPhotons         = (TH2D*) fileRec->Get("hOpeningangle_P_Pi0_B_DaughterPhotons");
TH2D * hOpeningangle_PT_Pi0_F_DaughterPhotons        = (TH2D*) fileRec->Get("hOpeningangle_PT_Pi0_F_DaughterPhotons");

TCanvas c_openingangle_Pi0("c_openingangle_Pi0", "c_openingangle_Pi0", 2500, 2500);
c_openingangle_Pi0.Divide(2,2);

TH2D* Mom_OpAngle_B_Pi0   = (TH2D*) hOpeningangle_P_Pi0_B_DaughterPhotons->Clone("P vs Photon Opening angle  distribution for Barrel");
TH2D* Mom_OpAngle_F_Pi0   = (TH2D*) hOpeningangle_PT_Pi0_F_DaughterPhotons->Clone("PT vs Photon Opening angle  distribution for Forward");

SetStyleTLatex( ltb_general_Additional_text, 0.03,4);

Mom_OpAngle_F_Pi0->GetXaxis()->SetTitle(p_T.Data());
Mom_OpAngle_F_Pi0->GetYaxis()->SetTitle("Opening Angle (rad)");
Mom_OpAngle_F_Pi0->GetXaxis()->SetRangeUser(0., 5.);
Mom_OpAngle_F_Pi0->GetYaxis()->SetRangeUser(0., 4.);

Mom_OpAngle_B_Pi0->GetXaxis()->SetTitle(momentum.Data());
Mom_OpAngle_B_Pi0->GetYaxis()->SetTitle("Opening Angle (rad)");
Mom_OpAngle_B_Pi0->GetXaxis()->SetRangeUser(0., 5.);
Mom_OpAngle_B_Pi0->GetYaxis()->SetRangeUser(0., 4.);

c_openingangle_Pi0.cd(1);
Mom_OpAngle_F_Pi0->Draw("colz");
ltb_general_Additional_text->Draw("SAME");

c_openingangle_Pi0.cd(2);
Mom_OpAngle_B_Pi0->Draw("colz");
ltb_general_Additional_text->Draw("SAME");


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
ltb_general_Additional_text->Draw("SAME");

c_openingangle_Pi0.cd(4);
Rap_OpAngle_B_Pi0->Draw("colz");
ltb_general_Additional_text->Draw("SAME");

//SetStyleTLatex( ltl_OpAngle_B, 0.03,4);
//ltl_OpAngle_B->Draw("SAME");

c_openingangle_Pi0.SaveAs("./meson_openingangle_Pi0.png");





///////////////  Eta Opening angle PLOTS    ///////////////

TH2D * hOpeningangle_PT_Eta_F_DaughterPhotons        = (TH2D*) fileRec->Get("hOpeningangle_PT_Eta_F_DaughterPhotons");
TH2D * hOpeningangle_P_Eta_B_DaughterPhotons         = (TH2D*) fileRec->Get("hOpeningangle_P_Eta_B_DaughterPhotons");

TCanvas c_openingangle_Eta("c_openingangle_Eta", "c_openingangle_Eta", 2500, 2500);
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
ltb_general_Additional_text->Draw("SAME");

c_openingangle_Eta.cd(2);
Mom_OpAngle_B_Eta->Draw("colz");
ltb_general_Additional_text->Draw("SAME");


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
ltb_general_Additional_text->Draw("SAME");

c_openingangle_Eta.cd(4);
Rap_OpAngle_B_Eta->Draw("colz");
ltb_general_Additional_text->Draw("SAME");

c_openingangle_Eta.SaveAs("./meson_openingangle_Eta.png");


}