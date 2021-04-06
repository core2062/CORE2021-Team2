#pragma once

#include <string>
#include <CORERobotLib.h>
#include "DriveAction.h"
#include "DelayAction.h"
#include "LauncherAction.h"
#include "ConveyorAction.h"

using namespace CORE;
using namespace std;

class TestRoutine: public COREAuton {
public:
    TestRoutine();
    void AddNodes() override;
private:
    Node * testNode;
    Node * delayNode;
    Node * testNode2;
};
