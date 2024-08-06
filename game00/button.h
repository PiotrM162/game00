#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class button
{
public:
	button() {}
	button(std::string txt, sf::Vector2f size, int charsize, sf::Color BgColor, sf::Color txtColor);
	button(std::string txt, sf::Vector2f size, int charsize, sf::Color BgColor, sf::Color txtColor, sf::Font& font, sf::Vector2f pos);

	void setFont(sf::Font& font);
	void setBgColor(sf::Color color);
	void setTxtColor(sf::Color color);
	void setPosition(sf::Vector2f pos);
	void setSclae(sf::Vector2f pos);
	void draw(sf::RenderTarget& target);
	bool isMouseOver(sf::RenderWindow& window);
	bool isMouseOver(sf::RenderWindow& window,sf::Vector2f worldPos);
	void setText(std::string txt);

	sf::RectangleShape DrawButton();
	sf::Text DrawTXT();
private:
	sf::RectangleShape Button;
	sf::Text text;
};

