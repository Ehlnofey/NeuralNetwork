#include <iostream>
#include <vector>
#include "Bind.h"
#include "Neuron.h"


Bind::Bind(Neuron * input, Neuron * output): m_input(input),m_output(output),m_coeff(double(rand()-RAND_MAX/2)/double(RAND_MAX/2)), m_stimulation(0), m_active(true), Epsilon(Neuron::sigmoide(0.0)), 
	DELETE_BIND(-100), m_disactivity(0), DEF_DELETE_BIND(10000), Lambda(0.1)
{
}

double Bind::getValue()
{
	if (!m_active)
	{
		m_disactivity++;
		if (m_disactivity > DEF_DELETE_BIND)
		{
			m_input->deleteMe(this);
			m_input->removeBind(this);
			m_output->removeBind(this);
		}
		return 0;
	}


	return m_coeff*m_input->getValue();
}

void Bind::correctError()
{
	double e(m_input->m_error);
	double eff_value(Lambda*e*m_output->m_value);
	m_coeff -= eff_value;
}

void Bind::calcError()
{
	m_output->calcError();
}

void Bind::stimulate()
{
	if (m_input == NULL)
		return;

	m_input->stimulate();

	double in_value = m_input->getValue();

	if (in_value < Epsilon)
		m_stimulation--;
	else if (in_value > Epsilon)
		m_stimulation++;

	if (m_stimulation < DELETE_BIND)
		m_active = false;
}

double Bind::getError()
{
	return m_coeff*m_output->m_error;
}

void Bind::init()
{
	m_coeff = rand() / RAND_MAX;
	m_stimulation = 0;
	m_disactivity = 0;
	m_active = true;
}

Bind::~Bind()
{
	m_input->removeBind(this);
	m_output->removeBind(this);
}
