#pragma once

class Bind;
class Neuron;

class Network
{
public:
	Network();
	void addLayer(unsigned int count);
	void setInput(std::vector<double> datas);
	std::vector<double> getOutput();
	~Network();

private:
	std::vector<std::vector<Neuron*> > m_network;
};

