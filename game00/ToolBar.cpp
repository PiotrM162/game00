#include "ToolBar.h"
#include"Field.h"



ToolBar::ToolBar()
{
}

void ToolBar::Initialize(sf::Font& font)// seting elements and adding them to map
{
	button bt("add", { 60.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9510.f, 9985.f });
	button bt00("delete", { 60.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9580.f, 9985.f });
	button bt1("add hitbox ", { 112.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 10230.f, 9915.f });
	button bt2("show hitboxes", { 138.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 10360.f, 9915.f });
	button bt3("add sprite", { 126.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9650.f, 9985.f });

	button bt4("new project", { 120.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9510.f, 9915.f });
	button bt5("open project", { 120.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9640.f, 9915.f });

	Buttons.insert({ "BtAdd", bt });
	Buttons.insert({ "usun", bt00 });
	Buttons.insert({ "Bt1", bt1 });
	Buttons.insert({ "Bt2", bt2 });
	Buttons.insert({ "Bt3", bt3 });

	Buttons.insert({ "NewProject", bt4 });
	Buttons.insert({ "OpenProject", bt5 });

	button bt0("circle", { 60.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9705.f, 10055.f });
	button bt01("rectangle ", { 100.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9800.f, 10055.f });
	button bt02("triangle", { 100.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9950.f, 10055.f });
	button bt03("covex shape", { 126.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 10080.f, 10055.f });
	button bt04("cancel", { 64.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 10360.f, 10055.f });
	button bt05("modify", { 66.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 10250.f, 10055.f });
	button bt06("delete", { 64.f,36.f }, 18, sf::Color::Color(156, 156, 166, 255), sf::Color::Black, font, { 9600.f, 10055.f });

	shapes.insert({ "circle",bt0 });
	shapes.insert({ "rectangle",bt01 });
	shapes.insert({ "triangle",bt02 });
	shapes.insert({ "covex shape",bt03 });
	shapes.insert({ "cancel",bt04 });
	shapes.insert({ "modify",bt05 });
	shapes.insert({ "delete",bt06 });

}

void ToolBar::DrawToolBar(sf::RenderTarget& target)
{
	sf::RectangleShape back;//  background
	back.setFillColor(sf::Color::Color(61, 70, 75,255));
	back.setSize(sf::Vector2f(1200.f, 800.f));
	back.setPosition(9400.f, 9600.f);

	target.draw(back);
	for (auto i : Buttons)
	{
		i.second.draw(target);
	}
	if (shapeSelecting)
	{
		for (auto i : shapes)
		{
			i.second.draw(target);
		}
	}
}

ButtonActions ToolBar::Controls(sf::Event event, sf::RenderWindow& window, FieldsColletction& collection, bool selected)
{

	if (event.type == sf::Event::MouseButtonPressed)//on pressing mouse button
	{

		if (event.key.code == sf::Mouse::Left)//on pressing mouse button left
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			if (Buttons["BtAdd"].isMouseOver(window,worldPos))//adding new element to collection
			{
				Field f(sf::Vector2f(1.f, 1.8f), sf::Vector2f(160.f, 140.f));
				f.SetTextureName("player");
				collection.AddToCollection(f);
			}
			if (Buttons["usun"].isMouseOver(window, worldPos))//delete element from colection
			{
				return BA_Delete;
			}
			if (Buttons["Bt1"].isMouseOver(window, worldPos)&& selected)//add hitbox
			{
				if (!shapeSelecting)
				{
					shapeSelecting = true;
					ActionsOnHitbox = HA_None;
					return BA_AddHitbox;
				}

			}			
			if (Buttons["Bt2"].isMouseOver(window, worldPos))//show hide hitbox
			{
				return BA_ShowHitbox;
			}
			if (Buttons["Bt3"].isMouseOver(window, worldPos))//show hide hitbox
			{
				return BA_AddSprite;
			}
			if (Buttons["NewProject"].isMouseOver(window, worldPos))//create new project
			{
				return BA_CreateProject;
			}
			if (Buttons["OpenProject"].isMouseOver(window, worldPos))//open project
			{
				return BA_OpenProject;
			}
			if (shapeSelecting)
			{
				if (shapes["modify"].isMouseOver(window, worldPos))
				{
					ActionsOnHitbox = HA_Modyfi;
				}
				else if (shapes["cancel"].isMouseOver(window, worldPos))
				{
					ActionsOnHitbox = HA_None;
					shapeSelecting = false;
				}
				else if (shapes["circle"].isMouseOver(window, worldPos))
				{
					ActionsOnHitbox = HA_Circle;
				}
				else if (shapes["rectangle"].isMouseOver(window, worldPos))
				{
					ActionsOnHitbox = HA_Rectangle;
				}
				else if (shapes["triangle"].isMouseOver(window, worldPos))
				{
					ActionsOnHitbox = HA_Triangle;
				}
				else if (shapes["covex shape"].isMouseOver(window, worldPos))
				{
					ActionsOnHitbox = HA_Convex;
				}
				else if (shapes["delete"].isMouseOver(window, worldPos))
				{
					ActionsOnHitbox = HA_Delete;
				}
			}
		}
	}
	return BA_NoAction;
}
