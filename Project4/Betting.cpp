#include "Betting.h"

Betting::Betting(int playerCount) : playerCount(playerCount), totalPot(0) {
    playerChips = new int[playerCount];
    for (int i = 0; i < playerCount; ++i) {
        playerChips[i] = 1000; // 每個玩家初始有1000籌碼
    }
}

void Betting::placeBet(int player, int amount) {
    if (playerChips[player] >= amount) {
        playerChips[player] -= amount;
        totalPot += amount;
    }
}

int Betting::getTotalPot() const {
    return totalPot;
}

int Betting::getPlayerChips(int player) const {
    return playerChips[player];
}

void Betting::declareWinner(int winner) {
    playerChips[winner] += totalPot;
    totalPot = 0;
}

Betting::~Betting() {
    delete[] playerChips;
}