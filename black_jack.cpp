#include <iostream>
#include <string>
#include <sstream>
#include <vector> 
#include <stdlib.h>
#include <typeinfo>
#include <time.h> 
#include "player.h"
#include "banker.h"
#include "AllocationSystem.h"
using namespace std;

void hitStand(int min, int& max, BST_Tree* root, Player* player) {
    // 
    AllocationSystem AC;
    cout << " ~ Please chooose an action: hit/stand" << endl;
    string action;
    while ((*player).calculate() < 21) {
        cin >> action;
        if (action == "hit") {
            (*player).add_card(AC.Allocate(min, max, root));
            cout << "New card: " << (*player).get_cards()[(*player).get_cards().size() - 1] << " | Your total point: " << (*player).calculate() << endl;
        }
        else if (action == "stand") {
            cout << "Total point: " << (*player).calculate() << endl;
            break;
        }
        else {
            cout << " ~ Incorrect action, please enter the correct action." << endl;
        }
    }
}

int comparison(int player, int banker, double bet, int& win_count) {
    if (player > banker) {
        cout << " ~ Congratulations! You win!" << endl;
        win_count++;
        return bet;
    }
    else if (player < banker) {
        cout << " ~ Sorry, you lose" << endl;
        return -bet;
    }
    else {
        cout << " ~ Break even" << endl;
        return 0;
    }
    return 0;
}

void Banker_card(int& min, int& max, BST_Tree* root, Banker* banker) {
    AllocationSystem AC;
    cout << "banker's cards: " << (*banker).get_cards()[0] << ", " << (*banker).get_cards()[1] << endl;
    while ((*banker).calculate() < 17) {
        (*banker).add_card(AC.Allocate(min, max, root));
        cout << "New card: " << (*banker).get_cards()[(*banker).get_cards().size() - 1] << " | Banker's total point: " << (*banker).calculate() << endl;
    }
}

void normProcess(int& min, int& max, BST_Tree* root, double bet, Player* player, Banker* banker, int& win_count) {
    hitStand(min, max, root, player);
    if ((*player).calculate() > 21) {
        cout << " ~ Sorry, you lose" << endl;
        (*player).balance -= bet;
    }
    else {
        Banker_card(min, max, root, banker);
        if ((*banker).calculate() > 21) {
            cout << " ~ Congratulations! You win!" << endl;
            (*player).balance += bet;
            win_count++;
        }
        else {
            (*player).balance += comparison((*player).calculate(), (*banker).calculate(), bet, win_count);
        }
    }
}

void codes(int& min, int& max, BST_Tree* root, double bet, Player* player, Banker* banker, int& win_count) {
    AllocationSystem AC;
    string a = (*player).get_cards()[0];
    string b = (*player).get_cards()[1];
    if (a.substr(1) == b.substr(1)){
        string split;
        cout << " ~ Split the card(Input Y or N): " << endl;
        cin >> split;
        if (split == "Y") {
            // codes for split play
            vector<int> results;
            (*player).keep_first();
            // repeating from 208-242(stand or hit);
            hitStand(min, max, root, player);
            results.push_back((*player).calculate());
            (*player).keep_first();
            // repeat
            hitStand(min, max, root, player);
            results.push_back((*player).calculate());
            if (results[0] > 21 && results[1] > 21) {
                //两局全爆牌
                cout << " ~ Sorry, you lose" << endl;
                (*player).balance -= 2 * bet;

            }
            else {
                //两个分别比，复制下面252-274，重复两次把两次分别比即可。
                for (int i = 0; i < 2; i++) {
                    cout << "Hand " << i + 1 << endl;
                    Banker_card(min, max, root, banker);
                    if (results[i] > 21 && (*banker).calculate() > 21) {
                        cout << " ~ Break even" << endl;
                    }
                    else if (results[i] > 21 && (*banker).calculate() <= 21) {
                        cout << " ~ Sorry, you lose" << endl;
                        (*player).balance -= bet;
                    }
                    else if (results[i] <= 21 && (*banker).calculate() > 21) {
                        cout << " ~ Congratulations! You win!" << endl;
                        (*player).balance += bet;
                        win_count++;
                    }
                    else {
                        (*player).balance += comparison(results[i], (*banker).calculate(), bet, win_count);
                    }

                }
            }
            results.clear();
        }
        else {
            //codes2
            normProcess(min, max, root, bet, player, banker, win_count);
        }
    }
    else { //codes2
        string double_bet;
        cout << " ~ Double the bet(Input Y or N): " << endl;
        cin >> double_bet;
        if (double_bet == "Y") {
            bet *= 2;
            //codes need
            (*player).add_card(AC.Allocate(min, max, root));
            // starts to compare. need to repeat the comparision part, which can be put into a function.
            cout << "New card: " << (*player).get_cards()[(*player).get_cards().size() - 1] << " | Your total point: " << (*player).calculate() << endl;
            if ((*player).calculate() > 21){
                cout << " ~ Sorry, you lose (T⌓T)" << endl;
                (*player).balance -= bet;
            }
            else {
                Banker_card(min, max, root, banker);
                if ((*banker).calculate() > 21) {
                    cout << " ~ Congratulations! You win! ^_^" << endl;
                    (*player).balance += bet;
                }
                else {
                    (*player).balance += comparison((*player).calculate(), (*banker).calculate(), bet, win_count);
                }
            }
        }
        else {
            normProcess(min, max, root, bet, player, banker, win_count);
        }
    }
}


