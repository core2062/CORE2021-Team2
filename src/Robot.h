#pragma once

#include <string>
#include <iostream>
#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>
#include <CORERobotLib.h>
#include <COREFramework/COREScheduler.h>
#include "DriveSubsystem.h"
#include "Config.h"
// #include "TestRoutine.h"
// #include "DriveRoutine.h"

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
public: 
 	Robot();
	void RobotPeriodic() override;
	void TeleopPeriodic() override;
	void robotInit() override;
    void teleopInit() override;
    void teleop() override;
	void test() override;
	void testInit() override;
	static Robot * GetInstance();
	DriveSubsystem driveSubsystem;
	TestRoutine testRoutine;
	DriveRoutine driveRoutine;
	RobotContainer robotContainer;

private:
  	frc2::Command* m_autonomousCommand = nullptr;
	static Robot * m_instance;
};
