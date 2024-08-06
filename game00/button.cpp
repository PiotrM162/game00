#include "button.h"

button::button(std::string txt, sf::Vector2f size, int charsiz, sf::Color BgColor, sf::Color txtColor)
{
	text.setString(txt);
	text.setFillColor(txtColor);

	Button.setFillColor(BgColor);
	Button.setSize(size);

	text.setOutlineThickness(0.5f);
	text.setOutlineColor(sf::Color::Black);
}

button::button(std::string txt, sf::Vector2f size, int charsize, sf::Color BgColor, sf::Color txtColor, sf::Font& font, sf::Vector2f pos)
{
	Button.setFillColor(BgColor);
	Button.setSize(size);
	Button.setPosition(pos);

	text.setFont(font);
	text.setString(txt);
	text.setFillColor(txtColor);
	text.setLetterSpacing(1.2f);
	text.setOutlineThickness(0.35);
	text.setOutlineColor(txtColor);
	text.setCharacterSize(charsize);
	//text.setScale({ 0.8f,0.2f });

	float xPos = ((pos.x + Button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2));
	float yPos = ((pos.y + Button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 1.5));
	text.setPosition({ xPos,yPos });
}

void button::setFont(sf::Font& font)
{
	text.setFont(font);
}

void button::setBgColor(sf::Color color)
{
	Button.setFillColor(color);
}

void button::setTxtColor(sf::Color color)
{
	text.setFillColor(color);
}

void button::setPosition(sf::Vector2f pos)
{
	Button.setPosition(pos);

	float xPos = ((pos.x + Button.getLocalBounds().width / 2) - (text.getLocalBounds().width / 2));
	float yPos = ((pos.y + Button.getLocalBounds().height / 2) - (text.getLocalBounds().height / 1.5));
	text.setPosition({ xPos,yPos });
}

void button::setSclae(sf::Vector2f pos)
{
	Button.setScale(pos);

	float xPos = ((Button.getPosition().x + Button.getLocalBounds().width / 1.9) - (text.getLocalBounds().width ));
	float yPos = ((Button.getPosition().y + Button.getLocalBounds().height / 1.9) - (text.getLocalBounds().height ));
	text.setPosition({ xPos,yPos });
	text.setScale(pos);
}

void button::draw(sf::RenderTarget& target)
{
	target.draw(Button);
	target.draw(text);
}

bool button::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float buttonX = Button.getPosition().x;
	float buttonY = Button.getPosition().y;

	float buttonEndX = Button.getPosition().x + Button.getLocalBounds().width;
	float buttonEndY = Button.getPosition().y + Button.getLocalBounds().height;

	if (mouseX <buttonEndX && mouseX > buttonX && mouseY < buttonEndY && mouseY > buttonY)
	{
		return true;
	}
	return false;
}

bool button::isMouseOver(sf::RenderWindow& window, sf::Vector2f worldPos)
{
	if (Button.getGlobalBounds().contains(worldPos))
	{
		return true;
	}
	return false;
}

void button::setText(std::string txt)
{
	text.setString(txt);
}

sf::RectangleShape button::DrawButton()
{
	return Button;
}

sf::Text button::DrawTXT()
{
	return text;
}
