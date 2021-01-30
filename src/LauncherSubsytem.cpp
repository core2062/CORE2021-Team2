#include "LauncherSubsystem.h"

LauncherSubsystem::LauncherSubsystem() : 
                                        m_winch(WINCH_PORT),
                                        m_winchSolenoid(WINCH_PCM,WINCH_PISTON_IN_PORT,WINCH_PISTON_OUT_PORT)
{}

//Note 2863 encoder ticks is 3ft using 2020 Bot wheels

void LauncherSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	operatorJoystick->RegisterButton(CORE::COREJoystick::Y_BUTTON);
}

void LauncherSubsystem::teleopInit() {
}

void LauncherSubsystem::teleop() {
}

void LauncherSubsystem::initTalons() {
	// Sets up talons
	m_winch.Set(ControlMode::PercentOutput, 0);

	// Encoder Functions
    m_winch.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
 
    m_winch.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
 
	m_winch.SetSensorPhase(false);

	// Motor Inversion
	m_winch.SetInverted(false);
}

void LauncherSubsystem::resetEncoders() {
    m_winch.SetSelectedSensorPosition(0);
}

void LauncherSubsystem::toggleGear() {
	// Shifts from high gear to low gear or vice versa
	if (m_toggle) {
		m_winchSolenoid.Set(DoubleSolenoid::kForward);
		m_toggle = false;
	} else {
		m_winchSolenoid.Set(DoubleSolenoid::kReverse);
		m_toggle = true;
	}
}

void LauncherSubsystem::teleopEnd() {}
