#ifndef HF_CLASSES_H
#define HF_CLASSES_H
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>


struct HandCard  /*A j�t�kos kez�ben l�v� k�rty�k list�ban t�rol�sa */
{
    unsigned int num;
    HandCard *next;
};

class Player    /*A j�t�kos oszt�lya. T�rolja a nev�t, a sorsz�m�t, illetve a k�rty�ira mutat� els� pointert */
{
    std::string name;
    unsigned int id;
    HandCard *first;
    int cardpieces = 0;
public:

    Player() { name = "error.name"; first = nullptr;}
    ~Player();
    void setID(unsigned int i)              {id = i;}
    void setName(std::string n)             {name = n;}
    void setName(int i);
    std::string getName()                   {return name;}
    HandCard* getHC()                       {return first;}
    void InsertList(unsigned int value);
    void DeleteNode(int number);
    bool Succesful(unsigned int number);
    int getPutCard(unsigned int number);
    void setCardpieces();
    int getCardpieces()                     {return cardpieces;}

};


#endif //HF_CLASSES_H
