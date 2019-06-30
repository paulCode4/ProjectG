#pragma once
#include "TestCase.h"

class GNode;

class TestNode :
    public TestCase
{
public:
    TestNode(void);
    ~TestNode(void);
    
protected:
    void run();
    int setUp(const std::string& iTestName);
    void tearDown(const std::string& iTestName);

private:
    //
    //
    //
    void testConstruct();
    
    //
    //
    //
    void testConnect();
    
    //
    //
    //
    void testDisconnect();
    
    //
    //
    //
    void testDisconnectAll();
    
};
