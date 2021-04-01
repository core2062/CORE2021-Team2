#include "LauncherSubsystem.h"

LauncherSubsystem::LauncherSubsystem() : 
                                        m_frontWinch(WINCH_ONE_PORT),
                                        m_backWinch(WINCH_TWO_PORT),
                                        m_releaseSolenoid(WINCH_PCM,WINCH_RELEASE_PISTON_IN_PORT,WINCH_RELEASE_PISTON_OUT_PORT),
                                        m_dogShifterSolenoid(WINCH_PCM,UNNAMED_WINCH_RELEASE_PISTON_IN_PORT,UNNAMED_WINCH_RELEASE_PISTON_OUT_PORT),
                                        m_winchSpeed("Winch drawback speed",0.1),
                                        m_limiter("Max winch drawback distance", 2048)
{}

void LauncherSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	operatorJoystick->RegisterAxis(CORE::COREJoystick::RIGHT_TRIGGER_AXIS);
	operatorJoystick->RegisterButton(CORE::COREJoystick::B_BUTTON);
	operatorJoystick->RegisterButton(CORE::COREJoystick::A_BUTTON);
    initTalons();
}

void LauncherSubsystem::teleopInit() {
    m_motorPercentSpeed = 0;
    initTalons();
}

void LauncherSubsystem::teleop() {

    // Putting useful data to smartdashboard
    SmartDashboard::PutNumber("Winch drawback distance", m_frontWinch.GetSelectedSensorPosition(0));
    SmartDashboard::PutBoolean("Winch motor active", !m_released);
    SmartDashboard::PutBoolean("Dog shifter toggled", m_dogShifterToggle);
    SmartDashboard::PutNumber("Winch motor speed", m_motorPercentSpeed);

    // Setting motor speed only if released
    double triggerAxis = operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_TRIGGER_AXIS);
    if (m_frontWinch.GetSelectedSensorPosition(0) <= m_limiter.Get()) {
        m_motorPercentSpeed = m_winchSpeed.Get() * triggerAxis;
    } else {
        m_motorPercentSpeed = 0;
    }

    setMotorSpeed(m_motorPercentSpeed);

    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
        toggleRelease();
    }

    
    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::A_BUTTON)) {
        toggledogShifter();
    }
}

// Sets the speed of the winch motor, only able to be called when m_released is false
void LauncherSubsystem::setMotorSpeed(double speed) {
    m_frontWinch.Set(ControlMode::PercentOutput,speed);
    m_backWinch.Set(ControlMode::PercentOutput,speed);
}

void LauncherSubsystem::initTalons() {
	// Sets up talons
	m_frontWinch.Set(ControlMode::PercentOutput, 0);
	m_backWinch.Set(ControlMode::PercentOutput, 0);

	// Encoder Functions
    m_frontWinch.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
 
    m_frontWinch.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
 
	m_frontWinch.SetSensorPhase(false);

	// Motor Inversion
	m_frontWinch.SetInverted(false);
	m_backWinch.SetInverted(false);
}

void LauncherSubsystem::resetEncoder() {
    m_frontWinch.SetSelectedSensorPosition(0);
}

// Toggles the launcher release, disables movement of the winch while released
void LauncherSubsystem::toggleRelease() {
	// Releases launcher
	if (m_released) {
		m_releaseSolenoid.Set(DoubleSolenoid::kForward);
        // Will reset the encoders everytime to accuratly determine the winch soft-stop 
        resetEncoder();
		m_released = false;
	} else {
		m_releaseSolenoid.Set(DoubleSolenoid::kReverse);
        // Will reset the encoders everytime to accuratly determine the winch soft-stop 
        resetEncoder();
		m_released = true;
	}
}

void LauncherSubsystem::toggledogShifter() {
	if (m_dogShifterToggle) {
		m_dogShifterSolenoid.Set(DoubleSolenoid::kForward);
		m_dogShifterToggle = false;
	} else {
		m_dogShifterSolenoid.Set(DoubleSolenoid::kReverse);
		m_dogShifterToggle = true;
	}
}

void LauncherSubsystem::teleopEnd() {}
