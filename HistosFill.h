// Purpose: Fill jet physics analysis histograms
// Author:  mikko.voutilainen@cern.ch
// Co-author: hannu.siikonen@cern.ch
// Created: April 19, 2010

////////////////////////////////////////////////////////////////////////
// Notes:   Automatically created using TChain::MakeClass("HistosFill")
//          Keep variable declarations in the automatic order,
//          update array maximum sizes!!
////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar  4 11:57:12 2016 by ROOT version 6.06/00
// from TTree ProcessedTree/ProcessedTree
//////////////////////////////////////////////////////////

#ifndef HistosFill_h
#define HistosFill_h

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"
#include "TStyle.h"
#include "TF1.h"
#include "TF2.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TDirectory.h"
#include "TStopwatch.h"
#include "TSystem.h"
#include "TLorentzVector.h"
#include "TRandom3.h"

#include "settings.h"
#include "HistosBasic.h"
#include "HistosEta.h"
#include "HistosMC.h"
#include "HistosRun.h"
#include "tools.h"
#include "IOV.h"

#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

class HistosFill {
public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain

  static const Int_t kMaxGenJets_   = 100;
  static const Int_t kMaxPFJetsCHS_ = 100;

  bool _initsuccess;

  // Declaration of leaf types
  //QCDEvent        *events;
  vector<vector<int> > filterIdList_;
  Bool_t          EvtHdr__mIsPVgood;
  Bool_t          EvtHdr__mHCALNoise;
  Bool_t          EvtHdr__mHCALNoiseNoMinZ;
  Int_t           EvtHdr__mRun;
  UInt_t          EvtHdr__mEvent; // Int_t -> UInt_t
  Int_t           EvtHdr__mLumi;
  Int_t           EvtHdr__mBunch;
  Int_t           EvtHdr__mNVtx;
  Int_t           EvtHdr__mNVtxGood;
  Int_t           EvtHdr__mOOTPUEarly;
  Int_t           EvtHdr__mOOTPULate;
  Int_t           EvtHdr__mINTPU;
  Int_t           EvtHdr__mNBX;
  Float_t         EvtHdr__mPVndof;
  Float_t         EvtHdr__mTrPu;
  Float_t         EvtHdr__mPVx;
  Float_t         EvtHdr__mPVy;
  Float_t         EvtHdr__mPVz;
  Float_t         EvtHdr__mBSx;
  Float_t         EvtHdr__mBSy;
  Float_t         EvtHdr__mBSz;
  Float_t         EvtHdr__mPthat;
  Float_t         EvtHdr__mWeight;
  Float_t         EvtHdr__mCaloRho;
  Float_t         EvtHdr__mPFRho;
  Float_t         CaloMet__et_;
  Float_t         CaloMet__CaloMetPt_;
  Float_t         CaloMet__sumEt_;
  Float_t         CaloMet__phi_;
  Float_t         PFMet__et_;
  Float_t         PFMet__CaloMetPt_;
  Float_t         PFMet__sumEt_;
  Float_t         PFMet__phi_;
  Float_t         MvaMet__et_;
  Float_t         MvaMet__CaloMetPt_;
  Float_t         MvaMet__sumEt_;
  Float_t         MvaMet__phi_;
  vector<int>     TriggerDecision_;
  vector<string>  triggerList_;
  vector<int>     L1Prescale_;
  vector<int>     HLTPrescale_;
  //vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > > > HLTObj_;
  //vector<vector<ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<double> > > > L1Obj_;
  Int_t           GenJets__;
  Double_t        GenJets__fCoordinates_fX[kMaxGenJets_];   //[GenJets__]
  Double_t        GenJets__fCoordinates_fY[kMaxGenJets_];   //[GenJets__]
  Double_t        GenJets__fCoordinates_fZ[kMaxGenJets_];   //[GenJets__]
  Double_t        GenJets__fCoordinates_fT[kMaxGenJets_];   //[GenJets__]
  Int_t           PFJetsCHS__;
  Double_t        PFJetsCHS__P4__fCoordinates_fX[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Double_t        PFJetsCHS__P4__fCoordinates_fY[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Double_t        PFJetsCHS__P4__fCoordinates_fZ[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Double_t        PFJetsCHS__P4__fCoordinates_fT[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Double_t        PFJetsCHS__genP4__fCoordinates_fX[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Double_t        PFJetsCHS__genP4__fCoordinates_fY[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Double_t        PFJetsCHS__genP4__fCoordinates_fZ[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Double_t        PFJetsCHS__genP4__fCoordinates_fT[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__genR_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__cor_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  vector<double>  PFJetsCHS__jecLabels_[kMaxPFJetsCHS_];
  Float_t         PFJetsCHS__unc_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  vector<float>   PFJetsCHS__uncSrc_[kMaxPFJetsCHS_];
  Float_t         PFJetsCHS__area_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Bool_t          PFJetsCHS__looseID_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Bool_t          PFJetsCHS__tightID_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__CSVpfPositive_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__CSVpfNegative_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  //Float_t         PFJetsCHS__boosted_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__QGtagger_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__partonFlavour_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__hadronFlavour_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__recommend1_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__recommend2_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__recommend3_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  //Float_t         PFJetsCHS__pfCombinedCvsL_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  //Float_t         PFJetsCHS__pfCombinedCvsB_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__chf_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__nhf_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__nemf_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__cemf_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__muf_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__hf_hf_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__hf_phf_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__hf_hm_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__hf_phm_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__chm_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__nhm_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__phm_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__elm_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__mum_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__ncand_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  //Int_t           PFJetsCHS__cm_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__beta_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__betaStar_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__betaPrime_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__mpuTrk_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__mlvTrk_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Int_t           PFJetsCHS__mjtTrk_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__hof_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__pujid_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__calojetpt_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  Float_t         PFJetsCHS__calojetef_[kMaxPFJetsCHS_];   //[PFJetsCHS__]
  vector<float>   genFlavour_;
  vector<float>   genFlavourHadron_;

  // List of branches
  TBranch        *b_events_filterIdList_;   //!
  TBranch        *b_events_EvtHdr__mIsPVgood;   //!
  TBranch        *b_events_EvtHdr__mHCALNoise;   //!
  TBranch        *b_events_EvtHdr__mHCALNoiseNoMinZ;   //!
  TBranch        *b_events_EvtHdr__mRun;   //!
  TBranch        *b_events_EvtHdr__mEvent;   //!
  TBranch        *b_events_EvtHdr__mLumi;   //!
  TBranch        *b_events_EvtHdr__mBunch;   //!
  TBranch        *b_events_EvtHdr__mNVtx;   //!
  TBranch        *b_events_EvtHdr__mNVtxGood;   //!
  TBranch        *b_events_EvtHdr__mOOTPUEarly;   //!
  TBranch        *b_events_EvtHdr__mOOTPULate;   //!
  TBranch        *b_events_EvtHdr__mINTPU;   //!
  TBranch        *b_events_EvtHdr__mNBX;   //!
  TBranch        *b_events_EvtHdr__mPVndof;   //!
  TBranch        *b_events_EvtHdr__mTrPu;   //!
  TBranch        *b_events_EvtHdr__mPVx;   //!
  TBranch        *b_events_EvtHdr__mPVy;   //!
  TBranch        *b_events_EvtHdr__mPVz;   //!
  TBranch        *b_events_EvtHdr__mBSx;   //!
  TBranch        *b_events_EvtHdr__mBSy;   //!
  TBranch        *b_events_EvtHdr__mBSz;   //!
  TBranch        *b_events_EvtHdr__mPthat;   //!
  TBranch        *b_events_EvtHdr__mWeight;   //!
  TBranch        *b_events_EvtHdr__mCaloRho;   //!
  TBranch        *b_events_EvtHdr__mPFRho;   //!
  TBranch        *b_events_CaloMet__et_;   //!
  TBranch        *b_events_CaloMet__CaloMetPt_;   //!
  TBranch        *b_events_CaloMet__sumEt_;   //!
  TBranch        *b_events_CaloMet__phi_;   //!
  TBranch        *b_events_PFMet__et_;   //!
  TBranch        *b_events_PFMet__CaloMetPt_;   //!
  TBranch        *b_events_PFMet__sumEt_;   //!
  TBranch        *b_events_PFMet__phi_;   //!
  TBranch        *b_events_MvaMet__et_;   //!
  TBranch        *b_events_MvaMet__CaloMetPt_;   //!
  TBranch        *b_events_MvaMet__sumEt_;   //!
  TBranch        *b_events_MvaMet__phi_;   //!
  TBranch        *b_events_TriggerDecision_;   //!
  TBranch        *b_events_triggerList_;   //!
  TBranch        *b_events_L1Prescale_;   //!
  TBranch        *b_events_HLTPrescale_;   //!
  TBranch        *b_events_GenJets__;   //!
  TBranch        *b_GenJets__fCoordinates_fX;   //!
  TBranch        *b_GenJets__fCoordinates_fY;   //!
  TBranch        *b_GenJets__fCoordinates_fZ;   //!
  TBranch        *b_GenJets__fCoordinates_fT;   //!
  TBranch        *b_events_PFJetsCHS__;   //!
  TBranch        *b_PFJetsCHS__P4__fCoordinates_fX;   //!
  TBranch        *b_PFJetsCHS__P4__fCoordinates_fY;   //!
  TBranch        *b_PFJetsCHS__P4__fCoordinates_fZ;   //!
  TBranch        *b_PFJetsCHS__P4__fCoordinates_fT;   //!
  TBranch        *b_PFJetsCHS__genP4__fCoordinates_fX;   //!
  TBranch        *b_PFJetsCHS__genP4__fCoordinates_fY;   //!
  TBranch        *b_PFJetsCHS__genP4__fCoordinates_fZ;   //!
  TBranch        *b_PFJetsCHS__genP4__fCoordinates_fT;   //!
  TBranch        *b_PFJetsCHS__genR_;   //!
  TBranch        *b_PFJetsCHS__cor_;   //!
  TBranch        *b_PFJetsCHS__jecLabels_;   //!
  TBranch        *b_PFJetsCHS__unc_;   //!
  TBranch        *b_PFJetsCHS__uncSrc_;   //!
  TBranch        *b_PFJetsCHS__area_;   //!
  TBranch        *b_PFJetsCHS__looseID_;   //!
  TBranch        *b_PFJetsCHS__tightID_;   //!
  TBranch        *b_PFJetsCHS__CSVpfPositive_;   //!
  TBranch        *b_PFJetsCHS__CSVpfNegative_;   //!
  //TBranch        *b_PFJetsCHS__boosted_;   //!
  TBranch        *b_PFJetsCHS__QGtagger_;   //!
  TBranch        *b_PFJetsCHS__partonFlavour_;   //!
  TBranch        *b_PFJetsCHS__hadronFlavour_;   //!
  TBranch        *b_PFJetsCHS__recommend1_;   //!
  TBranch        *b_PFJetsCHS__recommend2_;   //!
  TBranch        *b_PFJetsCHS__recommend3_;   //!
  //TBranch        *b_PFJetsCHS__pfCombinedCvsL_;   //!
  //TBranch        *b_PFJetsCHS__pfCombinedCvsB_;   //!
  TBranch        *b_PFJetsCHS__chf_;   //!
  TBranch        *b_PFJetsCHS__nhf_;   //!
  TBranch        *b_PFJetsCHS__nemf_;   //!
  TBranch        *b_PFJetsCHS__cemf_;   //!
  TBranch        *b_PFJetsCHS__muf_;   //!
  TBranch        *b_PFJetsCHS__hf_hf_;   //!
  TBranch        *b_PFJetsCHS__hf_phf_;   //!
  TBranch        *b_PFJetsCHS__hf_hm_;   //!
  TBranch        *b_PFJetsCHS__hf_phm_;   //!
  TBranch        *b_PFJetsCHS__chm_;   //!
  TBranch        *b_PFJetsCHS__nhm_;   //!
  TBranch        *b_PFJetsCHS__phm_;   //!
  TBranch        *b_PFJetsCHS__elm_;   //!
  TBranch        *b_PFJetsCHS__mum_;   //!
  TBranch        *b_PFJetsCHS__ncand_;   //!
  //TBranch        *b_PFJetsCHS__cm_;   //!
  TBranch        *b_PFJetsCHS__beta_;   //!
  TBranch        *b_PFJetsCHS__betaStar_;   //!
  TBranch        *b_PFJetsCHS__betaPrime_;   //!
  TBranch        *b_PFJetsCHS__mpuTrk_;   //!
  TBranch        *b_PFJetsCHS__mlvTrk_;   //!
  TBranch        *b_PFJetsCHS__mjtTrk_;   //!
  TBranch        *b_PFJetsCHS__hof_;   //!
  TBranch        *b_PFJetsCHS__pujid_;   //!
  TBranch        *b_PFJetsCHS__calojetpt_;   //!
  TBranch        *b_PFJetsCHS__calojetef_;   //!
  TBranch        *b_events_genFlavour_;   //!
  TBranch        *b_events_genFlavourHadron_;   //!

  /////////////////////////////////////////////////////////////////////////////
  // Following lines added by hand and must come *after* auto-generated header
  /////////////////////////////////////////////////////////////////////////////

  Int_t GetEntry(Long64_t entry) {
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
  }
  virtual void     Show(Long64_t entry = -1) {
    if (!fChain) return;
    fChain->Show(entry);
  }
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     PrintInfo(string info, bool printcout = false);
  virtual void     PrintMemInfo(bool printcout = false);

  // We don't delete that much stuff here, since ROOT takes care of garbage collection (and gets very easily angry!!!)
  ~HistosFill() {
    if (ferr) delete ferr;
  }
  HistosFill(TChain *tree);
  virtual bool     Init(TTree *tree); // custom

  virtual void     Loop();
  virtual bool     PreRun();
  virtual bool     AcceptEvent();
  virtual void     Report();

  void             FillJetID(vector<bool> &id);
  bool             GetTriggers();

  bool             LoadJSON(const char* filename);
  bool             LoadLumi(const char* filename);
  bool             LoadPuProfiles(const char* datafile, const char* mcfile);
  bool             LoadPrescales(const char* prescalefilename);
  bool             LoadVetoECAL(const char* filename);

  void             InitBasic(string name);
  void             FillBasic(string name);
  void             FillSingleBasic(HistosBasic *h);
  void             WriteBasic();

  void             InitEta(string name);
  void             FillEta(string name, Float_t *pt, Float_t *eta, Float_t *phi);
  void             FillSingleEta(HistosEta *h, Float_t *pt, Float_t *eta, Float_t *phi);
  void             WriteEta();

  void             InitMC(string name);
  void             FillMC(string name, Float_t *recopt, Float_t *genpt, Float_t *pt, Float_t *eta, Float_t *phi);
  void             FillSingleMC(HistosMC *h, Float_t *recopt, Float_t *genpt, Float_t *pt, Float_t *eta, Float_t *phi);
  void             WriteMC();

  void             InitRun(string name, double etamin, double etamax);
  void             FillRun(string name);
  void             WriteRun();

  inline double DPhi(double phi1, double phi2) { // Return value between 0 and phi.
    double dphi = fabs(phi1 - phi2);
    return (dphi <= TMath::Pi())? dphi : TMath::TwoPi() - dphi;
  }

private:
  bool worryHCALHotExcl;
  bool   _pass;
  bool   _pass_qcdmet;

  int _nbadevts_dup;
  int _nbadevts_run;
  int _nbadevts_ls;
  int _nbadevts_lum;
  int _nbadevts_json;
  int _nbadevts_veto;
  int _bscounter_bad;
  int _bscounter_good;
  int _ecalcounter_bad;
  int _ecalcounter_good;
  int _rhocounter_bad;
  int _rhocounter_good;
  int _trgcounter;
  int _evtcounter;
  int _totcounter;
  Long64_t _jentry;
  Long64_t _nentries;
  Long64_t _ntot ;
  Long64_t _nskip;;
  double _xsecMinBias;
  double _w, _w0;
  double _pthatweight;
  double _pthatuplim;

  double rangesHCALHotExcl[4];
  vector<string> _availTrigs;
  vector<unsigned int> _goodTrigs;
  vector<double> _goodWgts;
  vector<bool> _jetids;
  vector<int> _jkmore;

  set<string> _trigs;
  set<int> _badruns;
  set<pair<int, int> > _badlums;
  set<pair<int, int> > _nolums;
  set<pair<int, int> > _badjson;
  set<pair<int, int> > _passedlumis;

  map<int, map<int, set<int> > > _duplicates;
  map<string, map<int, int> > _prescales;
  map<int, map<int, int> > _json;
  map<int, map<int, float> > _avgpu;
  map<int, map<int, float> > _lums;
  map<int, map<int, float> > _lums2;
  map<string, double> _wt; // Trigger pileup and trigger weights
  map<string, vector<HistosBasic*> > _histos;
  map<string, vector<HistosEta*> > _etahistos;
  map<string, vector<HistosMC*> > _mchistos;
  map<string, HistosRun*> _runhistos;
  map<string, TH1D*> _pudist;
  map<string, int> _cnt; // efficiency counters

  TH1D *_pumc;
  TH1D *hmcweight;
  TH2D *h2ECALHotExcl;
  TH2F *_ecalveto;
  TH2F *_h2mu = 0;
  TH3D *_h3probg;

  TFile *_outfile;
  TFile *fECALHotExcl;

  TLorentzVector p4, gp4, genp4, _j1, _j2;
  jec::IOV _iov;
  FactorizedJetCorrector *_JEC, *_L1RC;
  JetCorrectionUncertainty *_jecUnc;

  ofstream *ferr;
  MemInfo_t _info;

  /////////////////////////////////////////////////////////////////////////////
  // Auxiliary variables (declare after TTree variables only)
  /////////////////////////////////////////////////////////////////////////////

  Float_t         trpu;
  Float_t         pvrho;

  Float_t         &pthat;
  Float_t         &weight;
  Int_t           &run;
  UInt_t          &evt;
  Int_t           &lbn;

  Int_t           &itpu;
  Int_t           &ootpulate;
  Int_t           &ootpuearly;

  Int_t           &npv;
  Int_t           &npvgood;
  Float_t         &pvx;
  Float_t         &pvy;
  Float_t         &pvz;
  Float_t         &pvndof;
  //UInt_t          pvntrk;
  Float_t         &bsx;
  Float_t         &bsy;
  //
  Int_t           &njt;
  Int_t           jt3leads[3]; // The three leading jets
  static const Int_t _maxnjt = 250;//100;//90;//kMaxPFJets_;
  Double_t        *jtp4x;//[_maxnjt];   //[njt]
  Double_t        *jtp4y;//[_maxnjt];   //[njt]
  Double_t        *jtp4z;//[_maxnjt];   //[njt]
  Double_t        *jtp4t;//[_maxnjt];   //[njt]
  Float_t         jte[_maxnjt];   //[njt]
  Float_t         jtpt[_maxnjt];   //[njt]
  //Float_t         jtptuchs[_maxnjt];   //EXTRA
  Float_t         jtptu[_maxnjt];   //EXTRA
  //Float_t         jteuchs[_maxnjt];   //EXTRA
  Float_t         jteu[_maxnjt];   //EXTRA
  Float_t         jteta[_maxnjt];   //[njt]
  Float_t         jtphi[_maxnjt];   //[njt]
  Float_t         jty[_maxnjt];   //[njt]
  Float_t         *jta;//[_maxnjt];   //[njt]
  Float_t         *jtjes;//[_maxnjt];   //[njt]
  Float_t         *jtbeta;
  Float_t         *jtbetastar;
  Float_t         *jtbetaprime;
  Float_t         jtjesnew[_maxnjt];   //[njt]
  Float_t         jtjes_l1[_maxnjt];   //[njt]
  Float_t         jtjes_l2l3[_maxnjt];   //[njt]
  Float_t         jtjes_res[_maxnjt];   //[njt]
  Bool_t          *jtidloose;//[_maxnjt];   //[njt]
  Bool_t          *jtidtight;//[_maxnjt];   //[njt]

  //Short_t         jtgenid[_maxnjt];   //[njt]
  //Short_t         jtgenflv[_maxnjt];   //[njt]
  Float_t         *jtgenr;//[_maxnjt];   //[njt]
  Double_t        *jtgenp4x;//[_maxnjt];   //[njt]
  Double_t        *jtgenp4y;//[_maxnjt];   //[njt]
  Double_t        *jtgenp4z;//[_maxnjt];   //[njt]
  Double_t        *jtgenp4t;//[_maxnjt];   //[njt]
  Float_t         jtgenpt[_maxnjt];   //[njt]
  Float_t         jtgeny[_maxnjt];   //EXTRA
  Float_t         jtgeneta[_maxnjt];   //[njt]
  Float_t         jtgenphi[_maxnjt];   //[njt]

  Float_t         *qgl;
  Float_t         *partonflavor;

  Int_t           *jtn;//[_maxnjt];   //[njt]
  Int_t           *jtnch;//[_maxnjt];   //[njt]
  Int_t           *jtnnh;//[_maxnjt];   //[njt]
  Int_t           *jtnne;//[_maxnjt];   //[njt]
  Int_t           *jtnce;//[_maxnjt];   //[njt]
  Int_t           *jtnmu;//[_maxnjt];   //[njt]
  Int_t           *jtnhh;//[_maxnjt];   //[njt]
  Int_t           *jtnhe;//[_maxnjt];   //[njt]

  Float_t         *jtchf;//[_maxnjt];   //[njt]
  Float_t         *jtnhf;//[_maxnjt];   //[njt]
  Float_t         *jtnef;//[_maxnjt];   //[njt]
  Float_t         *jtcef;//[_maxnjt];   //[njt]
  Float_t         *jtmuf;//[_maxnjt];   //[njt]
  Float_t         *jthhf;//[_maxnjt];   //[njt]
  Float_t         *jthef;//[_maxnjt];   //[njt]

  Int_t           &gen_njt;
  Double_t        *gen_jtp4x;//[_maxnjt];   //[njt]
  Double_t        *gen_jtp4y;//[_maxnjt];   //[njt]
  Double_t        *gen_jtp4z;//[_maxnjt];   //[njt]
  Double_t        *gen_jtp4t;//[_maxnjt];   //[njt]
  //Float_t         gen_jte[_maxnjt];   //[njt]
  Float_t         gen_jtpt[_maxnjt];   //[njt]
  Float_t         gen_jteta[_maxnjt];   //[njt]
  Float_t         gen_jtphi[_maxnjt];   //[njt]
  Float_t         gen_jty[_maxnjt];   //[njt]
  Int_t           gen_partonflavor[_maxnjt];

  Float_t         &rho;
  Float_t         &met;
  Float_t         &metphi;
  Float_t         &metsumet;

  Float_t         met1;
  Float_t         metphi1;
  Float_t         met2;
  Float_t         metphi2;
};

#endif