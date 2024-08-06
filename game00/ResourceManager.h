#pragma once
#include "json.hpp"
#include <map>
#include <string>
#include <SFML/Graphics.hpp>
class ResourceManager
{
public:
	ResourceManager(std::string Path);
	sf::Texture GetResource(std::string name) const;
	void AddResuorce(std::string name, std::string pathToTexture);
	void RemoveResource(std::string name);
	void LoadResource();
	void saveResource();
	const std::map<std::string, sf::Texture>& getResources();
private:
	std::map<std::string, sf::Texture> resources;
	std::map<std::string, std::string> pathOfResource;
	sf::Texture errorTXT;
	std::string path;
};

