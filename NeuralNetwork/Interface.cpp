#include <vector>
#include <map>
#include <list>
#include <thread>
#include "Network.h"
#include "Memory.h"
#include "Cortex.h"
#include "Interface.h"



Interface::Interface():m_cortex(NULL)
{
}

Interface::Interface(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize):m_cortex(new Cortex(inputSize, outputSize, hideLayerCount, hideLayerSize))
{
}

void Interface::init(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize)
{
	m_cortex = new Cortex(inputSize, outputSize, hideLayerCount, hideLayerSize);
}


Interface::~Interface()
{
	if(m_cortex!=NULL)
		delete m_cortex;
	m_cortex = NULL;
}
