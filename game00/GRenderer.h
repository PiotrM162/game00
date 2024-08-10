#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "GField.h"

class GRenderer
{
public:
	GRenderer(sf::RenderTarget& target);
	void draw(const GField& field, const ResourceManager& manager);
	sf::RenderTarget& RrenderTarget;// r == renderer 
private:
	sf::Sprite sprite{};
};

