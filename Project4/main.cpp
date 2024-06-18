#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "Licensing.h"
#include "CardTypeEvaluator.h"
#include "Betting.h"
using namespace std;

void displayChips(Betting& betting, int playerCount) {
    cout << "當前所有玩家的籌碼:" << endl;
    for (int i = 0; i < playerCount; ++i) {
        cout << (i == 0 ? "Me" : "玩家 " + std::to_string(i + 1)) << ": " << betting.getPlayerChips(i) << " 籌碼" << endl;
    }
}

int main() {
    int playerCount;
    cout << "請輸入玩家數量: ";
    cin >> playerCount;

    srand(static_cast<unsigned int>(time(nullptr)));

    Licensing licensing(playerCount);
    Betting betting(playerCount);

    while (betting.getPlayerChips(0) > 0) {
        licensing.shuffle();

        // 顯示所有玩家的初始籌碼
        displayChips(betting, playerCount);

        vector<int> handRanks(playerCount);
        vector<string> handTypes(playerCount);

        for (int i = 0; i < playerCount; ++i) {
            Card* hand = licensing.deal();
            cout << (i == 0 ? "Me" : "玩家 " + std::to_string(i + 1)) << " 的手牌: ";
            for (int j = 0; j < 5; ++j) {
                cout << hand[j].value << hand[j].suit << " ";
            }
            cout << endl;

            const char* type = CardTypeEvaluator::evaluateHand(hand);
            handTypes[i] = type;
            handRanks[i] = CardTypeEvaluator::getHandRank(type);
            cout << "牌型: " << type << endl;

            int betAmount;
            if (i == 0) {
                bool validBet = false;
                while (!validBet) {
                    cout << "Me 的下注籌碼 (輸入 -1 離開遊戲): ";
                    cin >> betAmount;
                    cout << "----------" << endl;
                    if (betAmount == -1) {
                        cout << "離開遊戲" << endl;
                        return 0;
                    }
                    if (betAmount > 0 && betAmount <= betting.getPlayerChips(i)) {
                        validBet = true;
                    }
                    else {
                        cout << "Me 的籌碼不足，無法下注。" << endl;
                    }
                }
            }
            else {
                betAmount = rand() % 101 + 50; // 隨機下注50到150籌碼
                cout << "玩家 " << i + 1 << " 的下注籌碼: " << betAmount << endl;
                cout << "----------" << endl;
            }

            // 檢查玩家是否有足夠的籌碼下注
            if (betting.getPlayerChips(i) >= betAmount) {
                betting.placeBet(i, betAmount);
            }
            else {
                cout << (i == 0 ? "Me" : "玩家 " + std::to_string(i + 1)) << " 的籌碼不足，無法下注。" << endl;
            }

            delete[] hand;
        }

        // 找出牌型最大的玩家
        int winner = 0;
        for (int i = 1; i < playerCount; ++i) {
            if (handRanks[i] > handRanks[winner]) {
                winner = i;
            }
        }

        betting.declareWinner(winner);

        cout << "贏家是: " << (winner == 0 ? "Me" : "玩家 " + std::to_string(winner + 1)) << endl;
        cout << "贏得的籌碼數量: " << betting.getPlayerChips(winner) << endl;
        cout << endl;
        cout << "==========" << endl;
        cout << endl;
        // 顯示所有玩家的現有籌碼
        displayChips(betting, playerCount);

        // 檢查 Me 的籌碼是否小於等於0
        if (betting.getPlayerChips(0) <= 0) {
            cout << "你破產了!!!" << endl;
            break;
        }

        // 清空下注籌碼
        for (int i = 0; i < playerCount; ++i) {
            betting.placeBet(i, 0);
        }
    }

    return 0;
}
