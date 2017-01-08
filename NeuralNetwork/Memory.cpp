#include <vector>
#include <map>
#include "Memory.h"



Memory::Memory():m_relevantValueCoeff(2.0), m_precisionCoeff(16), m_relevantDataSizeLow(10), m_relevantDataSizeHigh(100), old_mean(0)
{
}

void Memory::add(std::vector<double> &data)
{
	m_memory[convert(data)]++;
}

void Memory::analyzeData()
{
	double mean(0);

	for (std::map<std::vector<int>, int>::iterator it = m_memory.begin();it != m_memory.end();it++)
		mean += it->second;

	mean /= m_memory.size();

	if (old_mean == 0)
	{
		old_mean = mean;
		return;
	}
	
	if (std::abs(old_mean - mean) / mean < 0.1)
	{

		int relevantDataSize(0);

		for (std::map<std::vector<int>, int>::iterator it = m_memory.begin();it != m_memory.end();it++)
		{
			if (it->second < mean / m_relevantValueCoeff&&m_relevantData[it->first]>INT_MIN)
				m_relevantData[it->first]--;
			if (it->second > mean*m_relevantValueCoeff&&m_relevantData[it->first] < INT_MAX)
			{
				m_relevantData[it->first]++;
				relevantDataSize++;
			}
		}

		if (relevantDataSize < m_relevantDataSizeLow)
		{
			m_memory.clear();
			m_relevantData.clear();
			m_precisionCoeff /= 2;
		}
		if (relevantDataSize > m_relevantDataSizeHigh)
		{
			m_memory.clear();
			m_relevantData.clear();
			m_precisionCoeff *= 2;
		}
	}

	old_mean = mean;
}

void Memory::remove(int threshold)
{
	std::vector<std::vector<int> > todelete;
	for (std::map<std::vector<int>, int>::iterator it = m_relevantData.begin();it != m_relevantData.end();it++)
	{
		if (it->second <= threshold)
			todelete.push_back(it->first);
	}

	for (std::vector<int> &d : todelete)
	{
		m_relevantData.erase(d);
	}
}

bool Memory::isThisDataRelevant(std::vector<double> &data, int threshold)
{
	std::vector<int> ref(convert(data));
	if(m_memory.find(ref)==m_memory.end())
		return false;
	return (m_memory[ref] > threshold);
}

std::vector<int> Memory::convert(std::vector<double>& data)
{
	std::vector<int> refinedData(data.size(), 0);

	for (unsigned int i = 0;i < data.size();i++)
	{
		refinedData[i] = int(data[i] * m_precisionCoeff);
	}

	return refinedData;
}



Memory::~Memory()
{
}
