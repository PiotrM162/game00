#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "textbox.h"
#include "button.h"
#include <map>
#include <string>
#include "ResourceManager.h"

struct SelRes
{
	sf::Sprite sprite;
	std::string name = "";
	bool empty = true;
};

class InfoBar
{
public:
	void Initialize(sf::Font& font);// setting up elements
	void DrawInfoBar(sf::RenderTarget& target, ResourceManager resources);//
	void FieldInfo(Field& field);// it should be pointer but i dont know how to use them yet(there is a lot to lern)
	bool Controls(sf::Event event, sf::RenderWindow& window);//
	void updateField(Field& upField);// 
	void initializeSelecting();
	void destroySelecting();
private:
	std::map<std::string, button> Buttons;//every button
	std::vector<SelRes> SelResources;// option to select	
									 //TB is short for text box
	textbox TBsizeX;// size of field // i dont know why it dosent work in map 
	textbox TBsizeY;
	textbox TBpositionX;//position of field
	textbox TBpositionY;
	textbox TBrotation;

	std::string texture;

	button escape;

	bool SelTexture = false;// mode of selecting texture for field
	bool enter=false;//signal for updating field

	int scrool=0;
};

