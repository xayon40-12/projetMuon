#ifndef VetoAna_h
#define VetoAna_h 1

#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <unordered_map>
#include <fstream>
#include <unordered_set>

class G4VPhysicalVolume;
class G4Event;
class G4Run;
class G4Track;
class G4Step;
class G4HCofThisEvent;


class VetoAna : public G4UserSteppingAction, public G4UserEventAction, public G4UserRunAction {
    public:
        VetoAna();
        virtual ~VetoAna();

        void BeginOfRunAction(const G4Run*) override;
        void EndOfRunAction(const G4Run*) override;

        void BeginOfEventAction(const G4Event*) override;

        void EndOfEventAction(const G4Event*) override;
        void UserSteppingAction(const G4Step*) override;

    private:
        G4int trackerCollID;

        G4int event;
        std::unordered_map<G4int, G4String> names;
        std::ofstream file_decay, file_exp, file_count;
        std::unordered_set<std::string> processes;
        long count_decay, count_exp, count_exp_decay;
};

#endif
