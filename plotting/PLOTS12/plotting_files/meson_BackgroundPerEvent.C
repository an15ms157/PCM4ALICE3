#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <TROOT.h>
#include <TApplication.h>
#include <TPaveLabel.h>
#include <TSystem.h>
#include <TFrame.h>
#include <TStyle.h>
#include <TString.h>
#include <TLatex.h>
#include <TString.h>

// #include "TGaxis.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TProfile2D.h"
#include "TF1.h"
#include "TVirtualFitter.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TDatabasePDG.h"
#include "TMinuit.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingMeson.h"
#include "TASImage.h"
#include "TMath.h"
#include "TPostScript.h"
#include "TGraphErrors.h"
#include "TArrow.h"
#include "TGraphAsymmErrors.h"
#include "TGaxis.h"
#include "TMarker.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "THnSparse.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionAdditional.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/FittingGammaConversion.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/ConversionFunctions.h"
//#include "/home/abhishek/alice/AnalysisSoftware-master/TaskV1/ExtractSignalV2.h"
#include "./invmass_ptbins_fit.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/ExtractSignalBinning.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/ExtractSignalPlotting.h"

#include "./headers/ALICE3_setup.h"

using namespace std;









void meson_BackgroundPerEvent(){

//SET THIS VARIABLES: 

StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or
gStyle->SetLineWidth(2);
gStyle->SetPadLeftMargin(0.15);
gStyle->SetPadBottomMargin(0.15);
gStyle->SetPadTopMargin(0.05);
gStyle->SetPadRightMargin(0.05);
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


// INPUT SETUP 
bool SWITCH_write_to_file = true;

// INPUT CONDITIONS:
plot_minPt = 0.00;
plot_maxPt = 5.0;
plot_minY = 10e-5;
plot_maxY = 10e4;

TFile * fileRec;
TLatex *l_mesonbackground_b;

// OPTIONS:   pp = 0 || PbPb = 1;   fRap = F or B  fMesonID = 111 or 221

TString fNameHistoTrue_Pi0_B;
TString fNameHistoTrue_Pi0_F;
TString fNameHistoTrue_Eta_B;
TString fNameHistoTrue_Eta_F;

Double_t pt_bin_proj_fine[13]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_fine  = 12;

Float_t fMesonMassExpect_Pi0,fMesonWidthExpect_Pi0;
Float_t fMesonMassExpect_Eta,fMesonWidthExpect_Eta;

Int_t fStartPtBin = 0;
Int_t fColumn     = 5;
Int_t fRow        = 3;
Int_t fNBinsPt    = nbinspt_proj_fine;

Double_t *fBinsPt                               = nullptr;
fBinsPt                                         = new Double_t[fNBinsPt+1];

for (Int_t i = 0; i < fNBinsPt+1; i++) {fBinsPt[i]  = pt_bin_proj_fine[i];}

fMesonMassExpect_Pi0                            = (TDatabasePDG::Instance())->GetParticle(111)->Mass();
fMesonMassExpect_Eta                            = (TDatabasePDG::Instance())->GetParticle(221)->Mass();

fMesonWidthExpect_Pi0 = 0.05;
fMesonWidthExpect_Eta         = 0.05;


switch(collisionSystem){
    
case 0:{
    cout << "pp system"<< endl;
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/output/no_event_rep/ana_pTcut_withft3_check.root");
    fcollisionSystem = "pp";
    ltb_general_Additional_text = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    
    gSystem->Exec("mkdir meson_BackgroundPerEvent");
    gSystem->cd("meson_BackgroundPerEvent");
    gSystem->Exec(Form ("mkdir %s", fcollisionSystem.Data()));
    gSystem->cd(Form ("%s", fcollisionSystem.Data()));

    break;
    }  
    
case 1:{
    cout << "PbPb system"<< endl;
    fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/output/no_event_rep/PbPb/PbPb_100event_perfile/ana_pTcut_withft3_check.root");
    fcollisionSystem = "PbPb";
    ltb_general_Additional_text = new TLatex(0.15,0.8,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
     
    gSystem->Exec("mkdir meson_BackgroundPerEvent");
    gSystem->cd("meson_BackgroundPerEvent");
    gSystem->Exec(Form ("mkdir %s", fcollisionSystem.Data()));
    gSystem->cd(Form ("%s", fcollisionSystem.Data()));

        
    break;
    }
}

TH1D * hNPrimChPiP = (TH1D*) fileRec->Get("hNPrimChPiP");
int NEvents = hNPrimChPiP->GetEntries();

    //      BARREL 

TH1D** fHistoMappingTrueMesonInvMassPtBins_B  = nullptr;
fHistoMappingTrueMesonInvMassPtBins_B         = new TH1D*[nbinspt_proj_fine];

TH1D** fHistoBackgroundInvMassPtBin_B  = nullptr;
fHistoBackgroundInvMassPtBin_B         = new TH1D*[nbinspt_proj_fine];

TH2D * hInvMassPt_GG_rec_SmearedP_All_B     = (TH2D*) fileRec->Get("hInvMassPt_B_GG_rec_SmearedP_All");
TH2D * hInvMassPt_GG_rec_SmearedP_B         = (TH2D*) fileRec->Get("hInvMassPt_B_GG_rec_SmearedP");

for(Int_t iPt=0;iPt<nbinspt_proj_fine;iPt++){ 

    fNameHistoTrue_Pi0_B  = Form("Mapping_TrueMeson_InvMass_in_Pt_Bin_Pi0_B_%02d",iPt);
    fHistoBackgroundInvMassPtBin_B[iPt]   = FillProjectionX(hInvMassPt_GG_rec_SmearedP_All_B, fNameHistoTrue_Pi0_B, fBinsPt[iPt], fBinsPt[iPt+1], 1);

    }


TH1F* BackgroundPerEvent_Pi0_B = new TH1F("BackgroundPerEvent_Pi0_B","BackgroundPerEvent_Pi0_B",nbinspt_proj_fine,pt_bin_proj_fine);
TH1F* BackgroundPerEvent_Eta_B = new TH1F("BackgroundPerEvent_Eta_B","BackgroundPerEvent_Eta_B",nbinspt_proj_fine,pt_bin_proj_fine);

for(Int_t iPt=0;iPt<nbinspt_proj_fine;iPt++){ 
    TAxis *xaxis_InvMass = fHistoBackgroundInvMassPtBin_B[iPt]->GetXaxis();
    double_t integral_background_Pi0_B = fHistoBackgroundInvMassPtBin_B[iPt]->Integral(xaxis_InvMass->FindBin(fMesonMassExpect_Pi0 - fMesonWidthExpect_Pi0), xaxis_InvMass->FindBin(fMesonMassExpect_Pi0 + fMesonWidthExpect_Pi0));
    BackgroundPerEvent_Pi0_B->SetBinContent(iPt+1,integral_background_Pi0_B/NEvents );
    BackgroundPerEvent_Pi0_B->SetBinError(iPt+1, sqrt(integral_background_Pi0_B/NEvents));

    double_t integral_background_Eta_B = fHistoBackgroundInvMassPtBin_B[iPt]->Integral(xaxis_InvMass->FindBin(fMesonMassExpect_Eta - fMesonWidthExpect_Eta), xaxis_InvMass->FindBin(fMesonMassExpect_Eta + fMesonWidthExpect_Eta));
    BackgroundPerEvent_Eta_B->SetBinContent(iPt+1,integral_background_Eta_B/NEvents );
    BackgroundPerEvent_Eta_B->SetBinError(iPt+1, sqrt(integral_background_Eta_B/NEvents));
    
    }






    //      FORWARD 

TH1D** fHistoMappingTrueMesonInvMassPtBins_F  = nullptr;
fHistoMappingTrueMesonInvMassPtBins_F         = new TH1D*[nbinspt_proj_fine];

TH1D** fHistoBackgroundInvMassPtBin_F  = nullptr;
fHistoBackgroundInvMassPtBin_F         = new TH1D*[nbinspt_proj_fine];

TH2D * hInvMassPt_GG_rec_SmearedP_All_F     = (TH2D*) fileRec->Get("hInvMassPt_F_GG_rec_SmearedP_All");
TH2D * hInvMassPt_GG_rec_SmearedP_F         = (TH2D*) fileRec->Get("hInvMassPt_F_GG_rec_SmearedP");

for(Int_t iPt=0;iPt<nbinspt_proj_fine;iPt++){ 

    fNameHistoTrue_Pi0_F  = Form("Mapping_TrueMeson_InvMass_in_Pt_Bin_Pi0_F_%02d",iPt);
    fHistoBackgroundInvMassPtBin_F[iPt]   = FillProjectionX(hInvMassPt_GG_rec_SmearedP_All_F, fNameHistoTrue_Pi0_F, fBinsPt[iPt], fBinsPt[iPt+1], 1);
    }


TH1F* BackgroundPerEvent_Pi0_F = new TH1F("BackgroundPerEvent_Pi0_F","BackgroundPerEvent_Pi0_F",nbinspt_proj_fine,pt_bin_proj_fine);
TH1F* BackgroundPerEvent_Eta_F = new TH1F("BackgroundPerEvent_Eta_F","BackgroundPerEvent_Eta_F",nbinspt_proj_fine,pt_bin_proj_fine);

for(Int_t iPt=0;iPt<nbinspt_proj_fine;iPt++){ 
    TAxis *xaxis_InvMass = fHistoBackgroundInvMassPtBin_F[iPt]->GetXaxis();
    double_t integral_background_Pi0_F = fHistoBackgroundInvMassPtBin_F[iPt]->Integral(xaxis_InvMass->FindBin(fMesonMassExpect_Pi0 - fMesonWidthExpect_Pi0), xaxis_InvMass->FindBin(fMesonMassExpect_Pi0 + fMesonWidthExpect_Pi0));
    BackgroundPerEvent_Pi0_F->SetBinContent(iPt+1,integral_background_Pi0_F/NEvents );
    BackgroundPerEvent_Pi0_F->SetBinError(iPt+1, sqrt(integral_background_Pi0_F/NEvents));

    double_t integral_background_Eta_F = fHistoBackgroundInvMassPtBin_F[iPt]->Integral(xaxis_InvMass->FindBin(fMesonMassExpect_Eta - fMesonWidthExpect_Eta), xaxis_InvMass->FindBin(fMesonMassExpect_Eta + fMesonWidthExpect_Eta));
    BackgroundPerEvent_Eta_F->SetBinContent(iPt+1,integral_background_Eta_F/NEvents );
    BackgroundPerEvent_Eta_F->SetBinError(iPt+1, sqrt(integral_background_Eta_F/NEvents));
    
    }






TCanvas *meson_BackgroundPerEvent = new TCanvas("meson_BackgroundPerEvent","meson_BackgroundPerEvent",600,600); 
DrawGammaCanvasSettings( meson_BackgroundPerEvent, 0.1, 0.05, 0.1, 0.1);

meson_BackgroundPerEvent->SetLogy();

BackgroundPerEvent_Pi0_B->GetXaxis()->SetRangeUser(plot_minPt,plot_maxPt);
BackgroundPerEvent_Pi0_B->GetYaxis()->SetRangeUser(plot_minY,plot_maxY);

SetStyleHistoTH1ForGraphs(BackgroundPerEvent_Pi0_B, p_T.Data(), "#frac{Int. bkg.}{#Event}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title,LabelOffsetX,LabelOffsetY+.1);
DrawGammaSetMarker(BackgroundPerEvent_Pi0_B,marker_B,1.0,  Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(BackgroundPerEvent_Pi0_F,marker_F,1.0,Pi0_marker_color , Pi0_marker_color);
DrawGammaSetMarker(BackgroundPerEvent_Eta_B,marker_B,1.0, Eta_marker_color , Eta_marker_color);
DrawGammaSetMarker(BackgroundPerEvent_Eta_F,marker_F,1.0,Eta_marker_color , Eta_marker_color);

BackgroundPerEvent_Pi0_B->Draw("E1");
BackgroundPerEvent_Pi0_F->Draw("E1 SAME");
BackgroundPerEvent_Eta_B->Draw("E1 SAME");
BackgroundPerEvent_Eta_F->Draw("E1 SAME");

auto l_meson_BackgroundPerEvent = new TLegend(0.6,0.7, 0.8, 0.9);
l_meson_BackgroundPerEvent->SetHeader("");
l_meson_BackgroundPerEvent->SetBorderSize(0);
l_meson_BackgroundPerEvent->SetFillStyle(0);
l_meson_BackgroundPerEvent->SetTextSize(TextSize);
l_meson_BackgroundPerEvent->AddEntry(BackgroundPerEvent_Pi0_B,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_meson_BackgroundPerEvent->AddEntry(BackgroundPerEvent_Pi0_F,Form("%s : %.2f<|y|<%.2f ",LightMeson[0][1].Data(),Rap_F_all1,Rap_F_all2),"p");
l_meson_BackgroundPerEvent->AddEntry(BackgroundPerEvent_Eta_B,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_B_all1,Rap_B_all2),"p");
l_meson_BackgroundPerEvent->AddEntry(BackgroundPerEvent_Eta_F,Form("%s   : %.2f<|y|<%.2f ",LightMeson[1][1].Data(),Rap_F_all1,Rap_F_all2),"p");
l_meson_BackgroundPerEvent->Draw("SAME");


SetStyleTLatex( ltb_general_Additional_text, 0.03,4);
ltb_general_Additional_text->Draw("SAME");

meson_BackgroundPerEvent->SaveAs("./meson_BackgroundPerEvent.png");





if (SWITCH_write_to_file){
const char *outputFile = "./ALICE3_significance_input.root"; // merge output files after analysis was run to keep file size moderate
auto fout = TFile::Open(outputFile, "UPDATE");
//TFile *outputfile = TFile::Open("../../ALICE3_significance_input.root","UPDATE");
fout->cd();
fout->mkdir(Form("%s",fcollisionSystem.Data()));
fout->cd(Form("%s",fcollisionSystem.Data()));

BackgroundPerEvent_Pi0_B->GetXaxis()->SetTitle(p_T.Data());
BackgroundPerEvent_Pi0_B->GetYaxis()->SetTitle("#frac{Integrated background}{#Event}");

BackgroundPerEvent_Pi0_B->Write();
BackgroundPerEvent_Pi0_F->Write();
BackgroundPerEvent_Eta_B->Write();
BackgroundPerEvent_Eta_F->Write();

fout->Close();
}

}













//****************************************************************************
//******************** Projection out of 2D in X *****************************
//****************************************************************************
TH1D* FillProjectionX (TH2* dummy2D, TString name, Double_t minY, Double_t maxY, Int_t rebin){
        cout<< "It breaks after this " <<__LINE__<<endl;

    TH1D* dummy1D           = new TH1D(name.Data(), name.Data(), dummy2D->GetNbinsX(), 0., dummy2D->GetXaxis()->GetBinUpEdge(dummy2D->GetNbinsX()));
    dummy1D->Sumw2();
    Int_t startBin          = dummy2D->GetYaxis()->FindBin(minY+0.001);
    Int_t endBin            = dummy2D->GetYaxis()->FindBin(maxY-0.001);
    dummy2D->ProjectionX(name.Data(),startBin,endBin,"e");
    dummy1D                 = (TH1D*)gDirectory->Get(name.Data());
    if(rebin>1){
        dummy1D->Rebin(rebin);
    }
    return dummy1D;
}
