#include "TestRoutine.h"

TestRoutine::TestRoutine() : COREAuton("Test Routine") {}

void TestRoutine::AddNodes() {
    delayNode = new Node(3, new DelayAction());
    AddFirstNode(testNode);
    testNode->AddNext(testNode2);
    //delayNode->AddNext(testNode2);
}
