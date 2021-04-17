#pragma once

#include <string>
#include <iostream>
#include <frc/RobotBase.h>
#include <frc/TimedRobot.h>
#include <CORERobotLib.h>
#include <COREFramework/COREScheduler.h>
#include "DriveSubsystem.h"
#include "Config.h"
#include "auto/TestRoutine.h"
#include "auto/DriveRoutine.h"
#include "ConveyorSubsystem.h"
#include "LauncherSubsystem.h"

using namespace CORE;
using namespace std;

class Robot : public CORERobot {
public: 
 	Robot();
	void robotInit() override;
    void teleopInit() override;
    void teleop() override;
	void test() override;
	void testInit() override;
	static Robot * GetInstance();
	DriveSubsystem driveSubsystem;
	TestRoutine testRoutine;
	DriveRoutine driveRoutine;
	ConveyorSubsystem conveyorSubsystem;
	LauncherSubsystem launcherSubsystem;

private:
	static Robot * m_instance;
};
