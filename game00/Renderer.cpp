#include "Renderer.h"
#include <string>
Renderer::Renderer(sf::RenderTarget& target)
	:Target(target)
{
}

void Renderer::draw(const Field& field,const ResourceManager& manager, bool selected)
{
    sf::RectangleShape outline;
    outline.setOutlineColor(sf::Color::Yellow);
    outline.setOutlineThickness(0.1f);
    outline.setFillColor(sf::Color::Transparent);
    outline.setPosition(field.GetPosition());
    outline.setSize(field.GetSize());
    outline.setRotation(field.GetRotation());
    
    if (selected)
    {
        outline.setOutlineColor(sf::Color::Red);
    }

    Target.draw(outline);

    std::string name;
    sf::Sprite s;
    sprite = s;
    if (field.GetTextureName(name))
    {
        sf::Texture txt;
        txt = manager.GetResource(name);
        
        float ScaleOfX = field.GetSize().x / txt.getSize().x;
        float ScaleOfY = field.GetSize().y / txt.getSize().y;
        sprite.setScale(ScaleOfX, ScaleOfY);
        txt.setSmooth(true);
        sprite.setTexture(txt);
        sprite.setPosition(field.GetPosition());
        sprite.setRotation(field.GetRotation());
        
        Target.draw(sprite);
    }
    
}

void Renderer::drawHitbox(const Field& field, const ResourceManager& manager)
{

    for (auto a : field.seetHitboxes().polygons)
    {
        Target.draw(a.polygons);
    }
    for (auto a : field.seetHitboxes().rectangles)
    {
        Target.draw(a.rectangles);
    }
    for (auto a : field.seetHitboxes().irregular)
    {
        Target.draw(a.irregular);
    }

}
