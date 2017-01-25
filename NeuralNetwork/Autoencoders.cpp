#include <iostream>
#include "Autoencoders.h"



Autoencoders::Autoencoders(Matrix<Matrix2D<double>* >  &database, MatrixCoord<unsigned int> &layerSize) : m_database(database),
	m_network(layerSize), m_layerSize(layerSize)
{
}

void Autoencoders::minimizeError(double threshold, bool printError)
{
	double mean(threshold+1);
	double old_mean(mean*10000);
	while (std::abs(mean) >= threshold)
	{
		mean = m_network.train(m_database, m_database);

		if (printError)
			std::cout << mean << std::endl;

		if (std::abs(old_mean) <= std::abs(mean))
			break;

		old_mean = mean;
	}
}

void Autoencoders::extract()
{
	m_extractedNetwork = m_network.getSubNetwork((int)m_layerSize.length() / 2 + 1);
}

void Autoencoders::rebuild()
{
	//m_network.build(m_inputSize, m_outputSize, m_hideLayerCount, m_hideLayerSize);
}

Matrix2D<double> Autoencoders::getDream(Matrix2D<double> *data)
{
	if(data->length()==0)
		return Matrix2D<double>();

	return m_extractedNetwork.process(data);
}

Matrix2D<double> Autoencoders::getAleaDream()
{
	Matrix2D<double> data(m_layerSize.last(),1);

	for (unsigned int i = 0;i < data.length();i++)
		data(i,0) = double(rand() % RAND_MAX) / double(RAND_MAX);

	return getDream(&data);
}


Autoencoders::~Autoencoders()
{
}
