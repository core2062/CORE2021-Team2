#pragma once

#include <string>
#include <CORERobotLib.h>
#include "DriveAction.h"
#include "DelayAction.h"

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
