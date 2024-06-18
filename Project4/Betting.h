#ifndef BETTING_H
#define BETTING_H

class Betting {
public:
    Betting(int playerCount);
    ~Betting();
    void placeBet(int player, int amount);
    int getTotalPot() const;
    int getPlayerChips(int player) const;
    void declareWinner(int winner);
private:
    int* playerChips;
    int totalPot;
    int playerCount;
};

#endif
