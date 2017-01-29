#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include "TicTacToeMove.h"
#include "TicTacToeBoard.h"
#include "GameExceptions.h"

using namespace std;

int TicTacToeMove::mOnHeap = 0;

// Default Constructor
TicTacToeMove::TicTacToeMove() {
   // Passes
   mRow = -1;
   mCol = -1;
}

// Constructor
TicTacToeMove::TicTacToeMove(int row, int col) {
   // Sets the row and col to member variables
   mRow = row;
   mCol = col;
}

// Assignment = overload - 11 lines
GameMove& TicTacToeMove::operator=(const std::string &move) {
   char temp;
   istringstream in(move);

   // Takes the user move input using throwaway temp values
   // while assigning the numbers inputted to mRow and mCol
   in >> temp >> mRow >> temp >> mCol >> temp;
   if (TicTacToeBoard::InBounds(mRow, mCol))
      // Since we're using pointers we return the *this pointer to the OBJECT
      // POINTER
      return *this;
   else
      // Throw exception if the move is invalid
      throw TicTacToeException("Invalid move!");
}

bool TicTacToeMove::Equals(const GameMove &other) const {
   const TicTacToeMove &dOther = dynamic_cast<const TicTacToeMove&>(other);
   return((mRow == dOther.mRow) && (mCol == dOther.mCol));
}

// String overload - 4 lines
TicTacToeMove::operator string() const {
   return ("(" + to_string(mRow) + "," + to_string(mCol) + ")");
}


