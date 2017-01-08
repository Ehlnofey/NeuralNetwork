#include <vector>
#include <map>
#include <list>
#include <thread>
#include <string>
#include <iostream>
#include "Network.h"
#include "Memory.h"
#include "Cortex.h"
#include "Interface.h"
#include "WritingInterface.h"
#include "Brain.h"


Brain::Brain() : isRunning(true), learnningMod(true), count(0)
{
	Cortex::setRun(&isRunning);
	m_writingInterface = new  WritingInterface();
}

bool Brain::run()
{
	if (count > 10000)
		learnningMod = false;

	if (learnningMod)
	{
		m_writingInterface->learn();

		count++;
	}
	else
	{
		std::string s;

		std::cin >> s;

		if (s == "0")
			isRunning = false;

		std::cout << m_writingInterface->doYouReconizeThat(s) << std::endl;
	}

	return isRunning;
}


Brain::~Brain()
{
	delete m_writingInterface;
}
