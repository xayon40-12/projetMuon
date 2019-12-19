#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TApplication.h"
#include "TSystem.h"
#include "TH1.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TFile.h"
#include "G4ios.hh"
#include "RootFile_evt.hh"
#include <TTree.h>
#include <TMath.h>

RootFile_evt::RootFile_evt()
{
  //  hEdep_0 = (TH1D *)0;
  // hEdep_1 = (TH1D *)0;
  // hEKinelost_0 = (TH1D *)0;
  // hEKinelost_1 = (TH1D *)0;
 hfile = (TFile *)0; 
 tree = (TTree *)0; 

 ftotEPb=0;
 ftime=0;


}
RootFile_evt::~RootFile_evt()
{}

void RootFile_evt::Create()
{
 
hfile = new TFile("Results.root","RECREATE","ROOT file with histograms");
 

 
 

//treeP = new TTree("treeP","treeP"); 


tree = new TTree("tree","tree"); 
 
 //-------------------------------------------------------------------- 
 
 tree->Branch("Tot_depE_Pb",&ftotEPb,"ftotEPb/D");
 tree->Branch("time",&ftime,"ftime/D");

 tree->Branch("event",&fevent,"fevent/I"); 

}

 void RootFile_evt::FillTree() {
   tree->Fill();
}

void RootFile_evt::EndOfAction()
{
  tree->Write();
  hfile->Write();
  hfile->Close();
}
