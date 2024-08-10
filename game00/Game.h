#pragma once
#include <SFML/Graphics.hpp>
#include "ProjectHandler.h"
#include "GField.h"
#include "ResourceManager.h"
#include "GRenderer.h"
#include "GFieldsCollection.h"

class Game
{
public:
	Game(ProjectHandler& projectHandler);
	void GameLoop();

private:
	void update(float& deltatime);
	void render(sf::RenderTarget& target, const GFieldsCollection& collection, const ResourceManager& manager ,GRenderer& renderer );
	
	ProjectHandler& GprojectHandler;//G =game
};

