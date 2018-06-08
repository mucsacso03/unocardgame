#ifndef HF_GAMEC_H
#define HF_GAMEC_H

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include "CardC.h"

enum Direction
{
    increasing, decreasing
};

enum Gameend
{
    ended, notyet
};

class Game
{
    Card *cards[108];
    Player *players;
    int mixedcards[108];
    Direction direction = increasing;
    int db;
    int nextplayer = 0;
    int topcard;
    Gameend gameend = notyet;
public:
    Game(int loadgame) {/*ilenykor a Contsr fv tölti fel a classt.*/}
    Game();
    ~Game();
    void Contsr(Direction d, int db, int np, int tp, int* mx, Player *pl);
    void printCardName(int i)       {cards[i]->getFullName();}
    void printPlayerName(int i)     {std::cout << players[i].getName();}
    void printTopCard()             {cards[topcard]->getFullName();}
    void PrintCards(int i);
    int getNextPlayer()             {return nextplayer;}
    void setNextPlayer(int i);
    void CardPulling(int x);
    void NewMix();
    bool PutCard(unsigned int number);
    bool PutLogic(unsigned int number);
    void WildRequest();
    void WildDrawFourPut();
    void changeDirection();
    void uno();
    bool win(int i);
    void SaveGame();
    void setEnd(Gameend i)          {gameend = i;}

};


#endif //HF_GAMEC_H
