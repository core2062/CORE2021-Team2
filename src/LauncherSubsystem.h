#pragma once

#include <CORERobotLib.h>
#include <frc/DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include "Config.h"

using namespace CORE;
using namespace frc;

class LauncherSubsystem : public CORESubsystem {
public:
	LauncherSubsystem();
	void robotInit() override;
	void teleopInit() override;
	void teleop() override;
	void teleopEnd() override;
	
	void setMotorSpeed(double percent);
	void initTalons();
	void resetEncoder();
	void toggleRelease();
	void toggledogShifter();

private:
	TalonFX m_frontWinch,m_backWinch;
    DoubleSolenoid m_releaseSolenoid,m_dogShifterSolenoid;
	double m_motorPercentSpeed;
	bool m_released, m_dogShifterToggle;
	COREConstant<double> m_winchSpeed;
	COREConstant<int> m_limiter;
};