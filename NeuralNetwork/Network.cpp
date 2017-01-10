#include <vector>
#include "Neuron.h"
#include "Bind.h"
#include "Layer1D.h"
#include "Network.h"



Network::Network()
{
}

Network::Network(unsigned int inputSize, unsigned int outputSize, unsigned int neuronLayer, unsigned int neuronLayerSize)
{
	build(inputSize, outputSize, neuronLayer, neuronLayerSize);
}

void Network::addLayer(unsigned int count)
{
	if (m_network.size() == 0)
	{
		m_network.push_back(new Layer1D(count));
		return;
	}

	Layer1D *last(*m_network.rbegin());
	Layer1D *newLast(new Layer1D(count));

	m_network.push_back(newLast);

	last->bind(newLast);
}

void Network::setInput(std::vector<double> datas)
{
	if (m_network.size() == 0 || datas.size()==0)
		return;

	m_network[0]->setValue(datas);
	
	(*m_network.rbegin())->stimulate();
}

void Network::build(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize)
{
	clear();
	addLayer(inputSize);
	for (unsigned int i = 0;i < hideLayerCount;i++)
		addLayer(hideLayerSize);
	addLayer(outputSize);
}

void Network::clear()
{
	for (unsigned int i = 0;i < m_network.size();i++)
		delete m_network[i];

	m_network.clear();
}

std::vector<double> Network::getOutput()
{
	return (*m_network.rbegin())->getValue();
}


Network::~Network()
{
	clear();
}
