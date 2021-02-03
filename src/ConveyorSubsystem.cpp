#include "ConveyorSubsystem.h"
#include <CORERobotLib.h>

ConveyorSubsystem::ConveyorSubsystem() :    m_conveyorMotor(CONVEYOR_PORT),
                                            m_conveyorForwardSpeed("Conveyor Forward Speed", 0.2),
                                            m_conveyorReverseSpeed("Conveyor Reverse Speed", -0.2) {

}

void ConveyorSubsystem::robotInit() {
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::LEFT_TRIGGER);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::LEFT_BUTTON);
}

void ConveyorSubsystem::teleopInit() {
    m_conveyorMotor.Set(ControlMode::PercentOutput, 0);
}

void ConveyorSubsystem::teleop() {
    if (operatorJoystick->GetButton(COREJoystick::JoystickButton::LEFT_TRIGGER)) {
        setMotor(m_conveyorForwardSpeed.Get());
    } else if (operatorJoystick->GetButton(COREJoystick::JoystickButton::LEFT_BUTTON)) {
        setMotor(m_conveyorReverseSpeed.Get());
    } else {
        setMotor(0);
    }
}

void ConveyorSubsystem::setMotor(double speed) {
    m_conveyorMotor.Set(ControlMode::PercentOutput, speed);
}
