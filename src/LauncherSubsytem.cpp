#include "LauncherSubsystem.h"

LauncherSubsystem::LauncherSubsystem() : 
                                        m_frontWinch(FRONT_WINCH_PORT),
										m_backWinch(BACK_WINCH_PORT),
                                        m_winchSpeed("Winch drawback speed", 0.1),
                                        m_maxWinchDrawback("Max winch drawback distance", 2048),
                                        m_dogShifterSolenoid(WINCH_PCM, DOG_SHIFTER_PISTON_IN_PORT, DOG_SHIFTER_PISTON_OUT_PORT),
										m_releaseSolenoid(WINCH_PCM, RELEASE_PISTON_IN_PORT, RELEASE_PISTON_OUT_PORT),
                                        m_limitSwitch(0) //TODO: Put real number here
                                        {}

void LauncherSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	operatorJoystick->RegisterAxis(CORE::COREJoystick::RIGHT_TRIGGER_AXIS);
	operatorJoystick->RegisterButton(CORE::COREJoystick::B_BUTTON);
	operatorJoystick->RegisterButton(CORE::COREJoystick::START_BUTTON);
    initTalons();
}

void LauncherSubsystem::teleopInit() {
    // Initializes all the booleans so that they match initial robot setup
    m_motorPercentSpeed = 0;
    m_released = false;
    m_isMotorEngaged = true;
    m_isReleasedEngaged = false;
    m_isLauncherDown = false;
    initTalons();
    m_wantedState = STANDBY;
    m_loopNumber = 0;
}

void LauncherSubsystem::teleop() {
    // Putting useful data to smartdashboard
    SmartDashboard::PutNumber("Winch drawback distance",m_frontWinch.GetSelectedSensorPosition(0));
    SmartDashboard::PutBoolean("Winch motor active", !m_released);
    SmartDashboard::PutNumber("Winch motor speed", m_motorPercentSpeed);

    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
        m_wantedState = COCK;
    }
    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::START_BUTTON)) {
        m_wantedState = LAUNCH;
    }
    cockLauncher();
    launch();
}

void LauncherSubsystem::setMotorSpeed(double speed) {
    //Sets motor speed to inputted value
    m_frontWinch.Set(ControlMode::PercentOutput,speed);
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

    //Coast Mode
    m_frontWinch.SetNeutralMode(NeutralMode::Coast);
    m_backWinch.SetNeutralMode(NeutralMode::Coast);
}

void LauncherSubsystem::resetEncoder() {
    // Resets position, to be used after each launch
    m_frontWinch.SetSelectedSensorPosition(0, 0, 0);
}

void LauncherSubsystem::cockLauncher() {
    // Pulls down launcher and prepares it for release
    if (m_isLauncherDown == false && m_wantedState == COCK) {
        if (m_isMotorEngaged == false) {
            toggleDogShifter();
        }

        if (m_isReleasedEngaged == true) {
            toggleRelease();
        }

        if ((getEncoderValue() <= m_maxWinchDrawback.Get()) || !m_limitSwitch.Get()) {
            setMotorSpeed(m_winchSpeed.Get());
        } else if (m_loopNumber == 0) {
            toggleRelease();
            toggleDogShifter();
            setMotorSpeed(0.1);
        }
        m_loopNumber++;
        if (m_loopNumber > 5) {
            m_loopNumber = 0;
            setMotorSpeed(0);
            m_isLauncherDown = true;
            m_wantedState = STANDBY;
        }
    } 

}

void LauncherSubsystem::launch() {
    if (m_isLauncherDown == true && m_wantedState == LAUNCH) {
        toggleRelease();
        m_loopNumber++;
        if (m_loopNumber > 5) {
            toggleDogShifter();
            m_loopNumber = 0;
            m_wantedState = STANDBY;
            resetEncoder();
        }
    }
 
}

double LauncherSubsystem::getEncoderValue() {
    // Returns the position of the winch
    return m_frontWinch.GetSelectedSensorPosition();
}


void LauncherSubsystem::toggleRelease() {
	// Toggles the release arm
	if (m_isReleasedEngaged) {
		m_releaseSolenoid.Set(DoubleSolenoid::kForward);
		m_isReleasedEngaged = false;
	} else {
		m_releaseSolenoid.Set(DoubleSolenoid::kReverse);
		m_isReleasedEngaged = true;
	}
}

void LauncherSubsystem::toggleDogShifter() {
	if (m_isMotorEngaged) {
		m_dogShifterSolenoid.Set(DoubleSolenoid::kForward);
		m_isMotorEngaged = false;
	} else {
		m_dogShifterSolenoid.Set(DoubleSolenoid::kReverse);
		m_isMotorEngaged = true;
	}

}