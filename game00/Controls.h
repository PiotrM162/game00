#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <shobjidl.h> 
class Controls
{
public:
	Controls(sf::Event& Event, sf::RenderWindow& Window);
	void ControlsOnMainView(sf::View& view, bool& Drag, int& action, sf::Vector2f& OldPos);// testing
	void Zoom(sf::View& view);// contoling view zoom by scrool
	void BoundryOfelemt(sf::Vector2f pos,sf::Vector2f size);
	void BoundryOfelemt(sf::FloatRect glBounds);
private:
	sf::Event& event;
	sf::RenderWindow& window;
	sf::Vector2f positionOfSelectdElement;
	sf::Vector2f sizeOfSelectdElement;
};

