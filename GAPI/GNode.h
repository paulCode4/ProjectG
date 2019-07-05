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

	//
	//override delete op to have controled destruction/deallocation
	//
	void operator delete(void * p) noexcept;

	//
	//name getter
	//
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

	//
	//sets mf_graphOwned
	//
	void setGraphOwned(const bool& iGOwned);

	//
	//gets mf_markForDeletion
	//
	const bool& isMarkedForDeletion();

private:
    std::string m_name;
	//pointers to connected nodes mapped by name key
	std::map <std::string, GNode*> m_connNodes;
	//flag when node is part of graph
	bool mf_graphOwned;
	//flag node for deletion, deallocation will take place when node no longer used
	bool mf_markForDeletion;

	//Helper to avoid recursion call of connect
	//Makes the connection in the attached node
	//
	void connectPeer(GNode *ipNode);

	//Helper to avoid recursion call of disconnect
	//Breaks the connection in the attached node
	//
	void disconnectPeer(GNode *ipNode);
	//Helper to decide if a node
	//is no longer in use and can be deleted
	//
	bool isDeletable();

	//
	//When marked for deletion, connections with other nodes marked for deletion
	//will be removed
	void remConnectionWithDelMarkNodes();
};
