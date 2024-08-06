#pragma once
#include <string>
class ProjectHandler// project data handler 
{
public:
	void CreateDirectoryTree(std::string projectName);
	void openProject();

	const std::string getTexturesFile() const;
	const std::string getMapFile() const ;


private:
	std::string mainFolder;

	std::string texturesFolder;
	std::string MapFolder;
	std::string gameLogicFolder;

	std::string texturesFile;
	std::string MapFile;

};

