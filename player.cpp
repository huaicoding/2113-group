#include<iostream> 
#include<string>
#include <sstream>
#include "player.h"
using namespace std;

void Player :: add_card(string card){
    cards.push_back(card);
}
// add one card to the cards that player holds
vector<string> Player :: get_cards(){
    return cards;
}
// get the cards that player holds, which is in form of a vector string

void Player :: clear_cards(){
    cards.clear();
}
// clear all the cards that the player holds

int Player::calculate() {
    int sum = 0;
    int count = 0;
    for (int i = 0; i < cards.size(); i++) {
        if (cards[i][1] == 'K' || cards[i][1] == 'Q' || cards[i][1] == 'J') {
            sum += 10;
        }
        else if (cards[i][1] == 'A') {
            count++;
            sum += 11;
        }
        else {
            int x;
            istringstream(cards[i].substr(1)) >> x;
            sum += x;
        }
    }
    while (sum > 21 && count > 0) {
        sum -= 10;
        count--;
    }
    return sum;
} // calculate the total points of the cards that player holds


void Player :: keep_first(){
    // used in split, need to form two vectors, which only keep the first card.
    vector <string>::iterator k = cards.begin();
    cards.assign(k, k + 1);
}
