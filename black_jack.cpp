#include <iostream>
#include <string>
#include <sstream>
#include <vector> 
#include <stdlib.h>
#include <time.h> 
#include "player.h"
#include "banker.h"
#include "AllocationSystem.h"
using namespace std;

void hitStand(int min, int &max, BST_Tree* root, Player *player){
    cout << "please chooose an action: hit/stand" << endl;
    string action;
    cin >> action;
    while ((* player).calculate() < 21){
        if (action == "hit"){
            (*player).add_card(Allocate(min, max, root));
            cout << "New card: " << (*player).get_cards()[(*player).get_cards().size()-1] << "total point: " << (*player).calculate() << endl;
            cin >> action;
        }
        else if (action == "stand"){
            cout << "Total point: " << (*player).calculate() << endl;
            break;
        }
        else{
            cout << "Incorrect action, please enter the correct action." << endl; 
            cin >> action;
        }      
    }
}

int comparison(int player, int banker, double bet){
    if (player > banker){
        cout << "Congratulations! You win!" << endl;
        return bet;

    }
    else if(player < banker){
        cout << "Sorry, you lose" << endl;
        return -bet;
    }
    else{
        cout << "Break even" << endl;
        return 0;
    }
    return 0;
}

void Banker_card(int &min, int &max, BST_Tree *root, Banker *banker){
    cout << "banker's cards: " << (*banker).get_cards()[0] << ", " << (*banker).get_cards()[1] << endl;
    while ((*banker).calculate() < 17){
        (*banker).add_card(Allocate(min, max, root));
        cout << "New card: " << (*banker).get_cards()[(*banker).get_cards().size()-1] << "total point: " << (*banker).calculate() << endl;
    }
}

void normProcess(int &min, int &max, BST_Tree *root, double bet, Player *player, Banker *banker){
    hitStand(min, max, root, player);
    if ((*player).calculate() > 21){
        cout << "Sorry, you lose" << endl;
        (*player).balance -= bet;
    }
    else{
        Banker_card(min, max, root, banker);
        if ((*banker).calculate() > 21){
            cout << "Congratulations! You win!" << endl;
            (*player).balance += bet;
        }
        else{
            (*player).balance += comparison((*player).calculate(), (*banker).calculate(), bet);
        }
    }
}

void codes(int &min, int &max, BST_Tree *root, double bet, Player *player, Banker *banker){
    string a = (*player).get_cards()[0];
    a.pop_back();
    string b = (*player).get_cards()[1];
    b.pop_back();
    if (a == b){
        string split;
        cout << "Split the card(Input Y or N): " << endl;
        cin >> split;
        if (split == "Y"){
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
            if (results[0] > 21 && results[1] > 21){
                //两局全爆牌
                cout << "Sorry, you lose" << endl;
                (*player).balance -= 2*bet;
                
            }
            else{
                //两个分别比，复制下面252-274，重复两次把两次分别比即可。
                for ( int i = 0; i < 2; i ++){
                    cout << "Hand " << i + 1 << endl;
                    Banker_card(min, max, root, banker);
                    if ( results[i] > 21 && (*banker).calculate() > 21 ){
                        cout << "Break even" << endl;
                    }
                    else if ( results[i] > 21 && (*banker).calculate() <= 21 ){
                        cout << "Sorry, you lose" << endl;
                        (*player).balance -= bet;
                    }
                    else if ( results[i] <= 21 && (*banker).calculate() > 21 ){
                        cout << "Congratulations! You win!" << endl;
                        (*player).balance += bet;
                    }
                    else{
                        (*player).balance += comparison(results[i], (*banker).calculate(), bet);
                    }
                    
                }
            }
            results.clear();
        }
        else{
            //codes2
            normProcess(min, max, root, bet, player, banker);
        }
    }
    else{ //codes2
        string double_bet;
        cout << "Double the bet(Input Y or N): " << endl;
        cin >> double_bet;
        if (double_bet == "Y"){
            bet *=2;
            //codes need
            (*player).add_card(Allocate(min, max, root));
            // starts to compare. need to repeat the comparision part, which can be put into a function.
            Banker_card(min, max, root, banker);
            if ((*banker).calculate() > 21){
                cout << "Congratulations! You win!" << endl;
                (*player).balance += bet;
            }
            else{
                (*player).balance += comparison((*player).calculate(), (*banker).calculate(), bet);
            }

        }
        else{
            normProcess(min, max, root, bet, player, banker);
        }
    }
}


int main(){
    int min = 0, max = 207, sum; //参数范围？
    Player player;
    Banker banker;
    AllocationSystem AC;
    double buy_in, bet;
    int total_games, win_count;
    BST_Tree* root = AC.Initialisation();
    cout << "----- Welcome to HKU Blackjack game! ----- " << endl;
    cout << "Game Start" << endl;
    cout << "Please input your buy-in amount: " << endl;
    cin >> buy_in;
    player.balance = buy_in;
    while (bet != -1){
        cout << "Place your bet(or input -1 to exit): " << endl;
        cin >> bet;
        while (bet > player.balance){
            cout << "Insufficient balance. Please choose your bet again: " << endl;
            cin >> bet;
        }
        Card *head = NULL;
        loading(head);
        for (int i = 0; i < 2; i++){
            player.add_card(dealer(min, max, head));
        }
        for (int i = 0; i < 2; i++){
            banker.add_card(dealer(min, max, head));
        }
        cout << "Your card is " << player.get_cards()[0] << ", " << player.get_cards()[1] << endl;
        cout << "banker's card is " << banker.get_cards()[0] << ", " << "*" << endl;
        sum = player.calculate();
        if (sum == 21){
            cout << "Congradulations! You win with Blackjack!" << endl;
            player.balance += 1.5*bet;
            //code needs
        }
        else{
            string surrender;
            cout << "Choose to surrender?(Input Y or N)" << endl;
            cin >> surrender;
            if (surrender == "Y"){
                player.balance -= 0.5*bet;
            }
            else{
                if (banker.get_cards()[0][0] == 'A'){
                    string insurance;
                    cout << "Buy insurance(Input Y or N): " << endl;
                    cin >> insurance;
                    if (insurance == "Y"){
                         if (banker.calculate() != 21){
                            cout << "Youe lose the insurance!" << endl;
                            player.balance -= bet/2;
                            //codes
                            codes(min, max, head, bet, &player, &banker);
                        }
                    }
                    else{
                        //codes
                        codes(min, max, head, bet, &player, &banker);
                    }
                }
                else{ //codes
                    codes(min, max, head, bet, &player, &banker);
                }
            }
        }
        player.clear_cards();
        banker.clear_cards();
    }
    return 0;
}
