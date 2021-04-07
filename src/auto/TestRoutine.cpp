#include "TestRoutine.h"

TestRoutine::TestRoutine() : COREAuton("Test Routine") {}

void TestRoutine::AddNodes() {
    testNode = new Node(5, new LauncherAction(LAUNCHER_COCK));
    delayNode = new Node(3, new DelayAction());
    testNode2 = new Node(5,new LauncherAction(LAUNCHER_LAUNCH));
    AddFirstNode(testNode);
    testNode->AddNext(delayNode);
    delayNode->AddNext(testNode2);
}
