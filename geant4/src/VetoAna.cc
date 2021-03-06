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
#include <algorithm>

#include "electronics.hh"

VetoAna::VetoAna(): trackerCollID(0), event(0), file_decay("simulated_decay.txt"), file_exp("simulated_exp.txt"), file_exp_decay("simulated_exp_decay.txt"), file_count("simulated_count.txt"), file_processes("simulated_processes.txt"), file_energies("simulated_energies.txt"), first_event(true) {}
VetoAna::~VetoAna() {}

void VetoAna::BeginOfRunAction(const G4Run *aRun)
{
    G4cout << "### Begin Run " << aRun->GetRunID() << "." << G4endl;
    count_decay = count_exp = count_exp_decay = 0;
}


void VetoAna::BeginOfEventAction(const G4Event* /*evt*/) {}

void VetoAna::EndOfEventAction(const G4Event* evt)
{
    std::unordered_set<G4int> ids[3];
    //std::vector<B2TrackerHit> detected[3];
    std::vector<std::pair<double,std::string>> detected_times[3];
    double time = 0, time_exp = 0;
    bool found_up = false, found_down = false, found_down_exp = false, found = false, found_exp = false, found_exp_decay = false;
    G4double Etot = 0;
    int i_up = 0, i_down = 0, i_dec = 0;

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
                        /*G4double Edep = part->GetEdep();
                        Etot += Edep;*/
                        int ID = part->GetTrackID();

                        if (ic == 0 && part->GetPartName() == "mu-" && !found_up) {
                            //i_up = ids[ic].size()+1;
                            found_up = true; 
                        }
                        if (ic == 2 && found_up) {
                            if (part->GetCreationProcess() == "Decay" && !found && found_down) {
                                //i_dec = ids[ic].size()+1;
                                found = true;
                                time = part->GetGlobalTime() - time;
                                count_decay++;
                            }
                            if (part->GetPartName() == "mu-" && !found_down) {
                                //i_down = ids[ic].size()+1;
                                found_down = true;
                                time = part->GetGlobalTime();
                            }
                        }
                        //if (part->GetEdep() != 0 && i != 0) lastPart.SetDisappearTime(part->GetGlobalTime());

                        if(ids[ic].find(ID) == ids[ic].end()) {
                            ids[ic].insert(ID);
                            //if(detected_times[ic].size() == 0 && part->GetPartName() != "mu-") std::cerr << ic << ": " << part->GetPartName() << std::endl;
                            detected_times[ic].push_back({part->GetGlobalTime(),part->GetCreationProcess()});
                            /*if(i != 0) {
                                lastPart.SetEdep(totalDeposit);
                                lastPart.SetParentName(names[lastPart.GetParentID()]);
                                detected[ic].push_back(lastPart);
                                //lastPart.Print();
                            }
                            part->SetTotalEnergy(part->GetTotalEnergy() + part->GetEdep());// add edep the first time because it is already substracted
                            part->SetAppearTime(part->GetGlobalTime());
                            if (part->GetEdep() != 0) part->SetDisappearTime(part->GetGlobalTime());
                            lastPart = *part;
                            totalDeposit = 0;*/
                        }
                        //totalDeposit += part->GetEdep();
                    }
                    /*lastPart.SetEdep(totalDeposit);
                    lastPart.SetParentName(names[lastPart.GetParentID()]);
                    detected[ic].push_back(lastPart);*/

                    if(ic == 2 && n_hit>0) first_event = false;
                }
            }
        }
    }
    //if(i_dec > 0) std::cerr << i_up << "\t" << i_down << "\t" << i_dec << std::endl;
    //for(auto p: detected[2]) file_processes << p.GetCreationProcess() << std::endl;

    if (found) {
        //G4cout <<  "Event number " << evt->GetEventID() << ", " << ids.size() << " particle passed through the detector:\n";
        //for (auto part: detected[2]) part.Print();
        //G4cout << G4endl;

        file_decay << time/1000 << std::endl;
    }

    for(int i=0;i<3;i++){
        //for(auto &p: detected[i]) detected_times[i].push_back({p.GetAppearTime(),p.GetCreationProcess() == "Decay"});
        std::sort(detected_times[i].begin(), detected_times[i].end());
    }

    double gateL = 80*ns, gateNoL = 133*ns, delay = (gateNoL-gateL)/2;
    double dead_time = 174*ns; //TODO ask again why dead time
    for(auto up: detected_times[0]) {
        double time_up = up.first;
        for(auto down: detected_times[2]) {
            double time_down = down.first;
            if(found_down_exp && time_down-time_exp>dead_time){
                for(auto up: detected_times[0]) {
                    double time_up = up.first;
                    if(time_down+delay+gateL<time_up || time_down+delay>time_up+gateNoL){
                        time_exp = time_down-time_exp;
                        if(down.second == "Decay") {
                            count_exp_decay++;
                            found_exp_decay = true;
                        }else std::cerr << down.second << std::endl;
                        count_exp++;
                        found_exp = true;
                        break;
                    }
                }
            }
            if(found_exp) break;
            if(!found_down_exp && abs(time_down-time_up)<gateL){
                found_down_exp = true;
                time_exp = time_down;
            }
        }
        if(found_exp) break;
    }

    if (found_exp) {
        file_exp << time_exp/1000 << std::endl;
        if(found_exp_decay) file_exp_decay << time_exp/1000 << std::endl;
    }

}

void VetoAna::EndOfRunAction(const G4Run *aRun)
{
    G4cout << "### End Run " << aRun->GetRunID() << "." << G4endl;
    file_count << "decay: " << count_decay << "\nexp: " << count_exp << "\nexp_decay: " << count_exp_decay << std::endl;
    //for(auto p: processes) file_processes << p << std::endl;
}

void VetoAna::UserSteppingAction(const G4Step* aStep)
{
   /* //auto Edep = aStep->GetTotalEnergyDeposit();
    auto track = aStep->GetTrack();
    //auto Etot = track->GetTotalEnergy();
    auto ID = track->GetTrackID();
    //auto volName = track->GetVolume()->GetName();
    auto partName = track->GetDefinition()->GetParticleName();
    //auto vtx = track->GetVertexPosition();
    names[ID] = partName;*/
}
