#ifndef CARDTYPEEVALUATOR_H
#define CARDTYPEEVALUATOR_H

struct Card {
    int value;
    char suit;
};

class CardTypeEvaluator {
public:
    static void sortHand(Card* hand);
    static const char* evaluateHand(Card* hand);
    static int getHandRank(const char* type);

private:
    static bool isRoyalFlush(const Card* hand);
    static bool isStraightFlush(const Card* hand);
    static bool isFourOfAKind(const Card* hand);
    static bool isFullHouse(const Card* hand);
    static bool isFlush(const Card* hand);
    static bool isStraight(const Card* hand);
    static bool isThreeOfAKind(const Card* hand);
    static bool isTwoPair(const Card* hand);
    static bool isPair(const Card* hand);
};

#endif