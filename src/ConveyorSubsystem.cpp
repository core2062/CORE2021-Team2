#include "ConveyorSubsystem.h"
#include <CORERobotLib.h>

ConveyorSubsystem::ConveyorSubsystem() : m_conveyorMotor(CONVEYOR_PORT),
                                         m_conveyorForwardSpeed("Conveyor Forward Speed", 0.2), 
                                         //TODO: Change these values to actual numbers based on testing
                                         m_conveyorReverseSpeed("Conveyor Reverse Speed", -0.2) 
                                         //TODO: Change these values to actual numbers based on testing 
                                                                                                {

}

void ConveyorSubsystem::robotInit() {
    //Initializes the buttons on operator joystick
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::LEFT_TRIGGER);
    operatorJoystick->RegisterButton(COREJoystick::JoystickButton::LEFT_BUTTON);
}

void ConveyorSubsystem::teleopInit() {
    //Initializes the TalonSRX to start not move at start of teleop
    m_conveyorMotor.Set(ControlMode::PercentOutput, 0);
}

void ConveyorSubsystem::teleop() {
    //Allows for operator control of the robot
    if (operatorJoystick->GetButton(COREJoystick::JoystickButton::LEFT_TRIGGER)) {
        setMotor(m_conveyorForwardSpeed.Get());
    } else if (operatorJoystick->GetButton(COREJoystick::JoystickButton::LEFT_BUTTON)) {
        setMotor(m_conveyorReverseSpeed.Get());
    } else {
        setMotor(0);
    }
}

void ConveyorSubsystem::setMotor(double speed) {
    //Sets the conveyor motor to specified speed
    m_conveyorMotor.Set(ControlMode::PercentOutput, speed);
}
