#ifndef __TICTACTOEBOARD_H
#define __TICTACTOEBOARD_H

#include <vector>
#include "TicTacToeMove.h"
#include "GameBoard.h"
#include "GameMove.h"

const int TBOARD_SIZE = 3;

class TicTacToeBoard : public GameBoard {

public:
   enum Player { EMPTY = 0, X = 1, O = -1 };

   // Default constructor initializes the board to its starting "new game" state
   TicTacToeBoard();


   virtual void GetPossibleMoves(std::vector<GameMove *> *list) const;
   /*
   Applies a valid move to the board, updating the board state accordingly.
   You may assume that this move is valid.
   */
   virtual void ApplyMove(GameMove *move);

   /*
   Undoes the last move applied to the board, restoring it to the state it was
   in prior to the most recent move.
   */
   virtual void UndoLastMove();

   /*
   Creates an TicTacToeMove object on the heap. Whoever calls this method is
   responsible for managing the move's lifetime (or transferring that task to
   someone else.)
   */
   virtual GameMove *CreateMove() const { return new TicTacToeMove; }

   inline static bool InBounds(int row, int col) {
      return row >= 0 && row < TBOARD_SIZE && col >= 0 && col < TBOARD_SIZE;
   }

   // Returns true if the game is finished.
   virtual bool IsFinished() const {
      return (mValue == 1 || mValue == -1 || IsFull());
   }

   virtual std::string GetPlayerString(char player) {
      return (player == 1 ? "X" : "O");
   }

   virtual bool IsWinner() const;
   virtual bool IsFull() const;

private:
   friend class TicTacToeView;

   // NOTE: we inherit mNextPlayer, mValue, and mHistory from GameBoard.
   char mBoard[TBOARD_SIZE][TBOARD_SIZE];
};
#endif