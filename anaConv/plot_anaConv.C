#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"



void plot_anaConv(){

 gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetLineWidth(2);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadRightMargin(0.2);
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


TFile * fileRec = new TFile("./ana_211229_withft3.root");


/*
TFile * fileMCTruth = new TFile("./ana_211229_withft3.root");
TFile * fileRec = new TFile("./photon.histooutput-TotalSum.root");
TString inputFile = Form("./ana_211229_withft3.root");

//Double_t pt_bin_proj[]  = {0.0,0.1,0.2,0.4,0.6,0.8,1.0,1.3,1.6,2.,2.5,3,4.0,5.0,7.0,10.0};
double fMaxPt=10.0;
const int nBinsPt=71;
double pt_bin_proj[nBinsPt+1];
for(int i=0; i<nBinsPt+1; i++){
      if (i < 50) pt_bin_proj[i]              = 0.02*i;
      else if(i<60) pt_bin_proj[i]           = 1.+ 0.2*(i-50);
      else if(i<70) pt_bin_proj[i]          = 3. + 0.5*(i-60);
      else if(i<78) pt_bin_proj[i]          = 8.+ 2.0*(i-70);
      else pt_bin_proj[i]                    = fMaxPt;

     //   cout<< i<< " "<<  arrayPtBins[i]<< endl;
    };
Int_t nbinspt_proj  = sizeof(pt_bin_proj)/sizeof(*pt_bin_proj) -1;
double legPosTrack[4] = {0.45,0.6,0.8,0.75};

TFile *fIn  = TFile::Open(inputFile.Data());

/////       1. ETA ACCEPTANCE

///////      1,1 HISTOGRAMS    ///////

TH1F* hPt_Eta_gg_barrel               = (TH1F*) fIn->Get(Form("hPtGGEta"));
TH1F* hPt_Eta_gg_PtCut_barrel         = (TH1F*) fIn->Get(Form("hPtGGEtaCut"));
TH1F* hPt_Eta_gg_barrel_rebin         = (TH1F*) hPt_Eta_gg_barrel->Rebin(nbinspt_proj,"hPt_Eta_gg_barrel",&pt_bin_proj[0]);
TH1F* hPt_Eta_gg_PtCut_barrel_rebin   = (TH1F*) hPt_Eta_gg_PtCut_barrel->Rebin(nbinspt_proj,"hPt_Eta_gg_PtCut_barrel",&pt_bin_proj[0]);
TH1F* hPt_Eta_gg_barrel_rebin_ratio   = (TH1F*) hPt_Eta_gg_barrel_rebin->Clone("Ratio_hPt_Eta_gg_barrel_to_PtCut");
hPt_Eta_gg_barrel_rebin_ratio->Divide(hPt_Eta_gg_PtCut_barrel_rebin, hPt_Eta_gg_barrel_rebin,1,1,"B");

TH1F* hPt_Eta_gg_forward               = (TH1F*) fIn->Get(Form("hPtGGEtaF"));
TH1F* hPt_Eta_gg_PtCut_forward         = (TH1F*) fIn->Get(Form("hPtGGEtaFCut"));
TH1F* hPt_Eta_gg_forward_rebin         = (TH1F*) hPt_Eta_gg_forward->Rebin(nbinspt_proj,"hPt_Eta_gg_forward",&pt_bin_proj[0]);
TH1F* hPt_Eta_gg_PtCut_forward_rebin   = (TH1F*) hPt_Eta_gg_PtCut_forward->Rebin(nbinspt_proj,"hPt_Eta_gg_PtCut_forward",&pt_bin_proj[0]);
TH1F* hPt_Eta_gg_forward_rebin_ratio   = (TH1F*) hPt_Eta_gg_forward_rebin->Clone("Ratio_hPt_Eta_gg_forward_to_PtCut");
hPt_Eta_gg_forward_rebin_ratio->Divide(hPt_Eta_gg_PtCut_forward_rebin, hPt_Eta_gg_forward_rebin,1,1,"B");

TH1F* hPt_Eta_gg_barrelForward               = (TH1F*) fIn->Get(Form("hPtGGEtaBF"));
TH1F* hPt_Eta_gg_PtCut_barrelForward         = (TH1F*) fIn->Get(Form("hPtGGEtaBFCut"));
TH1F* hPt_Eta_gg_barrelForward_rebin         = (TH1F*) hPt_Eta_gg_barrelForward->Rebin(nbinspt_proj,"hPt_Eta_gg_barrelForward",&pt_bin_proj[0]);
TH1F* hPt_Eta_gg_PtCut_barrelForward_rebin   = (TH1F*) hPt_Eta_gg_PtCut_barrelForward->Rebin(nbinspt_proj,"hPt_Eta_gg_PtCut_barrelForward",&pt_bin_proj[0]);
TH1F* hPt_Eta_gg_barrelForward_rebin_ratio   = (TH1F*) hPt_Eta_gg_barrelForward_rebin->Clone("Ratio_hPt_Eta_gg_barrelForward_to_PtCut");
hPt_Eta_gg_barrelForward_rebin_ratio->Divide(hPt_Eta_gg_PtCut_barrelForward_rebin, hPt_Eta_gg_barrelForward_rebin,1,1,"B");

////// CANVAS  /////
auto leg_eta_acceptance = new TLegend(legPosTrack[0],legPosTrack[1],legPosTrack[2],legPosTrack[3]);
leg_eta_acceptance->SetBorderSize(0);
leg_eta_acceptance->SetFillStyle(0);
leg_eta_acceptance->SetTextSize(0.03);
hPt_Eta_gg_barrel_rebin_ratio->SetMarkerStyle(8);
hPt_Eta_gg_forward_rebin_ratio->SetMarkerStyle(8);
hPt_Eta_gg_barrelForward_rebin_ratio->SetMarkerStyle(8);

hPt_Eta_gg_barrel_rebin_ratio->SetMarkerColor(kRed);
hPt_Eta_gg_forward_rebin_ratio->SetMarkerColor(kBlue);
hPt_Eta_gg_barrelForward_rebin_ratio->SetMarkerColor(kGreen+3);
leg_eta_acceptance->SetHeader("ALICE 3 Study");
hPt_Eta_gg_barrel_rebin_ratio->SetLineColor(kRed);
hPt_Eta_gg_forward_rebin_ratio->SetLineColor(kBlue);
hPt_Eta_gg_barrelForward_rebin_ratio->SetLineColor(kGreen+3);
hPt_Eta_gg_barrel_rebin_ratio->SetLineWidth(2);
hPt_Eta_gg_forward_rebin_ratio->SetLineWidth(2);
hPt_Eta_gg_barrelForward_rebin_ratio->SetLineWidth(2);
leg_eta_acceptance->AddEntry(hPt_Eta_gg_barrel_rebin_ratio, " Barrel  : |#eta| < 1.3 ","lp");
leg_eta_acceptance->AddEntry(hPt_Eta_gg_forward_rebin_ratio," Forward : 1.75 < |#eta| < 4 ","lp");
//leg_eta_acceptance->AddEntry(hPt_Eta_gg_barrelForward_rebin_ratio," Barrel+Forward ","lp");

auto cEtaAcceptance = new TCanvas("cEtaAcceptance","cEtaAcceptance",800,800);
cEtaAcceptance->SetTopMargin(0.03);
cEtaAcceptance->SetRightMargin(0.03);
cEtaAcceptance->SetLeftMargin(0.13);
hPt_Eta_gg_barrel_rebin_ratio->GetYaxis()->SetTitle("#eta Acceptance");
hPt_Eta_gg_barrel_rebin_ratio->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
hPt_Eta_gg_barrel_rebin_ratio->GetXaxis()->SetRangeUser(0.0,5.0);
hPt_Eta_gg_barrel_rebin_ratio->GetYaxis()->SetRangeUser(0,1.1);
hPt_Eta_gg_barrel_rebin_ratio->Draw();
hPt_Eta_gg_forward_rebin_ratio->Draw("same");
//hPt_Eta_gg_barrelForward_rebin_ratio->Draw("same");
leg_eta_acceptance->Draw("same");




 /////       1.2 CONVERSION Probability
TH1D * histPrimPhotonPt = (TH1D*)fIn->Get("hPrimPhotonPt");
TH1D * histConvPrimPhotonPt = (TH1D*)fIn->Get("hPhotonPt");

TH1D* histConvPrimPhotonPtRebin = (TH1D*) histConvPrimPhotonPt->Rebin(nBinsPt,"histConvPrimPhotonPtRebin",pt_bin_proj);
TH1D* histPrimPhotonPtRebin = (TH1D*) histPrimPhotonPt->Rebin(nBinsPt,"histPrimPhotonPtRebin",pt_bin_proj);

TH1D * convProb = (TH1D*)histConvPrimPhotonPtRebin->Clone("convProb");
convProb ->Sumw2();
convProb->Divide(histConvPrimPhotonPtRebin,histPrimPhotonPtRebin,1,1,"B");
TCanvas * canvasPhotonConvProbPt = new TCanvas("canvasPhotonConvProbPt","",200,10,800,600);
TH2F * histo2Da;
histo2Da= new TH2F("histo2Da","histo2Da",1000,0.02,10.,1000,0.,0.1 );
histo2Da ->GetYaxis()->SetTitle("Conv prob");
histo2Da ->GetXaxis()->SetTitle("p_{T}(GeV/c)");
histo2Da ->DrawCopy();
convProb->GetYaxis()->SetTitle("Conv prob");
convProb->DrawCopy("same");


/////////     1.3 Reconstruction efficiency      ///////////////////

//TH1D * histConvPrimPhotonPt = (TH1D*)fileMCTruth->Get("hPhotonPt");
TH1D * histRecPhotonPt = (TH1D*) fileRec->Get("hPhotonPt");
//TH1D* histConvPrimPhotonPtRebin = (TH1D*) histConvPrimPhotonPt->Rebin(nBinsPt,"histConvPrimPhotonPtRebin",arrayPtBins);
TH1D* histRecPhotonPtRebin = (TH1D*) histRecPhotonPt->Rebin(nBinsPt,"histRecPhotonPtRebin",pt_bin_proj);
histConvPrimPhotonPtRebin->Sumw2();
histRecPhotonPtRebin->Sumw2();

    TH1D * recEff = (TH1D*)histConvPrimPhotonPtRebin->Clone("recEff");
    recEff ->Sumw2();
    recEff->Divide(histRecPhotonPtRebin,histConvPrimPhotonPtRebin,1,1,"B");
    TCanvas * canvasPhotonRecEffPt = new TCanvas("canvasPhotonRecEffPt","",200,10,800,600);

          TH2F * histo2Db;
          histo2Db= new TH2F("histo2Db","histo2Db",1000,0.02,10.,1000,0.,1.5);
    histo2Db ->GetYaxis()->SetTitle("rec_eff");
        histo2Db ->GetXaxis()->SetTitle("p_{T}(GeV/c)");
        histo2Db ->DrawCopy();
    recEff->GetYaxis()->SetTitle("rec_eff");
 //    TF1 * fitRecEff = new TF1("fitRecEff","(x<[4])*([0] * TMath::Power(x,[2])/([1]+TMath::Power(x,[3])))+(x>[4])*(1.)", 0.05,10.);
 //    fitRecEff->SetParameters(0.7,0.05,2.5,2.5,9.);
 TF1 * fitRecEff = new TF1("fitRecEff","([0] * TMath::Power(x,[2])/([1]+TMath::Power(x,[3])))", 0.05,10.);
  fitRecEff->SetParameters(0.7,0.05,2.5,2.5);

     histo2Db ->DrawCopy();
    recEff->Fit("fitRecEff","RME");
    recEff->Fit("fitRecEff","RME");

//    1  p0           5.72297e-01   1.81412e-03   5.12078e-06  -6.80217e-02
//    2  p1           6.86633e-02   1.68473e-03   3.74232e-06  -7.35543e-02
//    3  p2           3.35915e+00   1.44263e-02  -1.90377e-05   4.26185e-02
//    4  p3           3.08761e+00   1.16395e-02   1.16395e-02  -3.72290e-01

// Dezember 2021. New tracking from David

   // 1  p0           5.89182e-01   1.00126e-03   1.98354e-06  -5.15093e-01
   // 2  p1           2.96558e-03   1.37903e-04   4.73205e-07  -7.69393e+00
   // 3  p2           3.85834e+00   2.52500e-02  -3.91323e-05   4.95130e-01
   // 4  p3           3.72573e+00   2.39021e-02   2.39021e-02  -1.19343e-01

    histo2Db ->DrawCopy();
    recEff->DrawCopy("same");
    canvasPhotonRecEffPt->Print("PhotonRecEff.png");


*/ 

/*
///         RECO        ////        
double fMaxPt=10.0;
const int nBinsPt=71;
double pt_bin_proj[nBinsPt+1];
for(int i=0; i<nBinsPt+1; i++){
      if (i < 50) pt_bin_proj[i]              = 0.1*i;
      else if(i<60) pt_bin_proj[i]           = 1.+ 0.2*(i-50);
      else if(i<70) pt_bin_proj[i]          = 3. + 0.5*(i-60);
      else if(i<78) pt_bin_proj[i]          = 8.+ 2.0*(i-70);
      else pt_bin_proj[i]                    = fMaxPt;

     //   cout<< i<< " "<<  arrayPtBins[i]<< endl;
    };
Int_t nbinspt_proj  = sizeof(pt_bin_proj)/sizeof(*pt_bin_proj) -1;
double legPosTrack[4] = {0.45,0.6,0.8,0.75};

TH1D * histAll = (TH1D*) fileRec->Get("hPtGGEtaF_SmearedP");
TH1D * histRec = (TH1D*) fileRec->Get("hPtGGEtaF_rec");
TH1D * histConv = (TH1D*) fileRec->Get("hPtGGEtaF_rec_SmearedP");

TH1F* histAll_rebin         = (TH1F*) histAll->Rebin(nbinspt_proj,"hPt_Eta_gg_forward",&pt_bin_proj[0]);
TH1F* histRec_rebin   = (TH1F*) histRec->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_REC",&pt_bin_proj[0]);
TH1F* histConv_rebin   = (TH1F*) histConv->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_CONV",&pt_bin_proj[0]);

TH1F* recEFff_rebin_REC    = (TH1F*) histRec_rebin->Clone("ReC vs MC pT distribution on Eta");
TH1F* recEFff_rebin_CONV    = (TH1F*) histConv_rebin->Clone("ReC vs MC pT distribution on Eta");
recEFff_rebin_REC->Divide(histRec_rebin, histAll_rebin,1,1,"B");
recEFff_rebin_CONV->Divide(histConv_rebin, histAll_rebin,1,1,"B");
//TH1F* recEFff   = (TH1F*) histRec->Clone("recEFF");
//recEFff->Divide(histRec, histAll,1,1,"B");

TCanvas *c1 = new TCanvas("c1","multigraph",780,800);
TMultiGraph *mg = new TMultiGraph();

recEFff_rebin_REC->GetYaxis()->SetTitle("fraction");
recEFff_rebin_REC->SetMarkerColor(kBlack);
recEFff_rebin_REC->SetMarkerStyle(4);
recEFff_rebin_REC->SetLineColor(kRed);  
c1->SetLogy();  
recEFff_rebin_REC->Draw();

recEFff_rebin_CONV->GetYaxis()->SetTitle("fraction");
recEFff_rebin_CONV->SetMarkerColor(kBlack);
recEFff_rebin_CONV->SetMarkerStyle(8);
recEFff_rebin_CONV->SetLineColor(kBlue);  
recEFff_rebin_CONV->Draw("SAME");

recEFff_rebin_REC->GetXaxis()->SetRangeUser(0.1,5.0);
recEFff_rebin_REC->GetYaxis()->SetRangeUser(0.0001,0.1);

auto leg_ele_eff = new TLegend(0.2, 0.75, 0.7, 0.85);
leg_ele_eff->SetHeader("ALICE 3 Study");
leg_ele_eff->SetBorderSize(0);
leg_ele_eff->SetFillStyle(0);
leg_ele_eff->SetTextSize(0.02);
leg_ele_eff->AddEntry(recEFff_rebin_REC,"Eta ratio with Rec. eff* ConvProb cut","p");
leg_ele_eff->AddEntry(recEFff_rebin_CONV,"Eta ratio with Rec. eff* ConvProb cut and P Smeared","p");
//leg_ele_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_ele_eff->Draw("SAME");
c1->SaveAs("plots/hPtGGEtaF_ratio.png");



*/
/*
//         2D Rapidity & pT ratio        ////        


TH2D * histRapPt_ALL = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F");
TH2D * histRapPt_MC = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG");
TH2D * histRapPt_REC = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec");
//TH1F* histAll_rebin         = (TH1F*) histAll->Rebin(nbinspt_proj,"hPt_Eta_gg_forward",&pt_bin_proj[0]);
//TH1F* histRec_rebin   = (TH1F*) histRec->Rebin(nbinspt_proj,"hPt_Eta_gg_forward_REC",&pt_bin_proj[0]);
TH2D* RapPt_ratio_ALL   = (TH2D*) histRapPt_REC->Clone("ReC vs ALL rapidity and pT distribution on Pi0");
TH2D* RapPt_ratio_MC    = (TH2D*) histRapPt_REC->Clone("ReC vs ALL rapidity and pT distribution on Pi0");
RapPt_ratio_ALL->Divide(histRapPt_REC, histRapPt_ALL,1,1,"B");
RapPt_ratio_MC->Divide(histRapPt_REC, histRapPt_MC,1,1,"B");
RapPt_ratio_ALL->GetYaxis()->SetTitle("pT");
RapPt_ratio_ALL->GetXaxis()->SetTitle("Rapidity");
RapPt_ratio_ALL->Draw("colz");
//RapPt_ratio_MC->Draw("colz");

*/
/*

//                      2D projections              //

TH2D * histRapPt_ALL = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F");
TH1 * histPt_ALL_rap3to4 = histRapPt_ALL->ProjectionY("histPt_MC_rap3to4",30,40); 
TH1 * histPt_ALL_rap1_75to3 = histRapPt_ALL->ProjectionY("histPt_MC_rap1_75to3",18,30); 

TH2D * histRapPt_REC = (TH2D*) fileRec->Get("hRapidityPt_Pi0_F_GG_rec");
TH1 * histPt_REC_rap3to4 = histRapPt_REC->ProjectionY("histPt_REC_rap3to4",30,40); 
TH1 * histPt_REC_rap1_75to3 = histRapPt_REC->ProjectionY("histPt_REC_rap1_75to3",18,30); 

TH1F* histPt_RATIO_rap3to4  = (TH1F*) histPt_REC_rap3to4->Clone("histPt_RATIO_rap3to4");
histPt_RATIO_rap3to4->Divide(histPt_REC_rap3to4, histPt_ALL_rap3to4, 1,1,"B");

TH1F* histPt_RATIO_rap1_75to3  = (TH1F*) histPt_REC_rap1_75to3->Clone("histPt_RATIO_rap1_75to3");
histPt_RATIO_rap1_75to3->Divide(histPt_REC_rap1_75to3, histPt_ALL_rap1_75to3, 1,1,"B");

TCanvas *c1 = new TCanvas("c1","multigraph",780,800);
TMultiGraph *mg = new TMultiGraph();
histPt_RATIO_rap3to4->GetYaxis()->SetTitle("fraction");
histPt_RATIO_rap3to4->GetXaxis()->SetTitle("pT");
histPt_RATIO_rap3to4->SetMarkerColor(kRed);
histPt_RATIO_rap3to4->SetMarkerStyle(3);
histPt_RATIO_rap3to4->SetLineColor(kRed);  
histPt_RATIO_rap1_75to3->SetMarkerColor(kBlue);
histPt_RATIO_rap1_75to3->SetMarkerStyle(4);
histPt_RATIO_rap1_75to3->SetLineColor(kBlue);  
c1->SetLogy();  
histPt_RATIO_rap3to4->GetXaxis()->SetRangeUser(0.0,5.0);
//histPt_RATIO_rap3to4->GetYaxis()->SetRangeUser(.0001,1.1);

histPt_RATIO_rap3to4->Draw();
histPt_RATIO_rap1_75to3->Draw("SAME");

auto leg_ele_eff = new TLegend(0.5, 0.6, 0.7, 0.8);
leg_ele_eff->SetHeader("ALICE 3 Study");
leg_ele_eff->SetBorderSize(0);
leg_ele_eff->SetFillStyle(0);
leg_ele_eff->SetTextSize(0.03);
leg_ele_eff->AddEntry(histPt_RATIO_rap1_75to3,"Eta: rapidity: 1.75-3 ","p");
leg_ele_eff->AddEntry(histPt_RATIO_rap3to4,"Eta: rapidity: 3-4","p");
//leg_ele_eff->AddEntry(gr4,"3 layer DelphesO2 parameterization","l");
leg_ele_eff->Draw("SAME");

histPt_ALL_rap3to4->SetLineColor(kRed);  
histPt_ALL_rap3to4->Draw();
histPt_ALL_rap1_75to3->Draw("SAME");

histPt_REC_rap3to4->SetLineColor(kGreen);  
histPt_REC_rap3to4->Draw("SAME");
histPt_REC_rap1_75to3->SetLineColor(kViolet); 
histPt_REC_rap1_75to3->Draw("SAME");
*/

}






































