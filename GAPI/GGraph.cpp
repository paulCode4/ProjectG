#include "GGraph.h"

#include "stdio.h"
#include <iostream>
#include <fstream>
#include <vector>
//#include <algorithm>


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
			fRet = newNode;
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
			if (remNode->getNumConnectedTo() > 0)
			{
				fRet = RC_ParameterError;
				//printf("\nThe node is still connected to other nodes! Cannot remove!");
			}
			else
			{
				delete remNode;
				m_graphNodes.erase(iName);
				fRet = RC_OK;
			}
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
	output << m_name << "\n";
	fRet = RC_OK;
	//continue with graph nodes on 2nd line separated by space
	if (!m_graphNodes.empty())
	{
		for (auto node : m_graphNodes)
		{
			output << node.first << " ";
		}
		output << "\n";
		//from the 3rd line onwards print each node with its conections on separate lines
		//eg. NodeName ConnNode1 ConnNode2 ......
		for (auto node : m_graphNodes)
		{
			std::string nodeWithConns = node.first + node.second->getConnectedNodesOutputString();
			output << nodeWithConns << "\n";
		}
	}

	output.close();

    return fRet;
}

ReturnCode GGraph::load(const std::string& iFileName)
{
	ReturnCode fRet = RC_OK;

	std::ifstream input(iFileName);
	std::string line = "";
	if (input.is_open())
	{
		int lineCounter = 1;
		while (std::getline(input, line))
		{
			line.erase(line.find_last_not_of(" \n\r\t") + 1);
			if ("" != line)
			{
				switch (lineCounter)
				{
				case 1: //handle graph name on first line
				{
					m_name = line;
				}
					break;

				case 2: //handle graph nodes on second line
				{
					//if nodes map not empty, clear it up to load nodes as described in file
					if (!m_graphNodes.empty())
					{
						for (auto node : m_graphNodes)
						{
							delete node.second;
						}
						m_graphNodes.clear();
					}
					//parse and tokenize the line to get the graph nodes
					char * cstr = new char[line.length() + 1];
					std::strcpy(cstr, line.c_str());

					char * p = std::strtok(cstr, " ");
					while (p != 0)
					{
						if (NULL == addNode(p))
						{
							fRet = RC_ValueError;
						}
						p = std::strtok(NULL, " ");
					}

					delete[] cstr;
				}
					break;

				default://all following lines will contain nodes with their connections
				{
					//parse and tokenize the line to get the graph node and its connetions
					char * cstr = new char[line.length() + 1];
					std::strcpy(cstr, line.c_str());

					char * p = std::strtok(cstr, " ");
					GNode* node = getNode(p);
					while (p != 0)
					{
						if (node)
						{
							p = std::strtok(NULL, " ");
							if (p != 0)
							{
								GNode* connection = getNode(p);
								if (connection)
								{
									node->connect(connection);
								}
								else
								{
									fRet = RC_ValueError;
								}
							}
						}
						else
						{
							fRet = RC_ValueError;
						}
					}

					delete[] cstr;
				}
				}

			}
			else if (1 == lineCounter)
			{
				fRet = RC_ValueError;
				break;
			}
			lineCounter++;
		}
		input.close();
	}
	else
	{
		//printf("Unable to open file");
		fRet = RC_ParameterError;
	}
    return fRet;
}

int GGraph::getNumNodes()
{
    return m_graphNodes.size();
}

