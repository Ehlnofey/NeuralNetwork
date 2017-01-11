#pragma once

class Layer1D
{
public:
	Layer1D(unsigned int size);
	Neuron * operator[](unsigned int i);
	void bind(Layer1D* nextLayer);
	unsigned int size();
	void setValue(std::vector<double> datas);
	void correctError();
	void calcError();
	void calcError(std::vector<double> expected);
	std::vector<double> getError(std::vector<double> error);
	std::vector<double> getValue();
	void stimulate();
	~Layer1D();

private:
	std::vector<Neuron*> m_layer;
	Layer1D *m_nextLayer, *m_forwardLayer;
};

