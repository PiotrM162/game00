#include "Controls.h"
#include <Windows.h>
#include <iostream>
#include <locale>
#include <codecvt>

Controls::Controls(sf::Event& Event, sf::RenderWindow& Window)
    :event(Event),window(Window)
{
}

void Controls::ControlsOnMainView(sf::View& view,bool& Drag,int& action ,sf::Vector2f& OldPos)//for main window (where abjects are placed)
{
    window.setView(view);

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);//mouse position in window

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Drag)// selesting witch action you wont 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))// change size
        {
            action = 3;
            Drag = true;
            OldPos = worldPos;

        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))// change camera
        {
            action = 1;
            Drag = true;
            OldPos = worldPos;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))// change position
        {

            if (worldPos.x < (positionOfSelectdElement.x + sizeOfSelectdElement.x) && worldPos.x > positionOfSelectdElement.x &&
                worldPos.y < (positionOfSelectdElement.y + sizeOfSelectdElement.y) && worldPos.x > positionOfSelectdElement.y
                )
            {
                action = 2;
                Drag = true;
                OldPos = worldPos;
            }


        }
        else// canceling 
        {
            action = 0;
            //selected = false;
        }

    }
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && Drag)//canceling change
    {
        Drag = false;
        action = 0;
        //selected = false;
    }


}

void Controls::Zoom(sf::View& view)
{
    window.setView(view);

    if (event.type == sf::Event::MouseWheelScrolled)//zoom operations
    {
        if (event.mouseWheelScroll.delta > 0)
        {
            view.zoom(0.9f);
            window.setView(view);
        }
        else if (event.mouseWheelScroll.delta < 0)
        {
            view.zoom(1.1f);
            window.setView(view);
        }

    }
}

void Controls::BoundryOfelemt(sf::Vector2f pos, sf::Vector2f size)
{
    positionOfSelectdElement = pos;
    sizeOfSelectdElement = size;
}

void Controls::BoundryOfelemt(sf::FloatRect glBounds)
{
    positionOfSelectdElement = { glBounds.left, glBounds.top };
    sizeOfSelectdElement = { glBounds.width,glBounds.height };

}
