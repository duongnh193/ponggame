#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "include/players.hpp"
#include "include/sound.hpp"

player::player (std::string id,
                std::string filepath,
                std::string shadowfilepath,
                sf::Vector2f initPos
                /*soundManager& sManager*/)
:       id(id),
        filepath(filepath),
        shadowfilepath(shadowfilepath),
        score(0),
        isMoving(true),
        isPlaying(false),
        speed(40.0f),
        velY(0.0f),
        accY(0.0f),
        fric(-0.9f),
        initPos(initPos),
        currPos(initPos),
        dir{false, false}
        // sManager(sManager)
{
    init();
}

void player::init () 
{
    if (!texture.loadFromFile(filepath)) return;
    if (!shadowTex.loadFromFile(shadowfilepath)) return;
    shadow.setTexture(shadowTex);
    shadow.setOrigin(shadowTex.getSize().x/2.0f, shadowTex.getSize().y/2.0f);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2.0f, texture.getSize().y/2.0f);
    sprite.setPosition(currPos);
    setSides();
}

void player::movement () 
{
    float elapsedTime = clock.getElapsedTime().asSeconds();
    if (dir.up) 
    {
        if (!isPlaying) 
        {
            // sManager.playAudio("player-move");
            isPlaying = true;
        }
        accY = -speed;
    } 
    else if (dir.down) 
    {
        if (!isPlaying) 
        {
            // sManager.playAudio("player-move");
            isPlaying = true;
        }
        accY = speed;
    } 
    else 
    {
        accY = velY * fric;
    }
    velY += accY;
    currPos.y += velY * elapsedTime + 0.5 * accY * std::pow(elapsedTime, 2);
    sprite.setPosition(currPos);
    if (id == "player1") 
    {
        shadow.setPosition(sf::Vector2f(sprite.getPosition().x-sprite.getGlobalBounds().width/4.0f,
                                        sprite.getPosition().y));
    } 
    else if (id == "player2") 
    {
        shadow.setPosition(sf::Vector2f(sprite.getPosition().x+sprite.getGlobalBounds().width/4.0f,
                                        sprite.getPosition().y));
    }
}

void player::collision () 
{
    if (side.top <= 0.0f) 
    {
        velY = 0.0f;
        currPos.y = currPos.y + 1;
        dir.up = false;
    } 
    else if (side.bottom >= 480.0f) 
    {
        velY = 0.0f;
        currPos.y = currPos.y - 1;
        dir.down = false;
    }
}

void player::restartPos () 
{
    currPos = initPos;
}

void player::update () 
{
    shadow.setTexture(shadowTex);
    sprite.setTexture(texture);
    setSides();
    if (isMoving) 
    {
        collision();
        movement();
    }
    clock.restart();
}

void player::setSides () 
{
    side = {sprite.getGlobalBounds().top,
            sprite.getGlobalBounds().top+texture.getSize().y,
            sprite.getGlobalBounds().left,
            sprite.getGlobalBounds().left+texture.getSize().x};
}

players::players (sf::RenderWindow& renderWin/*, soundManager& sManager*/):
        renderWin(renderWin)
        // sManager(sManager)
{
    init();
}

players::~players () 
{
    playersVec.clear();
}

void players::init () 
{
    playersVec.push_back(player("player1",
                                "/home/duongnh/Projects/Qt/SFML/bin/gfx/player1.png",
                                "/home/duongnh/Projects/Qt/SFML/bin/gfx/player-shadow.png",
                                sf::Vector2f(50.0f, 240.0f)
                                /*sManager*/));
    playersVec.push_back(player("player2",
                                "/home/duongnh/Projects/Qt/SFML/bin/gfx/player2.png",
                                "/home/duongnh/Projects/Qt/SFML/bin/gfx/player-shadow.png",
                                sf::Vector2f(590.0f, 240.0f)
                                /*sManager*/));
}

void players::setScore (std::string id, int score) 
{
    for (unsigned int i = 0; i < playersVec.size(); ++i)
    {
        if (id == playersVec.at(i).id) 
        {
            playersVec.at(i).score += score;
        }
    }
}
void players::resetScore () 
{

    for (unsigned int i = 0; i < playersVec.size(); ++i)
    {
            playersVec.at(i).score = 0;
    }
}

void players::move (std::string id, std::string dir) 
{
    for (unsigned int i = 0; i < playersVec.size(); ++i) 
    {
        if (id == playersVec.at(i).id) 
        {
            if (dir == "up") 
            {
                playersVec.at(i).dir = {true, false};
            } 
            else if (dir == "down"){
                playersVec.at(i).dir = {false, true};
            }
        }
    }
}

void players::stop (std::string id) 
{
    for (unsigned int i = 0; i < playersVec.size(); ++i) 
    {
        if (id == playersVec.at(i).id) 
        {
            playersVec.at(i).dir = {false, false};
        }
    }
}

void players::pause () 
{
    for (unsigned int i = 0; i < playersVec.size(); ++i) 
    {
        playersVec.at(i).isMoving = false;
        stop(playersVec.at(i).id);
    }
}

void players::resume () 
{
    for (unsigned int i = 0; i < playersVec.size(); ++i) 
    {
        playersVec.at(i).isMoving = true;
    }
}

void players::restart () 
{
    resetScore();
    for (unsigned int i = 0; i < playersVec.size(); ++i) 
    {
        playersVec.at(i).restartPos();
    }
}

void players::events () 
{
    stop("player1");
    stop("player2");
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
    {
        move("player1", "up");
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
    {
        move("player1", "down");
    } 
    else 
    {
        playersVec.at(0).isPlaying = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
    {
        move("player2", "up");
    } 
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
    {
        move("player2", "down");
    } 
    else 
    {
        playersVec.at(1).isPlaying = false;
    }
}

void players::updates () 
{
    for (unsigned int i = 0; i < playersVec.size(); ++i) 
    {
        playersVec.at(i).update();
    }
}

void players::renders () 
{
    for (unsigned int i = 0; i < playersVec.size(); ++i) 
    {
        renderWin.draw(playersVec.at(i).shadow);
        renderWin.draw(playersVec.at(i).sprite);
    }
}


