#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void cash_out_result(int total_games, int win_count, double buy_in, double balance){
  ofstream fout;
  double score = buy_in - balance;
  fout.open("cash_out_result.txt");
  if (fout.fail()){
    cout << "Error in opening the file !" << endl;
    }
  else{
    fout << "-------------------------Game Result-----------------------------" << endl;
    fout << "You have played " << total_games << " games in total." << endl;
    fout << "You have won " << win_count << " games in total." << endl;
    if (score =< 0){
      score = -score;
      fout << "You have won " << score << " ." << endl;
    }
    else if (score > 0){
      fout << "You have lost " << score << " ." << endl;
    }
    fout << "-----------------------------------------------------------------" << endl;
  }
  fout.close();
}
