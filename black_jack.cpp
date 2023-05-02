#include <iostream>
#include <string>
#include <sstream>
#include <vector> 
#include <stdlib.h>
#include <time.h> 
#include "player.h"
#include "banker.h"
using namespace std;

struct Card{
    string rank;
    char suite;
    Card *next;
};


int random_num_generator(int min, int max){
    srand((unsigned)time(NULL)); 
    int range = max - min + 1;
    return rand() % range + min;
}

string dealer(int min, int &max, Card *head){
    int index = random_num_generator(min, max);
    Card *current = head, *previous = NULL;
    for (int i = 0; i < index; i++){
        previous = current;
        current = current -> next;
    }
    string card = current -> rank + current -> suite;
    previous -> next = current -> next;
    delete current;
    max --;
    return card;
}

void headInsert(Card *&head, string rank, char suite){
    Card *pNode = new Card;
    pNode -> rank = rank;
    pNode -> suite = suite;
    pNode -> next = head;
    head = pNode;
}

void loading(Card *&head){
    for (int i = 2; i < 11; i++){
        for (int j = 0; j < 16; j++){
            if (j % 4 == 0){
                headInsert(head, to_string(i),'h');
            }
            else if (j % 4 == 1)
            {
                headInsert(head, to_string(i),'s');
            }
            else if (j % 4 == 2){
                headInsert(head, to_string(i),'d');
            }
            else{
                headInsert(head, to_string(i),'c');
            } 
        }
    }
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 16; j++){
            if (i == 0){
                 if (j % 4 == 0){
                    headInsert(head, "A",'h');
                }
                else if (j % 4 == 1){
                    headInsert(head,"A",'s');
                }
                else if (j % 4 == 2){
                    headInsert(head, "A",'d');
                }
                else{
                    headInsert(head, "A",'c');
                } 
            }
            else if(i == 1){
                 if (j % 4 == 0){
                    headInsert(head, "K",'h');
                }
                else if (j % 4 == 1){
                    headInsert(head,"K",'s');
                }
                else if (j % 4 == 2){
                    headInsert(head, "K",'d');
                }
                else{
                    headInsert(head, "K",'c');
                } 
            }
            else if(i == 2){
                 if (j % 4 == 0){
                    headInsert(head, "Q",'h');
                }
                else if (j % 4 == 1){
                    headInsert(head,"Q",'s');
                }
                else if (j % 4 == 2){
                    headInsert(head, "Q",'d');
                }
                else{
                    headInsert(head, "Q",'c');
                } 
            }
            else{
                 if (j % 4 == 0){
                    headInsert(head, "J",'h');
                }
                else if (j % 4 == 1){
                    headInsert(head,"J",'s');
                }
                else if (j % 4 == 2){
                    headInsert(head, "J",'d');
                }
                else{
                    headInsert(head, "J",'c');
                } 
            }

        }
    }
}

void hitStand(){
    cout << "please chooose an action: hit/stand" << endl;
    string action;
    cin >> action;
    while (player.calculate() < 21){
        if (action == "hit"){
            player.add_card(dealer(min, max, head));
            cout << "New card: " << player.get_cards()[player.get_cards().size()-1] << "total point: " << player.calculate() << endl;
            cin >> action;
        }
        else if (action == "stand"){
            cout << "Total point: " << player.calculate() << endl;
            break;
        }
        else{
            cout << "Incorrect action, please enter the correct action." << endl; 
            cin >> action;
        }      
    }
}


