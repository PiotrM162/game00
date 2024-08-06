#pragma once
#include<SFML/Graphics.hpp>
#include"button.h"
#include<map>
#include<string>
#include"FieldsColletction.h"

enum ButtonActions
{
	BA_NoAction = 0,
	BA_Add = 1,
	BA_Delete = 2,
	BA_AddHitbox = 3,
	BA_ShowHitbox = 4,
	BA_AddSprite = 5,
	BA_CreateProject = 6,
	BA_OpenProject = 7
};

enum hitboxActions
{
	HA_None = 0,
	HA_Circle = 1,
	HA_Rectangle = 2,
	HA_Triangle = 3,
	HA_Convex = 4,
	HA_Modyfi = 5,
	HA_Delete = 6
};

class ToolBar
{
public:
	ToolBar();
	void Initialize(sf::Font& font);// setting up elements
	void DrawToolBar(sf::RenderTarget& target);//drowing element
	ButtonActions Controls(sf::Event event, sf::RenderWindow& window,FieldsColletction& collection,bool selected);//controling elements
	hitboxActions ActionsOnHitbox = HA_None;
	bool shapeSelecting = false;
private:
	std::map<std::string, button> Buttons;// every button 
	std::map<std::string, button> shapes;// every button 
};

