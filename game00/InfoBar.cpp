#include "InfoBar.h"
#include <iostream>

void InfoBar::Initialize(sf::Font& font)
{
	// buttons 
	button bt("position X: ", { 100.f,40.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 49890.f, 49620.f });
	Buttons.insert({ "PosX", bt });

	button bt1("position Y: ", { 100.f,40.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 49890.f, 49670.f });
	Buttons.insert({ "PosY", bt1 });

	button bt2("size X: ", { 100.f,40.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 49890.f, 49720.f });
	Buttons.insert({ "sizeX", bt2 });

	button bt3("size Y: ", { 100.f,40.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 49890.f, 49770.f });
	Buttons.insert({ "sizeY", bt3 });

	button bt5("Rotation ", { 100.f,40.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 49890.f, 49820.f });
	Buttons.insert({ "rotation", bt5 });
	
	button bt6("Texture ", { 100.f,40.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 49890.f, 49920.f });
	Buttons.insert({ "texture", bt6 });
	
	button bt7("ESCAPE ", { 100.f,40.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 49950.f, 50100.f });
	escape = bt7;

	button bt4("ENTER ", { 100.f,40.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 49950.f, 50100.f });
	Buttons.insert({ "enter", bt4 });

	// textboxes
	TBpositionX.set(18, sf::Color::Black);
	  
	TBpositionX.steFont(font);
	TBpositionX.setPosition({ 50000.f,49625.f });
	TBpositionX.setOutLine({ 120.f,40.f });
	TBpositionX.setOutColor(sf::Color::Black);
	TBpositionX.setText("xxx");
	TBpositionX.setSelected(true);
	  
	TBpositionY.set(18, sf::Color::Black);
		
	TBpositionY.steFont(font);
	TBpositionY.setPosition({ 50000.f,49675.f });
	TBpositionY.setOutLine({ 120.f,40.f });
	TBpositionY.setOutColor(sf::Color::Black);
	TBpositionY.setText("xxx");
	TBpositionY.setSelected(true);


	TBsizeX.set(18, sf::Color::Black);
	  
	TBsizeX.steFont(font);
	TBsizeX.setPosition({ 50000.f,49725.f });
	TBsizeX.setOutLine({ 120.f,40.f });
	TBsizeX.setOutColor(sf::Color::Black);
	TBsizeX.setText("xxx");
	TBsizeX.setSelected(true);
	  
	TBsizeY.set(18, sf::Color::Black);
	  
	TBsizeY.steFont(font);
	TBsizeY.setPosition({ 50000.f,49775.f });
	TBsizeY.setOutLine({ 120.f,40.f });
	TBsizeY.setOutColor(sf::Color::Black);
	TBsizeY.setText("xxx");
	TBsizeY.setSelected(true);
	
	TBrotation.set(18, sf::Color::Black);
	  
	TBrotation.steFont(font);
	TBrotation.setPosition({ 50000.f,49825.f });
	TBrotation.setOutLine({ 120.f,40.f });
	TBrotation.setOutColor(sf::Color::Black);
	TBrotation.setText("xxx");
	TBrotation.setSelected(true);

}

void InfoBar::DrawInfoBar(sf::RenderTarget& target, ResourceManager resources)
{
	sf::RectangleShape back;//background 
	back.setFillColor(sf::Color::Blue);
	back.setSize(sf::Vector2f(800.f, 1200.f));
	back.setPosition(49400.f, 49600.f);
	target.draw(back);

	if(!SelTexture)
	{

		sf::Sprite textureSample;
		sf::Texture txt = resources.GetResource(texture);
		txt.setSmooth(true);
		textureSample.setTexture(txt);
		textureSample.setPosition(50000.f, 49920.f);

		float ScaleOfX = static_cast<float>(100.f) / txt.getSize().x;
		float ScaleOfY = static_cast<float>(100.f) / txt.getSize().y;
		textureSample.setScale(ScaleOfX, ScaleOfY);
		for (auto i : Buttons)
		{
			i.second.draw(target);
		}

		TBpositionX.draw(target);
		TBpositionY.draw(target);
		TBsizeX.draw(target);
		TBsizeY.draw(target);
		TBrotation.draw(target);
		target.draw(textureSample);
	}
	else
	{
		int index=0;
		int index2 = 0;
		for ( auto i : resources.getResources())
		{
			if (index2 >= scrool)
			{
				if (index < SelResources.size())
				{
					sf::Texture txt = i.second;
			
					txt.setSmooth(true);
			
					SelResources.at(index).name = i.first;
					SelResources.at(index).sprite.setTexture(txt);
					SelResources.at(index).empty = false;
			
					float ScaleOfX = static_cast<float>(100.f) / txt.getSize().x;
					float ScaleOfY = static_cast<float>(100.f) / txt.getSize().y;
			
					SelResources.at(index).sprite.setScale(ScaleOfX, ScaleOfY);

					escape.draw(target);

					target.draw(SelResources.at(index).sprite);
					index++;
				}
			}
			index2++;

		}

	}
}

