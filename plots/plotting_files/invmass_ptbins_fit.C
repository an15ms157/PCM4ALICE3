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


using namespace std;



void invmass_ptbins_fit(){
StyleSettings();
SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or




                                                ////////////////FORWARD///////////////

//TFile * fileRec = new TFile("./ana_withft3.root");
TFile * fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/output/latest_output/ana_pTcut_withft3.root");
//TFile * fileRec = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3_check1.root");

double fMaxPt=10.0;
Int_t Font=42;
Double_t TextSize=0.025;
Double_t TextSize_lable=0.03;
Double_t TextSize_title=0.04;
Double_t TextSize_latex=20;
Double_t LabelOffsetLog=-0.015;

//const int nBinsPt=100;

Double_t pt_bin_proj_fine[13]={0.0,0.1,0.2,0.3,0.5,0.7,1.0,1.5,2.0,3.0,5.0,7.0,10.0 };
Int_t nbinspt_proj_fine  = 12;


Int_t fStartPtBin = 1;
Int_t fColumn     = 5;
Int_t fRow        = 3;
Int_t fNBinsPt    = nbinspt_proj_fine;



Double_t *fBinsPt                               = nullptr;
fBinsPt                                         = new Double_t[fNBinsPt+1];

for (Int_t i = 0; i < fNBinsPt+1; i++) {
      fBinsPt[i]  = pt_bin_proj_fine[i];
      }
//Int_t* fNRebin                                  = NULL;



Double_t* fMesonFitRange  = nullptr;
fMesonFitRange            = new Double_t[2];
fMesonFitRange[0]         = 0.1; 
fMesonFitRange[1]         = 0.2; 


fMesonIntDeltaRange         = new Double_t[2];
fMesonIntDeltaRange[0]      = -0.035;
fMesonIntDeltaRange[1]      =  0.015;

fBGFitRange                 = new Double_t[2];
fBGFitRange[0]              = 0.23;
fBGFitRange[1]              = 0.3;

fBGFitRangeLeft             = new Double_t[2];
fBGFitRangeLeft[0]          = 0.05;
fBGFitRangeLeft[1]          = 0.08;


fMesonIntDeltaRangeWide     = new Double_t[2];
fMesonIntDeltaRangeWide[0]      = -0.055;
fMesonIntDeltaRangeWide[1]      = 0.025;


fMesonIntDeltaRangeNarrow   = new Double_t[2];
fMesonIntDeltaRangeNarrow[0]    = -0.015;
fMesonIntDeltaRangeNarrow[1]    = 0.005;

fMesonMassLeft              = new Double_t[fNBinsPt];


fMesonTrueMass              = new Double_t[fNBinsPt];


fMesonMass                  = new Double_t[fNBinsPt];


fMesonFitRange              = new Double_t[2];
fMesonFitRange[0]           = 0.05;
fMesonFitRange[1]           = 0.28;

fMesonId            = 111;

fMesonWidthExpect               = 0.005;
//fMesonWidthRange[0]             = 0.001;


cout<< TDatabasePDG::Instance()->GetParticle(fMesonId)->Mass() <<endl; 


// calculate meson mass from pdg code
cout << "HELLO\n";
fMesonMassExpect                            = (TDatabasePDG::Instance())->GetParticle(fMesonId)->Mass();

Double_t* fMesonMassPlotRange_Alice3    = nullptr;
fMesonMassPlotRange_Alice3              = new Double_t[2];

fMesonMassPlotRange_Alice3[0]   = 0.1; 
fMesonMassPlotRange_Alice3[1]   = 0.2; 
Int_t mode                      = 9;
TString fEnergyFlag             = "5.02TeV";

Double_t* fMesonIntDeltaRange   = nullptr;
fMesonIntDeltaRange             = new Double_t[2];
fMesonIntDeltaRange[0]      = -0.010;
fMesonIntDeltaRange[1]      =  0.010;

//fMesonWidthRange[0]         = 0.001;
//fMesonWidthRange[1]         = 0.009;

TH2D * hInvMassPt_B_SmearedP = (TH2D*) fileRec->Get("hInvMassPt_B_SmearedP");
TH2D * hInvMassPt_B_GG = (TH2D*) fileRec->Get("hInvMassPt_B_GG_SmearedP");
TH2D * hInvMassPt_B_GG_rec_SmearedP = (TH2D*) fileRec->Get("hInvMassPt_B_GG_rec_SmearedP");

TH1D** fHistoMappingSignalInvMassPtBin      = nullptr;
TH1D** fHistoMappingTrueMesonInvMassPtBins  = nullptr;
TF1**  fFitSignalGaussianInvMassPtBin       = nullptr;

fHistoMappingSignalInvMassPtBin      = new TH1D*[nbinspt_proj_fine];
fHistoMappingTrueMesonInvMassPtBins  = new TH1D*[nbinspt_proj_fine];
fFitSignalGaussianInvMassPtBin       = new TF1*[nbinspt_proj_fine];


//TH1D * hInvMassGGB_SmearedP     = (TH1D*) fileRec->Get("hInvMassGGB_SmearedP");
TH1D * hInvMassGGPi0B_SmearedP  = (TH1D*) fileRec->Get("hInvMassGGPi0B_SmearedP");

TF1  *  fFitReco = nullptr;
fFitReco         = new TF1("fGauss","([0]*TMath::Exp(-0.5*((x-[1])/[2])^2))", fMesonFitRange[0], fMesonFitRange[1]);



for(Int_t iPt=0;iPt<nbinspt_proj_fine;iPt++){ 
      fNameHistoTrue  = Form("Mapping_TrueMeson_InvMass_in_Pt_Bin%02d", iPt);

      fHistoMappingSignalInvMassPtBin[iPt]=  FillProjectionX(hInvMassPt_B_SmearedP, fNameHistoTrue, fBinsPt[iPt], fBinsPt[iPt+1], 1);
      fHistoMappingSignalInvMassPtBin[iPt]->SetName(Form("fTrueHistoMappingSignalInvMass_in_Pt_Bin%02d",iPt));

//      CheckForNULLForPointer(fHistoMappingTrueMesonInvMassPtBins[iPt]);
      fHistoMappingTrueMesonInvMassPtBins[iPt]=  FillProjectionX(hInvMassPt_B_GG_rec_SmearedP, fNameHistoTrue, fBinsPt[iPt], fBinsPt[iPt+1], 1);
      cout << "bin: " << iPt << "\t Entries in projection: " << fHistoMappingTrueMesonInvMassPtBins[iPt]->GetEntries() << endl;
      fHistoMappingTrueMesonInvMassPtBins[iPt]->SetLineWidth(1);
      fHistoMappingTrueMesonInvMassPtBins[iPt]->SetLineColor(2);

      fMesonMass[iPt]                 = fMesonMassExpect;

      }

/*
hInvMassGGPi0B_SmearedP->Scale(10);
TF1 *gs_invMass_pi0_B = new TF1("gs_invMass_pi0_B", "gaus", 0.1, 0.2);
gs_invMass_pi0_B->SetParameters(.10, 0.547, 0.01);
hInvMassGGPi0B_SmearedP->Fit(gs_invMass_pi0_B,"RME+");
gs_invMass_pi0_B->SetLineColor(kAzure+2);
gs_invMass_pi0_B->SetLineWidth(2);
*/

TString nameMesonSub                = "MesonSubtractedPureGaussianFit.png";
TString nameCanvasSub               = "MesonCanvasSubtractedPureGaussianFit";
TString namePadSub                  = "MesonPadSubtractedPureGaussianFit";
TString fTextMeasurement            = " #rightarrow #gamma#gamma";
TString fDetectionProcess           = "";
TString     fCollisionSystem        = "";

TString fDate                   = ReturnDateString();
TString fPrefix                 = "PbPb";
TString fDecayChannel           = "#gamma#gamma";
bool fIsMC                           = 1;

//fFitTrueSignalInvMassPtBin[iPt]     = fFitReco;
//fMesonTrueMass[iPt]                 = fFitTrueSignalInvMassPtBin[iPt]->GetParameter(1);


for(Int_t iPt=fStartPtBin;iPt<fNBinsPt;iPt++){ 
      TFitResultPtr lFitResult = nullptr;
      //FitTrueInvMassPureGaussianInPtBins(fHistoMappingTrueMesonInvMassPtBins[iPt],iPt,lFitResult);
     // fFitSignalGaussianInvMassPtBin[iPt] = lFitResult;
      FitSubtractedPureGaussianInvMassInPtBins(fHistoMappingTrueMesonInvMassPtBins[iPt],iPt);
      fFitSignalGaussianInvMassPtBin[iPt] = fFitReco;
}

PlotWithFitSubtractedInvMassInPtBins( fHistoMappingSignalInvMassPtBin, fHistoMappingTrueMesonInvMassPtBins, fFitSignalGaussianInvMassPtBin, nameMesonSub, nameCanvasSub, namePadSub,
                                              fMesonMassPlotRange_Alice3, fDate, fPrefix, fRow, fColumn, fStartPtBin, fNBinsPt, fBinsPt, fTextMeasurement, fIsMC,fDecayChannel, fDetectionProcess,
                                              fCollisionSystem, "MC validated", kFALSE, "fit", "mixed evt. subtr. #it{M}_{#gamma#gamma}", kFALSE , fMesonMass,"performance",kFALSE, NULL);




fHistoBackgroundInvMassPtBin            = new TH1D*[nbinspt_proj_fine];
fHistoSignalInvMassPtBin                = new TH1D*[nbinspt_proj_fine];




TCanvas *c_mesonbackground = new TCanvas("c_mesonbackground"); 
c_mesonbackground->Divide(4,3);

for(Int_t iPt=0;iPt<nbinspt_proj_fine;iPt++){ 

      fHistoSignalInvMassPtBin[iPt]=  FillProjectionX(hInvMassPt_B_GG, fNameHistoTrue, fBinsPt[iPt], fBinsPt[iPt+1], 1);
      fHistoBackgroundInvMassPtBin[iPt]  = FillProjectionX(hInvMassPt_B_SmearedP, fNameHistoTrue, fBinsPt[iPt], fBinsPt[iPt+1], 1);

      c_mesonbackground->cd(iPt+1);
      c_mesonbackground->cd(iPt+1)->SetLogy();
      fHistoBackgroundInvMassPtBin[iPt]->GetXaxis()->SetTitle("M_{#gamma #gamma}(GeV/c)");
      fHistoBackgroundInvMassPtBin[iPt]->GetYaxis()->SetTitle("Counts");
      c_mesonbackground->cd(iPt+1)->SetTitle( Form("%2f < pT < %2f GeV", pt_bin_proj_fine[iPt], pt_bin_proj_fine[iPt+1]));
      fHistoBackgroundInvMassPtBin[iPt]->Add(fHistoSignalInvMassPtBin[iPt],-1);
      fHistoBackgroundInvMassPtBin[iPt]->SetLineColor(1);
      fHistoMappingSignalInvMassPtBin[iPt]->SetLineColor(2);
      //c_mesonbackground->cd(iPt+1)->SetHeading( Form("%2f < pT < %2f GeV", pt_bin_proj_fine[iPt], pt_bin_proj_fine[iPt+1]));
      //lt_mesonbackground->Draw("");
      fHistoBackgroundInvMassPtBin[iPt]->Draw("SAME");
      fHistoSignalInvMassPtBin[iPt]->Draw("SAME");
      fHistoMappingSignalInvMassPtBin[iPt]->Draw("SAME");
    }
    


TH1F* Ratio_signalVSbackground = new TH1F("Ratio_signalVSbackground","Ratio_signalVSbackground",nbinspt_proj_fine,pt_bin_proj_fine);
double_t x[nbinspt_proj_fine], y[nbinspt_proj_fine];

for(Int_t iPt=0;iPt<nbinspt_proj_fine;iPt++){ 
    TAxis *xaxis_InvMass = fHistoBackgroundInvMassPtBin[iPt]->GetXaxis();
    double_t integral_background = fHistoBackgroundInvMassPtBin[iPt]->Integral(xaxis_InvMass->FindBin(0.134977 - 0.01), xaxis_InvMass->FindBin(0.134977 + 0.01));
    double_t integral_signal = fHistoMappingTrueMesonInvMassPtBins[iPt]->Integral(xaxis_InvMass->FindBin(0.134977 - 0.01), xaxis_InvMass->FindBin(0.134977 + 0.01));
    double_t ratio_sig_back = integral_signal/integral_background;
    y[iPt]  = ratio_sig_back;
    x[iPt]  = (pt_bin_proj_fine[iPt]+pt_bin_proj_fine[iPt+1])/2;   
    }

TCanvas *c_meson_signalVSbackground = new TCanvas("c_meson_signalVSbackground"); 
    c_meson_signalVSbackground->SetLogy();
    auto g = new TGraph(nbinspt_proj_fine,x,y);
    g->GetXaxis()->SetTitle("p_T (GeV)");
    g->GetYaxis()->SetTitle("#frac{signal}{background}");
    g->GetYaxis()->SetRangeUser(0.000000001,0.1);
    g->Draw("AC*");




}




























