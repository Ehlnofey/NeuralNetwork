#include <vector>
#include <map>
#include <list>
#include <thread>
#include "Network.h"
#include "Memory.h"
#include "Cortex.h"
#include "Interface.h"
#include "Brain.h"


Brain::Brain() : isRunning(true)
{
	Cortex::setRun(&isRunning);
}


Brain::~Brain()
{
}
