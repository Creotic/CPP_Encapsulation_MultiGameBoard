#include<iostream>
#include "TicTacToeView.h"
using namespace std;

void TicTacToeView::PrintBoard(std::ostream &s) const {
   // Prints the board
   s << "\n- 0 1 2";
   for (int i = 0; i < TBOARD_SIZE; i++) {
      s << endl << i;
      for (int j = 0; j < TBOARD_SIZE; j++) {
         s << " ";
         if (mTicTacToeBoard->mBoard[i][j] == 1)
            s << "X";
         else if (mTicTacToeBoard->mBoard[i][j] == -1)
            s << "O";
         else
            s << ".";
      }
   }
   s << endl << endl;
}