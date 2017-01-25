#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <list>
#include <thread>
#include <string>
#include "MatrixNDim.h"
#include "Network.h"
#include "Memory.h"
#include "Cortex.h"
#include "Interface.h"
#include "WritingInterface.h"
#include "Brain.h"
#include "Autoencoders.h"

void __run()
{
	WritingInterface wi(true);

	const std::vector<std::string> & sdb(wi.getDatabase());
	Matrix<Matrix2D<double>* > db((unsigned int)sdb.size());

	for (unsigned int i = 0;i<db.length();i++)
		db[i] = new Matrix2D<double>(WritingInterface::convert(sdb[i]));

	Autoencoders autoencoders(db, MatrixCoord<unsigned int>(3, 50, 25, 50));

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

			std::cout << WritingInterface::convert(autoencoders.getAleaDream()) << std::endl;
		}
		else if (choix == 3)
		{
			autoencoders.rebuild();
		}

	}

	for (unsigned int i = 0;i < db.length();i++)
		delete db[i];
}

int main()
{
	srand((unsigned int)time(NULL));

	__run();

	system("pause");

	return 0;
}