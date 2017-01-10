#pragma once

class Layer1D
{
public:
	Layer1D(unsigned int size);
	Neuron * operator[](unsigned int i);
	void bind(Layer1D* nextLayer);
	unsigned int size();
	void setValue(std::vector<double> datas);
	std::vector<double> getValue();
	void stimulate();
	~Layer1D();

private:
	std::vector<Neuron*> m_layer;
	Layer1D *m_nextLayer, *m_forwardLayer;
};

