#pragma once
#include "GAPI.h"

class GAPI_API GTrackedObject
{
public:
	GTrackedObject();
	~GTrackedObject();
	
	//counter node mutators
	static void incrementNodeInstanceCounter();
	static void decrementNodeInstanceCounter();
	//counter graph mutators
	static void incrementGraphInstanceCounter();
	static void decrementGraphInstanceCounter();
	//counter getters
	static int getNodeInstanceCounter();
	static int getGraphInstanceCounter();
	static int getTotalInstanceCounter();
private:
	static int m_nodeInstanceCount;
	static int m_graphInstanceCount;
};
