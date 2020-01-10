//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.A                             *
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
// $Id: ExN01DetectorConstruction.hh,v 1.6 2006/06/29 17:47:13 gunter Exp $
// GEANT4 tag $Name: geant4-08-03-patch-01 $
//

#ifndef ExN01DetectorConstruction_H
#define ExN01DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;

#include "G4VUserDetectorConstruction.hh"

class ExN01DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    ExN01DetectorConstruction();
    ~ExN01DetectorConstruction();

    G4VPhysicalVolume* Construct();

  private:
    
    // Logical volumes
    //
    G4LogicalVolume* experimentalHall_log;
    G4LogicalVolume* scintillatorA_log;
    G4LogicalVolume* scintillatorB_log;
    G4LogicalVolume* scintillatorC_log;
    G4LogicalVolume* woodinterieur_log;
    G4LogicalVolume* woodexterieur_log;
    G4LogicalVolume* alinterieur_log;
    G4LogicalVolume* alexterieur_log;
    G4LogicalVolume* woodinterieur2_log;
    G4LogicalVolume* woodexterieur2_log;
  
    // Physical volumes
    //
    G4VPhysicalVolume* experimentalHall_phys;
    G4VPhysicalVolume* scintillatorA1_phys;
    G4VPhysicalVolume* scintillatorB_phys;
    G4VPhysicalVolume* scintillatorC1_phys;
    G4VPhysicalVolume* woodinterieur_phys;
    G4VPhysicalVolume* woodexterieur_phys;
    G4VPhysicalVolume* alinterieur_phys;
    G4VPhysicalVolume* alexterieur_phys;
    G4VPhysicalVolume* woodinterieur2_phys;
    G4VPhysicalVolume* woodexterieur2_phys;
  
};

#endif

