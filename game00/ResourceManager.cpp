#include "ResourceManager.h"
#include <iostream>
#include <fstream> 
#include "json.hpp"

using json = nlohmann::json;

ResourceManager::ResourceManager(std::string Path)
	:path(Path)
{
	errorTXT.loadFromFile("icon/not.png");
}



sf::Texture ResourceManager::GetResource(std::string name) const
{
	const auto& itr = resources.find(name);

	if (itr != resources.end())
		return itr->second;
	return errorTXT;
}

void ResourceManager::AddResuorce(std::string name, std::string pathToTexture)
{
	const auto& itr = resources.find(name);

	if (itr == resources.end())
	{
		sf::Texture txt;
		txt.setSmooth(true);
		txt.loadFromFile(pathToTexture);
		resources.insert({ name,txt });
		pathOfResource.insert({ name,pathToTexture});
	}

}

void ResourceManager::RemoveResource(std::string name)
{
	resources.erase(name);
	saveResource();
}

void ResourceManager::LoadResource()
{
	std::ifstream reader(path);
	json js;
	try
	{
		js = json::parse(reader);
	}
	catch (json::parse_error& ex)
	{
		std::cerr << "parse error at byte " << ex.byte << std::endl;
	}
	for (const auto& item : js.items())
	{
		std::string name = item.value()["name"].get<std::string>();
		std::string pathToTexture = item.value()["path"].get<std::string>();
		sf::Texture txt;
		txt.setSmooth(true);
		txt.loadFromFile(pathToTexture);
		resources.insert({ name,txt });
		pathOfResource.insert({ name,pathToTexture });
	}
}

void ResourceManager::saveResource()
{
	std::ofstream outfile(path);
	std::ofstream writer;
	writer.open(path);
	json js;
	outfile.close();
	int index = 0;
	for(auto i : pathOfResource)
	{
		std::string a = std::to_string(index);
		js[a]["name"] = i.first;
		js[a]["path"] = i.second;
			index++;
	}
	writer << js;
	writer.close();
}

const std::map<std::string, sf::Texture>& ResourceManager::getResources()
{
	return resources;
}
