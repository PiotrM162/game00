#include "Field.h"
#include <iostream>
Field::Field(sf::Vector2f size, sf::Vector2f position)
	:Size(size),Position(position)
{
}

const sf::Vector2f& Field::GetSize() const
{
	return Size;
}

void Field::SetSize(sf::Vector2f size)
{
	Size = size;

}

const sf::Vector2f& Field::GetScale() const
{
	return Scale;
}

void Field::SetScale(sf::Vector2f scale)
{
	Scale = scale;

}

void Field::SetPosition(sf::Vector2f position)
{
	Position = position;

}

const sf::Vector2f& Field::GetPosition() const
{
	return Position;
}

bool Field::GetTextureName(std::string& textureName) const
{
	if (TextureName.empty())
	{
		return false;
	}
	textureName = TextureName;
	return true;
}

std::string Field::GetTextureNameS() const
{
	return TextureName;
}

void Field::SetRotation(float Rotation)
{
	rotation = Rotation;
}

const float& Field::GetRotation() const
{
	return rotation;
}

void Field::AddPolygon(sf::CircleShape& polygon, sf::Vector2f offset, sf::Vector2f startSize)
{
	poly a;
	a.offset = offset;
	a.polygons = polygon;
	a.startSize = startSize;
	hitboxes.polygons.push_back(a);
}

void Field::AddRectangle(sf::RectangleShape& rectangle, sf::Vector2f offset, sf::Vector2f startSize)
{
	recta a;
	a.offset = offset;
	a.rectangles = rectangle;
	a.startSize = startSize;
	hitboxes.rectangles.push_back(a);
}

void Field::Addcovex(sf::ConvexShape& irregular, sf::Vector2f offset, sf::Vector2f startSize)
{
	convex a;
	a.offset = offset;
	a.irregular = irregular;
	a.startSize = startSize;
	hitboxes.irregular.push_back(a);
}


Hitboxes& Field::GetHitboxes() 
{
	return hitboxes;
}

const Hitboxes& Field::seetHitboxes() const
{
	return hitboxes;
}

void Field::update()
{
	for (auto& i : hitboxes.irregular)
	{
		i.scale = { Size.x / i.startSize.x , Size.y / i.startSize.y };
		i.irregular.setScale(i.scale );
		i.irregular.setPosition({ Position.x + i.offset.x * i.scale.x , Position.y + i.offset.y * i.scale.y });
	}
	for (auto& i : hitboxes.polygons)
	{
		i.scale = { Size.x / i.startSize.x , Size.y / i.startSize.y };
		i.polygons.setScale(i.scale);
		i.polygons.setPosition({ Position.x + i.offset.x * i.scale.x , Position.y + i.offset.y * i.scale.y });
	}
	for (auto& i : hitboxes.rectangles)
	{
		i.scale = { Size.x / i.startSize.x , Size.y / i.startSize.y };
		i.rectangles.setScale(i.scale);
		i.rectangles.setPosition({ Position.x + i.offset.x * i.scale.x , Position.y + i.offset.y * i.scale.y });
	}
}

void Field::SetTextureName(std::string textureName)
{
	TextureName = textureName;

}

