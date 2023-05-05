#include<iostream> 
#include<string>
#include <sstream>
#include "banker.h"
using namespace std;

void Banker :: add_card(string card){
    cards.push_back(card);
}

void Banker :: clear_cards(){
    cards.clear();
}

vector<string> Banker :: get_cards(){
    return cards;
}

int Banker::calculate() {
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
}

