#include "TestObjectTracker.h"

#include "../GAPI/GNode.h"
#include "../GAPI/GGraph.h"
//#include "../GAPI/GTrackedObject.h"

#include <iostream>



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
	GNode* pNode = new GNode("pNode");
	ASSERT_EQUALS(pNode->getObjectCounter(), 1);
	delete pNode;
	ASSERT_EQUALS(GTrackedObject::getInstanceCounter(), 0);
}

void TestObjectTracker::testGraph()
{
	GGraph* pGraph = new GGraph("pGraph");
	ASSERT_EQUALS(pGraph->getObjectCounter(), 1);
	delete pGraph;
	ASSERT_EQUALS(GTrackedObject::getInstanceCounter(), 0);
}

void TestObjectTracker::testNodeWithConnection()
{
	GNode* pNa = new GNode("pNa");
	GNode* pNb = new GNode("pNb");
	GNode* pNc = new GNode("pNc");
	GNode* pNd = new GNode("pNd");
	ASSERT_EQUALS(GTrackedObject::getInstanceCounter(), 4);
	
	ASSERT_EQUALS(pNa->connect(pNb), RC_OK);
	ASSERT_EQUALS(pNa->connect(pNc), RC_OK);
	ASSERT_EQUALS(pNa->connect(pNd), RC_OK);
	//WTF MAN
	ASSERT_EQUALS(pNb->connect(pNd), RC_OK);
	ASSERT_EQUALS(pNd->getNumConnectedTo(), 2);
	std::cout << std::endl << pNd->getConnectedNodesOutputString();
	printf("TestPND:%p", pNd);
	///
	delete pNd;
	ASSERT_EQUALS(GTrackedObject::getInstanceCounter(), 4); //WHY ???

	//ASSERT_EQUALS(GTrackedObject::getInstanceCounter(), 0);
}

void TestObjectTracker::testGraphWithNodes()
{
    //TO BE IMPLEMENTED
}
