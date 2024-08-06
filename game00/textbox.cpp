#include "textbox.h"

textbox::textbox(int size, sf::Color color, bool selected)
{
	Textbox.setCharacterSize(size);
	Textbox.setFillColor(color);
	Textbox.setOutlineColor(color);
	isSelected = selected;
	Textbox.setLetterSpacing(1.2f);
	Textbox.setOutlineThickness(0.35);

}

void textbox::set(int size, sf::Color color)
{
	Textbox.setCharacterSize(size);
	Textbox.setFillColor(color);
	Textbox.setOutlineColor(color);
	Textbox.setLetterSpacing(1.2f);
	Textbox.setOutlineThickness(0.35);
}

void textbox::steFont(sf::Font& font)
{
	Textbox.setFont(font);
}

void textbox::setPosition(sf::Vector2f pos)
{
	Textbox.setPosition(pos);
}

void textbox::setSelected(bool sel)
{
	isSelected = sel;
	if (!sel)
	{
		std::string t = text.str();
		std::string newt = "";
		for (int i = 0; i < t.length(); i++)
		{
			newt += t[i];
		}
		Textbox.setString(newt);
	}

}

void textbox::draw(sf::RenderWindow& window)
{
	window.draw(Button);
	window.draw(Textbox);
}

void textbox::draw(sf::RenderTarget& target)
{
	target.draw(Button);
	target.draw(Textbox);
}

void textbox::type(sf::Event input)
{
	if (isSelected)
	{
		int chartyped = input.text.unicode;
		if (chartyped < 128)
		{
			if (hasLimit)
			{
				if (text.str().length() <= limit)
				{
					inputLogic(chartyped);
				}
				if (text.str().length() > limit && chartyped == DELETE_KEY)
				{
					deleteLastChar();
				}
			}
			else
			{
				inputLogic(chartyped);
			}
		}
	}
}

void textbox::setText(std::string txt)
{
	text.str("");
	text << txt;
	Textbox.setString(text.str());
}

void textbox::paste(std::string Paste)
{
	if (isSelected)
	{
		text.str("");
		text << Paste;
	}

}

void textbox::setOutLine(sf::Vector2f size)
{
	Button.setSize(size);
	Button.setFillColor(sf::Color::Color(156, 156, 166, 255));
	Button.setOutlineThickness(2.f);
	Button.setPosition({ Textbox.getPosition().x - 5.f,Textbox.getPosition().y - 5.f });
}

bool textbox::isMouseOver(sf::RenderWindow& window)
{
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float buttonX = Button.getPosition().x;
	float buttonY = Button.getPosition().y;

	float buttonEndX = Button.getPosition().x + Button.getLocalBounds().width;
	float buttonEndY = Button.getPosition().y + Button.getLocalBounds().height;

	if (mouseX <buttonEndX && mouseX > buttonX && mouseY < buttonEndY && mouseY > buttonY)
	{
		isSelected = true;
		return true;
	}
	isSelected = false;
	return false;
}

bool textbox::isMouseOver(sf::RenderWindow& window, sf::Vector2f worldPos)
{
	if (Button.getGlobalBounds().contains(worldPos))
	{
		isSelected = true;
		return true;
	}
	isSelected = false;
	return false;
}

void textbox::setOutColor(sf::Color color)
{
	Button.setOutlineColor(color);
}

void textbox::getText(std::string& text)
{
	text = Textbox.getString();
}

bool textbox::getSelected()
{
	if (isSelected)
		return true;
	return false;
}

void textbox::inputLogic(int chartyped)
{
	if (chartyped != DELETE_KEY && chartyped != ENTER_KEY && chartyped != ESCAPE_KEY)
		text << static_cast<char>(chartyped);
	else if (chartyped == DELETE_KEY)
	{
		if (text.str().length() > 0)
		{
			deleteLastChar();
		}
	}
	Textbox.setString(text.str());
}

void textbox::deleteLastChar()
{
	std::string t = text.str();
	std::string newt;
	for (int i = 0; i < t.length() - 1; i++)
	{
		newt += t[i];
	}
	text.str("");
	text << newt;
}
