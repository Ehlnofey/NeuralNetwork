#pragma once
class Network;
class Memory;


class Cortex
{
public:
	Cortex(unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
	void feed(std::vector<double> &input_data);
	void run();
	static void setRun(bool *isRunning);
	~Cortex();
private:
	Network m_network;
	Memory m_memory;
	std::thread m_thread;
	std::list< std::vector<double> > datas;
	int dataAnalyze,dataAnalyzeBeforClear;
	int dataAnalyzisRate,dataClearRate;

	static bool* isRunning;

	friend void run_cortex(Cortex *c, unsigned int inputSize, unsigned int outputSize, unsigned int hideLayerCount, unsigned int hideLayerSize);
};
