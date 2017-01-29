#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include "OthelloMove.h"
#include "OthelloBoard.h"
#include "GameExceptions.h"

using namespace std;

int OthelloMove::mOnHeap = 0;

// Default Constructor
OthelloMove::OthelloMove() {
   // Passes
   mRow = -1;
   mCol = -1;
}

// Constructor
OthelloMove::OthelloMove(int row, int col) {
   // Sets the row and col to member variables
   mRow = row;
   mCol = col;
}

// Assignment = overload - 11 lines
GameMove& OthelloMove::operator=(const std::string &move) {
   char temp;
   istringstream in(move);

   // If the move is a pass
   if (move == " pass") {
      mRow = -1;
      mCol = -1;
      return *this;
   }

   // Takes the user move input using throwaway temp values
   // while assigning the numbers inputted to mRow and mCol
   in >> temp >> mRow >> temp >> mCol >> temp;
   if (OthelloBoard::InBounds(mRow, mCol))
      // Since we're using pointers we return the *this pointer to the OBJECT
      // POINTER
      return *this;
   else
      // Throw exception if the move is invalid
      throw OthelloException("Invalid move!");
}

bool OthelloMove::Equals(const GameMove &other) const {
   const OthelloMove &dOther = dynamic_cast<const OthelloMove&>(other);
   return((mRow == dOther.mRow) && (mCol == dOther.mCol));
}

// String overload - 4 lines
OthelloMove::operator string() const {
   if (OthelloMove::IsPass())
      return "pass";
   else
      return ("(" + to_string(mRow) + "," + to_string(mCol) + ")");
}


