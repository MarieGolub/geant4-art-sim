#include "ActionInitialization.hh"
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "SensitiveDetector.hh"

void ActionInitialization::Build() const
{
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new RunAction());
}

void ActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction());
}