//****************************************************************************
//************* Fit of Signal+ BG with Gaussian ******************
//****************************************************************************
void FitSubtractedPureGaussianInvMassInPtBins(TH1D* histoMappingSignalInvMassPtBinSingle, Int_t ptBin ){
      cout<< "It breaks after this " <<__LINE__<<endl;
    histoMappingSignalInvMassPtBinSingle->GetXaxis()->SetRangeUser(1,.2);
    Double_t mesonAmplitude         = histoMappingSignalInvMassPtBinSingle->GetMaximum();
    Double_t mesonAmplitudeMin      = 0;
    Double_t mesonAmplitudeMax      = 0;
    if (fPrefix.Contains("Pi0")){
                cout<< "It breaks after this " <<__LINE__<<endl;

        mesonAmplitudeMin = mesonAmplitude*98./100.;
        mesonAmplitudeMax = mesonAmplitude*115./100.;
        if (fEnergyFlag.CompareTo("PbPb_2.76TeV") == 0 || fEnergyFlag.Contains("pPb_5.023TeV") ) mesonAmplitudeMin = mesonAmplitude*92./100.;
        if (fMode == 2 || fMode == 13 || fMode == 3) {
            mesonAmplitudeMin = mesonAmplitude*98./100.;
            mesonAmplitudeMax = mesonAmplitude*400./100.;
        }
        if (fMode == 4 || fMode == 12 || fMode == 5 || fMode==14) {
            mesonAmplitudeMin = mesonAmplitude*10./100.;
            mesonAmplitudeMax = mesonAmplitude*400./100.;
            if( fEnergyFlag.BeginsWith("8TeV")  ){
                mesonAmplitudeMin = mesonAmplitude*90./100.;
                mesonAmplitudeMax = mesonAmplitude*400./100.;
                TString trigger = fEventCutSelection(GetEventSelectSpecialTriggerCutPosition(),2);
                if(trigger.CompareTo("52") == 0 && fBinsPt[ptBin]>=13. && fPrefix.CompareTo("Pi0EtaBinning")){
                    fMesonFitRange[0] = 0.08;
                    fMesonFitRange[1] = 0.29;
                }
            } else if (fEnergyFlag.Contains("PbPb")){
                mesonAmplitudeMin = mesonAmplitude*10./100.;
                mesonAmplitudeMax = mesonAmplitude*400./100.;
            }
        }

    } else {
                cout<< "It breaks after this " <<__LINE__<<endl;

        mesonAmplitudeMin = mesonAmplitude*50./100.;
        mesonAmplitudeMax = mesonAmplitude*120./100.;
        if (fMode == 2 || fMode == 13 || fMode == 3){
            mesonAmplitudeMin = mesonAmplitude*10./100.;
            if( fEnergyFlag.BeginsWith("8TeV")  || fEnergyFlag.Contains("pPb_8TeV") ){
              mesonAmplitudeMin = mesonAmplitude*10./100.;
              mesonAmplitudeMax = mesonAmplitude*200./100.;
            }
        }
        if(fMode == 4 || fMode == 12 || fMode==14){
            mesonAmplitudeMin = mesonAmplitude*30./100.;
            mesonAmplitudeMax = mesonAmplitude*220./100.;
        }
    }

    Double_t linBckg = 0.05;
    if(fEnergyFlag.BeginsWith("8TeV") && fPrefix.CompareTo("Eta") == 0) linBckg = 0.1;
    if ( fEnergyFlag.BeginsWith("8TeV") && fPrefix.CompareTo("Pi0") == 0){
        TString trigger         = fEventCutSelection(GetEventSelectSpecialTriggerCutPosition(),2);
        if( trigger.CompareTo("52") == 0 ){
            linBckg = 0.07;
        }
    }
      cout<< "It breaks after this " <<__LINE__<<endl;

    fFitReco= NULL;
    fFitReco = new TF1("GaussBGLinear","gaus(0)",0.1,0.2);
      cout<< "It breaks after this " <<__LINE__<<endl;

    //fFitLinearBck = NULL;
    //fFitLinearBck = new TF1("Linear","[0]+[1]*x",0.2-linBckg,0.2);
      cout<< "It breaks after this " <<__LINE__<<endl;

    fFitReco->SetParameter(0,mesonAmplitude);
    fFitReco->SetParameter(1,fMesonMassExpect);
    fFitReco->SetParameter(2,fMesonWidthExpect);
    fFitReco->SetParLimits(0,mesonAmplitudeMin,mesonAmplitudeMax);
    fFitReco->SetParLimits(1,0.12,0.15);
    fFitReco->SetParLimits(2,0.002,0.02);
      cout<< "It breaks after this " <<__LINE__<<endl;

    if( fEnergyFlag.BeginsWith("8TeV") && fMode == 4 ){
        fFitReco->SetParLimits(1,fMesonMassExpect*0.9,fMesonMassExpect*1.3);
    } else if( fEnergyFlag.Contains("PbPb") && fMode == 4 ){
        fFitReco->SetParLimits(1,fMesonMassExpect*0.9,fMesonMassExpect*1.5);
    }
    fFitReco->SetParLimits(2,0.001,0.009*2);
    histoMappingSignalInvMassPtBinSingle->Fit(fFitReco,"QRME");
    fFitReco->SetLineColor(5);
    fFitReco->SetLineWidth(1);
    fFitReco->SetLineStyle(1);
    fFitReco->SetNpx(10000);
      cout<< "It breaks after this " <<__LINE__<<endl;

    if(TString(gMinuit->fCstatu.Data()).Contains("CONVERGED") == 1 || TString(gMinuit->fCstatu.Data()).Contains("SUCCESSFUL") == 1 || TString(gMinuit->fCstatu.Data()).Contains("PROBLEMS") == 1){
        fFileDataLog << "Parameter for pure Gaussian bin " << ptBin << endl;
        fFileDataLog << "Gausexp: \t" << fFitReco->GetParameter(0) <<"+-" << fFitReco->GetParError(0) << "\t " << fFitReco->GetParameter(1)<<"+-" << fFitReco->GetParError(1) << "\t "<< fFitReco->GetParameter(2) <<"+-" << fFitReco->GetParError(2)<<endl;
    } else {
        fFileErrLog << "Pure Gaussian fitting failed in " << ptBin << " with status " << gMinuit->fCstatu.Data() <<endl << endl;
    }
    cout<< "It breaks after this " <<__LINE__<<endl;

}



