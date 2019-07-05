#pragma once
#include "TestCase.h"
//class GObjectTracker;
//class GTrackedObject;

/**
 * Test Case to check that life cycle of objects are managed correctly. Below the word 
 * "Deletion" is used as "not using an object anymore". It does not necesserily refer to 
 * keyword "delete" from C++. That part refers to the implementation. Developer should make 
 * sure that an object (be it graph or node) can not be removed from memory if there is 
 * anybody referring (using) it.
 */
class TestObjectTracker :
    public TestCase
{
public:
    TestObjectTracker(void);
    ~TestObjectTracker(void);
    
protected:
    void run();
    int setUp(const std::string& iTestName);
    void tearDown(const std::string& iTestName);
    
private:
    /**
     * @test: Creation of GNode object increases the tracked object counter by one
     * @test: Deletion of GNode object decreses the tracked object counter by one
     */
    void testNode();
    
    /**
     * @test: Creation of GGraph object increases the tracked object counter by one
     * @test: Deletion of GGraph object decreses the tracked object counter by one
     */
    void testGraph();
    

    /**
     * @test: Creation of GNode objects (A, B, C and D) increase the tracked object counter by 4
     * @action: Create connections A->B, A->C and A->D
     * @test: Deletion of GNode object (D) does NOT decrease the tracked object counter
     * @test: Disconnecting A->D connection decreases the tracked object counter by 1
	 * -------CONTRADICTS THE FIRST PART OF THE TEST------------------------------------
     * @test: Deletion of GNode object (B) does NOT decrease the tracked object counter
     * @test: Deletion of GNode object (A) decreses the tracked object counter by 2 destroying 
     * the connected object (B) but not (C)
	 * ---------------------------------------------------------------------------------
	 * As node (C) was still connected to (A), (A) should have remained alive, but marked for deletion.
	 * Having (C) still not Del marked, it makes sense to keep (A)
	 * We can destroy (B) with the assumption that a connection between 2 nodes Del marked is useless
	 * In the next step deletion of (C) should decrease the counter by 2, taking also (A) with it
	 * ---------------------------------------------------------------------------------
     * @test: Deletion of object C decreses the object counter by 1
     */
    void testNodeWithConnection();
    
    
    /**
     * @test: Creation of GGraph (G) and GNode objects (A, B) increase the tracked object counter by 3
     * @action: Add A and B to G 
     * @test: Deletion of A does NOT decrease the tracked object counter 
     * @test: Deletion of G object decreses the tracked object counter by 2 destroying A but not B
     * @test: Deletion of B object decreases the tracked object counter by 1
     */
    void testGraphWithNodes();
};
