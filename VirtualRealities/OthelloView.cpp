#include<iostream>
#include "OthelloView.h"
using namespace std;

void OthelloView::PrintBoard(std::ostream &s) const {
   // Prints the board
   s << "\n- 0 1 2 3 4 5 6 7";
   for (int i = 0; i < BOARD_SIZE; i++) {
      s << endl << i;
      for (int j = 0; j < BOARD_SIZE; j++) {
         s << " ";
         if (mOthelloBoard->mBoard[i][j] == 1)
            s << "B";
         else if (mOthelloBoard->mBoard[i][j] == -1)
            s << "W";
         else
            s << ".";
      }
   }
   s << endl << endl;
}