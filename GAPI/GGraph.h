#pragma once

#include "GAPI.h"

#include <string>
#include <map>

#include "GNode.h"
#include "GTrackedObject.h"


/**
 * GGraph class represents a graph object which is used to group a number of nodes.
 */
class GAPI_API GGraph : public GTrackedObject
{
public:
    GGraph(const std::string &iName);
    ~GGraph(void);
	//override == for graph comaprison (value-wise comparison)
	bool operator==(GGraph& iGraph);

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

	//
	//Exposing the object counter
	//
	int getObjectCounter();

private:
	std::map <std::string, GNode*> m_graphNodes;
	std::string m_name;
};
