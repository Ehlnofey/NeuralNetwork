#include <vector>
#include <map>
#include <list>
#include <thread>
#include "Network.h"
#include "Memory.h"
#include "Cortex.h"

bool* Cortex::isRunning(NULL);

void run_cortex(Cortex *c, unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize)
{
	c->m_network.build(inputSize, outputSize, hideLayerCount, hideLayerSize);

	if (c->isRunning == NULL)
		return;
	while(*c->isRunning)
		c->run();
}

Cortex::Cortex(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize) : m_thread(run_cortex, this, inputSize, outputSize, hideLayerCount, hideLayerSize),
dataAnalyze(0), dataAnalyzeBeforClear(0), dataAnalyzisRate(100), dataClearRate(1000)
{
}

void Cortex::feed(std::vector<double> &input_data)
{
	datas.push_back(input_data);
}

void Cortex::run()
{
	if (datas.size() == 0)
		return;
	std::list<std::vector<double>>::iterator input_data(datas.begin());
	m_network.setInput(*input_data);
	m_memory.add(m_network.getOutput());
	dataAnalyze++;
	dataAnalyzeBeforClear++;
	if (dataAnalyze > dataAnalyzisRate)
	{
		m_memory.analyzeData();
		dataAnalyze = 0;
	}
	if (dataAnalyzeBeforClear>dataClearRate)
	{
		m_memory.remove();
		dataAnalyzeBeforClear = 0;
	}
	datas.erase(input_data);
}

void Cortex::setRun(bool * ir)
{
	isRunning = ir;
}

Cortex::~Cortex()
{
	*isRunning = false;
	m_thread.join();
}
