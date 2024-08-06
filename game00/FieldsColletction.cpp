#include "FieldsColletction.h"
#include <SFML/Graphics.hpp>

void FieldsColletction::AddToCollection(Field field)
{
	Collection.push_back(field);
}

void FieldsColletction::DleteFromCollection(int position)
{
	Collection.erase(Collection.begin() + position);
}

void FieldsColletction::Draw(sf::RenderTarget& target)
{
	for (int i = 0; i < Collection.size(); i++)
	{
		Collection[i];
	}
}

Field& FieldsColletction::getField(size_t a)
{
	return Collection.at(a);
}

const std::vector<Field>& FieldsColletction::GetFieldCollection() const
{
	return Collection;
}

void FieldsColletction::update()
{
	for (auto& i : Collection)
	{
		i.update();
	}
}
