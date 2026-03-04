#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fParticleGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    auto particleTable = G4ParticleTable::GetParticleTable();

    // Randomly select particle (pi+, proton, e+)
    int choice = G4RandFlat::shootInt(3);
    G4String name;
    if(choice==0) name="pi+";
    else if(choice==1) name="proton";
    else name="e+";

    auto particle = particleTable->FindParticle(name);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->SetParticleEnergy(4*GeV);
    fParticleGun->SetParticlePosition(G4ThreeVector(0,0,-30*cm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    fParticleGun->GeneratePrimaryVertex(event);
}