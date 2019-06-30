#include "TestNode.h"

#include "../GAPI/GNode.h"

TestNode::TestNode(void)
{
}

TestNode::~TestNode(void)
{
    tearDown("");
}


void TestNode::run()
{
    RUN_TEST(testConstruct);
    RUN_TEST(testConnect);
    RUN_TEST(testDisconnect);
    RUN_TEST(testDisconnectAll);
}

int TestNode::setUp(const std::string& iTestName)
{
    return 0;
}

void TestNode::tearDown(const std::string& iTestName)
{
}

void TestNode::testConstruct()
{
    GNode *pNode = new GNode("na");
    ASSERT_NOT_EQUALS(pNode, NULL);
    ASSERT_EQUALS(pNode->getName(), "na");
    ASSERT_EQUALS(pNode->getNumConnectedTo(), 0);
    
}

void TestNode::testConnect()
{
    GNode *pNode = new GNode("node");
    ASSERT_EQUALS(pNode->connect(NULL), RC_ParameterError);
    
    GNode *pNa = new GNode("na");
    ASSERT_EQUALS(pNode->connect(pNa), RC_OK);
    ASSERT_EQUALS(pNode->getNumConnectedTo(), 1);
    ASSERT_EQUALS(pNode->connect(pNa), RC_ValueError);
    ASSERT_EQUALS(pNode->getNumConnectedTo(), 1);
}

void TestNode::testDisconnect()
{
    GNode *pNode = new GNode("node");
    ASSERT_EQUALS(pNode->disconnect(NULL), RC_ParameterError);
    
    GNode *pNa = new GNode("na");
    pNode->connect(pNa);
    
    ASSERT_EQUALS(pNode->disconnect(pNa), RC_OK);
    ASSERT_EQUALS(pNode->getNumConnectedTo(), 0);
    ASSERT_EQUALS(pNode->disconnect(pNa), RC_ValueError);
}

void TestNode::testDisconnectAll()
{
    GNode *pNode = new GNode("node");
    GNode *pNa = new GNode("na");
    GNode *pNb = new GNode("nb");
    pNode->connect(pNa);
    pNode->connect(pNb);
    
    ASSERT_EQUALS(pNode->getNumConnectedTo(), 2);
    ASSERT_EQUALS(pNode->disconnectAll(), RC_OK);
    ASSERT_EQUALS(pNode->getNumConnectedTo(), 0);
    ASSERT_EQUALS(pNode->disconnect(pNa), RC_ValueError);
    ASSERT_EQUALS(pNode->disconnect(pNb), RC_ValueError);
}

