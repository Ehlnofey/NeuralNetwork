#include <vector>
#include "Neuron.h"
#include "Bind.h"
#include "Network.h"



Network::Network()
{
}

void Network::addLayer(unsigned int count)
{
	m_network.push_back(std::vector<Neuron*>(count, NULL));
	for (unsigned int i = 0;i < count;i++)
		(*m_network.rbegin())[i] = new Neuron();

	for (unsigned int i = 0;i < (*m_network.rbegin()++).size();i++)
		for (unsigned int j = 0;j < (*m_network.rbegin()).size();j++)
			(*m_network.rbegin()++)[i]->bind((*m_network.rbegin())[j]);
}

void Network::setInput(std::vector<double> datas)
{
	if (m_network.size() == 0 || datas.size()==0)
		return;

	double resize(0);

	if(m_network[0].size()>1)
		resize=double(datas.size() - 1) / double(m_network[0].size() - 1);

	for (unsigned int i = 0;i < m_network[0].size();i++)
		m_network[0][i]->setValue(datas[unsigned int(double(i)*resize)]);
	

	for (unsigned int i = 0;i < (*m_network.rbegin()).size();i++)
		(*m_network.rbegin())[i]->stimulate();
}

std::vector<double> Network::getOutput()
{
	std::vector<double> output;

	for (unsigned int i = 0;i < (*m_network.rbegin()).size();i++)
		output.push_back((*m_network.rbegin())[i]->getValue());

	return output;
}


Network::~Network()
{
	for (unsigned int i = 0;i < m_network.size();i++)
		for (unsigned int j = 0;j < m_network.size();j++)
			delete m_network[i][j];
}