int main() {
    int min = 1, max = 208, sum; //参数范围？
    Player player;
    Banker banker;
    AllocationSystem AC;
    double buy_in, bet = 0;
    int total_games = 0, win_count = 0;
    BST_Tree* root = AC.Initialisation();
    cout << "----- Welcome to HKU Blackjack game! ----- " << endl;
    cout << " ~ Game Start" << endl;
    cout << " ~ Please input your buy-in amount: " << endl;
    cin >> buy_in;
    player.balance = buy_in;
    while (bet != -1) {
        cout << " ~ Your total balance is: " << player.balance << endl;
        cout << " ~ Place your bet(or input -1 to exit): " << endl;
        cin >> bet;
        if ( bet <= player.balance && bet > 0){
            cout << "----------Game " << total_games + 1 << "----------" << endl;
            for (int i = 0; i < 2; i++) {
                player.add_card(AC.Allocate(min, max, root));
            }
            for (int i = 0; i < 2; i++) {
                banker.add_card(AC.Allocate(min, max, root));
            }
            cout << " ~ Your card is " << player.get_cards()[0] << ", " << player.get_cards()[1] << endl;
            cout << " ~ banker's card is " << banker.get_cards()[0] << ", " << "*" << endl;
            sum = player.calculate();
            if (sum == 21) {
                cout << " ~ Congradulations! You win with Blackjack!" << endl;
                player.balance += 1.5 * bet;
                win_count++;
                //code needs
            }
            else {
                string surrender;
                cout << " ~ Choose to surrender?(Input Y or N)" << endl;
                cin >> surrender;
                if (surrender == "Y") {
                    player.balance -= 0.5 * bet;
                }
                else {
                    if (banker.get_cards()[0][0] == 'A') {
                        string insurance;
                        cout << " ~ Buy insurance(Input Y or N): " << endl;
                        cin >> insurance;
                        if (insurance == "Y") {
                            if (banker.calculate() != 21) {
                                cout << " ~ Youe lose the insurance!" << endl;
                                player.balance -= bet / 2;
                                //codes
                                codes(min, max, root, bet, &player, &banker, win_count);
                            }
                        }
                        else {
                            //codes
                            codes(min, max, root, bet, &player, &banker, win_count);
                        }
                    }
                    else { //codes
                        codes(min, max, root, bet, &player, &banker, win_count);
                    }
                }
            }
            player.clear_cards();
            banker.clear_cards();
            total_games++; 
            cout << "----------End of game " << total_games <<"----------" << endl;
        }
        else if (bet != -1)
            cout << " ~ Insufficient balance. Please choose your bet again." << endl;
    }
    return 0;
}
