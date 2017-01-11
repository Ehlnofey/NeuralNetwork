#include <vector>
#include "Neuron.h"
#include "Bind.h"
#include "Layer1D.h"

Layer1D::Layer1D(unsigned int size) : m_layer(size,NULL)
{
	for (unsigned int i = 0;i < m_layer.size();i++)
		m_layer[i] = new Neuron();
}

Neuron * Layer1D::operator[](unsigned int i)
{
	return m_layer[i];
}

void Layer1D::bind(Layer1D * nextLayer)
{
	for (unsigned int i = 0;i < m_layer.size();i++)
		for (unsigned int j = 0;j < nextLayer->m_layer.size();j++)
			m_layer[i]->bind(nextLayer->m_layer[j]);

	m_nextLayer = nextLayer;
	nextLayer->m_forwardLayer = this;
}

unsigned int Layer1D::size()
{
	return (unsigned int)m_layer.size();
}

void Layer1D::setValue(std::vector<double> datas)
{
	if (m_layer.size() == 0 || datas.size() == 0)
		return;

	double resize(0);

	if (m_layer.size()>1)
		resize = double(datas.size() - 1) / double(m_layer.size() - 1);

	for (unsigned int i = 0;i < m_layer.size();i++)
		m_layer[i]->setValue(datas[unsigned int(double(i)*resize)]);
}

void Layer1D::correctError()
{
	for (unsigned int i = 0;i < m_layer.size();i++)
	{
		m_layer[i]->correctError();
	}
}

void Layer1D::calcError()
{
	for (unsigned int i = 0;i < m_layer.size();i++)
	{
		m_layer[i]->calcError();
	}
}
void Layer1D::calcError(std::vector<double> expected)
{
	for (unsigned int i = 0;i < m_layer.size();i++)
	{
		m_layer[i]->calcError(expected[i]);
	}
}
std::vector<double> Layer1D::getError(std::vector<double> e)
{
	std::vector<double> error;

	for (unsigned int i = 0;i < m_layer.size();i++)
		error.push_back(m_layer[i]->getError(e[i]));

	return error;
}

std::vector<double> Layer1D::getValue()
{
	std::vector<double> output;

	for (unsigned int i = 0;i < m_layer.size();i++)
		output.push_back(m_layer[i]->getValue());

	return output;
}



void Layer1D::stimulate()
{
	for (unsigned int i = 0;i < m_layer.size();i++)
		m_layer[i]->stimulate();
}

Layer1D::~Layer1D()
{
	for (unsigned int i = 0;i < m_layer.size();i++)
		delete m_layer[i];
}
