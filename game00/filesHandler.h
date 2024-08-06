#pragma once
#include <string>

class filesHandler
{
public:
	std::string getfolderPath();
	std::string getFilePath();
	
	void createfolder(std::string path, std::string name);
	void createJsonFile(std::string path, std::string name);
};

