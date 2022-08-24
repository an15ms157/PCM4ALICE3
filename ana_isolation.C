#include <iostream>
#include <fstream>
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TH2.h"
#include "TPad.h"
#include "TLegend.h"


// CINT does not understand some files included by LorentzVector
#ifndef __CINT__
#include "Math/Vector3D.h"
#include "Math/Vector4D.h"
#include "progressbar.h"

using namespace ROOT::Math;

#endif

std::ofstream outfile;
//FILE * myfile;
//FILE * myfile1;

//#include "DetectorsCommonDataFormats/DetID.h"
//#include "SimulationDataFormat/MCTrack.h"

//bool isStrange(MCTrack *track)
//{
//	auto motherId = track.getMotherTrackId();
//	if (motherId < 0) return false;
//	auto mTrack = (*mcTracks)[motherId];
//	int mpid = fabs(mTrack.GetPdgCode());
//	switch (mpid) {
//		case /* value */:
//	}
//}

//TDatime t;
//gRandom->SetSeed(t.GetDate() + t.GetYear() * t.GetHour() * t.GetMinute() * t.GetSecond()); // NB: gRandom is a global pointer ?


//MOMENTUM SMEARING
TLorentzVector  ApplyMomentumSmearing_F (const TLorentzVector& p4True) {
  float sigmaPF0 = 0.04082;

  float sigmaPt0 = 0.0314;  // parameter  sigma0 for momentum resolution
  float sigmaPt1 = 0.00406; // parameter sigma1 for momentum resolution

  double pTrue = p4True.P();
  double phi = p4True.Phi();
  double theta = p4True.Theta();
  double sigmaP;  
  
  if( TMath::Abs(p4True.Eta()) < 1.3) {
    sigmaP = pTrue * TMath::Sqrt(sigmaPt0 * sigmaPt0 + (sigmaPt1 * pTrue) * (sigmaPt1 * pTrue));
  }
  else if ( TMath::Abs(p4True.Eta()) > 1.75   &&  TMath::Abs(p4True.Eta()) < 4 ) {
    sigmaP = pTrue * TMath::Sqrt(sigmaPF0 * sigmaPF0 );
  }
  double pSmearedMag = gRandom->Gaus(pTrue, sigmaP);
  if (pSmearedMag < 0) pSmearedMag = 0;
  // Calculate smeared components of 3-vector
  Double_t pxSmeared = pSmearedMag * TMath::Cos(phi) * TMath::Sin(theta);
  Double_t pySmeared = pSmearedMag * TMath::Sin(phi) * TMath::Sin(theta);
  Double_t pzSmeared = pSmearedMag * TMath::Cos(theta);
  // Construct new 4-momentum from smeared energy and 3-momentum
  TLorentzVector pSmeared;
  pSmeared.SetXYZM(pxSmeared, pySmeared, pzSmeared, 0.);
  return pSmeared;
}

