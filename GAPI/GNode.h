#pragma once

#include "GAPI.h"

#include <string>
#include <map>

#include "GTrackedObject.h"

/**
 * GNode class represents a node in a given graph. Each node is 
 * identified by a unique name.
 **/
class GAPI_API GNode : public GTrackedObject
{
public:
    GNode(const std::string &iName);
    ~GNode(void);
    
    const std::string& getName() {return m_name;}
    
    //
    //Connect this node to given ipNode
    //
    ReturnCode connect(GNode *ipNode);
    
    //
    //Break the connection between this node and given ip node
    //if exists.
    //
    ReturnCode disconnect(GNode *ipNode);
    
    //
    //Disconnect all connections of this node.
    //
    ReturnCode disconnectAll();

    //
    //Get number of nodes which this node connects to
    //
    int getNumConnectedTo();

	//
	//Used in the graph file saving feature
	//
	std::string getConnectedNodesOutputString();

	//
	//Exposing the object counter
	//
	int getObjectCounter();

private:
    std::string m_name;
	std::map <std::string, GNode*> m_connNodes;

	//Helper to avoid recursion call of connect
	//Makes the connection in the attached node
	//
	void connectPeer(GNode *ipNode);


	//Helper to avoid recursion call of disconnect
	//Breaks the connection in the attached node
	//
	void disconnectPeer(GNode *ipNode);
};
