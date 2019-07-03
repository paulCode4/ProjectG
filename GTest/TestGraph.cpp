#include "TestGraph.h"
#include "../GAPI/GGraph.h"
#include "../GAPI/GNode.h"

#include<fstream>
#include<iostream>
#include<conio.h>

TestGraph::TestGraph(void)
{
}

TestGraph::~TestGraph(void)
{
}


void TestGraph::run()
{
    RUN_TEST(testConstruct);
    RUN_TEST(testAddNode);
    RUN_TEST(testRemoveNode);
    RUN_TEST(testNodeAccess);
    RUN_TEST(testSaveLoad);
}

//
//
//
int TestGraph::setUp(const std::string& iTestName)
{
    return 0;
}

//
//
//
void TestGraph::tearDown(const std::string& iTestName)
{
}

//
//
//
void TestGraph::testConstruct()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_NOT_EQUALS(pGraph, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), 0);
	delete pGraph;
}

//
//
//
void TestGraph::testAddNode()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_NOT_EQUALS(pGraph, NULL);
    int numNodes = pGraph->getNumNodes();
    
    ASSERT_EQUALS(pGraph->addNode(""), NULL);

    GNode *pNode_na = pGraph->addNode("na");
    ASSERT_NOT_EQUALS(pNode_na, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes + 1);
    pNode_na = NULL;

    pNode_na = pGraph->addNode("na");
    ASSERT_EQUALS(pNode_na, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes + 1);
	delete pGraph;
}

//
//
//
void TestGraph::testRemoveNode()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_EQUALS(pGraph->removeNode(""), RC_ParameterError);
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_ValueError);
    
    pGraph->addNode("na");
    int numNodes = pGraph->getNumNodes();
    
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_OK);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes - 1);
    
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_ValueError);
	delete pGraph;
}


void TestGraph::testNodeAccess()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_EQUALS(pGraph->getNode("na"), NULL);
    GNode *pNode = pGraph->addNode("na");
    ASSERT_EQUALS(pGraph->getNode("na"), pNode);
	delete pGraph;
}

void TestGraph::testSaveLoad()
{
	GGraph *pGraph = new GGraph("ga");
	GNode *pNode1 = pGraph->addNode("na");
	GNode *pNode2 = pGraph->addNode("nb");
	pNode1->connect(pNode2);

	ASSERT_EQUALS(pGraph->save("testFileOut.txt"), RC_OK);

	GNode *pNode3 = pGraph->addNode("nc");

	ASSERT_EQUALS(pGraph->save("testFileOut.txt"), RC_OK);

	GGraph *pGraphL = new GGraph("gb");
	ASSERT_EQUALS(pGraphL->load("testFileOut.txt"), RC_OK);
	
	ASSERT_EQUALS(pGraphL->save("testFileOutLoaded.txt"), RC_OK);
	ASSERT_EQUALS(*pGraph == *pGraphL, true);
	ASSERT_EQUALS(compareTextFiles("testFileOut.txt", "testFileOutLoaded.txt"), true);

	ASSERT_EQUALS(pGraphL->load("whatFile?.txt"), RC_ParameterError);

	ASSERT_EQUALS(pGraph->load("testGraphLoad.txt"), RC_OK);
	ASSERT_EQUALS(pGraphL->load("testGraphLoad.txt"), RC_OK);
	ASSERT_EQUALS(*pGraph == *pGraphL, true);

	ASSERT_EQUALS(pGraphL->load("testFileOut.txt"), RC_OK);
	ASSERT_EQUALS(*pGraph == *pGraphL, false);

	ASSERT_EQUALS(pGraphL->load("failLoadG.txt"), RC_ValueError);

	delete pGraph;
	delete pGraphL;
}

bool TestGraph::compareTextFiles(std::string iFile1, std::string iFile2)
{
	bool fRet = true;
	std::fstream f1, f2;
	char c1, c2;

	f1.open(iFile1, std::ios::in);
	if (!f1.is_open())
	{
		std::cout << "File1 can't be opened" << std::endl;
	}

	f2.open(iFile2, std::ios::in);
	if (!f1.is_open())
	{
		std::cout << "File2 can't be opened" << std::endl;
	}

	do
	{
		c1 = f1.get();
		c2 = f2.get();
		if (c1 != c2) 
		{
			fRet = false;
			break;
		}
	} 
	while ((c1 != EOF) || (c2 != EOF));

	f1.close();
	f2.close();

	return fRet;
}