void InfoBar::FieldInfo(Field& field)
{

	TBpositionX.setText(std::to_string(field.GetPosition().x));
	TBpositionY.setText(std::to_string(field.GetPosition().y));
	TBsizeX.setText(std::to_string(field.GetSize().x));
	TBsizeY.setText(std::to_string(field.GetSize().y));
	TBrotation.setText(std::to_string(field.GetRotation()));
	field.GetTextureName(texture);
}

bool InfoBar::Controls(sf::Event event, sf::RenderWindow& window)
{	
	if(!SelTexture)
	{
		if (event.type == sf::Event::TextEntered)// typing if selected before 
		{
			TBpositionX.type(event);
			TBpositionY.type(event);
			TBsizeX.type(event);
			TBsizeY.type(event);
			TBrotation.type(event);
		}
		if (event.type == sf::Event::MouseButtonPressed)//on pressing mouse button
		{

			if (event.key.code == sf::Mouse::Left)//on pressing mouse button left
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

				TBpositionX.isMouseOver(window, worldPos);
				TBpositionY.isMouseOver(window, worldPos);
				TBsizeX.isMouseOver(window, worldPos);
				TBsizeY.isMouseOver(window, worldPos);
				TBrotation.isMouseOver(window, worldPos);

				if (Buttons["texture"].isMouseOver(window, worldPos))
				{
					SelTexture = true;
					initializeSelecting();
				}

				if (Buttons["enter"].isMouseOver(window, worldPos))
				{
					enter = true;
					return true;
				}
			}
		}
	}
	else
	{
		if (event.type == sf::Event::MouseButtonPressed)//on pressing mouse button
		{

			if (event.key.code == sf::Mouse::Left)//on pressing mouse button left
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

				if (escape.isMouseOver(window, worldPos))
				{
					SelTexture = false;
					destroySelecting();
				}

				for (auto i : SelResources)
				{
					if (!i.empty)
					{
						if (i.sprite.getGlobalBounds().contains(worldPos))
						{
							texture = i.name;
							SelTexture = false;
							enter = true;
							destroySelecting();
							return true;
						}
					}
				}
			}
		}
		if (event.type == sf::Event::MouseWheelScrolled)//zoom operations
		{
			if (event.mouseWheelScroll.delta > 0 && scrool >= 0)
			{
				scrool -= 2;
				initializeSelecting();
			}
			else if (event.mouseWheelScroll.delta < 0 && !SelResources.at(3).empty)
			{
				initializeSelecting();
				scrool += 2;
			}
		}
	}
	return false;
}

void InfoBar::updateField(Field& upField)
{
	if (enter)
	{
		enter = false;
		
		float posX = std::stof(TBpositionX.getText());
		float posY = std::stof(TBpositionY.getText());
		float sizeX = std::stof(TBsizeX.getText());
		float sizeY = std::stof(TBsizeY.getText());
		float rotation = std::stof(TBrotation.getText());

		upField.SetPosition({ posX,posY });
		upField.SetSize({ sizeX,sizeY });
		upField.SetRotation(rotation);
		upField.SetTextureName(texture);
	}
}

void InfoBar::initializeSelecting()
{
	SelResources.clear();
	bool pos = false;
	float posX = 50010;
	float posY = 49620.f;
	int a=0;
	for (int i = 0; i < 8; i++)
	{
		if (pos)
		{
			posX += 120.f;
			pos = false;
		}
		else
		{
			posX -= 120.f;
			pos = true;
		}
		if (i == a + 2)
		{
			posY += 120;
			a = i;
		}
		sf::Sprite sprite;
		sprite.setPosition({ posX,posY });
		SelRes a;
		a.sprite = sprite;
		SelResources.push_back(a);
	}
	
	
}

void InfoBar::destroySelecting()
{
	SelResources.clear();
}
