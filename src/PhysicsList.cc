#include "PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

PhysicsList::PhysicsList() : G4VUserPhysicsList() {}
PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructParticle()
{
    // all standard particles
    G4DecayPhysics decay;
    decay.ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    AddTransportation();
    G4EmStandardPhysics emPhysics;
    emPhysics.ConstructProcess();
}

void PhysicsList::SetCuts()
{
    SetCutsWithDefault();
}