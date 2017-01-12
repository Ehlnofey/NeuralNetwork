#include <vector>
#include <thread>
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

void thread_train(Network *network, int n, std::vector<double> &errors, std::vector<std::vector<double>> &inputs, 
	std::vector<std::vector<double>> &outputs)
{
	for (unsigned int i = 0; i < inputs.size() / n; i++)
	{
		unsigned int index(rand() % inputs.size());
		std::vector<double> e(network->train(inputs[index], outputs[index]));

		for (unsigned int j = 0; j < e.size(); j++)
			errors[j] += e[j];
	}
}

std::vector<double> Network::train(std::vector<std::vector<double>> inputs, std::vector<std::vector<double>> outputs)
{
	if (outputs.size() == 0)
		return std::vector<double>();

	std::vector<double> errors(outputs[0].size());

	unsigned int n(8);
	std::vector<std::thread*> m_thread;

	for (unsigned int k = 0; k < n; k++)
	{
		m_thread.push_back(new std::thread(thread_train,this,n,errors,inputs,outputs));
	}
	for (unsigned int k = 0; k < n; k++)
	{
		m_thread[k]->join();
		delete m_thread[k];
	}
	for (unsigned int j = 0;j < errors.size();j++)
		errors[j] /= inputs.size();

	(*m_network.rbegin())->calcError(errors);
	for(size_t i=m_network.size()-2;i>0;i--)
		m_network[i]->calcError();
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
