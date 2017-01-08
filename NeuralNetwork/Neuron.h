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
	static double sigmoide(double x);
	~Neuron();

protected:

	std::vector<Bind *> m_input;
	std::vector<Bind *> m_output;
	std::vector<Bind *> m_todelete;
	double m_value;
	static double Lambda;
};

