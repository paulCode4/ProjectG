#include "GGraph.h"

#include "stdio.h"

GGraph::GGraph(const std::string &iName) : m_name(iName)
{
}

GGraph::~GGraph(void)
{
	if (0 != m_graphNodes.size())
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
	if ("" != iName)
	{
		if (0 == m_graphNodes.count(iName))
		{
			GNode* newNode = new GNode(iName);
			m_graphNodes.emplace(std::make_pair(iName, newNode));
			return newNode;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}

GNode* GGraph::getNode(const std::string& iName)
{
	if (1 == m_graphNodes.count(iName))
	{
		return m_graphNodes[iName];
	}
	else
	{
		//printf("\nThe node identified by the name: %s does not exist!", iName);
		return NULL;
	}
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
    return RC_NotImplemented;
}

ReturnCode GGraph::load(const std::string& iFileName)
{
    return RC_NotImplemented;
}

int GGraph::getNumNodes()
{
    return m_graphNodes.size();
}

