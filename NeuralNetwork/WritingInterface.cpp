#include <vector>
#include <map>
#include <list>
#include <thread>
#include <fstream>
#include <string>
#include "Network.h"
#include "Memory.h"
#include "Cortex.h"
#include "Interface.h"
#include "WritingInterface.h"



WritingInterface::WritingInterface() :IN_LENGTH(50)
{
	init(IN_LENGTH, 5, 50, 50);

	std::ifstream file("./Ressources/liste.de.mots.francais.frgut.txt");/*test.txt");*/

	std::string c;
	while(getline(file,c))
		m_database.push_back(c);
}

std::vector<double> WritingInterface::getInfo()
{

	int rmax(0);
	int r(0);
	while (rmax < m_database.size())
	{
		rmax += RAND_MAX;
		r += rand();
	}

	std::string s(m_database[r%m_database.size()]);

	return convert(s);
}

std::vector<double> WritingInterface::convert(std::string s)
{
	std::vector<double> data(IN_LENGTH,0);

	for (unsigned int i = 0;i < s.size();i++)
		data[i] = double(s[i]);

	return data;
}

void WritingInterface::learn()
{
	m_cortex->feed(getInfo());
}

bool WritingInterface::doYouReconizeThat(std::string s)
{
	return (*m_cortex)(convert(s));
}



WritingInterface::~WritingInterface()
{
	if (m_cortex != NULL)
		delete m_cortex;
	m_cortex = NULL;
}
