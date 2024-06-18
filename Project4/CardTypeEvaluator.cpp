#include "CardTypeEvaluator.h"
#include <algorithm>

void CardTypeEvaluator::sortHand(Card* hand) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4 - i; ++j) {
            if (hand[j].value > hand[j + 1].value) {
                std::swap(hand[j], hand[j + 1]);
            }
        }
    }
}

const char* CardTypeEvaluator::evaluateHand(Card* hand) {
    // Sort the hand
    sortHand(hand);
    // Evaluate the type of hand
    if (isRoyalFlush(hand)) return "Royal Flush";
    if (isStraightFlush(hand)) return "Straight Flush";
    if (isFourOfAKind(hand)) return "Four of a Kind";
    if (isFullHouse(hand)) return "Full House";
    if (isFlush(hand)) return "Flush";
    if (isStraight(hand)) return "Straight";
    if (isThreeOfAKind(hand)) return "Three of a Kind";
    if (isTwoPair(hand)) return "Two Pair";
    if (isPair(hand)) return "Pair";
    return "High Card";
}

int CardTypeEvaluator::getHandRank(const char* type) {
    if (strcmp(type, "Royal Flush") == 0) return 10;
    if (strcmp(type, "Straight Flush") == 0) return 9;
    if (strcmp(type, "Four of a Kind") == 0) return 8;
    if (strcmp(type, "Full House") == 0) return 7;
    if (strcmp(type, "Flush") == 0) return 6;
    if (strcmp(type, "Straight") == 0) return 5;
    if (strcmp(type, "Three of a Kind") == 0) return 4;
    if (strcmp(type, "Two Pair") == 0) return 3;
    if (strcmp(type, "Pair") == 0) return 2;
    return 1; // High Card
}

bool CardTypeEvaluator::isRoyalFlush(const Card* hand) {
    // 判斷是否為皇家同花順
    if (!isStraightFlush(hand)) return false;
    return hand[0].value == 10 && hand[1].value == 11 && hand[2].value == 12 && hand[3].value == 13 && hand[4].value == 1;
}

bool CardTypeEvaluator::isStraightFlush(const Card* hand) {
    // 判斷是否為同花順
    if (!isFlush(hand)) return false;
    return isStraight(hand);
}

bool CardTypeEvaluator::isFourOfAKind(const Card* hand) {
    // 判斷是否為四條
    for (int i = 0; i <= 1; ++i) {
        if (hand[i].value == hand[i + 1].value && hand[i].value == hand[i + 2].value && hand[i].value == hand[i + 3].value) {
            return true;
        }
    }
    return false;
}

bool CardTypeEvaluator::isFullHouse(const Card* hand) {
    // 判斷是否為葫蘆
    if ((hand[0].value == hand[1].value && hand[0].value == hand[2].value && hand[3].value == hand[4].value) ||
        (hand[0].value == hand[1].value && hand[2].value == hand[3].value && hand[2].value == hand[4].value)) {
        return true;
    }
    return false;
}

bool CardTypeEvaluator::isFlush(const Card* hand) {
    // 判斷是否為同花
    char suit = hand[0].suit;
    for (int i = 1; i < 5; ++i) {
        if (hand[i].suit != suit) return false;
    }
    return true;
}

bool CardTypeEvaluator::isStraight(const Card* hand) {
    // 判斷是否為順子
    for (int i = 0; i < 4; ++i) {
        if (hand[i].value + 1 != hand[i + 1].value) {
            return false;
        }
    }
    return true;
}

bool CardTypeEvaluator::isThreeOfAKind(const Card* hand) {
    // 判斷是否為三條
    for (int i = 0; i <= 2; ++i) {
        if (hand[i].value == hand[i + 1].value && hand[i].value == hand[i + 2].value) {
            return true;
        }
    }
    return false;
}

bool CardTypeEvaluator::isTwoPair(const Card* hand) {
    // 判斷是否為兩對
    int pairs = 0;
    for (int i = 0; i < 4; ++i) {
        if (hand[i].value == hand[i + 1].value) {
            ++pairs;
            ++i; // Skip the next card
        }
    }
    return pairs == 2;
}

bool CardTypeEvaluator::isPair(const Card* hand) {
    // 判斷是否為對子
    for (int i = 0; i < 4; ++i) {
        if (hand[i].value == hand[i + 1].value) {
            return true;
        }
    }
    return false;
}