#include "TestObjectTracker.h"

#include "../GAPI/GNode.h"
#include "../GAPI/GGraph.h"

TestObjectTracker::TestObjectTracker(void)
{
}

TestObjectTracker::~TestObjectTracker(void)
{
    tearDown("");
}


void TestObjectTracker::run()
{
    RUN_TEST(testNode);
    RUN_TEST(testGraph);
    RUN_TEST(testNodeWithConnection);
    RUN_TEST(testGraphWithNodes);
}

int TestObjectTracker::setUp(const std::string& iTestName)
{
    return 0;
}

void TestObjectTracker::tearDown(const std::string& iTestName)
{
}

void TestObjectTracker::testNode()
{
    //TO BE IMPLEMENTED
}

void TestObjectTracker::testGraph()
{
    //TO BE IMPLEMENTED
}

void TestObjectTracker::testNodeWithConnection()
{
    //TO BE IMPLEMENTED
}

void TestObjectTracker::testGraphWithNodes()
{
    //TO BE IMPLEMENTED
}
