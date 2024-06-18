#include "Licensing.h"
#include "CardTypeEvaluator.h"
#include <algorithm>
Licensing::Licensing(int playerCount) : playerCount(playerCount) {
    deckSize = 52;
    deck = new Card[deckSize];
    for (int i = 0; i < deckSize; ++i) {
        deck[i].value = i % 13 + 1;
        deck[i].suit = "SHDC"[i / 13];
    }
}

Licensing::~Licensing() {
    delete[] deck;
}

void Licensing::shuffle() {
    for (int i = 0; i < deckSize; ++i) {
        int j = rand() % deckSize;
        std::swap(deck[i], deck[j]);
    }
}

Card* Licensing::deal() {
    Card* hand = new Card[5];
    for (int i = 0; i < 5; ++i) {
        hand[i] = deck[i];
    }
    for (int i = 0; i < deckSize - 5; ++i) {
        deck[i] = deck[i + 5];
    }
    deckSize -= 5;
    return hand;
}