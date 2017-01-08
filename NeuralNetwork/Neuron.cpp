#include <vector>
#include "Neuron.h"
#include "Bind.h"

double Neuron::Lambda(1.);

Neuron::Neuron()
{
}

double Neuron::getValue()
{
	if(m_input.size()==0)
		return sigmoide(m_value);

	m_value = 0;

	for (unsigned int i = 0;i < m_input.size();i++)
		m_value += m_input[i]->getValue();
	

	return m_value;
}

void Neuron::setValue(double x)
{
	m_value = x;
}

void Neuron::stimulate()
{
	for (unsigned int i = 0;i < m_todelete.size();i++)
		delete m_todelete[i];

	m_todelete.clear();

	for (unsigned int i = 0;i < m_input.size();i++)
		if(m_input[i]!=NULL)
			m_input[i]->stimulate();
}

void Neuron::removeBind(Bind * bind)
{
	for (unsigned int i = 0;i < m_input.size();i++)
		if (m_input[i] == bind)
			m_input[i] = NULL;
	for (unsigned int i = 0;i < m_output.size();i++)
		if (m_output[i] == bind)
			m_output[i] = NULL;
}

void Neuron::deleteMe(Bind * d)
{
	m_todelete.push_back(d);
}

void Neuron::bind(Neuron * out)
{
	m_output.push_back(new Bind(this, out));
	out->m_input.push_back(*m_output.rbegin());
}


Neuron::~Neuron()
{
}

double Neuron::sigmoide(double x)
{
	return 1/(1+exp(-x*Lambda));
}
