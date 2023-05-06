# 2113-group

Team members:
Wu Shuyang UID:3035835002
Wu Jingbo UID:3035845045
Huai Chengtian UID:3035845978
Fong Chi Hong UID:3035923330

------------------------------------------------------------Rules------------------------------------------------------------

Process: 
           1.Shuffle the cards
           2.Assign the two cards to the player
           3.Assign the two cards to the banker, the first card to be assigned needs to be shown to the player
           4.If the first card of the banker is 'A', the player will be asked whether he/she want to buy insurance
           5.The player could choose 'Surrender', 'Double' or 'Split', etc.
           6.The player choose whether countiue to hit or stand
           7.If the banker has less than 17 points, he has to add until he exceeds or equals 17 points
           8.If neither the player nor the banker have more than 21 points, compare the point sizes and let the person with higher point win and get the bet
           9.If the banker has more than 21 points and the player has less than 21 points, the player will win the bet directly
           10.If the player has more than 21 points and the banker has less than 21 points, the player will lose the bet directly
           11.If both the banker and the player have more than 21 points, then push


Point Calculation: 
           'A' will be considered as 1 point or 11 points
           '2'-'10' will be considered as 2-10 points
           'J','Q' and 'K' will be considered as 10 points
           For the initial two cards, if one of the cards is an 'A', then it will be treated as 11 points. 
           If the total number of points is greater than 21 points after adding other cards, the 'A' will be treated as 1 points.
           If the sum of the points is great than 21 points, it will be treated as 'Bust'


Special Rules: 
       Insurance: 
           When the banker's first card is an 'A', the player could choose to buy insurance with half of the bet.
           If the banker is not a blackjack, the insurance money is immediately forfeited. If it is a blackjack, the player will gain the twice of the insurance.

       Double: 
           The player could choose to increase his/her initial bet by 100%.
           However, the player can only get one more card after double the bet.

       Split: 
           If the player's first two cards have the same number of points, the player could choose to split the cards and creat two hands from a strating hand.
           Each new hand gets another card so that the player has two starting hands. This requires an additional bet on the second hand.
           The two hands are played out independently, and the bet on each hand is won or lost independently.

       Black Jack -- 21 points: 
           If the sum of the player's first two cards is 21 points, it is a 'Black Jack'. The player wins immediaterly unless the banker also has one.
           In the caes of a tie, bets are returned without adjustment.
           A 'Black Jack' beats any hand that is not a 'Black Jack', even one with the point of 21

-----------------------------------------------------------------------------------------------------------------------------

List of non-standard libraries:
#include <iostream> // used to input and output 
#include <string> // used to use data type string
#include <sstream> // used to support function istringstream
#include <vector> // to support the usage of vector
#include <time.h> // used to generate random number
#include <fstream> // used to support file in/out

