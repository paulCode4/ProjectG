#include "GTrackedObject.h"

int GTrackedObject::m_nodeInstanceCount = 0;
int GTrackedObject::m_graphInstanceCount = 0;

GTrackedObject::GTrackedObject()
{
}

GTrackedObject::~GTrackedObject()
{
}

//counter node mutators
void GTrackedObject::incrementNodeInstanceCounter()
{
	++m_nodeInstanceCount;
}
void GTrackedObject::decrementNodeInstanceCounter()
{
	--m_nodeInstanceCount;
}
//counter graph mutators
void GTrackedObject::incrementGraphInstanceCounter()
{
	++m_graphInstanceCount;
}
void GTrackedObject::decrementGraphInstanceCounter()
{
	--m_graphInstanceCount;
}
//counter getters
int GTrackedObject::getNodeInstanceCounter()
{
	return m_nodeInstanceCount;
}
int GTrackedObject::getGraphInstanceCounter()
{
	return m_graphInstanceCount;
}
int GTrackedObject::getTotalInstanceCounter()
{
	return (m_graphInstanceCount + m_nodeInstanceCount);
}

