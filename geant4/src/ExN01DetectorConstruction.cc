//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN01DetectorConstruction.cc,v 1.9 2006/06/29 17:47:19 gunter Exp $
// GEANT4 tag $Name: geant4-08-03-patch-01 $
//

#include "ExN01DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"
#include "G4NistManager.hh"
//#include "G4ENSDFSTATEDATA.hh"

ExN01DetectorConstruction::ExN01DetectorConstruction()
 :  experimentalHall_log(0), target_log(0), detector_log(0),
    experimentalHall_phys(0), target_phys(0), detector_phys(0), detector2_phys(0)
{;}

ExN01DetectorConstruction::~ExN01DetectorConstruction()
{
}

G4VPhysicalVolume* ExN01DetectorConstruction::Construct()
{

  //------------------------------------------------------ materials

  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
  G4int nel;
  G4NistManager* man = G4NistManager::Instance();


  //Air
  G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);
   
  G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
  Air->AddElement(N, 70*perCent);
  Air->AddElement(O, 30*perCent);
  
  //csi
  G4Material* csi = man->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  
  G4Element* Pb = new G4Element("Lead"  , "Pb", z=82., a= 207.20*g/mole);
  G4Material* pb = new G4Material("Lead", density= 11.35*g/cm3, nel=1);
  pb->AddElement(Pb, 100*perCent);
  

  //------------------------------------------------------ volumes

  //------------------------------ experimental hall (world volume)
  //------------------------------ beam line along x axis

  G4Box* experimentalHall_box = new G4Box("expHall_box",10.0*cm,10.0*cm,20.0*cm);
  experimentalHall_log = new G4LogicalVolume(experimentalHall_box, Air, "expHall_log", 0,0,0);
  experimentalHall_phys = new G4PVPlacement(0, G4ThreeVector(), experimentalHall_log, "expHall", 0, false, 0);


  //------------------------------ a target block

  G4double tub_hz = (40.7/2)*mm;
  G4Tubs* target_tub = new G4Tubs("target_tub",0.*mm,13.*mm, tub_hz,0.*deg,360.*deg);
  target_log = new G4LogicalVolume(target_tub, csi, "target_log", 0,0,0);
  target_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,tub_hz), target_log, "csi", experimentalHall_log, false, 0);


  //------------------------------ a shielding block

  tub_hz = (105/2)*mm;
  G4Tubs* shielding_tub = new G4Tubs("shielding_tub",3.*mm,24.*mm, tub_hz,0.*deg,360.*deg);
  shielding_log = new G4LogicalVolume(shielding_tub, pb, "shielding_log", 0,0,0);
  shielding_phys = new G4PVPlacement(0, G4ThreeVector(0.,0.,-tub_hz), shielding_log, "pb", experimentalHall_log, false, 0);

//--------- Visualization attributes -------------------------------

  G4VisAttributes* targetVisAtt= new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  experimentalHall_log->SetVisAttributes(targetVisAtt);  
  target_log ->SetVisAttributes(targetVisAtt);

  return experimentalHall_phys;
}

void ExN01DetectorConstruction::ConstructSDandField() {
  
  // Sensitive detectors

  G4String trackerChamberSDname = "ExN01/TrackerChamberSD";
  B2TrackerSD* aTrackerSD = new B2TrackerSD(trackerChamberSDname,
                                            "trackerCollection");
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  // Setting aTrackerSD to all logical volumes with the same name 
  // of "Chamber_LV".
  
  //SetSensitiveDetector("detector_log", aTrackerSD, true);
  SetSensitiveDetector("target_log", aTrackerSD, true);
}
