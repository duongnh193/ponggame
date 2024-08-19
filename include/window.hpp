#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "include/pongball.hpp"
#include "include/players.hpp"
#include "include/sound.hpp"
#include "include/background.hpp"
#include "include/AI.hpp"
#include "include/menu.hpp"
#include "include/inputbox.h"

// window class
class window 
{
public:
        bool                    isAI;
        bool                    isGameActive;
        bool                    isRunning;
        bool                    isScore;
        window                  (unsigned int, unsigned int, const std::string&);
        ~window                 ();
        void gameWin            ();
        int                     winScore;
        int                     winHeight=400;
        int                     winWidth=400;
private:
        void init               ();
        void textInit           (std::vector<std::unique_ptr<sf::Text>>&, float, sf::Color, sf::Vector2f);
        void events             ();
        void menuSelection      ();
        void updateScores       ();
        void updates            ();
        void renderScores       ();
        void render             ();
        void gameLoop           ();
        void setScoreLimit      (sf::RenderWindow&);
        void setWinningScore    (int);
        menu                    gameMenu;
        sf::RenderWindow        renderWin;
        sf::Clock               gameClock;
        sf::Font                font;
        Background              background;
        players                 _2players;
        Pongball                pongball;
        // soundManager            sManager;
        AI                      AIplayer;
        std::vector<std::unique_ptr<sf::Text>>   scoresTxt;
        std::vector<std::unique_ptr<sf::Text>>   AITxt;
};

#endif
