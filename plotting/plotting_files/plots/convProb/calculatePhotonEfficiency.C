#include <iostream>

#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"
#include "/home/abhishek/alice/AnalysisSoftware-master/CommonHeaders/PlottingGammaConversionHistos.h"



void calculatePhotonEfficiency()
{
/*    
    gROOT->Reset();
    gROOT->SetStyle("Plain");
    gStyle->SetOptTitle(kFALSE);
      gStyle->SetOptStat(0);
      gROOT->Reset();
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

      //    TFile * fileMCTruth = new TFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/anaConv/ana_allStat_Prim_maxR_20.root");
   // TFile * fileRec = new TFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve82/histooutput.root");
    //TFile * fileRec = new TFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/histooutput_total.root");
    //TFile * fileRec = new TFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/histooutput_total_withPhotonRes.root");
      //    TFile * fileRec = new TFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/histooutput_part1_allRes.root");


    // Dec2021; new track reconstruction from David
      TFile * fileMCTruth = new TFile("./fileMCTruth.root");

      TFile * fileRec = new TFile("./fileRec.root");
      TFile * fileRecForEv = new TFile("./fileRecForEv.root");


    TH1D * histPrimPhotonPt = (TH1D*)fileMCTruth->Get("hPrimPhotonPt");
    TH1D * histConvPrimPhotonPt = (TH1D*)fileMCTruth->Get("hPhotonPt");
    
    
    TH1D * histRecPhotonPt = (TH1D*) fileRec->Get("hPhotonPt");
    TH1D * hNTracks = (TH1D*) fileRecForEv->Get("hNTracks");
    TH2D * hPhotonPtRes  = (TH2D*)  fileRec->Get("hPhotonPtRes");
    TH2D * hPhotonPzRes  = (TH2D*)  fileRec->Get("hPhotonPzRes");
    TH2D * hPhotonPRes  = (TH2D*)  fileRec->Get("hPhotonPRes");
    
    histRecPhotonPt->Sumw2();
    histRecPhotonPt->Scale(1./hNTracks->GetEntries());
    
    
    // rebinning
   // int nBinsPt=78;
    const int nBinsPt=53;
    double arrayPtBins[nBinsPt+1];
    double fMaxPt=10.;

    for(int i=0; i<nBinsPt+1;i++){
      if (i < 20) arrayPtBins[i]              = 0.02*i;
      else if(i<35) arrayPtBins[i]           = 0.4+ 0.04*(i-20);
      else if(i<45) arrayPtBins[i]           = 1.+ 0.2*(i-35);
      else if(i<50) arrayPtBins[i]          = 3. + 0.4*(i-45);
      else if(i<51) arrayPtBins[i]          = 5.+ 1.0*(i-50);
      else if(i<53) arrayPtBins[i]          = 6.+ 2.0*(i-51);
      else arrayPtBins[i]                    = fMaxPt;
       
      //   cout<< i<< " "<<  arrayPtBins[i]<< endl;
    }

    //     for(int i=0; i<nBinsPt+1;i++){
    //   if (i < 50) arrayPtBins[i]              = 0.02*i;
    //   else if(i<60) arrayPtBins[i]           = 1.+ 0.2*(i-50);
    //   else if(i<70) arrayPtBins[i]          = 3. + 0.5*(i-60);
    //   else if(i<78) arrayPtBins[i]          = 8.+ 2.0*(i-70);
    //   else arrayPtBins[i]                    = fMaxPt;
       
    //   cout<< i<< " "<<  arrayPtBins[i]<< endl;
    // }

   TH1D* histPrimPhotonPtRebin = (TH1D*) histPrimPhotonPt->Rebin(nBinsPt,"histPrimPhotonPtRebin",arrayPtBins);
   TH1D* histConvPrimPhotonPtRebin = (TH1D*) histConvPrimPhotonPt->Rebin(nBinsPt,"histConvPrimPhotonPtRebin",arrayPtBins);
    TH1D* histRecPhotonPtRebin = (TH1D*) histRecPhotonPt->Rebin(nBinsPt,"histRecPhotonPtRebin",arrayPtBins);
     
            
    histPrimPhotonPtRebin->Sumw2();
    histConvPrimPhotonPtRebin->Sumw2();
    histRecPhotonPtRebin->Sumw2();
    for (Int_t i = 1; i < histRecPhotonPtRebin->GetNbinsX()+1; i++){
        histPrimPhotonPtRebin->SetBinContent(i,histPrimPhotonPtRebin->GetBinContent(i)/histPrimPhotonPtRebin->GetXaxis()->GetBinWidth(i));
        histPrimPhotonPtRebin->SetBinError(i,histPrimPhotonPtRebin->GetBinError(i)/histPrimPhotonPtRebin->GetXaxis()->GetBinWidth(i));

        histConvPrimPhotonPtRebin->SetBinContent(i,histConvPrimPhotonPtRebin->GetBinContent(i)/histConvPrimPhotonPtRebin->GetXaxis()->GetBinWidth(i));
        histConvPrimPhotonPtRebin->SetBinError(i,histConvPrimPhotonPtRebin->GetBinError(i)/histConvPrimPhotonPtRebin->GetXaxis()->GetBinWidth(i));

 
        histRecPhotonPtRebin->SetBinContent(i,histRecPhotonPtRebin->GetBinContent(i)/histRecPhotonPtRebin->GetXaxis()->GetBinWidth(i));
        histRecPhotonPtRebin->SetBinError(i,histRecPhotonPtRebin->GetBinError(i)/histRecPhotonPtRebin->GetXaxis()->GetBinWidth(i));

    }

    
    
    TCanvas * canvasPhotonPt = new TCanvas("canvasPhotonPt","",200,10,800,600);  // gives the page size
    
      canvasPhotonPt->SetLogx();
      canvasPhotonPt->SetLogy();
   //   canvasPhotonPt->SetGridx();
    //  canvasPhotonPt->SetGridy();
      TH2F * histo2D;
      histo2D= new TH2F("histo2D","histo2D",1000,0.02,11.,1000,5.e-8,50.5e1    );
histo2D ->GetYaxis()->SetTitle("N_{#gamma}/N_{ev}");
    histo2D ->GetXaxis()->SetTitle("p_{T}(GeV/c)");
    histo2D ->DrawCopy();
    histPrimPhotonPtRebin->SetMarkerStyle(20);
    histConvPrimPhotonPtRebin->SetMarkerStyle(24);
    histRecPhotonPtRebin->SetMarkerStyle(22);
  
    histPrimPhotonPtRebin->SetMarkerColor(4);
    histConvPrimPhotonPtRebin->SetMarkerColor(4);
    histRecPhotonPtRebin->SetMarkerColor(2);

      histPrimPhotonPtRebin->SetLineColor(4);
       histConvPrimPhotonPtRebin->SetLineColor(4);
       histRecPhotonPtRebin->SetLineColor(2);

    
    histPrimPhotonPtRebin->DrawCopy("same");
    histConvPrimPhotonPtRebin->DrawCopy("same");
    histRecPhotonPtRebin->DrawCopy("same");
    TLegend  * legendPhotons = new TLegend(0.7,0.7,0.9,0.9);
    legendPhotons->AddEntry(histPrimPhotonPtRebin,"#gamma","p");
    legendPhotons->AddEntry(histConvPrimPhotonPtRebin,"Converted #gamma","p");
    legendPhotons->AddEntry(histRecPhotonPtRebin,"Reconstructed #gamma","p");
    legendPhotons->Draw();
    canvasPhotonPt->Print("PhotonPrimConvRec.pdf");
    canvasPhotonPt->Print("PhotonPrimConvRec.png");
    
    TH1D * convProb = (TH1D*)histConvPrimPhotonPtRebin->Clone("convProb");
    convProb ->Sumw2();
    convProb->Divide(histConvPrimPhotonPtRebin,histPrimPhotonPtRebin,1,1,"B");

    TCanvas * canvasPhotonConvProbPt = new TCanvas("canvasPhotonConvProbPt","",200,20,800,600);
    canvasPhotonConvProbPt->SetLogx();
    TH2F * histo2Da;
    histo2Da= new TH2F("histo2Da","histo2Da",1000,0.02,10.,1000,0.,0.052 );
    //   histo2Da ->SetNdivisions(508,"Y");
    // histo2Da ->SetTickx();
    // histo2Da ->SetTicky();
    histo2Da ->GetYaxis()->SetMaxDigits(4);
    histo2Da ->GetYaxis()->SetTitleOffset(1.2);
    histo2Da ->GetXaxis()->SetTitleOffset(1.1);

    histo2Da ->GetYaxis()->SetTitle("Conv. Prob.");
    histo2Da ->GetXaxis()->SetTitle("p_{T}(GeV/c)");
    histo2Da ->DrawCopy();
    convProb->GetYaxis()->SetTitle("Conv Prob");
    convProb->DrawCopy("same");
//    TF1 * fitConvProb = new TF1("fitConvProb","(x<[4])*([0] * TMath::Power(x,[2])/([1]+TMath::Power(x,[3])))+(x>=[4])*(0.04)", 0.04,10.);
    TF1 * fitConvProb = new TF1("fitConvProb","([0] * TMath::Power(x,[2])/([1]+TMath::Power(x,[3])))", 0.04,10.);
    //fitConvProb->SetParameters(0.035,0.05,2.5,2.5,9.);
    fitConvProb->SetParameters(0.035,0.05,2.5,2.5);
   convProb->Fit("fitConvProb","RME0");
   convProb->Fit("fitConvProb","RME0");
//    1  p0           3.55541e-02   6.23467e-05   9.13230e-08  -2.83604e-01
//    2  p1           1.39201e-02   1.20122e-03  -1.09051e-07   8.04602e-02
//    3  p2           1.50281e+00   2.63357e-02   1.65095e-06   2.30003e-03
//    4  p3           1.45348e+00   2.31878e-02   2.31878e-02   2.41717e-02

//  December 2021
//     1  p0           3.54334e-02   8.80886e-05  -8.60997e-07   5.74650e+01
//    2  p1           1.56461e-02   1.80079e-03  -3.06691e-05  -2.14719e+01
//    3  p2           1.47512e+00   3.50346e-02   5.31157e-04  -2.17797e+00
//    4  p3           1.43599e+00   3.05145e-02   3.05145e-02   2.18234e-02
// 
    TLatex latexInfo;
    latexInfo.SetTextFont(42);
    latexInfo.SetTextSize(0.04);
    latexInfo.DrawLatex(0.028,0.045,"ALICE 3 Simulation");
    TLatex latexInfo1;
    latexInfo1.SetTextFont(42);
    latexInfo1.SetTextSize(0.03);
    latexInfo1.DrawLatex(0.028,0.04,"pp @ 14TeV");

    TLatex latexInfo2;
    latexInfo2.SetTextFont(42);
    latexInfo2.SetTextSize(0.03);
    latexInfo2.DrawLatex(0.028,0.035,"|#eta| < 1.3");

 
 
    canvasPhotonConvProbPt->Print("PhotonConvProb.pdf");
    canvasPhotonConvProbPt->Print("PhotonConvProb.png");
    
    TH1D * recEff = (TH1D*)histConvPrimPhotonPtRebin->Clone("recEff");
    recEff ->Sumw2();
    recEff->Divide(histRecPhotonPtRebin,histConvPrimPhotonPtRebin,1,1,"B");
    TCanvas * canvasPhotonRecEffPt = new TCanvas("canvasPhotonRecEffPt","",200,10,800,600);


    
    TH2F * histo2Db;
    histo2Db= new TH2F("histo2Db","histo2Db",1000,0.02,10.,1000,0.,1.5);
    histo2Db ->GetYaxis()->SetTitle("rec_eff");
    histo2Db ->GetXaxis()->SetTitle("p_{T}(GeV/c)");
    histo2Db ->GetYaxis()->SetMaxDigits(4);
    histo2Db ->GetYaxis()->SetTitleOffset(1.2);
    histo2Db ->GetXaxis()->SetTitleOffset(1.1);

    histo2Db ->DrawCopy();
    recEff->GetYaxis()->SetTitle("#epsilon");
 //    TF1 * fitRecEff = new TF1("fitRecEff","(x<[4])*([0] * TMath::Power(x,[2])/([1]+TMath::Power(x,[3])))+(x>[4])*(1.)", 0.05,10.);
 //    fitRecEff->SetParameters(0.7,0.05,2.5,2.5,9.);
 TF1 * fitRecEff = new TF1("fitRecEff","([0] * TMath::Power(x,[2])/([1]+TMath::Power(x,[3])))", 0.05,10.);
  fitRecEff->SetParameters(0.7,0.05,2.5,2.5);

    histo2Db ->DrawCopy();
    recEff->Fit("fitRecEff","RME0");
    recEff->Fit("fitRecEff","RME0");
    
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
    
    canvasPhotonRecEffPt->Print("PhotonRecEff.pdf");
    canvasPhotonRecEffPt->Print("PhotonRecEff.png");

    //----------------------
    
    TCanvas * canvasPhotonTotRecEffPt = new TCanvas("canvasPhotoTotnRecEffPt","",200,10,800,600);
    canvasPhotonTotRecEffPt->SetLogx();
    TH1D * totEff = (TH1D*)histConvPrimPhotonPtRebin->Clone("totEff");
    totEff ->Sumw2();
    totEff->Divide(histRecPhotonPtRebin,histPrimPhotonPtRebin,1,1,"B");
    TH2F * histo2Dbt;
    histo2Dbt= new TH2F("histo2Dbt","histo2Dbt",1000,0.09,11.,1000,0.001,0.051);
    histo2Dbt ->GetYaxis()->SetMaxDigits(4);
    histo2Dbt ->GetYaxis()->SetTitleOffset(1.2);
    histo2Dbt ->GetXaxis()->SetTitleOffset(1.1);
    histo2Dbt ->GetYaxis()->SetTitle("#epsilon_{total}");
    histo2Dbt ->GetXaxis()->SetTitle("p_{T}(GeV/c)");
    histo2Dbt ->DrawCopy();
    totEff->DrawCopy("same");


    TLatex latexInfo4;
    latexInfo4.SetTextFont(42);
    latexInfo4.SetTextSize(0.04);
    latexInfo4.DrawLatex(0.18,0.045,"ALICE 3 Simulation");
    TLatex latexInfo5;
    latexInfo5.SetTextFont(42);
    latexInfo5.SetTextSize(0.03);
    latexInfo5.DrawLatex(0.18,0.04,"pp @ 14TeV");

    TLatex latexInfo6;
    latexInfo6.SetTextFont(42);
    latexInfo6.SetTextSize(0.03);
    latexInfo6.DrawLatex(0.18,0.035,"|#eta| < 1.3");

 
    
    canvasPhotonTotRecEffPt->Print("totEff.pdf");
    canvasPhotonTotRecEffPt->Print("totEff.png");

    TCanvas * canvasPhotonPtRes = new TCanvas("canvasPhotonPtRes","",200,10,800,600);
    canvasPhotonPtRes->SetLogz();
    TH2F * histo2Dc;
    histo2Dc= new TH2F("histo2Dc","histo2Dc",1000,0.02,10.,1000,-0.05,0.05);
    histo2Dc ->GetYaxis()->SetTitle("p_{T}^{#gamma} Res ");
    histo2Dc ->GetXaxis()->SetTitle("p_{T}^{#gamma} (GeV/c)");
    histo2Dc ->DrawCopy();
    hPhotonPtRes->DrawCopy("col2,same");
    canvasPhotonPtRes->Print("PhotonRes.pdf");
    canvasPhotonPtRes->Print("PhotonRes.png");
    
    // Going to project and fit resolution plots
    
    int maxNBinsPt=11;
    double ptRanges[12]={0.05,0.1,0.2,0.4,0.6,0.8,1.,2.,4.,6.,8.,10.};
    double precision = 10E-4;
    double rangeMin = -0.07;
    double rangeMax = 0.07;
    double mean, meanE, sigma, sigmaE;
    TString defaultName="PhotonPRes";
    TH1D* Resolution_PRes[maxNBinsPt];
    TF1*  fitResolution_PRes[maxNBinsPt];
    TH1F *Resolution_Mean     = new TH1F("Resolution_Mean", "mean meson Resolution dPt vs Pt", maxNBinsPt,  ptRanges) ;
    TH1F *Resolution_Sigma    = new TH1F("Resolution_Sigma", "sigma meson Resolution dPt vs Pt", maxNBinsPt,  ptRanges) ;
    //cout<<"Bins"<< hPhotonPtRes->GetXaxis()->FindBin(0.1+0.001)<<endl;
    for (int i = 1; i < maxNBinsPt+1  ; i ++){
     //   cout<<"Pt=" << (ptRanges[i-1]+0.001)  << "  "<< (ptRanges[i]-0.001) << endl;
//        cout<< "Test=" << i<< "  "<< hPhotonPtRes->GetXaxis()->FindBin(ptRanges[i-1]+0.001)<< " "<< //hPhotonPtRes->GetXaxis()->FindBin(ptRanges[i]-0.001)<<endl;
      Resolution_PRes[i-1]= hPhotonPRes->ProjectionY(Form("%s_%i",defaultName.Data(),i-1), hPhotonPRes->GetXaxis()->FindBin(ptRanges[i-1]+0.001), hPhotonPRes->GetXaxis()->FindBin(ptRanges[i]-0.001));
        Resolution_PRes[i-1]->Sumw2();
        Resolution_PRes[i-1]->Rebin(2);
       
        if (Resolution_PRes[i-1]->GetEntries() > 0 ){
            TF1 *f0;
            f0 = new TF1("f0", "gaus" , rangeMin ,rangeMax);
            f0->SetParameter(0,1.5*Resolution_PRes[i-1]->GetMaximum());
            f0->SetParameter(1,0.);
            f0->SetParameter(2,0.02);
            if (ptRanges[i]<=0.2){
               f0->SetRange(-0.1 ,0.15);
            }else{
               f0->SetRange(rangeMin ,rangeMax);
            }
            Resolution_PRes[i-1]->Fit(f0,"RMEQF");
            mean = f0->GetParameter(1);
            meanE = f0->GetParError(1);
            sigma = f0->GetParameter(2);
            sigmaE = f0->GetParError(2);
           // new TCanvas;
            //Resolution_PRes[i-1]->DrawCopy();
            
                          cout << "Mean: " << mean << " +- " << meanE << ", sigma: " << sigma << " +- " << sigmaE << endl;
                          Resolution_Mean->SetBinContent(i, mean);
                          Resolution_Mean->SetBinError(i, meanE);
                          Resolution_Sigma->SetBinContent(i, sigma);
                          Resolution_Sigma->SetBinError(i, sigmaE);
                          delete f0;
        }
    }
    
    
//    new TCanvas;
//    Resolution_Mean->DrawCopy();
//    new TCanvas;
//    Resolution_Sigma->DrawCopy();
    TF1 * fitSigma = new TF1("fitSigma","TMath::Sqrt([0]**2+([1]*x)**2)",0.2,8.);
    Resolution_Sigma->Fit(fitSigma,"RMEQF");
    cout<< "Fit of the Sigma"<< endl;
    
    cout<< fitSigma->GetParameter(0)<< "  " << fitSigma->GetParameter(1)<< endl;
    
     TCanvas * canvasPhotonPResSigma = new TCanvas("canvasPhotonPResSigma","",200,10,800,600);
      canvasPhotonPResSigma->SetLogx();
      TH2F * histo2Dd;
      histo2Dd= new TH2F("histo2Dd","histo2Dd",1000,0.01,10.,1000,0.0,0.15);
      histo2Dd ->GetXaxis()->SetTitle("p^{#gamma} (GeV/c) ");
      histo2Dd ->GetYaxis()->SetTitle("#sigma(#Delta_{p^{#gamma}}/p) ");
      histo2Dd ->DrawCopy();
      Resolution_Sigma->SetMarkerStyle(20);
      Resolution_Sigma->SetLineColor(2);
      Resolution_Sigma->SetMarkerColor(2);
      Resolution_Sigma->DrawCopy("same");
      canvasPhotonPResSigma->Print("PhotonResSigma.pdf");
      canvasPhotonPResSigma->Print("PhotonResSigma.png");
    
    TFile fileOut("PhotonParametrization.root","RECREATE");
    convProb->Write("convProb");
    recEff->Write("recEff");
    fileOut.Close();
}

