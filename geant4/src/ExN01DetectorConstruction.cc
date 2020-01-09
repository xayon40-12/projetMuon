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
  :  experimentalHall_log(0), scintillatorA_log(0), scintillatorB_log(0),scintillatorC_log(0),wood1_log(0),
     experimentalHall_phys(0), scintillatorA1_phys(0),scintillatorB_phys(0),scintillatorC1_phys(0),wood1_1_phys(0),wood1_2_phys(0)
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

  G4double expHall_x = 1*m;
  G4double expHall_y = 1*m;
  G4double expHall_z = 1*m;
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
  
   //Scintillateur A

  G4double scintillatorA_x = 24*cm;
  G4double scintillatorA_y = 23.9*cm;
  G4double scintillatorA_z = 1.5*cm;

  G4Box* scintillatorA = new G4Box("scintillatorA",scintillatorA_x,
                                          scintillatorA_y,scintillatorA_z);
  
  scintillatorA_log = new G4LogicalVolume(scintillatorA,
                                   Scintillator,"scintillatorA_log",0,0,0);
  
  G4double scintillatorA1pos_x = 24.5*cm;
  G4double scintillatorA1pos_y = 0.0*cm;
  G4double scintillatorA1pos_z = 0.0*cm;

  G4double scintillatorA2pos_x = -24.5*cm;
  G4double scintillatorA2pos_y = 0.0*cm;
  G4double scintillatorA2pos_z = 0.0*cm;
  
  scintillatorA1_phys = new G4PVPlacement(0,
	      G4ThreeVector(scintillatorA1pos_x,scintillatorA1pos_y,scintillatorA1pos_z),
              scintillatorA_log,"Scintillator_A1",experimentalHall_log,false,0);

  G4String Scintillator1SDname = "SD1";
  B2TrackerSD* Scintillator1SD = new B2TrackerSD(Scintillator1SDname,
                                            "TrackerHitsCollection1");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator1SD);
  SetSensitiveDetector("scintillatorA_log", Scintillator1SD, true);

  //Scintillateur B

  G4double scintillatorB_x = 74.8*cm;
  G4double scintillatorB_y = 13.1*cm;
  G4double scintillatorB_z = 2.5*cm;
  
  G4Box* scintillatorB = new G4Box("scintillatorB",scintillatorB_x,
                                          scintillatorB_y,scintillatorB_z);
  
  scintillatorB_log = new G4LogicalVolume(scintillatorB,Scintillator,"scintillatorB_log",0,0,0);

  G4double scintillatorBpos_x = 0.0*cm;
  G4double scintillatorBpos_y = 0.0*cm;
  G4double scintillatorBpos_z = -20.5*cm;
  
  scintillatorB_phys = new G4PVPlacement(0,
	G4ThreeVector(scintillatorBpos_x,scintillatorBpos_y,scintillatorBpos_z),
              scintillatorB_log,"Scintillator_B",experimentalHall_log,false,0); 

  G4String Scintillator2SDname = "SD2";
  B2TrackerSD* Scintillator2SD = new B2TrackerSD(Scintillator2SDname ,
                                            "TrackerHitsCollection2");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator2SD);
  SetSensitiveDetector("scintillatorB_log", Scintillator2SD, true);


  //Scintillateur C

  G4double scintillatorC_x = 24*cm;
  G4double scintillatorC_y = 23.9*cm;
  G4double scintillatorC_z = 1.5*cm;
  
  G4Box* scintillatorC = new G4Box("scintillatorC",scintillatorC_x,
                                          scintillatorC_y,scintillatorC_z);
  
  scintillatorC_log = new G4LogicalVolume(scintillatorC,
                                   Scintillator,"scintillatorC_log",0,0,0);
  
  G4double scintillatorC1pos_x = 24.5*cm;
  G4double scintillatorC1pos_y = 0.0*cm;
  G4double scintillatorC1pos_z = -29.4*cm;
  scintillatorC1_phys = new G4PVPlacement(0,
	      G4ThreeVector(scintillatorC1pos_x,scintillatorC1pos_y,scintillatorC1pos_z),
              scintillatorC_log,"Scintillator_C",experimentalHall_log,false,0);

  G4String Scintillator3SDname = "SD3";
  B2TrackerSD* Scintillator3SD = new B2TrackerSD(Scintillator3SDname ,
                                            "TrackerHitsCollection3");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator3SD);
  SetSensitiveDetector("scintillatorC_log", Scintillator3SD, true);

  //-----------------------------------------------------------------------------------------
  
  // Dimensions bois
  G4double wood1_x = 1*cm;
  G4double wood1_y = 2*cm;
  G4double wood1_z = 10*cm;

  G4double wood2_x = 1*cm;//a definir
  G4double wood2_y = 2*cm;//a definir
  G4double wood2_z = 10*cm;//a definir

  G4double wood3_x = 1*cm;//a definir
  G4double wood3_y = 2*cm;//a definir
  G4double wood3_z = 10*cm;//a definir
  
  //Bois 1-1
  // G4Box* wood1 = new G4Box("wood1",wood1_x,wood1_y,wood1_z);
  //wood1_log = new G4LogicalVolume(wood1,Wood,"wood1_log",0,0,0);
  
  //  G4double wood1_1pos_x = scintillator1pos_x - scintillator1_x - wood1_x;
  //G4double wood1_1pos_y = scintillator1pos_y;
  //G4double wood1_1pos_z = scintillator1pos_z;
  //wood1_1_phys = new G4PVPlacement(0,G4ThreeVector(wood1_1pos_x,wood1_1pos_y,wood1_1pos_z),wood1_log,"Wood1_1",experimentalHall_log,false,0);

  //Bois 1-2
  //G4Box* wood1_2 = new G4Box("wood1_2",wood1_x,wood1_y,wood1_z);
  //wood1_2_log = new G4LogicalVolume(wood2,Wood,"wood2_log",0,0,0);
  
  //G4double wood2pos_x = scintillator1pos_x + scintillator1_x + wood1_x;
  //G4double wood2pos_y = scintillator1pos_y;
  //G4double wood2pos_z = scintillator1pos_z;
  //wood1_2_phys = new G4PVPlacement(0,G4ThreeVector(wood2pos_x,wood2pos_y,wood2pos_z),wood1_log,"Wood1_2",experimentalHall_log,false,0);

  //Bois 3
  //  G4double wood3_x = 37.4*cm;
  //  G4double wood3_y = 1.25*cm;
  //  G4double wood3_z = 6.55*cm;
  //  G4Box* wood3 = new G4Box("wood3",wood3_x,wood3_y,wood3_z);
  //  wood3_log = new G4LogicalVolume(wood3,Wood,"wood3_log",0,0,0);
  
  //  G4double wood3pos_x = 0.0*cm;
  //  G4double wood3pos_y = 7.0*cm;
  //  G4double wood3pos_z = 0.0*cm;
  //  wood3_phys = new G4PVPlacement(0,G4ThreeVector(wood3pos_x,wood3pos_y,wood3pos_z),wood3_log,"Wood_3",experimentalHall_log,false,0);
  
  //Bois 4
  //  G4double wood4_x = 37.4*cm;
  //  G4double wood4_y = 1.25*cm;
  //  G4double wood4_z = 6.55*cm;
  //  G4Box* wood4 = new G4Box("wood4",wood4_x,wood4_y,wood4_z);
  //  wood4_log = new G4LogicalVolume(wood4,Wood,"wood4_log",0,0,0);
  
  //  G4double wood4pos_x = 0.0*cm;
  //  G4double wood4pos_y = 7.0*cm;
  //  G4double wood4pos_z = 0.0*cm;
  //  wood4_phys = new G4PVPlacement(0,G4ThreeVector(wood4pos_x,wood4pos_y,wood4pos_z),wood4_log,"Wood_4",experimentalHall_log,false,0);
  
//--------- Visualization attributes -------------------------------

  G4VisAttributes* targetVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  experimentalHall_log->SetVisAttributes(targetVisAtt);  
  scintillatorA_log ->SetVisAttributes(targetVisAtt);
  scintillatorB_log ->SetVisAttributes(targetVisAtt);
  scintillatorC_log ->SetVisAttributes(targetVisAtt);
  //wood1_log ->SetVisAttributes(targetVisAtt);
  //  wood2_log ->SetVisAttributes(targetVisAtt);
  //wood3_log ->SetVisAttributes(targetVisAtt);

  return experimentalHall_phys;
}

