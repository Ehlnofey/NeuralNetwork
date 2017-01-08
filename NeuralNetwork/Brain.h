#pragma once

class Cortex;

class Brain
{
public:
	Brain();
	bool run();
	~Brain();

private:
	WritingInterface *m_writingInterface;
	bool isRunning;
	bool learnningMod;
	int count;
};

