#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>

class Game;

class Card;

class Player;

void Menu();

int MenuC();

void clrscr();

void Gameplay(Game&);

void DisplayGame(Game&);

int TopCardinMix(int *mixedcards);

bool LoadGame(Game& A);

void szabaly();

void CreateCard (Card **cards);

void CreatePlayer(int db, Player *players);

void CardDealer(int *mixedcards, Player *players, int db);

void CreateTopCard(int *mixedcards, int &topcard, Card **cards);

void CreateDeck(int *mixedcards);

void mix (int &a, int &b);

void HowMany(int &db);


#endif // MAIN_H_INCLUDED
