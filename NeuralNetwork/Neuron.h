#pragma once

class Bind;

class Neuron
{
public:
	Neuron();
	double getValue();
	void setValue(double x);
	void stimulate();
	void removeBind(Bind *bind);
	void deleteMe(Bind *d);
	void bind(Neuron *out);
	void correctError();
	void calcError();
	void calcError(double expected);
	double getError(double expected);
	static double sigmoide(double x);
	static double der_sigmoide(double x);
	~Neuron();

protected:

	double getError();
	std::vector<Bind *> m_input;
	std::vector<Bind *> m_output;
	std::vector<Bind *> m_todelete;
	double m_value, m_error;
	friend Bind;
	static double Lambda;
};

