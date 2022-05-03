#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"

#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"


void calculateConvProbForward()
{
  /*
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(kFALSE);
  gStyle->SetOptStat(0);
  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(kFALSE);
  gStyle->SetOptStat(0);
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  StyleSettingsThesis();
  SetPlotStyle();
  */
  StyleSettings();
  SetPlotStyle();
gStyle->SetOptTitle(0); //this will disable the title for all coming histograms or

//  TFile * fileMCTruthF = new TFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/anaConv/ana_211229_withft3.root");


  TFile * fileMCTruthF = new TFile("/home/abhishek/PhD/Work/work_A/photons/PCM4ALICE3/ana_pTcut_withft3.root");
  TH1D * histPrimPhotonPtF = (TH1D*)fileMCTruthF->Get("hPrimPhotonPF");
  TH1D * histConvPrimPhotonPtF = (TH1D*)fileMCTruthF->Get("hPhotonPF");
  TH1D * histNPhotonConv = (TH1D*) fileMCTruthF->Get("hNPhotonConv");

  Float_t nEv = histNPhotonConv->GetEntries();
  
  const int nBinsPt=116;
  double arrayPtBins[nBinsPt+1];
  double fMaxPt=100.;

  for(int i=0; i<nBinsPt+1;i++){
    if (i < 50) arrayPtBins[i]              = 0.02*i;
    else if(i<60) arrayPtBins[i]           = 1.+ 0.2*(i-50);
    else if(i<70) arrayPtBins[i]          = 3. + 0.5*(i-60);
    else if(i<116) arrayPtBins[i]          = 8.+ 2.0*(i-70);
    else arrayPtBins[i]                    = fMaxPt;
       
    //   cout<< i<< " "<<  arrayPtBins[i]<< endl;
  }

  TH1D* histPrimPhotonPtFRebin = (TH1D*) histPrimPhotonPtF->Rebin(nBinsPt,"histPrimPhotonPtFRebin",arrayPtBins);
  TH1D* histConvPrimPhotonPtFRebin = (TH1D*) histConvPrimPhotonPtF->Rebin(nBinsPt,"histConvPrimPhotonPtFRebin",arrayPtBins);

  histPrimPhotonPtFRebin->Sumw2();
  histConvPrimPhotonPtFRebin->Sumw2();
  
  histPrimPhotonPtFRebin->Scale(1./nEv);
  histConvPrimPhotonPtFRebin->Scale(1./nEv);

  
  for (Int_t i = 1; i < histPrimPhotonPtFRebin->GetNbinsX()+1; i++){
    histPrimPhotonPtFRebin->SetBinContent(i,histPrimPhotonPtFRebin->GetBinContent(i)/histPrimPhotonPtFRebin->GetXaxis()->GetBinWidth(i));
    histPrimPhotonPtFRebin->SetBinError(i,histPrimPhotonPtFRebin->GetBinError(i)/histPrimPhotonPtFRebin->GetXaxis()->GetBinWidth(i));
    
    histConvPrimPhotonPtFRebin->SetBinContent(i,histConvPrimPhotonPtFRebin->GetBinContent(i)/histConvPrimPhotonPtFRebin->GetXaxis()->GetBinWidth(i));
    histConvPrimPhotonPtFRebin->SetBinError(i,histConvPrimPhotonPtFRebin->GetBinError(i)/histConvPrimPhotonPtFRebin->GetXaxis()->GetBinWidth(i));
  }  
  
  TCanvas * canvasPhotonPtF = new TCanvas("canvasPhotonPtF","",200,10,800,600);  // gives the page size
    
  canvasPhotonPtF->SetLogx();
  canvasPhotonPtF->SetLogy();

  TH2F * histo2DF;
  histo2DF = new TH2F("histo2DF","histo2DF",1000,0.02,100.,1000,5.e-8,50.5e1    );
  histo2DF ->GetYaxis()->SetTitle("N_{#gamma}/N_{ev}");
  histo2DF ->GetXaxis()->SetTitle("p_{T}(GeV/c)");
  histo2DF ->DrawCopy();
  histPrimPhotonPtFRebin->SetMarkerStyle(21);
  histConvPrimPhotonPtFRebin->SetMarkerStyle(25);
  
  histPrimPhotonPtFRebin->SetMarkerColor(4);
  histConvPrimPhotonPtFRebin->SetMarkerColor(4);

  histPrimPhotonPtFRebin->DrawCopy("same");
  histConvPrimPhotonPtFRebin->DrawCopy("same");

  TLegend  * legendPhotonsF = new TLegend(0.7,0.7,0.9,0.9);
  legendPhotonsF->AddEntry(histPrimPhotonPtFRebin,"#gamma 1.75< #eta <4","p");
  legendPhotonsF->AddEntry(histConvPrimPhotonPtFRebin,"Converted #gamma 1.75< #eta <4","p");

  legendPhotonsF->Draw();
  canvasPhotonPtF->Print("PhotonPrimConvF.pdf");
  canvasPhotonPtF->Print("PhotonPrimConvF.png");

  
  TH1D * convProbF = (TH1D*)histConvPrimPhotonPtFRebin->Clone("convProbF");
  convProbF ->Sumw2();
  convProbF->Divide(histConvPrimPhotonPtFRebin,histPrimPhotonPtFRebin,1,1,"B");

  TCanvas * canvasPhotonConvProbPtF = new TCanvas("canvasPhotonConvProbPtF","",200,10,800,600);
  canvasPhotonConvProbPtF->SetLogx();
  //  canvasPhotonConvProbPtF->SetLogy();


  TH2F * histo2DFa;
  histo2DFa= new TH2F("histo2DFa","histo2DFa",1000,0.051,100.,1000,0.,0.1 );
  histo2DFa ->GetYaxis()->SetTitle("Conv. Prob.");
  histo2DFa ->GetXaxis()->SetTitle("p(GeV/c)");
  histo2DFa ->GetYaxis()->SetMaxDigits(4);
  histo2DFa ->GetYaxis()->SetTitleOffset(1.2);
  histo2DFa ->GetXaxis()->SetTitleOffset(1.1);


  //  TF1 * fitConvProbF = new TF1("fitConvProbF","(x<[4])*([0] * TMath::Power(x,[2])/([1]+TMath::Power(x,[3])))+(x>=[4])*(0.0898)", 0.02,10.);
   TF1 * fitConvProbF = new TF1("fitConvProbF","([0] * (TMath::Power(x,[2])-[4]*x)/([1]+TMath::Power(x,[3])))", 0.2,100.);
  //fitConvProb->SetParameters(0.035,0.05,2.5,2.5,9.);

    fitConvProbF->SetParameters(0.035,0.05,2.5,2.5,1.5);
    //  fitConvProbF->SetParameters(0.035,0.05,2.5,2.5);
   convProbF->Fit("fitConvProbF","RME0");
   convProbF->Fit("fitConvProbF","RME0");
  histo2DFa ->DrawCopy();
  convProbF->GetYaxis()->SetTitle("Conv. Prob.");
  convProbF->DrawCopy("same");
  // When checking the conv Prob in forward direction, using p, it has a decrease at high p
  
   // 1  p0          -8.24825e-03   2.50048e-04   1.06765e-04   1.20940e+05
   // 2  p1           2.23495e-01   5.61954e-03   1.91319e-03   1.63366e+02
   // 3  p2          -5.03182e-01   1.92418e-02  -8.08812e-03   2.24357e+02
   // 4  p3           1.08338e+00   1.33947e-03   1.87792e-04   1.53831e+03
   // 5  p4           1.13113e+01   3.45870e-01   1.48171e-01  -7.88360e+01

    TLatex latexInfo;
    latexInfo.SetTextFont(42);
    latexInfo.SetTextSize(0.04);
    latexInfo.DrawLatex(0.068,0.09,"ALICE 3 Simulation");
    TLatex latexInfo1;
    latexInfo1.SetTextFont(42);
    latexInfo1.SetTextSize(0.03);
    latexInfo1.DrawLatex(0.068,0.08,"pp @ 14TeV");

    TLatex latexInfo2;
    latexInfo2.SetTextFont(42);
    latexInfo2.SetTextSize(0.03);
    latexInfo2.DrawLatex(0.068,0.075,"1.75 < |#eta| < 4.");

   

  
  canvasPhotonConvProbPtF->Print("PhotonConvProbF.pdf");
  canvasPhotonConvProbPtF->Print("PhotonConvProbF.png");
  
}
