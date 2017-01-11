#pragma once

class Interface;

class WritingInterface :
	public Interface
{
public:
	WritingInterface(bool out=false);
	virtual std::vector<double> getInfo();
	virtual	const std::vector<std::string>& getDatabase();
	static std::vector<double> convert(std::string s);
	virtual void learn();
	virtual ~WritingInterface();

private:
	std::vector<std::string> m_database;
	static const int IN_LENGTH;
};

