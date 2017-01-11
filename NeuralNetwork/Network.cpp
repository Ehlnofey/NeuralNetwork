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
	
	//(*m_network.rbegin())->stimulate();
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

std::vector<Layer1D*> Network::getijLayer(unsigned int i, unsigned int j)
{
	std::vector<Layer1D*> networkPart;

	if (j == -1 || j >= m_network.size())
		j = unsigned int(m_network.size() - 1);

	for (unsigned int k = i;k <= j;k++)
		networkPart.push_back(m_network[k]);

	return networkPart;
}

std::vector<double> Network::train(std::vector<std::vector<double>> inputs, std::vector<std::vector<double>> outputs)
{
	if (outputs.size() == 0)
		return std::vector<double>();

	std::vector<double> errors(outputs[0].size());

	for (unsigned int i = 0;i < inputs.size();i++)
	{
		std::vector<double> e(train(inputs[i],outputs[i]));

		for (unsigned int j = 0;j < e.size();j++)
			errors[j] += e[j];
	}
	for (unsigned int j = 0;j < errors.size();j++)
		errors[j] /= inputs.size();

	m_network[0]->calcError();
	(*m_network.rbegin())->calcError(errors);
	(*m_network.rbegin())->correctError();


	return errors;
}

std::vector<double> Network::train(std::vector<double> input, std::vector<double> output)
{
	setInput(input);

	std::vector<double> error(output);
	std::vector<double> get(getOutput());

	if (error.size() != output.size())
		throw std::exception("Given ouput doesn't match with neural output layer.");

	for (unsigned int i = 0;i < get.size();i++)
		error[i] -= get[i];

	return error;
}

std::vector<double> Network::getOutput()
{
	return (*m_network.rbegin())->getValue();
}


Network::~Network()
{
	clear();
}
