#pragma once
#include "TestCase.h"

class GGraph;

class TestGraph :
    public TestCase
{
public:
    TestGraph(void);
    ~TestGraph(void);
    
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
    void testAddNode();
    
    //
    //
    //
    void testRemoveNode();

    //
    //
    //
    void testNodeAccess();
    
    //
    //Test both save and load functionality of GGraph
    //When saved, a Graph dumps all its content to a file so 
    //it can be restored back from file. 
    //
    void testSaveLoad();  
};
