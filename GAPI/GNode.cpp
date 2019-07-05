#include "GNode.h"

#include <algorithm>

std::vector<std::string> GNode::ms_names = {};

GNode::GNode(const std::string &iName) : m_name(iName), mp_graphOwned(NULL), mf_markForDeletion(false)
{
	GTrackedObject::incrementNodeInstanceCounter();
}

GNode::~GNode(void)
{
	GTrackedObject::decrementNodeInstanceCounter();
}

bool GNode::operator==(GNode& iNode)
{
	//as nodes have to be unique, a node will be equal to another
	//only when we have the same node, RVal pointing towards the same address as LVal

	return (this == &iNode);
}

bool GNode::operator!=(GNode& iNode)
{
	//as nodes have to be unique, a node will be equal to another
	//only when we have the same node, RVal pointing towards the same address as LVal

	return (this != &iNode);
}

void GNode::deleteNode()
{
	if (isDeletable())
	{
		delete(this);
	}
	else
	{
		mf_markForDeletion = true;
		//connections with nodes that are also marked for deletion
		//become useless, therefore have to be disconnected
		remConnectionWithDelMarkNodes();
		//in the meantime the node may become deletable
		if (isDeletable())
		{
			delete(this);
		}
	}
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

	if (!mp_graphOwned && mf_markForDeletion)
	{
		deleteNode();
	}

    return fRet;
}

int GNode::getNumConnectedTo()
{
    return m_connNodes.size();
}

std::string GNode::getConnectedNodesOutputString()
{
	std::string fRet = "";

	if (!m_connNodes.empty())
	{
		for (auto conn : m_connNodes)
		{
			fRet = fRet + " " + conn.first;
		}
	}

	return fRet;
}

void GNode::setGraphOwned(void* iGraphAddress)
{
	mp_graphOwned = iGraphAddress;

	if (isDeletable() && mf_markForDeletion)
	{
		deleteNode();
	}
}

const bool & GNode::isMarkedForDeletion()
{
	return mf_markForDeletion;
}

bool GNode::isNodeNameUnique(const std::string& iNewNameCtor)
{
	bool fRet = false;

	if (!ms_names.empty())
	{
		if (std::find(ms_names.begin(), ms_names.end(), iNewNameCtor) == ms_names.end())
		{
			fRet = true;
		}
	}
	else
	{
		fRet = true;
	}

	return fRet;
}

void GNode::connectPeer(GNode * ipNode)
{
	m_connNodes.emplace(std::make_pair(ipNode->getName(), ipNode));
}

void GNode::disconnectPeer(GNode * ipNode)
{
	m_connNodes.erase(ipNode->getName());
	//printf("discPeerNodeConn:%s\n", this->getConnectedNodesOutputString().c_str());
	//printf("discPeer:%p-isDel:%d-markDel:%d", this, isDeletable(), mf_markForDeletion);
	if (isDeletable() && mf_markForDeletion)
	{
		deleteNode();
	}
}

bool GNode::isDeletable()
{
	bool fRet = false;
	//printf("<ConnEmpty:%d - ConnSize:%d- %s>", m_connNodes.empty(), m_connNodes.size(), getConnectedNodesOutputString().c_str());
	if ((!mp_graphOwned) && m_connNodes.empty())
	{
		fRet = true;
	}
	
	return fRet;
}

void GNode::remConnectionWithDelMarkNodes()
{
	std::vector<std::string> nodeStringsToRem;
	for (auto node : m_connNodes)
	{
		if (node.second->isMarkedForDeletion())
		{
			node.second->disconnectPeer(this);
			nodeStringsToRem.push_back(node.first);
		}
	}
	
	for (auto name : nodeStringsToRem)
	{
		m_connNodes.erase(name);
	}
}