void ana_isolation(){
  TChain mcTree("o2sim");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve1/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve2/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve3/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve4/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve5/o2sim_Kine.root");

  mcTree.SetBranchStatus("*", 0);
  mcTree.SetBranchStatus("MCTrack*", 1);
  std::vector<o2::MCTrack> *mcTracks = nullptr;
  mcTree.SetBranchAddress("MCTrack", &mcTracks);
  const int nEvents = mcTree.GetEntries();
  const float r = 130.;
  //	const float r = 15.;
  const float maxZ = 150.;

  TH2D hVertex {"hVertex", "prod. vertices of e^{+}/e^{-} with photon mother;x (cm);y (cm)", 1000, -r, r, 1000, -r, r};
  TH2D hVertexR {"hVertexR", "prod. vertices of e^{+}/e^{-} with photon mother;z (cm);r (cm)", 1000, -maxZ, maxZ, 1000, 0., r};
  TH2D hVertexR_F {"hVertexR_F", "prod. vertices of e^{+}/e^{-} with photon mother in Forwards disks;z (cm);r (cm)", 1000, -maxZ, maxZ, 1000, 0., r};
    
  TH1D hInvMass {"hInvMass", "invariant mass of e^{+}/e^{-} with photon mother;m (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassSame {"hInvMassSame", "invariant mass of e^{+}/e^{-} with same photon mother;m (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hChargedPionPt {"hChargedPionPt", "Charged pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPi0Pt {"hPi0Pt", "pi0 pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hEtaPt {"hEtaPt", "eta pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};

  TH1D hPiPlusPt {"hPiPlusPt", "pi+ pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPiMinusPt {"hPiMinusPt", "pi- pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hProtonPlusPt {"hProtonPlusPt", "proton pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hProtonMinusPt {"hProtonMinusPt", "antiproton pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hKaonPlusPt {"hKaonPlusPt", "Kaon Plus pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hKaonMinusPt {"hKaonMinusPt", "Kaon Minus pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hElecPlusPt {"hElecPlusPt", "Positron pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hElecMinusPt {"hElecMinusPt", "Electron pT  ; p_{T}(GeV/c);N / N_{ev}", 10000, 0., 10.};
          
  TH1D hPrimPhotonPt {"hPrimPhotonPt", "primary Photon pT  ;p_{T} (GeV/c);N / N_{ev}", 10000, 0., 10.};
    
  TH1D hPhotonPt {"hPhotonPt", "reconstructed Photon pT  e^{+}/e^{-} with same photon mother;p_{T} (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassPrim {"hInvMassPrim", "invariant mass of primary e^{+}/e^{-}; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};

  TH1D hInvMassGG{"hInvMassGG", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0{"hInvMassGGPi0", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0_SmearedP{"hInvMassGGPi0_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEta{"hInvMassGGEta", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEta_SmearedP{"hInvMassGGEta_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0Cut{"hInvMassGGPi0Cut", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaCut{"hInvMassGGEtaCut", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  
  TH1D hPtGGPi0{"hPtGGPi0", "pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEta{"hPtGGEta", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0Cut{"hPtGGPi0Cut", "pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaCut{"hPtGGEtaCut", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};

  TH2D hRapidityPt_Pi0 {"hRapidityPt_Pi0", "Rapidity and Pt Pi0",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta {"hRapidityPt_Eta", "Rapidity and Pt Eta",10000,-5.,5.,10000,0.,10.};


  ////////////////////////
  TH1D hInvMassGGB{"hInvMassGGB", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0B{"hInvMassGGPi0B", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaB{"hInvMassGGEtaB", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0BCut{"hInvMassGGPi0BCut", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaBCut{"hInvMassGGEtaBCut", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0B{"hPtGGPi0B", "pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaB{"hPtGGEtaB", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0BCut{"hPtGGPi0BCut", "pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaBCut{"hPtGGEtaBCut", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};

  TH1D hInvMassGGB_SmearedP{"hInvMassGGB_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0B_SmearedP{"hInvMassGGPi0B_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaB_SmearedP{"hInvMassGGEtaB_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0BCut_SmearedP{"hInvMassGGPi0BCut_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaBCut_SmearedP{"hInvMassGGEtaBCut_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0B_SmearedP{"hPtGGPi0B_SmearedP", "Smeared pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaB_SmearedP{"hPtGGEtaB_SmearedP", "Smeared pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0BCut_SmearedP{"hPtGGPi0BCut_SmearedP", "pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaBCut_SmearedP{"hPtGGEtaBCut_SmearedP", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};

  TH1D hInvMassGGB_rec{"hInvMassGGB_rec", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0B_rec{"hInvMassGGPi0B_rec", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaB_rec{"hInvMassGGEtaB_rec", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0BCut_rec{"hInvMassGGPi0BCut_rec", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaBCut_rec{"hInvMassGGEtaBCut_rec", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0BCut_rec{"hPtGGPi0BCut_rec", "pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaBCut_rec{"hPtGGEtaBCut_rec", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaB_rec{"hPtGGEtaB_rec", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0B_rec{"hPtGGPi0B_rec", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassGGB_Samemother_rec{"hInvMassGGB_Samemother_rec", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
    
  TH1D hInvMassGGB_rec_SmearedP{"hInvMassGGB_rec_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0B_rec_SmearedP{"hInvMassGGPi0B_rec_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaB_rec_SmearedP{"hInvMassGGEtaB_rec_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0BCut_rec_SmearedP{"hInvMassGGPi0BCut_rec_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaBCut_rec_SmearedP{"hInvMassGGEtaBCut_rec_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0B_rec_SmearedP{"hPtGGPi0B_rec_SmearedP", "Smeared pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaB_rec_SmearedP{"hPtGGEtaB_rec_SmearedP", "Smeared pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0BCut_rec_SmearedP{"hPtGGPi0BCut_rec_SmearedP", "Smeared pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaBCut_rec_SmearedP{"hPtGGEtaBCut_rec_SmearedP", "Smeared pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassGGB_Samemother_rec_SmearedP{"hInvMassGGB_Samemother_rec_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};

  TH1D hInvMassGGB_conv{"hInvMassGGB_conv", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0B_conv{"hInvMassGGPi0B_conv", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaB_conv{"hInvMassGGEtaB_conv", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0BCut_conv{"hInvMassGGPi0BCut_conv", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaBCut_conv{"hInvMassGGEtaBCut_conv", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0BCut_conv{"hPtGGPi0BCut_conv", "pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaBCut_conv{"hPtGGEtaBCut_conv", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaB_conv{"hPtGGEtaB_conv", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0B_conv{"hPtGGPi0B_conv", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassGGB_Samemother_conv{"hInvMassGGB_Samemother_conv", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
    
  TH1D hInvMassGGB_conv_SmearedP{"hInvMassGGB_conv_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0B_conv_SmearedP{"hInvMassGGPi0B_conv_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaB_conv_SmearedP{"hInvMassGGEtaB_conv_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0BCut_conv_SmearedP{"hInvMassGGPi0BCut_conv_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaBCut_conv_SmearedP{"hInvMassGGEtaBCut_conv_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0B_conv_SmearedP{"hPtGGPi0B_conv_SmearedP", "Smeared pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaB_conv_SmearedP{"hPtGGEtaB_conv_SmearedP", "Smeared pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0BCut_conv_SmearedP{"hPtGGPi0BCut_conv_SmearedP", "pT of #pi^0 #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaBCut_conv_SmearedP{"hPtGGEtaBCut_conv_SmearedP", "pT of #h #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassGGB_Samemother_conv_SmearedP{"hInvMassGGB_Samemother_conv_SmearedP", "invariant mass of #gamma#gamma Barrel; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};

  TH2D hRapidityPt_Pi0_B {"hRapidityPt_Pi0_B", "Rapidity and Pt Pi0 in Barrel region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_B_GG {"hRapidityPt_Pi0_B_GG", "Rapidity and Pt of all Photons pairs with pi0 as same mother in Barrel region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_B_GG_conv {"hRapidityPt_Pi0_B_GG_conv", "Rapidity and Pt of all Photons pairs in Barrel region after convProb",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_B_GG_rec {"hRapidityPt_Pi0_B_GG_rec", "Rapidity and Pt of all Photons pairs in Barrel after convProb*ParamRecEff",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_B {"hRapidityPt_Eta_B", "Rapidity and Pt of all Eta in Barrel region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_B_GG{"hRapidityPt_Eta_B_GG", "Rapidity and Pt of all Photons pairs with eta as same mother in Barrel region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_B_GG_conv {"hRapidityPt_Eta_B_GG_conv", "Rapidity and Pt of all Photons pairs with eta as same mother in Barrel region after convProb",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_B_GG_rec {"hRapidityPt_Eta_B_GG_rec", "Rapidity and Pt of all Photons pairs in Barrel with eta as same mother after convProb*ParamRecEff",10000,-5.,5.,10000,0.,10.};

  TH2D hRapidityPt_Pi0_B_SmearedP {"hRapidityPt_Pi0_B_SmearedP", "Rapidity and Pt Pi0 in Barrel region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_B_GG_SmearedP {"hRapidityPt_Pi0_B_GG_SmearedP", "Rapidity and Pt of all Photons pairs with pi0 as same mother in Barrel region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_B_GG_conv_SmearedP {"hRapidityPt_Pi0_B_GG_conv_SmearedP", "Rapidity and Pt of all Photons pairs in Barrel region after convProb",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_B_GG_rec_SmearedP {"hRapidityPt_Pi0_B_GG_rec_SmearedP", "Rapidity and Pt of all Photons pairs in Barrel after convProb*ParamRecEff",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_B_SmearedP {"hRapidityPt_Eta_B_SmearedP", "Rapidity and Pt of all Eta in Barrel region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_B_GG_SmearedP{"hRapidityPt_Eta_B_GG_SmearedP", "Rapidity and Pt of all Photons pairs with eta as same mother in Barrel region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_B_GG_conv_SmearedP {"hRapidityPt_Eta_B_GG_conv_SmearedP", "Rapidity and Pt of all Photons pairs with eta as same mother in Barrel region after convProb",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_B_GG_rec_SmearedP {"hRapidityPt_Eta_B_GG_rec_SmearedP", "Rapidity and Pt of all Photons pairs in Barrel with eta as same mother after convProb*ParamRecEff",10000,-5.,5.,10000,0.,10.};

  TH2D hInvMassPt_B {"hInvMassPt_B", "InvMass and Pt in Barrel region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_B_GG {"hInvMassPt_B_GG", "InvMass and Pt of all Photons pairs with as same mother in Barrel region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_B_GG_conv {"hInvMassPt_B_GG_conv", "InvMass and Pt of all Photons pairs in Barrel region after convProb",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_B_GG_rec {"hInvMassPt_B_GG_rec", "InvMass and Pt of all Photons pairs in Barrel after convProb*ParamRecEff",1000,0.,1.,10000,0.,10.}; 
  TH2D hInvMassPt_B_SmearedP {"hInvMassPt_B_SmearedP", "InvMass and Pt in Barrel region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_B_GG_SmearedP {"hInvMassPt_B_GG_SmearedP", "InvMass and Pt of all Photons pairs with as same mother in Barrel region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_B_GG_conv_SmearedP {"hInvMassPt_B_GG_conv_SmearedP", "InvMass and Pt of all Photons pairs in Barrel region after convProb",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_B_GG_rec_SmearedP {"hInvMassPt_B_GG_rec_SmearedP", "InvMass and Pt of all Photons pairs in Barrel after convProb*ParamRecEff",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_B_GG_rec_SmearedP_All {"hInvMassPt_B_GG_rec_SmearedP_All", "InvMass and Pt of all Photons pairs in Barrel before convProb*ParamRecEff",1000,0.,1.,10000,0.,10.};

  TH2D hInvMassPt_Pi0_B_SmearedP {"hInvMassPt_Pi0_B_SmearedP", "InvMass and Pt Pi0 in barrel region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Pi0_B_GG_SmearedP {"hInvMassPt_Pi0_B_GG_SmearedP", "InvMass and Pt of all Photons pairs with pi0 as same mother in barrel region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Pi0_B_GG_conv_SmearedP {"hInvMassPt_Pi0_B_GG_conv_SmearedP", "InvMass and Pt of all Photons pairs in barrel region after convProb",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Pi0_B_GG_rec_SmearedP {"hInvMassPt_Pi0_B_GG_rec_SmearedP", "InvMass and Pt of all Photons pairs in barrel after convProb*ParamRecEff",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Eta_B_SmearedP {"hInvMassPt_Eta_B_SmearedP", "InvMass and Pt of all Eta in barrel region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Eta_B_GG_SmearedP{"hInvMassPt_Eta_B_GG_SmearedP", "InvMass and Pt of all Photons pairs with eta as same mother in barrel region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Eta_B_GG_conv_SmearedP {"hInvMassPt_Eta_B_GG_conv_SmearedP", "InvMass and Pt of all Photons pairs with eta as same mother in barrel region after convProb",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Eta_B_GG_rec_SmearedP {"hInvMassPt_Eta_B_GG_rec_SmearedP", "InvMass and Pt of all Photons pairs in barrel with eta as same mother after convProb*ParamRecEff",1000,0.,1.,10000,0.,10.};

  ////////////////////////////////

  TH1D hInvMassF {"hInvMassF", "invariant mass of e^{+}/e^{-} with photon mother Forward;m (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassSameF {"hInvMassSameF", "invariant mass of e^{+}/e^{-} with same photon mother Forward;m (GeV/c);N / N_{ev}", 2000, 0., 2.};

  TH1D hInvMassGGF{"hInvMassGGF", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0F{"hInvMassGGPi0F", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaF{"hInvMassGGEtaF", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0FCut{"hInvMassGGPi0FCut", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaFCut{"hInvMassGGEtaFCut", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0F{"hPtGGPi0F", "pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaF{"hPtGGEtaF", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0FCut{"hPtGGPi0FCut", "pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaFCut{"hPtGGEtaFCut", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};

  TH1D hInvMassGGF_SmearedP{"hInvMassGGF_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0F_SmearedP{"hInvMassGGPi0F_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaF_SmearedP{"hInvMassGGEtaF_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0FCut_SmearedP{"hInvMassGGPi0FCut_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaFCut_SmearedP{"hInvMassGGEtaFCut_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0F_SmearedP{"hPtGGPi0F_SmearedP", "Smeared pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaF_SmearedP{"hPtGGEtaF_SmearedP", "Smeared pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0FCut_SmearedP{"hPtGGPi0FCut_SmearedP", "pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaFCut_SmearedP{"hPtGGEtaFCut_SmearedP", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};

  TH1D hInvMassGGF_rec{"hInvMassGGF_rec", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0F_rec{"hInvMassGGPi0F_rec", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaF_rec{"hInvMassGGEtaF_rec", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0FCut_rec{"hInvMassGGPi0FCut_rec", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaFCut_rec{"hInvMassGGEtaFCut_rec", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0FCut_rec{"hPtGGPi0FCut_rec", "pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaFCut_rec{"hPtGGEtaFCut_rec", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaF_rec{"hPtGGEtaF_rec", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0F_rec{"hPtGGPi0F_rec", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassGGF_Samemother_rec{"hInvMassGGF_Samemother_rec", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
    
  TH1D hInvMassGGF_rec_SmearedP{"hInvMassGGF_rec_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0F_rec_SmearedP{"hInvMassGGPi0F_rec_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaF_rec_SmearedP{"hInvMassGGEtaF_rec_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0FCut_rec_SmearedP{"hInvMassGGPi0FCut_rec_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaFCut_rec_SmearedP{"hInvMassGGEtaFCut_rec_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0F_rec_SmearedP{"hPtGGPi0F_rec_SmearedP", "Smeared pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaF_rec_SmearedP{"hPtGGEtaF_rec_SmearedP", "Smeared pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0FCut_rec_SmearedP{"hPtGGPi0FCut_rec_SmearedP", "Smeared pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaFCut_rec_SmearedP{"hPtGGEtaFCut_rec_SmearedP", "Smeared pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassGGF_Samemother_rec_SmearedP{"hInvMassGGF_Samemother_rec_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};

  TH1D hInvMassGGF_conv{"hInvMassGGF_conv", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0F_conv{"hInvMassGGPi0F_conv", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaF_conv{"hInvMassGGEtaF_conv", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0FCut_conv{"hInvMassGGPi0FCut_conv", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaFCut_conv{"hInvMassGGEtaFCut_conv", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0FCut_conv{"hPtGGPi0FCut_conv", "pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaFCut_conv{"hPtGGEtaFCut_conv", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaF_conv{"hPtGGEtaF_conv", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0F_conv{"hPtGGPi0F_conv", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassGGF_Samemother_conv{"hInvMassGGF_Samemother_conv", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
    
  TH1D hInvMassGGF_conv_SmearedP{"hInvMassGGF_conv_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0F_conv_SmearedP{"hInvMassGGPi0F_conv_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaF_conv_SmearedP{"hInvMassGGEtaF_conv_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0FCut_conv_SmearedP{"hInvMassGGPi0FCut_conv_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaFCut_conv_SmearedP{"hInvMassGGEtaFCut_conv_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hPtGGPi0F_conv_SmearedP{"hPtGGPi0F_conv_SmearedP", "Smeared pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaF_conv_SmearedP{"hPtGGEtaF_conv_SmearedP", "Smeared pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0FCut_conv_SmearedP{"hPtGGPi0FCut_conv_SmearedP", "pT of #pi^0 #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaFCut_conv_SmearedP{"hPtGGEtaFCut_conv_SmearedP", "pT of #h #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hInvMassGGF_Samemother_conv_SmearedP{"hInvMassGGF_Samemother_conv_SmearedP", "invariant mass of #gamma#gamma Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};

  TH2D hRapidityPt_Pi0_F {"hRapidityPt_Pi0_F", "Rapidity and Pt Pi0 in forward region",10000,-5.,5,10000,0.,10.};
  TH2D hRapidityPt_Pi0_F_GG {"hRapidityPt_Pi0_F_GG", "Rapidity and Pt of all Photons pairs with pi0 as same mother in forward region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_F_GG_conv {"hRapidityPt_Pi0_F_GG_conv", "Rapidity and Pt of all Photons pairs in forward region after convProb",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_F_GG_rec {"hRapidityPt_Pi0_F_GG_rec", "Rapidity and Pt of all Photons pairs in forward after convProb*ParamRecEff",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_F {"hRapidityPt_Eta_F", "Rapidity and Pt of all Eta in forward region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_F_GG{"hRapidityPt_Eta_F_GG", "Rapidity and Pt of all Photons pairs with eta as same mother in forward region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_F_GG_conv {"hRapidityPt_Eta_F_GG_conv", "Rapidity and Pt of all Photons pairs with eta as same mother in forward region after convProb",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_F_GG_rec {"hRapidityPt_Eta_F_GG_rec", "Rapidity and Pt of all Photons pairs in forward with eta as same mother after convProb*ParamRecEff",10000,-5.,5.,10000,0.,10.};

  TH2D hRapidityPt_Pi0_F_SmearedP {"hRapidityPt_Pi0_F_SmearedP", "Rapidity and Pt Pi0 in forward region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_F_GG_SmearedP {"hRapidityPt_Pi0_F_GG_SmearedP", "Rapidity and Pt of all Photons pairs with pi0 as same mother in forward region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_F_GG_conv_SmearedP {"hRapidityPt_Pi0_F_GG_conv_SmearedP", "Rapidity and Pt of all Photons pairs in forward region after convProb",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Pi0_F_GG_rec_SmearedP {"hRapidityPt_Pi0_F_GG_rec_SmearedP", "Rapidity and Pt of all Photons pairs in forward after convProb*ParamRecEff",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_F_SmearedP {"hRapidityPt_Eta_F_SmearedP", "Rapidity and Pt of all Eta in forward region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_F_GG_SmearedP{"hRapidityPt_Eta_F_GG_SmearedP", "Rapidity and Pt of all Photons pairs with eta as same mother in forward region",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_F_GG_conv_SmearedP {"hRapidityPt_Eta_F_GG_conv_SmearedP", "Rapidity and Pt of all Photons pairs with eta as same mother in forward region after convProb",10000,-5.,5.,10000,0.,10.};
  TH2D hRapidityPt_Eta_F_GG_rec_SmearedP {"hRapidityPt_Eta_F_GG_rec_SmearedP", "Rapidity and Pt of all Photons pairs in forward with eta as same mother after convProb*ParamRecEff",10000,-5.,5.,10000,0.,10.};

  TH2D hInvMassPt_F {"hInvMassPt_F", "InvMass and Pt in forward region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_F_GG {"hInvMassPt_F_GG", "InvMass and Pt of all Photons pairs with as same mother in forward region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_F_GG_conv {"hInvMassPt_F_GG_conv", "InvMass and Pt of all Photons pairs in forward region after convProb",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_F_GG_rec {"hInvMassPt_F_GG_rec", "InvMass and Pt of all Photons pairs in forward after convProb*ParamRecEff",1000,0.,1.,10000,0.,10.}; 
  TH2D hInvMassPt_F_SmearedP {"hInvMassPt_F_SmearedP", "InvMass and Pt in forward region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_F_GG_SmearedP {"hInvMassPt_F_GG_SmearedP", "InvMass and Pt of all Photons pairs with as same mother in forward region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_F_GG_conv_SmearedP {"hInvMassPt_F_GG_conv_SmearedP", "InvMass and Pt of all Photons pairs in forward region after convProb",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_F_GG_rec_SmearedP {"hInvMassPt_F_GG_rec_SmearedP", "InvMass and Pt of all Photons pairs in forward after convProb*ParamRecEff",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_F_GG_rec_SmearedP_All {"hInvMassPt_F_GG_rec_SmearedP_All", "InvMass and Pt of all Photons pairs in Barrel before convProb*ParamRecEff",1000,0.,1.,10000,0.,10.};

  TH2D hInvMassPt_Pi0_F_SmearedP {"hInvMassPt_Pi0_F_SmearedP", "InvMass and Pt Pi0 in forward region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Pi0_F_GG_SmearedP {"hInvMassPt_Pi0_F_GG_SmearedP", "InvMass and Pt of all Photons pairs with pi0 as same mother in forward region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Pi0_F_GG_conv_SmearedP {"hInvMassPt_Pi0_F_GG_conv_SmearedP", "InvMass and Pt of all Photons pairs in forward region after convProb",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Pi0_F_GG_rec_SmearedP {"hInvMassPt_Pi0_F_GG_rec_SmearedP", "InvMass and Pt of all Photons pairs in forward after convProb*ParamRecEff",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Eta_F_SmearedP {"hInvMassPt_Eta_F_SmearedP", "InvMass and Pt of all Eta in forward region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Eta_F_GG_SmearedP{"hInvMassPt_Eta_F_GG_SmearedP", "InvMass and Pt of all Photons pairs with eta as same mother in forward region",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Eta_F_GG_conv_SmearedP {"hInvMassPt_Eta_F_GG_conv_SmearedP", "InvMass and Pt of all Photons pairs with eta as same mother in forward region after convProb",1000,0.,1.,10000,0.,10.};
  TH2D hInvMassPt_Eta_F_GG_rec_SmearedP {"hInvMassPt_Eta_F_GG_rec_SmearedP", "InvMass and Pt of all Photons pairs in forward with eta as same mother after convProb*ParamRecEff",1000,0.,1.,10000,0.,10.};

  TH1D hPrimPhotonPtF {"hPrimPhotonPtF", "primary Photon pT  F ;p_{T} (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPhotonPtF {"hPhotonPtF", "reconstructed Photon pT forward e^{+}/e^{-} with same photon mother;p_{T} (GeV/c);N / N_{ev}", 10000, 0., 10.};

  TH1D hPrimPhotonPF {"hPrimPhotonPF", "primary Photon p  F ;p_{T} (GeV/c);N / N_{ev}", 5000, 0., 100.};
  TH1D hPhotonPF {"hPhotonPF", "reconstructed Photon p forward e^{+}/e^{-} with same photon mother;p (GeV/c);N / N_{ev}", 5000, 0., 100.};

                    
  TH1D hInvMassGGBF{"hInvMassGGBF", "invariant mass of #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0BF{"hInvMassGGPi0BF", "invariant mass of #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaBF{"hInvMassGGEtaBF", "invariant mass of #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGPi0BFCut{"hInvMassGGPi0BFCut", "invariant mass of #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
  TH1D hInvMassGGEtaBFCut{"hInvMassGGEtaBFCut", "invariant mass of #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 2000, 0., 2.};
 
  TH1D hPtGGPi0BF{"hPtGGPi0BF", "pT of #pi^0 #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaBF{"hPtGGEtaBF", "pT of #h #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGPi0BFCut{"hPtGGPi0BFCut", "pT of #pi^0 #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
  TH1D hPtGGEtaBFCut{"hPtGGEtaBFCut", "pT of #h #gamma#gamma Barrel-Forward; p_{T}  (GeV/c);N / N_{ev}", 10000, 0., 10.};
 



  TH1D hNPrimChPiP {"hNPrimChPiP", "number of primary charged pi+; N#pi+  ;N / N_{ev}", 2000, -0.5, 199.5};
  TH1D hNPrimChPiM {"hNPrimChPiM", "number of primary charged pi-; N#pi-  ;N / N_{ev}", 2000, -0.5, 199.5};
  TH1D hNPhotonConv{"hNPhotonConv", "number of Photon conversions; N#g  ;N / N_{ev}", 2000, -0.5, 199.5};

  TH1D hLS1 {"hLS1","Like Sign spectrum of -- pairs from all particles;m_{ee} (GeV/c^{2})", 100,0,1};
  TH1D hLS2 {"hLS2","Like Sign spectrum of ++ pairs from all particles;m_{ee} (GeV/c^{2})", 100,0,1};
  TH1D hLS1prim {"hLS1prim","Like Sign spectrum of -- pairs from primary particles;m_{ee} (GeV/c^{2})", 100,0,1};
  TH1D hLS2prim {"hLS2prim","Like Sign spectrum of ++ pairs from primary particles;m_{ee} (GeV/c^{2})", 100,0,1};


  TH3D hRapidityP_Pi0_F_DaughterPhotons {"hRapidityP_Pi0_F_DaughterPhotons", "Rapidity and P for Pi0 daughter photons in forward region",10000,-5.,5.,10000,-5.,5.,10000,0.,10.};
  TH3D hRapidityP_Eta_F_DaughterPhotons {"hRapidityP_Eta_F_DaughterPhotons", "Rapidity and P for Eta daughter photons in forward region",10000,-5.,5.,10000,-5.,5.,10000,0.,10.};
  TH3D hRapidityP_Pi0_B_DaughterPhotons {"hRapidityP_Pi0_B_DaughterPhotons", "Rapidity and P for Pi0 daughter photons in Barrel region",10000,-5.,5.,10000,-5.,5.,10000,0.,10.};
  TH3D hRapidityP_Eta_B_DaughterPhotons {"hRapidityP_Eta_B_DaughterPhotons", "Rapidity and P for Eta daughter photons in Barrel region",10000,-5.,5.,10000,-5.,5.,10000,0.,10.};

  TH2D hRapidityOpeningangle_Pi0_F_DaughterPhotons {"hRapidityOpeningangle_Pi0_F_DaughterPhotons", "Rapidity and Opening angle for Pi0 daughter photons in forward region",10000,-5.,5.,10000,-5.,5.};
  TH2D hRapidityOpeningangle_Eta_F_DaughterPhotons {"hRapidityOpeningangle_Eta_F_DaughterPhotons", "Rapidity and Opening angle for Eta daughter photons in forward region",10000,-5.,5.,10000,-5.,5.};
  TH2D hRapidityOpeningangle_Pi0_B_DaughterPhotons {"hRapidityOpeningangle_Pi0_B_DaughterPhotons", "Rapidity and Opening angle for Pi0 daughter photons in barrel region",10000,-5.,5.,10000,-5.,5.};
  TH2D hRapidityOpeningangle_Eta_B_DaughterPhotons {"hRapidityOpeningangle_Eta_B_DaughterPhotons", "Rapidity and Opening angle for Eta daughter photons in barrel region",10000,-5.,5.,10000,-5.,5.};

  TH2D hOpeningangle_PT_Pi0_F_DaughterPhotons {"hOpeningangle_PT_Pi0_F_DaughterPhotons", "Pt and Opening angle for Pi0 daughter photons in forward region",10000,0.,10.,10000,-5.,5.};
  TH2D hOpeningangle_PT_Eta_F_DaughterPhotons {"hOpeningangle_PT_Eta_F_DaughterPhotons", "Pt and Opening angle for Eta daughter photons in forward region",10000,0.,10.,10000,-5.,5.};
  TH2D hOpeningangle_P_Pi0_B_DaughterPhotons {"hOpeningangle_P_Pi0_B_DaughterPhotons", "P and Opening angle for Pi0 daughter photons in barrel region",10000,0.,10.,10000,-5.,5.};
  TH2D hOpeningangle_P_Eta_B_DaughterPhotons {"hOpeningangle_P_Eta_B_DaughterPhotons", "P and Opening angle for Eta daughter photons in barrel region",10000,0.,10.,10000,-5.,5.};

    
  double eMass = 0.000511;
  double minPt = 0.01;
  double minPtG = 0.1;
  double minPFG = 0.1;
  //double maxR  = 15;
  double maxR  = 22;
  //    double maxR  = 120;
  bool momentum_cut = TRUE;

  std::vector<o2::MCTrack> ep, em, ep_prim, em_prim, pip_prim, pim_prim;
  std::vector<o2::MCTrack> gamma_prim_B, gamB_rec_conv, gamB_conv;
  std::vector<ROOT::Math::XYZTVector> gamma_prim_B_P4;
  std::vector<o2::MCTrack> pi0_prim, eta_prim;
  std::vector<o2::MCTrack> kap_prim, kam_prim, prom_prim, prop_prim;
  std::vector<o2::MCTrack> pi0_prim_F, eta_prim_F;
  std::vector<o2::MCTrack> gamma_prim_F, gamF_rec_conv, gamF_conv;
  std::vector<ROOT::Math::XYZTVector> gamma_prim_F_P4;
  std::vector<o2::MCTrack> ep_F, em_F;

  float totPiP=0;
  float totGammaConv= 0;
  float totPiM=0;
  float totPi0=0;
  float totEta=0;
  float totPi0F=0;
  float totEtaF=0;
  int count=0;
  int countPi0=0;
  int countEta=0;
  //myfile=fopen("example.txt", "a");
  //myfile1=fopen("example1.txt", "a");

  ProgressBar bar1(nEvents); 
  for(int iEvent = 0; iEvent < nEvents; ++iEvent) {
    ep.clear();
    em.clear();
    ep_prim.clear();
    em_prim.clear();
    pi0_prim.clear();
    eta_prim.clear();
    
    
    pip_prim.clear();
    pim_prim.clear();
    kap_prim.clear();
    kam_prim.clear();
    prop_prim.clear();
    prom_prim.clear();
    
    pi0_prim_F.clear();
    eta_prim_F.clear();

    gamma_prim_B.clear();
    gamB_rec_conv.clear();
    gamB_conv.clear();
    gamma_prim_B_P4.clear();
    gamma_prim_F.clear();
    gamF_rec_conv.clear();
    gamF_conv.clear();
    gamma_prim_F_P4.clear();

    mcTree.GetEntry(iEvent);
    int nConv = 0;

	  //BARREL

    for (const auto track : *mcTracks) {

	    if (TMath::Abs(track.GetRapidity()) > 1.3) continue;

	    if (track.isPrimary()) {
 	      float convProb,eff;

        convProb = 3.54334e-02 * TMath::Power(track.GetPt(), 1.47512) / (1.56461e-02 + TMath::Power(track.GetPt(), 1.43599));
        //convProb = -8.24825e-03  *( TMath::Power(track.GetP(), -5.03182e-01 )-1.13113e+01*track.GetP()) / (2.23495e-01 + TMath::Power(track.GetP(), 1.08338e+00 ));
        if (convProb > 0.04)	convProb = 0.04;

        eff = 5.89182e-01 * TMath::Power(track.GetPt(), 3.85834) / (2.96558e-03 + TMath::Power(track.GetPt(), 3.72573));
        if (eff > 1.)	eff = 1.;

	      if (track.GetPdgCode() == 211 )  pip_prim.emplace_back(track);
	      if (track.GetPdgCode() == -211 ) pim_prim.emplace_back(track);

	      if (track.GetPdgCode() == 2212 )  prop_prim.emplace_back(track);
	      if (track.GetPdgCode() == -2212 ) prom_prim.emplace_back(track);

	      if (track.GetPdgCode() == 321 )  kap_prim.emplace_back(track);
	      if (track.GetPdgCode() == -321 ) kam_prim.emplace_back(track);

        if (track.GetPdgCode() == 111 ) {
          pi0_prim.emplace_back(track);
          hRapidityPt_Pi0_B.Fill((track.GetRapidity()) ,track.GetPt());
          hRapidityPt_Pi0_B_SmearedP.Fill((track.GetRapidity()) ,track.GetPt());
        }

	      if (track.GetPdgCode() == 221 )  {
          eta_prim.emplace_back(track);
          hRapidityPt_Eta_B.Fill((track.GetRapidity()) ,track.GetPt());
          hRapidityPt_Eta_B_SmearedP.Fill((track.GetRapidity()) ,track.GetPt());
        }

        //if (track.GetP()< minPFG  ) continue;    /////    MOMENTUM CUT ON PHOTONS
	      if (track.GetPdgCode() == 22 )   gamma_prim_B.emplace_back(track);
	      if ( (gRandom->Uniform() < (convProb )) && (track.GetPdgCode() == 22 ) ) gamB_conv.emplace_back(track);   
        if ( (gRandom->Uniform() < (convProb * eff)) && (track.GetPdgCode() == 22 ) ) gamB_rec_conv.emplace_back(track);

	    }	
	    // Take only electron/positron 
	    if (TMath::Abs(track.GetPdgCode()) != 11  ) continue;

	    if (track.GetPt() < minPt) continue;
	    // AM- I am interested in conversions all the way
	    if (sqrt(track.GetStartVertexCoordinatesX()*track.GetStartVertexCoordinatesX()+ track.GetStartVertexCoordinatesY()*track.GetStartVertexCoordinatesY())> maxR) continue;
	    
      if (track.isPrimary()) {
	      if (track.GetPdgCode() > 0) ep_prim.emplace_back(track);
	      else em_prim.emplace_back(track);
	      //continue;
	    }
	    auto motherId = track.getMotherTrackId();
	    if (motherId < 0) continue;
	    auto mTrack = (*mcTracks)[motherId];
	    //cout<<"checking mother pdgcode, primary, Z of photon origin::" << mTrack.GetPdgCode()  << "  " << mTrack.isPrimary() << "  "<< mTrack.GetStartVertexCoordinatesZ()<< endl;
	    if (mTrack.GetPdgCode() != 22) continue;
	    if (!mTrack.isPrimary() ) continue;
	    hVertex.Fill(track.GetStartVertexCoordinatesX(), track.GetStartVertexCoordinatesY());
	    const auto r_vtx = std::sqrt(std::pow(track.GetStartVertexCoordinatesX(), 2) + std::pow(track.GetStartVertexCoordinatesY(), 2));
	    hVertexR.Fill(track.GetStartVertexCoordinatesZ(), r_vtx);
	    ++nConv;
	    if (track.GetPdgCode() == 11) ep.emplace_back(track);
	    else em.emplace_back(track);
    }


    totPiP+=pip_prim.size();
    totPiM+=pim_prim.size();
    
    totPi0+=pi0_prim.size();
    totEta+=eta_prim.size();
    
    
    hNPrimChPiP.Fill(pip_prim.size());
    hNPrimChPiM.Fill(pim_prim.size());
      
    //printf("nConv / nTracks = %i / %zu\n", nConv, mcTracks->size());
    int nConvSame = 0;
    for (auto p : ep) {
	    TLorentzVector vp;
	    p.Get4Momentum(vp);
	    for (auto e : em) {
	      TLorentzVector ve;
	      e.Get4Momentum(ve);
	      //cout<< "mother id of e+e-::"<< p.getMotherTrackId()<< "   " << e.getMotherTrackId()<< endl;
	      const float mass = (ve + vp).M();
	      const float gammaPt = (ve + vp).Pt();
	      hInvMass.Fill(mass);
	      if (p.getMotherTrackId() ==  e.getMotherTrackId()){
	        hInvMassSame.Fill(mass);
	        hPhotonPt.Fill(gammaPt);
	        nConvSame++;
	      }
	    }
    }

    hNPhotonConv.Fill(nConvSame);
    totGammaConv+=nConvSame;
    for (auto pip : pip_prim) {
	    TLorentzVector vpip;
	    pip.Get4Momentum(vpip);
	    hChargedPionPt.Fill(vpip.Pt());
	    hPiPlusPt.Fill(vpip.Pt());
    }

    for (auto pim : pim_prim) {
	    TLorentzVector vpim;
	    pim.Get4Momentum(vpim);
	    hChargedPionPt.Fill(vpim.Pt());
	    hPiMinusPt.Fill(vpim.Pt());
    }
      
    for (auto pi0 : pi0_prim) {
	    TLorentzVector vpi0;
	    pi0.Get4Momentum(vpi0);
	    hPi0Pt.Fill(vpi0.Pt());
    }
    
    for (auto eta : eta_prim) {
	    TLorentzVector veta;
	    eta.Get4Momentum(veta);
	    hEtaPt.Fill(veta.Pt());
    }      
    
    for (auto kap : kap_prim) {
	    TLorentzVector vkap;
	    kap.Get4Momentum(vkap);
	    hKaonPlusPt.Fill(vkap.Pt());
    }
    
    for (auto kam : kam_prim) {
	    TLorentzVector vkam;
	    kam.Get4Momentum(vkam);
	    hKaonMinusPt.Fill(vkam.Pt());
    }
      
    for (auto prop : prop_prim) {
	    TLorentzVector vprop;
	    prop.Get4Momentum(vprop);
	    hProtonPlusPt.Fill(vprop.Pt());
    }
      
    for (auto prom : prom_prim) {
	    TLorentzVector vprom;
	    prom.Get4Momentum(vprom);
	    hProtonMinusPt.Fill(vprom.Pt());
    }
      
    for (auto elp : ep_prim) {
	    TLorentzVector velp;
	    elp.Get4Momentum(velp);
	    hElecPlusPt.Fill(velp.Pt());
    }

    for (auto elm : em_prim) {
	    TLorentzVector velm;
	    elm.Get4Momentum(velm);
	    hElecMinusPt.Fill(velm.Pt());
    }	

    for (auto gam1= gamma_prim_B.begin(); gam1!=gamma_prim_B.end();++gam1   ) {
	    TLorentzVector LVgam1, LVgam1_Smear_P;
	    gam1->Get4Momentum(LVgam1);
      LVgam1_Smear_P = ApplyMomentumSmearing_F(LVgam1);
	    for (auto gam2= gam1+1;  gam2!= gamma_prim_B.end(); ++gam2 ) {
	      TLorentzVector LVgam2, LVgam2_Smear_P;
	      gam2->Get4Momentum(LVgam2); 
        LVgam2_Smear_P = ApplyMomentumSmearing_F(LVgam2);
        //cout<<LVgam2_Smear_P.Px()<<" "<<LVgam2.Px()<< endl;
        hInvMassGGB.Fill((LVgam1+LVgam2).M());
        hInvMassGGB_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());

        hInvMassPt_B.Fill((LVgam1+LVgam2).M() ,(LVgam1+LVgam2).Pt());
        hInvMassPt_B_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
	      // add that the two gammas have the same mother
	      auto mTrackMother_gam1 = (*mcTracks)[gam1->getMotherTrackId()];
        auto mTrackMother_gam2 = (*mcTracks)[gam2->getMotherTrackId()];

	      if (gam1->getMotherTrackId() ==  gam2->getMotherTrackId()){
          hInvMassPt_B_GG.Fill((LVgam1+LVgam2).M() ,(LVgam1+LVgam2).Pt());
          hInvMassPt_B_GG_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
      
          if ((mTrackMother_gam1.GetPdgCode() == 111) && (0<TMath::Abs(mTrackMother_gam1.GetRapidity())) && (TMath::Abs(mTrackMother_gam1.GetRapidity())<1.3) ){
	          hInvMassGGPi0B.Fill((LVgam1+LVgam2).M());
            hInvMassGGPi0B_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
	          hPtGGPi0B.Fill((LVgam1+LVgam2).Pt());
            hPtGGPi0B_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            hRapidityPt_Pi0_B_GG.Fill(((LVgam1+LVgam2).Rapidity()) ,(LVgam1+LVgam2).Pt());
            hRapidityPt_Pi0_B_GG_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity()) ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            //hRapidityP_Pi0_B_DaughterPhotons.Fill((LVgam1_Smear_P).Rapidity(),(LVgam2_Smear_P).Rapidity(),(LVgam1_Smear_P+LVgam2_Smear_P).P());
            hRapidityOpeningangle_Pi0_B_DaughterPhotons.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity(),(LVgam1_Smear_P.Vect()).Angle((LVgam2_Smear_P).Vect()));
            hOpeningangle_P_Pi0_B_DaughterPhotons.Fill((LVgam1_Smear_P+LVgam2_Smear_P).P(),(LVgam1_Smear_P.Vect()).Angle((LVgam2_Smear_P).Vect()));
  
            if( gam1->GetPt()> minPtG && gam2->GetPt()> minPtG){
		          hInvMassGGPi0BCut.Fill((LVgam1+LVgam2).M());
		          hPtGGPi0BCut.Fill((LVgam1+LVgam2).Pt());
	            hInvMassGGPi0BCut_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hPtGGPi0BCut_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }

          }

          if ((mTrackMother_gam1.GetPdgCode() == 221) && (0<TMath::Abs(mTrackMother_gam1.GetRapidity())) && (TMath::Abs(mTrackMother_gam1.GetRapidity())<1.3) ){
	          hInvMassGGEtaB.Fill((LVgam1+LVgam2).M());
	          hInvMassGGEtaB_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
	          hPtGGEtaB.Fill((LVgam1+LVgam2).Pt());
	          hPtGGEtaB_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            hRapidityPt_Eta_B_GG.Fill(((LVgam1+LVgam2).Rapidity()) ,(LVgam1+LVgam2).Pt());
            hRapidityPt_Eta_B_GG_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity()) ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            //hRapidityP_Eta_B_DaughterPhotons.Fill((LVgam1_Smear_P).Rapidity(),(LVgam2_Smear_P).Rapidity(),1);
            hRapidityOpeningangle_Eta_B_DaughterPhotons.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity(),(LVgam1_Smear_P.Vect()).Angle((LVgam2_Smear_P).Vect()));
            hOpeningangle_P_Eta_B_DaughterPhotons.Fill((LVgam1_Smear_P+LVgam2_Smear_P).P(),(LVgam1_Smear_P.Vect()).Angle((LVgam2_Smear_P).Vect()));

	          if( gam1->GetPt()> minPtG && gam2->GetPt()> minPtG){
		          hInvMassGGEtaBCut.Fill((LVgam1+LVgam2).M());
		          hPtGGEtaBCut.Fill((LVgam1+LVgam2).Pt());
		          hInvMassGGEtaBCut_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hPtGGEtaBCut_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }
	        }
	      }    
	    }
    }

  

    for (auto gam1= gamB_rec_conv.begin(); gam1!=gamB_rec_conv.end();++gam1   ) {
      TLorentzVector LVgam1, LVgam1_Smear_P;
      gam1->Get4Momentum(LVgam1);
      LVgam1_Smear_P = ApplyMomentumSmearing_F(LVgam1);

      for (auto gam2= gam1+1;  gam2!= gamB_rec_conv.end(); ++gam2 ) {
        TLorentzVector LVgam2, LVgam2_Smear_P;
        gam2->Get4Momentum(LVgam2);
        LVgam2_Smear_P = ApplyMomentumSmearing_F(LVgam2);

        hInvMassGGB_rec.Fill((LVgam1+LVgam2).M());
        hInvMassGGB_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
        hInvMassPt_B_GG_rec_SmearedP_All.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
        // add that the two gammas have the same mother

        auto mTrackMother_gam1 = (*mcTracks)[gam1->getMotherTrackId()];
        auto mTrackMother_gam2 = (*mcTracks)[gam2->getMotherTrackId()];

        if (gam1->getMotherTrackId() ==  gam2->getMotherTrackId()){
          hInvMassPt_B_GG_rec.Fill((LVgam1+LVgam2).M() ,(LVgam1+LVgam2).Pt());
          hInvMassPt_B_GG_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
		      hInvMassGGB_Samemother_rec.Fill((LVgam1+LVgam2).M());
		      hInvMassGGB_Samemother_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());

	        //	cout<< gam1->getMotherTrackId() <<endl;
          if ((mTrackMother_gam1.GetPdgCode() == 111) && (0<TMath::Abs(mTrackMother_gam1.GetRapidity())) && (TMath::Abs(mTrackMother_gam1.GetRapidity())<1.3) ){

	          hInvMassGGPi0B_rec.Fill((LVgam1+LVgam2).M());
            hInvMassGGPi0B_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
            hPtGGPi0B_rec.Fill((LVgam1+LVgam2).Pt());
            hPtGGPi0B_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            hRapidityPt_Pi0_B_GG_rec.Fill(((LVgam1+LVgam2).Rapidity()) ,(LVgam1+LVgam2).Pt());

            if(( LVgam1_Smear_P).Pt()> minPtG && (LVgam2_Smear_P).Pt() > minPtG){
              hRapidityPt_Pi0_B_GG_rec_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity()) ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
              hInvMassPt_Pi0_B_GG_rec_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).M()) ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }          

            if( gam1->GetPt()> minPtG && gam2->GetPt()> minPtG){
		          hInvMassGGPi0BCut_rec.Fill((LVgam1+LVgam2).M());
              hPtGGPi0BCut_rec.Fill((LVgam1+LVgam2).Pt());
		          hInvMassGGPi0BCut_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hPtGGPi0BCut_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }
          }

          if ((mTrackMother_gam1.GetPdgCode() == 221) && (0<TMath::Abs(mTrackMother_gam1.GetRapidity())) && (TMath::Abs(mTrackMother_gam1.GetRapidity())<1.3) ){
            hInvMassGGEtaB_rec.Fill((LVgam1+LVgam2).M());
       	    hPtGGEtaB_rec.Fill((LVgam1+LVgam2).Pt());
            hRapidityPt_Eta_B_GG_rec.Fill(((LVgam1+LVgam2).Rapidity()) ,(LVgam1+LVgam2).Pt());
            hInvMassGGEtaB_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
       	    hPtGGEtaB_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());

            if( (LVgam1_Smear_P).Pt()> minPtG && (LVgam2_Smear_P).Pt() > minPtG){
              hRapidityPt_Eta_B_GG_rec_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity()) ,(LVgam1+LVgam2).Pt());
              hInvMassPt_Eta_B_GG_rec_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).M()) ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }

            if( gam1->GetPt()> minPtG && gam2->GetPt()> minPtG){
              hInvMassGGEtaBCut_rec.Fill((LVgam1+LVgam2).M());
              hPtGGEtaBCut_rec.Fill((LVgam1+LVgam2).Pt());
              hInvMassGGEtaBCut_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hPtGGEtaBCut_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }
          }
        }
      }
    }

  


    // ELECTRON RESULTS
    
    for (auto p : ep_prim) {
    	TLorentzVector vp;
    	p.Get4Momentum(vp);
    	for (auto e : em_prim) {
    	  TLorentzVector ve;
    	  e.Get4Momentum(ve);
    	  const float mass = (ve + vp).M();
    	  hInvMassPrim.Fill(mass);
    	}
    }

    for (auto track1 = em.begin(); track1!=em.end(); ++track1) {
    	TLorentzVector LV1;
    	track1->Get4Momentum(LV1);
    	for (auto track2 = track1+1; track2!=em.end(); ++track2) {
    	  TLorentzVector LV2;
    	  track2->Get4Momentum(LV2);
    	  hLS1.Fill((LV1+LV2).M());
    	}
    }

    for (auto track1 = ep.begin(); track1!=ep.end(); ++track1) {
    	TLorentzVector LV1;
    	track1->Get4Momentum(LV1);
    	for (auto track2 = track1+1; track2!=ep.end(); ++track2) {
    	  TLorentzVector LV2;
    	  track2->Get4Momentum(LV2);
    	  hLS2.Fill((LV1+LV2).M());
    	}
    }

    for (auto track1 = em_prim.begin(); track1!=em_prim.end(); ++track1){
    	TLorentzVector LV1;
    	track1->Get4Momentum(LV1);
    	for (auto track2 = track1+1; track2!=em_prim.end(); ++track2){
    	  TLorentzVector LV2;
    	  track2->Get4Momentum(LV2);
    	  hLS1prim.Fill((LV1+LV2).M());
    	}
    }

    for (auto track1 = ep_prim.begin(); track1!=ep_prim.end(); ++track1) {
      TLorentzVector LV1;
      track1->Get4Momentum(LV1);
      for (auto track2 = track1+1; track2!=ep_prim.end(); ++track2) {
        TLorentzVector LV2;
        track2->Get4Momentum(LV2);
        hLS2prim.Fill((LV1+LV2).M());
      }
    }
          
      
    //  Analysing forward region
    // Fig. 67 , Table 7 LOI, 122 cm is disk 6 (150 cm disk 7), still 6 more disks
      
    float maxZConv=135;  
    ep_F.clear();
    em_F.clear();
    int nConvF=0;


    for (const auto track : *mcTracks) {
  	  //  Forward	
	    if ( (TMath::Abs(track.GetRapidity()) < 1.75) ||  (TMath::Abs(track.GetRapidity()) > 4.) )  continue;
  
  	  if (track.isPrimary()) {
	      float convProb,eff;
        convProb = -8.24825e-03  *( TMath::Power(track.GetP(), -5.03182e-01 )-1.13113e+01*track.GetP()) / (2.23495e-01 + TMath::Power(track.GetP(), 1.08338e+00 ));
        eff = 5.89182e-01 * TMath::Power(track.GetP(), 3.85834) / (2.96558e-03 + TMath::Power(track.GetP(), 3.72573));
        if (eff > 1.)	eff = 1.;
    
        if (track.GetPdgCode() == 111 ) {
          pi0_prim_F.emplace_back(track);
          hRapidityPt_Pi0_F.Fill((track.GetRapidity()) ,track.GetPt());
          hRapidityPt_Pi0_F_SmearedP.Fill((track.GetRapidity()) ,track.GetPt());
        }

	      if (track.GetPdgCode() == 221 )  {
          eta_prim_F.emplace_back(track);
          hRapidityPt_Eta_F.Fill((track.GetRapidity()) ,track.GetPt());
          hRapidityPt_Eta_F_SmearedP.Fill((track.GetRapidity()) ,track.GetPt());
        }

        //if (track.GetP()< minPFG  ) continue;    /////    MOMENTUM CUT ON PHOTONS
	      if (track.GetPdgCode() == 22 )   gamma_prim_F.emplace_back(track);
	      if ( (gRandom->Uniform() < (convProb )) && (track.GetPdgCode() == 22 ) ) gamF_conv.emplace_back(track);   
        if ( (gRandom->Uniform() < (convProb * eff)) && (track.GetPdgCode() == 22 ) ) gamF_rec_conv.emplace_back(track);
    
	    }
	
      // Conversions in forward
	    if (TMath::Abs(track.GetPdgCode()) != 11  ) continue;
      if (track.GetP()< minPFG  ) continue;
	    //// Under construction
      // AM- I am interested in conversions in forward direction
      if ( TMath::Abs(track.GetStartVertexCoordinatesZ()) > maxZConv) continue;

      auto motherId = track.getMotherTrackId();
      if (motherId < 0) continue;
      auto mTrack = (*mcTracks)[motherId];
      //cout<<"checking mother pdgcode, primary, Z of photon origin::" << mTrack.GetPdgCode()  << "  " << mTrack.isPrimary() << "  "<< mTrack.GetStartVertexCoordinatesZ()<< endl;
      if (mTrack.GetPdgCode() != 22) continue;
      if (!mTrack.isPrimary() ) continue;

      const auto r_vtx = std::sqrt(std::pow(track.GetStartVertexCoordinatesX(), 2) + std::pow(track.GetStartVertexCoordinatesY(), 2));
      hVertexR_F.Fill(track.GetStartVertexCoordinatesZ(), r_vtx);
      ++nConvF;
      if (track.GetPdgCode() == 11) ep_F.emplace_back(track);
      else em_F.emplace_back(track);
	
	    ///////////
	
    }

    // ELECTRON RESULTS
    
    for (auto pF : ep_F) {
	    TLorentzVector vpF;
	    pF.Get4Momentum(vpF);
	    for (auto eF : em_F) {
	      TLorentzVector veF;
	      eF.Get4Momentum(veF);
	      //cout<< "mother id of e+e-::"<< p.getMotherTrackId()<< "   " << e.getMotherTrackId()<< endl;
	      const float massF = (veF + vpF).M();
	      const float gammaPtF = (veF + vpF).Pt();
	      const float gammaPF = (veF + vpF).P();
	      hInvMassF.Fill(massF);
	      if (pF.getMotherTrackId() ==  eF.getMotherTrackId()){
	        hInvMassSameF.Fill(massF);
	        hPhotonPtF.Fill(gammaPtF);
	        hPhotonPF.Fill(gammaPF);
	        nConvSame++;
	      }
	    }
    }


    for (auto gamF : gamma_prim_F) {
	    TLorentzVector gammaF;
	    gamF.Get4Momentum(gammaF);
	    hPrimPhotonPtF.Fill(gammaF.Pt());
	    hPrimPhotonPF.Fill(gammaF.P());
    }
      
    totPi0F+=pi0_prim_F.size();
    totEtaF+=eta_prim_F.size();
      
    for (auto gam1= gamma_prim_F.begin(); gam1!=gamma_prim_F.end();++gam1   ) {
	    TLorentzVector LVgam1, LVgam1_Smear_P;
	    gam1->Get4Momentum(LVgam1);
      LVgam1_Smear_P = ApplyMomentumSmearing_F(LVgam1);
	    for (auto gam2= gam1+1;  gam2!= gamma_prim_F.end(); ++gam2 ) {
	      TLorentzVector LVgam2, LVgam2_Smear_P;
	      gam2->Get4Momentum(LVgam2); 
        LVgam2_Smear_P = ApplyMomentumSmearing_F(LVgam2);
        //cout<<LVgam2_Smear_P.Px()<<" "<<LVgam2.Px()<< endl;
        hInvMassGGF.Fill((LVgam1+LVgam2).M());
        hInvMassGGF_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
        hInvMassPt_F.Fill((LVgam1+LVgam2).M() ,(LVgam1+LVgam2).Pt());
        hInvMassPt_F_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
	      // add that the two gammas have the same mother
	      auto mTrackMother_gam1 = (*mcTracks)[gam1->getMotherTrackId()];
        auto mTrackMother_gam2 = (*mcTracks)[gam2->getMotherTrackId()];

	      if (gam1->getMotherTrackId() ==  gam2->getMotherTrackId()){
          hInvMassPt_F_GG.Fill((LVgam1+LVgam2).M() ,(LVgam1+LVgam2).Pt());
          hInvMassPt_F_GG_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());

    	    if ((mTrackMother_gam1.GetPdgCode() == 111) && (1.75<TMath::Abs(mTrackMother_gam1.GetRapidity())) && (TMath::Abs(mTrackMother_gam1.GetRapidity()))<4.0) {
	          hInvMassGGPi0F.Fill((LVgam1+LVgam2).M());
            hInvMassGGPi0F_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
	          hPtGGPi0F.Fill((LVgam1+LVgam2).Pt());
            hPtGGPi0F_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            hRapidityPt_Pi0_F_GG.Fill(((LVgam1+LVgam2).Rapidity()) ,(LVgam1+LVgam2).Pt());
            hRapidityPt_Pi0_F_GG_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity()) ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            //hRapidityP_Pi0_F_DaughterPhotons.Fill((LVgam1_Smear_P).Rapidity(),(LVgam2_Smear_P).Rapidity(),(LVgam1_Smear_P+LVgam2_Smear_P).P());
            hRapidityOpeningangle_Pi0_F_DaughterPhotons.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity(),(LVgam1_Smear_P.Vect()).Angle((LVgam2_Smear_P).Vect()));
            hOpeningangle_PT_Pi0_F_DaughterPhotons.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt(),(LVgam1_Smear_P.Vect()).Angle((LVgam2_Smear_P).Vect()));

	          if( gam1->GetP()> minPFG && gam2->GetP()> minPFG){
	  	        hInvMassGGPi0FCut.Fill((LVgam1+LVgam2).M());
	  	        hPtGGPi0FCut.Fill((LVgam1+LVgam2).Pt());
	            hInvMassGGPi0FCut_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hPtGGPi0FCut_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }
	        }

          if ((mTrackMother_gam1.GetPdgCode() == 221) && (1.75<TMath::Abs(mTrackMother_gam1.GetRapidity())) && (TMath::Abs(mTrackMother_gam1.GetRapidity()))<4.0) {
            hInvMassGGEtaF.Fill((LVgam1+LVgam2).M());
            hInvMassGGEtaF_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
            hPtGGEtaF.Fill((LVgam1+LVgam2).Pt());
            hPtGGEtaF_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            hRapidityPt_Eta_F_GG.Fill(((LVgam1+LVgam2).Rapidity()) ,(LVgam1+LVgam2).Pt());
            hRapidityPt_Eta_F_GG_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity()) ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            //hRapidityP_Eta_F_DaughterPhotons.Fill((LVgam1_Smear_P).Rapidity(),(LVgam2_Smear_P).Rapidity(),(LVgam1_Smear_P+LVgam2_Smear_P).P());
            hRapidityOpeningangle_Eta_F_DaughterPhotons.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity(),(LVgam1_Smear_P.Vect()).Angle((LVgam2_Smear_P).Vect()));
            hOpeningangle_PT_Eta_F_DaughterPhotons.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt(),(LVgam1_Smear_P.Vect()).Angle((LVgam2_Smear_P).Vect()));

           if( gam1->GetP()> minPFG && gam2->GetP()> minPFG){
 	            hInvMassGGEtaFCut.Fill((LVgam1+LVgam2).M());
 	            hPtGGEtaFCut.Fill((LVgam1+LVgam2).Pt());
 	            hInvMassGGEtaFCut_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hPtGGEtaFCut_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }
          }
        }    
      }
    }	



    for (auto gam1= gamF_rec_conv.begin(); gam1!=gamF_rec_conv.end();++gam1   ) {
      TLorentzVector LVgam1, LVgam1_Smear_P;
      gam1->Get4Momentum(LVgam1);
      LVgam1_Smear_P = ApplyMomentumSmearing_F(LVgam1);

      for (auto gam2= gam1+1;  gam2!= gamF_rec_conv.end(); ++gam2 ) {
        TLorentzVector LVgam2, LVgam2_Smear_P;
        gam2->Get4Momentum(LVgam2);
        LVgam2_Smear_P = ApplyMomentumSmearing_F(LVgam2);

        hInvMassGGF_rec.Fill((LVgam1+LVgam2).M());
        hInvMassGGF_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
        hInvMassPt_F_GG_rec_SmearedP_All.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
          
        // add that the two gammas have the same mother

        auto mTrackMother_gam1 = (*mcTracks)[gam1->getMotherTrackId()];
        auto mTrackMother_gam2 = (*mcTracks)[gam2->getMotherTrackId()];

        if (gam1->getMotherTrackId() ==  gam2->getMotherTrackId()){
          hInvMassPt_F_GG_rec.Fill((LVgam1+LVgam2).M() ,(LVgam1+LVgam2).Pt());
          hInvMassPt_F_GG_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
		      hInvMassGGF_Samemother_rec.Fill((LVgam1+LVgam2).M());
		      hInvMassGGF_Samemother_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
      		count++;
          //fprintf(myfile,"SAME MOTHER: %d, %d \n", gam1->getMotherTrackId(),gam2->getMotherTrackId());

	        //	cout<< gam1->getMotherTrackId() <<endl;
          if ((mTrackMother_gam1.GetPdgCode() == 111) && (1.75<TMath::Abs(mTrackMother_gam1.GetRapidity())) && (TMath::Abs(mTrackMother_gam1.GetRapidity())<4.0)) {
	          countPi0++;
	          hInvMassGGPi0F_rec.Fill((LVgam1+LVgam2).M());
            hRapidityPt_Pi0_F_GG_rec.Fill(((LVgam1+LVgam2).Rapidity()) ,(LVgam1+LVgam2).Pt());
            hPtGGPi0F_rec.Fill((LVgam1+LVgam2).Pt());

            if( (LVgam1_Smear_P).P()> minPFG && (LVgam2_Smear_P).P() > minPFG){
              hPtGGPi0F_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
              hInvMassGGPi0F_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hRapidityPt_Pi0_F_GG_rec_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity()) ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());              
              hInvMassPt_Pi0_F_GG_rec_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).M()) ,(LVgam1_Smear_P+LVgam2_Smear_P).P());
            }

            if( gam1->GetP()> minPFG && gam2->GetP()> minPFG){
              countEta++;
		          hInvMassGGPi0FCut_rec.Fill((LVgam1+LVgam2).M());
              hPtGGPi0FCut_rec.Fill((LVgam1+LVgam2).Pt());
		          hInvMassGGPi0FCut_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hPtGGPi0FCut_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }
          }

     
          if ((mTrackMother_gam1.GetPdgCode() == 221) && (1.75<TMath::Abs(mTrackMother_gam1.GetRapidity())) && (TMath::Abs(mTrackMother_gam1.GetRapidity())<4.0)) {
            hInvMassGGEtaF_rec.Fill((LVgam1+LVgam2).M());
       	    hPtGGEtaF_rec.Fill((LVgam1+LVgam2).Pt());
            hRapidityPt_Eta_F_GG_rec.Fill(((LVgam1+LVgam2).Rapidity()) ,(LVgam1+LVgam2).Pt());
          
            if( (LVgam1_Smear_P).P()> minPFG && (LVgam2_Smear_P).P() > minPFG){
              hInvMassGGEtaF_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
       	      hPtGGEtaF_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
              hRapidityPt_Eta_F_GG_rec_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).Rapidity()) ,(LVgam1+LVgam2).Pt());
              hInvMassPt_Eta_F_GG_rec_SmearedP.Fill(((LVgam1_Smear_P+LVgam2_Smear_P).M()) ,(LVgam1_Smear_P+LVgam2_Smear_P).P());

            }
            if( gam1->GetP()> minPFG && gam2->GetP()> minPFG){
              hInvMassGGEtaFCut_rec.Fill((LVgam1+LVgam2).M());
              hPtGGEtaFCut_rec.Fill((LVgam1+LVgam2).Pt());
              hInvMassGGEtaFCut_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
              hPtGGEtaFCut_rec_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).Pt());
            }
          }
        }
      }

      //fprintf(myfile1," End of small loop \n");

    }

    //fprintf(myfile1," End of big loop \n");
    
  }

  ProgressBar bar2(10); 

  std::unique_ptr<TFile> f {TFile::Open("ana_pTcut_withft3_check.root", "RECREATE")};

	f->WriteTObject(&hVertex);
  f->WriteTObject(&hVertexR);
  f->WriteTObject(&hInvMassSame);
  f->WriteTObject(&hInvMass);
  f->WriteTObject(&hInvMassPrim);
   
  f->WriteTObject(&hInvMassGG);
  f->WriteTObject(&hInvMassGGPi0);
  f->WriteTObject(&hInvMassGGPi0_SmearedP);
  f->WriteTObject(&hInvMassGGEta);
  f->WriteTObject(&hPtGGPi0);
  f->WriteTObject(&hPtGGEta);
  f->WriteTObject(&hPtGGPi0Cut);
  f->WriteTObject(&hPtGGEtaCut);

  f->WriteTObject(&hInvMassF);
  f->WriteTObject(&hInvMassSameF);
  f->WriteTObject(&hVertexR_F);
  f->WriteTObject(&hPrimPhotonPtF);
  f->WriteTObject(&hPhotonPtF);
  f->WriteTObject(&hPrimPhotonPF);
  f->WriteTObject(&hPhotonPF);

////////////
  f->WriteTObject(&hInvMassGGB);
  f->WriteTObject(&hInvMassGGPi0B);
  f->WriteTObject(&hInvMassGGEtaB);
  f->WriteTObject(&hPtGGPi0B);
  f->WriteTObject(&hPtGGEtaB);
  f->WriteTObject(&hPtGGPi0BCut);
  f->WriteTObject(&hPtGGEtaBCut);

  f->WriteTObject(&hInvMassGGB_SmearedP);
  f->WriteTObject(&hInvMassGGPi0B_SmearedP);
  f->WriteTObject(&hInvMassGGEtaB_SmearedP);
  f->WriteTObject(&hPtGGPi0B_SmearedP);
  f->WriteTObject(&hPtGGEtaB_SmearedP);
  f->WriteTObject(&hPtGGPi0BCut_SmearedP);
  f->WriteTObject(&hPtGGEtaBCut_SmearedP);

  f->WriteTObject(&hRapidityPt_Pi0_B);
  f->WriteTObject(&hRapidityPt_Pi0_B_GG);
  f->WriteTObject(&hRapidityPt_Pi0_B_GG_conv);
  f->WriteTObject(&hRapidityPt_Pi0_B_GG_rec);
  f->WriteTObject(&hRapidityPt_Eta_B);
  f->WriteTObject(&hRapidityPt_Eta_B_GG);
  f->WriteTObject(&hRapidityPt_Eta_B_GG_conv);
  f->WriteTObject(&hRapidityPt_Eta_B_GG_rec);

  f->WriteTObject(&hRapidityPt_Pi0_B_SmearedP);
  f->WriteTObject(&hRapidityPt_Pi0_B_GG_SmearedP);
  f->WriteTObject(&hRapidityPt_Pi0_B_GG_conv_SmearedP);
  f->WriteTObject(&hRapidityPt_Pi0_B_GG_rec_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_B_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_B_GG_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_B_GG_conv_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_B_GG_rec_SmearedP);

  f->WriteTObject(&hInvMassGGB_rec);
  f->WriteTObject(&hInvMassGGPi0B_rec);
  f->WriteTObject(&hInvMassGGEtaB_rec);
  f->WriteTObject(&hInvMassGGPi0BCut_rec);
  f->WriteTObject(&hInvMassGGEtaBCut_rec);
  f->WriteTObject(&hPtGGPi0BCut_rec);
  f->WriteTObject(&hPtGGEtaBCut_rec);
  f->WriteTObject(&hPtGGEtaB_rec);
  f->WriteTObject(&hPtGGPi0B_rec);

  f->WriteTObject(&hInvMassGGB_rec_SmearedP);
  f->WriteTObject(&hInvMassGGPi0B_rec_SmearedP);
  f->WriteTObject(&hInvMassGGEtaB_rec_SmearedP);
  f->WriteTObject(&hInvMassGGPi0BCut_rec_SmearedP);
  f->WriteTObject(&hInvMassGGEtaBCut_rec_SmearedP);
  f->WriteTObject(&hPtGGPi0BCut_rec_SmearedP);
  f->WriteTObject(&hPtGGEtaBCut_rec_SmearedP);
  f->WriteTObject(&hPtGGEtaB_rec_SmearedP);
  f->WriteTObject(&hPtGGPi0B_rec_SmearedP);

  f->WriteTObject(&hInvMassGGB_conv);
  f->WriteTObject(&hInvMassGGPi0B_conv);
  f->WriteTObject(&hInvMassGGEtaB_conv);
  f->WriteTObject(&hInvMassGGPi0BCut_conv);
  f->WriteTObject(&hInvMassGGEtaBCut_conv);
  f->WriteTObject(&hPtGGPi0BCut_conv);
  f->WriteTObject(&hPtGGEtaBCut_conv);
  f->WriteTObject(&hPtGGEtaB_conv);
  f->WriteTObject(&hPtGGPi0B_conv);
  f->WriteTObject(&hInvMassGGB_Samemother_conv);

  f->WriteTObject(&hInvMassGGB_conv_SmearedP);
  f->WriteTObject(&hInvMassGGPi0B_conv_SmearedP);
  f->WriteTObject(&hInvMassGGEtaB_conv_SmearedP);
  f->WriteTObject(&hInvMassGGPi0BCut_conv_SmearedP);
  f->WriteTObject(&hInvMassGGEtaBCut_conv_SmearedP);
  f->WriteTObject(&hPtGGPi0BCut_conv_SmearedP);
  f->WriteTObject(&hPtGGEtaBCut_conv_SmearedP);
  f->WriteTObject(&hPtGGEtaB_conv_SmearedP);
  f->WriteTObject(&hPtGGPi0B_conv_SmearedP);
  f->WriteTObject(&hInvMassGGB_Samemother_conv_SmearedP);    

  ////////////////////////

  bar2.progress(5);


  ////////////
  f->WriteTObject(&hInvMassGGF);
  f->WriteTObject(&hInvMassGGPi0F);
  f->WriteTObject(&hInvMassGGEtaF);
  f->WriteTObject(&hPtGGPi0F);
  f->WriteTObject(&hPtGGEtaF);
  f->WriteTObject(&hPtGGPi0FCut);
  f->WriteTObject(&hPtGGEtaFCut);

  f->WriteTObject(&hInvMassGGF_SmearedP);
  f->WriteTObject(&hInvMassGGPi0F_SmearedP);
  f->WriteTObject(&hInvMassGGEtaF_SmearedP);
  f->WriteTObject(&hPtGGPi0F_SmearedP);
  f->WriteTObject(&hPtGGEtaF_SmearedP);
  f->WriteTObject(&hPtGGPi0FCut_SmearedP);
  f->WriteTObject(&hPtGGEtaFCut_SmearedP);

  f->WriteTObject(&hRapidityPt_Pi0_F);
  f->WriteTObject(&hRapidityPt_Pi0_F_GG);
  f->WriteTObject(&hRapidityPt_Pi0_F_GG_conv);
  f->WriteTObject(&hRapidityPt_Pi0_F_GG_rec);
  f->WriteTObject(&hRapidityPt_Eta_F);
  f->WriteTObject(&hRapidityPt_Eta_F_GG);
  f->WriteTObject(&hRapidityPt_Eta_F_GG_conv);
  f->WriteTObject(&hRapidityPt_Eta_F_GG_rec);

  f->WriteTObject(&hRapidityPt_Pi0_F_SmearedP);
  f->WriteTObject(&hRapidityPt_Pi0_F_GG_SmearedP);
  f->WriteTObject(&hRapidityPt_Pi0_F_GG_conv_SmearedP);
  f->WriteTObject(&hRapidityPt_Pi0_F_GG_rec_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_F_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_F_GG_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_F_GG_conv_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_F_GG_rec_SmearedP);

  f->WriteTObject(&hInvMassPt_F);
  f->WriteTObject(&hInvMassPt_F_GG);
  f->WriteTObject(&hInvMassPt_F_GG_conv);
  f->WriteTObject(&hInvMassPt_F_GG_rec);
  f->WriteTObject(&hInvMassPt_F_SmearedP);
  f->WriteTObject(&hInvMassPt_F_GG_SmearedP);
  f->WriteTObject(&hInvMassPt_F_GG_conv_SmearedP);
  f->WriteTObject(&hInvMassPt_F_GG_rec_SmearedP);
  f->WriteTObject(&hInvMassPt_F_GG_rec_SmearedP_All);

  f->WriteTObject(&hInvMassPt_B);
  f->WriteTObject(&hInvMassPt_B_GG);
  f->WriteTObject(&hInvMassPt_B_GG_conv);
  f->WriteTObject(&hInvMassPt_B_GG_rec);
  f->WriteTObject(&hInvMassPt_B_SmearedP);
  f->WriteTObject(&hInvMassPt_B_GG_SmearedP);
  f->WriteTObject(&hInvMassPt_B_GG_conv_SmearedP);
  f->WriteTObject(&hInvMassPt_B_GG_rec_SmearedP);
  f->WriteTObject(&hInvMassPt_B_GG_rec_SmearedP_All);
    
  f->WriteTObject(&hInvMassPt_Pi0_B_SmearedP);
  f->WriteTObject(&hInvMassPt_Pi0_B_GG_SmearedP);
  f->WriteTObject(&hInvMassPt_Pi0_B_GG_conv_SmearedP);
  f->WriteTObject(&hInvMassPt_Pi0_B_GG_rec_SmearedP);
  f->WriteTObject(&hInvMassPt_Eta_B_SmearedP);
  f->WriteTObject(&hInvMassPt_Eta_B_GG_SmearedP);
  f->WriteTObject(&hInvMassPt_Eta_B_GG_conv_SmearedP);
  f->WriteTObject(&hInvMassPt_Eta_B_GG_rec_SmearedP);

  f->WriteTObject(&hInvMassPt_Pi0_F_SmearedP);
  f->WriteTObject(&hInvMassPt_Pi0_F_GG_SmearedP);
  f->WriteTObject(&hInvMassPt_Pi0_F_GG_conv_SmearedP);
  f->WriteTObject(&hInvMassPt_Pi0_F_GG_rec_SmearedP);
  f->WriteTObject(&hInvMassPt_Eta_F_SmearedP);
  f->WriteTObject(&hInvMassPt_Eta_F_GG_SmearedP);
  f->WriteTObject(&hInvMassPt_Eta_F_GG_conv_SmearedP);
  f->WriteTObject(&hInvMassPt_Eta_F_GG_rec_SmearedP);


  f->WriteTObject(&hInvMassGGF_rec);
  f->WriteTObject(&hInvMassGGPi0F_rec);
  f->WriteTObject(&hInvMassGGEtaF_rec);
  f->WriteTObject(&hInvMassGGPi0FCut_rec);
  f->WriteTObject(&hInvMassGGEtaFCut_rec);
  f->WriteTObject(&hPtGGPi0FCut_rec);
  f->WriteTObject(&hPtGGEtaFCut_rec);
  f->WriteTObject(&hPtGGEtaF_rec);
  f->WriteTObject(&hPtGGPi0F_rec);

  f->WriteTObject(&hInvMassGGF_rec_SmearedP);
  f->WriteTObject(&hInvMassGGPi0F_rec_SmearedP);
  f->WriteTObject(&hInvMassGGEtaF_rec_SmearedP);
  f->WriteTObject(&hInvMassGGPi0FCut_rec_SmearedP);
  f->WriteTObject(&hInvMassGGEtaFCut_rec_SmearedP);
  f->WriteTObject(&hPtGGPi0FCut_rec_SmearedP);
  f->WriteTObject(&hPtGGEtaFCut_rec_SmearedP);
  f->WriteTObject(&hPtGGEtaF_rec_SmearedP);
  f->WriteTObject(&hPtGGPi0F_rec_SmearedP);

  f->WriteTObject(&hInvMassGGF_conv);
  f->WriteTObject(&hInvMassGGPi0F_conv);
  f->WriteTObject(&hInvMassGGEtaF_conv);
  f->WriteTObject(&hInvMassGGPi0FCut_conv);
  f->WriteTObject(&hInvMassGGEtaFCut_conv);
  f->WriteTObject(&hPtGGPi0FCut_conv);
  f->WriteTObject(&hPtGGEtaFCut_conv);
  f->WriteTObject(&hPtGGEtaF_conv);
  f->WriteTObject(&hPtGGPi0F_conv);
  f->WriteTObject(&hInvMassGGF_Samemother_conv);

  f->WriteTObject(&hInvMassGGF_conv_SmearedP);
  f->WriteTObject(&hInvMassGGPi0F_conv_SmearedP);
  f->WriteTObject(&hInvMassGGEtaF_conv_SmearedP);
  f->WriteTObject(&hInvMassGGPi0FCut_conv_SmearedP);
  f->WriteTObject(&hInvMassGGEtaFCut_conv_SmearedP);
  f->WriteTObject(&hPtGGPi0FCut_conv_SmearedP);
  f->WriteTObject(&hPtGGEtaFCut_conv_SmearedP);
  f->WriteTObject(&hPtGGEtaF_conv_SmearedP);
  f->WriteTObject(&hPtGGPi0F_conv_SmearedP);
  f->WriteTObject(&hInvMassGGF_Samemother_conv_SmearedP);    
  
  ////////////////////////



  f->WriteTObject(&hInvMassGGBF);
  f->WriteTObject(&hInvMassGGPi0BF);
  f->WriteTObject(&hInvMassGGEtaBF);
  f->WriteTObject(&hPtGGPi0BF);
  f->WriteTObject(&hPtGGEtaBF);
  f->WriteTObject(&hPtGGPi0BFCut);
  f->WriteTObject(&hPtGGEtaBFCut);


  f->WriteTObject(&hChargedPionPt);
  f->WriteTObject(&hPhotonPt);
  f->WriteTObject(&hNPrimChPiM);
  f->WriteTObject(&hNPhotonConv);
  f->WriteTObject(&hNPrimChPiP);
  f->WriteTObject(&hPrimPhotonPt);
  f->WriteTObject(&hPiPlusPt);
  f->WriteTObject(&hPi0Pt);
  f->WriteTObject(&hEtaPt);

  f->WriteTObject(&hPiMinusPt);
  f->WriteTObject(&hProtonPlusPt);
  f->WriteTObject(&hProtonMinusPt);
  f->WriteTObject(&hKaonPlusPt);
  f->WriteTObject(&hKaonMinusPt);
  f->WriteTObject(&hElecPlusPt);
  f->WriteTObject(&hElecMinusPt);
  
    //f->WriteTObject(&hRapidityP_Pi0_F_DaughterPhotons);
    //f->WriteTObject(&hRapidityP_Eta_F_DaughterPhotons);
    //f->WriteTObject(&hRapidityP_Pi0_B_DaughterPhotons);
    //f->WriteTObject(&hRapidityP_Eta_B_DaughterPhotons);
  f->WriteTObject(&hRapidityOpeningangle_Pi0_F_DaughterPhotons);
  f->WriteTObject(&hRapidityOpeningangle_Eta_F_DaughterPhotons);
  f->WriteTObject(&hRapidityOpeningangle_Pi0_B_DaughterPhotons);
  f->WriteTObject(&hRapidityOpeningangle_Eta_B_DaughterPhotons);

  f->WriteTObject(&hOpeningangle_PT_Pi0_F_DaughterPhotons);
  f->WriteTObject(&hOpeningangle_PT_Eta_F_DaughterPhotons);
  f->WriteTObject(&hOpeningangle_P_Pi0_B_DaughterPhotons);
  f->WriteTObject(&hOpeningangle_P_Eta_B_DaughterPhotons);



  bar2.progress(9);




  cout<<"events, totGammaConv,totPiM, totPiP::"<<  nEvents << "  " <<totGammaConv<< "  "<< totPiM  << " " << totPiP<< endl;
  cout<< count << " " << countPi0 << " " << countEta << " "<< endl;


}