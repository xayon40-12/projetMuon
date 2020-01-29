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

#include "CLHEP/Random/RandGauss.h"
#include "VetoAna.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


#include <unordered_set>

#include "electronics.hh"

VetoAna::VetoAna(): trackerCollID(0), event(0), file_decay("simulated_decay.txt"), file_exp("simulated_exp.txt") {}
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
    double time = 0, time_exp = 0, time_up = 0;
    bool found_up = false, found_down = false, found_down_exp = false, found = false, found_exp = false;
    G4double Etot = 0;

    event=evt->GetEventID();
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

                    B2TrackerHit lastPart;
                    G4double totalDeposit = 0;

                    for (G4int i=0;i<n_hit;i++) {
                        B2TrackerHit *part = (*THC)[i];

                        //get particle name and total energy
                        G4double Edep = part->GetEdep();
                        Etot += Edep;
                        int ID = part->GetTrackID();

                        if (ic == 0 && part->GetPartName() == "mu-" && !found_up) {
                            found_up = true; 
                            time_up = part->GetGlobalTime();
                        }
                        if (ic == 2 && found_up) {
                            if (part->GetPartName() == "mu-" && !found_down) {
                                found_down = true;
                                time = part->GetGlobalTime();
                            }
                            if (part->GetCreationProcess() == "Decay" && !found) {
                                found = true;
                                time = part->GetGlobalTime() - time;    
                            }

                            if(found_down_exp && !found_exp) {
                                found_exp = true;
                                time_exp = part->GetGlobalTime() - time_exp;
                            }
                            if(!found_down_exp) {
                                found_down_exp = true;
                                time_exp = part->GetGlobalTime();
                            }
                        }
                        
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

    if (found) {  
        G4cout <<  "Event number " << evt->GetEventID() << ", " << ids.size() << " particle passed through the detector:\n";
        for (auto part: detected[2]) part.Print();
        G4cout << G4endl;

        file_decay << time/1000 << std::endl;
    }     
    if (found_exp) {
        file_exp << time_exp/1000 << std::endl;
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
