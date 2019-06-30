#include "TestGraph.h"
#include "../GAPI/GGraph.h"
#include "../GAPI/GNode.h"

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
    pGraph = NULL;
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
}


void TestGraph::testNodeAccess()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_EQUALS(pGraph->getNode("na"), NULL);
    GNode *pNode = pGraph->addNode("na");
    ASSERT_EQUALS(pGraph->getNode("na"), pNode);
}

void TestGraph::testSaveLoad()
{
    //TO BE IMPLEMENTED
}
