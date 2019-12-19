#ifndef VetoAna_h
#define VetoAna_h 1

#include "G4UserEventAction.hh"
#include "G4UserRunAction.hh"
#include "G4UserSteppingAction.hh"
#include "globals.hh"

#include <unordered_map>

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
  
public:
  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;
  
  void BeginOfEventAction(const G4Event*) override;

  void EndOfEventAction(const G4Event*) override;
  void UserSteppingAction(const G4Step*) override;
 
public:
  G4double edeptot0;
  G4double edeptotH0;
  G4double edeptotH1;
  G4double LTot0;
  G4double LTot1;
  G4double ekin0;
  G4double  ekin1;
  G4int vol0;
  G4int vol1;
   G4double E0;
 G4double E1;
 G4double E2;
 G4double E3;

  G4double IDCurrent;
 G4int gPb, nPb, ePb,muPb,otherPb;
  G4double Edep_gPb, Edep_nPb, Edep_ePb, Edep_otherPb,Edep_muPb;
 
G4double totEPb;

 
private:
 G4int trackerCollID;
 
  G4int event;
  std::unordered_map<G4int, G4String> names;
};

#endif
