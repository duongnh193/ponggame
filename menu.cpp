#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "include/menu.hpp"

button::button (const std::string& str, const sf::Color& buttonColor, const sf::Color& textColor, float textCharSize, const sf::Vector2f& buttonSize, const sf::Vector2f& position)
:       isHovered(false),
        isSelected(false),
        str(str),
        buttonColor(buttonColor),
        textColor(textColor),
        textCharSize(textCharSize),
        buttonSize(buttonSize),
        position(position) 
{
        init();
}

void button::init () 
{
        if (!fontObj.loadFromFile("/home/duongnh/Projects/Qt/SFML/bin/gfx/font/november.ttf"))
                return;
        buttonObj.setFillColor(buttonColor);
        buttonObj.setSize(buttonSize);
        buttonObj.setOrigin(buttonObj.getSize().x/2.0f, buttonObj.getSize().y/2.0f);
        buttonObj.setPosition(position);
        textObj.setString(str);
        textObj.setFont(fontObj);
        textObj.setFillColor(textColor);
        textObj.setCharacterSize(textCharSize);
        textObj.setOrigin(textObj.getGlobalBounds().width/2.0f, textObj.getGlobalBounds().height/2.0f);
        textObj.setPosition(buttonObj.getPosition());
}

menu::menu (sf::RenderWindow& renderWin/*, soundManager& sManager*/)
:       isPlaying(false),
        isMenu(true),
        renderWin(renderWin)
        // sManager(sManager)
{
        init();
}

void menu::init () 
{
        if (!gameLogo.loadFromFile("/home/duongnh/Projects/Qt/SFML/bin/gfx/game-logo.png")) return;
        if (!mouseTexture.loadFromFile("/home/duongnh/Projects/Qt/SFML/bin/gfx/mouse-pointer.png")) return;
        if (!menuBackground.loadFromFile("/home/duongnh/Projects/Qt/SFML/bin/gfx/menu-background.png")) return;
        gameLogoTexture.loadFromImage(gameLogo);
        gameLogoSprite.setTexture(gameLogoTexture);
        mouseSprite.setTexture(mouseTexture);
        mouseSprite.setOrigin(sf::Vector2f(mouseSprite.getGlobalBounds().width/2.0f, mouseSprite.getGlobalBounds().height/2.0f));
        mouseSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(renderWin).x, sf::Mouse::getPosition(renderWin).y));
        menuTexture.loadFromImage(menuBackground);
        menuSprite.setTexture(menuTexture);
        createButton(menuButtons, "Player vs. CPU", sf::Color(0, 0, 0, 80), sf::Color::White, 30.0f, sf::Vector2f(280.0f, 80.0f), sf::Vector2f(180.0f, 240.0f));
        createButton(menuButtons, "Player vs. Player", sf::Color(0, 0, 0, 80), sf::Color::White, 30.0f, sf::Vector2f(280.0f, 80.0f), sf::Vector2f(480.0f, 240.0f));
        createButton(menuButtons, "Set Score", sf::Color(0, 0, 0, 80), sf::Color::White, 30.0f, sf::Vector2f(160.0f, 80.0f), sf::Vector2f(130.0f, 380.0f ));
        createButton(menuButtons, "Exit", sf::Color(0, 0, 0, 80), sf::Color::White, 30.0f, sf::Vector2f(160.0f, 80.0f), sf::Vector2f(530.0f, 380.0f));
        createButton(menuButtons, "Level", sf::Color(0, 0, 0, 80), sf::Color::White, 30.0f, sf::Vector2f(160.0f, 80.0f), sf::Vector2f(340.0f, 380.0f));
}

void menu::mouseSelect (std::vector<std::unique_ptr<button>>& listObj, const sf::Color& hoverButtonColor, const sf::Color& hoverTextColor) 
{
    sf::Vector2i mousePos = mouse.getPosition(renderWin);
    for (auto iter = listObj.begin(); iter != listObj.end(); iter++) 
    {
        button* pButton = iter->get();
        if (mousePos.x > pButton->buttonObj.getGlobalBounds().left &&
            mousePos.x < pButton->buttonObj.getGlobalBounds().left+pButton->buttonObj.getGlobalBounds().width &&
            mousePos.y > pButton->buttonObj.getGlobalBounds().top &&
            mousePos.y < pButton->buttonObj.getGlobalBounds().top+pButton->buttonObj.getGlobalBounds().height) 
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
            {
                // sManager.playAudio("select");
                pButton->isSelected = true;
            } 
            else if (pButton->isHovered) 
            {
                pButton->buttonObj.setFillColor(hoverButtonColor);
                pButton->textObj.setFillColor(hoverTextColor);
            } 
            else 
            {
                isPlaying = true;
                pButton->isHovered = true;
            }
        } 
        else 
        {
            pButton->buttonObj.setFillColor(pButton->buttonColor);
            pButton->textObj.setFillColor(pButton->textColor);
            pButton->isHovered = false;
            pButton->isSelected = false;
        }
    }
    if (isPlaying) 
    {
        // sManager.playAudio("blip");
        isPlaying = false;
    }
}

std::string menu::checkSelected ()
{
    for (auto iter = menuButtons.begin(); iter != menuButtons.end(); iter++) 
    {
        button* pButton = iter->get();
        if (pButton->isSelected) 
        {
            pButton->isSelected = false;
            return pButton->str;
        }
    }
    return "";
}

void menu::update () 
{
    mouseSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(renderWin).x,
                                         sf::Mouse::getPosition(renderWin).y));
    if (isMenu)
        mouseSelect(menuButtons, sf::Color(255, 255, 255, 80), sf::Color::Black);
}

void menu::renderMenu (std::vector<std::unique_ptr<button>>& listObj) 
{
        for (auto iter = listObj.begin(); iter != listObj.end(); iter++) 
        {
                button* btn = iter->get();
                renderWin.draw(btn->buttonObj);
                renderWin.draw(btn->textObj);
        }
}

void menu::render () 
{
    if (isMenu) 
    {
        renderWin.draw(menuSprite);
        renderWin.draw(gameLogoSprite);
        renderMenu(menuButtons);
        renderWin.draw(mouseSprite);
    }
}

void menu::createButton (std::vector<std::unique_ptr<button>>& listObj,
                         const std::string& str,
                         const sf::Color& buttonColor,
                         const sf::Color& textColor,
                         float textCharSize,
                         const sf::Vector2f& buttonSize,
                         const sf::Vector2f& position) 
{
        listObj.push_back(std::make_unique<button>(
                str,
                buttonColor,
                textColor,
                textCharSize,
                buttonSize,
                position
        ));
}
