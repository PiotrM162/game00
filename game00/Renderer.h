#pragma once
#include<SFML/Graphics.hpp>
#include"Field.h"
#include"ResourceManager.h"
class Renderer
{
public:
	Renderer(sf::RenderTarget &target);
	void draw(const Field& field,const ResourceManager& manager,bool selected);
	void drawHitbox(const Field& field, const ResourceManager& manager);
	sf::RenderTarget& Target;
private:
	sf::Sprite sprite{};
};

