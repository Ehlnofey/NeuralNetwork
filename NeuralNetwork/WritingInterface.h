#pragma once

class Interface;

class WritingInterface :
	public Interface
{
public:
	WritingInterface();
	virtual std::vector<double> getInfo();
	std::vector<double> convert(std::string s);
	virtual void learn();
	bool doYouReconizeThat(std::string s);
	virtual ~WritingInterface();

private:
	std::vector<std::string> m_database;
	const int IN_LENGTH;
};

