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
  :  experimentalHall_log(0), scintillatorA_log(0), scintillatorB_log(0),scintillatorC_log(0),woodinterieur_log(0),woodexterieur_log(0),alexterieur_log(0),alinterieur_log(0),woodinterieur2_log(0),woodexterieur2_log(0),
     experimentalHall_phys(0), scintillatorA1_phys(0),scintillatorB_phys(0),scintillatorC1_phys(0),woodinterieur_phys(0),woodexterieur_phys(0),alexterieur_phys(0),alinterieur_phys(0),woodinterieur2_phys(0),woodexterieur2_phys(0)
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
  //G4Element* Al = new G4Element("Aluminium"  , "Al", z=13., a= 26.98*g/mole);
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

  //Aluminium
  G4Material* Al = new G4Material("Aluminium", z=13., a= 26.98*g/mole,density= 2.6989*g/cm3);

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

 
  //Bois exterieur

  // Dimensions bois exterieur
  G4double woodexterieur_x = 50.3*cm;
  G4double woodexterieur_y = 32.8*cm;
  G4double woodexterieur_z = 5.9*cm;
  
  G4Box* woodexterieur = new G4Box("woodexterieur",woodexterieur_x,woodexterieur_y,woodexterieur_z);
  woodexterieur_log = new G4LogicalVolume(woodexterieur,Wood,"woodexterieur_log",0,0,0);

  // Position bois exterieur
  G4double woodexterieur_pos_x = 0*cm;
  G4double woodexterieur_pos_y = 0*cm;
  G4double woodexterieur_pos_z = 0*cm;
  woodexterieur_phys = new G4PVPlacement(0,G4ThreeVector(woodexterieur_pos_x,woodexterieur_pos_y,woodexterieur_pos_z),woodexterieur_log,"Woodexterieur",experimentalHall_log,false,0);
  
  //Bois interieur (contient de l'air)
  
  // Dimensions bois interieur
  G4double woodinterieur_x = 48.5*cm;
  G4double woodinterieur_y = 31*cm;
  G4double woodinterieur_z = 4.1*cm;
  
  G4Box* woodinterieur = new G4Box("woodinterieur",woodinterieur_x,woodinterieur_y,woodinterieur_z);
  woodinterieur_log = new G4LogicalVolume(woodinterieur,Air,"woodinterieur_log",0,0,0);

  // Position bois interieur (par rapport au volume mere bois exterieur)
  // Les 2 volumes sont centrés au même endroit
  G4double woodinterieur_pos_x = 0*cm;
  G4double woodinterieur_pos_y = 0*cm;
  G4double woodinterieur_pos_z = 0*cm;
  
  woodinterieur_phys = new G4PVPlacement(0,G4ThreeVector(woodinterieur_pos_x,woodinterieur_pos_y,woodinterieur_pos_z),woodinterieur_log,"Woodinterieur",woodexterieur_log,false,0);
  
   //Scintillateur A

  G4double scintillatorA_x = 24*cm;
  G4double scintillatorA_y = 23.9*cm;
  G4double scintillatorA_z = 1.5*cm;

  G4Box* scintillatorA = new G4Box("scintillatorA",scintillatorA_x,
                                          scintillatorA_y,scintillatorA_z);
  
  scintillatorA_log = new G4LogicalVolume(scintillatorA,
                                   Scintillator,"scintillatorA_log",0,0,0);
  
  G4double scintillatorA1pos_x = 24.5*cm;
  G4double scintillatorA1pos_y = -6.9*cm;
  G4double scintillatorA1pos_z = 0.0*cm;

  G4double scintillatorA2pos_x = -24.5*cm;
  G4double scintillatorA2pos_y = -6.9*cm;
  G4double scintillatorA2pos_z = 0.0*cm;
  
  scintillatorA1_phys = new G4PVPlacement(0,
	      G4ThreeVector(scintillatorA1pos_x,scintillatorA1pos_y,scintillatorA1pos_z),
              scintillatorA_log,"Scintillator_A1",woodinterieur_log,false,0);

  scintillatorA1_phys = new G4PVPlacement(0,
	      G4ThreeVector(scintillatorA2pos_x,scintillatorA2pos_y,scintillatorA2pos_z),
              scintillatorA_log,"Scintillator_A1",woodinterieur_log,false,1);

  G4String Scintillator1SDname = "SD1";
  B2TrackerSD* Scintillator1SD = new B2TrackerSD(Scintillator1SDname,
                                            "TrackerHitsCollection1");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator1SD);
  SetSensitiveDetector("scintillatorA_log", Scintillator1SD, true);

  // Aluminium exterieur

   // Dimensions aluminium exterieur
  G4double alexterieur_x = 75.5*cm;
  G4double alexterieur_y = 13.6*cm;
  G4double alexterieur_z = 7.9*cm;
  
  G4Box* alexterieur = new G4Box("alexterieur",alexterieur_x,alexterieur_y,alexterieur_z);
  alexterieur_log = new G4LogicalVolume(alexterieur,Al,"alexterieur_log",0,0,0);

  // Position aluminium exterieur
  G4double alexterieur_pos_x = 0*cm;
  G4double alexterieur_pos_y = -6.9*cm;
  G4double alexterieur_pos_z = -15.6*cm;
  alexterieur_phys = new G4PVPlacement(0,G4ThreeVector(alexterieur_pos_x,alexterieur_pos_y,alexterieur_pos_z),alexterieur_log,"alexterieur",experimentalHall_log,false,0);
  
  // Metal interieur (contient de l'air)
  
  // Dimensions aluminium interieur
  G4double alinterieur_x = 75*cm;
  G4double alinterieur_y = 13.1*cm;
  G4double alinterieur_z = 7.4*cm;
  
  G4Box* alinterieur = new G4Box("alinterieur",alinterieur_x,alinterieur_y,alinterieur_z);
  alinterieur_log = new G4LogicalVolume(alinterieur,Air,"alinterieur_log",0,0,0);

  // Position aluminium interieur (par rapport au volume mere aluminium exterieur)
  // Les 2 volumes sont centrés au même endroit
  G4double alinterieur_pos_x = 0*cm;
  G4double alinterieur_pos_y = 0*cm;
  G4double alinterieur_pos_z = 0*cm;
  
  alinterieur_phys = new G4PVPlacement(0,G4ThreeVector(alinterieur_pos_x,alinterieur_pos_y,alinterieur_pos_z),alinterieur_log,"alinterieur",alexterieur_log,false,0);
  
  //Scintillateur B

  G4double scintillatorB_x = 74.8*cm;
  G4double scintillatorB_y = 13.1*cm;
  G4double scintillatorB_z = 2.5*cm;
  
  G4Box* scintillatorB = new G4Box("scintillatorB",scintillatorB_x,
                                          scintillatorB_y,scintillatorB_z);
  
  scintillatorB_log = new G4LogicalVolume(scintillatorB,Scintillator,"scintillatorB_log",0,0,0);

  G4double scintillatorBpos_x = 0.0*cm;
  G4double scintillatorBpos_y = 0.0*cm;
  G4double scintillatorBpos_z = -4.9*cm;
  
  scintillatorB_phys = new G4PVPlacement(0,
	G4ThreeVector(scintillatorBpos_x,scintillatorBpos_y,scintillatorBpos_z),
              scintillatorB_log,"Scintillator_B",alinterieur_log,false,0); 

  G4String Scintillator2SDname = "SD2";
  B2TrackerSD* Scintillator2SD = new B2TrackerSD(Scintillator2SDname ,
                                            "TrackerHitsCollection2");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator2SD);
  SetSensitiveDetector("scintillatorB_log", Scintillator2SD, true);

  // --------------------------------------------------------------------------------------------------------------------------------------------------

  //Bois exterieur 2

  // Dimensions bois exterieur 2
  G4double woodexterieur2_x = 50.3*cm;
  G4double woodexterieur2_y = 32.8*cm;
  G4double woodexterieur2_z = 5.9*cm;
  
  G4Box* woodexterieur2 = new G4Box("woodexterieur2",woodexterieur2_x,woodexterieur2_y,woodexterieur2_z);
  woodexterieur2_log = new G4LogicalVolume(woodexterieur2,Wood,"woodexterieur2_log",0,0,0);

  // Position bois exterieur 2
  G4double woodexterieur2_pos_x = 0*cm;
  G4double woodexterieur2_pos_y = 0*cm;
  G4double woodexterieur2_pos_z = -29.4*cm;
  woodexterieur2_phys = new G4PVPlacement(0,G4ThreeVector(woodexterieur2_pos_x,woodexterieur2_pos_y,woodexterieur2_pos_z),woodexterieur2_log,"Woodexterieur2",experimentalHall_log,false,0);
  
  //Bois interieur 2 (contient de l'air)
  
  // Dimensions bois interieur
  G4double woodinterieur2_x = 48.5*cm;
  G4double woodinterieur2_y = 31*cm;
  G4double woodinterieur2_z = 4.1*cm;
  
  G4Box* woodinterieur2 = new G4Box("woodinterieur2",woodinterieur2_x,woodinterieur2_y,woodinterieur2_z);
  woodinterieur2_log = new G4LogicalVolume(woodinterieur2,Air,"woodinterieur2_log",0,0,0);

  // Position bois interieur 2 (par rapport au volume mere bois exterieur)
  // Les 2 volumes sont centrés au même endroit
  G4double woodinterieur2_pos_x = 0*cm;
  G4double woodinterieur2_pos_y = 0*cm;
  G4double woodinterieur2_pos_z = 0*cm;
  
  woodinterieur2_phys = new G4PVPlacement(0,G4ThreeVector(woodinterieur2_pos_x,woodinterieur2_pos_y,woodinterieur2_pos_z),woodinterieur2_log,"Woodinterieur2",woodexterieur2_log,false,0);
  
  //Scintillateur C
  
  G4double scintillatorC_x = 24*cm;
  G4double scintillatorC_y = 23.9*cm;
  G4double scintillatorC_z = 1.5*cm;
  
  G4Box* scintillatorC = new G4Box("scintillatorC",scintillatorC_x,
                                          scintillatorC_y,scintillatorC_z);
  
  scintillatorC_log = new G4LogicalVolume(scintillatorC,
                                   Scintillator,"scintillatorC_log",0,0,0);
  
  G4double scintillatorC1pos_x = 24.5*cm;
  G4double scintillatorC1pos_y = -6.9*cm;
  G4double scintillatorC1pos_z = 0*cm;

  G4double scintillatorC2pos_x = -24.5*cm;
  G4double scintillatorC2pos_y = -6.9*cm;
  G4double scintillatorC2pos_z = 0*cm;
  
  scintillatorC1_phys = new G4PVPlacement(0,
	      G4ThreeVector(scintillatorC1pos_x,scintillatorC1pos_y,scintillatorC1pos_z),
              scintillatorC_log,"Scintillator_C",woodinterieur2_log,false,0);

  scintillatorC1_phys = new G4PVPlacement(0,
	      G4ThreeVector(scintillatorC2pos_x,scintillatorC2pos_y,scintillatorC2pos_z),
              scintillatorC_log,"Scintillator_C",woodinterieur2_log,false,1);

  G4String Scintillator3SDname = "SD3";
  B2TrackerSD* Scintillator3SD = new B2TrackerSD(Scintillator3SDname ,
                                            "TrackerHitsCollection3");
  G4SDManager::GetSDMpointer()->AddNewDetector(Scintillator3SD);
  SetSensitiveDetector("scintillatorC_log", Scintillator3SD, true);
  
  //-----------------------------------------------------------------------------------------
  

  
//--------- Visualization attributes -------------------------------

  G4VisAttributes* targetVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  experimentalHall_log->SetVisAttributes(targetVisAtt);  
  scintillatorA_log ->SetVisAttributes(targetVisAtt);
  scintillatorB_log ->SetVisAttributes(targetVisAtt);
  scintillatorC_log ->SetVisAttributes(targetVisAtt);
  woodinterieur_log ->SetVisAttributes(targetVisAtt);
  woodexterieur_log ->SetVisAttributes(targetVisAtt);
  alinterieur_log ->SetVisAttributes(targetVisAtt);
  alexterieur_log ->SetVisAttributes(targetVisAtt);
  woodinterieur2_log ->SetVisAttributes(targetVisAtt);
  woodexterieur2_log ->SetVisAttributes(targetVisAtt);
  
  return experimentalHall_phys;
}

