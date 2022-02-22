#ifndef ROOT_SBSCherenkovDetector
#define ROOT_SBSCherenkovDetector

//////////////////////////////////////////////////////////////////////////
//
// SBSCherenkovDetector
//
// The Hall A RICH
//
//////////////////////////////////////////////////////////////////////////

//#include "THaPidDetector.h"
#include "SBSGenericDetector.h"
#include "SBSCherenkov_ClusterList.h"
#include "TBits.h"
#include "TClonesArray.h"
#include <stdint.h>
#include <map>

class THaTrack;
class THaBenchmark;

const double m_el = 0.5110034e-3; // electron mas in GeV
 const double m_pi = 139.57018e-3; // pion mass in GeV
// const double m_pi = 0.5110034e-3; // FC: NOT TRUE, JUST FOR TESTING!
const double m_ka = 493.677e-3;   // kaon mass in GeV
const double m_pr = 938.272e-3;   // proton mass in GeV

class SBSCherenkovDetector : public SBSGenericDetector {
  
public:

  SBSCherenkovDetector( const char* name, const char* description="", 
	   THaApparatus* apparatus=NULL );
  virtual ~SBSCherenkovDetector();
  
  virtual void         Clear( Option_t* opt="" );
  virtual Int_t        Decode( const THaEvData& );
  virtual Int_t        CoarseProcess( TClonesArray& tracks );
  virtual Int_t        FineProcess( TClonesArray& tracks );

  SBSCherenkov_Hit*         GetHit(Int_t i) const  
  { return (SBSCherenkov_Hit*)fHits->At(i); } 
  SBSCherenkov_Cluster*     GetCluster(Int_t i) const 
  { return (SBSCherenkov_Cluster*)fClusters->At(i); } 
  
  Int_t                GetNumHits() const 
    { return fHits->GetLast()+1; }
  Int_t                GetNumClusters() const 
    { return fClusters->GetLast()+1; }

  //Int_t                GetMaxNumHits() const { return fMaxNumHits; }
  //void                 SetMaxNumHits( Int_t MaxNumHit ) 
  //{ fMaxNumHits=MaxNumHit; }
  void                 EnableClusterResolving( Bool_t flag = kTRUE )
  { fDoResolve = flag; }
  void                 EnableBenchmarks( Bool_t b = kTRUE )
  { fDoBench = b; }
  void                 PrintBenchmarks() const;
  
protected:

  TClonesArray*     fHits;          // Array of hits for each event
  TClonesArray*     fClusters;      // Clusters of hits

  Bool_t  fDoResolve;    // true = resolve overlapping clusters
  Bool_t  fDoTimeFilter; // true = filter the hits in each cluster with timing
  
  //Double_t fTrackX;      // x pos of Golden Track in RICH plane
  //Double_t fTrackY;      // y pos of Golden Track in RICH plane

  Bool_t         fDoBench;         //Collect detailed timing statistics
  THaBenchmark*  fBench;           //Counters for timing statistics
  
  void    DeleteClusters();
  Int_t   FindClusters();
  //Int_t   MatchClustersWithTracks( TClonesArray& tracks );
  //Int_t   CleanClustersWithTime();

  std::vector<Double_t> fHit_tmin;
  std::vector<Double_t> fHit_tmax;

  std::vector<Double_t> fAmpToTCoeff;
  
  virtual Int_t  ReadDatabase( const TDatime& date );
  virtual Int_t  DefineVariables( EMode mode = kDefine );

private:
  
  bool fMCdata;// easy way to enable/disable the use of MC data.
  
  ClassDef(SBSCherenkovDetector,0)   //The Hall A RICH
};

#endif









