#include <cmath>
#include "include/pongball.hpp"
#include "include/players.hpp"
#include "include/AI.hpp"

AI::AI (player& pPlayer, Pongball& pBall): 
        pPlayer(pPlayer), pBall(pBall) 
{
    init();
}

void AI::init () 
{
    if (pPlayer.id == "player2")
        pPlayer.fric = -0.08f;
}

void AI::sense () 
{
    if (pPlayer.id == "player2") 
    {
        pPlayer.isPlaying = true;
        if (pBall.isMoving &&
            pBall.currPos.x > 220 &&
            pBall.vertex2.position.y < 2*480 &&
            pBall.vertex2.position.y > -480) 
        {
            if (pBall.vertex1.position.y > pPlayer.side.top &&
                pBall.vertex1.position.y < pPlayer.side.bottom) 
            {
                // status = "zEuS0390 (AI): Stop";
                pPlayer.dir = {false, false};
            } 
            else if (pBall.vertex1.position.y > pPlayer.currPos.y) 
            {
                // status = "zEuS0390 (AI): Down";
                pPlayer.dir = {false, true};
            } 
            else if (pBall.vertex1.position.y < pPlayer.currPos.y) 
            {
                // status = "zEuS0390 (AI): Up";
                pPlayer.dir = {true, false};
            }
        } 
        else 
        {
            // status = "zEuS0390 (AI):";
            if (pPlayer.dir.up || pPlayer.dir.down) 
            {
                pPlayer.dir = {false, false};
            }
        }
    }
    if (pPlayer.id == "player1") 
    {
        if (pBall.isMoving &&
            pBall.currPos.x < 420 &&
            pBall.vertex2.position.y < 2*480 &&
            pBall.vertex2.position.y > -480) 
        {
            if (pBall.vertex2.position.y > pPlayer.side.top &&
                pBall.vertex2.position.y < pPlayer.side.bottom) 
            {
                pPlayer.dir = {false, false};
            } 
            else if (pBall.vertex2.position.y > pPlayer.currPos.y) 
            {
                pPlayer.dir = {false, true};
            } 
            else if (pBall.vertex2.position.y < pPlayer.currPos.y) 
            {
                pPlayer.dir = {true, false};
            }
        } 
        else 
        {
            if (pPlayer.dir.up || pPlayer.dir.down) 
            {
                pPlayer.dir = {false, false};
            }
        }
    }
}

void AI::update () 
{
    sense();
}
