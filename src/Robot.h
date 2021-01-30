#pragma once

#include <string>
#include <iostream>
#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>
#include <CORERobotLib.h>
#include <COREFramework/COREScheduler.h>
#include "DriveSubsystem.h"
#include "LauncherSubsystem.h"
#include "Config.h"
#include "auto/TestRoutine.h"
#include "auto/DriveRoutine.h"

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
public: 
 	Robot();
	~Robot();
	void robotInit() override;
    void teleopInit() override;
    void teleop() override;
	void test() override;
	void testInit() override;
	static Robot * GetInstance();
	DriveSubsystem driveSubsystem;
	LauncherSubsystem launcherSubsystem;
	TestRoutine testRoutine;
	DriveRoutine driveRoutine;

private:
	static Robot * m_instance;
};
