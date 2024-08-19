#ifndef PLAYERS_H
#define PLAYERS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "include/rect.hpp"
#include "include/sound.hpp"
#include "include/menu.hpp"


// player class
class player 
{
public:
        std::string             id;
        std::string             filepath;
        std::string             shadowfilepath;
        int                     score;
        bool                    isMoving;
        bool                    isPlaying;
        float                   speed;
        float                   velY;
        float                   accY;
        float                   fric;
        player                  (std::string, std::string, std::string, sf::Vector2f /*,soundManager&*/);
        void init               ();
        void movement           ();
        void collision          ();
        void restartPos         ();
        void update             ();
        sf::Vector2f            initPos;
        sf::Vector2f            currPos;
        sf::Sprite              sprite;
        sf::Sprite              shadow;
        sf::Texture             texture;
        sf::Texture		shadowTex;
        Dir                     dir;
        Side			side;
private:
        sf::Clock               clock;
        // soundManager&           sManager;
        void setSides           ();
};

// players class
class players
{
public:
        std::vector<player>     playersVec;
        players                 (sf::RenderWindow&/*, soundManager&*/);
        ~players                ();
        void init               ();
        void setScore           (std::string, int);
        void resetScore         ();
        void move               (std::string, std::string);
        void stop               (std::string);
        void pause              ();
        void resume             ();
        void restart            ();
        void events             ();
        void updates            ();
        void renders            ();
        int getScore            (int);
private:
        sf::RenderWindow&       renderWin;
        // soundManager&           sManager;
};

#endif
