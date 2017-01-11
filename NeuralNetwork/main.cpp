#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <list>
#include <thread>
#include "Network.h"
#include "Memory.h"
#include "Cortex.h"
#include "Interface.h"
#include "WritingInterface.h"
#include "Brain.h"
#include "Autoencoders.h"

int main()
{
	srand((unsigned int)time(NULL));

	WritingInterface wi(true);

	const std::vector<std::string> & sdb(wi.getDatabase());
	std::vector<std::vector<double> > db(sdb.size());

	for (unsigned int i = 0;i<db.size();i++)
		db[i] = WritingInterface::convert(sdb[i]);

	Autoencoders autoencoders(db,25,25,2,12);

	bool run(true);

	while (run)
	{
		int choix(0);

		std::cout << "Choix?" << std::endl;

		std::cin >> choix;

		if (choix == -1)
			run = false;
		else if (choix == 0)
		{
			double thershold(0.1);

			std::cout << "Seuil?" << std::endl;

			std::cin >> thershold;

			autoencoders.minimizeError(thershold, true);
		}
		else if (choix == 1)
		{
			double thershold(0.1);

			std::cout << "Seuil?" << std::endl;

			std::cin >> thershold;

			autoencoders.minimizeError(thershold, false);
		}
		else if (choix == 2)
		{
			autoencoders.extract();

			autoencoders.getAleaDream();
		}

	}

	return 0;
}