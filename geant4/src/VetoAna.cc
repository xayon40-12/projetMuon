
#include "TrackerHit.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4SDManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "G4Run.hh"
//#include "RootFile_evt.hh"

#include "CLHEP/Random/RandGauss.h"
#include "VetoAna.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//extern RootFile_evt *test; 

#include <unordered_set>

#include "RootFile_evt.hh"
extern RootFile_evt *test;

VetoAna::VetoAna(): event(0), trackerCollID(0) {}
VetoAna::~VetoAna() {}

void VetoAna::BeginOfRunAction(const G4Run *aRun)
{
   G4cout << "### Begin Run " << aRun->GetRunID() << " start." << G4endl;
}
void VetoAna::EndOfRunAction(const G4Run *aRun)
{
   G4cout << "### End Run " << aRun->GetRunID() << " stop." << G4endl;
}


void VetoAna::BeginOfEventAction(const G4Event* evt)
{
  G4cout << ">>> Begin Event number " << evt->GetEventID() << G4endl;

    event=evt->GetEventID();
    test->SetEvent(event);
    G4SDManager * SDman = G4SDManager::GetSDMpointer();
    trackerCollID = SDman->GetCollectionID("TrackerHitsCollection");
}

void VetoAna::EndOfEventAction(const G4Event* evt)
{
  std::unordered_set<G4int> ids;
  G4double Etot = 0;
  if(trackerCollID>=0) {
    G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    if(HCE){
      B2TrackerHitsCollection* THC = (B2TrackerHitsCollection*)(HCE->GetHC(trackerCollID));
      if(THC){
	int n_hit = THC->entries();
	G4cout << "    " << n_hit << " hits are stored in trackerCollection:" << G4endl << G4endl; 
	B2TrackerHit lastPart;
	G4double totalDeposit = 0;
	
	for (G4int i=0;i<n_hit;i++)
	{
	  B2TrackerHit *part = (*THC)[i];
	  G4double Edep = part->GetEdep();
	  Etot += Edep;
	  int ID = part->GetTrackID();
	  
	  if(ids.find(ID) == ids.end()) {
	    ids.insert(ID);
	    if(i != 0) {
	      lastPart.SetEdep(totalDeposit);
	      lastPart.SetParentName(names[lastPart.GetParentID()]);
	      lastPart.Print();
	    }
	    part->SetTotalEnergy(part->GetTotalEnergy() + part->GetEdep());// add edep the first time because it is already substracted
	    lastPart = *part;
	    totalDeposit = 0;
	  }
	  
	  totalDeposit += part->GetEdep();
	}
      }
    }
  }
  
 // G4cout << ">>> End Event number " << evt->GetEventID() <<" Etot "<< G4BestUnit(Etot,"Energy") << G4endl;
  G4cout << G4endl << "    " << ids.size() << " particle passed through the detector." << G4endl;
  G4cout << " ----------------------------- " << G4endl;
  
  //Filling tree
  //  test->GetFileRoot()->cd();

  if(Etot > 0) test->SettotEPb(Etot);
  test->FillTree();
}
void VetoAna::UserSteppingAction(const G4Step* aStep)
{
  //auto Edep = aStep->GetTotalEnergyDeposit();
  auto track = aStep->GetTrack();
  //auto Etot = track->GetTotalEnergy();
  auto ID = track->GetTrackID();
  //auto volName = track->GetVolume()->GetName();
  auto partName = track->GetDefinition()->GetParticleName();
  //auto vtx = track->GetVertexPosition();
  names[ID] = partName;
}
