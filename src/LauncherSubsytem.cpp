#include "LauncherSubsystem.h"

LauncherSubsystem::LauncherSubsystem() : 
                                        m_winch(WINCH_PORT),
                                        m_winchSolenoid(WINCH_PCM,WINCH_PISTON_IN_PORT,WINCH_PISTON_OUT_PORT),
                                        m_winchSpeed("Winch drawback speed",0.1),
                                        m_maxWinchDrawback("Max winch drawback distance", 2048)
{}

void LauncherSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	operatorJoystick->RegisterAxis(CORE::COREJoystick::RIGHT_TRIGGER_AXIS);
	operatorJoystick->RegisterButton(CORE::COREJoystick::B_BUTTON);
    initTalons();
}

void LauncherSubsystem::teleopInit() {
    m_motorPercentSpeed = 0;
    initTalons();
}

void LauncherSubsystem::teleop() {

    // Putting useful data to smartdashboard
    SmartDashboard::PutNumber("Winch drawback distance",m_winch.GetSelectedSensorPosition(0));
    SmartDashboard::PutBoolean("Winch motor active", !m_released);
    SmartDashboard::PutNumber("Winch motor speed", m_motorPercentSpeed);

    //Setting motor speed only if released
    double triggerAxis = operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::RIGHT_TRIGGER_AXIS);
    if (m_winch.GetSelectedSensorPosition(0) <= m_maxWinchDrawback.Get() && !m_released) {
        m_motorPercentSpeed = m_winchSpeed.Get() * triggerAxis;
    } else {
        m_motorPercentSpeed = 0;
    }

    if (operatorJoystick->GetRisingEdge(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
        toggleRelease();
    }
    setMotorSpeed(m_motorPercentSpeed);
}

void LauncherSubsystem::setMotorSpeed(double speed) {
    m_winch.Set(ControlMode::PercentOutput,speed);
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

void LauncherSubsystem::resetEncoder() {
    m_winch.SetSelectedSensorPosition(0);
}

void LauncherSubsystem::toggleRelease() {
	// Releases launcher
	if (m_released) {
		m_winchSolenoid.Set(DoubleSolenoid::kForward);
        resetEncoder();
		m_released = false;
	} else {
		m_winchSolenoid.Set(DoubleSolenoid::kReverse);
        resetEncoder();
		m_released = true;
	}
}

void LauncherSubsystem::teleopEnd() {}
