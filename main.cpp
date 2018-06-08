#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

#include "main.h"
#include "PlayerC.h"
#include "memtrace.h"
#include "GameC.h"
#include "CardC.h"

/*
Piros - 1
Sarga - 2
Zold - 3
Kek - 4
Fekete - 5
Spec:
Reverse - 1
Skip - 2
Draw two - 3
Wild - 4
Wild Draw Four - 5 */

void CreateCard (Card **cards)
{
    unsigned int i, j = 1;
    for(i = 0; i < 76; i += 25, j++)
    {
        cards[i] = new Number(0, i, j);
    }
    unsigned int k = 10, l = 0;
    for (j = 1; j <= 4; j++, k+=25, l+= 25)
    {
        for (i = 1; i < 10; i++ )
        {
            cards[l+i] = new Number(i, l+i, j);
            cards[l+i+12] = new Number(i, l+i+12, j);
        }
        if(k < 100)
        {
            cards[k] =      new Skip(k, j);
            cards[k+1] =    new Reverse(k+1, j);
            cards[k+2] =    new DrawTwo(k+2, j);
            cards[k+12] =   new Skip(k, j);
            cards[k+13] =   new Reverse(k+1, j);
            cards[k+14] =   new DrawTwo(k+2, j);
        }
    }
    for (i = 100; i < 104; i++)
    {
        cards[i] = new Wild(i, 5);
        cards[i+4] = new WildDF(i+4, 5);
    }
}

void HowMany(int &db)
{
    std::cout << "\n   Hany Jatekos legyen? ";
    std::cin >> db;
    if(db < 2 || db > 10)
    {
        clrscr();
        std::cout << "  Jatekosoknak 2-10 kozott kell lenniuk";
        HowMany(db);
    }
}

void CreatePlayer(int db, Player *players)
{
    unsigned int i;
    for(i = 0; (int)i < db; i++)
    {
       players[i].setID(i+1);
    }
    clrscr();
    for(i = 0; (int)i < db; i++)
    {
        players[i].setName(i+1);
    }
}

void mix (int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void CreateDeck(int *mixedcards)
{
    srand ( time(NULL) );
    int i;
    for(i = 0; i < 108; i++)
    {
        mixedcards[i] = i;
    }
    for(i = 107; i > 0; i--)
    {
        int j = rand() % (i+1);
        mix(mixedcards[i], mixedcards[j]);
    }
}

void CardDealer(int *mixedcards, Player *players, int db)
{
    int k = 0;
    for(int j = 0; j < db; j++)
    {
        for(int i = 0; i < 7; i++)
        {
            players[j].InsertList(mixedcards[k]);
            mixedcards[k] = -1;
            k++;
        }
        players[j].setCardpieces();
    }
}

void CreateTopCard(int *mixedcards, int &topcard, Card **cards)
{
    int i;
    for( i = 0; mixedcards[i] == -1; i++) {}
    for(int k = 0; k < 120; k++)
    {
        if(cards[mixedcards[i]]->getSpec() == 0)
        {
            topcard = mixedcards[i];
            mixedcards[i] = -1;
            return;
        }
        int tmp = mixedcards[i];
        for(int j = i; j < 108; j++)
        {
            mixedcards[j] = mixedcards[j+1];
        }
        mixedcards[107] = tmp;
    }
}

int TopCardinMix(int *mixedcards)
{
    int i, j;
    for (i = 0; mixedcards[i] == -1 ; i++ ){}
    j = mixedcards[i];
    mixedcards[i] = -1;
    return j;
}

bool LoadGame(Game& A)
{
    unsigned int i;
    Direction direction;
    int direc = -1, db, nextplayer, topcard, mx[108], j, x;
    std::ifstream load;
    load.open("savegame.txt");
    load >> topcard >> db >> nextplayer >> direc;
    if(direc == -1)
    {
        std::cout << "Nincs mentett jatek\n";
        load.close();
        return false;
    }
    if(direc == 0)
        direction = increasing;
    else
        direction = decreasing;
    for(i = 0; i < 108; i++)
    {
        load >> mx[i];
    }
    Player *players;
    players = new Player[db];
    std::string name;
    for(i = 0; (int)i < db; i++)
    {
        x = 0;
        players[i].setID(i + 1);
        load >> name;
        players[i].setName(name);
        for(j = 0; x != -1; j++ )
        {
            load >> x;
            if(x != -1)
            {
                players[i].InsertList(x);
            }
        }
    }
    load.close();
    A.Contsr(direction, db, nextplayer, topcard, mx, players);
    std::cout << " Sikeres betoltes\n ";
    return true;
}

void Menu()
{
    clrscr();
    char menuk[6][50] =
            {
                    "Udvozollek az Uno jatekomban\n\n",
                    "1. Jatek!",
                    "2. Jatek szabaly",
                    "3. Jatek betoltese",
                    "9. Kilepes\n",
                    "Valassz egyet a tovabblepeshez: "
            };
    std::cout << std::endl;
    int i;
    for(i = 0; i < 6; i++)
    {
        std::cout << "   " << menuk[i] << std::endl;
    }
    switch(MenuC())
    {
        case 1 :   {Game A;
                    Gameplay(A);
                    return; }
        case 2 :    szabaly();
                    break;
        case 3 :   {Game A(1);
                    if(!LoadGame(A))
                        return;
                    Gameplay(A);
                    return;}
        case 9 :    exit(0);
        default : std::cout << "Nincs ilyen opcio";
    }
}

int MenuC()
{
    int x = 0;
    while(x != 1 || x != 3 || x != 9 || x != 2)
    {
        std::cout << "  ";
        std::cin >> x;
        if(x == 1 || x == 3 || x == 9 || x == 2)
        {
            return x;
        }
        else
        {
            clrscr();
            std::cout << "  Nincs ilyen lehetoseg!\n";
            Menu();
        }
    }
    return x;
}

void Gameplay(Game& A)
{
    unsigned int i;
    DisplayGame(A);
    std::cin >> i;
    switch(i)
    {
        case 0 :    {A.CardPulling(1);
                    A.NewMix();
                    A.setNextPlayer(1);
                    Gameplay(A);
                    return;}
        case -1 :  {A.setEnd(ended);
                    return;}
        case 999 :  {A.SaveGame();
                    break;}
    }
    if(!A.PutCard(i))
    {
        Gameplay(A);
        return;
    }
    if(A.win(0))
    {
        return;
    }
    A.setNextPlayer(1);
    Gameplay(A);
}

void szabaly()
{
    clrscr();
    std::ifstream szabaly;
    szabaly.open("szabaly.txt");
    char r[50];
    while(r[9] != '!')
    {
        szabaly >> r;
        if(r[0] == '?')
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << r << " ";
        }
    }
}

void clrscr()
{
    // system("cls || clear");
}

void DisplayGame(Game& A)
{
    clrscr();
    std::cout << "\n\n ";
    A.printPlayerName(A.getNextPlayer());
    std::cout << " jon.\n Valassz egy kartyat es ird le a szamat\n [0-val huzol lapot, -1 -el kilepsz, 999-el mented az allast]\n\n";
    std::cout << " Legfelso lap: ";
    A.printTopCard();
    std::cout << std::endl;
    A.PrintCards(A.getNextPlayer());
    std::cout << std::endl;
}

int main()
{
    int i = 0;
    while(i != 1000)
    {
        Menu();
        i++;
    }
    std::cout << "\n\n\n Tul sokat jatszottal, pihenj kicsit!";
    return 0;
}
