#include<string>
#include <vector>
using namespace std;

class Banker{
    private:
        vector<string> cards;
    public:
        void add_card(string card);
        void clear_cards();
        vector<string> get_cards();
        int calculate();
};