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
	void toggleUnnamed();

private:
	TalonSRX m_winchOne,m_winchTwo;
    DoubleSolenoid m_winchSolenoid,m_unnamedWinchSolenoid;
	double m_winchDistance, m_motorPercentSpeed;
	bool m_released,m_unnamedSolenoidToggle;
	COREConstant<double> m_winchSpeed;
	COREConstant<int> m_maxWinchDrawback;
};