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



