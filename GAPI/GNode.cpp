#include "GNode.h"


GNode::GNode(const std::string &iName) : m_name(iName)
{
}

GNode::~GNode(void)
{
}

ReturnCode GNode::connect(GNode *ipNode)
{
	ReturnCode fRet = RC_NotImplemented;

	if (ipNode)
	{
		if (0 == m_connNodes.count(ipNode->getName()))
		{
			m_connNodes.emplace(std::make_pair(ipNode->getName(), ipNode));
			ipNode->connectPeer(this);
			fRet = RC_OK;
		}
		else
		{
			//already connected to ipNode
			fRet = RC_ValueError;
		}
	}
	else
	{
		//printf("\nCannot add NULL pointer node connection!");
		fRet = RC_ParameterError;
	}

    return fRet;
}

ReturnCode GNode::disconnect(GNode *ipNode)
{
	ReturnCode fRet = RC_NotImplemented;

	if (ipNode)
	{
		if (1 == m_connNodes.count(ipNode->getName()))
		{
			m_connNodes.erase(ipNode->getName());
			ipNode->disconnectPeer(this);
			fRet = RC_OK;
		}
		else
		{
			//not connected to ipNode
			fRet = RC_ValueError;
		}
	}
	else
	{
		//printf("\nCannot remove NULL pointer node connection!");
		fRet = RC_ParameterError;
	}

	return fRet;
}

ReturnCode GNode::disconnectAll()
{
	ReturnCode fRet = RC_NotImplemented;
	
	if (0 != m_connNodes.size())
	{
		for (auto conn : m_connNodes)
		{
			conn.second->disconnectPeer(this);
		}
		m_connNodes.clear();
		fRet = RC_OK;
	}
	else
	{
		//printf("\nNothing to disconnect from. Node not connected to any other node.");
		fRet = RC_ValueError;
	}

    return fRet;
}

int GNode::getNumConnectedTo()
{
    return m_connNodes.size();
}

void GNode::connectPeer(GNode * ipNode)
{
	m_connNodes.emplace(std::make_pair(ipNode->getName(), ipNode));
}

void GNode::disconnectPeer(GNode * ipNode)
{
	m_connNodes.erase(ipNode->getName());
}
