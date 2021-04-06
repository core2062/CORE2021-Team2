#pragma once

#include <CORERobotLib.h>
#include <frc/DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include "Config.h"

using namespace CORE;
using namespace frc;

class ConveyorSubsystem : public CORESubsystem {
public:
    ConveyorSubsystem();
    void robotInit() override;
	void teleopInit() override;
	void teleop() override;

    void setMotor(double speed);
    
    COREConstant<double> conveyorForwardSpeed, conveyorReverseSpeed;
private:
    TalonSRX m_conveyorMotor;   
};