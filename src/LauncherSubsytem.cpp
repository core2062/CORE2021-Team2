#include "LauncherSubsystem.h"

LauncherSubsystem::LauncherSubsystem() : 
                                        m_frontWinch(FRONT_WINCH_PORT),
										m_backWinch(BACK_WINCH_PORT),
                                        m_winchSpeed("Winch drawback speed", 0.7),
                                        m_maxWinchDrawback("Max winch drawback distance", 33000),
                                        m_dogShifterSolenoid(WINCH_PCM, DOG_SHIFTER_PISTON_IN_PORT, DOG_SHIFTER_PISTON_OUT_PORT),
										m_releaseSolenoid(WINCH_PCM, RELEASE_PISTON_IN_PORT, RELEASE_PISTON_OUT_PORT),
                                        m_limitSwitch(0) //TODO: Put real number here
                                        {}

void LauncherSubsystem::robotInit() {
	// Registers joystick axis and buttons, does inital setup for talons
	operatorJoystick->RegisterAxis(CORE::COREJoystick::RIGHT_TRIGGER_AXIS);
	operatorJoystick->RegisterButton(CORE::COREJoystick::B_BUTTON);
	operatorJoystick->RegisterButton(CORE::COREJoystick::START_BUTTON);

    m_released = false;
    m_isMotorEngaged = true;
    m_isReleasedEngaged = false;
    isLauncherDown = false;

    initTalons();
    
    wantedState = STANDBY;
}

void LauncherSubsystem::teleopInit() {
    // Initializes all the booleans so that they match initial robot setup
    m_motorPercentSpeed = 0;
    m_released = false;
    m_isMotorEngaged = true;
    m_isReleasedEngaged = false;
    isLauncherDown = false;
    initTalons();
    wantedState = STANDBY;
    resetEncoder();
    m_releaseSolenoid.Set(DoubleSolenoid::kReverse);
    m_dogShifterSolenoid.Set(DoubleSolenoid::kForward);
    time.Reset();
    time2.Reset();
}

void LauncherSubsystem::teleop() {
    // Putting useful data to smartdashboard
    SmartDashboard::PutNumber("Winch drawback distance", getEncoderValue());
    SmartDashboard::PutBoolean("Winch motor active", !m_released);
    SmartDashboard::PutNumber("Winch motor speed", m_motorPercentSpeed);

    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
        wantedState = COCK;
    }
    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::START_BUTTON)) {
        wantedState = LAUNCH;
    }
    cockLauncher();
    launch();
}

void LauncherSubsystem::setMotorSpeed(double speed) {
    //Sets motor speed to inputted value
    m_frontWinch.Set(ControlMode::PercentOutput,speed);
    m_backWinch.Set(ControlMode::PercentOutput, speed);
}

void LauncherSubsystem::initTalons() {
	// Sets up talons
	m_frontWinch.Set(ControlMode::PercentOutput, 0);
	m_backWinch.Set(ControlMode::PercentOutput, 0);

	// Encoder Functions
    m_frontWinch.SetStatusFramePeriod(StatusFrameEnhanced::Status_1_General, 10, 0);
    m_frontWinch.ConfigSelectedFeedbackSensor(ctre::phoenix::motorcontrol::FeedbackDevice::IntegratedSensor, 0, 0);
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
    if (isLauncherDown == false && wantedState == COCK) {
        if ((getEncoderValue() <= m_maxWinchDrawback.Get() && m_isReleasedEngaged == false) /*|| !m_limitSwitch.Get()*/) {
            setMotorSpeed(m_winchSpeed.Get());
        } else if (m_isMotorEngaged == true) {
            m_releaseSolenoid.Set(DoubleSolenoid::kForward);
            toggleDogShifter();
            time2.Reset();
            time2.Start();
        }

        if (time2.Get() > 0.25) {
            m_isReleasedEngaged = true;
            setMotorSpeed(-0.1);
            time2.Reset();
        }

        if (((getEncoderValue()) >= (m_maxWinchDrawback.Get() - 2000)) && m_isReleasedEngaged == true) {
            setMotorSpeed(0);
            isLauncherDown = true;
            wantedState = STANDBY;
        }
    } 

}

void LauncherSubsystem::launch() {
    if (isLauncherDown == true && wantedState == LAUNCH) {
        if (m_isReleasedEngaged) {
            toggleRelease();
            time.Reset();
            time.Start();
        }
        if (time.Get() > 2) {
            isLauncherDown = false;
            wantedState = STANDBY;
            toggleDogShifter();
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
		m_releaseSolenoid.Set(DoubleSolenoid::kReverse);
		m_isReleasedEngaged = false;
	} else {
		m_releaseSolenoid.Set(DoubleSolenoid::kForward);
		m_isReleasedEngaged = true;
	}
}

void LauncherSubsystem::toggleDogShifter() {
	if (m_isMotorEngaged) {
		m_dogShifterSolenoid.Set(DoubleSolenoid::kReverse);
		m_isMotorEngaged = false;
	} else {
		m_dogShifterSolenoid.Set(DoubleSolenoid::kForward);
		m_isMotorEngaged = true;
	}

}