//****************************************************************************
//*************** Check if histo already exists if not clear *****************
//****************************************************************************
void CheckForNULLForPointer(TH1D* dummy1){
    if(dummy1!= NULL){
        delete dummy1;
        dummy1           = NULL;
    }
}


//****************************************************************************
//******************** Projection out of 2D in X *****************************
//****************************************************************************
TH1D* FillProjectionX (TH2* dummy2D, TString name, Double_t minY, Double_t maxY, Int_t rebin){
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



//****************************************************************************
//*** Fit of Pure MC Signal with Gaussian ************************************
//****************************************************************************
void FitTrueInvMassPureGaussianInPtBins(TH1D* histoMappingSignalInvMassPtBinSingle, Int_t ptBin, TFitResultPtr& theFitResult ){
    histoMappingSignalInvMassPtBinSingle->GetXaxis()->SetRangeUser(.1,.2);
    Double_t mesonAmplitude         = histoMappingSignalInvMassPtBinSingle->GetMaximum();
    Double_t mesonAmplitudeMin      = 0;
    Double_t mesonAmplitudeMax      = 0;
    if (fPrefix.Contains("Pi0")){
        mesonAmplitudeMin = mesonAmplitude*98./100.;
        mesonAmplitudeMax = mesonAmplitude*115./100.;
        if (fEnergyFlag.CompareTo("PbPb_2.76TeV") == 0 || fEnergyFlag.Contains("pPb_5.023TeV") ) mesonAmplitudeMin = mesonAmplitude*92./100.;
        if (fMode == 2 || fMode == 13 || fMode == 3) {
            mesonAmplitudeMin = mesonAmplitude*98./100.;
            mesonAmplitudeMax = mesonAmplitude*400./100.;
            if( fEnergyFlag.Contains("pPb_8TeV") ){
              mesonAmplitudeMin = mesonAmplitude*85./100.;
              mesonAmplitudeMax = mesonAmplitude*115./100.;
            }
        }
        if (fMode == 4 || fMode == 12 || fMode == 5 || fMode==14) {
            mesonAmplitudeMin = mesonAmplitude*10./100.;
            mesonAmplitudeMax = mesonAmplitude*400./100.;
            if( fEnergyFlag.BeginsWith("8TeV")  ){
              mesonAmplitudeMin = mesonAmplitude*90./100.;
              mesonAmplitudeMax = mesonAmplitude*400./100.;
            }
        }
    } else {
        mesonAmplitudeMin = mesonAmplitude*50./100.;
        mesonAmplitudeMax = mesonAmplitude*120./100.;
        if (fMode == 2 || fMode == 13 || fMode == 3){
            mesonAmplitudeMin = mesonAmplitude*10./100.;
            if( fEnergyFlag.BeginsWith("8TeV")  || fEnergyFlag.Contains("pPb_8TeV") ){
              mesonAmplitudeMin = mesonAmplitude*10./100.;
              mesonAmplitudeMax = mesonAmplitude*200./100.;
            }
        }
    }

    fFitReco= NULL;
    fFitReco = new TF1("GaussLinearBG","gaus(0)",.1-0.05,.2);
    fFitReco->SetParameter(0,mesonAmplitude);
    fFitReco->SetParameter(1,fMesonMassExpect);
    fFitReco->SetParameter(2,fMesonWidthExpect);
    fFitReco->SetParLimits(0,mesonAmplitudeMin,mesonAmplitudeMax);
    fFitReco->SetParLimits(1,fMesonMassExpect*0.8,fMesonMassExpect*1.2);

    if( fEnergyFlag.BeginsWith("8TeV") && fMode == 4 ){
      fFitReco->SetParLimits(1,fMesonMassExpect*0.9,fMesonMassExpect*1.3);
    }
    fFitReco->SetParLimits(2,0.001,0.009);

    theFitResult = histoMappingSignalInvMassPtBinSingle->Fit(fFitReco,"SQRME");
    //exclude second iteration of fitting, otherwise fits go completely wrong in 8 TeV
    fFitReco->SetLineColor(5);
    fFitReco->SetLineWidth(1);
    fFitReco->SetLineStyle(1);

    if(TString(gMinuit->fCstatu.Data()).Contains("CONVERGED") == 1 || TString(gMinuit->fCstatu.Data()).Contains("SUCCESSFUL") == 1 || TString(gMinuit->fCstatu.Data()).Contains("PROBLEMS") == 1){
        fFileDataLog << "Parameter for pure Gaussian bin " << ptBin << endl;
        fFileDataLog << "Gausexp: \t" << fFitReco->GetParameter(0) <<"+-" << fFitReco->GetParError(0) << "\t " << fFitReco->GetParameter(1)<<"+-" << fFitReco->GetParError(1) << "\t "<< fFitReco->GetParameter(2) <<"+-" << fFitReco->GetParError(2)<<endl;
    } else {
        fFileDataLog << "Pure Gaussian fitting failed in " << ptBin << " with status " << gMinuit->fCstatu.Data() <<endl << endl;
    }
    
}

