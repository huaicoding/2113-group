#include<string>
#include <vector>
using namespace std;

class Player{
    private:
        vector<string> cards;
    public:
        double balance;
        bool insurance = false;
        void add_card(string card);
        void clear_cards();
        vector<string> get_cards();
        int calculate();
};