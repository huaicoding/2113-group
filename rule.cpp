#include <iostream>
#include <string>
using namespace std;

int main(){
    cout << "-----------------------------------Rules-----------------------------------" << endl;
    cout << "" << endl;
    cout << "Processing: " << endl;
    cout << "           1.Shuffle the cards" << endl;
    cout << "           2.Assign the first card to the player" << endl;
    cout << "           3.Assign the first card to the banker, which need to show it to the player" << endl;
    cout << "           4.Assign the second card to the player" << endl;
    cout << "           5.Assign the second card to the player, which no need to show it to the player" << endl;
    cout << "           6.If the first card of the banker is 'A', the player will be asked whether he/she want to buy insurance" << endl;
    cout << "           7.The player could choose 'Surrender', 'Double' or 'Split', etc." << endl;
    cout << "           8.The player choose whether countiue to hit or stand" << endl;
    cout << "           9.If the banker has less than 17 points, he has to add until he exceeds or equals 17 points" << endl;
    cout << "           10.If neither the player nor the banker have more than 21 points, compare the point sizes and let the person with higher point win and get the bet" << endl;
    cout << "           11.If the banker has more than 21 points and the player has less than 21 points, the player will win the bet directly" << endl;
    cout << "           12.If both the banker and the player have more than 21 points, then push" << endl;
    cout << "" << endl;
    cout << "" << endl;

    cout << "Point Calculation: " << endl;
    cout << "           'A' will be considered as 1 point or 11 points" << endl;
    cout << "           '2'-'10' will be considered as 2-10 points" << endl;
    cout << "           'J','Q' and 'K' will be considered as 10 points" << endl;
    cout << "           If the sum of the points is great than 21 points, it will be treated as 'Bust'" << endl;
    cout << "" << endl;
    cout << "" << endl;

    cout << "Special Rules: " << endl;
    cout << "       Insurance: " << endl;
    cout << "           When the banker's first card is an 'A', the player could choose to buy insurance with half of the bet." << endl;
    cout << "           If the banker is not a blackjack, the insurance money is immediately forfeited. If it is a blackjack, the player will gain the twice of the insurance." << endl;
    cout << "" << endl;
    cout << "       Double: " << endl;
    cout << "           The player could choose to increase his/her initial bet by 100%." << endl;
    cout << "           However, the player can only get one more card after double the bet." << endl;
    cout << "" << endl;
    cout << "       Split: " << endl;
    cout << "           If the player's first two cards have the same number of points, the player could choose to split the cards and creat two hands from a strating hand." << endl;
    cout << "           Each new hand gets another card so that the player has two starting hands. This requires an additional bet on the second hand." << endl;
    cout << "           The two hands are played out independently, and the bet on each hand is won or lost independently." << endl;
    cout << "" << endl;
    cout << "       Black Jack -- 21 points: " << endl;
    cout << "           If the sum of the player's first two cards is 21 points, it is a 'Black Jack'. The player wins immediaterly unless the banker also has one." << endl;
    cout << "           In the caes of a tie, bets are returned without adjustment." << endl;
    cout << "           A 'Black Jack' beats any hand that is not a 'Black Jack', even one with the point of 21" << endl;
    cout << "" << endl;
    cout << "---------------------------------------------------------------------------" << endl;

    return 0;
}
