#ifndef HF_CARDC_H
#define HF_CARDC_H

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>

class Card      /*A k�rty�k oszt�lya. T�rolja a k�rtya azonos�t�j�t, nev�t �s a sz�n�t. */
{
    unsigned int id;
    std::string name;
    unsigned int colour;
public:
    Card(unsigned int id, unsigned int colourr): id(id), colour(colourr)
    {
        if (colourr < 5)
        {
            switch (colourr)
            {
                case 1 :    name = "Piros ";
                    break;
                case 2 :    name = "Sarga ";
                    break;
                case 3 :    name = "Zold ";
                    break;
                case 4 :    name = "Kek ";
                    break;
            }
        }
    }
    virtual ~Card() {}
    std::string getName()               {return name;}
    unsigned int getColour()            {return colour;}
    virtual int getNum() = 0;
    virtual int getSpec()  = 0;
    virtual void getFullName()  = 0;
    void setName (std::string nam)      {name = nam;}
    virtual bool Check(int n, unsigned int c, int s) = 0;
};

class Number : public Card
{
    int num;
    int spec = 0;
public:
    Number(int number, unsigned int id, unsigned int colourr) : Card(id, colourr), num(number) {}
    ~Number() {}
    void getFullName()                          {std::cout << getName() << " " << num;}
    int getSpec()                               {return spec;}
    int getNum()                                {return num;}
    bool Check(int n, unsigned int c, int s)
    {
        if(n == num)
            return true;
        return false;
    }
};

class Reverse : public Card
{
    int spec;
    std::string spname = "Fordulj";
public:
    Reverse(unsigned int id, unsigned int colour): Card(id, colour), spec(1) {}
    ~Reverse() {}
    void getFullName()                          {std::cout << getName() << " " << spname;}
    int getSpec()                               {return spec;}
    int getNum()                                {return -1;}
    bool Check(int n, unsigned int c, int s)
    {
        if (s == spec)
            return true;
        return false;
    }
};

class Skip : public Card
{
    int spec;
    std::string spname = "Ugorj";
public:
    Skip(unsigned int id, unsigned int colour): Card(id, colour), spec(2) {}
    ~Skip() {}
    void getFullName()                          {std::cout << getName() << " " << spname;}
    int getSpec()                               {return spec;}
    int getNum()                                {return -1;}
    bool Check(int n, unsigned int c, int s)
    {
        if (s == spec)
            return true;
        return false;
    }
};

class DrawTwo : public Card
{
    int spec;
    std::string spname = "Huzz kettot";
public:
    DrawTwo(unsigned int id, unsigned int colour): Card(id, colour), spec(3) {}
    ~DrawTwo() {}
    void getFullName()                          {std::cout << getName() << " " << spname;}
    int getSpec()                               {return spec;}
    int getNum()                                {return -1;}
    bool Check(int n, unsigned int c, int s)
    {
        if (s == spec)
            return true;
        return false;
    }
};

class Wild : public Card
{
    int spec;
public:
    Wild(unsigned int id, unsigned int colour): Card(id, colour), spec(4)
    {
        setName("Joker");
    }
    ~Wild() {}
    void getFullName()                          {std::cout << getName();}
    int getSpec()                               {return spec;}
    int getNum()                                {return -1;}
    bool Check(int n, unsigned int c, int s)    {return true;}
};

class WildDF : public Card
{
    int spec = 5;
public:
    WildDF(unsigned int id, unsigned int colour): Card(id, colour)
    {
        setName("Huzz negyet! Joker");
    }
    ~WildDF() {}
    void getFullName()                          {std::cout << getName();}
    int getSpec()                               {return spec;}
    int getNum()                                {return -1;}
    bool Check(int n, unsigned int c, int s)    {return true;}
};


#endif //HF_CARDC_H
