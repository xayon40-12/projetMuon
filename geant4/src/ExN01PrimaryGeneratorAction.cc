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
// $Id: ExN01PrimaryGeneratorAction.cc,v 1.6 2006/06/29 17:47:23 gunter Exp $
// GEANT4 tag $Name: geant4-08-03-patch-01 $
//

#include "ExN01PrimaryGeneratorAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "Randomize.hh"
  

// ******************** ExN01PrimaryGeneratorAction ********************

ExN01PrimaryGeneratorAction::ExN01PrimaryGeneratorAction(): gun(1) {
    gun.SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("gamma"));
    gun.SetParticlePosition(G4ThreeVector(0.,0.,-44*mm));
}

ExN01PrimaryGeneratorAction::~ExN01PrimaryGeneratorAction() {}

void ExN01PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4double phi = G4UniformRand()*2*M_PI, theta = acos(G4UniformRand()*2.-1.);
    gun.SetParticleEnergy(1.275*MeV);
    gun.SetParticleMomentumDirection(G4ThreeVector(cos(phi)*sin(theta),cos(theta),sin(phi)*sin(theta)));
    gun.GeneratePrimaryVertex(anEvent);
    
    phi = G4UniformRand()*2*M_PI; theta = acos(G4UniformRand()*2.-1.);
    gun.SetParticleEnergy(0.511*MeV);
    gun.SetParticleMomentumDirection(G4ThreeVector(cos(phi)*sin(theta),cos(theta),sin(phi)*sin(theta)));
    gun.GeneratePrimaryVertex(anEvent);
    gun.SetParticleMomentumDirection(-G4ThreeVector(cos(phi)*sin(theta),cos(theta),sin(phi)*sin(theta)));
    gun.GeneratePrimaryVertex(anEvent);
}


