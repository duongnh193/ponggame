#include <SFML/Graphics.hpp>
#include "include/background.hpp"

Background::Background (sf::RenderWindow& renderWin, sf::Vector2f initPos)
:       pos(initPos), 
        renderWin(renderWin) 
{
        init();
}

void Background::init () 
{
        if (!image.loadFromFile("/home/duongnh/Projects/Qt/SFML/bin/gfx/background.png")) return;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x/2.0f, texture.getSize().y/2.0f);
        sprite.setPosition(pos);
}

void Background::update () 
{
        sprite.setTexture(texture);
}

void Background::render () 
{
        renderWin.draw(sprite);
}
