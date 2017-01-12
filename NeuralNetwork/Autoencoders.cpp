#include <vector>
#include <iostream>
#include "Neuron.h"
#include "Bind.h"
#include "Layer1D.h"
#include "Network.h"
#include "Autoencoders.h"



Autoencoders::Autoencoders(std::vector<std::vector<double> > &database, unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize) : m_database(database),
	m_network(inputSize, outputSize, hideLayerCount, hideLayerSize), m_hideLayerCount(hideLayerCount),m_inputSize(inputSize),m_outputSize(outputSize),m_hideLayerSize(hideLayerSize)
{
}

void Autoencoders::minimizeError(double threshold, bool printError)
{
	double mean(threshold+1);
	double old_mean(mean*10000);
	while (std::abs(mean) >= threshold)
	{
		std::vector<double> error(m_network.train(m_database, m_database));

		for (double &e : error)
			mean += e;

		mean /= error.size();

		if (printError)
			std::cout << mean << std::endl;

		if (std::abs(old_mean) <= std::abs(mean))
			break;

		old_mean = mean;
	}
}

void Autoencoders::extract()
{
	m_extractedLayer = m_network.getijLayer(m_hideLayerCount / 2 + 1);
}

void Autoencoders::rebuild()
{
	m_network.build(m_inputSize, m_outputSize, m_hideLayerCount, m_hideLayerSize);
}

std::vector<double> Autoencoders::getDream(std::vector<double> data)
{
	if(data.size()==0)
		return std::vector<double>();

	m_extractedLayer[0]->setValue(data);

	return (*m_extractedLayer.rbegin())->getValue();
}

std::vector<double> Autoencoders::getAleaDream()
{
	std::vector<double> data(m_extractedLayer[0]->size());

	for (unsigned int i = 0;i < data.size();i++)
		data[i] = double(rand() % RAND_MAX) / double(RAND_MAX);

	return getDream(data);
}


Autoencoders::~Autoencoders()
{
}
