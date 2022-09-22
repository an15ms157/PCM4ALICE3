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
//
//#include "TrackSmearer.hh"
//#include "TrackUtils.hh"

#include "DetectorsVertexing/PVertexer.h"
#include "DetectorsVertexing/PVertexerHelpers.h"
#include "CommonDataFormat/BunchFilling.h"

//#include "GPUChainITS.h"
//#include "GPUReconstructionIncludesITS.h"
//#include "DataFormatsITS/TrackITS.h"
//#include <algorithm>

using namespace GPUCA_NAMESPACE::gpu;
using namespace o2::its;

//

//This switch will enable or disable ALL CUTS BELOW
const Float_t lMasterSwitch = -1; //1: ON, -1: OFF

const Bool_t lAssociateXiDaughters = kTRUE;
const Bool_t lAssociateXic = kTRUE;
const Bool_t lAssociateXicc = kTRUE;
//Ask for hohlweger boolean
const Bool_t lHohlwegerBooleanXic = kFALSE;
const Bool_t lHohlwegerBooleanXicc = kFALSE;

//Tracking pass configuration

//Progressively loosening, works OK
const Float_t lFirstOpening = 3.;
const Float_t lOpening = 6.;
const Float_t lThirdPass = 9.;
const Float_t lFourthPass = 12.;

const Float_t lMemoryOffset = 2000;

//{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}
// Cut tune from findable level, alpha 1
//const Float_t TrackletMaxDeltaZMultiplier = 500.0;
//const Float_t CellMaxDCAMultiplier = 10.0;
//const Float_t CellMaxDeltaZMultiplier = 500.0;
//const Float_t NeighbourMaxDeltaCurvatureMultiplier = 250;
//const Float_t NeighbourMaxDeltaNMultiplier = 250.0;
//
//const Float_t TrackletMaxDeltaPhiMultiplier = 1.;
//const Float_t CellMaxDeltaPhiMultiplier = 1.;
//const Float_t CellMaxDeltaTanLambdaMultiplier = 1000.0;
//{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}

//{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}
// Cut tune from findable level, alpha 2
const Float_t TrackletMaxDeltaZMultiplier = 800.0;
const Float_t CellMaxDCAMultiplier = 100.0;
const Float_t CellMaxDeltaZMultiplier = 800.0;
const Float_t NeighbourMaxDeltaCurvatureMultiplier = 500;
const Float_t NeighbourMaxDeltaNMultiplier = 500.0;

const Float_t TrackletMaxDeltaPhiMultiplier = 1.;
const Float_t CellMaxDeltaPhiMultiplier = 1.;
const Float_t CellMaxDeltaTanLambdaMultiplier = 1500.0;
//{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}-{}


//const Float_t lFirstOpening = 6.;
//const Float_t lOpening = 12.;
//const Float_t lThirdPass = 18.;
//const Float_t lFourthPass = 25.;

//===============================================================
// PRESELECTIONS
//===============================================================

//Remove fundamentally insane combinatorics, please
const Float_t lMinV0Radius = lMasterSwitch*0.475; //in centimeters
const Float_t lMinXiRadius = lMasterSwitch*0.475; //in centimeters
const Float_t lMinDCAxyBachelor = lMasterSwitch*0.0040; //in centimeters
const Float_t lMinDCAzBachelor = lMasterSwitch*0.0040; //in centimeters
const Float_t lMinDCAxyPositive = lMasterSwitch*0.0050; //in centimeters
const Float_t lMinDCAzPositive = lMasterSwitch*0.0040; //in centimeters
const Float_t lMinDCAxyNegative = lMasterSwitch*0.0100; //in centimeters
const Float_t lMinDCAzNegative = lMasterSwitch*0.0050; //in centimeters
const Float_t lMinDCAxyHFPions = lMasterSwitch*0.0010; //in centimeters
const Float_t lMinDCAzHFPions  = lMasterSwitch*0.0010; //in centimeters

const Float_t lMassWindowLambda = 0.012;
const Float_t lMassWindowXi = 0.012;
const Float_t lMassWindowXic = 0.060;
const Float_t lMassWindowXicc = 0.6;

const Float_t lMaxDCAV0Daughters = 1000; //in microns
const Float_t lMaxDCACascadeDaughters = 1200; //in microns

const Float_t lMinXiTransverseMomentum = 0.2;
const Float_t lMaxDCAxyPositive = 5000; //in microns

const Float_t lMaxTimeOffsetInnerTOF = 100; //in picoseconds, for weak decay
const Float_t lMaxTimeOffsetHFPions = 100; //in picoseconds, for HF pions

const Float_t lMaxDCAToPVXiCCCandidate = 50; //in microns

const Float_t lMaxDCAXiCDaughters = 50; //in microns
const Float_t lMaxDCAXiCCDaughters = 50; //in microns
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

//+-+-+

//int RunITSTrackFit(std::vector<o2::its::Road>& roads, std::vector<const o2::its::Cluster*>& clusters, std::vector<const o2::its::Cell*>& cells, const std::vector<std::vector<o2::its::TrackingFrameInfo>>& tf, std::vector<o2::its::TrackITSExt>& tracks)
//{
//  auto threadContext = GetThreadContext();
//
//  GPUITSFitter& Fitter = processors()->itsFitter;
//  GPUITSFitter& FitterShadow = Fitter;
//
//  Fitter.clearMemory();
//  Fitter.SetNumberOfRoads(roads.size());
//  for (unsigned int i = 0; i < clusters.size(); i++) {
//    Fitter.SetNumberTF(i, tf[i].size());
//  }
//  Fitter.SetMaxData(processors()->ioPtrs);
//  std::copy(clusters.begin(), clusters.end(), Fitter.clusters());
//  std::copy(cells.begin(), cells.end(), Fitter.cells());
//  SetupGPUProcessor(&Fitter, true);
//  std::copy(roads.begin(), roads.end(), Fitter.roads());
//  for (unsigned int i = 0; i < clusters.size(); i++) {
//    std::copy(tf[i].begin(), tf[i].end(), Fitter.trackingFrame()[i]);
//  }
//
//  WriteToConstantMemory(RecoStep::ITSTracking, (char*)&processors()->itsFitter - (char*)processors(), &FitterShadow, sizeof(FitterShadow), 0);
//  TransferMemoryResourcesToGPU(RecoStep::ITSTracking, &Fitter, 0);
//  runKernel<GPUITSFitterKernel>(GetGridBlk(BlockCount(), 0), krnlRunRangeNone, krnlEventNone);
//  TransferMemoryResourcesToHost(RecoStep::ITSTracking, &Fitter, 0);
//
//  SynchronizeGPU();
//
//  for (unsigned int i = 0; i < Fitter.NumberOfTracks(); i++) {
//    auto& trkin = Fitter.tracks()[i];
//
//    tracks.emplace_back(TrackITSExt{{trkin.X(),
//                                     trkin.mAlpha,
//                                     {trkin.Par()[0], trkin.Par()[1], trkin.Par()[2], trkin.Par()[3], trkin.Par()[4]},
//                                     {trkin.Cov()[0], trkin.Cov()[1], trkin.Cov()[2], trkin.Cov()[3], trkin.Cov()[4], trkin.Cov()[5], trkin.Cov()[6], trkin.Cov()[7], trkin.Cov()[8], trkin.Cov()[9], trkin.Cov()[10], trkin.Cov()[11], trkin.Cov()[12], trkin.Cov()[13], trkin.Cov()[14]}},
//                                    (short int)((trkin.NDF() + 5) / 2),
//                                    trkin.Chi2(),
//                                    {trkin.mOuterParam.X,
//                                     trkin.mOuterParam.alpha,
//                                     {trkin.mOuterParam.P[0], trkin.mOuterParam.P[1], trkin.mOuterParam.P[2], trkin.mOuterParam.P[3], trkin.mOuterParam.P[4]},
//                                     {trkin.mOuterParam.C[0], trkin.mOuterParam.C[1], trkin.mOuterParam.C[2], trkin.mOuterParam.C[3], trkin.mOuterParam.C[4], trkin.mOuterParam.C[5], trkin.mOuterParam.C[6], trkin.mOuterParam.C[7], trkin.mOuterParam.C[8], trkin.mOuterParam.C[9],
//                                      trkin.mOuterParam.C[10], trkin.mOuterParam.C[11], trkin.mOuterParam.C[12], trkin.mOuterParam.C[13], trkin.mOuterParam.C[14]}},
//                                    {{trkin.mClusters[0], trkin.mClusters[1], trkin.mClusters[2], trkin.mClusters[3], trkin.mClusters[4], trkin.mClusters[5], trkin.mClusters[6]}}});
//  }
//  return 0;
//}

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

//class SmearO2KineGenerator : public o2::eventgen::GeneratorFromO2Kine
//{
//public:
//  SmearO2KineGenerator(const char *name) : GeneratorFromO2Kine(name) { };
//  bool Init() override {
//    auto retval = o2::eventgen::GeneratorFromO2Kine::Init();
//    setContinueMode(true);
//    return retval; };
//  //  bool importParticles() override {
//protected:
//
//};

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

