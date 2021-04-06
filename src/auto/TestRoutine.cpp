#include "TestRoutine.h"

TestRoutine::TestRoutine() : COREAuton("Test Routine") {}

void TestRoutine::AddNodes() {
    testNode = new Node(3, new LauncherAction(LAUNCHER_COCK));
    delayNode = new Node(3, new DelayAction());
    testNode2 = new Node(3,new LauncherAction(LAUNCHER_LAUNCH));
    AddFirstNode(testNode);
    testNode->AddNext(testNode2);
    //delayNode->AddNext(testNode2);
}
