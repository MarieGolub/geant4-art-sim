#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

SensitiveDetector::SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name) {}
SensitiveDetector::~SensitiveDetector() {}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    // Only record entrance point
    if(step->GetPreStepPoint()->GetStepStatus() != fGeomBoundary) return false;

    auto pos = step->GetPreStepPoint()->GetPosition();
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0, pos.x()/mm);
    analysisManager->FillNtupleDColumn(1, pos.y()/mm);
    analysisManager->AddNtupleRow();

    return true;
}