#include<iostream> 
#include<string>
#include <sstream>
#include "player.h"
using namespace std;

void Player :: add_card(string card){
    cards.push_back(card);
}

vector<string> Player :: get_cards(){
    return cards;
}

void Player :: clear_cards(){
    cards.clear();
}

int Player :: calculate(){
    int sum = 0;
    int count = 0;
    for (int i = 0; i < cards.size(); i++){
        if (cards[i][0] == 'K' || cards[i][0] =='Q' || cards[i][0] == 'J'){
            sum += 10;
        }
        else if (cards[i][0] == 'A'){
            count ++;
            sum += 11;
        }
        else{
            int x;
            istringstream(cards[i]) >> x;
            sum += x;
        }
    }
    while (sum > 21 && count > 0){
        sum -= 10;
        count --;
    }
    return sum;
}