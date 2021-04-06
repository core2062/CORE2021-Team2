#pragma once

#include <CORERobotLib.h>
#include <frc/DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include "Config.h"
#include <frc/DigitalInput.h>

using namespace CORE;
using namespace frc;

enum LauncherWantedState {
	STANDBY, COCK, LAUNCH
};

class LauncherSubsystem : public CORESubsystem {
public:
	LauncherSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	
	void launch();
	void cockLauncher();
	void setMotorSpeed(double percent);
	void initTalons();
	void resetEncoder();
	double getEncoderValue();
	void toggleRelease();
	void toggleDogShifter();

	LauncherWantedState wantedState;
	bool isLauncherDown;
	
private:
	TalonFX m_frontWinch, m_backWinch;
	COREConstant<double> m_winchSpeed;
	COREConstant<int> m_maxWinchDrawback;
    DoubleSolenoid m_dogShifterSolenoid, m_releaseSolenoid;
	double m_winchDistance, m_motorPercentSpeed, m_loopNumber;
	bool m_released, m_isMotorEngaged, m_isReleasedEngaged;
	DigitalInput m_limitSwitch;
	CORETimer time;
	CORETimer time2;
};