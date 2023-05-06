#include <iostream>
#include <string>
#include <sstream>
#include <vector> 
#include <stdlib.h>
#include <typeinfo>
#include <time.h> 
#include <fstream> 
#include "player.h"
#include "banker.h"
#include "AllocationSystem.h"
using namespace std;

//Function to choose to add or stop adding cards
void hitStand(int min, int& max, BST_Tree* root, Player* player) {  //Input the maximum and minimum values of the current card. Generate a root of the BST. Input the information of the player
    AllocationSystem AC;  
    cout << " ~ Please chooose an action: hit/stand" << endl;
    string action;
    while ((*player).calculate() < 21) {  //If the player's hand is not greater than 21 points, the player will be given the option to add or stop adding cards
        getline(cin,action);  //Read the input of the player's actions
        if (action == "hit") {
            (*player).add_card(AC.Allocate(min, max, root));  //Distribute a card to the player
            cout << "New card: " << (*player).get_cards()[(*player).get_cards().size() - 1] << " | Your total point: " << (*player).calculate() << endl;  //  Show the newly assigned card and calculate the total points of the current hand
        }
        else if (action == "stand") {
            cout << "Total point: " << (*player).calculate() << endl;  //Displaying and calculating the player's hand points
            break;
        }
        else {
            cout << " ~ Incorrect action, please enter the correct action." << endl;
        }
    }
}

