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
 #include <Math/Vector4D.h>
#include "TLorentzVector.h"
#include "analysis_files/progressbar.h"

using namespace ROOT::Math;

#endif

std::ofstream outfile;
FILE * myfile;
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
  //pSmeared.SetXYZT(pxSmeared, pySmeared, pzSmeared, 0.);
  pSmeared.SetXYZM(pxSmeared, pySmeared, pzSmeared, 0.);
  return pSmeared;
}

void print_MCTrack(std::vector<o2::MCTrack> const &a ) {
   std::cout << "The vector elements are : ";

   //for(int i=0; i < a.size(); i++)
   //std::cout << a.at(i) << ' ';
}


void ana_isolation(){
  TChain mcTree("o2sim");

//mcTree.AddFile("/misc/alidata120/alice_u/nath/electron-pack/pTcut/anaConV3/pythia_testing/pythia_gRandom_different/resultsPbPb220623/eve21/o2sim_Kine.root");
//mcTree.AddFile("/misc/alidata120/alice_u/nath/electron-pack/pTcut/anaConV3/pythia_testing/pythia_gRandom_different/resultsPbPb220623/eve22/o2sim_Kine.root");
//mcTree.AddFile("/misc/alidata120/alice_u/nath/electron-pack/pTcut/anaConV3/pythia_testing/pythia_gRandom_different/resultsPbPb220623/eve23/o2sim_Kine.root");
//mcTree.AddFile("/home/abhishek/PhD/Work/work_A/photons/input/pythia_testing/resultsPbPb220623/eve22");
  // pp events
/*  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve1/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve2/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve3/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve4/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve5/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve6/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve7/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve8/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve9/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve10/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve11/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve12/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve13/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve14/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve15/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve16/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve17/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve18/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve19/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve20/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve21/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve22/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve23/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve24/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve25/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve26/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve27/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve28/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve29/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve30/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve31/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve32/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve33/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve34/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve35/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701//results/eve36/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve37/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve37/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve37/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve38/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve39/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve40/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve41/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve42/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve43/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve44/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve45/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve46/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve47/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve48/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve49/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve50/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve51/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve52/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve53/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve54/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve55/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve56/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve57/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve58/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve59/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve60/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve61/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve62/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve63/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve64/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve65/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve66/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve67/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve68/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve69/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve70/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve71/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve72/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve73/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve74/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve75/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve76/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve77/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve78/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve79/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack-210701/results/eve80/o2sim_Kine.root");
  
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve101/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve102/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve103/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve104/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve105/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve106/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve107/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve108/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve109/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve110/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve111/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve112/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve113/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve114/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve115/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve116/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve117/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve118/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve119/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve120/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve121/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve122/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve123/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve124/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve125/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve126/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve127/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve128/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve129/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve130/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve132/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve133/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve134/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve135/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve136/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve137/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve138/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve139/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve140/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve141/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve142/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve143/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve144/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve145/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve146/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve147/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve149/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve150/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve151/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve152/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve153/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve154/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve155/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve156/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve157/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve158/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve159/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve160/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve161/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve162/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve163/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve164/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve165/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve166/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve167/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve168/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve169/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve170/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve171/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve172/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve173/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve174/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve175/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve176/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve177/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve178/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve179/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve180/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve181/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve182/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve183/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve184/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve185/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve186/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve187/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve188/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve189/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve190/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve191/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve192/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve193/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve194/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve195/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve196/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve197/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve198/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve199/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve201/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve202/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve203/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve204/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve205/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve206/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve207/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve208/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve209/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve210/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve211/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve212/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve213/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve214/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve215/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve216/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve217/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve218/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve219/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve220/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve221/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve222/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve223/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve224/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve225/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve226/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve227/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve228/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve229/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve230/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve231/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve232/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve233/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve234/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve235/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve236/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve237/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve238/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve239/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve240/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve241/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve242/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve243/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve244/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve245/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve246/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve247/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve248/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve249/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve250/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve251/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve252/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve253/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve254/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve255/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve256/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve257/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve258/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve259/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve260/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve261/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve262/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve263/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve264/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve265/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve266/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve267/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve268/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve269/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve270/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve271/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve272/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve273/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve274/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve275/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve276/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve277/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve278/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve279/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve280/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve281/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve282/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve283/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve284/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve285/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve286/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve287/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve288/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve289/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve290/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve291/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve292/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve293/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve294/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve295/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve296/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve297/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve298/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve299/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve01/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve02/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve03/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve04/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve05/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve06/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve07/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve08/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve09/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve10/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve11/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve12/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve13/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve14/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve16/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve17/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve18/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve19/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve20/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve21/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve22/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve23/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve24/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve25/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve26/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve27/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve28/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve29/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve30/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve31/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve32/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve33/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve34/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve35/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve36/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve37/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve38/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve39/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve40/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve41/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve42/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve43/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve44/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve45/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve46/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve47/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve48/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve49/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve51/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve52/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve53/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve54/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve56/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve57/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve58/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve59/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve62/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve63/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve64/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve65/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve66/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve67/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve68/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve69/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve70/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve71/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve72/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve73/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve74/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve75/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve76/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve77/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve78/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve79/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve80/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve81/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve82/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve83/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve84/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve85/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve86/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve87/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve88/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve89/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve93/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve95/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve96/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve97/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve98/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve99/o2sim_Kine.root");*/


  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve301/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve302/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve303/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve304/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve305/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve306/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve307/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve308/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve309/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve310/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve311/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve312/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve313/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve314/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve315/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve316/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve317/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve318/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve319/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve320/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve321/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve322/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve324/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve325/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve326/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve327/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve328/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve329/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve330/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve331/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve332/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve333/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve334/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve335/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve336/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve338/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve339/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve340/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve341/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve342/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve343/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve344/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve345/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve346/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve347/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve348/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve349/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve350/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve351/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve352/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve353/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve354/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve355/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve356/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve357/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve358/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve359/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve360/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve361/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve362/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve363/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve364/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve365/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve366/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve367/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve368/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve369/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve370/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve371/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve372/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve373/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve374/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve375/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve376/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve377/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve378/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve379/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve380/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve381/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve382/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve383/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve384/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve385/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve386/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve387/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve388/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve389/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve390/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve391/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve392/o2sim_Kine.root"); 
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve393/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve394/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve395/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve396/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve397/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve398/o2sim_Kine.root");

  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve401/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve402/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve403/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve404/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve405/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve406/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve407/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve408/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve409/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve410/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve411/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve412/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve413/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve414/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve415/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve416/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve417/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve418/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve419/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve420/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve421/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve422/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve424/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve425/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve426/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve427/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve428/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve429/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve430/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve431/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve432/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve433/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve434/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve435/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve436/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve438/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve439/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve440/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve441/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve442/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve443/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve444/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve445/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve446/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve447/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve448/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve449/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve450/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve451/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve452/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve453/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve454/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve455/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve456/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve457/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve458/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve459/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve460/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve461/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve462/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve463/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve464/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve465/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve466/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve467/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve468/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve469/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve470/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve471/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve472/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve473/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve474/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve475/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve476/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve477/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve478/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve479/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve480/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve481/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve482/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve483/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve484/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve485/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve486/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve487/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve488/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve489/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve490/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve491/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve492/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve493/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve494/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve495/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve496/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve497/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/results/eve498/o2sim_Kine.root");


  // PbPb events
  /*
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve601/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve602/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve603/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve604/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve605/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve606/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve607/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve608/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve609/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve610/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve611/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve612/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve613/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve614/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve615/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve616/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve617/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve618/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve619/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve620/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve621/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve622/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve624/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve625/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve626/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve627/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve628/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve629/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve630/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve631/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve632/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve633/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve634/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve635/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve636/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve638/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve639/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve640/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve641/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve642/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve643/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve644/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve645/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve646/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve647/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve648/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve649/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve650/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve651/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve652/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve653/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve654/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve655/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve656/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve657/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve658/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve659/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve660/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve661/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve662/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve663/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve664/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve665/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve666/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve667/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve668/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve669/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve670/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve671/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve672/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve673/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve674/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve675/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve676/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve677/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve678/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve679/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve680/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve681/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve682/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve683/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve684/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve685/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve686/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve687/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve688/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve689/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve690/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve691/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve692/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve693/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve694/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve695/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve696/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve697/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve698/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve699/o2sim_Kine.root");

  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve701/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve702/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve703/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve704/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve705/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve706/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve707/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve708/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve709/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve710/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve711/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve712/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve713/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve714/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve715/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve716/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve717/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve718/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve719/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve720/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve721/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve722/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve724/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve725/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve726/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve727/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve728/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve729/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve730/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve731/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve732/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve733/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve734/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve735/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve736/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve738/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve739/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve740/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve741/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve742/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve743/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve744/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve745/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve746/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve747/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve748/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve749/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve750/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve751/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve752/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve753/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve754/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve755/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve756/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve757/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve758/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve759/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve760/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve761/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve762/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve763/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve764/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve765/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve766/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve767/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve768/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve769/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve770/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve771/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve772/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve773/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve774/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve775/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve776/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve777/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve778/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve779/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve780/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve781/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve782/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve783/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve784/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve785/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve786/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve787/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve788/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve789/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve790/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve791/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve792/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve793/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve794/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve795/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve796/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve797/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve798/o2sim_Kine.root");
  mcTree.AddFile("/misc/alidata120/alice_u/marin/ALICE3/electron-pack/resultsPbPb/eve799/o2sim_Kine.root");*/



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
  TH2D hInvMassPt_B_SmearedP_Global {"hInvMassPt_B_SmearedP_Global", "InvMass and Pt in Barrel region",1000,0.,1.,10000,0.,10.};
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
  std::vector<o2::MCTrack> pi0_prim, eta_prim;
  std::vector<o2::MCTrack> kap_prim, kam_prim, prom_prim, prop_prim;
  std::vector<o2::MCTrack> pi0_prim_F, eta_prim_F;
  std::vector<o2::MCTrack> gamma_prim_F, gamF_rec_conv, gamF_conv;
  std::vector<o2::MCTrack> ep_F, em_F;

  std::vector<pair<o2::MCTrack, TLorentzVector >> gamma_prim_B_SmearedP;

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
  myfile=fopen("example.txt", "w");
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
    gamma_prim_B_SmearedP.clear();

    //gamB_rec_conv_SmearedP.clear();
    gamB_conv.clear();
    gamma_prim_F.clear();
    gamF_rec_conv.clear();
    gamF_conv.clear();

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
        if (track.GetPdgCode() == 22 ) {  

          gamma_prim_B.emplace_back(track);     
          TLorentzVector LVgam, LVgam_Smear_P;   
          (gamma_prim_B.back()).Get4Momentum(LVgam);
          LVgam_Smear_P = ApplyMomentumSmearing_F(LVgam);
          gamma_prim_B_SmearedP.emplace_back(make_pair(track, LVgam_Smear_P));        

        }
        if ( (gRandom->Uniform() < (convProb )) && (track.GetPdgCode() == 22 ) ) gamB_conv.emplace_back(track);   
        if ( (gRandom->Uniform() < (convProb * eff)) && (track.GetPdgCode() == 22 ) ) gamB_rec_conv.emplace_back(track);
        //continue;
      }	
      fprintf(myfile, "End of loop over tracks in #event: %d \n", iEvent) ;
    }

    for (auto gam1= gamma_prim_B_SmearedP.begin(); gam1!=gamma_prim_B_SmearedP.end();++gam1   ) {
      
      TLorentzVector LVgam1, LVgam1_Smear_P, LVgam1_Smear_P_Global;
      (gam1->first).Get4Momentum(LVgam1);
      fprintf(myfile,"ORIGINAL GAM 1: %f, %f, %f, %f, %f \n",LVgam1.Px(), LVgam1.Py(), LVgam1.Pz(), LVgam1.E(), LVgam1.M());
      LVgam1_Smear_P = ApplyMomentumSmearing_F(LVgam1);
      LVgam1_Smear_P_Global=gam1->second ;
      fprintf(myfile,"LOCAL SMEARING: %f, %f, %f, %f, %f \n",LVgam1_Smear_P.Px(), LVgam1_Smear_P.Py(), LVgam1_Smear_P.Pz(), LVgam1_Smear_P.E(), LVgam1_Smear_P.M());
      fprintf(myfile,"GLOBAL SMEARING: %f, %f, %f, %f, %f \n\n",LVgam1_Smear_P_Global.Px(), LVgam1_Smear_P_Global.Py(), LVgam1_Smear_P_Global.Pz(), LVgam1_Smear_P_Global.E(), LVgam1_Smear_P_Global.M());
      

      for (auto gam2= gam1+1;  gam2!= gamma_prim_B_SmearedP.end(); ++gam2 ) {

        TLorentzVector LVgam2, LVgam2_Smear_P, LVgam2_Smear_P_Global;
        (gam2->first).Get4Momentum(LVgam2); 
        fprintf(myfile,"ORIGINAL GAM 2: %f, %f, %f, %f, %f \n",LVgam2.Px(), LVgam2.Py(), LVgam2.Pz(), LVgam2.E(), LVgam2.M());
        LVgam2_Smear_P = ApplyMomentumSmearing_F(LVgam2);
        hInvMassGGB.Fill((LVgam1+LVgam2).M());
        hInvMassGGB_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M());
        hInvMassPt_B.Fill((LVgam1+LVgam2).M() ,(LVgam1+LVgam2).Pt());
        hInvMassPt_B_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());
        LVgam2_Smear_P_Global=gam2->second ;
        hInvMassPt_B_SmearedP_Global.Fill((LVgam1_Smear_P_Global+LVgam2_Smear_P_Global).M() ,(LVgam1_Smear_P_Global+LVgam2_Smear_P_Global).Pt());
        fprintf(myfile,"LOCAL SMEARING: %f, %f, %f, %f, %f \n",LVgam2_Smear_P.Px(), LVgam2_Smear_P.Py(), LVgam2_Smear_P.Pz(), LVgam2_Smear_P.E(), LVgam2_Smear_P.M());
        fprintf(myfile,"GLOBAL SMEARING: %f, %f, %f, %f, %f \n\n",LVgam2_Smear_P_Global.Px(), LVgam2_Smear_P_Global.Py(), LVgam2_Smear_P_Global.Pz(), LVgam2_Smear_P_Global.E(), LVgam2_Smear_P_Global.M());
      /*
        // add that the two gammas have the same mother
        auto mTrackMother_gam1 = (*mcTracks)[gam1->getMotherTrackId()];
        auto mTrackMother_gam2 = (*mcTracks)[gam2->getMotherTrackId()];

        if (gam1->getMotherTrackId() ==  gam2->getMotherTrackId()){
          hInvMassPt_B_GG.Fill((LVgam1+LVgam2).M() ,(LVgam1+LVgam2).Pt());
          hInvMassPt_B_GG_SmearedP.Fill((LVgam1_Smear_P+LVgam2_Smear_P).M() ,(LVgam1_Smear_P+LVgam2_Smear_P).Pt());

        } */   
      }
      fprintf(myfile, "End of a loop over pairing in #event: %d \n", iEvent) ;
    }
    bar1.progress(iEvent+1);
    fprintf(myfile, "End of #event: %d \n", iEvent) ;
  }

  ProgressBar bar2(10); 
  bar2.progress(1);
  std::unique_ptr<TFile> f {TFile::Open("ana_pTcut_withft3_check.root", "RECREATE")};

  f->WriteTObject(&hInvMassGGB);
  f->WriteTObject(&hInvMassGGB_SmearedP);
  f->WriteTObject(&hInvMassPt_B);
  f->WriteTObject(&hInvMassPt_B_SmearedP);
  f->WriteTObject(&hInvMassPt_B_SmearedP_Global);

  f->WriteTObject(&hRapidityPt_Pi0_B);
  f->WriteTObject(&hRapidityPt_Pi0_B_SmearedP);
  f->WriteTObject(&hRapidityPt_Eta_B);
  f->WriteTObject(&hRapidityPt_Eta_B_SmearedP);

  f->WriteTObject(&hInvMassGGPi0B);
  f->WriteTObject(&hInvMassGGPi0B_SmearedP);
  f->WriteTObject(&hPtGGPi0B);
  f->WriteTObject(&hPtGGPi0B_SmearedP);

  f->WriteTObject(&hInvMassGGPi0BCut);
  f->WriteTObject(&hPtGGPi0BCut);
  f->WriteTObject(&hInvMassGGPi0BCut_SmearedP);
  f->WriteTObject(&hPtGGPi0BCut_SmearedP);

  f->WriteTObject(&hInvMassGGEtaB);
  f->WriteTObject(&hInvMassGGEtaB_SmearedP);
  f->WriteTObject(&hPtGGEtaB);
  f->WriteTObject(&hPtGGEtaB_SmearedP);

  f->WriteTObject(&hRapidityPt_Eta_B_GG);
  f->WriteTObject(&hRapidityPt_Eta_B_GG_SmearedP);
  f->WriteTObject(&hRapidityPt_Pi0_B_GG);
  f->WriteTObject(&hRapidityPt_Pi0_B_GG_SmearedP);

  f->WriteTObject(&hInvMassGGEtaBCut);
  f->WriteTObject(&hPtGGEtaBCut);
  f->WriteTObject(&hInvMassGGEtaBCut_SmearedP);
  f->WriteTObject(&hPtGGEtaBCut_SmearedP);

  f->WriteTObject(&hRapidityOpeningangle_Eta_B_DaughterPhotons);
  f->WriteTObject(&hOpeningangle_P_Eta_B_DaughterPhotons);
  f->WriteTObject(&hRapidityOpeningangle_Pi0_B_DaughterPhotons);
  f->WriteTObject(&hOpeningangle_P_Pi0_B_DaughterPhotons);

  bar2.progress(9);
  fprintf(myfile, "End of analysis: \n") ;
  fclose(myfile);
}