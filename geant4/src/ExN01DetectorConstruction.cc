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
#include "TrackerSD.hh"
#include "TrackerHit.hh"
#include "G4SDManager.hh"
//#include "G4ENSDFSTATEDATA.hh"
#include "G4NistManager.hh"

ExN01DetectorConstruction::ExN01DetectorConstruction()
 :  experimentalHall_log(0), scintillator1_log(0), scintillator2_log(0),scintillator3_log(0),
    experimentalHall_phys(0), scintillator1_phys(0),scintillator2_phys(0),scintillator3_phys(0)
{;}

ExN01DetectorConstruction::~ExN01DetectorConstruction()
{
}

G4VPhysicalVolume* ExN01DetectorConstruction::Construct()
{

  //------------------------------------------------------ materials
  // Elements
  G4double a;  // atomic mass
  G4double z;  // atomic number
  G4double density;
  G4int nel;

  G4Element* H = new G4Element("Hydrogen"  , "H", z=1., a= 1.00*g/mole);
  G4Element* C = new G4Element("Carbon"  , "C", z=6., a= 12.01*g/mole);
  G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);
  G4Element* Na = new G4Element("Sodium"  , "Na", z=11., a= 22.99*g/mole);
  G4Element* Mg = new G4Element("Magnesium"  , "Mg", z=12., a= 24.31*g/mole);
  G4Element* Al = new G4Element("Aluminium"  , "Al", z=13., a= 26.98*g/mole);
  G4Element* K = new G4Element("Potasium"  , "K", z=19., a= 39.10*g/mole);
  G4Element* Ca = new G4Element("Calcium"  , "Ca", z=20., a= 40.08*g/mole);
  G4Element* Mn = new G4Element("Manganese"  , "Mn", z=25., a= 54.94*g/mole);
  G4Element* Fe = new G4Element("Iron"  , "Fe", z=26., a= 55.85*g/mole);

  // Aluminium
  G4Material* Al = new G4Material("Aluminium", density= 2.7*g/cm3,nel=1);
  Al->AddElement(Al, 100*perCent);

  //Air
  G4Material* Air = new G4Material("Air", density= 0.00001*mg/cm3, nel=2);
  Air->AddElement(N, 70*perCent);
  Air->AddElement(O, 30*perCent);
  
  // Scintillateur
  G4Material* Scintillator = new G4Material("Scintillator", density= 0.8*g/cm3, nel=2);
  Scintillator->AddElement(C, 47*perCent);
  Scintillator->AddElement(H, 53*perCent);
  
  G4Material* Wood = new G4Material("Wood", density= 0.51*g/cm3, nel=10);
  Wood->AddElement(C, 50*perCent);
  Wood->AddElement(O, 42*perCent);
  Wood->AddElement(H, 6*perCent);
  Wood->AddElement(N, 1*perCent);
  Wood->AddElement(Ca, 0.2*perCent);
  Wood->AddElement(K, 0.2*perCent);
  Wood->AddElement(Na, 0.2*perCent);
  Wood->AddElement(Mg, 0.2*perCent);
  Wood->AddElement(Mn, 0.1*perCent);
  Wood->AddElement(Fe, 0.1*perCent);


  G4NistManager* man = G4NistManager::Instance();
  G4Material* csiMaterial = man->FindOrBuildMaterial("G4_CESIUM_IODIDE");

  //------------------------------------------------------ volumes

  //------------------------------ experimental hall (world volume)
  //------------------------------ beam line along x axis

  G4double expHall_x = 5*m;
  G4double expHall_y = 5*m;
  G4double expHall_z = 5*m;
  G4Box* experimentalHall_box
    = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);
  experimentalHall_log = new G4LogicalVolume(experimentalHall_box,
                                             Air,"expHall_log",0,0,0);
  experimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),
                                      experimentalHall_log,"expHall",0,false,0);

  //------------------------------ Lead shielding
  //  G4double innerRadiusOfTheTubeshield = 3/2.*mm;
  //  G4double outerRadiusOfTheTubeshield = 24/2.*mm;
  //  G4double hightOfTheTubeshield = 105/2.*mm;
  //  G4double startAngleOfTheTubeshield = 0.*deg;
  //  G4double spanningAngleOfTheTubeshield = 360.*deg;
  //  G4Tubs* Pbshield
  //    = new G4Tubs("Pbshield",
  //  		 innerRadiusOfTheTubeshield,
  //  		 outerRadiusOfTheTubeshield,
  //  		 hightOfTheTubeshield,
  //  		 startAngleOfTheTubeshield,
  //  		 spanningAngleOfTheTubeshield);
  
  //  Pbshield_log = new G4LogicalVolume(Pbshield,
  //  				    Pb,"Pbshield_log",0,0,0);
  
  //  G4double shieldPos_x = 0.0*mm;
  //  G4double shieldPos_y = 0.0*mm;
  //  G4double shieldPos_z = -72.85*mm;
  //  Pbshield_phys = new G4PVPlacement(0,
  //  				   G4ThreeVector(shieldPos_x,shieldPos_y,shieldPos_z),
  //  				   Pbshield_log,"BlindagePb",experimentalHall_log,false,0);
  //------------------------------ a target block

   //Scintillateur1

  G4double scintillator1_x = 0.5*m;
  G4double scintillator1_y = 0.5*m;
  G4double scintillator1_z = 0.5*m;
  G4Box* scintillator1 = new G4Box("scintillator1",scintillator1_x,
                                          scintillator1_y,scintillator1_z);
  
  scintillator1_log = new G4LogicalVolume(scintillator1,
                                   Scintillator,"scintillator1_log",0,0,0);
  G4double scintillator1pos_x = 0.0*m;
  G4double scintillator1pos_y = 0.0*m;
  G4double scintillator1pos_z = 0.0*m;
  scintillator1_phys = new G4PVPlacement(0,
	      G4ThreeVector(scintillator1pos_x,scintillator1pos_y,scintillator1pos_z),
              scintillator1_log,"Scintillator_1",experimentalHall_log,false,0);

  G4String Scintillator1SDname = "SD1";
  B2TrackerSD* Scintillator1SD = new B2TrackerSD(Scintillator1SDname,
                                            "TrackerHitsCollection1");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator1SD);
  SetSensitiveDetector("scintillator1_log", Scintillator1SD, true);

  //Scintillateur 2

  G4double scintillator2_x = 0.5*m;
  G4double scintillator2_y = 0.5*m;
  G4double scintillator2_z = 0.5*m;
  G4Box* scintillator2 = new G4Box("scintillator2",scintillator2_x,
                                          scintillator2_y,scintillator2_z);
  
  scintillator2_log = new G4LogicalVolume(scintillator2,Scintillator,"scintillator2_log",0,0,0);

  G4double scintillator2pos_x = 2.0*m;
  G4double scintillator2pos_y = 0.0*m;
  G4double scintillator2pos_z = 0.0*m;
  
  scintillator2_phys = new G4PVPlacement(0,
	G4ThreeVector(scintillator2pos_x,scintillator2pos_y,scintillator2pos_z),
              scintillator2_log,"Scintillator_2",experimentalHall_log,false,0); 

  G4String Scintillator2SDname = "SD2";
  B2TrackerSD* Scintillator2SD = new B2TrackerSD(Scintillator2SDname ,
                                            "TrackerHitsCollection2");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator2SD);
  SetSensitiveDetector("scintillator2_log", Scintillator2SD, true);


  //Scintillateur 3

  G4double scintillator3_x = 0.5*m;
  G4double scintillator3_y = 0.5*m;
  G4double scintillator3_z = 0.5*m;
  G4Box* scintillator3 = new G4Box("scintillator3",scintillator3_x,
                                          scintillator3_y,scintillator3_z);
  
  scintillator3_log = new G4LogicalVolume(scintillator3,
                                   Scintillator,"scintillator3_log",0,0,0);
  G4double scintillator3pos_x = 4.0*m;
  G4double scintillator3pos_y = 0.0*m;
  G4double scintillator3pos_z = 0.0*m;
  scintillator3_phys = new G4PVPlacement(0,
	      G4ThreeVector(scintillator3pos_x,scintillator3pos_y,scintillator3pos_z),
              scintillator3_log,"Scintillator_3",experimentalHall_log,false,0);

  G4String Scintillator3SDname = "SD3";
  B2TrackerSD* Scintillator3SD = new B2TrackerSD(Scintillator3SDname ,
                                            "TrackerHitsCollection3");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator3SD);
  SetSensitiveDetector("scintillator3_log", Scintillator3SD, true);
 
  
//--------- Visualization attributes -------------------------------

  G4VisAttributes* targetVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  experimentalHall_log->SetVisAttributes(targetVisAtt);  
  scintillator1_log ->SetVisAttributes(targetVisAtt);
  scintillator2_log ->SetVisAttributes(targetVisAtt);
  scintillator3_log ->SetVisAttributes(targetVisAtt);

  return experimentalHall_phys;
}

