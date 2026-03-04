#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
public:
    ActionInitialization() : G4VUserActionInitialization() {}
    virtual ~ActionInitialization() {}
    virtual void Build() const override;
    virtual void BuildForMaster() const override;
};

#endif