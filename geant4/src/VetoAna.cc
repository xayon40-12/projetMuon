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

VetoAna::VetoAna(): trackerCollID(0), event(0), file("simulated_times.txt") {}
VetoAna::~VetoAna() {}

void VetoAna::BeginOfRunAction(const G4Run *aRun)
{
    G4cout << "### Begin Run " << aRun->GetRunID() << "." << G4endl;
}
void VetoAna::EndOfRunAction(const G4Run *aRun)
{
    G4cout << "### End Run " << aRun->GetRunID() << "." << G4endl;
}


void VetoAna::BeginOfEventAction(const G4Event* /*evt*/) {}

void VetoAna::EndOfEventAction(const G4Event* evt)
{
    std::unordered_set<G4int> ids;
    std::vector<B2TrackerHit> detected[3];
    double time = 0, time_up = 0;
    bool found_up = false, found = false;
    double max_delay = 100*ns;
    G4double Etot = 0;

    event=evt->GetEventID();
    test->SetEvent(event);
    G4SDManager * SDman = G4SDManager::GetSDMpointer();

    std::string colls[3] = {"TrackerHitsCollection1","TrackerHitsCollection2","TrackerHitsCollection3"};

    G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    for (int ic = 0; ic<3; ic++) {
        trackerCollID = SDman->GetCollectionID(colls[ic]);
        if(trackerCollID>=0) {
            if(HCE){
                B2TrackerHitsCollection* THC = (B2TrackerHitsCollection*)(HCE->GetHC(trackerCollID));
                if(THC){
                    int n_hit = THC->entries();
                    if (n_hit < 1) continue;

                    B2TrackerHit *part0 = (*THC)[0];
                    auto p0name = part0->GetPartName();

                    if (ic == 1) {
                        found_up = true; 
                        time_up = part0->GetGlobalTime();
                    }

                    if (ic == 3 && found_up) {
                        time = part0->GetGlobalTime();
                        double diff = part0->GetGlobalTime() - time_up;
                        if (diff < 0 || diff > max_delay) break;
                    }

                    B2TrackerHit lastPart;
                    G4double totalDeposit = 0;

                    for (G4int i=0;i<n_hit;i++) {
                        B2TrackerHit *part = (*THC)[i];
                        //set time with first particle generated
                        if (part->GetPartName() != p0name && !found) { time = part->GetGlobalTime() - time; found = true; }

                        //get particle name and total energy
                        G4double Edep = part->GetEdep();
                        Etot += Edep;
                        int ID = part->GetTrackID();
                        
                        if (part->GetEdep() != 0 && i != 0) lastPart.SetDisappearTime(part->GetGlobalTime());

                        if(ids.find(ID) == ids.end()) {
                            ids.insert(ID);
                            if(i != 0) {
                                lastPart.SetEdep(totalDeposit);
                                lastPart.SetParentName(names[lastPart.GetParentID()]);
                                detected[ic].push_back(lastPart);
                                //lastPart.Print();
                            }
                            part->SetTotalEnergy(part->GetTotalEnergy() + part->GetEdep());// add edep the first time because it is already substracted
                            part->SetAppearTime(part->GetGlobalTime());
                            if (part->GetEdep() != 0) part->SetDisappearTime(part->GetGlobalTime());
                            lastPart = *part;
                            totalDeposit = 0;
                        }
                        totalDeposit += part->GetEdep();
                    }
                    lastPart.SetEdep(totalDeposit);
                    lastPart.SetParentName(names[lastPart.GetParentID()]);
                    detected[ic].push_back(lastPart);
                }
            }
        }
    }

    if (ids.size() > 1) {  
        G4cout <<  "Event number " << evt->GetEventID() << ", " << ids.size() << " particle passed through the detector:\n";
        for (auto part: detected[2]) part.Print();
        G4cout << G4endl;

        file << time << std::endl;

        //if(Etot > 0) test->SettotEPb(Etot);
        //test->SetTime(time);
        //test->FillTree();
    }     
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
