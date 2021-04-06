#include "ConveyorAction.h"
#include "Robot.h"

ConveyorAction::ConveyorAction(conveyorAction requestedConveyorAction) {
    m_conveyorAction = requestedConveyorAction;

}

void ConveyorAction::ActionInit() {
    m_conveyorForwardSpeed = Robot::GetInstance()->conveyorSubsystem.conveyorForwardSpeed.Get();
    m_conveyorReverseSpeed = Robot::GetInstance()->conveyorSubsystem.conveyorReverseSpeed.Get();
}

CORE::COREAutonAction::actionStatus ConveyorAction::Action() {
    switch(m_conveyorAction)
    {
        case CONVEYOR_FORWARD:
            Robot::GetInstance()->conveyorSubsystem.setMotor(m_conveyorForwardSpeed);
            break;
        case CONVEYOR_BACKWARD:
            Robot::GetInstance()->conveyorSubsystem.setMotor(m_conveyorReverseSpeed);
            break;
        case CONVEYOR_OFF:
            Robot::GetInstance()->conveyorSubsystem.setMotor(0);
            break;
    }
    return COREAutonAction::actionStatus::END;
}

void ConveyorAction::ActionEnd() {
    
}