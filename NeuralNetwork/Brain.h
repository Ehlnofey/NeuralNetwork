#pragma once

class Cortex;

class Brain
{
public:
	Brain();
	~Brain();

private:
	Interface m_writingInterface;
	bool isRunning;
};

