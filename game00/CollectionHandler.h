#pragma once
#include <string>
#include "FieldsColletction.h"
class CollectionHandler
{
public:
	CollectionHandler(std::string Path);
	void saveCollection(FieldsColletction collection);
	void loadCollection(FieldsColletction& collection);
private:
	std::string path;
};

