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

const int WritingInterface::IN_LENGTH(50);

WritingInterface::WritingInterface(bool out)
{
	if(!out)
		init(IN_LENGTH, 5, 50, 50);

	std::ifstream file("./Ressources/test.txt");/*liste.de.mots.francais.frgut.txt");/**/

	std::string c;
	while(getline(file,c)&&m_database.size()<std::pow(8,6))
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

const std::vector<std::string>& WritingInterface::getDatabase()
{
	return m_database;
}

std::vector<double> WritingInterface::convert(std::string s)
{
	const double norm(0.0001);
	std::vector<double> data(IN_LENGTH,0);

	for (unsigned int i = 0;i < s.size();i++)
		data[i] = double(s[i])*norm;

	return data;
}

std::string WritingInterface::convert(std::vector<double> s)
{
	const double norm(0.0001);
	std::string data(IN_LENGTH, 0);

	for (unsigned int i = 0; i < s.size(); i++)
		data[i] = char(s[i]/norm);

	return data;
}

void WritingInterface::learn()
{
	m_cortex->feed(getInfo());
}

WritingInterface::~WritingInterface()
{
	if (m_cortex != NULL)
		delete m_cortex;
	m_cortex = NULL;
}
