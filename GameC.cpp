#include "PlayerC.h"
#include "main.h"
#include "GameC.h"
#include "CardC.h"

Game::Game()
{
    clrscr();
    CreateCard(cards);
    HowMany(db);
    players = new Player[db];
    CreatePlayer(db, players);
    CreateDeck(mixedcards);
    CardDealer(mixedcards, players, db);
    CreateTopCard(mixedcards, topcard, cards);
}

Game::~Game()
{
    if(cards[0] != nullptr)
    {
        for(int i = 0; i < 108; i++)
        {
            delete cards[i];
        }
        delete[] players;
    }
}

void Game::Contsr(Direction d, int db, int np, int tp, int *mx, Player *pl)
{
    players = pl; direction = d; this->db = db; nextplayer = np; topcard = tp;
    for(int i = 0; i < 108; i++)
    {
        mixedcards[i] = mx[i];
    }
    CreateCard(cards);
}

void Game::CardPulling(int x)
{
    for(int i = 0; i < x; i++)
    {
        int n = TopCardinMix(mixedcards);
        players[nextplayer].InsertList(n);
    }
}

void Game::NewMix()
{
    if(mixedcards[107] == -1)
    {
        HandCard *tmp;
        CreateDeck(mixedcards);
        int i,j,  b = 0;
        for (j = 0; j < db; j++)
        {
            for (tmp = players[j].getHC(); tmp != nullptr; tmp = tmp->next)
            {
                for(i = 0; i < 108; i++)
                {
                    if((int)tmp->num == mixedcards[i] || mixedcards[i] == topcard)
                    {
                        mixedcards[i] = -1;
                    }
                }
            }
        }
        for(i = 0; i < 108; i++)
        {
            if(mixedcards[i] == -1)
            {
                mix(mixedcards[i], mixedcards[b]);
                b++;
            }
        }
    }
    else
        return;
}

void Game::setNextPlayer(int i)
{
    switch(direction)
    {
        case increasing :
        {
            if(nextplayer < db-1)
            {
                nextplayer += i;
            }
            else
            {
                nextplayer = 0;
            }
            break;
        }
        case decreasing :
        {
            if(nextplayer > 0)
            {
                nextplayer -= i;
            }
            else
            {
                nextplayer = db-1;
            }
            break;
        }
        default: std::cerr << "error:nextplayer";
    }
}

void Game::PrintCards(int i)
{
    int j = 1;
    HandCard *tmp = players[i].getHC();
    while(tmp != nullptr)
    {
        std::cout << "\n  " << j++ << ": " ;
        printCardName(tmp->num);
        tmp = tmp->next;
    }
}

void Game::SaveGame()
{
    int i;
    HandCard *tmp;
    std::ofstream save;
    save.open("savegame.txt");
    save << topcard << " " << db << " " << nextplayer << " " << direction << "\r\n";
    for(i = 0; i < 108; i++)
    {
        save << mixedcards[i] << " ";
    }
    save << "\r\n";
    for(i = 0; i < db; i++)
    {
        if (i > 0)
        {
            save << "-1\r\n";
        }
        save << players[i].getName() << " ";
        for(tmp = players[i].getHC(); tmp != nullptr; tmp = tmp->next)
        {
            save << tmp->num << " ";
        }
    }
    save << "-1\r\n";
    save.close();
    std::cout << " Jatek elmentve!";
}

bool Game::win(int i)
{
    if( gameend == ended || players[nextplayer].getCardpieces() == 0)
    {
        if(i == 0)
        {
            std::cout << players[nextplayer].getName() << " nyert!" << std::endl;
        }
        return true;
    }
    return false;
}

void Game::uno()
{
    if(players[nextplayer].getCardpieces() == 1)
    {
        std::cout << "UNO";
    }
}

void Game::WildDrawFourPut()
{
    setNextPlayer(1);
    CardPulling(4);
}

void Game::changeDirection()
{
    if(direction == increasing)
        direction = decreasing;
    else
        direction = increasing;
}

void Game::WildRequest()
{
    int q;
    std::cout << "\n  Milyen szint kersz? (1: Piros, 2: Sarga, 3: Zold, 4: Kek) ";
    std::cin >> q;
    if(q > 0 && q < 5)
        topcard = (q-1) * 25;
    else
    {
        clrscr();
        std::cout << "\n  Hibas valasz!" << std::endl;
        WildRequest();
    }
}

bool Game::PutLogic(unsigned int number)
{
    unsigned int c;
    int n, s;
    int a = players[nextplayer].getPutCard(number);
    c = cards[topcard]->getColour();
    n = cards[topcard]->getNum();
    s = cards[topcard]->getSpec();
    if(c == 5 || c == cards[a]->getColour() || cards[a]->Check(n, c, s))
    {
        std::cout << "Sikeres lepes\n";
        return true;
    }
    else
    {
        std::cout << "Nem rakhatod ra";
        return false;
    }

}

bool Game::PutCard(unsigned int number)
{
    if(number > 0)
    {
        int a = players[nextplayer].getPutCard(number);
        if(!players[nextplayer].Succesful(number))
        {
            return false;
        }
        if(!PutLogic(number))
        {
            return false;
        }
        players[nextplayer].DeleteNode(number);
        players[nextplayer].setCardpieces();
        uno();
        if(win(1)) { return true; }
        if(cards[a]->getSpec() == 5)
        {
            WildDrawFourPut();
        }
        else
        {
            topcard = a;
            switch(cards[a]->getSpec())
            {
                case 1 :    changeDirection();
                    players[nextplayer].setCardpieces();
                    break;
                case 2 :    setNextPlayer(1);
                    players[nextplayer].setCardpieces();
                    break;
                case 3 :    setNextPlayer(1);
                    CardPulling(2);
                    players[nextplayer].setCardpieces();
                    break;
            }
        }
        if(cards[a]->getColour() == 5)
        {
            clrscr();
            WildRequest();
        }
        return true;
    }
    return true;
}
