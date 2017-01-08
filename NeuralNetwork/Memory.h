#pragma once

class Network;

class Memory
{
public:
	Memory();

	void add(std::vector<double> &data);
	void analyzeData();
	void remove(int threshold=INT_MIN);
	bool isThisDataRelevant(std::vector<double> &data, int threshold=0);

	~Memory();

private:

	std::vector<int> convert(std::vector<double> &data);

	std::map<std::vector<int>,int> m_memory;

	std::map<std::vector<int>,int> m_relevantData;
	
	double m_relevantValueCoeff;
	double m_precisionCoeff;
	int m_relevantDataSizeLow, m_relevantDataSizeHigh;

	double old_mean;
};

