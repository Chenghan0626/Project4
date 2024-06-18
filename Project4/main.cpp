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
    cout << "��e�Ҧ����a���w�X:" << endl;
    for (int i = 0; i < playerCount; ++i) {
        cout << (i == 0 ? "Me" : "���a " + std::to_string(i + 1)) << ": " << betting.getPlayerChips(i) << " �w�X" << endl;
    }
}

int main() {
    int playerCount;
    cout << "�п�J���a�ƶq: ";
    cin >> playerCount;

    srand(static_cast<unsigned int>(time(nullptr)));

    Licensing licensing(playerCount);
    Betting betting(playerCount);

    while (betting.getPlayerChips(0) > 0) {
        licensing.shuffle();

        // ��ܩҦ����a����l�w�X
        displayChips(betting, playerCount);

        vector<int> handRanks(playerCount);
        vector<string> handTypes(playerCount);

        for (int i = 0; i < playerCount; ++i) {
            Card* hand = licensing.deal();
            cout << (i == 0 ? "Me" : "���a " + std::to_string(i + 1)) << " ����P: ";
            for (int j = 0; j < 5; ++j) {
                cout << hand[j].value << hand[j].suit << " ";
            }
            cout << endl;

            const char* type = CardTypeEvaluator::evaluateHand(hand);
            handTypes[i] = type;
            handRanks[i] = CardTypeEvaluator::getHandRank(type);
            cout << "�P��: " << type << endl;

            int betAmount;
            if (i == 0) {
                bool validBet = false;
                while (!validBet) {
                    cout << "Me ���U�`�w�X (��J -1 ���}�C��): ";
                    cin >> betAmount;
                    cout << "----------" << endl;
                    if (betAmount == -1) {
                        cout << "���}�C��" << endl;
                        return 0;
                    }
                    if (betAmount > 0 && betAmount <= betting.getPlayerChips(i)) {
                        validBet = true;
                    }
                    else {
                        cout << "Me ���w�X�����A�L�k�U�`�C" << endl;
                    }
                }
            }
            else {
                betAmount = rand() % 101 + 50; // �H���U�`50��150�w�X
                cout << "���a " << i + 1 << " ���U�`�w�X: " << betAmount << endl;
                cout << "----------" << endl;
            }

            // �ˬd���a�O�_���������w�X�U�`
            if (betting.getPlayerChips(i) >= betAmount) {
                betting.placeBet(i, betAmount);
            }
            else {
                cout << (i == 0 ? "Me" : "���a " + std::to_string(i + 1)) << " ���w�X�����A�L�k�U�`�C" << endl;
            }

            delete[] hand;
        }

        // ��X�P���̤j�����a
        int winner = 0;
        for (int i = 1; i < playerCount; ++i) {
            if (handRanks[i] > handRanks[winner]) {
                winner = i;
            }
        }

        betting.declareWinner(winner);

        cout << "Ĺ�a�O: " << (winner == 0 ? "Me" : "���a " + std::to_string(winner + 1)) << endl;
        cout << "Ĺ�o���w�X�ƶq: " << betting.getPlayerChips(winner) << endl;
        cout << endl;
        cout << "==========" << endl;
        cout << endl;
        // ��ܩҦ����a���{���w�X
        displayChips(betting, playerCount);

        // �ˬd Me ���w�X�O�_�p�󵥩�0
        if (betting.getPlayerChips(0) <= 0) {
            cout << "�A�}���F!!!" << endl;
            break;
        }

        // �M�ŤU�`�w�X
        for (int i = 0; i < playerCount; ++i) {
            betting.placeBet(i, 0);
        }
    }

    return 0;
}
