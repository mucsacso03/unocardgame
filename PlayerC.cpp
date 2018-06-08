#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

#include "PlayerC.h"
#include "main.h"
#include "GameC.h"
#include "CardC.h"

Player::~Player()
{
    HandCard *tmp = first;
    HandCard *tmp2;
    while(tmp != nullptr)
    {
        tmp2 = tmp->next;
        delete tmp;
        tmp = tmp2;
    }
}

void Player::setName(int i)
{
    std::cout << std::endl << "  Mi legyen " << i << " a jatekos neve?  ";
    std::cin >> this->name;
}

void Player::setCardpieces()
{
    cardpieces = 0;
    HandCard *t = first;
    while(t != nullptr)
    {
        cardpieces++;
        t = t->next;
    }
}

void Player::InsertList(unsigned int value)
{
    HandCard *nw = new HandCard;
    nw->num = value;
    nw->next = nullptr;
    if(first == nullptr)
    {
        first = nw;
    }
    else
    {
        HandCard *tmp = first;
        while(tmp->next != nullptr)
        {
            tmp = tmp->next;
        }
        tmp->next = nw;
    }
}

void Player::DeleteNode(int number)
{
    HandCard *lag, *tmp;
    int a = 0;
    lag = nullptr;
    tmp = first;
    while (tmp != nullptr && number-1 != a)
    {
        a++;
        lag = tmp;
        tmp = tmp->next;
    }
    if(tmp == nullptr) {}
    else if (lag == nullptr)
    {
        HandCard *newfirst = tmp->next;
        delete tmp;
        first = newfirst;
    }
    else
    {
        lag->next = tmp->next;
        delete tmp;
    }
}

bool Player::Succesful(unsigned int number)
{
    HandCard *tmp = first;
    unsigned int i;
    for(i = 0; tmp != nullptr; i++, tmp = tmp->next) {}
    if(number <= i) {/*std::cout << "Sikeres lepes\n";*/ return true;}
    else
    {
        std::cout << "Nincs ilyen kartyad";
        return false;
    }
}

int Player::getPutCard(unsigned int number)
{
    HandCard *tmp = first;
    unsigned int i = 0;
    for(;tmp != nullptr; tmp = tmp->next, i++)
    {
        if(i == number-1)
        {
            return tmp->num;
        }
    }
    return -1;
}

