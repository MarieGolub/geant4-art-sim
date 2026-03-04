#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() : logicDWC1(nullptr), logicDWC2(nullptr) {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();

    // World
    auto worldSize = 1.0*m;
    auto solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
    auto logicWorld = new G4LogicalVolume(solidWorld, nist->FindOrBuildMaterial("G4_AIR"), "World");
    auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0);

    // Material block in the middle
    auto block = new G4Box("Block", 5*cm, 5*cm, 2*cm);
    auto logicBlock = new G4LogicalVolume(block, nist->FindOrBuildMaterial("G4_Cu"), "Block");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,0), logicBlock, "Block", logicWorld, false, 0);

    // DWC1
    auto dwcSize = 10*cm;
    auto dwcThickness = 1*mm;
    auto solidDWC = new G4Box("DWC", dwcSize, dwcSize, dwcThickness);
    logicDWC1 = new G4LogicalVolume(solidDWC, nist->FindOrBuildMaterial("G4_Galactic"), "DWC1");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,-10*cm), logicDWC1, "DWC1", logicWorld, false, 0);

    // DWC2
    logicDWC2 = new G4LogicalVolume(solidDWC, nist->FindOrBuildMaterial("G4_Galactic"), "DWC2");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,10*cm), logicDWC2, "DWC2", logicWorld, false, 0);

    // Scintillators
    auto scintSize = 10*cm;
    auto scintThickness = 1*cm;
    auto solidScint = new G4Box("Scint", scintSize, scintSize, scintThickness);
    auto logicScint = new G4LogicalVolume(solidScint, nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "Scintillator1");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,-15*cm), logicScint, "Scintillator1", logicWorld, false, 0);
    logicScint = new G4LogicalVolume(solidScint, nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"), "Scintillator2");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,15*cm), logicScint, "Scintillator2", logicWorld, false, 0);

    return physWorld;
}

void DetectorConstruction::ConstructSDandField()
{
    auto sdManager = G4SDManager::GetSDMpointer();

    auto dwcSD = new SensitiveDetector("DWCSD");
    sdManager->AddNewDetector(dwcSD);

    logicDWC1->SetSensitiveDetector(dwcSD);
    logicDWC2->SetSensitiveDetector(dwcSD);
}