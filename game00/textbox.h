#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class textbox
{
public:
	textbox() {};
	textbox(int size, sf::Color color, bool selected);

	void set(int size, sf::Color color);

	void steFont(sf::Font& font);

	void setPosition(sf::Vector2f pos);

	void setSelected(bool sel);

	std::string getText() { return text.str(); }

	void setLimit(bool ToF, int lim) { hasLimit = ToF; limit = lim; }

	void draw(sf::RenderWindow& window);

	void draw(sf::RenderTarget& target);

	void type(sf::Event input);

	void setText(std::string txt);

	void paste(std::string Paste);

	void setOutLine(sf::Vector2f size);

	bool isMouseOver(sf::RenderWindow& window);

	bool isMouseOver(sf::RenderWindow& window, sf::Vector2f worldPos);


	void setOutColor(sf::Color color);

	void getText(std::string& text);

	bool getSelected();


private:

	sf::RectangleShape Button;
	sf::Text Textbox;
	std::ostringstream text;

	bool isSelected = false;
	int limit;
	bool hasLimit = false;

	void inputLogic(int chartyped);
	void deleteLastChar();
};

