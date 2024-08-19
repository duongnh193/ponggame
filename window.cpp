#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include "include/window.hpp"
#include "include/players.hpp"
#include "include/funcs.hpp"

// Main constructor of the window class
window::window (unsigned int x, unsigned int y, const std::string& titleName)
:   isAI(false),
    isGameActive(false),
    isRunning(true),
    renderWin(sf::VideoMode(x, y), titleName, sf::Style::Titlebar),
    gameMenu(renderWin/*, sManager*/),
    background(renderWin, sf::Vector2f(x/2.0f, y/2.0f)),
    _2players(renderWin/*, sManager*/),
    pongball(renderWin, _2players/*, sManager*/),
    AIplayer(_2players.playersVec.at(1), pongball) 
{
    init();
}

// Main destructor of the window class
window::~window () 
{
    scoresTxt.clear();
}

// Initialization of objects in the game
void window::init () 
{
    renderWin.setFramerateLimit(120);
    renderWin.setMouseCursorVisible(false);
    if (!font.loadFromFile("/home/duongnh/Projects/Qt/SFML/bin/gfx/font/november.ttf")) return;
    textInit(scoresTxt, 60.0f, sf::Color::White, sf::Vector2f(160.0f, 50.0f));
    textInit(scoresTxt, 60.0f, sf::Color::White, sf::Vector2f(480.0f, 50.0f));
    textInit(AITxt, 20.0f, sf::Color::Yellow, sf::Vector2f(350.0f, 440.0f));
    gameLoop();
}

void window::textInit (std::vector<std::unique_ptr<sf::Text>>& textVec, float characterSize, sf::Color color, sf::Vector2f pos) 
{
        std::unique_ptr<sf::Text> ptext = std::make_unique<sf::Text>();
        ptext->setFont(font);
        ptext->setCharacterSize(characterSize);
        ptext->setFillColor(color);
        ptext->setPosition(pos);
        textVec.push_back(std::move(ptext));
}

// Handles events
void window::events () 
{
    sf::Event event;
    while (renderWin.pollEvent(event)) 
    {
        if (event.type == sf::Event::KeyPressed) 
        {
            if (isGameActive) 
            {
                if (event.key.code == sf::Keyboard::Escape) 
                {
                    // sManager.playAudio("quit");
                    gameMenu.isMenu = true;
                    isGameActive = false;
                    pongball.restart();
                    _2players.restart();
                }
            }
        }
        _2players.events();
    }
}

void window::gameWin()
{
    if(isGameActive)
    {
        gameMenu.isMenu = true;
        isGameActive = false;
        pongball.restart();
        _2players.restart();
    }
}

void window::menuSelection () 
{
    const std::string& selected = gameMenu.checkSelected();
    if (selected == "Player vs. CPU" || selected == "Player vs. Player")
    {
        if (!isScore)
        {
            std::cout << "Set score before play" << std::endl;
            return;
        } else
        {
            if (selected == "Player vs. CPU")
            {
                isAI = true;
                gameMenu.isMenu = false;
                isGameActive = true;
                pongball.isMoving = false;
                pongball.isCounting = true;
                pongball.restart();
            }
            else if (selected == "Player vs. Player")
            {
                isAI = false;
                gameMenu.isMenu = false;
                isGameActive = true;
                pongball.isMoving = false;
                pongball.isCounting = true;
                pongball.restart();
            }
        }
    }
    else if (selected == "Exit") 
    {
        isRunning = false;
    }
    else if (selected == "Set Score"){
        setScoreLimit(renderWin);
    }
}

void window::updateScores () 
{
    // sf::Text* text;
    bool winnerFound = false;
    std::string winnerText;
        for (unsigned int i = 0; i < _2players.playersVec.size(); i++) 
        {
                sf::Text* txt = scoresTxt.at(i).get();
                txt->setString(funcs::intToStr(_2players.playersVec.at(i).score));
                txt->setOrigin(txt->getGlobalBounds().width/2.0f, txt->getGlobalBounds().height/2.0f);
                if(_2players.playersVec.at(i).score >= winScore ){
                    if (!winnerFound) {
                        winnerText = "Player " + std::to_string(i + 1) + " wins!";
                        winnerFound = true;
                    }
                    gameMenu.isMenu = true;
                    isGameActive = false;
                    pongball.restart();
                    _2players.restart();
                }
        }
        if (winnerFound) {

            sf::Text winnerDisplay;
            winnerDisplay.setFont(font);
            winnerDisplay.setCharacterSize(50);
            winnerDisplay.setFillColor(sf::Color::Red);
            winnerDisplay.setString(winnerText);
            winnerDisplay.setPosition(30, 160);

            sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Game Over");
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear();
                window.draw(winnerDisplay);
                window.display();
            }
        }
}

// Handles updates
void window::updates () 
{
        menuSelection();
        if (isGameActive)
        {
                updateScores();
                pongball.update();
                _2players.updates();
                if (isAI) 
                {
                        AITxt.back()->setString(AIplayer.status);
                        AIplayer.update();
                }
                background.update();
        }
        gameMenu.update();
}

void window::renderScores () 
{
        for (unsigned int i = 0; i < _2players.playersVec.size(); i++) 
        {
                sf::Text* txt = scoresTxt.at(i).get();
                renderWin.draw(*txt);
        }
}

// Handles render
void window::render () 
{
        renderWin.clear();
        gameMenu.render();
        if (isGameActive) 
        {
                sf::Text* txt = AITxt.back().get();
                background.render();
                renderWin.draw(*txt);
                renderScores();
                _2players.renders();
                pongball.render();
        }
        renderWin.display();
}

// Handles game loop
void window::gameLoop () 
{
    while (isRunning) 
    {
        events();
        updates();
        render();
    }
}

void window::setScoreLimit(sf::RenderWindow &window)
{
    InputBox inputBox(300, 50);
    // inputBox.box.setPosition(150, 200);

    bool validInput = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            inputBox.handleEvent(event, window);

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                int scoreLimit = std::stoi(inputBox.getInput());
                if (scoreLimit < 20)
                {
                    setWinningScore(scoreLimit);
                    isScore = true;
                    validInput = true;
                    break; // Thoát vòng lặp sau khi thiết lập xong
                }
                else
                {

                    std::cout << "Score limit out of range!!!" << std::endl;
                    std::cout << "Please enter a score number less than 20" << std::endl;

                    // Xóa nội dung của InputBox để người dùng nhập lại
                    inputBox.clearInput();
                }
            }
        }

        window.clear(sf::Color::Cyan);
        inputBox.render(window);
        window.display();

        if (validInput) {
            break; // Thoát vòng lặp sau khi thiết lập xong và đầu vào hợp lệ
        }
    }
}

void window::setWinningScore(int scoreLimit)
{
        winScore = scoreLimit;
}