int main(){
    int min = 0, max = 207, sum;
    Player player;
    Banker banker;
    double buy_in, bet;
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
                            player.balance -= bet/2;
                            //codes
                         }
                    }
                    else{
                            //codes
                    }
                }
                else{ //codes
                    string a = player.get_cards()[0];
                    a.pop_back();
                    string b = player.get_cards()[1];
                    b.pop_back();
                    if (a == b){
                        string split;
                        cout << "Split the card(Input Y or N): " << endl;
                        cin >> split;
                        if (split == "Y"){
                            // codes for split play
                            vector<int> results;
                            player.keep_first();
                            // repeating from 208-242(stand or hit);
                            hitStand();
                            result.push_back(player.calculate());
                            player.keep_first();
                            // repeat
                            hitStand();
                            result.push_back(player.calculate());
                            if (result[0] > 21 && result[1] > 21){
                                //两局全爆牌
                                cout << "Sorry, you lose" << endl;
                                player.balance -= 2*bet;
                                player.clear_cards();
                                banker.clear_cards();
                            }
                            else{
                                //两个分别比，复制下面252-274，重复两次把两次分别比即可。
                                
                            }
                        else{
                            //codes2
                        }
                    }
                    else{ //codes2
                        string double_bet;
                        cout << "Double the bet(Input Y or N): " << endl;
                        cin >> double_bet;
                        if (double_bet == "Y"){
                            bet *=2;
                            //codes need
                            player.add_card(dealer(min, max, head));
                            // starts to compare. need to repeat the comparision part, which can be put into a function.
                        }
                        else{
                            hitStand();
                            if (player.calculate() > 21){
                                cout << "Sorry, you lose" << endl;
                                player.balance -= bet;
                                player.clear_cards();
                                banker.clear_cards();
                            }
                            else{
                                cout << "banker's cards: " << banker.get_cards()[0] << ", " << banker.get_cards()[1] << endl;
                                while (banker.calculate() < 17){
                                    banker.add_card(dealer(min, max, head));
                                    cout << "New card: " << banker.get_cards()[banker.get_cards().size()-1] << "total point: " << banker.calculate() << endl;
                                }
                                if (banker.calculate() > 21){
                                    cout << "Congratulations! You win!" << endl;
                                    player.balance += bet;
                                    player.clear_cards();
                                    banker.clear_cards();
                                }
                                else{
                                    if (player.calculate() > banker.calculate()){
                                        cout << "Congratulations! You win!" << endl;
                                        player.balance += bet;
                                        player.clear_cards();
                                        banker.clear_cards();
                                    }
                                    else if(player.calculate() < banker.calculate()){
                                        cout << "Sorry, you lose" << endl;
                                        player.balance -= bet;
                                        player.clear_cards();
                                        banker.clear_cards();
                                    }
                                    else{
                                        cout << "Break even" << endl;
                                        player.clear_cards();
                                        banker.clear_cards();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
}
                /*
                string double_bet;
                cout << "Double the bet(Input Y or N): " << endl;
                cin >> double_bet;
                if (double_bet == "Y"){
                    

                }
                string a = player.get_cards()[0];
                a.pop_back();
                string b = player.get_cards()[1];
                b.pop_back();
                if (a == b){
                    string split;
                    cout << "Split the card(Input Y or N): " << endl;
                    cin >> split;
                    if (split == "Y"){
                        if (banker.get_cards()[0][0] == 'A'){
                            string insurance;
                            cout << "Buy insurance(Input Y or N): " << endl;
                            cin >> insurance;
                            if (insurance == "Y"){
                                my_insurance = true;
                            }
                        }
                    }
                    else{
                        if (banker.get_cards()[0][0] == 'A'){
                            string insurance;
                            cout << "Buy insurance(Input Y or N): " << endl;
                            cin >> insurance;
                            if (insurance == "Y"){
                                my_insurance = true;
                            }
                        }

                    }
                }
                else{
                    if (banker.get_cards()[0][0] == 'A'){
                        string insurance;
                        cout << "Buy insurance(Input Y or N): " << endl;
                        cin >> insurance;
                        if (insurance == "Y"){
                            my_insurance = true;
                        }
                    }
                }
            }
        }
    }
    */
    /*
    Card *current;
    current = head;
    int count = 0;
    while (current != NULL){
        cout << current-> rank << current -> suite << endl;
        count ++;
        current = current -> next;  
    } 
    cout << count << endl;
    */
    
    return 0;
}
