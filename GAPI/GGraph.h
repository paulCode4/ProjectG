#pragma once

#include "GAPI.h"

#include <string>
#include <map>

#include "GNode.h"
#include "GTrackedObject.h"


/**
 * GGraph class represents a graph object which is used to group a number of nodes.
 */
class GAPI_API GGraph
{
public:
    GGraph(const std::string &iName);
	GGraph(const GGraph&) = delete;
    ~GGraph(void);
	//override == for graph comaprison (value-wise comparison)
	bool operator==(GGraph& iGraph);

	//
	//Deletes the graph only, but:
	//Nodes that are connectionless and marked for deletion will also go
	//Nodes that are still interconnected will remain allocated
	void removeGraph();

	//
	//Completely deletes the graph and all its nodes
	//
	void deleteGraph();

    //
    //Create a new node object and store it in graph for future access
    //Created object is returned to the caller as well
    //
    GNode* addNode(const std::string &iName);

    //
    //Remove the node given by its name.
    //
    ReturnCode removeNode(const std::string &iName);

	//
	//Removes all the nodes of the graph
	//
	void removeAllNodes();
    
    //
    //Return the node object identified by iName
    //
    GNode* getNode(const std::string& iName);
    
    //
    //Return number of nodes attached to this graph
    //
    int getNumNodes();

    //
    //Dump the current state of the graph to given file
    //
    ReturnCode save(const std::string& iFileName);
    
    //
    //Update the current state of the graph from given file
    //
    ReturnCode load(const std::string& iFileName);

private:
	//Nodes of the graph
	std::map <std::string, GNode*> m_graphNodes;
	//Graph name
	std::string m_name;
};
