#include <string>

#include <TFile.h>
#include <TChain.h>
#include <TH2D.h>
#include <TProfile.h>
#include <TBranch.h>
#include <TRandom3.h>
#include <TGeoGlobalMagField.h>
#include <vector>

#include <Generators/GeneratorFactory.h>
#include "FairPrimaryGenerator.h"
#include "FairGenerator.h"
#include "FairBoxGenerator.h"
#include <FairLogger.h>
#include <SimConfig/SimConfig.h>
#include <Generators/GeneratorFromFile.h>

#include "Steer/InteractionSampler.h"
#include "DataFormatsITSMFT/ROFRecord.h"
#include "ITSMFTSimulation/Hit.h"
#include "ITStracking/Configuration.h"
#include "ITStracking/IOUtils.h"
#include "ITStracking/Tracker.h"
#include "ITStracking/TrackerTraitsCPU.h"
#include "ITStracking/Vertexer.h"
#include "ITStracking/VertexerTraits.h"
#include "DataFormatsITSMFT/Cluster.h"
#include "DataFormatsITSMFT/TopologyDictionary.h"
#include "DataFormatsITSMFT/CompCluster.h"
#include "DetectorsCommonDataFormats/DetID.h"
#include "SimulationDataFormat/MCTrack.h"
#include "MathUtils/Cartesian.h"
#include "ReconstructionDataFormats/TrackParametrization.h"
#include "ReconstructionDataFormats/TrackParametrizationWithError.h"
#include "SimulationDataFormat/MCEventHeader.h"
#include "SimulationDataFormat/MCTruthContainer.h"

#include <Generators/GeneratorFactory.h>
#include "FairPrimaryGenerator.h"
#include "FairGenerator.h"
#include "FairBoxGenerator.h"
#include <FairLogger.h>
#include <SimConfig/SimConfig.h>
#include <Generators/GeneratorFromFile.h>

#include "DetectorsVertexing/DCAFitterN.h"
#include "RecoDecay.h"

#include "ReconstructionDataFormats/DCA.h"
#include "ReconstructionDataFormats/Vertex.h"
#include "Framework/DataTypes.h"
#include "DataFormatsParameters/GRPObject.h"
#include "DetectorsBase/GeometryManager.h"
#include "DetectorsBase/Propagator.h"
#include "Field/MagneticField.h"
#include "ITSBase/GeometryTGeo.h"
#include "TStopwatch.h" //for bechmarking

#include "DetectorsVertexing/PVertexer.h"
#include "DetectorsVertexing/PVertexerHelpers.h"
#include "CommonDataFormat/BunchFilling.h"
//

//This switch will enable or disable ALL CUTS BELOW
const Float_t lMasterSwitch = -1; //1: ON, -1: OFF

const Bool_t lAssociateXiDaughters = kTRUE;
const Bool_t lAssociateXic = kTRUE;
const Bool_t lAssociateXicc = kTRUE;
//Ask for hohlweger boolean
const Bool_t lHohlwegerBooleanXic = kFALSE;
const Bool_t lHohlwegerBooleanXicc = kFALSE;

//Progressively loosening, works OK
const Float_t lFirstOpening = 3.;
const Float_t lOpening = 6.;
const Float_t lThirdPass = 9.;
const Float_t lFourthPass = 12.;

//===============================================================
// PRESELECTIONS - defined individually for the magnetic field
//===============================================================

//Remove fundamentally insane combinatorics, please
Float_t lMinV0Radius; //in centimeters
Float_t lMinXiRadius; //in centimeters
Float_t lMinDCAxyBachelor; //in centimeters
Float_t lMinDCAzBachelor; //in centimeters
Float_t lMinDCAxyPositive; //in centimeters
Float_t lMinDCAzPositive; //in centimeters
Float_t lMinDCAxyNegative; //in centimeters
Float_t lMinDCAzNegative; //in centimeters
Float_t lMinDCAxyHFPions; //in centimeters
Float_t lMinDCAzHFPions ; //in centimeters

Float_t lMassWindowLambda;
Float_t lMassWindowXi;
Float_t lMassWindowXic;
Float_t lMassWindowXicc;

Float_t lMaxDCAV0Daughters; //in microns
Float_t lMaxDCACascadeDaughters; //in microns

Float_t lMinHFPionCMomentum; //in centimeters
Float_t lMinHFPionCCMomentum; //in centimeters
Float_t lMinXiTransverseMomentum;

Float_t lMaxTimeOffsetInnerTOF; //in picoseconds, for weak decay
Float_t lMaxTimeOffsetHFPions; //in picoseconds, for HF pions

Float_t lMaxDCAToPVXiCCandidate; //in microns, for separate XiC analysis
Float_t lMaxDCAToPVXiCCCandidate; //in microns

Float_t lMaxDCAXiCDaughters; //in microns
Float_t lMaxDCAXiCCDaughters; //in microns
//===============================================================

const Double_t lIBresolution = 0.00025f;
const Double_t lOBresolution = 0.00100f;

const Double_t liTOFresolution = 50; //ps
const Double_t loTOFresolution = 20; //ps
const Int_t lNStepsLIntegrator = 200;

using o2::its::MemoryParameters;
using o2::its::TrackingParameters;
using o2::itsmft::Hit;
using std::string;

using TrackingVertex = o2::dataformats::Vertex<o2::dataformats::TimeStamp<int>>;

constexpr bool kUseSmearing{true};

// Class to hold the track information for the O2 vertexing
class TrackAlice3 : public o2::track::TrackParCov
{
  using TimeEst = o2::dataformats::TimeStampWithError<float, float>;
  
public:
  TrackAlice3() = default;
  ~TrackAlice3() = default;
  TrackAlice3(const TrackAlice3& src) = default;
  TrackAlice3(const o2::track::TrackParCov& src, const float t = 0, const float te = 1, const int label = 0) : o2::track::TrackParCov(src), timeEst{t, te}, mLabel{label} {}
  const TimeEst& getTimeMUS() const { return timeEst; }
  const int mLabel;
  TimeEst timeEst; ///< time estimate in ns
};

struct particle {
  int pdg = 0;
  int pdgmother = 0;
  int motherID = 0;
  int nLayers = 0;
  float pt;
  float eta;
  float phi;
  float recoPt;
  float recoEta;
  float energyFirst;
  float energyLast;
  float vX;
  float vY;
  float vZ;
  int isReco = 0; // 0 = no, 1 = good, 2 = fake
};

/// get mass from TParticlePDG
double getMass(int input_pdg){
  double mass = 0;
  if(TDatabasePDG::Instance()){
    TParticlePDG* particle = TDatabasePDG::Instance()->GetParticle(input_pdg);
    if(particle)  mass = particle->Mass();
    else      std::cout << "===> particle mass equal to 0" << std::endl;
  }
  return mass;
}

float getDetLengthFromEta(const float eta, const float radius)
{
  return 10. * (10. + radius * std::cos(2 * std::atan(std::exp(-eta))));
}

Double_t Velocity(Double_t lMomentum, Double_t lMass){
  //Momentum p and mass m -> returns speed in centimeters per picosecond
  //Useful for TOF calculations
  Double_t lA = TMath::Power(lMomentum / lMass, 2);
  return 0.0299792458*TMath::Sqrt(lA/(1+lA));
}

Double_t TrackLength( o2::track::TrackParCov track, Double_t lX0, Double_t lX1 , Double_t lMagneticField ){
  std::array<float, 3> lPointN;
  std::array<float, 3> lPointNplus;
  Double_t lLength = 0.0;
  track.propagateTo(lX0, lMagneticField);
  for(Int_t iStep=1; iStep<lNStepsLIntegrator; iStep++){
    track.getXYZGlo(lPointN);
    Float_t lPosition = lX0 + (lX1-lX0)*((Float_t)(iStep))/((Float_t)(lNStepsLIntegrator-1));
    track.propagateTo(lPosition, lMagneticField);
    track.getXYZGlo(lPointNplus);
    lLength += std::hypot( lPointNplus[0]-lPointN[0], lPointNplus[1]-lPointN[1], lPointNplus[2]-lPointN[2] );
  }
  return lLength;
}

