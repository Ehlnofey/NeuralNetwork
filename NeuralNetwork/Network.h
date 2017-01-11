#pragma once

class Bind;
class Neuron;
class Layer1D;

class Network
{
public:
	Network();
	Network(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
	void addLayer(unsigned int count);
	void setInput(std::vector<double> datas);
	void build(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
	void clear();
	std::vector<Layer1D*> getijLayer(unsigned int i,unsigned int j=-1);
	std::vector<double> train(std::vector< std::vector<double> > inputs, std::vector< std::vector<double> > outputs);
	std::vector<double> train(std::vector<double> input, std::vector<double> output);
	std::vector<double> getOutput();
	~Network();

private:
	std::vector<Layer1D*> m_network;
};

