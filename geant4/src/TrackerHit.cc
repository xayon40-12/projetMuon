#include "TrackerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<B2TrackerHit>* B2TrackerHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerHit::B2TrackerHit()
 : G4VHit(),
   fTrackID(-1),
   fParentID(-1),
   fParentName("Unknown"),
   fTotalEnergy(-1),
   fProcessName("None"),
   fChamberNb(-1),
   fEdep(0.),
   fPos(G4ThreeVector()),
   partName("None")
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerHit::~B2TrackerHit() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B2TrackerHit::B2TrackerHit(const B2TrackerHit& right)
  : G4VHit()
{
  fTrackID   = right.fTrackID;
  fParentID   = right.fParentID;
  fParentName   = right.fParentName;
  fTotalEnergy = right.fTotalEnergy;
  fProcessName = right.fProcessName;
  fChamberNb = right.fChamberNb;
  fEdep      = right.fEdep;
  fPos       = right.fPos;
  partName   = right.partName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const B2TrackerHit& B2TrackerHit::operator=(const B2TrackerHit& right)
{
  fTrackID   = right.fTrackID;
  fParentID   = right.fParentID;
  fParentName   = right.fParentName;
  fTotalEnergy = right.fTotalEnergy;
  fProcessName = right.fProcessName;
  fChamberNb = right.fChamberNb;
  fEdep      = right.fEdep;
  fPos       = right.fPos;
  partName   = right.partName;

  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4int B2TrackerHit::operator==(const B2TrackerHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2TrackerHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B2TrackerHit::Print()
{
  G4cout
     << "    " << partName
     << "   \tID: " << fTrackID
     << "   \tparentID: " << fParentID
     << "   \tparentName: " << fParentName
     << "   \tcreation process: " << fProcessName
     << "   \tchamberNb: " << std::setw(2) << fChamberNb
     << "   \tEdep: " << std::setw(7) << G4BestUnit(fEdep,"Energy")
     << "   \ttotal energy: " << std::setw(7) << G4BestUnit(fTotalEnergy,"Energy")
     << "   \tPosition: " << std::setw(7) << G4BestUnit( fPos,"Length")
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
