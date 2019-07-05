#include "GNode.h"


GNode::GNode(const std::string &iName) : m_name(iName), mf_graphOwned(false), mf_markForDeletion(false)
{
}

GNode::~GNode(void)
{
}

void GNode::operator delete(void * p) noexcept
{
	GNode* node = reinterpret_cast<GNode*> (p);
	printf("DeleteP:%p\n", p);
	printf("DeleteNode:%p\n", node);
	if (node->isDeletable())
	{
		::delete(p);
	}
	else
	{
		node->mf_markForDeletion = true;
		//connections with nodes that are also marked for deletion
		//become useless, therefore have to be disconnected
		node->remConnectionWithDelMarkNodes();
		
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

	if (!mf_graphOwned && mf_markForDeletion)
	{
		delete(this);
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

int GNode::getObjectCounter()
{
	return GTrackedObject::getInstanceCounter();
}

void GNode::setGraphOwned(const bool& iGOwned)
{
	mf_graphOwned = iGOwned;

	if (isDeletable() && mf_markForDeletion)
	{
		delete(this);
	}
}

const bool & GNode::isMarkedForDeletion()
{
	return mf_markForDeletion;
}

void GNode::connectPeer(GNode * ipNode)
{
	m_connNodes.emplace(std::make_pair(ipNode->getName(), ipNode));
}

void GNode::disconnectPeer(GNode * ipNode)
{
	m_connNodes.erase(ipNode->getName());
	if (isDeletable() && mf_markForDeletion)
	{
		delete(this);
	}
}

bool GNode::isDeletable()
{
	bool fRet = false;
	//printf("<ConnEmpty:%d - ConnSize:%d- %s>", m_connNodes.empty(), m_connNodes.size(), getConnectedNodesOutputString().c_str());
	if ((!mf_graphOwned) && m_connNodes.empty())
	{
		fRet = true;
	}
	
	return fRet;
}

void GNode::remConnectionWithDelMarkNodes()
{
	for (auto node : m_connNodes)
	{
		if (node.second->isMarkedForDeletion())
		{
			node.second->disconnectPeer(this);
			m_connNodes.erase(node.first);
		}
	}
}
