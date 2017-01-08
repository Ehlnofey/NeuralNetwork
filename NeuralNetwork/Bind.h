#pragma once

class Neuron;

class Bind
{
public:
	Bind(Neuron *input, Neuron *output);
	double getValue();
	void stimulate();
	void init();
	~Bind();

private :
	Neuron *m_input;
	Neuron *m_output;
	double m_coeff;
	int m_stimulation;
	int m_disactivity;
	bool m_active;

	const double Epsilon;
	const double DELETE_BIND;
	const double DEF_DELETE_BIND;
};

