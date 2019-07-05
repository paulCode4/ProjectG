#pragma once
#include "GAPI.h"

class GAPI_API GTrackedObject
{
public:
	GTrackedObject();
	GTrackedObject(const GTrackedObject&);
	~GTrackedObject();
	
	//counter getter
	static int getInstanceCounter();

private:
	static int m_instanceCount;
};
