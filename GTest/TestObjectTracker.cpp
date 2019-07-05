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
	auto nodeCount = GTrackedObject::getNodeInstanceCounter();
	GNode* pNode = new GNode("pNode");
	ASSERT_EQUALS(GTrackedObject::getNodeInstanceCounter(), nodeCount + 1);

	nodeCount = GTrackedObject::getNodeInstanceCounter();
	pNode->deleteNode();
	ASSERT_EQUALS(GTrackedObject::getNodeInstanceCounter(), nodeCount - 1);
}

void TestObjectTracker::testGraph()
{
	auto graphCount = GTrackedObject::getGraphInstanceCounter();
	GGraph* pGraph = new GGraph("pGraph");
	ASSERT_EQUALS(GTrackedObject::getGraphInstanceCounter(), graphCount + 1);

	graphCount = GTrackedObject::getGraphInstanceCounter();
	pGraph->deleteGraph();
	ASSERT_EQUALS(GTrackedObject::getGraphInstanceCounter(), graphCount - 1);
}

void TestObjectTracker::testNodeWithConnection()
{
	auto nodeCount = GTrackedObject::getNodeInstanceCounter();
	GNode* pNa = new GNode("pNa");
	GNode* pNb = new GNode("pNb");
	GNode* pNc = new GNode("pNc");
	GNode* pNd = new GNode("pNd");
	ASSERT_EQUALS(GTrackedObject::getNodeInstanceCounter(), nodeCount + 4);
	
	ASSERT_EQUALS(pNa->connect(pNb), RC_OK);
	ASSERT_EQUALS(pNa->connect(pNc), RC_OK);
	ASSERT_EQUALS(pNa->connect(pNd), RC_OK);

	nodeCount = GTrackedObject::getNodeInstanceCounter();
	pNd->deleteNode();
	ASSERT_EQUALS(GTrackedObject::getNodeInstanceCounter(), nodeCount);
	pNa->disconnect(pNd);
	ASSERT_EQUALS(GTrackedObject::getNodeInstanceCounter(), nodeCount - 1);
	pNd = nullptr;

	nodeCount = GTrackedObject::getNodeInstanceCounter();
	pNb->deleteNode();
	ASSERT_EQUALS(GTrackedObject::getNodeInstanceCounter(), nodeCount);

	pNa->deleteNode();
	ASSERT_EQUALS(GTrackedObject::getNodeInstanceCounter(), nodeCount - 1);
	pNb = nullptr;

	nodeCount = GTrackedObject::getNodeInstanceCounter();
	pNc->deleteNode();
	ASSERT_EQUALS(GTrackedObject::getNodeInstanceCounter(), nodeCount - 2);
}

void TestObjectTracker::testGraphWithNodes()
{
	auto objectCount = GTrackedObject::getTotalInstanceCounter();
	
	auto graph = new GGraph("graph");
	auto nodeA = graph->addNode("A");
	ASSERT_NOT_EQUALS(nodeA, NULL);
	auto nodeB = graph->addNode("B");
	ASSERT_NOT_EQUALS(nodeB, NULL);
	ASSERT_EQUALS(GTrackedObject::getTotalInstanceCounter(), objectCount + 3);

	objectCount = GTrackedObject::getTotalInstanceCounter();
	nodeA->deleteNode();
	ASSERT_EQUALS(GTrackedObject::getTotalInstanceCounter(), objectCount);

	objectCount = GTrackedObject::getTotalInstanceCounter();
	graph->removeGraph();
	ASSERT_EQUALS(GTrackedObject::getTotalInstanceCounter(), objectCount - 2);
	nodeA = nullptr;
	graph = nullptr;

	objectCount = GTrackedObject::getTotalInstanceCounter();
	nodeB->deleteNode();
	ASSERT_EQUALS(GTrackedObject::getTotalInstanceCounter(), objectCount - 1);
}
