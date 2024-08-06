#pragma once
#include<SFML/Graphics.hpp>
#include<string>

struct poly
{
	sf::CircleShape polygons;
	sf::Vector2f offset;
	sf::Vector2f startSize;
	sf::Vector2f scale = { 1.f,1.f };
};
struct recta
{
	sf::RectangleShape rectangles;
	sf::Vector2f offset;
	sf::Vector2f startSize;
	sf::Vector2f scale = { 1.f,1.f };
};
struct convex
{
	sf::ConvexShape irregular;
	sf::Vector2f offset;
	sf::Vector2f startSize;
	sf::Vector2f scale = {1.f,1.f};
};

struct Hitboxes
{
	std::vector < poly> polygons;
	std::vector < recta> rectangles;
	std::vector < convex> irregular;
};
class Field
{
public:

	Field();
	Field(sf::Vector2f size,sf::Vector2f position);

	void SetSize(sf::Vector2f size);	
	const sf::Vector2f& GetSize()const;
	
	void SetScale(sf::Vector2f scale);	
	const sf::Vector2f& GetScale() const;

	void SetPosition(sf::Vector2f position);
	const sf::Vector2f& GetPosition() const;

	void SetTextureName(std::string textureName);
	bool GetTextureName(std::string& textureName) const;
	std::string GetTextureNameS() const;

	void SetRotation(float Rotation);
	const float& GetRotation()const;


	void AddPolygon(sf::CircleShape& polygon, sf::Vector2f offset, sf::Vector2f startSize);
	void AddRectangle(sf::RectangleShape& rectangle,sf::Vector2f offset, sf::Vector2f startSize);
	void Addcovex(sf::ConvexShape& irregular,sf::Vector2f offset, sf::Vector2f startSize);


	Hitboxes& GetHitboxes() ;
	const Hitboxes& seetHitboxes() const;

	void update();

private:
	sf::Vector2f Size;
	sf::Vector2f Scale;
	sf::Vector2f Position;
	std::string TextureName;
	
	Hitboxes hitboxes;

	float rotation =0;
};

