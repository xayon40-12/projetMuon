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

 
 
 fekin0=-1;
 fekin1=-1;

 fE0=-1;
 fE1=-1;
 fE2=-1;
 fE3=-1;

 fevent=0;

 fgPb=0,fnPb=0,fePb=0,fotherPb=0,fmuPb=0;


 

 fEdep_gPb=0,fEdep_nPb=0,fEdep_ePb=0,fEdep_otherPb=0,fEdep_muPb=0;



 ftotEPb=0;


}
RootFile_evt::~RootFile_evt()
{}

void RootFile_evt::Create()
{
 
hfile = new TFile("Results.root","RECREATE","ROOT file with histograms");
 

 
 

//treeP = new TTree("treeP","treeP"); 


tree = new TTree("tree","tree"); 
 

 tree->Branch("Nb_gammas_Pb",&fgPb,"fgPb/I"); 
 tree->Branch("Nb_neutrons_Pb",&fnPb,"fnPb/I"); 
 tree->Branch("Nb_electrons_Pb",&fePb,"fePb/I"); 
 tree->Branch("Nb_muons_Pb",&fmuPb,"fmuPb/I"); 
 tree->Branch("Nb_other_part_Pb",&fotherPb,"fotherPb/I"); 

 
 tree->Branch("DepE_gammas_Pb",&fEdep_gPb,"fEdep_gPb/D"); 
 tree->Branch("DepE_neutrons_Pb",&fEdep_nPb,"fEdep_nPb/D"); 
 tree->Branch("DepE_electrons_Pb",&fEdep_ePb,"fEdep_ePb/D");
 tree->Branch("DepE_muons_Pb",&fEdep_muPb,"fEdep_muPb/D");

 

 //-------------------------------------------------------------------- 
 
 tree->Branch("Tot_depE_Pb",&ftotEPb,"ftotEPb/D");

 tree->Branch("ekin0",&fekin0,"fekin0/D"); 
 tree->Branch("ekin1",&fekin1,"fekin1/D"); 

 
 tree->Branch("E0",&fE0,"fE0/D");  
 tree->Branch("E1",&fE1,"fE1/D"); 
 tree->Branch("E2",&fE2,"fE2/D"); 
 tree->Branch("E3",&fE3,"fE3/D"); 
 tree->Branch("event",&fevent,"fevent/I"); 
 // tree->Branch("TrackID",&ID,"ID/I"); 

}

 void RootFile_evt::FillTree() {
   //G4cout<< "tree:  " << tree << G4endl;
   //G4cout<< "fE0:  " << fE0 << G4endl;
   tree->Fill();
}

void RootFile_evt::EndOfAction()
{
  tree->Write();
  hfile->Write();
  hfile->Close();
}
