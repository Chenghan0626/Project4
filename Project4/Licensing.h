#ifndef LICENSING_H
#define LICENSING_H
#include "CardTypeEvaluator.h"
#include <cstdlib>
#include <ctime>

struct Card;

class Licensing {
public:
    Licensing(int playerCount);
    ~Licensing();
    void shuffle();
    Card* deal();

private:
    int playerCount;
    int deckSize;
    Card* deck;
};

#endif 