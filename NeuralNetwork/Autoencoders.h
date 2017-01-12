#pragma once

class Network;
class Layer1D;

class Autoencoders
{
public:
	Autoencoders(std::vector<std::vector<double> >& database, unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
	void minimizeError(double threshold=0.1,bool printError=false);
	void extract();
	void rebuild();
	std::vector<double> getDream(std::vector<double> data);
	std::vector<double> getAleaDream();
	~Autoencoders();

private:
	Network m_network;

	unsigned int m_inputSize, m_outputSize, m_hideLayerCount, m_hideLayerSize;

	std::vector<std::vector<double> > &m_database;
	std::vector<Layer1D*> m_extractedLayer;
};