void run_analysis_example(TString lDataPath = "./", TString lLutPath =  "../")
{
  
  TStopwatch lWatchTracking, lWatchAnalysis, lWatchSmearing;
  
  std::cout << "\e[1;31m***********************************************\e[0;00m" << std::endl;
  std::cout << "\e[1;31m   ALICE 3 Strangeness tracking tool: XiCC      \e[0;00m" << std::endl;
  std::cout << "\e[1;31m***********************************************\e[0;00m" << std::endl;
  
  cout<<"Main configuration: "<<endl;
  cout<<"Data path for analysis.......: "<<lDataPath.Data()<<endl;
  cout<<"Data path for LUTs...........: "<<lLutPath.Data()<<endl;
  
  //Open Geometry, please
  o2::base::GeometryManager::loadGeometry(lDataPath.Data());
  
  //Open GRP
  const auto grp = o2::parameters::GRPObject::loadFrom(Form("%so2sim_grp.root",lDataPath.Data()));
  if (!grp) {
    LOG(FATAL) << "Cannot run w/o GRP object";
  }
  
  o2::base::Propagator::initFieldFromGRP(grp);
  auto field = static_cast<o2::field::MagneticField*>(TGeoGlobalMagField::Instance()->GetField());
  if (!field) {
    LOG(FATAL) << "Failed to load ma";
  }
  double origD[3] = {0., 0., 0.};
  
  //Operational parameters
  const Double_t lMagneticField = field->GetBz(0,0,0);
  cout<<"Magnetic field auto-detected to be "<<lMagneticField<<endl;
  
  if ( lMagneticField > 10 ) { //2 T case
    std::cout << "Precuts for 2.0 T \n";
    lMinV0Radius = lMasterSwitch*0.475; //in centimeters
    lMinXiRadius = lMasterSwitch*0.475; //in centimeters
    lMinDCAxyBachelor = lMasterSwitch*0.0040; //in centimeters
    lMinDCAzBachelor = lMasterSwitch*0.0040; //in centimeters
    lMinDCAxyPositive = lMasterSwitch*0.0050; //in centimeters
    lMinDCAzPositive = lMasterSwitch*0.0040; //in centimeters
    lMinDCAxyNegative = lMasterSwitch*0.0100; //in centimeters
    lMinDCAzNegative = lMasterSwitch*0.0050; //in centimeters
    lMinDCAxyHFPions = lMasterSwitch*0.0010; //in centimeters
    lMinDCAzHFPions  = lMasterSwitch*0.0010; //in centimeters
    
    lMassWindowLambda = 0.005;
    lMassWindowXi = 0.005;
    lMassWindowXic = 0.030;
    lMassWindowXicc = 0.65;
    
    lMaxDCAV0Daughters = 400; //in microns
    lMaxDCACascadeDaughters = 400; //in microns
    lMinHFPionCMomentum = lMasterSwitch*0.15;
    lMinHFPionCCMomentum = lMasterSwitch*0.3;
    lMinXiTransverseMomentum = 0.0;
    
    lMaxTimeOffsetInnerTOF = 75; //in picoseconds, for weak decay
    lMaxTimeOffsetHFPions = 75; //in picoseconds, for HF pions
    
    lMaxDCAToPVXiCCandidate = 100; //in microns
    lMaxDCAToPVXiCCCandidate = 100; //in microns
    
    lMaxDCAXiCDaughters = 50; //in microns
    lMaxDCAXiCCDaughters = 30; //in microns
  } else { // 0.5 T
    std::cout << "Precuts for 0.5 T \n";
    lMinV0Radius = lMasterSwitch*0.475; //in centimeters
    lMinXiRadius = lMasterSwitch*0.475; //in centimeters
    lMinDCAxyBachelor = lMasterSwitch*0.0040; //in centimeters
    lMinDCAzBachelor = lMasterSwitch*0.0040; //in centimeters
    lMinDCAxyPositive = lMasterSwitch*0.0050; //in centimeters
    lMinDCAzPositive = lMasterSwitch*0.0040; //in centimeters
    lMinDCAxyNegative = lMasterSwitch*0.0100; //in centimeters
    lMinDCAzNegative = lMasterSwitch*0.0050; //in centimeters
    lMinDCAxyHFPions = lMasterSwitch*0.0010; //in centimeters
    lMinDCAzHFPions  = lMasterSwitch*0.0010; //in centimeters
    
    lMassWindowLambda = 0.015;
    lMassWindowXi = 0.015;
    lMassWindowXic = 0.090;
    lMassWindowXicc = 0.65;
    
    lMaxDCAV0Daughters = 400; //in microns
    lMaxDCACascadeDaughters = 400; //in microns
    
    lMinHFPionCMomentum = lMasterSwitch*0.15;
    lMinHFPionCCMomentum = lMasterSwitch*0.3;
    lMinXiTransverseMomentum = 0.0;
    
    lMaxTimeOffsetInnerTOF = 75; //in picoseconds, for weak decay
    lMaxTimeOffsetHFPions = 75; //in picoseconds, for HF pions
    
    lMaxDCAToPVXiCCandidate = 100; //in microns
    lMaxDCAToPVXiCCCandidate = 100; //in microns
    
    lMaxDCAXiCDaughters = 50; //in microns
    lMaxDCAXiCCDaughters = 30; //in microns
  }
  
  Int_t Particle = 3122;
  Int_t lNLayers = 7;
  const string hitsFileName = Form("%so2sim_HitsTRK.root", lDataPath.Data());
  TChain mcTree("o2sim");
  mcTree.AddFile(Form("%so2sim_Kine.root", lDataPath.Data()));
  
  o2::dataformats::MCEventHeader* mcHead = nullptr;
  mcTree.SetBranchStatus("*", 0); //disable all branches
  mcTree.SetBranchStatus("MCTrack*", 1);
  mcTree.SetBranchStatus("MCEventHeader.*", 1);
  mcTree.SetBranchAddress("MCEventHeader.", &mcHead);
  
  std::vector<o2::MCTrack>* mcArr = nullptr;
  mcTree.SetBranchAddress("MCTrack", &mcArr);
  
  TChain itsHits("o2sim");
  
  itsHits.AddFile(hitsFileName.data());
  
  o2::its::Tracker tracker(new o2::its::TrackerTraitsCPU());
  tracker.setBz(lMagneticField);
  tracker.setCorrType(o2::base::PropagatorImpl<float>::MatCorrType::USEMatCorrTGeo);
  
  std::uint32_t roFrame;
  std::vector<Hit>* hits = nullptr;
  itsHits.SetBranchAddress("TRKHit", &hits);
  
  Double_t ptbinlimits[] ={ 0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8, 0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.,2.2,2.4,2.6,2.8,3.0,
    3.3,3.6,3.9,4.2,4.6,5,5.4,5.9, 6.5,7,7.5,8,8.5,9.2,10,11,12,13.5,15,17,20};
  Long_t ptbinnumb = sizeof(ptbinlimits)/sizeof(Double_t) - 1;
  
  TH1D dcav0("dcav0", ";DCA V0 daughters (#mum);Counts", 400, 0.0,400);
  TH1D cosPA("cosPA", ";CosPA;", 400, -1,1);
  TH1D v0radius("v0radius", ";v0radius;", 500, 0,50);
  TH1D hmassk0("hmassk0", ";Mass;", 2000,0,2);
  
  TH1D *hNVertices = new TH1D("hNVertices", "", 10,0,10);
  TH1D *hNTracks = new TH1D("hNTracks", "", 10000,0,10000);
  TH1D *hNLongTracks = new TH1D("hNLongTracks", "", 10000,0,10000);
  TH1D *hNLongPrimaryTracks = new TH1D("hNLongPrimaryTracks", "", 10000,0,10000);
  TH1D *hNPrimaryTracks = new TH1D("hNPrimaryTracks", "", 10000,0,10000);
  
  TH1D *hGenerated = new TH1D("hGenerated", "", ptbinnumb, ptbinlimits);
  TH1D *hPt = new TH1D("hPt", "", ptbinnumb, ptbinlimits);
  TH2D *hMassVsPt = new TH2D("hMassVsPt", "", 150,0,15,2000,0,2);
  TH2D *hDCADauVsPt = new TH2D("hDCADauVsPt", "", 150,0,15,600,0,600);
  TH2D *hPAVsPt = new TH2D("hPAVsPt", "", 150,0,15,200,0,0.5);
  
  TProfile *hDCAProf = new TProfile("hDCAProf","",ptbinnumb, ptbinlimits);
  TProfile *hPAProf = new TProfile("hPAProf","",ptbinnumb, ptbinlimits);
  
  TH1D *hCascFinding = new TH1D("hCascFinding", "", 10,0,10);
  TH1D *hMassXi = new TH1D("hMassXi", "", 200, 1.672-0.050, 1.672+0.050);
  
  TH1D dcacasc("dcacasc", ";DCA V0 daughters (#mum);Counts", 400, 0.0,400);
  TProfile *hCascDCAProf = new TProfile("hCascDCAProf","",ptbinnumb, ptbinlimits);
  TH1D *hPtCascade = new TH1D("hPtCascade", "", 100,0,10);
  TH2D *hCascadeMassVsPt = new TH2D("hCascadeMassVsPt", "", 150,0,15,2000,0,2);
  TH1D* hCascadeCosPA = new TH1D("hCascadeCosPA", "", 400, -1, 1);
  TProfile *hCascadePAProf = new TProfile("hCascadePAProf","",ptbinnumb, ptbinlimits);
  
  TH1D *hTrackCount = new TH1D("hTrackCount", "", 5,0,5);
  TH1D *hCombinatorics = new TH1D("hCombinatorics", "",2,0,2);
  TH1D *hCombinatoricsV0 = new TH1D("hCombinatoricsV0", "",5,0,5);
  
  TH1D *hHitXa = new TH1D("hHitXa", "", 2000,-10,10);
  TH1D *hHitYa = new TH1D("hHitYa", "", 2000,-10,10);
  TH1D *hHitZa = new TH1D("hHitZa", "", 2000,-10,10);
  TH1D *hHitNumber = new TH1D("hHitNumber", "", 10,0,10);
  
  TH1D *hXiR2D = new TH1D("hXiR2D", "", 2000,0,100);
  TH1D *hLambdaR2D = new TH1D("hLambdaR2D", "", 2000,0,100);
  Double_t lRadii[] = {0.0f,0.5f,1.2f, 2.5f, 3.75f, 7.0f, 12.0f, 20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  TH1D *hXiR2Dbinned = new TH1D("hXiR2Dbinned", "", 12, lRadii);
  TH1D *hLambdaR2Dbinned = new TH1D("hLambdaR2Dbinned", "", 12, lRadii);
  
  TH2D *hPtEtaGeneratedXi = new TH2D("hPtEtaGeneratedXi", "", 200,0,20,30,-1.5,1.5);
  TH2D *hPtEtaGeneratedXiC = new TH2D("hPtEtaGeneratedXiC", "", 200,0,20,30,-1.5,1.5);
  TH2D *hPtEtaGeneratedXiCC = new TH2D("hPtEtaGeneratedXiCC", "", 200,0,20,30,-1.5,1.5);
  
  TH2D *hPtYGeneratedXi = new TH2D("hPtYGeneratedXi", "", 200,0,20,30,-1.5,1.5);
  TH2D *hPtYGeneratedXiC = new TH2D("hPtYGeneratedXiC", "", 200,0,20,30,-1.5,1.5);
  TH2D *hPtYGeneratedXiCC = new TH2D("hPtYGeneratedXiCC", "", 200,0,20,30,-1.5,1.5);
  
  Long_t lMaxMult = 10000;
  
  TH2D *hPtMultGeneratedXi_AllEta = new TH2D("hPtMultGeneratedXi_AllEta", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiC_AllEta = new TH2D("hPtMultGeneratedXiC_AllEta", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiCC_AllEta = new TH2D("hPtMultGeneratedXiCC_AllEta", "", 200,0,20,lMaxMult,0,lMaxMult);
  
  TH2D *hPtMultGeneratedXi_AllY = new TH2D("hPtMultGeneratedXi_AllY", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiC_AllY = new TH2D("hPtMultGeneratedXiC_AllY", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiCC_AllY = new TH2D("hPtMultGeneratedXiCC_AllY", "", 200,0,20,lMaxMult,0,lMaxMult);
  
  TH2D *hPtMultGeneratedXi_Eta5 = new TH2D("hPtMultGeneratedXi_Eta5", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiC_Eta5 = new TH2D("hPtMultGeneratedXiC_Eta5", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiCC_Eta5 = new TH2D("hPtMultGeneratedXiCC_Eta5", "", 200,0,20,lMaxMult,0,lMaxMult);
  
  TH2D *hPtMultGeneratedXi_Y5 = new TH2D("hPtMultGeneratedXi_Y5", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiC_Y5 = new TH2D("hPtMultGeneratedXiC_Y5", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiCC_Y5 = new TH2D("hPtMultGeneratedXiCC_Y5", "", 200,0,20,lMaxMult,0,lMaxMult);
  
  TH2D *hPtMultGeneratedXi_Eta10 = new TH2D("hPtMultGeneratedXi_Eta10", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiC_Eta10 = new TH2D("hPtMultGeneratedXiC_Eta10", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiCC_Eta10 = new TH2D("hPtMultGeneratedXiCC_Eta10", "", 200,0,20,lMaxMult,0,lMaxMult);
  
  TH2D *hPtMultGeneratedXi_Y10 = new TH2D("hPtMultGeneratedXi_Y10", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiC_Y10 = new TH2D("hPtMultGeneratedXiC_Y10", "", 200,0,20,lMaxMult,0,lMaxMult);
  TH2D *hPtMultGeneratedXiCC_Y10 = new TH2D("hPtMultGeneratedXiCC_Y10", "", 200,0,20,lMaxMult,0,lMaxMult);
  
  TH1D* hSkimmingLosses = new TH1D("hSkimmingLosses", "", 50, 0, 50);
  int iBin=1;
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinV0Radius");             // 0.5 -> l.1925(7)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinXiRadius");             // 1.5 -> l.2061(10)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinDCABachelor");          // 2.5 -> l.1706(3)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinDCAPositive");          // 3.5 -> l.1678(1)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinDCANegative");          // 4.5 -> l.1684(2)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinDCAHFPions");           // 5.5 -> l.1749(5)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMassWindowLambda");        // 6.5 -> l.1941(8)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMassWindowXi");            // 7.5 -> l.2097(11)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMassWindowXic");           // 8.5 -> l.2621(15)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMassWindowXicc");          // 9.5 -> l.2828(19)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMaxDCAV0Daughters");       //10.5 -> l.1898(6)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMaxDCACascadeDaughters");  //11.5 -> l.2057(9)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinXiTransverseMomentum"); //12.5 -> l.2213(12)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMaxTimeOffsetInnerTOF");   //13.5 -> l.2468(13)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMaxTimeOffsetHFPions");    //14.5 -> l.1738(4)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMaxDCAToPVXiCCCandidate"); //15.5 -> l.2877(20)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMaxDCAXiCDaughters");      //16.5 -> l.2628(16)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMaxDCAXiCCDaughters");     //17.5 -> l.2832(17)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinHFPionCMomentum");      //18.5 -> l.2614(14)
  hSkimmingLosses->GetXaxis()->SetBinLabel(iBin++,"lMinHFPionCCMomentum");     //19.5 -> l.2798(18)
  
  
  TH1D *hTime = new TH1D("hTime", "Processing time", 6, 0, 6);
  hTime->GetXaxis()->SetBinLabel(1, "Smearing real time");
  hTime->GetXaxis()->SetBinLabel(2, "Tracking real time");
  hTime->GetXaxis()->SetBinLabel(3, "Analysis real time");
  hTime->GetXaxis()->SetBinLabel(4, "Smearing CPU time");
  hTime->GetXaxis()->SetBinLabel(5, "Tracking CPU time");
  hTime->GetXaxis()->SetBinLabel(6, "Analysis CPU time");
  
  TH1D *hPartialTransportDebug = new TH1D("hPartialTransportDebug", "", 6,0,6);
  hPartialTransportDebug->GetXaxis()->SetBinLabel(1, "All particles");
  hPartialTransportDebug->GetXaxis()->SetBinLabel(2, "Not tranported");
  hPartialTransportDebug->GetXaxis()->SetBinLabel(3, "Successfully smeared");
  hPartialTransportDebug->GetXaxis()->SetBinLabel(4, "Fully tracked particles");
  
  TH1D *hQADCAxy = new TH1D("hQADCAxy","", 1000,-500,500);
  TH1D *hQADCAz = new TH1D("hQADCAz","", 1000,-500,500);
  
  TH1D *hQAMCNch = new TH1D("hQAMCNch", "", 6000, 0, 6000);
  
  TH2D *hQANchCorrelation = new TH2D("hQANchCorrelation", "", 600, 0, 12000, 600, 0, 12000);


  // PCM related histograms
  const float r = 130.;
 //    const float r = 15.;
  const float maxZ = 150.;

  TH1D *hInvMassSame = new TH1D("hInvMassSame", "invariant mass of e^{+}/e^{-} with same photon mother;m (GeV/c);N / N_{ev}", 200, 0., 2.);
  TH1D *hPhotonPt = new TH1D("hPhotonPt", "reconstructed Photon pT  e^{+}/e^{-} with same photon mother;p_{T} (GeV/c);N / N_{ev}", 500, 0., 10.);
  TH1D *hPhotonPtMC = new TH1D("hPhotonPtMC", "MC Photon pT (recTracks) e^{+}/e^{-} with same photon mother;p_{T} (GeV/c);N / N_{ev}", 500, 0., 10.);
  TH2D *hPhotonPtRes = new TH2D("hPhotonPtRes", "Photon pT resolution(recTracks) e^{+}/e^{-} with same photon mother;p_{T} (GeV/c);delta pT/pT", 500, 0., 10.,1000,-1., 1.);
  TH2D *hPhotonPzRes = new TH2D("hPhotonPzRes", "Photon pz resolution(recTracks) e^{+}/e^{-} with same photon mother;p_{T} (GeV/c);delta pT/pT", 500, 0., 10.,1000,-1., 1.);
  TH2D *hPhotonPRes = new TH2D("hPhotonPRes", "Photon p resolution(recTracks) e^{+}/e^{-} with same photon mother;p_{T} (GeV/c);delta pT/pT", 500, 0., 10.,1000,-1., 1.);
  TH2D *hVertex = new TH2D("hVertex", "prod. vertices of e^{+}/e^{-} with photon mother;x (cm);y (cm)", 1000, -r, r, 1000, -r, r);
  TH2D *hVertexR = new TH2D("hVertexR", "prod. vertices of e^{+}/e^{-} with photon mother;z (cm);r (cm)", 1000, -maxZ, maxZ, 1000, 0., r);

  //Define o2 fitter, 2-prong
  o2::vertexing::DCAFitterN<2> fitterV0, fitterCasc, fitterCascCC;
  o2::vertexing::DCAFitterN<3> retrofitter, fitterCascC;
  
  fitterV0.setBz(lMagneticField);
  fitterV0.setPropagateToPCA(true);
  fitterV0.setMaxR(200.);
  fitterV0.setMinParamChange(1e-5);
  fitterV0.setMinRelChi2Change(0.9);
  fitterV0.setMaxDZIni(1e9);
  fitterV0.setMaxChi2(1e9);
  fitterV0.setUseAbsDCA(true);
  
  fitterCasc.setBz(lMagneticField);
  fitterCasc.setPropagateToPCA(true);
  fitterCasc.setMaxR(200.);
  fitterCasc.setMinParamChange(1e-3);
  fitterCasc.setMinRelChi2Change(0.9);
  fitterCasc.setMaxDZIni(1e9);
  fitterCasc.setMaxChi2(1e9);
  fitterCasc.setUseAbsDCA(true);
  
  fitterCascC.setBz(lMagneticField);
  fitterCascC.setPropagateToPCA(true);
  fitterCascC.setMaxR(200.);
  fitterCascC.setMinParamChange(1e-3);
  fitterCascC.setMinRelChi2Change(0.9);
  fitterCascC.setMaxDZIni(1e9);
  fitterCascC.setMaxChi2(1e9);
  fitterCascC.setUseAbsDCA(true);
  
  fitterCascCC.setBz(lMagneticField);
  fitterCascCC.setPropagateToPCA(true);
  fitterCascCC.setMaxR(200.);
  fitterCascCC.setMinParamChange(1e-3);
  fitterCascCC.setMinRelChi2Change(0.9);
  fitterCascCC.setMaxDZIni(1e9);
  fitterCascCC.setMaxChi2(1e9);
  fitterCascCC.setUseAbsDCA(true);
  
  //Atempt retro-fit: fit 3 tracks to Xi
  retrofitter.setBz(lMagneticField);
  retrofitter.setPropagateToPCA(true);
  retrofitter.setMaxR(200.);
  retrofitter.setMinParamChange(1e-3);
  retrofitter.setMinRelChi2Change(0.9);
  retrofitter.setMaxDZIni(1e9);
  retrofitter.setMaxChi2(1e9);
  retrofitter.setUseAbsDCA(true);
  
  Int_t fParticle, fMinNLayerReco;
  Double_t fDCAV0Dau, fPA, fV0Radius, fMass, fPt, fPtMC, fPtMCMother;
  
  TFile *fileTree = new TFile("xicc.treeoutput.root", "RECREATE", "", 109);
  
  TH1D *hEventCounter = new TH1D("hEventCounter", "", 1,0,1);
  TH1D *hEventCounterWithVertex = new TH1D("hEventCounterWithVertex", "", 1,0,1);
  TH1D *hVertexZ = new TH1D("hVertexZ", "", 100, -15,15);
  TH1D *hXiCGeneratedPt = new TH1D("hXiCGeneratedPt", "", 200,0,20);
  TH1D *hXiCCGeneratedPt = new TH1D("hXiCCGeneratedPt", "", 200,0,20);
  
  TH1D *hNDirectTrackingLayers = new TH1D("hNDirectTrackingLayers", "",12,0,12);
  TH1D *hNV0DauLayers = new TH1D("hNV0DauLayers", "",12,0,12);
  
  //Declare
  Float_t fPtXi=0, fPtMCXi=0;
  Float_t fXicPt=0, fXicPtMC=0;
  
  Bool_t fTrueXi = kFALSE;
  Bool_t fTrueXic = kFALSE;
  Bool_t fTrueXicc = kFALSE;
  
  Float_t fXiDCAxyToPV=0;
  Float_t fXiDCAzToPV=0;
  Float_t fXicDCAxyToPV=0;
  Float_t fXicDCAzToPV=0;
  Float_t fXiccDCAxyToPV=0;
  Float_t fXiccDCAzToPV=0;
  
  Int_t fXiHitsAdded=0;;
  Float_t fXicMass=0;
  
  Float_t fPic1DCAxyToPV =0;
  Float_t fPic1DCAzToPV =0;
  Float_t fPic2DCAxyToPV =0;
  Float_t fPic2DCAzToPV =0;
  
  Float_t fV0DauDCA = 0;
  Float_t fXiDauDCA = 0;
  
  Float_t fXiDecayRadius = 0;
  Float_t fV0DecayRadius = 0;
  Float_t fXiDecayRadiusMC = 0;
  Float_t fV0DecayRadiusMC = 0;
  
  Float_t fLambdaMass = 0, fXiMass = 0;
  
  Float_t fXicDecayRadius = 0;
  Float_t fXicDecayDistanceFromPV = 0;
  Float_t fXicDaughterDCA = 0;
  Float_t fXiccDecayRadius = 0;
  Float_t fXiccDecayDistanceFromPV = 0;
  Float_t fXiccDaughterDCA = 0;
  
  Float_t fPrimaryVertexX = 0, fPrimaryVertexY = 0, fPrimaryVertexZ = 0;
  Float_t fXicVertexX = 0, fXicVertexY = 0, fXicVertexZ = 0;
  Float_t fXicVertexXMC = 0, fXicVertexYMC = 0, fXicVertexZMC = 0;
  Float_t fXiccMass=0;
  
  Float_t fPiccDCAxyToPV, fPiccDCAzToPV;
  
  Bool_t fFirstCandidateXiC, fFirstCandidateXiCC;
  
  Int_t fNTracks = 0, fNLongTracks = 0, fNLongPrimaryTracks = 0, fNPrimaryTracks = 0;
  
  TTree *fTreeCandidates = new TTree ( "fTreeCandidates", "Event Characterization Tree" ) ;
  fTreeCandidates->Branch ("fNTracks",    &fNTracks,    "fNTracks/I"    );
  fTreeCandidates->Branch ("fNLongTracks",    &fNLongTracks,    "fNLongTracks/I"    );
  fTreeCandidates->Branch ("fNLongPrimaryTracks",    &fNLongPrimaryTracks,    "fNLongPrimaryTracks/I"    );
  fTreeCandidates->Branch ("fNPrimaryTracks",    &fNPrimaryTracks,    "fNPrimaryTracks/I"    );
  
  Float_t fPtXiC, fPtMCXiC, fPtXiCC, fPtMCXiCC;
  Float_t fPXiC, fPMCXiC, fPXiCC, fPMCXiCC;
  
  fTreeCandidates->Branch ("fPtXi",    &fPtXi,    "fPtXi/F"    );
  fTreeCandidates->Branch ("fPtXiC",  &fPtXiC,  "fPtXiC/F"  );
  fTreeCandidates->Branch ("fPtXiCC",  &fPtXiCC,  "fPtXiCC/F"  );
  fTreeCandidates->Branch ("fPtMCXi",  &fPtMCXi,  "fPtMCXi/F"  );
  fTreeCandidates->Branch ("fPtMCXiC",  &fPtMCXiC,  "fPtMCXiC/F"  );
  fTreeCandidates->Branch ("fPtMCXiCC",  &fPtMCXiCC,  "fPtMCXiCC/F"  );
  
  fTreeCandidates->Branch ("fPXiC",  &fPXiC,  "fPXiC/F"  );
  fTreeCandidates->Branch ("fPXiCC",  &fPXiCC,  "fPXiCC/F"  );
  fTreeCandidates->Branch ("fPMCXiC",  &fPMCXiC,  "fPMCXiC/F"  );
  fTreeCandidates->Branch ("fPMCXiCC",  &fPMCXiCC,  "fPMCXiCC/F"  );
  
  fTreeCandidates->Branch ("fXiDecayRadiusMC",  &fXiDecayRadiusMC,  "fXiDecayRadiusMC/F"  );
  fTreeCandidates->Branch ("fV0DecayRadiusMC",  &fV0DecayRadiusMC,  "fV0DecayRadiusMC/F"  );
  fTreeCandidates->Branch ("fXiDecayRadius",  &fXiDecayRadius,  "fXiDecayRadius/F"  );
  fTreeCandidates->Branch ("fV0DecayRadius",  &fV0DecayRadius,  "fV0DecayRadius/F"  );
  
  fTreeCandidates->Branch ("fXiDCAxyToPV",  &fXiDCAxyToPV,  "fXiDCAxyToPV/F"  );
  fTreeCandidates->Branch ("fXiDCAzToPV",  &fXiDCAzToPV,  "fXiDCAzToPV/F"  );
  fTreeCandidates->Branch ("fXicDCAxyToPV",  &fXicDCAxyToPV,  "fXicDCAxyToPV/F"  );
  fTreeCandidates->Branch ("fXicDCAzToPV",  &fXicDCAzToPV,  "fXicDCAzToPV/F"  );
  fTreeCandidates->Branch ("fXiccDCAxyToPV",  &fXiccDCAxyToPV,  "fXiccDCAxyToPV/F"  );
  fTreeCandidates->Branch ("fXiccDCAzToPV",  &fXiccDCAzToPV,  "fXiccDCAzToPV/F"  );
  
  fTreeCandidates->Branch ("fPic1DCAxyToPV",  &fPic1DCAxyToPV,  "fPic1DCAxyToPV/F"  );
  fTreeCandidates->Branch ("fPic1DCAzToPV",  &fPic1DCAzToPV,  "fPic1DCAzToPV/F"  );
  fTreeCandidates->Branch ("fPic2DCAxyToPV",  &fPic2DCAxyToPV,  "fPic2DCAxyToPV/F"  );
  fTreeCandidates->Branch ("fPic2DCAzToPV",  &fPic2DCAzToPV,  "fPic2DCAzToPV/F"  );
  fTreeCandidates->Branch ("fPiccDCAxyToPV",  &fPiccDCAxyToPV,  "fPiccDCAxyToPV/F"  );
  fTreeCandidates->Branch ("fPiccDCAzToPV",  &fPiccDCAzToPV,  "fPiccDCAzToPV/F"  );
  
  fTreeCandidates->Branch ("fV0DauDCA",  &fV0DauDCA,  "fV0DauDCA/F"  );
  fTreeCandidates->Branch ("fXiDauDCA",  &fXiDauDCA,  "fXiDauDCA/F"  );
  fTreeCandidates->Branch ("fTrueXi",  &fTrueXi,  "fTrueXi/O"  );
  fTreeCandidates->Branch ("fTrueXic",  &fTrueXic,  "fTrueXic/O"  );
  fTreeCandidates->Branch ("fTrueXicc",  &fTrueXicc,  "fTrueXicc/O"  );
  fTreeCandidates->Branch ("fXiHitsAdded",  &fXiHitsAdded,  "fXiHitsAdded/I"  );
  
  fTreeCandidates->Branch ("fLambdaMass",  &fLambdaMass,  "fLambdaMass/F"  );
  fTreeCandidates->Branch ("fXiMass",  &fXiMass,  "fXiMass/F"  );
  fTreeCandidates->Branch ("fXicMass",  &fXicMass,  "fXicMass/F"  );
  fTreeCandidates->Branch ("fXiccMass",  &fXiccMass,  "fXiccMass/F"  );
  
  fTreeCandidates->Branch ("fXicDecayRadius",  &fXicDecayRadius,  "fXicDecayRadius/F"  );
  fTreeCandidates->Branch ("fXicDecayDistanceFromPV",  &fXicDecayDistanceFromPV,  "fXicDecayDistanceFromPV/F"  );
  fTreeCandidates->Branch ("fXicDaughterDCA",  &fXicDaughterDCA,  "fXicDaughterDCA/F"  );
  fTreeCandidates->Branch ("fXiccDecayRadius",  &fXiccDecayRadius,  "fXiccDecayRadius/F"  );
  fTreeCandidates->Branch ("fXiccDecayDistanceFromPV",  &fXiccDecayDistanceFromPV,  "fXiccDecayDistanceFromPV/F"  );
  fTreeCandidates->Branch ("fXiccDaughterDCA",  &fXiccDaughterDCA,  "fXiccDaughterDCA/F"  );
  
  fTreeCandidates->Branch ("fXicVertexX",  &fXicVertexX,  "fXicVertexX/F"  );
  fTreeCandidates->Branch ("fXicVertexY",  &fXicVertexY,  "fXicVertexY/F"  );
  fTreeCandidates->Branch ("fXicVertexZ",  &fXicVertexZ,  "fXicVertexZ/F"  );
  fTreeCandidates->Branch ("fXicVertexXMC",  &fXicVertexXMC,  "fXicVertexXMC/F"  );
  fTreeCandidates->Branch ("fXicVertexYMC",  &fXicVertexYMC,  "fXicVertexYMC/F"  );
  fTreeCandidates->Branch ("fXicVertexZMC",  &fXicVertexZMC,  "fXicVertexZMC/F"  );
  
  fTreeCandidates->Branch ("fFirstCandidateXiC",  &fFirstCandidateXiC,  "fFirstCandidateXiC/O"  );
  fTreeCandidates->Branch ("fFirstCandidateXiCC",  &fFirstCandidateXiCC,  "fFirstCandidateXiCC/O"  );
  
  //PDG Codes
  Int_t fPiccMotherPDG, fPic1MotherPDG, fPic2MotherPDG;
  Float_t fPiccMotherPt, fPic1MotherPt, fPic2MotherPt;
  Int_t fPiccMotherNChain, fPic1MotherNChain, fPic2MotherNChain;
  Int_t fPiccMotherChain[20], fPic1MotherChain[20], fPic2MotherChain[20];
  
  Float_t fXiCCtoXiCLength, fXiCtoXiLength;
  
  fTreeCandidates->Branch ("fXiCCtoXiCLength",  &fXiCCtoXiCLength,  "fXiCCtoXiCLength/F"  );
  fTreeCandidates->Branch ("fXiCtoXiLength",  &fXiCtoXiLength,  "fXiCtoXiLength/F"  );
  
  Float_t fBachelorDCAxy, fBachelorDCAz, fNegativeDCAxy, fNegativeDCAz, fPositiveDCAxy, fPositiveDCAz;
  
  fTreeCandidates->Branch ("fBachelorDCAxy",  &fBachelorDCAxy,  "fBachelorDCAxy/F"  );
  fTreeCandidates->Branch ("fBachelorDCAz",  &fBachelorDCAz,  "fBachelorDCAz/F"  );
  fTreeCandidates->Branch ("fNegativeDCAxy",  &fNegativeDCAxy,  "fNegativeDCAxy/F"  );
  fTreeCandidates->Branch ("fNegativeDCAz",  &fNegativeDCAz,  "fNegativeDCAz/F"  );
  fTreeCandidates->Branch ("fPositiveDCAxy",  &fPositiveDCAxy,  "fPositiveDCAxy/F"  );
  fTreeCandidates->Branch ("fPositiveDCAz",  &fPositiveDCAz,  "fPositiveDCAz/F"  );
  
  Float_t fV0DCAxyToPV, fV0DCAzToPV, fV0DecayLength, fXiDecayLength;
  fTreeCandidates->Branch ("fV0DCAxyToPV",  &fV0DCAxyToPV,  "fV0DCAxyToPV/F"  );
  fTreeCandidates->Branch ("fV0DCAzToPV",  &fV0DCAzToPV,  "fV0DCAzToPV/F"  );
  fTreeCandidates->Branch ("fV0DecayLength",  &fV0DecayLength,  "fV0DecayLength/F"  );
  fTreeCandidates->Branch ("fXiDecayLength",  &fXiDecayLength,  "fXiDecayLength/F"  );
  
  //Six prong momenta for efficiency composition
  Float_t fPiCCPt, fPiC1Pt, fPiC2Pt, fBachelorPt, fPositivePt, fNegativePt;
  fTreeCandidates->Branch ("fPiC1Pt",  &fPiC1Pt,  "fPiC1Pt/F"  );
  fTreeCandidates->Branch ("fPiC2Pt",  &fPiC2Pt,  "fPiC2Pt/F"  );
  fTreeCandidates->Branch ("fPiCCPt",  &fPiCCPt,  "fPiCCPt/F"  );
  fTreeCandidates->Branch ("fBachelorPt",  &fBachelorPt,  "fBachelorPt/F"  );
  fTreeCandidates->Branch ("fPositivePt",  &fPositivePt,  "fPositivePt/F"  );
  fTreeCandidates->Branch ("fNegativePt",  &fNegativePt,  "fNegativePt/F"  );
  
  Float_t fV0TotalMomentum, fXiTotalMomentum;
  fTreeCandidates->Branch ("fV0TotalMomentum",  &fV0TotalMomentum,  "fV0TotalMomentum/F"  );
  fTreeCandidates->Branch ("fXiTotalMomentum",  &fXiTotalMomentum,  "fXiTotalMomentum/F"  );
  
  Int_t fPiC1Clusters, fPiC2Clusters, fPiCCClusters, fNegativeClusters, fPositiveClusters, fBachelorClusters;
  Float_t fPiC1Chisquare, fPiC2Chisquare, fPiCCChisquare, fNegativeChisquare, fPositiveChisquare, fBachelorChisquare;
  
  fTreeCandidates->Branch ("fNegativeClusters",  &fNegativeClusters,  "fNegativeClusters/I"  );
  fTreeCandidates->Branch ("fPositiveClusters",  &fPositiveClusters,  "fPositiveClusters/I"  );
  fTreeCandidates->Branch ("fBachelorClusters",  &fBachelorClusters,  "fBachelorClusters/I"  );
  
  fTreeCandidates->Branch ("fNegativeChisquare",  &fNegativeChisquare,  "fNegativeChisquare/F"  );
  fTreeCandidates->Branch ("fPositiveChisquare",  &fPositiveChisquare,  "fPositiveChisquare/F"  );
  fTreeCandidates->Branch ("fBachelorChisquare",  &fBachelorChisquare,  "fBachelorChisquare/F"  );
  
  TLorentzVector *lVector = new TLorentzVector();
  Float_t fPiCCEta, fPiC1Eta, fPiC2Eta, fNegativeEta, fPositiveEta, fBachelorEta;
  fTreeCandidates->Branch ("fPiCCEta",  &fPiCCEta,  "fPiCCEta/F"  );
  fTreeCandidates->Branch ("fPiC1Eta",  &fPiC1Eta,  "fPiC1Eta/F"  );
  fTreeCandidates->Branch ("fPiC2Eta",  &fPiC2Eta,  "fPiC2Eta/F"  );
  fTreeCandidates->Branch ("fNegativeEta",  &fNegativeEta,  "fNegativeEta/F"  );
  fTreeCandidates->Branch ("fPositiveEta",  &fPositiveEta,  "fPositiveEta/F"  );
  fTreeCandidates->Branch ("fBachelorEta",  &fBachelorEta,  "fBachelorEta/F"  );
  
  Float_t fXiEta, fXiCEta, fXiCCEta;
  fTreeCandidates->Branch ("fXiEta",  &fXiEta,  "fXiEta/F"  );
  fTreeCandidates->Branch ("fXiCEta",  &fXiCEta,  "fXiCEta/F"  );
  fTreeCandidates->Branch ("fXiCCEta",  &fXiCCEta,  "fXiCCEta/F"  );
  
  Bool_t fPiccUsed;
  Int_t fPicUsed;
  fTreeCandidates->Branch ("fPiccUsed",  &fPiccUsed,  "fPiccUsed/O"  );
  fTreeCandidates->Branch ("fPicUsed",  &fPicUsed,  "fPicUsed/I"  );
  
  Float_t fBachelorTOFSignal, fPositiveTOFSignal, fNegativeTOFSignal, fPic1TOFSignal, fPic2TOFSignal, fPiccTOFSignal;
  Float_t fBachelorTOFSignalMC, fPositiveTOFSignalMC, fNegativeTOFSignalMC, fPic1TOFSignalMC, fPic2TOFSignalMC, fPiccTOFSignalMC;
  Float_t fBachelorExpectedSignal, fPositiveExpectedSignal, fNegativeExpectedSignal, fPic1ExpectedSignal, fPic2ExpectedSignal, fPiccExpectedSignal;
  Float_t fBachelorExpectedSignalFromPV, fPositiveExpectedSignalFromPV, fNegativeExpectedSignalFromPV;
  
  Float_t fBachelorLength, fNegativeLength, fPositiveLength, fCascadeLength, fV0Length;
  Float_t fBachelorLife, fNegativeLife, fPositiveLife, fCascadeLife, fV0Life;
  
  Int_t fPiccPDG, fPic1PDG, fPic2PDG, fNegativePDG, fPositivePDG, fBachelorPDG;
  fTreeCandidates->Branch ("fPiccPDG",  &fPiccPDG,  "fPiccPDG/I"  );
  fTreeCandidates->Branch ("fPic1PDG",  &fPic1PDG,  "fPic1PDG/I"  );
  fTreeCandidates->Branch ("fPic2PDG",  &fPic2PDG,  "fPic2PDG/I"  );
  fTreeCandidates->Branch ("fNegativePDG",  &fNegativePDG,  "fNegativePDG/I"  );
  fTreeCandidates->Branch ("fPositivePDG",  &fPositivePDG,  "fPositivePDG/I"  );
  fTreeCandidates->Branch ("fBachelorPDG",  &fBachelorPDG,  "fBachelorPDG/I"  );
  
  //INNER TOF
  Float_t fBachelorInnerTOF20Signal, fPositiveInnerTOF20Signal, fNegativeInnerTOF20Signal, fPic1InnerTOF20Signal, fPic2InnerTOF20Signal, fPiccInnerTOF20Signal;
  Float_t fBachelorInnerTOF50Signal, fPositiveInnerTOF50Signal, fNegativeInnerTOF50Signal, fPic1InnerTOF50Signal, fPic2InnerTOF50Signal, fPiccInnerTOF50Signal;
  Float_t fBachelorInnerTOFSignalMC, fPositiveInnerTOFSignalMC, fNegativeInnerTOFSignalMC, fPic1InnerTOFSignalMC, fPic2InnerTOFSignalMC, fPiccInnerTOFSignalMC;
  Float_t fBachelorInnerExpectedSignal, fPositiveInnerExpectedSignal, fNegativeInnerExpectedSignal, fPic1InnerExpectedSignal, fPic2InnerExpectedSignal, fPiccInnerExpectedSignal;
  
  fTreeCandidates->Branch ("fBachelorInnerTOF20Signal",  &fBachelorInnerTOF20Signal,  "fBachelorInnerTOF20Signal/F"  );
  fTreeCandidates->Branch ("fPositiveInnerTOF20Signal",  &fPositiveInnerTOF20Signal,  "fPositiveInnerTOF20Signal/F"  );
  fTreeCandidates->Branch ("fNegativeInnerTOF20Signal",  &fNegativeInnerTOF20Signal,  "fNegativeInnerTOF20Signal/F"  );
  fTreeCandidates->Branch ("fPic1InnerTOF20Signal",  &fPic1InnerTOF20Signal,  "fPic1InnerTOF20Signal/F"  );
  fTreeCandidates->Branch ("fPic2InnerTOF20Signal",  &fPic2InnerTOF20Signal,  "fPic2InnerTOF20Signal/F"  );
  fTreeCandidates->Branch ("fPiccInnerTOF20Signal",  &fPiccInnerTOF20Signal,  "fPiccInnerTOF20Signal/F"  );
  
  fTreeCandidates->Branch ("fBachelorInnerTOF50Signal",  &fBachelorInnerTOF50Signal,  "fBachelorInnerTOF50Signal/F"  );
  fTreeCandidates->Branch ("fPositiveInnerTOF50Signal",  &fPositiveInnerTOF50Signal,  "fPositiveInnerTOF50Signal/F"  );
  fTreeCandidates->Branch ("fNegativeInnerTOF50Signal",  &fNegativeInnerTOF50Signal,  "fNegativeInnerTOF50Signal/F"  );
  fTreeCandidates->Branch ("fPic1InnerTOF50Signal",  &fPic1InnerTOF50Signal,  "fPic1InnerTOF50Signal/F"  );
  fTreeCandidates->Branch ("fPic2InnerTOF50Signal",  &fPic2InnerTOF50Signal,  "fPic2InnerTOF50Signal/F"  );
  fTreeCandidates->Branch ("fPiccInnerTOF50Signal",  &fPiccInnerTOF50Signal,  "fPiccInnerTOF50Signal/F"  );
  
  fTreeCandidates->Branch ("fBachelorInnerTOFSignalMC",  &fBachelorInnerTOFSignalMC,  "fBachelorInnerTOFSignalMC/F"  );
  fTreeCandidates->Branch ("fPositiveInnerTOFSignalMC",  &fPositiveInnerTOFSignalMC,  "fPositiveInnerTOFSignalMC/F"  );
  fTreeCandidates->Branch ("fNegativeInnerTOFSignalMC",  &fNegativeInnerTOFSignalMC,  "fNegativeInnerTOFSignalMC/F"  );
  fTreeCandidates->Branch ("fPic1InnerTOFSignalMC",  &fPic1InnerTOFSignalMC,  "fPic1InnerTOFSignalMC/F"  );
  fTreeCandidates->Branch ("fPic2InnerTOFSignalMC",  &fPic2InnerTOFSignalMC,  "fPic2InnerTOFSignalMC/F"  );
  fTreeCandidates->Branch ("fPiccInnerTOFSignalMC",  &fPiccInnerTOFSignalMC,  "fPiccInnerTOFSignalMC/F"  );
  
  fTreeCandidates->Branch ("fBachelorInnerExpectedSignal",  &fBachelorInnerExpectedSignal,  "fBachelorInnerExpectedSignal/F"  );
  fTreeCandidates->Branch ("fPositiveInnerExpectedSignal",  &fPositiveInnerExpectedSignal,  "fPositiveInnerExpectedSignal/F"  );
  fTreeCandidates->Branch ("fNegativeInnerExpectedSignal",  &fNegativeInnerExpectedSignal,  "fNegativeInnerExpectedSignal/F"  );
  fTreeCandidates->Branch ("fPic1InnerExpectedSignal",  &fPic1InnerExpectedSignal,  "fPic1InnerExpectedSignal/F"  );
  fTreeCandidates->Branch ("fPic2InnerExpectedSignal",  &fPic2InnerExpectedSignal,  "fPic2InnerExpectedSignal/F"  );
  fTreeCandidates->Branch ("fPiccInnerExpectedSignal",  &fPiccInnerExpectedSignal,  "fPiccInnerExpectedSignal/F"  );
  
  Bool_t fUsesXiCCProngs, fTrueNegative, fTrueBachelor, fTruePositive, fTruePicc, fTruePic1, fTruePic2;
  fTreeCandidates->Branch ("fUsesXiCCProngs",  &fUsesXiCCProngs,  "fUsesXiCCProngs/O"  );
  fTreeCandidates->Branch ("fTrueNegative",  &fTrueNegative,  "fTrueNegative/O"  );
  fTreeCandidates->Branch ("fTrueBachelor",  &fTrueBachelor,  "fTrueBachelor/O"  );
  fTreeCandidates->Branch ("fTruePositive",  &fTruePositive,  "fTruePositive/O"  );
  fTreeCandidates->Branch ("fTruePicc",  &fTruePicc,  "fTruePicc/O"  );
  fTreeCandidates->Branch ("fTruePic1",  &fTruePic1,  "fTruePic1/O"  );
  fTreeCandidates->Branch ("fTruePic2",  &fTruePic2,  "fTruePic2/O"  );
  
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  // Save XiC too
  TFile *fileTreeXic = new TFile("xic.treeoutput.root", "RECREATE", "", 109);
  TTree *fTreeCandidatesC = new TTree ( "fTreeCandidatesC", "Event Characterization Tree" ) ;
  fTreeCandidatesC->Branch ("fNTracks",    &fNTracks,    "fNTracks/I"    );
  fTreeCandidatesC->Branch ("fNLongTracks",    &fNLongTracks,    "fNLongTracks/I"    );
  fTreeCandidatesC->Branch ("fNLongPrimaryTracks",    &fNLongPrimaryTracks,    "fNLongPrimaryTracks/I"    );
  fTreeCandidatesC->Branch ("fNPrimaryTracks",    &fNPrimaryTracks,    "fNPrimaryTracks/I"    );
  
  fTreeCandidatesC->Branch ("fPtXi",    &fPtXi,    "fPtXi/F"    );
  fTreeCandidatesC->Branch ("fPtXiC",  &fPtXiC,  "fPtXiC/F"  );
  fTreeCandidatesC->Branch ("fPtMCXi",  &fPtMCXi,  "fPtMCXi/F"  );
  fTreeCandidatesC->Branch ("fPtMCXiC",  &fPtMCXiC,  "fPtMCXiC/F"  );
  
  fTreeCandidatesC->Branch ("fPXiC",  &fPXiC,  "fPXiC/F"  );
  fTreeCandidatesC->Branch ("fPMCXiC",  &fPMCXiC,  "fPMCXiC/F"  );
  
  fTreeCandidatesC->Branch ("fXiDecayRadiusMC",  &fXiDecayRadiusMC,  "fXiDecayRadiusMC/F"  );
  fTreeCandidatesC->Branch ("fV0DecayRadiusMC",  &fV0DecayRadiusMC,  "fV0DecayRadiusMC/F"  );
  fTreeCandidatesC->Branch ("fXiDecayRadius",  &fXiDecayRadius,  "fXiDecayRadius/F"  );
  fTreeCandidatesC->Branch ("fV0DecayRadius",  &fV0DecayRadius,  "fV0DecayRadius/F"  );
  
  fTreeCandidatesC->Branch ("fXiDCAxyToPV",  &fXiDCAxyToPV,  "fXiDCAxyToPV/F"  );
  fTreeCandidatesC->Branch ("fXiDCAzToPV",  &fXiDCAzToPV,  "fXiDCAzToPV/F"  );
  fTreeCandidatesC->Branch ("fXicDCAxyToPV",  &fXicDCAxyToPV,  "fXicDCAxyToPV/F"  );
  fTreeCandidatesC->Branch ("fXicDCAzToPV",  &fXicDCAzToPV,  "fXicDCAzToPV/F"  );
  
  fTreeCandidatesC->Branch ("fPic1DCAxyToPV",  &fPic1DCAxyToPV,  "fPic1DCAxyToPV/F"  );
  fTreeCandidatesC->Branch ("fPic1DCAzToPV",  &fPic1DCAzToPV,  "fPic1DCAzToPV/F"  );
  fTreeCandidatesC->Branch ("fPic2DCAxyToPV",  &fPic2DCAxyToPV,  "fPic2DCAxyToPV/F"  );
  fTreeCandidatesC->Branch ("fPic2DCAzToPV",  &fPic2DCAzToPV,  "fPic2DCAzToPV/F"  );
  
  fTreeCandidatesC->Branch ("fV0DauDCA",  &fV0DauDCA,  "fV0DauDCA/F"  );
  fTreeCandidatesC->Branch ("fXiDauDCA",  &fXiDauDCA,  "fXiDauDCA/F"  );
  fTreeCandidatesC->Branch ("fTrueXi",  &fTrueXi,  "fTrueXi/O"  );
  fTreeCandidatesC->Branch ("fTrueXic",  &fTrueXic,  "fTrueXic/O"  );
  fTreeCandidatesC->Branch ("fXiHitsAdded",  &fXiHitsAdded,  "fXiHitsAdded/I"  );
  
  fTreeCandidatesC->Branch ("fLambdaMass",  &fLambdaMass,  "fLambdaMass/F"  );
  fTreeCandidatesC->Branch ("fXiMass",  &fXiMass,  "fXiMass/F"  );
  fTreeCandidatesC->Branch ("fXicMass",  &fXicMass,  "fXicMass/F"  );
  
  fTreeCandidatesC->Branch ("fXicDecayRadius",  &fXicDecayRadius,  "fXicDecayRadius/F"  );
  fTreeCandidatesC->Branch ("fXicDecayDistanceFromPV",  &fXicDecayDistanceFromPV,  "fXicDecayDistanceFromPV/F"  );
  fTreeCandidatesC->Branch ("fXicDaughterDCA",  &fXicDaughterDCA,  "fXicDaughterDCA/F"  );
  
  fTreeCandidatesC->Branch ("fXicVertexX",  &fXicVertexX,  "fXicVertexX/F"  );
  fTreeCandidatesC->Branch ("fXicVertexY",  &fXicVertexY,  "fXicVertexY/F"  );
  fTreeCandidatesC->Branch ("fXicVertexZ",  &fXicVertexZ,  "fXicVertexZ/F"  );
  fTreeCandidatesC->Branch ("fXicVertexXMC",  &fXicVertexXMC,  "fXicVertexXMC/F"  );
  fTreeCandidatesC->Branch ("fXicVertexYMC",  &fXicVertexYMC,  "fXicVertexYMC/F"  );
  fTreeCandidatesC->Branch ("fXicVertexZMC",  &fXicVertexZMC,  "fXicVertexZMC/F"  );
  
  fTreeCandidatesC->Branch ("fXiCtoXiLength",  &fXiCtoXiLength,  "fXiCtoXiLength/F"  );
  
  fTreeCandidatesC->Branch ("fBachelorDCAxy",  &fBachelorDCAxy,  "fBachelorDCAxy/F"  );
  fTreeCandidatesC->Branch ("fBachelorDCAz",  &fBachelorDCAz,  "fBachelorDCAz/F"  );
  fTreeCandidatesC->Branch ("fNegativeDCAxy",  &fNegativeDCAxy,  "fNegativeDCAxy/F"  );
  fTreeCandidatesC->Branch ("fNegativeDCAz",  &fNegativeDCAz,  "fNegativeDCAz/F"  );
  fTreeCandidatesC->Branch ("fPositiveDCAxy",  &fPositiveDCAxy,  "fPositiveDCAxy/F"  );
  fTreeCandidatesC->Branch ("fPositiveDCAz",  &fPositiveDCAz,  "fPositiveDCAz/F"  );
  
  fTreeCandidatesC->Branch ("fV0DCAxyToPV",  &fV0DCAxyToPV,  "fV0DCAxyToPV/F"  );
  fTreeCandidatesC->Branch ("fV0DCAzToPV",  &fV0DCAzToPV,  "fV0DCAzToPV/F"  );
  fTreeCandidatesC->Branch ("fV0DecayLength",  &fV0DecayLength,  "fV0DecayLength/F"  );
  fTreeCandidatesC->Branch ("fXiDecayLength",  &fXiDecayLength,  "fXiDecayLength/F"  );
  
  //Six prong momenta for efficiency composition
  fTreeCandidatesC->Branch ("fPiC1Pt",  &fPiC1Pt,  "fPiC1Pt/F"  );
  fTreeCandidatesC->Branch ("fPiC2Pt",  &fPiC2Pt,  "fPiC2Pt/F"  );
  fTreeCandidatesC->Branch ("fBachelorPt",  &fBachelorPt,  "fBachelorPt/F"  );
  fTreeCandidatesC->Branch ("fPositivePt",  &fPositivePt,  "fPositivePt/F"  );
  fTreeCandidatesC->Branch ("fNegativePt",  &fNegativePt,  "fNegativePt/F"  );
  
  fTreeCandidatesC->Branch ("fV0TotalMomentum",  &fV0TotalMomentum,  "fV0TotalMomentum/F"  );
  fTreeCandidatesC->Branch ("fXiTotalMomentum",  &fXiTotalMomentum,  "fXiTotalMomentum/F"  );
  
  fTreeCandidatesC->Branch ("fNegativeClusters",  &fNegativeClusters,  "fNegativeClusters/I"  );
  fTreeCandidatesC->Branch ("fPositiveClusters",  &fPositiveClusters,  "fPositiveClusters/I"  );
  fTreeCandidatesC->Branch ("fBachelorClusters",  &fBachelorClusters,  "fBachelorClusters/I"  );
  
  fTreeCandidatesC->Branch ("fNegativeChisquare",  &fNegativeChisquare,  "fNegativeChisquare/F"  );
  fTreeCandidatesC->Branch ("fPositiveChisquare",  &fPositiveChisquare,  "fPositiveChisquare/F"  );
  fTreeCandidatesC->Branch ("fBachelorChisquare",  &fBachelorChisquare,  "fBachelorChisquare/F"  );
  
  fTreeCandidatesC->Branch ("fPiC1Eta",  &fPiC1Eta,  "fPiC1Eta/F"  );
  fTreeCandidatesC->Branch ("fPiC2Eta",  &fPiC2Eta,  "fPiC2Eta/F"  );
  fTreeCandidatesC->Branch ("fNegativeEta",  &fNegativeEta,  "fNegativeEta/F"  );
  fTreeCandidatesC->Branch ("fPositiveEta",  &fPositiveEta,  "fPositiveEta/F"  );
  fTreeCandidatesC->Branch ("fBachelorEta",  &fBachelorEta,  "fBachelorEta/F"  );
  
  fTreeCandidatesC->Branch ("fXiEta",  &fXiEta,  "fXiEta/F"  );
  fTreeCandidatesC->Branch ("fXiCEta",  &fXiCEta,  "fXiCEta/F"  );
  
  fTreeCandidatesC->Branch ("fPicUsed",  &fPicUsed,  "fPicUsed/I"  );
  
  fTreeCandidatesC->Branch ("fPic1PDG",  &fPic1PDG,  "fPic1PDG/I"  );
  fTreeCandidatesC->Branch ("fPic2PDG",  &fPic2PDG,  "fPic2PDG/I"  );
  fTreeCandidatesC->Branch ("fNegativePDG",  &fNegativePDG,  "fNegativePDG/I"  );
  fTreeCandidatesC->Branch ("fPositivePDG",  &fPositivePDG,  "fPositivePDG/I"  );
  fTreeCandidatesC->Branch ("fBachelorPDG",  &fBachelorPDG,  "fBachelorPDG/I"  );
  
  
  fTreeCandidatesC->Branch ("fBachelorInnerTOF20Signal",  &fBachelorInnerTOF20Signal,  "fBachelorInnerTOF20Signal/F"  );
  fTreeCandidatesC->Branch ("fPositiveInnerTOF20Signal",  &fPositiveInnerTOF20Signal,  "fPositiveInnerTOF20Signal/F"  );
  fTreeCandidatesC->Branch ("fNegativeInnerTOF20Signal",  &fNegativeInnerTOF20Signal,  "fNegativeInnerTOF20Signal/F"  );
  fTreeCandidatesC->Branch ("fPic1InnerTOF20Signal",  &fPic1InnerTOF20Signal,  "fPic1InnerTOF20Signal/F"  );
  fTreeCandidatesC->Branch ("fPic2InnerTOF20Signal",  &fPic2InnerTOF20Signal,  "fPic2InnerTOF20Signal/F"  );
  
  fTreeCandidatesC->Branch ("fBachelorInnerTOF50Signal",  &fBachelorInnerTOF50Signal,  "fBachelorInnerTOF50Signal/F"  );
  fTreeCandidatesC->Branch ("fPositiveInnerTOF50Signal",  &fPositiveInnerTOF50Signal,  "fPositiveInnerTOF50Signal/F"  );
  fTreeCandidatesC->Branch ("fNegativeInnerTOF50Signal",  &fNegativeInnerTOF50Signal,  "fNegativeInnerTOF50Signal/F"  );
  fTreeCandidatesC->Branch ("fPic1InnerTOF50Signal",  &fPic1InnerTOF50Signal,  "fPic1InnerTOF50Signal/F"  );
  fTreeCandidatesC->Branch ("fPic2InnerTOF50Signal",  &fPic2InnerTOF50Signal,  "fPic2InnerTOF50Signal/F"  );
  
  fTreeCandidatesC->Branch ("fBachelorInnerTOFSignalMC",  &fBachelorInnerTOFSignalMC,  "fBachelorInnerTOFSignalMC/F"  );
  fTreeCandidatesC->Branch ("fPositiveInnerTOFSignalMC",  &fPositiveInnerTOFSignalMC,  "fPositiveInnerTOFSignalMC/F"  );
  fTreeCandidatesC->Branch ("fNegativeInnerTOFSignalMC",  &fNegativeInnerTOFSignalMC,  "fNegativeInnerTOFSignalMC/F"  );
  fTreeCandidatesC->Branch ("fPic1InnerTOFSignalMC",  &fPic1InnerTOFSignalMC,  "fPic1InnerTOFSignalMC/F"  );
  fTreeCandidatesC->Branch ("fPic2InnerTOFSignalMC",  &fPic2InnerTOFSignalMC,  "fPic2InnerTOFSignalMC/F"  );
  
  fTreeCandidatesC->Branch ("fBachelorInnerExpectedSignal",  &fBachelorInnerExpectedSignal,  "fBachelorInnerExpectedSignal/F"  );
  fTreeCandidatesC->Branch ("fPositiveInnerExpectedSignal",  &fPositiveInnerExpectedSignal,  "fPositiveInnerExpectedSignal/F"  );
  fTreeCandidatesC->Branch ("fNegativeInnerExpectedSignal",  &fNegativeInnerExpectedSignal,  "fNegativeInnerExpectedSignal/F"  );
  fTreeCandidatesC->Branch ("fPic1InnerExpectedSignal",  &fPic1InnerExpectedSignal,  "fPic1InnerExpectedSignal/F"  );
  fTreeCandidatesC->Branch ("fPic2InnerExpectedSignal",  &fPic2InnerExpectedSignal,  "fPic2InnerExpectedSignal/F"  );
  
  fTreeCandidatesC->Branch ("fUsesXiCCProngs",  &fUsesXiCCProngs,  "fUsesXiCCProngs/O"  );
  fTreeCandidatesC->Branch ("fTrueNegative",  &fTrueNegative,  "fTrueNegative/O"  );
  fTreeCandidatesC->Branch ("fTrueBachelor",  &fTrueBachelor,  "fTrueBachelor/O"  );
  fTreeCandidatesC->Branch ("fTruePositive",  &fTruePositive,  "fTruePositive/O"  );
  fTreeCandidatesC->Branch ("fTruePic1",  &fTruePic1,  "fTruePic1/O"  );
  fTreeCandidatesC->Branch ("fTruePic2",  &fTruePic2,  "fTruePic2/O"  );
  fileTree->cd();
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
  
  // Will load tracks determined elsewhere
  std::cout << "*- Loading tracks from file"<<endl;
  TFile *fFileTracks = new TFile("tracks.root", "READ");
  TTree *fTreeTracks = (TTree*) fFileTracks->Get("fTreeTracks");
  
  //Create std::vectors
  o2::its::TrackITS *wdTrack = new o2::its::TrackITS();
  o2::MCCompLabel *wdTrackLabel = new o2::MCCompLabel();
  Int_t wdEvent = 0;
  
  o2::dataformats::DCA dca;
  
  //Associate to tree
  fTreeTracks->SetBranchAddress("wdTrack",&wdTrack);
  fTreeTracks->SetBranchAddress("wdTrackLabel",&wdTrackLabel);
  fTreeTracks->SetBranchAddress("wdEvent",&wdEvent);
  
   for (int iEvent{0}; iEvent < itsHits.GetEntriesFast(); ++iEvent) {
     // for (int iEvent{0}; iEvent < ; ++iEvent) {
    fXiDecayRadius = 0;
    fV0DecayRadius = 0;
    fXiDecayRadiusMC = 0;
    fV0DecayRadiusMC = 0;
    std::cout << "*************** Event " << iEvent << " ***************" << std::endl;
    itsHits.GetEntry(iEvent);
    mcTree.GetEvent(iEvent);
    o2::its::ROframe event{iEvent, 12};
    hEventCounter->Fill(0.5);
    
    //Locate Xi decay point
    Int_t lDirectTrackingNLayers = 0;
    Int_t lNLayersLambda = 0;
    cout<<"Checking parenthood - mcArr size "<<mcArr->size()<<endl;
    
    //Check type of MC
    fPtMCXiC = -1;
    fPtMCXiCC = -1;
    
    Long_t lNchThisEvent = 0;
    Long_t lNchThisEventAll = 0;
    
    roFrame = iEvent;
    //std::cout << "*- Event " << iEvent << " MC loop" << std::endl;
    
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //LUT APPROACH STEP 1: DO ALL PRIMARY TRACKS
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    
    //Perfect MC vertex from mcHeader
    
    Double_t fPVxMC = mcHead->GetX();
    Double_t fPVyMC = mcHead->GetY();
    Double_t fPVzMC = mcHead->GetZ();
    
    o2::math_utils::Point3D<float> pos{fPVxMC,fPVyMC,fPVzMC};
    std::array<float, 6> cov;
    for(Int_t jj=0; jj<6; jj++) cov[jj]=1e-6;
    o2::dataformats::VertexBase vtx(pos, cov);
    
    hEventCounterWithVertex->Fill(0.5);
    
    lWatchSmearing.Stop();
    lWatchTracking.Start(kFALSE);
    
    //trivial and simple
    std::vector<o2::its::TrackITS> tracks;
    std::vector<o2::MCCompLabel> tracksLabels;
    
    for(Int_t iwdTrack = 0; iwdTrack<fTreeTracks->GetEntries(); iwdTrack++){
      fTreeTracks->GetEntry(iwdTrack);
      if( wdEvent == iEvent){
        o2::its::TrackITS wdTrackObj = *wdTrack;
        o2::MCCompLabel wdTrackLabelObj = *wdTrackLabel;
        tracks.emplace_back(wdTrackObj);
        tracksLabels.emplace_back(wdTrackLabelObj);
      }
    }
    
    std::cout << "*- Event " << iEvent << " done loading "<<tracks.size()<<" tracks, proceeding..." << std::endl;
    
    lWatchTracking.Stop();
    
    for (Long_t iii=0; iii< mcArr->size(); iii++ ){
      auto part = mcArr->at(iii);

      //Loop in generated
    }
    
    lWatchAnalysis.Start(kFALSE);
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Now merge track lists and label lists
    cout<<"Read track array size: "<<tracks.size()<<endl;
    cout<<"Read label array size: "<<tracksLabels.size()<<endl;
    
    hQANchCorrelation->Fill(tracks.size(), lNchThisEventAll);
    
    TArrayI negtra(tracks.size());
    TArrayI postra(tracks.size());
    TArrayI truenegtra(tracks.size());
    TArrayI truepostra(tracks.size());
    Long_t nneg=0, npos=0;
        
    hNTracks -> Fill(tracks.size());
    fNTracks = tracks.size();
    
    TArrayF DCAxytoPVArray(tracks.size()); //store all DCAs to PV in memory, please
    TArrayF DCAztoPVArray(tracks.size()); //store all DCAs to PV in memory, please

    Int_t fTrackPDG;

    // create two arrays: with track indexes for 1)electrons and 2) positrons
    std::vector<int64_t> recoElectron(tracks.size());
    std::vector<int64_t> recoPositron(tracks.size());
    int ntrksPos =0;
    int ntrksNeg =0;

    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    //Loop over found tracks, attempt to find V0 candidates
    // simple reset
    
    for (unsigned int i{0}; i < tracks.size(); ++i) {
      auto& lab = tracksLabels[i];
      auto& track = tracks[i];
      int trackID = lab.getTrackID();
      
      Int_t lPos, lNeg;
      // if( Particle == 3122){
      //   lPos = 2212; lNeg = -211;
      // }
      // if( Particle == 310){
      //   lPos = 211; lNeg= -211;
      // }
      if( Particle == 22){
        lPos = 11; lNeg= -11;
      }
      Float_t lThisDCAxy=0.0, lThisDCAz=0.0;
      DCAxytoPVArray[i] = 1e+10;
      DCAztoPVArray[i] = 1e+10;
      
      if (!track.propagateToDCA(vtx, tracker.getBz(), &dca)) {
        std::cout << "Propagation failed." << std::endl;
        lThisDCAxy = 1e+10;
        lThisDCAz = 1e+10;
      } else {
        lThisDCAxy = dca.getY();
        lThisDCAz = dca.getZ();
        DCAxytoPVArray[i] = lThisDCAxy;
        DCAztoPVArray[i] = lThisDCAz;
      }
      
      hQADCAxy->Fill(1e+4*lThisDCAxy);
      hQADCAz->Fill(1e+4*lThisDCAz);
      
      fNLongTracks++;
      if( TMath::Abs(1e+4*lThisDCAxy)<25 && TMath::Abs(1e+4*lThisDCAz)<25) fNLongPrimaryTracks++;
      if( TMath::Abs(1e+4*lThisDCAxy)<25 && TMath::Abs(1e+4*lThisDCAz)<25) fNPrimaryTracks++;
      
      Bool_t lIsPos = kFALSE, lIsPosPDG = kFALSE;
      Bool_t lIsNeg = kFALSE, lIsNegPDG = kFALSE;
      
      if(track.getSign()>0) lIsPos = kTRUE;
      if(track.getSign()<0) lIsNeg = kTRUE;
      
      Bool_t lIsMotherDesired = kFALSE;
      Bool_t lIsGrandMotherDesired = kFALSE;
      if(trackID>=0 && trackID<mcArr->size()){
        auto part = mcArr->at(trackID);
	fTrackPDG = part.GetPdgCode();
	auto indexParticleIMother = part.getMotherTrackId();
	// Get the mother.
	auto particleIMother = mcArr->at(indexParticleIMother);
	auto PDGParticleIMother = particleIMother.GetPdgCode(); 

	if( !(part.isPrimary()) && PDGParticleIMother == 22  ){
	  //cout <<"electron/positron from Conv Photon ::PDG code::"<<  part.GetPdgCode() << "   "<< PDGParticleIMother  << endl;
	  if ( fTrackPDG ==11 ){
	    recoPositron[ntrksPos++]=i;
	    //cout <<"positron::PDG code"<<  part.GetPdgCode() << "   "<< PDGParticleIMother  << endl;
	  }
	  
	  if ( fTrackPDG ==-11 ){
	    recoElectron[ntrksNeg++]=i;
	    //cout <<"electron::PDG code"<<  part.GetPdgCode() << "   "<< PDGParticleIMother  << endl;
	  }
	}


	
        if( part.GetPdgCode() == lPos ) lIsPosPDG = kTRUE;
        if( part.GetPdgCode() == lNeg ) lIsNegPDG = kTRUE;
        Int_t lMotherTrackID=part.getMotherTrackId();
        if(lMotherTrackID>=0 && lMotherTrackID<mcArr->size()){
          auto partmom = mcArr->at(lMotherTrackID);
          if(partmom.GetPdgCode() == Particle) lIsMotherDesired = kTRUE;
          auto partgrandmomidx = partmom.getMotherTrackId();
          if(partgrandmomidx>=0){
            auto partgrandmom = mcArr->at(partgrandmomidx);
            if(partgrandmom.GetPdgCode() == 111 ||partgrandmom.GetPdgCode() == 221 ) lIsGrandMotherDesired = kTRUE;
          }
        }
      }
      
      if( lIsPos && ((lIsMotherDesired&&lIsGrandMotherDesired&&lIsPosPDG)||lAssociateXiDaughters==kFALSE) && ((TMath::Abs(lThisDCAxy) > lMinDCAxyPositive && TMath::Abs(lThisDCAz) > lMinDCAzPositive ) || lMasterSwitch<0 ) ) {
        truepostra[npos] = 0;
        if(lIsMotherDesired) truepostra[npos] = 1;
        postra[npos++]=i;
      }
      if( lIsNeg && ((lIsMotherDesired&&lIsGrandMotherDesired&&lIsNegPDG)||lAssociateXiDaughters==kFALSE) && ((TMath::Abs(lThisDCAxy) > lMinDCAxyNegative && TMath::Abs(lThisDCAz) > lMinDCAzNegative)|| lMasterSwitch<0) )   {
        truenegtra[nneg] = 0;
        if(lIsMotherDesired) truenegtra[nneg] = 1;
        negtra[nneg++]=i;
      }
    }
    hNLongTracks -> Fill(fNLongTracks);
    hNLongPrimaryTracks -> Fill(fNLongPrimaryTracks);
    hNPrimaryTracks -> Fill(fNPrimaryTracks);

    // +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // Loops from e+e- as we had it
    double eMass = 0.000511;
    for(unsigned int i{0}; i<ntrksPos; i++    )
      {
        auto & labPos = tracksLabels[recoPositron[i]];
        auto & trackPos = tracks[recoPositron[i]];
        int lMCIDPos = labPos.getTrackID();
        auto partPos = mcArr ->at(lMCIDPos);
	// auto partPos = trackPos.mcParticle();
        double radiusConv = sqrt(partPos.GetStartVertexCoordinatesX()*partPos.GetStartVertexCoordinatesX()+
                                 partPos.GetStartVertexCoordinatesY()*partPos.GetStartVertexCoordinatesY());
        //cout << partPos.GetStartVertexCoordinatesX() << "  "<< partPos.GetStartVertexCoordinatesY() << " "<< partPos.GetStartVertexCoordinatesZ()<< "  "<< radiusConv<< endl;
	
        for(unsigned int j{0}; j<ntrksNeg; j++    )
	  {
            auto & labNeg = tracksLabels[recoElectron[i]];
            auto & trackNeg = tracks[recoElectron[i]];
            int lMCIDNeg = labNeg.getTrackID();
            auto partNeg = mcArr ->at(lMCIDNeg);
	    // auto partNeg = trackNeg.mcParticle();
            //cout<< "Numbers::" << partPos.getMotherTrackId() << "  " << partNeg.getMotherTrackId()<< " "<< partPos.Px()  <<endl;
            if (partPos.getMotherTrackId() == partNeg.getMotherTrackId() )
	      {
		
                int nCand = fitterV0.process(trackPos, trackNeg);
                if (nCand > 0) {
		  std::array<float, 3> pos = {0.};
		  std::array<float, 3> posXi = {0.};
		  std::array<float, 3> pvecpos = {0.};
		  std::array<float, 3> pvecneg = {0.};
		  std::array<float, 3> pvecbach = {0.};
		  std::array<float, 21> cov0 = {0};
		  std::array<float, 21> cov1 = {0};
		  std::array<float, 21> covV0 = {0};
                  
		  //Covariance matrix calculation
		  const int momInd[6] = {9, 13, 14, 18, 19, 20}; // cov matrix elements for momentum component
		  fitterV0.getTrack(0).getPxPyPzGlo(pvecpos);
		  fitterV0.getTrack(1).getPxPyPzGlo(pvecneg);
		  fitterV0.getTrack(0).getCovXYZPxPyPzGlo(cov0);
		  fitterV0.getTrack(1).getCovXYZPxPyPzGlo(cov1);
                  
		  for (int i = 0; i < 6; i++) {
		    int j = momInd[i];
		    covV0[j] = cov0[j]+cov1[j];
		  }
		  auto covVtxV0 = fitterV0.calcPCACovMatrix();
		  const auto& wvtx = fitterV0.getPCACandidate();
                  
		  covV0[0] = covVtxV0(0, 0);
		  covV0[1] = covVtxV0(1, 0);
		  covV0[2] = covVtxV0(1, 1);
		  covV0[3] = covVtxV0(2, 0);
		  covV0[4] = covVtxV0(2, 1);
		  covV0[5] = covVtxV0(2, 2);
                  
		  for (int i = 0; i < 21; i++) {
		    //std::cout<<" covV0["<<i<<"] = "<< covV0[i]<< std::endl;
		  }
                  
		  const std::array<float, 3> vertex = {(float)wvtx[0], (float)wvtx[1], (float)wvtx[2]};
		  const std::array<float, 3> momentum = {pvecpos[0] + pvecneg[0], pvecpos[1] + pvecneg[1], pvecpos[2] + pvecneg[2]};
                  
		  // fPosPt = std::hypot( pvecpos[0] , pvecpos[1] );
		  // fNegPt = std::hypot( pvecneg[0] , pvecneg[1] );
                  
		  TLorentzVector pElec, pPosi, pGamma;
		  TLorentzVector pElecMC, pPosiMC, pGammaMC;
		  //  I cannot use for the moment reconstructed tracks....
		  //                pPosi.SetPtEtaPhiM(trackPos.pt(), trackPos.eta(), trackPos.phi(), eMass);
		  //                pElec.SetPtEtaPhiM(trackNeg.pt(), trackNeg.eta(), trackNeg.phi(), eMass);
		  
		  pPosiMC.SetXYZM(partPos.Px(), partPos.Py(), partPos.Pz(), eMass);
		  pElecMC.SetXYZM(partNeg.Px(), partNeg.Py(), partNeg.Pz(), eMass);
		  pPosi.SetXYZM(pvecpos[0], pvecpos[1], pvecpos[2], eMass);
		  pElec.SetXYZM(pvecneg[0], pvecneg[1], pvecneg[2], eMass);

		  pGamma = pPosi + pElec;
		  pGammaMC = pPosiMC + pElecMC;
		  hInvMassSame ->Fill(pGamma.M());
		  hPhotonPt ->Fill(pGamma.Pt());
		  hPhotonPtMC ->Fill(pGammaMC.Pt());
		  if (pGammaMC.Pt()!=0  && pGammaMC.Pz()!=0 && pGammaMC.P()!=0){
                    hPhotonPtRes ->Fill(pGammaMC.Pt(),(pGamma.Pt()-pGammaMC.Pt())/pGammaMC.Pt());
                    hPhotonPzRes ->Fill(pGammaMC.Pz(),(pGamma.Pz()-pGammaMC.Pz())/pGammaMC.Pz());
                    hPhotonPRes ->Fill(pGammaMC.P(),(pGamma.P()-pGammaMC.P())/pGammaMC.P());
                    
		  }
		  hVertex -> Fill(partPos.GetStartVertexCoordinatesX(),partPos.GetStartVertexCoordinatesY() );
		  hVertexR->Fill(partPos.GetStartVertexCoordinatesZ(),radiusConv);
		}
	      } // same mother
	    
	  }
      }
    
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    // for (unsigned int i{0}; i < npos; ++i) {
    //   for (unsigned int j{0}; j < nneg; ++j) {
    //     //Try to progate to dca
    //     hCombinatorics->Fill(0.5);
    //     auto Track1 = tracks[postra[i]];
    //     auto Track2 = tracks[negtra[j]];
        
    //     //Check same mother
    //     auto& labi = tracksLabels[postra[i]];
    //     int trackIDi = labi.getTrackID();
    //     auto& labj = tracksLabels[negtra[j]];
    //     int trackIDj = labj.getTrackID();
        
    //     //De-reference from memory, no need to propagate like crazy now
    //     fPositiveDCAxy = DCAxytoPVArray[postra[i]] * 1.e4;
    //     fPositiveDCAz = DCAztoPVArray[postra[i]] * 1.e4;
    //     fNegativeDCAxy = DCAxytoPVArray[negtra[j]] * 1.e4;
    //     fNegativeDCAz = DCAztoPVArray[negtra[j]] * 1.e4;
        
    //     fPositiveClusters = Track1.getNumberOfClusters();
    //     fNegativeClusters = Track2.getNumberOfClusters();
    //     fPositiveChisquare = Track1.getChi2();
    //     fNegativeChisquare = Track2.getChi2();
        
    //     //Not same mother -> discard
    //     //if( trackIDi >= mcArr->size()) continue;
    //     //if( trackIDj >= mcArr->size()) continue;
    //     //auto parti = mcArr->at(trackIDi);
    //     //auto partj = mcArr->at(trackIDj);
    //     //if( abs(parti.getMotherTrackId()) != ) continue;
        
    //     hCombinatoricsV0->Fill(1.5);
    //     //Get mother momentum from stack
    //     auto part1 = mcArr->at( trackIDi );
    //     auto part2 = mcArr->at( trackIDj );
        
    //     fPositivePDG = part1.GetPdgCode();
    //     fNegativePDG = part2.GetPdgCode();
        
    //     Int_t lCascadeID = -1;
    //     Bool_t lSameMotherPosNeg = kFALSE;
    //     fPtMCMother = -1;
    //     fPtMCXi = -1;
    //     Int_t lCascadeMotherID = -1;
    //     Int_t lCascadePDGcheck = -1;
    //     Bool_t lCascadeFromXiCC = kFALSE;
    //     if( part1.getMotherTrackId()>=0 && part2.getMotherTrackId()>=0 && part1.getMotherTrackId()<mcArr->size() ){
    //       if( part1.getMotherTrackId() == part2.getMotherTrackId() ) lSameMotherPosNeg = kTRUE;
    //       auto part3 = mcArr->at( abs(part1.getMotherTrackId()) );
    //       fPtMCMother = TMath::Sqrt(TMath::Power(part3.Px(),2) + TMath::Power(part3.Py(),2));
    //       lCascadeID = part3.getMotherTrackId();
    //       if( lCascadeID >= 0 ){
    //         auto partCasc = mcArr->at( lCascadeID );
    //         lCascadePDGcheck = partCasc.GetPdgCode();
    //         fPtMCXi = partCasc.GetPt();
    //         lCascadeMotherID = partCasc.getMotherTrackId();
    //         if( lCascadeMotherID >= 0 ){
    //           auto partCascMother = mcArr->at( lCascadeMotherID );
    //           if( partCascMother.GetPdgCode() == 4232 && partCascMother.getMotherTrackId() >= 0){
    //             auto partCascGrandMother = mcArr->at( partCascMother.getMotherTrackId() );
    //             if( partCascGrandMother.GetPdgCode() == 4422 ) lCascadeFromXiCC = kTRUE;
    //           }
    //         }
    //       }
    //     }
    //     fTrueNegative = kFALSE;
    //     fTruePositive = kFALSE;
        
    //     if( lCascadeFromXiCC && truepostra[j] == 1 ) fTruePositive = kTRUE;
    //     if( lCascadeFromXiCC && truenegtra[j] == 1 ) fTrueNegative = kTRUE;
        
    //     if(lCascadeID<0&&lAssociateXiDaughters) continue;
    //     if(lSameMotherPosNeg==kFALSE&&lAssociateXiDaughters) continue;
    //     if(lCascadePDGcheck!=3312&&lAssociateXiDaughters) continue;
    //     fV0DecayRadiusMC=-1;
    //     if( lSameMotherPosNeg == kTRUE ) fV0DecayRadiusMC = std::hypot(part1.Vx(),part1.Vy());
        
    //     hCombinatoricsV0->Fill(2.5);
        
    //     fPtMC = TMath::Sqrt(TMath::Power(part1.Px()+part2.Px(),2) + TMath::Power(part1.Py()+part2.Py(),2));
    //     //pT of V0 via actual V0
        
    //     int nCand = fitterV0.process(Track1, Track2);
    //     if (nCand == 0) {
    //       //std::cout<<"Crap candidate"<<std::endl;
    //       continue;
    //     }
    //     hCombinatoricsV0->Fill(3.5);
        
    //     float thisdcav0dau = TMath::Sqrt(fitterV0.getChi2AtPCACandidate(0));
    //     fDCAV0Dau = thisdcav0dau * 1.e4; //in microns!
    //     if(fDCAV0Dau > lMaxDCAV0Daughters && lMasterSwitch > 0) continue;
    //     hSkimmingLosses->Fill(10.5);
    //     fV0DauDCA = fDCAV0Dau ;
        
    //     const auto& wvtx = fitterV0.getPCACandidate();
        
    //     std::array<float, 3> weakdecaypos = {0.};
    //     std::array<float, 3> pvec0;
    //     std::array<float, 3> pvec1;
    //     for (int i = 0; i < 3; i++) {
    //       weakdecaypos[i] = wvtx[i];
    //     }
    //     std::array<float, 3> Track1Pos;
    //     std::array<float, 3> Track2Pos;
    //     fitterV0.getTrack(0).getXYZGlo(Track1Pos);
    //     fitterV0.getTrack(1).getXYZGlo(Track2Pos);
        
    //     fitterV0.getTrack(0).getPxPyPzGlo(pvec0);
    //     fitterV0.getTrack(1).getPxPyPzGlo(pvec1);
        
    //     auto thisv0cospa = RecoDecay::CPA(array{fPVxMC, fPVyMC, fPVzMC},
    //                                       array{weakdecaypos[0], weakdecaypos[1], weakdecaypos[2]}, array{pvec0[0] + pvec1[0], pvec0[1] + pvec1[1], pvec0[2] + pvec1[2]});
        
    //     //Fiducial: min radius
    //     auto thisv0radius = std::hypot(weakdecaypos[0], weakdecaypos[1]);
    //     fV0DecayRadius=thisv0radius;
        
    //     if( fV0DecayRadius < lMinV0Radius && lMasterSwitch > 0) continue;
    //     hSkimmingLosses->Fill(0.5);
    //     Double_t lMassPos, lMassNeg;
    //     if(Particle==310){
    //       lMassPos = RecoDecay::getMassPDG(kPiPlus);
    //       lMassNeg = RecoDecay::getMassPDG(kPiPlus);
    //     }
    //     if(Particle==3122){
    //       lMassPos = RecoDecay::getMassPDG(kProton);
    //       lMassNeg = RecoDecay::getMassPDG(kPiPlus);
    //     }
        
    //     auto massk0 = RecoDecay::M(array{array{pvec0[0], pvec0[1], pvec0[2]}, array{pvec1[0], pvec1[1], pvec1[2]}}, array{lMassPos, lMassNeg});
    //     fMass = massk0;
    //     fLambdaMass = fMass;
        
    //     if( TMath::Abs(fLambdaMass-1.116)> lMassWindowLambda && lMasterSwitch > 0 ) continue; //only look at peak, please
    //     hSkimmingLosses->Fill(6.5);
    //     fPt = TMath::Sqrt(TMath::Power(pvec0[0]+pvec1[0],2) + TMath::Power(pvec0[1]+pvec1[1],2) );
        
    //     Double_t lExpMass=1.115683;
    //     if(Particle==310) lExpMass = 0.497;
        
    //     fPA = TMath::ACos(thisv0cospa);
    //   }
    // }//end loop on track pairs
    lWatchAnalysis.Stop();
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    std::cout<<"---> Valid attempts so far = "<<fTreeCandidates->GetEntries()<< std::endl;
  } //end event loop
  
  //fQA->Write();
  fileTree->cd();
  hSkimmingLosses->Write();
  hEventCounter->Write(); // keep track of event counter, please
  hEventCounterWithVertex->Write();
  hVertexZ->Write();
  hXiCGeneratedPt->Write();
  hXiCCGeneratedPt->Write();
  fTreeCandidates->Write();
  hNTracks->Write();
  hNLongTracks->Write();
  hNLongPrimaryTracks->Write();
  hNPrimaryTracks->Write();
  hNVertices->Write();
  
  hPtEtaGeneratedXi->Write();
  hPtEtaGeneratedXiC->Write();
  hPtEtaGeneratedXiCC->Write();
  hPtYGeneratedXi->Write();
  hPtYGeneratedXiC->Write();
  hPtYGeneratedXiCC->Write();
  
  hTime->Fill(0.5, lWatchSmearing.RealTime());
  hTime->Fill(1.5, lWatchTracking.RealTime());
  hTime->Fill(2.5, lWatchAnalysis.RealTime());
  hTime->Fill(3.5, lWatchSmearing.CpuTime());
  hTime->Fill(4.5, lWatchTracking.CpuTime());
  hTime->Fill(5.5, lWatchAnalysis.CpuTime());
  
  hTime->Write();
  
  hPtMultGeneratedXi_AllEta -> Write();
  hPtMultGeneratedXiC_AllEta -> Write();
  hPtMultGeneratedXiCC_AllEta -> Write();
  
  hPtMultGeneratedXi_AllY -> Write();
  hPtMultGeneratedXiC_AllY -> Write();
  hPtMultGeneratedXiCC_AllY -> Write();
  
  hPtMultGeneratedXi_Eta5 -> Write();
  hPtMultGeneratedXiC_Eta5 -> Write();
  hPtMultGeneratedXiCC_Eta5 -> Write();
  
  hPtMultGeneratedXi_Y5 -> Write();
  hPtMultGeneratedXiC_Y5 -> Write();
  hPtMultGeneratedXiCC_Y5 -> Write();
  
  hPtMultGeneratedXi_Eta10 -> Write();
  hPtMultGeneratedXiC_Eta10 -> Write();
  hPtMultGeneratedXiCC_Eta10 -> Write();
  
  hPtMultGeneratedXi_Y10 -> Write();
  hPtMultGeneratedXiC_Y10 -> Write();
  hPtMultGeneratedXiCC_Y10 -> Write();
  
  hQADCAxy->Write();
  hQADCAz->Write();
  hQAMCNch->Write();
  hQANchCorrelation->Write();
  
  fileTreeXic->cd();
  
  hSkimmingLosses->Write();
  hEventCounter->Write(); // keep track of event counter, please
  hEventCounterWithVertex->Write();
  hVertexZ->Write();
  hXiCGeneratedPt->Write();
  hXiCCGeneratedPt->Write();
  fTreeCandidatesC->Write();
  hNTracks->Write();
  hNLongTracks->Write();
  hNLongPrimaryTracks->Write();
  hNPrimaryTracks->Write();
  hNVertices->Write();
  
  hPtEtaGeneratedXi->Write();
  hPtEtaGeneratedXiC->Write();
  hPtEtaGeneratedXiCC->Write();
  hPtYGeneratedXi->Write();
  hPtYGeneratedXiC->Write();
  hPtYGeneratedXiCC->Write();
  hTime->Write();

  
  hPtMultGeneratedXi_AllEta -> Write();
  hPtMultGeneratedXiC_AllEta -> Write();
  hPtMultGeneratedXiCC_AllEta -> Write();
  
  hPtMultGeneratedXi_AllY -> Write();
  hPtMultGeneratedXiC_AllY -> Write();
  hPtMultGeneratedXiCC_AllY -> Write();
  
  hPtMultGeneratedXi_Eta5 -> Write();
  hPtMultGeneratedXiC_Eta5 -> Write();
  hPtMultGeneratedXiCC_Eta5 -> Write();
  
  hPtMultGeneratedXi_Y5 -> Write();
  hPtMultGeneratedXiC_Y5 -> Write();
  hPtMultGeneratedXiCC_Y5 -> Write();
  
  hPtMultGeneratedXi_Eta10 -> Write();
  hPtMultGeneratedXiC_Eta10 -> Write();
  hPtMultGeneratedXiCC_Eta10 -> Write();
  
  hPtMultGeneratedXi_Y10 -> Write();
  hPtMultGeneratedXiC_Y10 -> Write();
  hPtMultGeneratedXiCC_Y10 -> Write();
  
  hQADCAxy->Write();
  hQADCAz->Write();
  hQAMCNch->Write();
  hQANchCorrelation->Write();
  
  //std::cout<<"---> Xi              = "<<fTreeXi->GetEntries()<< std::endl;
  std::cout<<"---> Xi_c candidates  = "<<fTreeCandidatesC->GetEntries()<< std::endl;
  std::cout<<"---> Xi_cc candidates = "<<fTreeCandidates->GetEntries()<< std::endl;
  
  TFile output("xicc.histooutput.root", "recreate");
  
  hGenerated->Write();
  hNVertices->Write();
  hNTracks->Write();
  hVertexZ->Write();
  
  hTrackCount->Write();
  hCombinatorics->Write();
  
  hCombinatoricsV0->Write();

 
  TFile outputPhoton("photon.histooutput.root", "recreate");
 
  hInvMassSame -> Write();
  hPhotonPt -> Write();
  hPhotonPtMC -> Write();
  hPhotonPtRes -> Write();
  hPhotonPzRes -> Write();
  hPhotonPRes -> Write();
  hVertex ->Write();
  hVertexR->Write();

  cout<<"Performance characteristics: "<<endl;
  cout<<"Smearing time (real).....: "<<lWatchSmearing.RealTime()<<" seconds"<<endl;
  cout<<"Tracking time (real).....: "<<lWatchTracking.RealTime()<<" seconds"<<endl;
  cout<<"Anslysis time (real).....: "<<lWatchAnalysis.RealTime()<<" seconds"<<endl;
  
  cout<<"Smearing time (CPU).....: "<<lWatchSmearing.CpuTime()<<" seconds"<<endl;
  cout<<"Tracking time (CPU).....: "<<lWatchTracking.CpuTime()<<" seconds"<<endl;
  cout<<"Anslysis time (CPU).....: "<<lWatchAnalysis.CpuTime()<<" seconds"<<endl;
  
}