int comparison(int player, int banker, double bet, int& win_count) { 
    if (player > banker) {
        cout << " ~ Congratulations! You win! ^_^" << endl;
        win_count++;
        return bet;
    }
    else if (player < banker) {
        cout << " ~ Sorry, you lose (T⌓T)" << endl;
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
        cout << " ~ Sorry, you lose (T⌓T)" << endl;
        (*player).balance -= bet;
    }
    else {
        Banker_card(min, max, root, banker);
        if ((*banker).calculate() > 21) {
            cout << " ~ Congratulations! You win! ^_^" << endl;
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
        getline(cin, split);
        while (split != "Y" && split != "N"){
            cout << " ~ Invalid option, please input Y for split and N for not split." << endl;
            getline(cin, split);
        }
        if (split == "Y") {
            // codes for split play
            vector<int> results;
            (*player).keep_first();
            // repeating from (stand or hit);
            cout << " ~ Game 1" << endl;
            hitStand(min, max, root, player);
            results.push_back((*player).calculate());
            (*player).keep_first();
            // repeat
            cout << " ~ Game 2" << endl;
            hitStand(min, max, root, player);
            results.push_back((*player).calculate());
            if (results[0] > 21 && results[1] > 21) {
                cout << " ~ Sorry, you lose (T⌓T)" << endl;
                (*player).balance -= 2 * bet;

            }
            else {
                Banker_card(min, max, root, banker);
                for (int i = 0; i < 2; i++) {
                    cout << " ~ Hand " << i + 1 << endl;
                    if (results[i] > 21 && (*banker).calculate() > 21) {
                        cout << " ~ Break even" << endl;
                    }
                    else if (results[i] > 21 && (*banker).calculate() <= 21) {
                        cout << " ~ Sorry, you lose (T⌓T)" << endl;
                        (*player).balance -= bet;
                    }
                    else if (results[i] <= 21 && (*banker).calculate() > 21) {
                        cout << " ~ Congratulations! You win! ^_^" << endl;
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
        getline (cin, double_bet);
        while (double_bet != "Y" && double_bet != "N"){
            cout << " ~ Invalid option, please input Y for double and N for not double." << endl;
            getline (cin, double_bet);
        }
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

bool InvalidInput(string input){  //Avoid players entering incorrect text, such as spaces and non-numeric characters
    for (int i = 0; i < input.length(); i++){
            if (!(isdigit(input[i]))){
                cout << "Invalid input, please input again." << endl;
                return true;
            }
    }
    return false;
}

void cash_in() { //To view the player's game history
    string line;
    ifstream fin;
    fin.open("cash_out_result.txt"); 
    if (fin.fail())
        cout << "Fail to open the file." << endl;
    else {
        while (getline(fin, line)) //Output the game logs recorded in the txt
            cout << line << endl;
    }
    fin.close();
}

void cash_out_result(int total_games, int win_count, double buy_in, double balance){  //Input the total number of games played, the number of games won by the player, and the initial capital and remaining balance
  ofstream fout;
  double score = buy_in - balance; 
  fout.open("cash_out_result.txt");  //Enter the total number of games played, the number of games won by the player
  if (fout.fail()){
    cout << "Error in opening the file !" << endl;
    }
  else{
    fout << "-------------------------Game Result-----------------------------" << endl;
    fout << "You have played " << total_games << " games in total." << endl;
    fout << "You have won " << win_count << " games in total." << endl;
    if (score < 0){
      score = -score;
      fout << "You have won " << score << " ." << endl;
    }
    else if (score >= 0){
      fout << "You have lost " << score << " ." << endl;
    }
    fout << "-----------------------------------------------------------------" << endl;
  }
  fout.close();
}

int main() {
    int min = 1, max = 208, sum, residual; //Range for cards
    Player player;
    Banker banker;
    AllocationSystem AC;
    double buy_in, bet = 0;
    int total_games = 0, win_count = 0;
    BST_Tree* root = AC.Initialisation();
    cout << "----- Welcome to HKU Blackjack game! ----- " << endl;
    cout << " ~ Game Start" << endl;
    cout << " ~ Please input your buy-in amount: " << endl;
    string input1;
    getline(cin,input1); //Read the capital entered by the player
    while (InvalidInput(input1))
        getline(cin,input1); 
    buy_in = stod(input1);  //Changing the type of numbers in the string
    player.balance = buy_in;
    string input2;
    while (bet != -1) {  
        cout << " ~ Your total balance is: " << player.balance << endl;
        cout << " ~ Place your bet(or input -1 to exit): " << endl;
        getline(cin,input2);  //Read the bet entered by the player
        if (input2 == "-1")
            break;  //Players choose whether to quit the game
        while (InvalidInput(input2))
            getline(cin,input2);
        bet = stod(input2);  //Changing the type of numbers in the string
        if ( bet <= player.balance && bet > 0){  //Determine if the player has a positive bet and enough capital to cover the bet
            cout << "----------Game " << total_games + 1 << "----------" << endl;
            residual = AC.Remained_cards();  
            cout << "Cards remained: " << residual << endl;  //Show the total number of cards remaining
            for (int i = 0; i < 2; i++) {
                player.add_card(AC.Allocate(min, max, root));  //Distributing cards to the player
            }
            for (int i = 0; i < 2; i++) {
                banker.add_card(AC.Allocate(min, max, root));  //Distributing cards to the banker
            }
            //The player checks his or her cards and the banker's first card
            cout << " ~ Your card is " << player.get_cards()[0] << ", " << player.get_cards()[1] << " | Your points is: " << player.calculate()<< endl;
            cout << " ~ banker's card is " << banker.get_cards()[0] << ", " << "*" << endl;
            sum = player.calculate();
            if (sum == 21) {
                cout << " ~ Congradulations! You win with Blackjack! ^_^" << endl;  //The player wins with "Black Jack"
                player.balance += 1.5 * bet; //The player gains 1.5 times the bet
                win_count++;
                
            }
            else {
                string surrender; 
                cout << " ~ Choose to surrender?(Input Y or N)" << endl;  //The player chooses whether to give up this round of game
                getline(cin,surrender); 
                while (surrender != "Y" && surrender != "N"){
                    cout << " ~ Invalid option, please input Y for surrender and N for not surrender." << endl;
                    getline(cin,surrender);
                }
                if (surrender == "Y") {
                    player.balance -= 0.5 * bet;  //If the player chooses to give up this round of, he/she will lose half of his/her bet
                }
                else {
                    if (banker.get_cards()[0][0] == 'A') {  //If the banker's first card is an A, then the player may consider whether to buy insurance
                        string insurance;
                        cout << " ~ Buy insurance(Input Y or N): " << endl;
                        getline(cin,insurance);
                        while (insurance != "Y"&& insurance != "N"){
                            cout << " ~ Invalid option, please input Y for buying and N for not buying insurance." << endl;
                            getline(cin,insurance);
                        }
                        if (insurance == "Y") {
                            if (banker.calculate() != 21) {
                                cout << " ~ Youe lose the insurance! (T⌓T)" << endl;
                                player.balance -= bet / 2; //If the banker is not "Black Jack", then the player loses an additional half of the bet
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
            residual = AC.Remained_cards();
            if (residual < 188) {  //If the number of cards remaining is less than 188, we will reshuffle the deck. It prevents the player from remembering the category of the remaining cards
                root = AC.Initialisation();
                cout << "Card shuffled" << endl;
            }
        }
        else if (bet != -1)
            cout << " ~ Insufficient balance. Please choose your bet again." << endl;             
    }
    
    cash_out_result(total_games, win_count, buy_in, player.balance); 
    cout << "----------End of the game!----------" << endl;
    string choise;
    cout << " ~ Do you want to check your performance? (Input Y or N)" << endl;
    getline(cin,choise);
    while (choise != "Y" && choise != "N"){
        cout << "Invalid input, please input again." << endl;
        getline(cin,choise);
    }
    if (choise == "Y"){
        cash_in();
    }


    return 0;
}
