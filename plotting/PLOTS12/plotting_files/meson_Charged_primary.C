#include <string>

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

void meson_Charged_primary(){

gSystem->Exec("mkdir meson_Charged_primary");
gSystem->Exec("cd meson_Charged_primary");



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

bool SWITCH_write_to_file = TRUE ;

TString input_file_loc="/home/abhishek/PhD/Work/work_A/photons/output/no_event_rep/PbPb/PbPb_100event_perfile/ana_pTcut_withft3_check.root";
gSystem->Exec("mkdir ./meson_Charged_primary");
gSystem->cd("./meson_Charged_primary");


switch(collisionSystem){
    case 0:{
        
    fcollisionSystem = "pp";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.7,0.85,"#splitline{ALICE 3 Study}{pp #sqrt{#it{s}_{NN}} = 14 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
    case 1:{

    fcollisionSystem = "PbPb";
    fileRec = new TFile(input_file_loc.Data());
    ltb_general_Additional_text = new TLatex(0.7,0.85,"#splitline{ALICE 3 Study}{PbPb #sqrt{#it{s}_{NN}} = 5.5 TeV}");
    gSystem->Exec(Form("mkdir %s",fcollisionSystem.Data()));
    gSystem->cd(Form("./%s",fcollisionSystem.Data()));
    gSystem->pwd();
    cout << Form("%s system, using input root file:", fcollisionSystem.Data())<< input_file_loc.Data() << endl;

        break;
    }
}



// INPUT CONDITIONS:
plot_minPt = 0.01;
plot_maxPt = 1e3;
plot_minY = 1;
plot_maxY = 1e3;



// INPUT CONDITIONS:

//Pi0
TH1D * hNPrimChPiP = (TH1D*) fileRec->Get("hNPrimChPiP");  
TH1D * hNPrimChPiM = (TH1D*) fileRec->Get("hNPrimChPiM");  
TH1D * hNPrimChProtonPlus = (TH1D*) fileRec->Get("hNPrimChProtonPlus");  
TH1D * hNPrimChProtonMinus = (TH1D*) fileRec->Get("hNPrimChProtonMinus");  
TH1D * hNPrimChKaonP = (TH1D*) fileRec->Get("hNPrimChKaonP");  
TH1D * hNPrimChKaonM = (TH1D*) fileRec->Get("hNPrimChKaonM");  
TH1D * hNPhotonConv = (TH1D*) fileRec->Get("hNPhotonConv");  

hNPrimChPiP->Sumw2();
hNPrimChPiM->Sumw2();
hNPrimChProtonPlus->Sumw2();
hNPrimChProtonMinus->Sumw2();
hNPrimChKaonP->Sumw2();
hNPrimChKaonM->Sumw2();
hNPhotonConv->Sumw2();


TCanvas* c_meson_Charged_primary = new TCanvas(Form("c_meson_Charged_primary_%s",fcollisionSystem.Data()), Form("c_meson_Charged_primary_%s",fcollisionSystem.Data()), 0,0,600,600);
c_meson_Charged_primary->SetLogx();  
//c_meson_Charged_primary->SetLogy();  

SetStyleHistoTH1ForGraphs(hNPhotonConv, p_T.Data(), "N_{ev}", TextSize_lable, TextSize_title, TextSize_lable,TextSize_title);
DrawGammaSetMarker(hNPrimChPiP,24,0.8, kMagenta , kMagenta);
DrawGammaSetMarker(hNPrimChPiM,8,0.8, kMagenta , kMagenta);

DrawGammaSetMarker(hNPrimChProtonPlus,24,0.8, kBlue , kBlue);
DrawGammaSetMarker(hNPrimChProtonMinus,8,0.8, kBlue , kBlue);

DrawGammaSetMarker(hNPrimChKaonP,24,0.8, kCyan , kCyan);
DrawGammaSetMarker(hNPrimChKaonM,8,0.8, kCyan , kCyan);

DrawGammaSetMarker(hNPhotonConv,20,0.8, kBlack , kBlack);

hNPhotonConv->GetXaxis()->SetRangeUser(plot_minPt,plot_maxPt); 
//hNPhotonConv->GetYaxis()->SetRangeUser(plot_minY,plot_maxY); 

hNPhotonConv->SetMinimum(0); 
hNPhotonConv->Draw("");
hNPrimChPiP->Draw("SAME");
hNPrimChPiM->Draw("SAME");
hNPrimChProtonPlus->Draw("SAME");
hNPrimChProtonMinus->Draw("SAME");
hNPrimChKaonP->Draw("SAME");
hNPrimChKaonM->Draw("SAME");

SetStyleTLatex( ltb_general_Additional_text, 0.03,4);
ltb_general_Additional_text->Draw("SAME");


auto l_meson_Charged_primary = new TLegend(0.7, 0.7, 0.8, 0.5);
l_meson_Charged_primary->SetBorderSize(0);
l_meson_Charged_primary->SetFillStyle(0);
l_meson_Charged_primary->SetTextSize(TextSize);

l_meson_Charged_primary->AddEntry(hNPhotonConv,Form("Converted Photons"),"p");
l_meson_Charged_primary->AddEntry(hNPrimChPiP,Form("Pion + "),"p");
l_meson_Charged_primary->AddEntry(hNPrimChPiM,Form("Pion - "),"p");
l_meson_Charged_primary->AddEntry(hNPrimChProtonPlus,Form("Proton + "),"p");
l_meson_Charged_primary->AddEntry(hNPrimChProtonMinus,Form("Proton - "),"p");
l_meson_Charged_primary->AddEntry(hNPrimChKaonP,Form("Kaon + "),"p");
l_meson_Charged_primary->AddEntry(hNPrimChKaonM,Form("Kaon + "),"p");
l_meson_Charged_primary->Draw("SAME");

c_meson_Charged_primary->SaveAs(Form("meson_Charged_Primary.png"));


}