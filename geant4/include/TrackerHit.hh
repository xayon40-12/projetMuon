#ifndef TrackerHit_h
#define TrackerHit_h

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

/// Tracker hit class
///
/// It defines data members to store the trackID, chamberNb, energy deposit,
/// and position of charged particles in a selected volume:
/// - fTrackID, fChamberNB, fEdep, fPos

class B2TrackerHit : public G4VHit
{
  public:
    B2TrackerHit();
    B2TrackerHit(const B2TrackerHit&);
    virtual ~B2TrackerHit();

    // operators
    const B2TrackerHit& operator=(const B2TrackerHit&);
    G4int operator==(const B2TrackerHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw();
    virtual void Print();

    // Set methods
    void SetTrackID         (G4int track)       { fTrackID = track; };
    void SetParentID        (G4int parent)      { fParentID = parent; };
    void SetParentName      (G4String name)     { if(name != "") fParentName = name; };
    void SetTotalEnergy     (G4double e)        { fTotalEnergy = e; };
    void SetCreationProcess (G4String process)  { fProcessName = process; };
    void SetChamberNb       (G4int chamb)       { fChamberNb = chamb; };
    void SetEdep            (G4double de)       { fEdep = de; };
    void SetPos             (G4ThreeVector xyz) { fPos = xyz; };
    void SetPartName        (G4String pName)    { partName = pName; };
    void SetGlobalTime      (G4double time)     { globTime = time; };
    void SetAppearTime      (G4double time)     { appearTime = time; disappearTime = time; };
    void SetDisappearTime   (G4double time)     { disappearTime = time; };


    // Get methods
    G4int GetTrackID() const            { return fTrackID; };
    G4int GetParentID() const           { return fParentID; };
    G4String GetParentName() const      { return fParentName; };
    G4double GetTotalEnergy() const     { return fTotalEnergy; };
    G4String GetCreationProcess() const { return fProcessName; };
    G4int GetChamberNb() const          { return fChamberNb; };
    G4double GetEdep() const            { return fEdep; };
    G4ThreeVector GetPos() const        { return fPos; };
    G4String GetPartName() const        { return partName; };
    G4double GetGlobalTime() const      { return globTime; };
    G4double GetAppearTime() const      { return appearTime; };
    G4double GetDisappearTime() const   { return disappearTime; };

  private:

      G4double      appearTime;
      G4int         fTrackID;
      G4int         fParentID;
      G4String      fParentName;
      G4double      fTotalEnergy;
      G4String      fProcessName;
      G4int         fChamberNb;
      G4double      fEdep;
      G4ThreeVector fPos;
      G4String      partName;
      G4double      globTime;
      G4double      disappearTime;
};

bool operator<(const B2TrackerHit & lhs, const B2TrackerHit & rhs);

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<B2TrackerHit> B2TrackerHitsCollection;

extern G4ThreadLocal G4Allocator<B2TrackerHit>* B2TrackerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* B2TrackerHit::operator new(size_t)
{
  if(!B2TrackerHitAllocator)
      B2TrackerHitAllocator = new G4Allocator<B2TrackerHit>;
  return (void *) B2TrackerHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void B2TrackerHit::operator delete(void *hit)
{
  B2TrackerHitAllocator->FreeSingle((B2TrackerHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
