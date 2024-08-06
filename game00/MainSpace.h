#pragma once
#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Controls.h"
#include "button.h"
#include "ToolBar.h"
#include "FieldsColletction.h"
#include "InfoBar.h"
#include "ProjectHandler.h"

class MainSpace
{
public:
	void Core(); // main loop
private:
	void Render(sf::RenderTarget& target, Renderer& renderer,ResourceManager& manager);// rendering
	void ControlsForFields(sf::Event& event, sf::RenderWindow& window, Controls controls);// actions for fields
	void ControlsForHitbox(sf::Event& event,sf::RenderWindow& window, Controls controls);// actions for hitboxes
	bool openProject();

	bool Drag = false;// if mouse is moving
	bool selected = false;//if elemnt is selected from collection(elements0
	bool HitboxAdd = false;//if adding hitbox
	bool showHitboxes = false;
	bool isHitboxSelected = false;

	sf::View view;// main view
	sf::View ToolBarView;
	sf::View InfoBarView;
	sf::Vector2f NewPos;
	sf::Vector2f OldPos;	
	sf::Font font;

	std::vector<sf::Vector2f> convexShapeCordinats;

	ProjectHandler projectHandler;

	ToolBar toolBar;
	InfoBar infoBar;
	FieldsColletction Elements;//collection

	poly* polygonPtr;
	recta* rectanglePtr;
	convex* irregularPtr;

	int ElementSelected= -1;
	int action;//what you want to do i dont know how to use enum 
};

