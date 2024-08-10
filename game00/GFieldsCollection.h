#pragma once
#include"GField.h"
#include<SFML/Graphics.hpp>
class GFieldsCollection
{
public:
	void GFinit(std::string path );
	const std::vector<GField>& GetFieldCollection() const;// getting whole collection not for modifing 
private:
	std::vector<GField> Collection;// collection of fields 
};

