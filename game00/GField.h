#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <box2d/box2d.h>
class GField
{
public:
	void SetSize(const sf::Vector2f& size);
	const sf::Vector2f& GetSize()const;

	void SetScale(const sf::Vector2f& scale);
	const sf::Vector2f& GetScale() const;

	void SetPosition(const sf::Vector2f& position);
	const sf::Vector2f& GetPosition() const;

	void SetTextureName(const std::string& textureName);
	const std::string GetTextureNameS() const;

private:
	sf::Vector2f Size;
	sf::Vector2f Scale;
	sf::Vector2f Position;
	std::string TextureName = "" ;

	b2Body* body;
};

