#pragma once

#include <CORERobotLib.h>
#include "ConveyorSubsystem.h"

using namespace CORE;

enum conveyorAction {
    CONVEYOR_FORWARD,
    CONVEYOR_BACKWARD,
    CONVEYOR_OFF
};

class ConveyorAction : public COREAutonAction {
public:
    ConveyorAction(conveyorAction requestedConveyorAction);
    void ActionInit() override;
    CORE::COREAutonAction::actionStatus Action() override;
    void ActionEnd() override;
private:
    conveyorAction m_conveyorAction;
    double m_conveyorForwardSpeed, m_conveyorReverseSpeed;
};