void runtracking(TString lDataPath = "./", TString lLutPath =  "../")
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
  
  //We are going to have to create
  //tracker12 [0]  0.50
  //tracker11 [1]  1.20
  //tracker10 [2]  2.50
  //tracker09 [3]  3.75
  //tracker08 [4]  7.00
  //tracker07 [5] 12.00
  //tracker06 [6] 20.00
  
  // o2::its::Tracker tracker(new o2::its::TrackerTraitsCPU());
  
  o2::its::Tracker tracker0(new o2::its::TrackerTraitsCPU());
  o2::its::Tracker tracker1(new o2::its::TrackerTraitsCPU());
  o2::its::Tracker tracker2(new o2::its::TrackerTraitsCPU());
  o2::its::Tracker tracker3(new o2::its::TrackerTraitsCPU());
  o2::its::Tracker tracker4(new o2::its::TrackerTraitsCPU());
  o2::its::Tracker tracker5(new o2::its::TrackerTraitsCPU());
  o2::its::Tracker tracker6(new o2::its::TrackerTraitsCPU());
  
  tracker0.setBz(lMagneticField);
  tracker1.setBz(lMagneticField);
  tracker2.setBz(lMagneticField);
  tracker3.setBz(lMagneticField);
  tracker4.setBz(lMagneticField);
  tracker5.setBz(lMagneticField);
  tracker6.setBz(lMagneticField);
  
  tracker0.setCorrType(o2::base::PropagatorImpl<float>::MatCorrType::USEMatCorrTGeo);
  tracker1.setCorrType(o2::base::PropagatorImpl<float>::MatCorrType::USEMatCorrTGeo);
  tracker2.setCorrType(o2::base::PropagatorImpl<float>::MatCorrType::USEMatCorrTGeo);
  tracker3.setCorrType(o2::base::PropagatorImpl<float>::MatCorrType::USEMatCorrTGeo);
  tracker4.setCorrType(o2::base::PropagatorImpl<float>::MatCorrType::USEMatCorrTGeo);
  tracker5.setCorrType(o2::base::PropagatorImpl<float>::MatCorrType::USEMatCorrTGeo);
  tracker6.setCorrType(o2::base::PropagatorImpl<float>::MatCorrType::USEMatCorrTGeo);
  
  std::uint32_t roFrame;
  std::vector<Hit>* hits = nullptr;
  itsHits.SetBranchAddress("TRKHit", &hits);
  
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  // TRACKING PARAMETERS
  std::vector<float> LayerRadii = {0.5f, 1.2f, 2.5f, 3.75f, 7.0f, 12.0f, 20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  std::vector<float> LayerZ(12);
  for (int i{0}; i < 12; ++i)
  LayerZ[i] = getDetLengthFromEta(1.44, LayerRadii[i]) + 1.;
  
  Double_t LayerRadiiArray[] = {0.5f, 1.2f, 2.5f, 3.75f, 7.0f, 12.0f, 20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  
  TH1D *hRadii = new TH1D("hRadii", "", 11, LayerRadiiArray);
  TH1D *hRadiiAll = new TH1D("hRadiiAll", "", 11, LayerRadiiArray);
  TH1D *hRadiiGenerated = new TH1D("hRadiiGenerated", "", 11, LayerRadiiArray);
  
  TH1D *hHitCountAll = new TH1D("hHitCountAll", "", 100,0,100);
  TH1D *hHitCountFound = new TH1D("hHitCountFound", "", 100,0,100);
  
  // EXPERIMENTAL THREE-PASS VERSION
  std::vector<TrackingParameters> trackParams(4);
  //Tracking parameters for 12 layer setup
  trackParams[0].NLayers = 12;
  trackParams[0].MinTrackLength = 6; //this is the one with fixed params
  
  //loosely based on run_trac_alice3.C but with extra stuff for the innermost layers
  //FIXME: This may be subject to further tuning and is only a first guess
  std::vector<float> TrackletMaxDeltaZ = {TrackletMaxDeltaZMultiplier*lFirstOpening*0.1f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.1f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.1f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.1f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.3f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.3f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.3f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.3f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.5f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.5f, TrackletMaxDeltaZMultiplier*lFirstOpening*0.5f};
  
  std::vector<float> CellMaxDCA = {CellMaxDCAMultiplier*lFirstOpening*0.05f, CellMaxDCAMultiplier*lFirstOpening*0.05f, CellMaxDCAMultiplier*lFirstOpening*0.05f, CellMaxDCAMultiplier*lFirstOpening*0.04f, CellMaxDCAMultiplier*lFirstOpening*0.05f, CellMaxDCAMultiplier*lFirstOpening*0.2f, CellMaxDCAMultiplier*lFirstOpening*0.4f, CellMaxDCAMultiplier*lFirstOpening*0.5f, CellMaxDCAMultiplier*lFirstOpening*0.5f, CellMaxDCAMultiplier*lFirstOpening*0.5f};
  
  std::vector<float> CellMaxDeltaZ = {CellMaxDeltaZMultiplier*lFirstOpening*0.2f, CellMaxDeltaZMultiplier*lFirstOpening*0.2f, CellMaxDeltaZMultiplier*lFirstOpening*0.2f,CellMaxDeltaZMultiplier*lFirstOpening*0.4f, CellMaxDeltaZMultiplier*lFirstOpening*0.5f, CellMaxDeltaZMultiplier*lFirstOpening*0.6f, CellMaxDeltaZMultiplier*lFirstOpening*3.0f, CellMaxDeltaZMultiplier*lFirstOpening*3.0f, CellMaxDeltaZMultiplier*lFirstOpening*3.0f,CellMaxDeltaZMultiplier*lFirstOpening*3.0f};
  
  std::vector<float> NeighbourMaxDeltaCurvature = {NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.012f, NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.010f, NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.008f, NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.0025f, NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.003f, NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.0035f, NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.004f, NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.004f, NeighbourMaxDeltaCurvatureMultiplier*lFirstOpening*0.005f};
  
  std::vector<float> NeighbourMaxDeltaN = {NeighbourMaxDeltaNMultiplier*lFirstOpening*0.002f, NeighbourMaxDeltaNMultiplier*lFirstOpening*0.002f, NeighbourMaxDeltaNMultiplier*lFirstOpening*0.002f, NeighbourMaxDeltaNMultiplier*lFirstOpening*0.0090f, NeighbourMaxDeltaNMultiplier*lFirstOpening*0.002f, NeighbourMaxDeltaNMultiplier*lFirstOpening*0.005f,
    NeighbourMaxDeltaNMultiplier*lFirstOpening* 0.005f,NeighbourMaxDeltaNMultiplier*lFirstOpening* 0.005f, NeighbourMaxDeltaNMultiplier*lFirstOpening*0.005f};
  
  //Second pass - looser cuts, shorter tracks
  std::vector<float> SecondTrackletMaxDeltaZ = {TrackletMaxDeltaZMultiplier*lOpening*0.1f, TrackletMaxDeltaZMultiplier*lOpening*0.1f, TrackletMaxDeltaZMultiplier*lOpening*0.1f, TrackletMaxDeltaZMultiplier*lOpening*0.1f, TrackletMaxDeltaZMultiplier*lOpening*0.3f, TrackletMaxDeltaZMultiplier*lOpening*0.3f, TrackletMaxDeltaZMultiplier*lOpening*0.3f, TrackletMaxDeltaZMultiplier*lOpening*0.3f, TrackletMaxDeltaZMultiplier*lOpening*0.5f, TrackletMaxDeltaZMultiplier*lOpening*0.5f, TrackletMaxDeltaZMultiplier*lOpening*0.5f};
  
  std::vector<float> SecondCellMaxDCA = {CellMaxDCAMultiplier*lOpening*0.05f, CellMaxDCAMultiplier*lOpening*0.05f, CellMaxDCAMultiplier*lOpening*0.05f, CellMaxDCAMultiplier*lOpening*0.04f, CellMaxDCAMultiplier*lOpening*0.05f, CellMaxDCAMultiplier*lOpening*0.2f, CellMaxDCAMultiplier*lOpening*0.4f, CellMaxDCAMultiplier*lOpening*0.5f, CellMaxDCAMultiplier*lOpening*0.5f, CellMaxDCAMultiplier*lOpening*0.5f};
  
  std::vector<float> SecondCellMaxDeltaZ = {CellMaxDeltaZMultiplier*lOpening*0.2f, CellMaxDeltaZMultiplier*lOpening*0.2f, CellMaxDeltaZMultiplier*lOpening*0.2f,CellMaxDeltaZMultiplier*lOpening*0.4f, CellMaxDeltaZMultiplier*lOpening*0.5f, CellMaxDeltaZMultiplier*lOpening*0.6f, CellMaxDeltaZMultiplier*lOpening*3.0f, CellMaxDeltaZMultiplier*lOpening*3.0f, CellMaxDeltaZMultiplier*lOpening*3.0f,CellMaxDeltaZMultiplier*lOpening*3.0f};
  
  std::vector<float> SecondNeighbourMaxDeltaCurvature = {NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.012f, NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.010f, NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.008f, NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.0025f, NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.003f, NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.0035f, NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.004f, NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.004f, NeighbourMaxDeltaCurvatureMultiplier*lOpening*0.005f};
  
  std::vector<float> SecondNeighbourMaxDeltaN = {NeighbourMaxDeltaNMultiplier*lOpening*0.002f, NeighbourMaxDeltaNMultiplier*lOpening*0.002f, NeighbourMaxDeltaNMultiplier*lOpening*0.002f, NeighbourMaxDeltaNMultiplier*lOpening*0.0090f, NeighbourMaxDeltaNMultiplier*lOpening*0.002f, NeighbourMaxDeltaNMultiplier*lOpening*0.005f, NeighbourMaxDeltaNMultiplier*lOpening* 0.005f,NeighbourMaxDeltaNMultiplier*lOpening* 0.005f, NeighbourMaxDeltaNMultiplier*lOpening*0.005f};
  
  //Third pass: loosest, pick up more secondaries
  std::vector<float> ThirdTrackletMaxDeltaZ = {TrackletMaxDeltaZMultiplier*lThirdPass*0.1f, TrackletMaxDeltaZMultiplier*lThirdPass*0.1f, TrackletMaxDeltaZMultiplier*lThirdPass*0.1f, TrackletMaxDeltaZMultiplier*lThirdPass*0.1f, TrackletMaxDeltaZMultiplier*lThirdPass*0.3f, TrackletMaxDeltaZMultiplier*lThirdPass*0.3f, TrackletMaxDeltaZMultiplier*lThirdPass*0.3f, TrackletMaxDeltaZMultiplier*lThirdPass*0.3f, TrackletMaxDeltaZMultiplier*lThirdPass*0.5f, TrackletMaxDeltaZMultiplier*lThirdPass*0.5f, TrackletMaxDeltaZMultiplier*lThirdPass*0.5f};
  
  std::vector<float> ThirdCellMaxDCA = {CellMaxDCAMultiplier*lThirdPass*0.05f, CellMaxDCAMultiplier*lThirdPass*0.05f, CellMaxDCAMultiplier*lThirdPass*0.05f, CellMaxDCAMultiplier*lThirdPass*0.04f, CellMaxDCAMultiplier*lThirdPass*0.05f, CellMaxDCAMultiplier*lThirdPass*0.2f, CellMaxDCAMultiplier*lThirdPass*0.4f, CellMaxDCAMultiplier*lThirdPass*0.5f, CellMaxDCAMultiplier*lThirdPass*0.5f, CellMaxDCAMultiplier*lThirdPass*0.5f};
  
  std::vector<float> ThirdCellMaxDeltaZ = {CellMaxDeltaZMultiplier*lThirdPass*0.2f, CellMaxDeltaZMultiplier*lThirdPass*0.2f, CellMaxDeltaZMultiplier*lThirdPass*0.2f,CellMaxDeltaZMultiplier*lThirdPass*0.4f, CellMaxDeltaZMultiplier*lThirdPass*0.5f, CellMaxDeltaZMultiplier*lThirdPass*0.6f, CellMaxDeltaZMultiplier*lThirdPass*3.0f, CellMaxDeltaZMultiplier*lThirdPass*3.0f, CellMaxDeltaZMultiplier*lThirdPass*3.0f,CellMaxDeltaZMultiplier*lThirdPass*3.0f};
  
  std::vector<float> ThirdNeighbourMaxDeltaCurvature = {NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.012f, NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.010f, NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.008f, NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.0025f, NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.003f, NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.0035f, NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.004f, NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.004f, NeighbourMaxDeltaCurvatureMultiplier*lThirdPass*0.005f};
  
  std::vector<float> ThirdNeighbourMaxDeltaN = {NeighbourMaxDeltaNMultiplier*lThirdPass*0.002f, NeighbourMaxDeltaNMultiplier*lThirdPass*0.002f, NeighbourMaxDeltaNMultiplier*lThirdPass*0.002f, NeighbourMaxDeltaNMultiplier*lThirdPass*0.0090f, NeighbourMaxDeltaNMultiplier*lThirdPass*0.002f, NeighbourMaxDeltaNMultiplier*lThirdPass*0.005f, NeighbourMaxDeltaNMultiplier*lThirdPass* 0.005f,NeighbourMaxDeltaNMultiplier*lThirdPass* 0.005f, NeighbourMaxDeltaNMultiplier*lThirdPass*0.005f};
  
  //Fourth pass: bonus
  std::vector<float> FourthTrackletMaxDeltaZ = {TrackletMaxDeltaZMultiplier*lFourthPass*0.1f, TrackletMaxDeltaZMultiplier*lFourthPass*0.1f, TrackletMaxDeltaZMultiplier*lFourthPass*0.1f, TrackletMaxDeltaZMultiplier*lFourthPass*0.1f, TrackletMaxDeltaZMultiplier*lFourthPass*0.3f, TrackletMaxDeltaZMultiplier*lFourthPass*0.3f, TrackletMaxDeltaZMultiplier*lFourthPass*0.3f, TrackletMaxDeltaZMultiplier*lFourthPass*0.3f, TrackletMaxDeltaZMultiplier*lFourthPass*0.5f, TrackletMaxDeltaZMultiplier*lFourthPass*0.5f, TrackletMaxDeltaZMultiplier*lFourthPass*0.5f};
  
  std::vector<float> FourthCellMaxDCA = {CellMaxDCAMultiplier*lFourthPass*0.05f, CellMaxDCAMultiplier*lFourthPass*0.05f, CellMaxDCAMultiplier*lFourthPass*0.05f, CellMaxDCAMultiplier*lFourthPass*0.04f, CellMaxDCAMultiplier*lFourthPass*0.05f, CellMaxDCAMultiplier*lFourthPass*0.2f, CellMaxDCAMultiplier*lFourthPass*0.4f, CellMaxDCAMultiplier*lFourthPass*0.5f, CellMaxDCAMultiplier*lFourthPass*0.5f, CellMaxDCAMultiplier*lFourthPass*0.5f};
  
  std::vector<float> FourthCellMaxDeltaZ = {CellMaxDeltaZMultiplier*lFourthPass*0.2f, CellMaxDeltaZMultiplier*lFourthPass*0.2f, CellMaxDeltaZMultiplier*lFourthPass*0.2f,CellMaxDeltaZMultiplier*lFourthPass*0.4f, CellMaxDeltaZMultiplier*lFourthPass*0.5f, CellMaxDeltaZMultiplier*lFourthPass*0.6f, CellMaxDeltaZMultiplier*lFourthPass*3.0f, CellMaxDeltaZMultiplier*lFourthPass*3.0f, CellMaxDeltaZMultiplier*lFourthPass*3.0f,CellMaxDeltaZMultiplier*lFourthPass*3.0f};
  
  std::vector<float> FourthNeighbourMaxDeltaCurvature = {NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.012f, NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.010f, NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.008f, NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.0025f, NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.003f, NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.0035f, NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.004f, NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.004f, NeighbourMaxDeltaCurvatureMultiplier*lFourthPass*0.005f};
  
  std::vector<float> FourthNeighbourMaxDeltaN = {NeighbourMaxDeltaNMultiplier*lFourthPass*0.002f, NeighbourMaxDeltaNMultiplier*lFourthPass*0.002f, NeighbourMaxDeltaNMultiplier*lFourthPass*0.002f, NeighbourMaxDeltaNMultiplier*lFourthPass*0.0090f,NeighbourMaxDeltaNMultiplier*lFourthPass*0.002f, NeighbourMaxDeltaNMultiplier*lFourthPass*0.005f, NeighbourMaxDeltaNMultiplier*lFourthPass* 0.005f,NeighbourMaxDeltaNMultiplier*lFourthPass* 0.005f, NeighbourMaxDeltaNMultiplier*lFourthPass*0.005f};
  
  trackParams[0].LayerRadii = LayerRadii;
  trackParams[0].LayerZ = LayerZ;
  trackParams[0].TrackletMaxDeltaPhi = TMath::Min(lFirstOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams[0].CellMaxDeltaPhi = TMath::Min(lFirstOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams[0].CellMaxDeltaTanLambda = lFirstOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams[0].TrackletMaxDeltaZ = TrackletMaxDeltaZ;
  trackParams[0].CellMaxDCA = CellMaxDCA;
  trackParams[0].CellMaxDeltaZ = CellMaxDeltaZ;
  trackParams[0].NeighbourMaxDeltaCurvature = NeighbourMaxDeltaCurvature;
  trackParams[0].NeighbourMaxDeltaN = NeighbourMaxDeltaN;
  
  Float_t lFactor = 50;
  std::vector<MemoryParameters> memParams(4);
  std::vector<float> CellsMemoryCoefficients = {2.3208e-08f * 10, 2.104e-08f * 10, 1.6432e-08f * 10, 1.2412e-08f * 10, 1.3543e-08f * 10, 1.5e-08f * 10, 1.6e-08f * 10, 1.7e-08f * 10};
  std::vector<float> TrackletsMemoryCoefficients = {0.0016353f * lFactor, 0.0013627f * lFactor, 0.000984f * lFactor, 0.00078135f * lFactor, 0.00057934f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor};
  
  memParams[0].CellsMemoryCoefficients = CellsMemoryCoefficients;
  memParams[0].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients;
  memParams[0].MemoryOffset = lMemoryOffset;
  
  //Pass 2: capture long tracks that are lower in pT, etc
  trackParams[1].NLayers = 12;
  trackParams[1].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams[1].LayerRadii = LayerRadii;
  trackParams[1].LayerZ = LayerZ;
  trackParams[1].TrackletMaxDeltaPhi = TMath::Min(lOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams[1].CellMaxDeltaPhi = TMath::Min(lOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams[1].CellMaxDeltaTanLambda = lOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams[1].TrackletMaxDeltaZ = SecondTrackletMaxDeltaZ;
  trackParams[1].CellMaxDCA = SecondCellMaxDCA;
  trackParams[1].CellMaxDeltaZ = SecondCellMaxDeltaZ;
  trackParams[1].NeighbourMaxDeltaCurvature = SecondNeighbourMaxDeltaCurvature;
  trackParams[1].NeighbourMaxDeltaN = SecondNeighbourMaxDeltaN;
  
  memParams[1].CellsMemoryCoefficients = CellsMemoryCoefficients;
  memParams[1].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients;
  memParams[1].MemoryOffset = lMemoryOffset;
  
  //Pass 3: Secondaries
  trackParams[2].NLayers = 12;
  trackParams[2].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams[2].LayerRadii = LayerRadii;
  trackParams[2].LayerZ = LayerZ;
  trackParams[2].TrackletMaxDeltaPhi = TMath::Min(lThirdPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams[2].CellMaxDeltaPhi = TMath::Min(lThirdPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams[2].CellMaxDeltaTanLambda = lThirdPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams[2].TrackletMaxDeltaZ = ThirdTrackletMaxDeltaZ;
  trackParams[2].CellMaxDCA = ThirdCellMaxDCA;
  trackParams[2].CellMaxDeltaZ = ThirdCellMaxDeltaZ;
  trackParams[2].NeighbourMaxDeltaCurvature = ThirdNeighbourMaxDeltaCurvature;
  trackParams[2].NeighbourMaxDeltaN = ThirdNeighbourMaxDeltaN;
  
  memParams[2].CellsMemoryCoefficients = CellsMemoryCoefficients;
  memParams[2].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients;
  memParams[2].MemoryOffset = lMemoryOffset;
  
  //Pass 4: Bonus
  trackParams[3].NLayers = 12;
  trackParams[3].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams[3].LayerRadii = LayerRadii;
  trackParams[3].LayerZ = LayerZ;
  trackParams[3].TrackletMaxDeltaPhi = TMath::Min(lFourthPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams[3].CellMaxDeltaPhi = TMath::Min(lFourthPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams[3].CellMaxDeltaTanLambda = lFourthPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams[3].TrackletMaxDeltaZ = FourthTrackletMaxDeltaZ;
  trackParams[3].CellMaxDCA = FourthCellMaxDCA;
  trackParams[3].CellMaxDeltaZ = FourthCellMaxDeltaZ;
  trackParams[3].NeighbourMaxDeltaCurvature = FourthNeighbourMaxDeltaCurvature;
  trackParams[3].NeighbourMaxDeltaN = FourthNeighbourMaxDeltaN;
  
  memParams[3].CellsMemoryCoefficients = CellsMemoryCoefficients;
  memParams[3].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients;
  memParams[3].MemoryOffset = lMemoryOffset;
  
  tracker0.setParameters(memParams, trackParams);
  
  //Now we go ahead and try and duplicate settings while removing the innermost layers
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  // TRACKING PARAMETERS ONE
  std::vector<float> LayerRadii1 = {1.2f, 2.5f, 3.75f, 7.0f, 12.0f, 20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  std::vector<float> LayerZ1(11);
  for (int i{0}; i < 11; ++i)
  LayerZ1[i] = getDetLengthFromEta(1.44, LayerRadii1[i]) + 1.;
  
  // EXPERIMENTAL THREE-PASS VERSION
  std::vector<TrackingParameters> trackParams1(4);
  //Tracking parameters for 12 layer setup
  trackParams1[0].NLayers = 11;
  trackParams1[0].MinTrackLength = 6; //this is the one with fixed params
  
  //loosely based on run_trac_alice3.C but with extra stuff for the innermost layers
  //FIXME: This may be subject to further tuning and is only a first guess
  std::vector<float> TrackletMaxDeltaZ1;
  std::vector<float> CellMaxDCA1;
  std::vector<float> CellMaxDeltaZ1;
  std::vector<float> NeighbourMaxDeltaCurvature1;
  std::vector<float> NeighbourMaxDeltaN1;
  
  for (int i=1; i<TrackletMaxDeltaZ.size(); i++)            TrackletMaxDeltaZ1.push_back(TrackletMaxDeltaZ[i]);
  for (int i=1; i<CellMaxDCA.size(); i++)                   CellMaxDCA1.push_back(CellMaxDCA[i]);
  for (int i=1; i<CellMaxDeltaZ.size(); i++)                CellMaxDeltaZ1.push_back(CellMaxDeltaZ[i]);
  for (int i=1; i<NeighbourMaxDeltaCurvature.size(); i++)   NeighbourMaxDeltaCurvature1.push_back(NeighbourMaxDeltaCurvature[i]);
  for (int i=1; i<NeighbourMaxDeltaN.size(); i++)           NeighbourMaxDeltaN1.push_back(NeighbourMaxDeltaN[i]);
  
  //Second pass - looser cuts, shorter tracks
  std::vector<float> SecondTrackletMaxDeltaZ1;
  std::vector<float> SecondCellMaxDCA1;
  std::vector<float> SecondCellMaxDeltaZ1;
  std::vector<float> SecondNeighbourMaxDeltaCurvature1;
  std::vector<float> SecondNeighbourMaxDeltaN1;
  
  for (int i=1; i<SecondTrackletMaxDeltaZ.size(); i++)            SecondTrackletMaxDeltaZ1.push_back(SecondTrackletMaxDeltaZ[i]);
  for (int i=1; i<SecondCellMaxDCA.size(); i++)                   SecondCellMaxDCA1.push_back(SecondCellMaxDCA[i]);
  for (int i=1; i<SecondCellMaxDeltaZ.size(); i++)                SecondCellMaxDeltaZ1.push_back(SecondCellMaxDeltaZ[i]);
  for (int i=1; i<SecondNeighbourMaxDeltaCurvature.size(); i++)   SecondNeighbourMaxDeltaCurvature1.push_back(SecondNeighbourMaxDeltaCurvature[i]);
  for (int i=1; i<SecondNeighbourMaxDeltaN.size(); i++)           SecondNeighbourMaxDeltaN1.push_back(SecondNeighbourMaxDeltaN[i]);
  
  //Third pass: loosest, pick up more secondaries
  std::vector<float> ThirdTrackletMaxDeltaZ1;
  std::vector<float> ThirdCellMaxDCA1;
  std::vector<float> ThirdCellMaxDeltaZ1;
  std::vector<float> ThirdNeighbourMaxDeltaCurvature1;
  std::vector<float> ThirdNeighbourMaxDeltaN1;
  
  for (int i=1; i<ThirdTrackletMaxDeltaZ.size(); i++)            ThirdTrackletMaxDeltaZ1.push_back(ThirdTrackletMaxDeltaZ[i]);
  for (int i=1; i<ThirdCellMaxDCA.size(); i++)                   ThirdCellMaxDCA1.push_back(ThirdCellMaxDCA[i]);
  for (int i=1; i<ThirdCellMaxDeltaZ.size(); i++)                ThirdCellMaxDeltaZ1.push_back(ThirdCellMaxDeltaZ[i]);
  for (int i=1; i<ThirdNeighbourMaxDeltaCurvature.size(); i++)   ThirdNeighbourMaxDeltaCurvature1.push_back(ThirdNeighbourMaxDeltaCurvature[i]);
  for (int i=1; i<ThirdNeighbourMaxDeltaN.size(); i++)           ThirdNeighbourMaxDeltaN1.push_back(ThirdNeighbourMaxDeltaN[i]);
  
  //Fourth pass: bonus
  std::vector<float> FourthTrackletMaxDeltaZ1;
  std::vector<float> FourthCellMaxDCA1;
  std::vector<float> FourthCellMaxDeltaZ1;
  std::vector<float> FourthNeighbourMaxDeltaCurvature1;
  std::vector<float> FourthNeighbourMaxDeltaN1;
  
  for (int i=1; i<FourthTrackletMaxDeltaZ.size(); i++)            FourthTrackletMaxDeltaZ1.push_back(FourthTrackletMaxDeltaZ[i]);
  for (int i=1; i<FourthCellMaxDCA.size(); i++)                   FourthCellMaxDCA1.push_back(FourthCellMaxDCA[i]);
  for (int i=1; i<FourthCellMaxDeltaZ.size(); i++)                FourthCellMaxDeltaZ1.push_back(FourthCellMaxDeltaZ[i]);
  for (int i=1; i<FourthNeighbourMaxDeltaCurvature.size(); i++)   FourthNeighbourMaxDeltaCurvature1.push_back(FourthNeighbourMaxDeltaCurvature[i]);
  for (int i=1; i<FourthNeighbourMaxDeltaN.size(); i++)           FourthNeighbourMaxDeltaN1.push_back(FourthNeighbourMaxDeltaN[i]);
  
  trackParams1[0].LayerRadii = LayerRadii1;
  trackParams1[0].LayerZ = LayerZ1;
  trackParams1[0].TrackletMaxDeltaPhi = TMath::Min(lFirstOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams1[0].CellMaxDeltaPhi = TMath::Min(lFirstOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams1[0].CellMaxDeltaTanLambda = lFirstOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams1[0].TrackletMaxDeltaZ = TrackletMaxDeltaZ1;
  trackParams1[0].CellMaxDCA = CellMaxDCA1;
  trackParams1[0].CellMaxDeltaZ = CellMaxDeltaZ1;
  trackParams1[0].NeighbourMaxDeltaCurvature = NeighbourMaxDeltaCurvature1;
  trackParams1[0].NeighbourMaxDeltaN = NeighbourMaxDeltaN1;
  
  std::vector<MemoryParameters> memParams1(4);
  std::vector<float> CellsMemoryCoefficients1 = {2.104e-08f * 10, 1.6432e-08f * 10, 1.2412e-08f * 10, 1.3543e-08f * 10, 1.5e-08f * 10, 1.6e-08f * 10, 1.7e-08f * 10};
  std::vector<float> TrackletsMemoryCoefficients1 = {0.0013627f * lFactor, 0.000984f * lFactor, 0.00078135f * lFactor, 0.00057934f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor};
  
  memParams1[0].CellsMemoryCoefficients = CellsMemoryCoefficients1;
  memParams1[0].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients1;
  memParams1[0].MemoryOffset = lMemoryOffset;
  
  //Pass 2: capture long tracks that are lower in pT, etc
  trackParams1[1].NLayers = 11;
  trackParams1[1].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams1[1].LayerRadii = LayerRadii1;
  trackParams1[1].LayerZ = LayerZ1;
  trackParams1[1].TrackletMaxDeltaPhi = TMath::Min(lOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams1[1].CellMaxDeltaPhi = TMath::Min(lOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams1[1].CellMaxDeltaTanLambda = lOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams1[1].TrackletMaxDeltaZ = SecondTrackletMaxDeltaZ1;
  trackParams1[1].CellMaxDCA = SecondCellMaxDCA1;
  trackParams1[1].CellMaxDeltaZ = SecondCellMaxDeltaZ1;
  trackParams1[1].NeighbourMaxDeltaCurvature = SecondNeighbourMaxDeltaCurvature1;
  trackParams1[1].NeighbourMaxDeltaN = SecondNeighbourMaxDeltaN1;
  
  memParams1[1].CellsMemoryCoefficients = CellsMemoryCoefficients1;
  memParams1[1].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients1;
  memParams1[1].MemoryOffset = lMemoryOffset;
  
  //Pass 3: Secondaries
  trackParams1[2].NLayers = 11;
  trackParams1[2].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams1[2].LayerRadii = LayerRadii1;
  trackParams1[2].LayerZ = LayerZ1;
  trackParams1[2].TrackletMaxDeltaPhi = TMath::Min(lThirdPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams1[2].CellMaxDeltaPhi = TMath::Min(lThirdPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams1[2].CellMaxDeltaTanLambda = lThirdPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams1[2].TrackletMaxDeltaZ = ThirdTrackletMaxDeltaZ1;
  trackParams1[2].CellMaxDCA = ThirdCellMaxDCA1;
  trackParams1[2].CellMaxDeltaZ = ThirdCellMaxDeltaZ1;
  trackParams1[2].NeighbourMaxDeltaCurvature = ThirdNeighbourMaxDeltaCurvature1;
  trackParams1[2].NeighbourMaxDeltaN = ThirdNeighbourMaxDeltaN1;
  
  memParams1[2].CellsMemoryCoefficients = CellsMemoryCoefficients1;
  memParams1[2].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients1;
  memParams1[2].MemoryOffset = lMemoryOffset;
  
  //Pass 4: Bonus
  trackParams1[3].NLayers = 11;
  trackParams1[3].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams1[3].LayerRadii = LayerRadii1;
  trackParams1[3].LayerZ = LayerZ1;
  trackParams1[3].TrackletMaxDeltaPhi = TMath::Min(lFourthPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams1[3].CellMaxDeltaPhi = TMath::Min(lFourthPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams1[3].CellMaxDeltaTanLambda = lFourthPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams1[3].TrackletMaxDeltaZ = FourthTrackletMaxDeltaZ1;
  trackParams1[3].CellMaxDCA = FourthCellMaxDCA1;
  trackParams1[3].CellMaxDeltaZ = FourthCellMaxDeltaZ1;
  trackParams1[3].NeighbourMaxDeltaCurvature = FourthNeighbourMaxDeltaCurvature1;
  trackParams1[3].NeighbourMaxDeltaN = FourthNeighbourMaxDeltaN1;
  
  memParams1[3].CellsMemoryCoefficients = CellsMemoryCoefficients1;
  memParams1[3].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients1;
  memParams1[3].MemoryOffset = lMemoryOffset;
  
  tracker1.setParameters(memParams1, trackParams1);
  
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  // TRACKING PARAMETERS TWO
  std::vector<float> LayerRadii2 = {2.5f, 3.75f, 7.0f, 12.0f, 20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  std::vector<float> LayerZ2(10);
  for (int i{0}; i < 10; ++i)
  LayerZ2[i] = getDetLengthFromEta(1.44, LayerRadii2[i]) + 1.;
  
  // EXPERIMENTAL THREE-PASS VERSION
  std::vector<TrackingParameters> trackParams2(4);
  //Tracking parameters for 12 layer setup
  trackParams2[0].NLayers = 10;
  trackParams2[0].MinTrackLength = 6; //this is the one with fixed params
  
  Int_t lThisIndex = 2;
  
  //loosely based on run_trac_alice3.C but with extra stuff for the innermost layers
  //FIXME: This may be subject to further tuning and is only a first guess
  std::vector<float> TrackletMaxDeltaZ2;
  std::vector<float> CellMaxDCA2;
  std::vector<float> CellMaxDeltaZ2;
  std::vector<float> NeighbourMaxDeltaCurvature2;
  std::vector<float> NeighbourMaxDeltaN2;
  
  for (int i=lThisIndex; i<TrackletMaxDeltaZ.size(); i++)            TrackletMaxDeltaZ2.push_back(TrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<CellMaxDCA.size(); i++)                   CellMaxDCA2.push_back(CellMaxDCA[i]);
  for (int i=lThisIndex; i<CellMaxDeltaZ.size(); i++)                CellMaxDeltaZ2.push_back(CellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaCurvature.size(); i++)   NeighbourMaxDeltaCurvature2.push_back(NeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaN.size(); i++)           NeighbourMaxDeltaN2.push_back(NeighbourMaxDeltaN[i]);
  
  //Second pass - looser cuts, shorter tracks
  std::vector<float> SecondTrackletMaxDeltaZ2;
  std::vector<float> SecondCellMaxDCA2;
  std::vector<float> SecondCellMaxDeltaZ2;
  std::vector<float> SecondNeighbourMaxDeltaCurvature2;
  std::vector<float> SecondNeighbourMaxDeltaN2;
  
  for (int i=lThisIndex; i<SecondTrackletMaxDeltaZ.size(); i++)            SecondTrackletMaxDeltaZ2.push_back(SecondTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondCellMaxDCA.size(); i++)                   SecondCellMaxDCA2.push_back(SecondCellMaxDCA[i]);
  for (int i=lThisIndex; i<SecondCellMaxDeltaZ.size(); i++)                SecondCellMaxDeltaZ2.push_back(SecondCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaCurvature.size(); i++)   SecondNeighbourMaxDeltaCurvature2.push_back(SecondNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaN.size(); i++)           SecondNeighbourMaxDeltaN2.push_back(SecondNeighbourMaxDeltaN[i]);
  
  //Third pass: loosest, pick up more secondaries
  std::vector<float> ThirdTrackletMaxDeltaZ2;
  std::vector<float> ThirdCellMaxDCA2;
  std::vector<float> ThirdCellMaxDeltaZ2;
  std::vector<float> ThirdNeighbourMaxDeltaCurvature2;
  std::vector<float> ThirdNeighbourMaxDeltaN2;
  
  for (int i=lThisIndex; i<ThirdTrackletMaxDeltaZ.size(); i++)            ThirdTrackletMaxDeltaZ2.push_back(ThirdTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDCA.size(); i++)                   ThirdCellMaxDCA2.push_back(ThirdCellMaxDCA[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDeltaZ.size(); i++)                ThirdCellMaxDeltaZ2.push_back(ThirdCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaCurvature.size(); i++)   ThirdNeighbourMaxDeltaCurvature2.push_back(ThirdNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaN.size(); i++)           ThirdNeighbourMaxDeltaN2.push_back(ThirdNeighbourMaxDeltaN[i]);
  
  //Fourth pass: bonus
  std::vector<float> FourthTrackletMaxDeltaZ2;
  std::vector<float> FourthCellMaxDCA2;
  std::vector<float> FourthCellMaxDeltaZ2;
  std::vector<float> FourthNeighbourMaxDeltaCurvature2;
  std::vector<float> FourthNeighbourMaxDeltaN2;
  
  for (int i=lThisIndex; i<FourthTrackletMaxDeltaZ.size(); i++)            FourthTrackletMaxDeltaZ2.push_back(FourthTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthCellMaxDCA.size(); i++)                   FourthCellMaxDCA2.push_back(FourthCellMaxDCA[i]);
  for (int i=lThisIndex; i<FourthCellMaxDeltaZ.size(); i++)                FourthCellMaxDeltaZ2.push_back(FourthCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaCurvature.size(); i++)   FourthNeighbourMaxDeltaCurvature2.push_back(FourthNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaN.size(); i++)           FourthNeighbourMaxDeltaN2.push_back(FourthNeighbourMaxDeltaN[i]);
  
  trackParams2[0].LayerRadii = LayerRadii2;
  trackParams2[0].LayerZ = LayerZ2;
  trackParams2[0].TrackletMaxDeltaPhi = TMath::Min(lFirstOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams2[0].CellMaxDeltaPhi = TMath::Min(lFirstOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams2[0].CellMaxDeltaTanLambda = lFirstOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams2[0].TrackletMaxDeltaZ = TrackletMaxDeltaZ2;
  trackParams2[0].CellMaxDCA = CellMaxDCA2;
  trackParams2[0].CellMaxDeltaZ = CellMaxDeltaZ2;
  trackParams2[0].NeighbourMaxDeltaCurvature = NeighbourMaxDeltaCurvature2;
  trackParams2[0].NeighbourMaxDeltaN = NeighbourMaxDeltaN2;
  
  std::vector<MemoryParameters> memParams2(4);
  std::vector<float> CellsMemoryCoefficients2 = {1.6432e-08f * 10, 1.2412e-08f * 10, 1.3543e-08f * 10, 1.5e-08f * 10, 1.6e-08f * 10, 1.7e-08f * 10};
  std::vector<float> TrackletsMemoryCoefficients2 = {0.000984f * lFactor, 0.00078135f * lFactor, 0.00057934f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor};
  
  memParams2[0].CellsMemoryCoefficients = CellsMemoryCoefficients2;
  memParams2[0].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients2;
  memParams2[0].MemoryOffset = lMemoryOffset;
  
  //Pass 2: capture long tracks that are lower in pT, etc
  trackParams2[1].NLayers = 10;
  trackParams2[1].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams2[1].LayerRadii = LayerRadii2;
  trackParams2[1].LayerZ = LayerZ2;
  trackParams2[1].TrackletMaxDeltaPhi = TMath::Min(lOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams2[1].CellMaxDeltaPhi = TMath::Min(lOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams2[1].CellMaxDeltaTanLambda = lOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams2[1].TrackletMaxDeltaZ = SecondTrackletMaxDeltaZ2;
  trackParams2[1].CellMaxDCA = SecondCellMaxDCA2;
  trackParams2[1].CellMaxDeltaZ = SecondCellMaxDeltaZ2;
  trackParams2[1].NeighbourMaxDeltaCurvature = SecondNeighbourMaxDeltaCurvature2;
  trackParams2[1].NeighbourMaxDeltaN = SecondNeighbourMaxDeltaN2;
  
  memParams2[1].CellsMemoryCoefficients = CellsMemoryCoefficients2;
  memParams2[1].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients2;
  memParams2[1].MemoryOffset = lMemoryOffset;
  
  //Pass 3: Secondaries
  trackParams2[2].NLayers = 10;
  trackParams2[2].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams2[2].LayerRadii = LayerRadii2;
  trackParams2[2].LayerZ = LayerZ2;
  trackParams2[2].TrackletMaxDeltaPhi = TMath::Min(lThirdPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams2[2].CellMaxDeltaPhi = TMath::Min(lThirdPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams2[2].CellMaxDeltaTanLambda = lThirdPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams2[2].TrackletMaxDeltaZ = ThirdTrackletMaxDeltaZ2;
  trackParams2[2].CellMaxDCA = ThirdCellMaxDCA2;
  trackParams2[2].CellMaxDeltaZ = ThirdCellMaxDeltaZ2;
  trackParams2[2].NeighbourMaxDeltaCurvature = ThirdNeighbourMaxDeltaCurvature2;
  trackParams2[2].NeighbourMaxDeltaN = ThirdNeighbourMaxDeltaN2;
  
  memParams2[2].CellsMemoryCoefficients = CellsMemoryCoefficients2;
  memParams2[2].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients2;
  memParams2[2].MemoryOffset = lMemoryOffset;
  
  //Pass 4: Bonus
  trackParams2[3].NLayers = 10;
  trackParams2[3].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams2[3].LayerRadii = LayerRadii2;
  trackParams2[3].LayerZ = LayerZ2;
  trackParams2[3].TrackletMaxDeltaPhi = TMath::Min(lFourthPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams2[3].CellMaxDeltaPhi = TMath::Min(lFourthPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams2[3].CellMaxDeltaTanLambda = lFourthPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams2[3].TrackletMaxDeltaZ = FourthTrackletMaxDeltaZ2;
  trackParams2[3].CellMaxDCA = FourthCellMaxDCA2;
  trackParams2[3].CellMaxDeltaZ = FourthCellMaxDeltaZ2;
  trackParams2[3].NeighbourMaxDeltaCurvature = FourthNeighbourMaxDeltaCurvature2;
  trackParams2[3].NeighbourMaxDeltaN = FourthNeighbourMaxDeltaN2;
  
  memParams2[3].CellsMemoryCoefficients = CellsMemoryCoefficients2;
  memParams2[3].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients2;
  memParams2[3].MemoryOffset = lMemoryOffset;
  
  tracker2.setParameters(memParams2, trackParams2);
  
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  // TRACKING PARAMETERS THREE
  std::vector<float> LayerRadii3 = {3.75f, 7.0f, 12.0f, 20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  std::vector<float> LayerZ3(9);
  for (int i{0}; i < 9; ++i)
  LayerZ3[i] = getDetLengthFromEta(1.44, LayerRadii3[i]) + 1.;
  
  // EXPERIMENTAL THREE-PASS VERSION
  std::vector<TrackingParameters> trackParams3(4);
  //Tracking parameters for 12 layer setup
  trackParams3[0].NLayers = 9;
  trackParams3[0].MinTrackLength = 6; //this is the one with fixed params
  
  lThisIndex = 3;
  
  //loosely based on run_trac_alice3.C but with extra stuff for the innermost layers
  //FIXME: This may be subject to further tuning and is only a first guess
  std::vector<float> TrackletMaxDeltaZ3;
  std::vector<float> CellMaxDCA3;
  std::vector<float> CellMaxDeltaZ3;
  std::vector<float> NeighbourMaxDeltaCurvature3;
  std::vector<float> NeighbourMaxDeltaN3;
  
  for (int i=lThisIndex; i<TrackletMaxDeltaZ.size(); i++)            TrackletMaxDeltaZ3.push_back(TrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<CellMaxDCA.size(); i++)                   CellMaxDCA3.push_back(CellMaxDCA[i]);
  for (int i=lThisIndex; i<CellMaxDeltaZ.size(); i++)                CellMaxDeltaZ3.push_back(CellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaCurvature.size(); i++)   NeighbourMaxDeltaCurvature3.push_back(NeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaN.size(); i++)           NeighbourMaxDeltaN3.push_back(NeighbourMaxDeltaN[i]);
  
  //Second pass - looser cuts, shorter tracks
  std::vector<float> SecondTrackletMaxDeltaZ3;
  std::vector<float> SecondCellMaxDCA3;
  std::vector<float> SecondCellMaxDeltaZ3;
  std::vector<float> SecondNeighbourMaxDeltaCurvature3;
  std::vector<float> SecondNeighbourMaxDeltaN3;
  
  for (int i=lThisIndex; i<SecondTrackletMaxDeltaZ.size(); i++)            SecondTrackletMaxDeltaZ3.push_back(SecondTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondCellMaxDCA.size(); i++)                   SecondCellMaxDCA3.push_back(SecondCellMaxDCA[i]);
  for (int i=lThisIndex; i<SecondCellMaxDeltaZ.size(); i++)                SecondCellMaxDeltaZ3.push_back(SecondCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaCurvature.size(); i++)   SecondNeighbourMaxDeltaCurvature3.push_back(SecondNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaN.size(); i++)           SecondNeighbourMaxDeltaN3.push_back(SecondNeighbourMaxDeltaN[i]);
  
  //Third pass: loosest, pick up more secondaries
  std::vector<float> ThirdTrackletMaxDeltaZ3;
  std::vector<float> ThirdCellMaxDCA3;
  std::vector<float> ThirdCellMaxDeltaZ3;
  std::vector<float> ThirdNeighbourMaxDeltaCurvature3;
  std::vector<float> ThirdNeighbourMaxDeltaN3;
  
  for (int i=lThisIndex; i<ThirdTrackletMaxDeltaZ.size(); i++)            ThirdTrackletMaxDeltaZ3.push_back(ThirdTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDCA.size(); i++)                   ThirdCellMaxDCA3.push_back(ThirdCellMaxDCA[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDeltaZ.size(); i++)                ThirdCellMaxDeltaZ3.push_back(ThirdCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaCurvature.size(); i++)   ThirdNeighbourMaxDeltaCurvature3.push_back(ThirdNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaN.size(); i++)           ThirdNeighbourMaxDeltaN3.push_back(ThirdNeighbourMaxDeltaN[i]);
  
  //Fourth pass: bonus
  std::vector<float> FourthTrackletMaxDeltaZ3;
  std::vector<float> FourthCellMaxDCA3;
  std::vector<float> FourthCellMaxDeltaZ3;
  std::vector<float> FourthNeighbourMaxDeltaCurvature3;
  std::vector<float> FourthNeighbourMaxDeltaN3;
  
  for (int i=lThisIndex; i<FourthTrackletMaxDeltaZ.size(); i++)            FourthTrackletMaxDeltaZ3.push_back(FourthTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthCellMaxDCA.size(); i++)                   FourthCellMaxDCA3.push_back(FourthCellMaxDCA[i]);
  for (int i=lThisIndex; i<FourthCellMaxDeltaZ.size(); i++)                FourthCellMaxDeltaZ3.push_back(FourthCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaCurvature.size(); i++)   FourthNeighbourMaxDeltaCurvature3.push_back(FourthNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaN.size(); i++)           FourthNeighbourMaxDeltaN3.push_back(FourthNeighbourMaxDeltaN[i]);
  
  trackParams3[0].LayerRadii = LayerRadii3;
  trackParams3[0].LayerZ = LayerZ3;
  trackParams3[0].TrackletMaxDeltaPhi = TMath::Min(lFirstOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams3[0].CellMaxDeltaPhi = TMath::Min(lFirstOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams3[0].CellMaxDeltaTanLambda = lFirstOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams3[0].TrackletMaxDeltaZ = TrackletMaxDeltaZ3;
  trackParams3[0].CellMaxDCA = CellMaxDCA3;
  trackParams3[0].CellMaxDeltaZ = CellMaxDeltaZ3;
  trackParams3[0].NeighbourMaxDeltaCurvature = NeighbourMaxDeltaCurvature3;
  trackParams3[0].NeighbourMaxDeltaN = NeighbourMaxDeltaN3;
  
  std::vector<MemoryParameters> memParams3(4);
  std::vector<float> CellsMemoryCoefficients3 = {1.2412e-08f * 10, 1.3543e-08f * 10, 1.5e-08f * 10, 1.6e-08f * 10, 1.7e-08f * 10};
  std::vector<float> TrackletsMemoryCoefficients3 = {0.00078135f * lFactor, 0.00057934f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor};
  
  memParams3[0].CellsMemoryCoefficients = CellsMemoryCoefficients3;
  memParams3[0].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients3;
  memParams3[0].MemoryOffset = lMemoryOffset;
  
  //Pass 2: capture long tracks that are lower in pT, etc
  trackParams3[1].NLayers = 9;
  trackParams3[1].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams3[1].LayerRadii = LayerRadii3;
  trackParams3[1].LayerZ = LayerZ3;
  trackParams3[1].TrackletMaxDeltaPhi = TMath::Min(lOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams3[1].CellMaxDeltaPhi = TMath::Min(lOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams3[1].CellMaxDeltaTanLambda = lOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams3[1].TrackletMaxDeltaZ = SecondTrackletMaxDeltaZ3;
  trackParams3[1].CellMaxDCA = SecondCellMaxDCA3;
  trackParams3[1].CellMaxDeltaZ = SecondCellMaxDeltaZ3;
  trackParams3[1].NeighbourMaxDeltaCurvature = SecondNeighbourMaxDeltaCurvature3;
  trackParams3[1].NeighbourMaxDeltaN = SecondNeighbourMaxDeltaN3;
  
  memParams3[1].CellsMemoryCoefficients = CellsMemoryCoefficients3;
  memParams3[1].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients3;
  memParams3[1].MemoryOffset = lMemoryOffset;
  
  //Pass 3: Secondaries
  trackParams3[2].NLayers = 9;
  trackParams3[2].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams3[2].LayerRadii = LayerRadii3;
  trackParams3[2].LayerZ = LayerZ3;
  trackParams3[2].TrackletMaxDeltaPhi = TMath::Min(lThirdPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams3[2].CellMaxDeltaPhi = TMath::Min(lThirdPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams3[2].CellMaxDeltaTanLambda = lThirdPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams3[2].TrackletMaxDeltaZ = ThirdTrackletMaxDeltaZ3;
  trackParams3[2].CellMaxDCA = ThirdCellMaxDCA3;
  trackParams3[2].CellMaxDeltaZ = ThirdCellMaxDeltaZ3;
  trackParams3[2].NeighbourMaxDeltaCurvature = ThirdNeighbourMaxDeltaCurvature3;
  trackParams3[2].NeighbourMaxDeltaN = ThirdNeighbourMaxDeltaN3;
  
  memParams3[2].CellsMemoryCoefficients = CellsMemoryCoefficients3;
  memParams3[2].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients3;
  memParams3[2].MemoryOffset = lMemoryOffset;
  
  //Pass 4: Bonus
  trackParams3[3].NLayers = 9;
  trackParams3[3].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams3[3].LayerRadii = LayerRadii3;
  trackParams3[3].LayerZ = LayerZ3;
  trackParams3[3].TrackletMaxDeltaPhi = TMath::Min(lFourthPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams3[3].CellMaxDeltaPhi = TMath::Min(lFourthPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams3[3].CellMaxDeltaTanLambda = lFourthPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams3[3].TrackletMaxDeltaZ = FourthTrackletMaxDeltaZ3;
  trackParams3[3].CellMaxDCA = FourthCellMaxDCA3;
  trackParams3[3].CellMaxDeltaZ = FourthCellMaxDeltaZ3;
  trackParams3[3].NeighbourMaxDeltaCurvature = FourthNeighbourMaxDeltaCurvature3;
  trackParams3[3].NeighbourMaxDeltaN = FourthNeighbourMaxDeltaN3;
  
  memParams3[3].CellsMemoryCoefficients = CellsMemoryCoefficients3;
  memParams3[3].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients3;
  memParams3[3].MemoryOffset = lMemoryOffset;
  
  tracker3.setParameters(memParams3, trackParams3);
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  // TRACKING PARAMETERS FOUR
  std::vector<float> LayerRadii4 = {7.0f, 12.0f, 20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  std::vector<float> LayerZ4(8);
  for (int i{0}; i < 8; ++i)
  LayerZ4[i] = getDetLengthFromEta(1.44, LayerRadii4[i]) + 1.;
  
  // EXPERIMENTAL THREE-PASS VERSION
  std::vector<TrackingParameters> trackParams4(4);
  //Tracking parameters for 12 layer setup
  trackParams4[0].NLayers = 8;
  trackParams4[0].MinTrackLength = 6; //this is the one with fixed params
  
  lThisIndex = 4;
  
  //loosely based on run_trac_alice3.C but with extra stuff for the innermost layers
  //FIXME: This may be subject to further tuning and is only a first guess
  std::vector<float> TrackletMaxDeltaZ4;
  std::vector<float> CellMaxDCA4;
  std::vector<float> CellMaxDeltaZ4;
  std::vector<float> NeighbourMaxDeltaCurvature4;
  std::vector<float> NeighbourMaxDeltaN4;
  
  for (int i=lThisIndex; i<TrackletMaxDeltaZ.size(); i++)            TrackletMaxDeltaZ4.push_back(TrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<CellMaxDCA.size(); i++)                   CellMaxDCA4.push_back(CellMaxDCA[i]);
  for (int i=lThisIndex; i<CellMaxDeltaZ.size(); i++)                CellMaxDeltaZ4.push_back(CellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaCurvature.size(); i++)   NeighbourMaxDeltaCurvature4.push_back(NeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaN.size(); i++)           NeighbourMaxDeltaN4.push_back(NeighbourMaxDeltaN[i]);
  
  //Second pass - looser cuts, shorter tracks
  std::vector<float> SecondTrackletMaxDeltaZ4;
  std::vector<float> SecondCellMaxDCA4;
  std::vector<float> SecondCellMaxDeltaZ4;
  std::vector<float> SecondNeighbourMaxDeltaCurvature4;
  std::vector<float> SecondNeighbourMaxDeltaN4;
  
  for (int i=lThisIndex; i<SecondTrackletMaxDeltaZ.size(); i++)            SecondTrackletMaxDeltaZ4.push_back(SecondTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondCellMaxDCA.size(); i++)                   SecondCellMaxDCA4.push_back(SecondCellMaxDCA[i]);
  for (int i=lThisIndex; i<SecondCellMaxDeltaZ.size(); i++)                SecondCellMaxDeltaZ4.push_back(SecondCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaCurvature.size(); i++)   SecondNeighbourMaxDeltaCurvature4.push_back(SecondNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaN.size(); i++)           SecondNeighbourMaxDeltaN4.push_back(SecondNeighbourMaxDeltaN[i]);
  
  //Third pass: loosest, pick up more secondaries
  std::vector<float> ThirdTrackletMaxDeltaZ4;
  std::vector<float> ThirdCellMaxDCA4;
  std::vector<float> ThirdCellMaxDeltaZ4;
  std::vector<float> ThirdNeighbourMaxDeltaCurvature4;
  std::vector<float> ThirdNeighbourMaxDeltaN4;
  
  for (int i=lThisIndex; i<ThirdTrackletMaxDeltaZ.size(); i++)            ThirdTrackletMaxDeltaZ4.push_back(ThirdTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDCA.size(); i++)                   ThirdCellMaxDCA4.push_back(ThirdCellMaxDCA[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDeltaZ.size(); i++)                ThirdCellMaxDeltaZ4.push_back(ThirdCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaCurvature.size(); i++)   ThirdNeighbourMaxDeltaCurvature4.push_back(ThirdNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaN.size(); i++)           ThirdNeighbourMaxDeltaN4.push_back(ThirdNeighbourMaxDeltaN[i]);
  
  //Fourth pass: bonus
  std::vector<float> FourthTrackletMaxDeltaZ4;
  std::vector<float> FourthCellMaxDCA4;
  std::vector<float> FourthCellMaxDeltaZ4;
  std::vector<float> FourthNeighbourMaxDeltaCurvature4;
  std::vector<float> FourthNeighbourMaxDeltaN4;
  
  for (int i=lThisIndex; i<FourthTrackletMaxDeltaZ.size(); i++)            FourthTrackletMaxDeltaZ4.push_back(FourthTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthCellMaxDCA.size(); i++)                   FourthCellMaxDCA4.push_back(FourthCellMaxDCA[i]);
  for (int i=lThisIndex; i<FourthCellMaxDeltaZ.size(); i++)                FourthCellMaxDeltaZ4.push_back(FourthCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaCurvature.size(); i++)   FourthNeighbourMaxDeltaCurvature4.push_back(FourthNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaN.size(); i++)           FourthNeighbourMaxDeltaN4.push_back(FourthNeighbourMaxDeltaN[i]);
  
  for (Int_t i=0; i<FourthNeighbourMaxDeltaN4.size(); i++ ) cout<<"element "<<i<<" - "<<FourthNeighbourMaxDeltaN4[i]<<endl;
  
  
  trackParams4[0].LayerRadii = LayerRadii4;
  trackParams4[0].LayerZ = LayerZ4;
  trackParams4[0].TrackletMaxDeltaPhi = TMath::Min(lFirstOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams4[0].CellMaxDeltaPhi = TMath::Min(lFirstOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams4[0].CellMaxDeltaTanLambda = lFirstOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams4[0].TrackletMaxDeltaZ = TrackletMaxDeltaZ4;
  trackParams4[0].CellMaxDCA = CellMaxDCA4;
  trackParams4[0].CellMaxDeltaZ = CellMaxDeltaZ4;
  trackParams4[0].NeighbourMaxDeltaCurvature = NeighbourMaxDeltaCurvature4;
  trackParams4[0].NeighbourMaxDeltaN = NeighbourMaxDeltaN4;
  
  std::vector<MemoryParameters> memParams4(4);
  std::vector<float> CellsMemoryCoefficients4 = {1.3543e-08f * 10, 1.5e-08f * 10, 1.6e-08f * 10, 1.7e-08f * 10};
  std::vector<float> TrackletsMemoryCoefficients4 = {0.00057934f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor};
  
  memParams4[0].CellsMemoryCoefficients = CellsMemoryCoefficients4;
  memParams4[0].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients4;
  memParams4[0].MemoryOffset = lMemoryOffset;
  
  //Pass 2: capture long tracks that are lower in pT, etc
  trackParams4[1].NLayers = 8;
  trackParams4[1].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams4[1].LayerRadii = LayerRadii4;
  trackParams4[1].LayerZ = LayerZ4;
  trackParams4[1].TrackletMaxDeltaPhi = TMath::Min(lOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams4[1].CellMaxDeltaPhi = TMath::Min(lOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams4[1].CellMaxDeltaTanLambda = lOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams4[1].TrackletMaxDeltaZ = SecondTrackletMaxDeltaZ4;
  trackParams4[1].CellMaxDCA = SecondCellMaxDCA4;
  trackParams4[1].CellMaxDeltaZ = SecondCellMaxDeltaZ4;
  trackParams4[1].NeighbourMaxDeltaCurvature = SecondNeighbourMaxDeltaCurvature4;
  trackParams4[1].NeighbourMaxDeltaN = SecondNeighbourMaxDeltaN4;
  
  memParams4[1].CellsMemoryCoefficients = CellsMemoryCoefficients4;
  memParams4[1].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients4;
  memParams4[1].MemoryOffset = lMemoryOffset;
  
  //Pass 3: Secondaries
  trackParams4[2].NLayers = 8;
  trackParams4[2].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams4[2].LayerRadii = LayerRadii4;
  trackParams4[2].LayerZ = LayerZ4;
  trackParams4[2].TrackletMaxDeltaPhi = TMath::Min(lThirdPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams4[2].CellMaxDeltaPhi = TMath::Min(lThirdPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams4[2].CellMaxDeltaTanLambda = lThirdPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams4[2].TrackletMaxDeltaZ = ThirdTrackletMaxDeltaZ4;
  trackParams4[2].CellMaxDCA = ThirdCellMaxDCA4;
  trackParams4[2].CellMaxDeltaZ = ThirdCellMaxDeltaZ4;
  trackParams4[2].NeighbourMaxDeltaCurvature = ThirdNeighbourMaxDeltaCurvature4;
  trackParams4[2].NeighbourMaxDeltaN = ThirdNeighbourMaxDeltaN4;
  
  memParams4[2].CellsMemoryCoefficients = CellsMemoryCoefficients4;
  memParams4[2].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients4;
  memParams4[2].MemoryOffset = lMemoryOffset;
  
  //Pass 4: Bonus
  trackParams4[3].NLayers = 8;
  trackParams4[3].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams4[3].LayerRadii = LayerRadii4;
  trackParams4[3].LayerZ = LayerZ4;
  trackParams4[3].TrackletMaxDeltaPhi = TMath::Min(lFourthPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams4[3].CellMaxDeltaPhi = TMath::Min(lFourthPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams4[3].CellMaxDeltaTanLambda = lFourthPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams4[3].TrackletMaxDeltaZ = FourthTrackletMaxDeltaZ4;
  trackParams4[3].CellMaxDCA = FourthCellMaxDCA4;
  trackParams4[3].CellMaxDeltaZ = FourthCellMaxDeltaZ4;
  trackParams4[3].NeighbourMaxDeltaCurvature = FourthNeighbourMaxDeltaCurvature4;
  trackParams4[3].NeighbourMaxDeltaN = FourthNeighbourMaxDeltaN4;
  
  memParams4[3].CellsMemoryCoefficients = CellsMemoryCoefficients4;
  memParams4[3].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients4;
  memParams4[3].MemoryOffset = lMemoryOffset;
  
  tracker4.setParameters(memParams4, trackParams4);
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  // TRACKING PARAMETERS FIVE
  std::vector<float> LayerRadii5 = {12.0f, 20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  std::vector<float> LayerZ5(7);
  for (int i{0}; i < 8; ++i)
  LayerZ5[i] = getDetLengthFromEta(1.44, LayerRadii5[i]) + 1.;
  
  // EXPERIMENTAL THREE-PASS VERSION
  std::vector<TrackingParameters> trackParams5(4);
  //Tracking parameters for 12 layer setup
  trackParams5[0].NLayers = 7;
  trackParams5[0].MinTrackLength = 6; //this is the one with fixed params
  
  lThisIndex = 5;
  
  //loosely based on run_trac_alice3.C but with extra stuff for the innermost layers
  //FIXME: This may be subject to further tuning and is only a first guess
  std::vector<float> TrackletMaxDeltaZ5;
  std::vector<float> CellMaxDCA5;
  std::vector<float> CellMaxDeltaZ5;
  std::vector<float> NeighbourMaxDeltaCurvature5;
  std::vector<float> NeighbourMaxDeltaN5;
  
  for (int i=lThisIndex; i<TrackletMaxDeltaZ.size(); i++)            TrackletMaxDeltaZ5.push_back(TrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<CellMaxDCA.size(); i++)                   CellMaxDCA5.push_back(CellMaxDCA[i]);
  for (int i=lThisIndex; i<CellMaxDeltaZ.size(); i++)                CellMaxDeltaZ5.push_back(CellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaCurvature.size(); i++)   NeighbourMaxDeltaCurvature5.push_back(NeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaN.size(); i++)           NeighbourMaxDeltaN5.push_back(NeighbourMaxDeltaN[i]);
  
  //Second pass - looser cuts, shorter tracks
  std::vector<float> SecondTrackletMaxDeltaZ5;
  std::vector<float> SecondCellMaxDCA5;
  std::vector<float> SecondCellMaxDeltaZ5;
  std::vector<float> SecondNeighbourMaxDeltaCurvature5;
  std::vector<float> SecondNeighbourMaxDeltaN5;
  
  for (int i=lThisIndex; i<SecondTrackletMaxDeltaZ.size(); i++)            SecondTrackletMaxDeltaZ5.push_back(SecondTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondCellMaxDCA.size(); i++)                   SecondCellMaxDCA5.push_back(SecondCellMaxDCA[i]);
  for (int i=lThisIndex; i<SecondCellMaxDeltaZ.size(); i++)                SecondCellMaxDeltaZ5.push_back(SecondCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaCurvature.size(); i++)   SecondNeighbourMaxDeltaCurvature5.push_back(SecondNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaN.size(); i++)           SecondNeighbourMaxDeltaN5.push_back(SecondNeighbourMaxDeltaN[i]);
  
  //Third pass: loosest, pick up more secondaries
  std::vector<float> ThirdTrackletMaxDeltaZ5;
  std::vector<float> ThirdCellMaxDCA5;
  std::vector<float> ThirdCellMaxDeltaZ5;
  std::vector<float> ThirdNeighbourMaxDeltaCurvature5;
  std::vector<float> ThirdNeighbourMaxDeltaN5;
  
  for (int i=lThisIndex; i<ThirdTrackletMaxDeltaZ.size(); i++)            ThirdTrackletMaxDeltaZ5.push_back(ThirdTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDCA.size(); i++)                   ThirdCellMaxDCA5.push_back(ThirdCellMaxDCA[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDeltaZ.size(); i++)                ThirdCellMaxDeltaZ5.push_back(ThirdCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaCurvature.size(); i++)   ThirdNeighbourMaxDeltaCurvature5.push_back(ThirdNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaN.size(); i++)           ThirdNeighbourMaxDeltaN5.push_back(ThirdNeighbourMaxDeltaN[i]);
  
  //Fourth pass: bonus
  std::vector<float> FourthTrackletMaxDeltaZ5;
  std::vector<float> FourthCellMaxDCA5;
  std::vector<float> FourthCellMaxDeltaZ5;
  std::vector<float> FourthNeighbourMaxDeltaCurvature5;
  std::vector<float> FourthNeighbourMaxDeltaN5;
  
  for (int i=lThisIndex; i<FourthTrackletMaxDeltaZ.size(); i++)            FourthTrackletMaxDeltaZ5.push_back(FourthTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthCellMaxDCA.size(); i++)                   FourthCellMaxDCA5.push_back(FourthCellMaxDCA[i]);
  for (int i=lThisIndex; i<FourthCellMaxDeltaZ.size(); i++)                FourthCellMaxDeltaZ5.push_back(FourthCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaCurvature.size(); i++)   FourthNeighbourMaxDeltaCurvature5.push_back(FourthNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaN.size(); i++)           FourthNeighbourMaxDeltaN5.push_back(FourthNeighbourMaxDeltaN[i]);
  
  trackParams5[0].LayerRadii = LayerRadii5;
  trackParams5[0].LayerZ = LayerZ5;
  trackParams5[0].TrackletMaxDeltaPhi = TMath::Min(lFirstOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams5[0].CellMaxDeltaPhi = TMath::Min(lFirstOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams5[0].CellMaxDeltaTanLambda = lFirstOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams5[0].TrackletMaxDeltaZ = TrackletMaxDeltaZ5;
  trackParams5[0].CellMaxDCA = CellMaxDCA5;
  trackParams5[0].CellMaxDeltaZ = CellMaxDeltaZ5;
  trackParams5[0].NeighbourMaxDeltaCurvature = NeighbourMaxDeltaCurvature5;
  trackParams5[0].NeighbourMaxDeltaN = NeighbourMaxDeltaN5;
  
  std::vector<MemoryParameters> memParams5(4);
  std::vector<float> CellsMemoryCoefficients5 = {1.5e-08f * 10, 1.6e-08f * 10, 1.7e-08f * 10};
  std::vector<float> TrackletsMemoryCoefficients5 = {0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor};
  
  memParams5[0].CellsMemoryCoefficients = CellsMemoryCoefficients5;
  memParams5[0].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients5;
  memParams5[0].MemoryOffset = lMemoryOffset;
  
  //Pass 2: capture long tracks that are lower in pT, etc
  trackParams5[1].NLayers = 7;
  trackParams5[1].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams5[1].LayerRadii = LayerRadii5;
  trackParams5[1].LayerZ = LayerZ5;
  trackParams5[1].TrackletMaxDeltaPhi = TMath::Min(lOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams5[1].CellMaxDeltaPhi = TMath::Min(lOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams5[1].CellMaxDeltaTanLambda = lOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams5[1].TrackletMaxDeltaZ = SecondTrackletMaxDeltaZ5;
  trackParams5[1].CellMaxDCA = SecondCellMaxDCA5;
  trackParams5[1].CellMaxDeltaZ = SecondCellMaxDeltaZ5;
  trackParams5[1].NeighbourMaxDeltaCurvature = SecondNeighbourMaxDeltaCurvature5;
  trackParams5[1].NeighbourMaxDeltaN = SecondNeighbourMaxDeltaN5;
  
  memParams5[1].CellsMemoryCoefficients = CellsMemoryCoefficients5;
  memParams5[1].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients5;
  memParams5[1].MemoryOffset = lMemoryOffset;
  
  //Pass 3: Secondaries
  trackParams5[2].NLayers = 7;
  trackParams5[2].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams5[2].LayerRadii = LayerRadii5;
  trackParams5[2].LayerZ = LayerZ5;
  trackParams5[2].TrackletMaxDeltaPhi = TMath::Min(lThirdPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams5[2].CellMaxDeltaPhi = TMath::Min(lThirdPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams5[2].CellMaxDeltaTanLambda = lThirdPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams5[2].TrackletMaxDeltaZ = ThirdTrackletMaxDeltaZ5;
  trackParams5[2].CellMaxDCA = ThirdCellMaxDCA5;
  trackParams5[2].CellMaxDeltaZ = ThirdCellMaxDeltaZ5;
  trackParams5[2].NeighbourMaxDeltaCurvature = ThirdNeighbourMaxDeltaCurvature5;
  trackParams5[2].NeighbourMaxDeltaN = ThirdNeighbourMaxDeltaN5;
  
  memParams5[2].CellsMemoryCoefficients = CellsMemoryCoefficients5;
  memParams5[2].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients5;
  memParams5[2].MemoryOffset = lMemoryOffset;
  
  //Pass 4: Bonus
  trackParams5[3].NLayers = 7;
  trackParams5[3].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams5[3].LayerRadii = LayerRadii5;
  trackParams5[3].LayerZ = LayerZ5;
  trackParams5[3].TrackletMaxDeltaPhi = TMath::Min(lFourthPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams5[3].CellMaxDeltaPhi = TMath::Min(lFourthPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams5[3].CellMaxDeltaTanLambda = lFourthPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams5[3].TrackletMaxDeltaZ = FourthTrackletMaxDeltaZ5;
  trackParams5[3].CellMaxDCA = FourthCellMaxDCA5;
  trackParams5[3].CellMaxDeltaZ = FourthCellMaxDeltaZ5;
  trackParams5[3].NeighbourMaxDeltaCurvature = FourthNeighbourMaxDeltaCurvature5;
  trackParams5[3].NeighbourMaxDeltaN = FourthNeighbourMaxDeltaN5;
  
  memParams5[3].CellsMemoryCoefficients = CellsMemoryCoefficients5;
  memParams5[3].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients5;
  memParams5[3].MemoryOffset = lMemoryOffset;
  
  tracker5.setParameters(memParams5, trackParams5);
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  // TRACKING PARAMETERS FIVE
  std::vector<float> LayerRadii6 = {20.0f, 30.0f, 45.0f, 60.0f, 80.0f, 100.0f};
  std::vector<float> LayerZ6(7);
  for (int i{0}; i < 8; ++i)
  LayerZ6[i] = getDetLengthFromEta(1.44, LayerRadii6[i]) + 1.;
  
  // EXPERIMENTAL THREE-PASS VERSION
  std::vector<TrackingParameters> trackParams6(4);
  //Tracking parameters for 12 layer setup
  trackParams6[0].NLayers = 6;
  trackParams6[0].MinTrackLength = 6; //this is the one with fixed params
  
  lThisIndex = 6;
  
  //loosely based on run_trac_alice3.C but with extra stuff for the innermost layers
  //FIXME: This may be subject to further tuning and is only a first guess
  std::vector<float> TrackletMaxDeltaZ6;
  std::vector<float> CellMaxDCA6;
  std::vector<float> CellMaxDeltaZ6;
  std::vector<float> NeighbourMaxDeltaCurvature6;
  std::vector<float> NeighbourMaxDeltaN6;
  
  for (int i=lThisIndex; i<TrackletMaxDeltaZ.size(); i++)            TrackletMaxDeltaZ6.push_back(TrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<CellMaxDCA.size(); i++)                   CellMaxDCA6.push_back(CellMaxDCA[i]);
  for (int i=lThisIndex; i<CellMaxDeltaZ.size(); i++)                CellMaxDeltaZ6.push_back(CellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaCurvature.size(); i++)   NeighbourMaxDeltaCurvature6.push_back(NeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<NeighbourMaxDeltaN.size(); i++)           NeighbourMaxDeltaN6.push_back(NeighbourMaxDeltaN[i]);
  
  //Second pass - looser cuts, shorter tracks
  std::vector<float> SecondTrackletMaxDeltaZ6;
  std::vector<float> SecondCellMaxDCA6;
  std::vector<float> SecondCellMaxDeltaZ6;
  std::vector<float> SecondNeighbourMaxDeltaCurvature6;
  std::vector<float> SecondNeighbourMaxDeltaN6;
  
  for (int i=lThisIndex; i<SecondTrackletMaxDeltaZ.size(); i++)            SecondTrackletMaxDeltaZ6.push_back(SecondTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondCellMaxDCA.size(); i++)                   SecondCellMaxDCA6.push_back(SecondCellMaxDCA[i]);
  for (int i=lThisIndex; i<SecondCellMaxDeltaZ.size(); i++)                SecondCellMaxDeltaZ6.push_back(SecondCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaCurvature.size(); i++)   SecondNeighbourMaxDeltaCurvature6.push_back(SecondNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<SecondNeighbourMaxDeltaN.size(); i++)           SecondNeighbourMaxDeltaN6.push_back(SecondNeighbourMaxDeltaN[i]);
  
  //Third pass: loosest, pick up more secondaries
  std::vector<float> ThirdTrackletMaxDeltaZ6;
  std::vector<float> ThirdCellMaxDCA6;
  std::vector<float> ThirdCellMaxDeltaZ6;
  std::vector<float> ThirdNeighbourMaxDeltaCurvature6;
  std::vector<float> ThirdNeighbourMaxDeltaN6;
  
  for (int i=lThisIndex; i<ThirdTrackletMaxDeltaZ.size(); i++)            ThirdTrackletMaxDeltaZ6.push_back(ThirdTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDCA.size(); i++)                   ThirdCellMaxDCA6.push_back(ThirdCellMaxDCA[i]);
  for (int i=lThisIndex; i<ThirdCellMaxDeltaZ.size(); i++)                ThirdCellMaxDeltaZ6.push_back(ThirdCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaCurvature.size(); i++)   ThirdNeighbourMaxDeltaCurvature6.push_back(ThirdNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<ThirdNeighbourMaxDeltaN.size(); i++)           ThirdNeighbourMaxDeltaN6.push_back(ThirdNeighbourMaxDeltaN[i]);
  
  //Fourth pass: bonus
  std::vector<float> FourthTrackletMaxDeltaZ6;
  std::vector<float> FourthCellMaxDCA6;
  std::vector<float> FourthCellMaxDeltaZ6;
  std::vector<float> FourthNeighbourMaxDeltaCurvature6;
  std::vector<float> FourthNeighbourMaxDeltaN6;
  
  for (int i=lThisIndex; i<FourthTrackletMaxDeltaZ.size(); i++)            FourthTrackletMaxDeltaZ6.push_back(FourthTrackletMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthCellMaxDCA.size(); i++)                   FourthCellMaxDCA6.push_back(FourthCellMaxDCA[i]);
  for (int i=lThisIndex; i<FourthCellMaxDeltaZ.size(); i++)                FourthCellMaxDeltaZ6.push_back(FourthCellMaxDeltaZ[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaCurvature.size(); i++)   FourthNeighbourMaxDeltaCurvature6.push_back(FourthNeighbourMaxDeltaCurvature[i]);
  for (int i=lThisIndex; i<FourthNeighbourMaxDeltaN.size(); i++)           FourthNeighbourMaxDeltaN6.push_back(FourthNeighbourMaxDeltaN[i]);
  
  trackParams6[0].LayerRadii = LayerRadii6;
  trackParams6[0].LayerZ = LayerZ6;
  trackParams6[0].TrackletMaxDeltaPhi = TMath::Min(lFirstOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams6[0].CellMaxDeltaPhi = TMath::Min(lFirstOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams6[0].CellMaxDeltaTanLambda = lFirstOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams6[0].TrackletMaxDeltaZ = TrackletMaxDeltaZ6;
  trackParams6[0].CellMaxDCA = CellMaxDCA6;
  trackParams6[0].CellMaxDeltaZ = CellMaxDeltaZ6;
  trackParams6[0].NeighbourMaxDeltaCurvature = NeighbourMaxDeltaCurvature6;
  trackParams6[0].NeighbourMaxDeltaN = NeighbourMaxDeltaN6;
  
  std::vector<MemoryParameters> memParams6(4);
  std::vector<float> CellsMemoryCoefficients6 = {1.6e-08f * 10, 1.7e-08f * 10};
  std::vector<float> TrackletsMemoryCoefficients6 = {0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor, 0.00052217f * lFactor};
  
  memParams6[0].CellsMemoryCoefficients = CellsMemoryCoefficients5;
  memParams6[0].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients5;
  memParams6[0].MemoryOffset = lMemoryOffset;
  
  //Pass 2: capture long tracks that are lower in pT, etc
  trackParams6[1].NLayers = 6;
  trackParams6[1].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams6[1].LayerRadii = LayerRadii6;
  trackParams6[1].LayerZ = LayerZ6;
  trackParams6[1].TrackletMaxDeltaPhi = TMath::Min(lOpening*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams6[1].CellMaxDeltaPhi = TMath::Min(lOpening*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams6[1].CellMaxDeltaTanLambda = lOpening*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams6[1].TrackletMaxDeltaZ = SecondTrackletMaxDeltaZ6;
  trackParams6[1].CellMaxDCA = SecondCellMaxDCA6;
  trackParams6[1].CellMaxDeltaZ = SecondCellMaxDeltaZ6;
  trackParams6[1].NeighbourMaxDeltaCurvature = SecondNeighbourMaxDeltaCurvature6;
  trackParams6[1].NeighbourMaxDeltaN = SecondNeighbourMaxDeltaN6;
  
  memParams6[1].CellsMemoryCoefficients = CellsMemoryCoefficients6;
  memParams6[1].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients6;
  memParams6[1].MemoryOffset = lMemoryOffset;
  
  //Pass 3: Secondaries
  trackParams6[2].NLayers = 6;
  trackParams6[2].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams6[2].LayerRadii = LayerRadii6;
  trackParams6[2].LayerZ = LayerZ6;
  trackParams6[2].TrackletMaxDeltaPhi = TMath::Min(lThirdPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams6[2].CellMaxDeltaPhi = TMath::Min(lThirdPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams6[2].CellMaxDeltaTanLambda = lThirdPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams6[2].TrackletMaxDeltaZ = ThirdTrackletMaxDeltaZ6;
  trackParams6[2].CellMaxDCA = ThirdCellMaxDCA6;
  trackParams6[2].CellMaxDeltaZ = ThirdCellMaxDeltaZ6;
  trackParams6[2].NeighbourMaxDeltaCurvature = ThirdNeighbourMaxDeltaCurvature6;
  trackParams6[2].NeighbourMaxDeltaN = ThirdNeighbourMaxDeltaN6;
  
  memParams6[2].CellsMemoryCoefficients = CellsMemoryCoefficients6;
  memParams6[2].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients6;
  memParams6[2].MemoryOffset = lMemoryOffset;
  
  //Pass 4: Bonus
  trackParams6[3].NLayers = 6;
  trackParams6[3].MinTrackLength = 6; //this is the one with fixed params
  
  trackParams6[3].LayerRadii = LayerRadii6;
  trackParams6[3].LayerZ = LayerZ6;
  trackParams6[3].TrackletMaxDeltaPhi = TMath::Min(lFourthPass*TrackletMaxDeltaPhiMultiplier*0.3, TMath::Pi());
  trackParams6[3].CellMaxDeltaPhi = TMath::Min(lFourthPass*CellMaxDeltaPhiMultiplier*0.15, TMath::Pi());
  trackParams6[3].CellMaxDeltaTanLambda = lFourthPass*CellMaxDeltaTanLambdaMultiplier*0.03;
  trackParams6[3].TrackletMaxDeltaZ = FourthTrackletMaxDeltaZ6;
  trackParams6[3].CellMaxDCA = FourthCellMaxDCA6;
  trackParams6[3].CellMaxDeltaZ = FourthCellMaxDeltaZ6;
  trackParams6[3].NeighbourMaxDeltaCurvature = FourthNeighbourMaxDeltaCurvature6;
  trackParams6[3].NeighbourMaxDeltaN = FourthNeighbourMaxDeltaN6;
  
  memParams6[3].CellsMemoryCoefficients = CellsMemoryCoefficients6;
  memParams6[3].TrackletsMemoryCoefficients = TrackletsMemoryCoefficients6;
  memParams6[3].MemoryOffset = lMemoryOffset;
  
  tracker6.setParameters(memParams6, trackParams6);
  //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
  //return;
  
  //vertexer QA
  TFile *fQA = new TFile("findable.root", "RECREATE");
  
  TH1D *hGenerated = new TH1D("hGenerated", "", 200,0,20);
  
  TH1D *hPartialTransportDebug = new TH1D("hPartialTransportDebug", "", 6,0,6);
  hPartialTransportDebug->GetXaxis()->SetBinLabel(1, "All particles");
  hPartialTransportDebug->GetXaxis()->SetBinLabel(2, "Not tranported");
  hPartialTransportDebug->GetXaxis()->SetBinLabel(3, "Successfully smeared");
  hPartialTransportDebug->GetXaxis()->SetBinLabel(4, "Fully tracked particles");
  
  TTree *fTree = new TTree("fTree", "");
  
  Float_t fPtMC, fEtaMC;
  Int_t fBachHits, fNegHits, fPosHits;
  
  fTree->Branch("fPtMC", &fPtMC, "fPtMC/F");
  fTree->Branch("fEtaMC", &fEtaMC, "fEtaMC/F");
  
  fTree->Branch("fBachHits", &fBachHits, "fBachHits/I");
  fTree->Branch("fPosHits", &fPosHits, "fPosHits/I");
  fTree->Branch("fNegHits", &fNegHits, "fNegHits/I");
  
  Bool_t fBachHitLayer[12];
  Bool_t fPosHitLayer[12];
  Bool_t fNegHitLayer[12];
  
  for(Int_t ih=0; ih<12; ih++) fTree->Branch( Form("fBachHits%i", ih), &(fBachHitLayer[ih]), Form("fBachHits%i/O",ih) );
  for(Int_t ih=0; ih<12; ih++) fTree->Branch( Form("fPosHits%i", ih), &(fPosHitLayer[ih]), Form("fPosHits%i/O",ih) );
  for(Int_t ih=0; ih<12; ih++) fTree->Branch( Form("fNegHits%i", ih), &(fNegHitLayer[ih]), Form("fNegHits%i/O",ih) );
  
  Bool_t fBachTracked, fPosTracked, fNegTracked;
  
  fTree->Branch("fBachTracked", &fBachTracked, "fBachTracked/O");
  fTree->Branch("fPosTracked", &fPosTracked, "fPosTracked/O");
  fTree->Branch("fNegTracked", &fNegTracked, "fNegTracked/O");
  
  Bool_t fCascadeReco;
  
  fTree->Branch("fCascadeReco", &fCascadeReco, "fCascadeReco/O");
  
  //Hybrid modular output: save tracks and open from other analysis codes
  TFile *fileTracks = new TFile("tracks.root", "RECREATE");
  TTree *fTreeTracks = new TTree("fTreeTracks","");
  
  //Create std::vectors
  o2::its::TrackITS *wdTrack = new o2::its::TrackITS();
  o2::MCCompLabel *wdTrackLabel = new o2::MCCompLabel();
  Int_t wdEvent = 0;
  
  //Associate to tree
  fTreeTracks->Branch("wdTrack",&wdTrack);
  fTreeTracks->Branch("wdTrackLabel",&wdTrackLabel);
  fTreeTracks->Branch("wdEvent",&wdEvent, "wdEvent/I");
  
  //Define o2 fitter, 2-prong
  o2::vertexing::DCAFitterN<2> fitterV0, fitterCasc;
  
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
  
  Long_t lAllTracksAttempted = 0;
  Long_t lAllTracksRecoed = 0;
  
  Long_t lInnerTracksAttempted = 0;
  Long_t lInnerTracksRecoed = 0;
  
  //Establish indices for the xi
  const Int_t lMax = 100; //absolute max one can store
  
  Int_t lPoIIndex[lMax];
  Float_t lPoIPt[lMax];
  Float_t lPoIEta[lMax];
  Int_t lPoIBachelor[lMax];
  Int_t lPoIPositive[lMax];
  Int_t lPoINegative[lMax];
  Bool_t lPoIBachelorLayer[lMax][12];
  Bool_t lPoIPositiveLayer[lMax][12];
  Bool_t lPoINegativeLayer[lMax][12];
  Int_t lNPoI = 0;
  
  Long_t lNchThisEvent = 0;
  
  for (int iEvent{0}; iEvent < itsHits.GetEntries(); ++iEvent) {
    std::cout << "*************** Event " << iEvent << "/"<<itsHits.GetEntries()<<" ***************" << std::endl;
    itsHits.GetEntry(iEvent);
    mcTree.GetEvent(iEvent);
    
    cout<<"Finding generated Xi in this event..."<<endl;
    lNPoI=0;
    lNchThisEvent=0;
    //Identify Xis in this event: store indices
    for (Long_t iii=0; iii< mcArr->size(); iii++ ){
      auto part = mcArr->at(iii);
      
      //Count primary particles
      if(TMath::Abs(part.GetEta())<0.5 && part.isPrimary() &&
         (
          TMath::Abs( part.GetPdgCode() ) == 211 ||
          TMath::Abs( part.GetPdgCode() ) == 321 ||
          TMath::Abs( part.GetPdgCode() ) == 2212 ||
          TMath::Abs( part.GetPdgCode() ) == 13 ||
          TMath::Abs( part.GetPdgCode() ) == 11
          )
         )
        lNchThisEvent++;
      
      
      if( part.GetPdgCode() == 3312 ){
        hGenerated->Fill(part.GetPt());
        for(Int_t ih=0; ih<12; ih++){
          lPoIBachelorLayer[lNPoI][ih] = kFALSE;
          lPoIPositiveLayer[lNPoI][ih] = kFALSE;
          lPoINegativeLayer[lNPoI][ih] = kFALSE;
        }
        
        lPoIIndex[lNPoI] = iii;
        lPoIPt[lNPoI] = part.GetPt();
        lPoIEta[lNPoI] = part.GetEta();
        
        Int_t lFirstDauID = part.getFirstDaughterTrackId();
        Int_t lLastDauID = part.getLastDaughterTrackId();
        
        //cout<<"To deref: "<<lFirstDauID<<" and "<<lLastDauID<<endl;
        if(lFirstDauID<0||lLastDauID<0) continue;
        
        auto firstdau = mcArr->at(lFirstDauID);
        auto lastdau = mcArr->at(lLastDauID);
        
        lPoIBachelor[lNPoI] = -1;
        lPoINegative[lNPoI] = -1;
        lPoIPositive[lNPoI] = -1;
        
        if(firstdau.GetPdgCode() == -211&&lastdau.GetPdgCode() == 3122){
          lPoIBachelor[lNPoI] = lFirstDauID;
          
          //cout<<"a) Lambda daus to deref: "<<lastdau.getFirstDaughterTrackId()<<" and "<<lastdau.getLastDaughterTrackId()<<endl;
          
          if(lastdau.getFirstDaughterTrackId()<0||lastdau.getLastDaughterTrackId()<0) continue;
          
          auto lambdadau1 = mcArr->at(lastdau.getFirstDaughterTrackId());
          auto lambdadau2 = mcArr->at(lastdau.getLastDaughterTrackId());
          
          if(lambdadau1.GetPdgCode() == -211 && lambdadau2.GetPdgCode() == 2212){
            lPoINegative[lNPoI] = lastdau.getFirstDaughterTrackId();
            lPoIPositive[lNPoI] = lastdau.getLastDaughterTrackId();
          }
          if(lambdadau1.GetPdgCode() == 2212 && lambdadau2.GetPdgCode() == -211){
            lPoINegative[lNPoI] = lastdau.getLastDaughterTrackId();
            lPoIPositive[lNPoI] = lastdau.getFirstDaughterTrackId();
          }
        }
        if(firstdau.GetPdgCode() == 3122&&lastdau.GetPdgCode() == -211){
          lPoIBachelor[lNPoI] = lLastDauID;
          
          //cout<<"b) Lambda daus to deref: "<<firstdau.getFirstDaughterTrackId()<<" and "<<firstdau.getLastDaughterTrackId()<<endl;
          
          if(firstdau.getFirstDaughterTrackId()<0||firstdau.getLastDaughterTrackId()<0) continue;
          
          auto lambdadau1 = mcArr->at(firstdau.getFirstDaughterTrackId());
          auto lambdadau2 = mcArr->at(firstdau.getLastDaughterTrackId());
          
          if(lambdadau1.GetPdgCode() == -211 && lambdadau2.GetPdgCode() == 2212){
            lPoINegative[lNPoI] = firstdau.getFirstDaughterTrackId();
            lPoIPositive[lNPoI] = firstdau.getLastDaughterTrackId();
          }
          if(lambdadau1.GetPdgCode() == 2212 && lambdadau2.GetPdgCode() == -211){
            lPoINegative[lNPoI] = firstdau.getLastDaughterTrackId();
            lPoIPositive[lNPoI] = firstdau.getFirstDaughterTrackId();
          }
        }
        cout<<"Xi indexed "<<lPoIIndex[lNPoI]<<", daughter indices "<<lPoIBachelor[lNPoI]<<", "<<lPoIPositive[lNPoI]<<", "<<lPoINegative[lNPoI]<<endl;
        lNPoI++;
      }
    }
    cout<<"Found "<<lNPoI<<" Xi in this event. Sweeping for daughter hit information"<<endl;
    
    //Let's try to do the tracking and see if we find the desired tracks
    o2::math_utils::Point3D<float> zeropos{0,0,0};
    std::array<float, 6> zerocov;
    for(Int_t jj=0; jj<6; jj++) zerocov[jj]=1e-6;
    o2::dataformats::VertexBase zerovtx(zeropos, zerocov);
    o2::dataformats::DCA dca;
    
    //For vertexing
    std::vector<TrackAlice3> smearedTracks;
    std::vector<o2::InteractionRecord> bcData;
    
    //clear old stuff
//    gen->clearParticles();
//
//    // loop over events
//    if(!gen->importParticles()){
//      cout<<"PROBLEM RETRIEVING EVENT "<< iEvent<<endl;
//    }
    //auto particles = gen->getParticles();
    lWatchSmearing.Start(kFALSE);
    Long_t lParticlesForVertexing = 0;
    Long_t lCorruptedTracks=0;
    lAllTracksRecoed=0;
    lAllTracksAttempted=0;
    
    std::vector<o2::its::TrackITS> allTracks;
    std::vector<o2::MCCompLabel> allTrackLabels;
    
    cout<<"Total particle count: "<<mcArr->size()<<endl;
    Int_t zeroStatus=0;
    for (int iparticle = 0; iparticle < mcArr->size(); ++iparticle){
      //Inner and outer TOF signal initialization
      auto particle = mcArr->at(iparticle);
      if( TMath::Abs(particle.GetEta())> 1.5) continue; //skip outside barrel
      
      Int_t lTrackerIndex = hRadii->FindBin( std::hypot( particle.Vx(), particle.Vy() ) );
      o2::its::ROframe event{iEvent, 12-lTrackerIndex};
      int id{0};
      Bool_t lOnLayer[12];
      for(Int_t il=0;il<12;il++) lOnLayer[il]=kFALSE;
      Int_t lNHitsAll = 0;
      
      //==========================================================================================
      //First investigation: check number of hits
      const Int_t lMaxHits = 500;
      Float_t lHitTime[lMaxHits], lHitIndex[lMaxHits];
      //for (auto& hit : *hits) {
      for(Long_t ihit = 0; ihit<hits->size(); ihit++){
        Hit hit = hits->at(ihit);
        
        if(lNHitsAll>400) continue;
        if(hit.GetTrackID()!=iparticle) continue; //yeah, yeah, there are better ways ... I know ...
        
        int layer{hit.GetDetectorID()};
        float xyz[3]{hit.GetX(), hit.GetY(), hit.GetZ()};
        float r{std::hypot(xyz[0], xyz[1])};
        float phi{std::atan2(-xyz[1], -xyz[0]) + o2::its::constants::math::Pi};
        
        //if you see radius + epsilon, it's still the N-th layer... likely a bug
        if(r>99.0&&r<101){
          //std::cout << "*- Exception caught at a radius of "<< r << std::endl;
          layer = 11;
        }
        if(layer<0 || layer>11){
          std::cout << "*- Layer "<< layer << ": no such thing! What are you doing, mister?"<< std::endl;
        }
        if( layer < lTrackerIndex ) continue;
        
        lHitTime[lNHitsAll] = 1e+12*hit.GetTime();
        lHitIndex[lNHitsAll] = ihit;
        lNHitsAll++;
      }
      //==========================================================================================
      //Second step: only feed first hits, travel outward
      Int_t lNHits = 0;
      const Int_t lhitconstant = lNHitsAll;
      Int_t lHitOrderedIndex[lNHitsAll];
      
      //ordering
      TMath::Sort(lhitconstant,lHitTime,lHitOrderedIndex, kFALSE);
      
      //Avoid loopers
      for(Long_t ihit = 0; ihit<TMath::Min(lNHitsAll,20); ihit++){
        Hit hit = hits->at(lHitIndex[lHitOrderedIndex[ihit]]);
        //cout<<"Particle "<<iparticle<<" hit time "<<1e+12*hit.GetTime()<<endl;
        if(hit.GetTrackID()!=iparticle) continue; //yeah, yeah, there are better ways ... I know ...
        
        int layer{hit.GetDetectorID()};
        float xyz[3]{hit.GetX(), hit.GetY(), hit.GetZ()};
        float r{std::hypot(xyz[0], xyz[1])};
        float phi{std::atan2(-xyz[1], -xyz[0]) + o2::its::constants::math::Pi};
        
        //if you see radius + epsilon, it's still the N-th layer... likely a bug
        if(r>99.0&&r<101){
          //std::cout << "*- Exception caught at a radius of "<< r << std::endl;
          layer = 11;
        }
        if(layer<0 || layer>11){
          std::cout << "*- Layer "<< layer << ": no such thing! What are you doing, mister?"<< std::endl;
        }
        if( layer < lTrackerIndex ) continue;
        
        float lSmearing = lIBresolution;
        if(layer>3) lSmearing = lOBresolution;
        lOnLayer[layer]=kTRUE;

        if (kUseSmearing) {
          phi = gRandom->Gaus(phi, std::asin(lSmearing / r));
          xyz[0] = r * std::cos(phi);
          xyz[1] = r * std::sin(phi);
          xyz[2] = gRandom->Gaus(xyz[2], lSmearing);
        }
        //input offset layer information, ignore first layers
        layer = layer - lTrackerIndex;
        event.addTrackingFrameInfoToLayer(layer, xyz[0], xyz[1], xyz[2], r, phi, std::array<float, 2>{0.f, xyz[2]},
                                          std::array<float, 3>{lSmearing * lSmearing, 0.f, lSmearing * lSmearing});
        event.addClusterToLayer(layer, xyz[0], xyz[1], xyz[2], event.getClustersOnLayer(layer).size());
        event.addClusterLabelToLayer(layer, o2::MCCompLabel(hit.GetTrackID(), iEvent, iEvent, false));
        event.addClusterExternalIndexToLayer(layer, id++);
        lNHits++;
      }
      //==========================================================================================
      
      cout<<"Hits added: "<<lNHits<<endl;
      roFrame = iEvent;
      hRadiiGenerated->Fill(lTrackerIndex);
      
//      if(lNHits<6) continue;
      //if(lTrackerIndex>=7) continue;
      //check contiguous
      Bool_t lContiguous=kFALSE;
      for(Int_t ih=0; ih<7; ih++){
        Int_t lCond=1;
        for(Int_t ic=0; ic<6; ic++){
          lCond *= lOnLayer[ih+ic];
        }
        if(lCond>0) lContiguous=kTRUE;
      }
      if(!lContiguous) continue;
      hRadiiAll->Fill(lTrackerIndex);
      hHitCountAll->Fill(lNHits);
      lAllTracksAttempted++;
      if( std::hypot(particle.Vx(),particle.Vy()) < 0.5 ) lInnerTracksAttempted++;
      //event.addPrimaryVertex(0,0,0);
      if( std::hypot(particle.Vx(),particle.Vy(),particle.Vz()) < 40 ){
        event.addPrimaryVertex(particle.Vx(),particle.Vy(),particle.Vz());
      }else{
        event.addPrimaryVertex(0.,0.,0.);
      }
      
      wdEvent = iEvent;
      
      if(lTrackerIndex==0){
        std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" layer 0 tracking" << std::endl;
        tracker0.clustersToTracks(event);
        auto& tracks = tracker0.getTracks();
        auto& tracksLabels = tracker0.getTrackLabels();
        //std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" done tracking" << std::endl;
        for(Int_t iTrack = 0; iTrack<tracks.size(); iTrack++){
          auto& lab = tracksLabels[iTrack];
          auto& track = tracks[iTrack];
          int lMCID = lab.getTrackID();
          if(lMCID==iparticle){
            lAllTracksRecoed++;
            hRadii->Fill(lTrackerIndex);
            hHitCountFound->Fill(lNHits);
            if( std::hypot(particle.Vx(),particle.Vy()) < 0.5 ) lInnerTracksRecoed++;
            allTracks.emplace_back(tracks[iTrack]);
            allTrackLabels.emplace_back(tracksLabels[iTrack]);
            wdTrack = &track;
            wdTrackLabel = &lab;
            fTreeTracks -> Fill();
          }
        }
      }
      
      if(lTrackerIndex==1){
        //std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" layer 1 tracking" << std::endl;
        tracker1.clustersToTracks(event);
        auto& tracks = tracker1.getTracks();
        auto& tracksLabels = tracker1.getTrackLabels();
        std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" done tracking" << std::endl;
        for(Int_t iTrack = 0; iTrack<tracks.size(); iTrack++){
          auto& lab = tracksLabels[iTrack];
          auto& track = tracks[iTrack];
          int lMCID = lab.getTrackID();
          if(lMCID==iparticle){
            lAllTracksRecoed++;
            hRadii->Fill(lTrackerIndex);
            hHitCountFound->Fill(lNHits);
            if( std::hypot(particle.Vx(),particle.Vy()) < 0.5 ) lInnerTracksRecoed++;
            allTracks.emplace_back(tracks[iTrack]);
            allTrackLabels.emplace_back(tracksLabels[iTrack]);
            wdTrack = &track;
            wdTrackLabel = &lab;
            fTreeTracks -> Fill();
          }
        }
      }
      
      if(lTrackerIndex==2){
        //std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" layer 2 tracking" << std::endl;
        tracker2.clustersToTracks(event);
        auto& tracks = tracker2.getTracks();
        auto& tracksLabels = tracker2.getTrackLabels();
        std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" done tracking" << std::endl;
        for(Int_t iTrack = 0; iTrack<tracks.size(); iTrack++){
          auto& lab = tracksLabels[iTrack];
          auto& track = tracks[iTrack];
          int lMCID = lab.getTrackID();
          if(lMCID==iparticle){
            lAllTracksRecoed++;
            hRadii->Fill(lTrackerIndex);
            hHitCountFound->Fill(lNHits);
            if( std::hypot(particle.Vx(),particle.Vy()) < 0.5 ) lInnerTracksRecoed++;
            allTracks.emplace_back(tracks[iTrack]);
            allTrackLabels.emplace_back(tracksLabels[iTrack]);
            wdTrack = &track;
            wdTrackLabel = &lab;
            fTreeTracks -> Fill();
          }
        }
      }
      
      if(lTrackerIndex==3){
        //std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" layer 3 tracking" << std::endl;
        tracker3.clustersToTracks(event);
        auto& tracks = tracker3.getTracks();
        auto& tracksLabels = tracker3.getTrackLabels();
        std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" done tracking" << std::endl;
        for(Int_t iTrack = 0; iTrack<tracks.size(); iTrack++){
          auto& lab = tracksLabels[iTrack];
          auto& track = tracks[iTrack];
          int lMCID = lab.getTrackID();
          if(lMCID==iparticle){
            lAllTracksRecoed++;
            hRadii->Fill(lTrackerIndex);
            hHitCountFound->Fill(lNHits);
            if( std::hypot(particle.Vx(),particle.Vy()) < 0.5 ) lInnerTracksRecoed++;
            allTracks.emplace_back(tracks[iTrack]);
            allTrackLabels.emplace_back(tracksLabels[iTrack]);
            wdTrack = &track;
            wdTrackLabel = &lab;
            fTreeTracks -> Fill();
          }
        }
      }
      
      if(lTrackerIndex==4){
        //std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" layer 4 tracking" << std::endl;
        tracker4.clustersToTracks(event);
        auto& tracks = tracker4.getTracks();
        auto& tracksLabels = tracker4.getTrackLabels();
        std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" done tracking" << std::endl;
        for(Int_t iTrack = 0; iTrack<tracks.size(); iTrack++){
          auto& lab = tracksLabels[iTrack];
          auto& track = tracks[iTrack];
          int lMCID = lab.getTrackID();
          if(lMCID==iparticle){
            lAllTracksRecoed++;
            hRadii->Fill(lTrackerIndex);
            hHitCountFound->Fill(lNHits);
            if( std::hypot(particle.Vx(),particle.Vy()) < 0.5 ) lInnerTracksRecoed++;
            allTracks.emplace_back(tracks[iTrack]);
            allTrackLabels.emplace_back(tracksLabels[iTrack]);
            wdTrack = &track;
            wdTrackLabel = &lab;
            fTreeTracks -> Fill();
          }
        }
      }
      
      if(lTrackerIndex==5){
        //std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" layer 5 tracking" << std::endl;
        tracker5.clustersToTracks(event);
        auto& tracks = tracker5.getTracks();
        auto& tracksLabels = tracker5.getTrackLabels();
        std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" done tracking" << std::endl;
        for(Int_t iTrack = 0; iTrack<tracks.size(); iTrack++){
          auto& lab = tracksLabels[iTrack];
          auto& track = tracks[iTrack];
          int lMCID = lab.getTrackID();
          if(lMCID==iparticle){
            lAllTracksRecoed++;
            hRadii->Fill(lTrackerIndex);
            hHitCountFound->Fill(lNHits);
            if( std::hypot(particle.Vx(),particle.Vy()) < 0.5 ) lInnerTracksRecoed++;
            allTracks.emplace_back(tracks[iTrack]);
            allTrackLabels.emplace_back(tracksLabels[iTrack]);
            wdTrack = &track;
            wdTrackLabel = &lab;
            fTreeTracks -> Fill();
          }
        }
      }
      
      if(lTrackerIndex>=6){
        //std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" layer 6 tracking" << std::endl;
        tracker6.clustersToTracks(event);
        auto& tracks = tracker6.getTracks();
        auto& tracksLabels = tracker6.getTrackLabels();
        std::cout << "*- Event " << iEvent << ", particle "<<iparticle<<" done tracking" << std::endl;
        for(Int_t iTrack = 0; iTrack<tracks.size(); iTrack++){
          auto& lab = tracksLabels[iTrack];
          auto& track = tracks[iTrack];
          int lMCID = lab.getTrackID();
          if(lMCID==iparticle){
            lAllTracksRecoed++;
            hRadii->Fill(lTrackerIndex);
            hHitCountFound->Fill(lNHits);
            if( std::hypot(particle.Vx(),particle.Vy()) < 0.5 ) lInnerTracksRecoed++;
            allTracks.emplace_back(tracks[iTrack]);
            allTrackLabels.emplace_back(tracksLabels[iTrack]);
            wdTrack = &track;
            wdTrackLabel = &lab;
            fTreeTracks -> Fill();
          }
        }
      }
    }
    cout<<"Current size of fTreeTracks -> "<<fTreeTracks -> GetEntries()<<" (Ntracks "<<lAllTracksRecoed<<")"<<endl;
    
    //cout<<zeroStatus<<" out of "<<particles.size()<<" transported"<<endl;
    cout<<"Partial outcome: "<<lAllTracksRecoed<<" out of "<<lAllTracksAttempted<<endl;
    cout<<"Partial outcome (inner): "<<lInnerTracksRecoed<<" out of "<<lInnerTracksAttempted<<endl;
    std::cout << "*- Determining if xi daughter indices are captured by tracker or not..." << std::endl;
    
    for(Int_t ip=0; ip<lNPoI; ip++){
      fPtMC = lPoIPt[ip];
      fEtaMC = lPoIEta[ip];
      fBachHits=0;
      fNegHits=0;
      fPosHits=0;
      for(Int_t ih=0; ih<12; ih++){
        fBachHitLayer[ih] = kFALSE;
        fPosHitLayer[ih] = kFALSE;
        fNegHitLayer[ih] = kFALSE;
      }
      for(Int_t ih=0; ih<12; ih++){
        if( lPoIBachelorLayer[ip][ih] ) fBachHits++;
        if( lPoIPositiveLayer[ip][ih] ) fPosHits++;
        if( lPoINegativeLayer[ip][ih] ) fNegHits++;
        if( lPoIBachelorLayer[ip][ih] ) fBachHitLayer[ih] = kTRUE;
        if( lPoIPositiveLayer[ip][ih] ) fPosHitLayer[ih] = kTRUE;
        if( lPoINegativeLayer[ip][ih] ) fNegHitLayer[ih] = kTRUE;
      }
      //only fill if in correct channel
      if( lPoIPositive[ip] < 0 || lPoINegative[ip] < 0) continue;
      
      fBachTracked = kFALSE;
      fPosTracked = kFALSE;
      fNegTracked = kFALSE;
      
      Int_t lBachTrackIndex=-1, lPosTrackIndex=-1, lNegTrackIndex=-1;
      
      for (unsigned int i{0}; i < allTracks.size(); ++i) {
        auto& lab = allTrackLabels[i];
        auto& track = allTracks[i];
        int lMCID = lab.getTrackID();
        
        if( lMCID == lPoIBachelor[ip] ) {
          fBachTracked = kTRUE;
          lBachTrackIndex = i;
        }
        if( lMCID == lPoIPositive[ip] ){
          fPosTracked = kTRUE;
          lPosTrackIndex = i;
        }
        if( lMCID == lPoINegative[ip] ){
          fNegTracked = kTRUE;
          lNegTrackIndex = i;
        }
      }
      fCascadeReco = kFALSE;
      
      //Attempt combination in case tracks correctly recoed
      if(fBachTracked&&fPosTracked&&fNegTracked){
        auto TrackBach = allTracks[lBachTrackIndex];
        auto TrackPos = allTracks[lPosTrackIndex];
        auto TrackNeg = allTracks[lNegTrackIndex];
        
        int nCand = fitterV0.process(TrackPos, TrackNeg);
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
          
          auto tV0 = o2::track::TrackParCov(vertex, momentum, covV0, 0);
          
          int nCand2 = fitterCasc.process(tV0, TrackBach);
          if (nCand2 > 0) {
            fCascadeReco = kTRUE;
          }
        }
      } //end attempt at cascade reconstruction
      
      fTree->Fill();
    } //end PoI loop
  }//end event loop
  fQA->cd();
  hRadii->Write();
  hRadiiAll->Write();
  hRadiiGenerated->Write();
  
  hHitCountAll->Write(); 
  hHitCountFound->Write();
  
  hGenerated->Write();
  hPartialTransportDebug->Write();
  fQA->Write();
  
  fileTracks->Write();
  
  TFile *fTrackingOut = new TFile("trackingqa.root", "RECREATE");
  hRadii->Write();
  hRadiiAll->Write();
  hRadiiGenerated->Write();
  hHitCountAll->Write();
  hHitCountFound->Write();
  hGenerated->Write();
  hPartialTransportDebug->Write();
  fTrackingOut->Write();
  
  cout<<"Final outcome: "<<lAllTracksRecoed<<" out of "<<lAllTracksAttempted<<endl;
  cout<<"Final outcome (inner): "<<lInnerTracksRecoed<<" out of "<<lInnerTracksAttempted<<endl;
  cout<<"Done!"<<endl;
}

