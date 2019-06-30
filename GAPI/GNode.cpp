#include "GNode.h"


GNode::GNode(const std::string &iName)
{
}

GNode::~GNode(void)
{
}

ReturnCode GNode::connect(GNode *ipNode)
{
    return RC_NotImplemented;
}

ReturnCode GNode::disconnect(GNode *ipNode)
{
    return RC_NotImplemented;
}

ReturnCode GNode::disconnectAll()
{
    return RC_NotImplemented;
}

int GNode::getNumConnectedTo()
{
    return -1;
}
