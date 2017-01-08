#pragma once

class Bind;
class Neuron;

class Network
{
public:
	Network();
	Network(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
	void addLayer(unsigned int count);
	void setInput(std::vector<double> datas);
	void build(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
	void clear();
	std::vector<double> getOutput();
	~Network();

private:
	std::vector<std::vector<Neuron*> > m_network;
};

