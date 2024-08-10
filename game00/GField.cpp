#include "GField.h"

void GField::SetSize(const sf::Vector2f& size)
{
	Size = size;
}

const sf::Vector2f& GField::GetSize() const
{
	return Size;
}

void GField::SetScale(const sf::Vector2f& scale)
{
	Scale = scale;
}

const sf::Vector2f& GField::GetScale() const
{
	return Scale;
}

void GField::SetPosition(const sf::Vector2f& position)
{
	Position = position;
}

const sf::Vector2f& GField::GetPosition() const
{
	return Position;
}

void GField::SetTextureName(const std::string& textureName)
{
	TextureName = textureName;
}

const std::string GField::GetTextureNameS() const
{
	return TextureName;
}
