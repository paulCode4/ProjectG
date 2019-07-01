#include "GGraph.h"

#include "stdio.h"
#include <iostream>
#include <fstream>

GGraph::GGraph(const std::string &iName) : m_name(iName)
{
}

GGraph::~GGraph(void)
{
	if (!m_graphNodes.empty())
	{
		for (auto node : m_graphNodes)
		{
			delete node.second;
		}
		m_graphNodes.clear();
	}
}


GNode* GGraph::addNode(const std::string& iName)
{
	GNode* fRet = NULL;

	if ("" != iName)
	{
		if (0 == m_graphNodes.count(iName))
		{
			GNode* newNode = new GNode(iName);
			m_graphNodes.emplace(std::make_pair(iName, newNode));
			return newNode;
		}
	}

	return fRet;
}

GNode* GGraph::getNode(const std::string& iName)
{
	GNode* fRet = NULL;

	if (1 == m_graphNodes.count(iName))
	{
		fRet = m_graphNodes[iName];
	}
	else
	{
		//printf("\nThe node identified by the name: %s does not exist!", iName);
	}

	return fRet;
}

ReturnCode GGraph::removeNode(const std::string& iName)
{
	ReturnCode fRet = RC_NotImplemented;

	if ("" != iName)
	{
		GNode* remNode = getNode(iName);
		if (NULL != remNode)
		{
			delete remNode;
			m_graphNodes.erase(iName);
			fRet = RC_OK;
		}
		else
		{
			fRet = RC_ValueError;
			//printf("\nThe node identified by the name: %s does not exist!", iName);
		}
	}
	else
	{
		fRet = RC_ParameterError;
	}

    return fRet;
}

ReturnCode GGraph::save(const std::string& iFileName)
{
	ReturnCode fRet = RC_NotImplemented;

	std::ofstream output;
	output.open(iFileName);

	//write graph name on 1st line
	output << m_name;
	output << "\n";
	//continue with graph nodes on 2nd line to the nth line
	if (!m_graphNodes.empty())
	{
		for (auto node : m_graphNodes)
		{
			output << node.first;
			output << "\n";
		}
		//finish node representation with another new line
		output << "\n";

		//for each node print on a line separated by space all its connection nodes
		//eg. NodeName ConnNode1 ConnNode2 ......
		for (auto node : m_graphNodes)
		{
			std::string nodeWithConns = node.first + node.second->getConnectedNodesOutputString();
			output << nodeWithConns;
			output << "\n";
		}
		fRet = RC_OK;
	}

	output.close();

    return fRet;
}

ReturnCode GGraph::load(const std::string& iFileName)
{
    return RC_NotImplemented;
}

int GGraph::getNumNodes()
{
    return m_graphNodes.size();
}

