#include "GRenderer.h"

GRenderer::GRenderer(sf::RenderTarget& target)
	:RrenderTarget(target)
{
}

void GRenderer::draw(const GField& field, const ResourceManager& manager)
{
    sf::Sprite s;
    sprite = s;
    if (field.GetTextureNameS()!= "" )
    {
        sf::Texture txt;
        txt = manager.GetResource(field.GetTextureNameS());

        float ScaleOfX = field.GetSize().x / txt.getSize().x;
        float ScaleOfY = field.GetSize().y / txt.getSize().y;
        sprite.setScale(ScaleOfX, ScaleOfY);
        txt.setSmooth(true);
        sprite.setPosition(field.GetPosition());
        sprite.setTexture(txt);

        RrenderTarget.draw(sprite);
    }
}

