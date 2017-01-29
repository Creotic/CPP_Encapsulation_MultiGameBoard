#include<iostream>
#include<vector>
#include "OthelloBoard.h"

using namespace std;

const int MID1 = 3;
const int MID2 = 4;

// Constructor - 5 Lines
OthelloBoard::OthelloBoard() :
mPassCount(0), mBoard() {
   GameBoard *b = dynamic_cast<OthelloBoard*>(this);
   if (b == nullptr)
      throw OthelloException("Tried to apply a non-OthelloMove.");

   this->mNextPlayer = 1;
   this->mValue = 0;

   mBoard[MID1][MID1] = WHITE;
   mBoard[MID2][MID2] = WHITE;
   mBoard[MID1][MID2] = BLACK;
   mBoard[MID2][MID1] = BLACK;
}

// GetPossibleMoves - 22 lines
void OthelloBoard::GetPossibleMoves(std::vector<GameMove *> *list) const {
   int row, col, opposingPlayer;

   // For loop to search the board
   for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
         // Bool to check if move is valid
         bool moveCheck = false;

         // If the board has a space, search in each direction
         if (mBoard[i][j] == 0) {
            for (int x = -1; x <= 1; x++) {
               for (int y = -1; y <= 1; y++) {
                  row = i, col = j, opposingPlayer = 0;

                  // Steps forward in one direction
                  if (x != 0 || y != 0) {
                     row = row + x;
                     col = col + y;
                  }

                  // While the board has not reached the end and 
                  // stepping forward has an opposing piece
                  while ((x != 0 || y != 0) && InBounds(row + x, col + y)
                     && mBoard[row][col] == mNextPlayer * -1) {
                     // Increment the opposingPlayer counter
                     opposingPlayer++;

                     // Step forward
                     row = row + x;
                     col = col + y;

                     // If the space has a player piece, it's a valid possible
                     // move so push the list back for the new move and
                     // sets moveCheck to true for next iteration
                     if (!moveCheck && mBoard[row][col] ==
                        mNextPlayer && opposingPlayer > 0) {
                        list->push_back(new OthelloMove(i, j));
                        moveCheck = true;
                     }
                  }
               }
            }
         }
      }
   }
   // If the size of vector (possible moves) is 0 push a pass.
   if (list->size() == 0)
      list->push_back(new OthelloMove());
}

// ApplyMove - 30 Lines
void OthelloBoard::ApplyMove(GameMove *move) {
   OthelloMove *dMove = dynamic_cast<OthelloMove*>(move);
   if (dMove == nullptr)
      throw OthelloException("Tried to apply non-OthelloMove.");

   if (dMove->IsPass()) {
      cout << "Passed." << endl;
      mPassCount++;
   }
   else {
      // opposing Player counter for determining FlipSets
      mPassCount = 0;
      int oppCount = 0, cP = mNextPlayer, oP = -cP;
      // Resets the counter
      // Applies the piece to the board
      mBoard[dMove->mRow][dMove->mCol] = mNextPlayer;

      // Double for-loop for checking each direction
      for (int i = -1; i <= 1; i++) {
         for (int j = -1; j <= 1; j++) {

            // If an opposing player piece is found set x and y
            // to keep moving forward in that direction
            if (mBoard[dMove->mRow + i][dMove->mCol + j] == oP) {
               int x = dMove->mRow, y = dMove->mCol;

               // For loop for moving forward in one direction
               for (;;) {
                  x = x + i;
                  y = y + j;
                  oppCount++;

                  // If the boundaries of the gameboard are
                  // reached, break the loop.
                  if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE
                     || mBoard[x][y] == 0)
                     break;

                  // This checks to see if there is a player piece at end
                  // If true, this moves back and flips the enemy pieces
                  // Otherwise, break the loop. 
                  if (mBoard[x][y] == cP) {
                     while (mBoard[x = x - i][y = y - j] == oP){
                        mBoard[x][y] = cP;
                        dMove->AddFlipSet(OthelloMove::FlipSet(oppCount, x, y));
                        oppCount--;
                     }
                     break;
                  }
               }
            }
         }
      }
   }

   mValue = 0;
   for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
         mValue += mBoard[i][j];
      }
   }
   // After apply move add to history vector
   mHistory.push_back(move);
   mNextPlayer *= -1;
}

// UndoLastMove - 21 lines
void OthelloBoard::UndoLastMove() {
   // Object pointer to the history vector
   OthelloMove *m = (OthelloMove*)mHistory.back();

   // If the player passes, pop back and move on to next player
   if (m->IsPass()) {
      delete m;
      mHistory.pop_back();
      mNextPlayer *= -1;
   }
   // Otherwise, flip the pieces back from each FlipSet and pop
   // according to the number of undo moves.
   else {
      for (OthelloMove::FlipSet &s : m->mFlips) {
         // Assign temporary row and col values for flipping
         int tempRow = m->mRow + s.rowDelta;
         int tempCol = m->mCol + s.colDelta;
         int opposingPlayer = s.switched;
         mBoard[m->mRow][m->mCol] = EMPTY;

         // Takes the opposingPlayer counter to determine how many
         // FlipSets were used to undo.
         while (opposingPlayer != 0) {
            mBoard[tempRow - (m->mRow)][tempCol - (m->mCol)] = mNextPlayer;
            opposingPlayer--;
         }
      }
      delete m;
      mNextPlayer = mNextPlayer * -1;
      mHistory.pop_back();
   }

   mValue = 0;
   for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
         mValue += mBoard[i][j];
      }
   }
}