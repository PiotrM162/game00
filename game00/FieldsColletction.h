#pragma once
#include"Field.h"
#include<SFML/Graphics.hpp>
class FieldsColletction
{
public:
	void AddToCollection(Field field);
	void DleteFromCollection(int position);
	void Draw(sf::RenderTarget& target);
	Field& getField(size_t a);// getting single field
	const std::vector<Field>& GetFieldCollection() const;// getting whole collection not for modifing 
	void update();
private:
	std::vector<Field> Collection;// collection of fields 
};

