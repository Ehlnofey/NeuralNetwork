#pragma once

class Cortex;

class Interface
{
public:
	Interface();
	Interface(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
	virtual std::vector<double> getInfo()=0;
	virtual void learn()=0;
	virtual ~Interface();

protected:
	Cortex *m_cortex;
	void init(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
};

