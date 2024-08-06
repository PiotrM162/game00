#include "ProjectHandler.h"
#include "filesHandler.h"

void ProjectHandler::CreateDirectoryTree(std::string projectName)
{
	filesHandler fHandler;

	std::string folderPath = fHandler.getfolderPath();

	fHandler.createfolder(folderPath, projectName);
	mainFolder = folderPath + "/" + projectName;

	texturesFolder = mainFolder + "/textures";
	fHandler.createfolder(mainFolder, "textures");

	fHandler.createJsonFile(texturesFolder, "textures");
	texturesFile = texturesFolder + "/textures.json";

	MapFolder = mainFolder + "/Map";
	fHandler.createfolder(mainFolder, "Map");

	fHandler.createJsonFile(MapFolder, "Map");
	MapFile = MapFolder + "/Map.json";
	
	gameLogicFolder = mainFolder + "/GameLogic";
	fHandler.createfolder(mainFolder, "GameLogic");
	
	fHandler.createJsonFile(gameLogicFolder, "GameLogic");
	 

}

void ProjectHandler::openProject()
{
	filesHandler fHandler;

	std::string folderPath = fHandler.getfolderPath();

	mainFolder = folderPath ;

	texturesFolder = mainFolder + "/textures";

	MapFolder = mainFolder + "/Map";

	gameLogicFolder = mainFolder + "/GameLogic";

	texturesFile = texturesFolder + "/textures.json";

	MapFile = MapFolder + "/Map.json";
}

const std::string ProjectHandler::getTexturesFile() const
{
	return texturesFile;
}

const std::string ProjectHandler::getMapFile() const
{
	return MapFile;
}
