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

int main()
{
	srand((unsigned int)time(NULL));

	Brain myBrain;

	while (myBrain.run());

	return 0;
}