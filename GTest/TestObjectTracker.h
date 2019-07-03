#pragma once
#include "TestCase.h"
//class GObjectTracker;
//class GTrackedObject;

//****The GObjectTracker counter class will keep hold of all instances numbers (graphs + nodes) - common counter variable
//****Rename to GTrackedObject

//will have to implement the marking of the objects for deletion/removal when linked to other nodes
//shall be destructed when connectionless

//A node can be destroyed only if not connected to other node/s AND not being part of a graph 

//Add existing nodes to a graph

//ObjectPool?
	//could create instances (dynamically)
	//dispense() could mark an object(nodes mainly as not needed)

//OR

//https://www.geeksforgeeks.org/overloading-new-delete-operator-c/
//https://www.modernescpp.com/index.php/overloading-operator-new-and-delete




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
     * @test: Deletion of GNode object (B) does NOT decrease the tracked object counter
     * @test: Deletion of GNode object (A) decreses the tracked object counter by 2 destroying 
     * the connected object (B) but not (C)
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
