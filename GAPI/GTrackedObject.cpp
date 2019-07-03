#include "GTrackedObject.h"

int GTrackedObject::m_instanceCount = 0;

GTrackedObject::GTrackedObject()
{
	++m_instanceCount;
}


GTrackedObject::~GTrackedObject()
{
	--m_instanceCount;
}

GTrackedObject::GTrackedObject(const GTrackedObject &)
{
	++m_instanceCount;
}

int GTrackedObject::getInstanceCounter()
{
	return m_instanceCount;
}

