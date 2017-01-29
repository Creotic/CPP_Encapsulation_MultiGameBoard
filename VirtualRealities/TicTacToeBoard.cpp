#include<iostream>
#include<vector>
#include "TicTacToeBoard.h"

using namespace std;

// Constructor - 5 Lines
TicTacToeBoard::TicTacToeBoard() : mBoard() {
   GameBoard *b = dynamic_cast<TicTacToeBoard*>(this);
   if (b == nullptr)
      throw TicTacToeException("Tried to apply a non-TicTacToeMove.");

   this->mNextPlayer = 1;
   this->mValue = 0;

}

// GetPossibleMoves - 22 lines
void TicTacToeBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {

   // For loop to search the board
   for (int i = 0; i < TBOARD_SIZE; i++) {
      for (int j = 0; j < TBOARD_SIZE; j++) {

         // If the board has a space, search in each direction
         if (mBoard[i][j] == 0)
            list->push_back(new TicTacToeMove(i, j));
      }
   }
}

// ApplyMove - 30 Lines
void TicTacToeBoard::ApplyMove(GameMove *move) {
   TicTacToeMove *dMove = dynamic_cast<TicTacToeMove*>(move);
   if (dMove == nullptr) {
      throw TicTacToeException("Tried to apply non-TicTacToeMove.");
   }
   else {
      // Applies the piece to the board
      mBoard[dMove->mRow][dMove->mCol] = mNextPlayer;
   }
   
   bool winner = IsWinner();
   if (winner)
      mValue += mNextPlayer;

   // After apply move add to history vector
   mHistory.push_back(move);
   mNextPlayer *= -1;
}

// UndoLastMove - 21 lines
void TicTacToeBoard::UndoLastMove() {
   // Object pointer to the history vector
   TicTacToeMove *m = (TicTacToeMove*)mHistory.back();

   mBoard[m->mRow][m->mCol] = EMPTY;

   delete m;
   mNextPlayer = mNextPlayer * -1;
   mHistory.pop_back();
}

bool TicTacToeBoard::IsWinner() const {
   bool winner = false;

   for (int i = 0; i < 3; i++) {
      if (mBoard[i][0] == mNextPlayer && mBoard[i][1] == mNextPlayer && mBoard[i][2] == mNextPlayer) {
         winner = true;
         return winner;
         break;
      }
   }
   for (int i = 0; i < 3; i++) {
      if (mBoard[0][i] == mNextPlayer && mBoard[1][i] == mNextPlayer && mBoard[2][i] == mNextPlayer) {
         winner = true;
         return winner;
         break;
      }
   }
   if ((mBoard[0][0] == mNextPlayer && mBoard[1][1] == mNextPlayer && mBoard[1][1] == mNextPlayer && mBoard[2][2] == mNextPlayer) ||
      (mBoard[0][2] == mNextPlayer && mBoard[1][1] == mNextPlayer && mBoard[1][1] == mNextPlayer && mBoard[2][0] == mNextPlayer)) {
      winner = true;
      return winner;
   }
   else
      winner = false;

   return winner;
}

bool TicTacToeBoard::IsFull() const {
   bool full = true;
   for (int i = 0; i < TBOARD_SIZE; i++) {
      for (int j = 0; j < TBOARD_SIZE; j++) {
         if (mBoard[i][j] == EMPTY)
            full = false;
      }
   }

   return full;
}