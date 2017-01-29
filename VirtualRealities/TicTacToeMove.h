#ifndef __TICTACTOEMOVE_H
#define __TICTACTOEMOVE_H
#include "GameMove.h"
#include <string>
#include <vector>
#include <iostream>
/*
An TicTacToeMove encapsulates a single potential move on an TicTacToeBoard. It
is represented internally by a row and column, both 0-based.
*/
class TicTacToeMove : public GameMove {
private:
   // TicTacToeBoard is a friend so it can access mRow and mCol.
   friend class TicTacToeBoard;

   int mRow, mCol;

   // KEEP THESE CONSTRUCTORS PRIVATE.
   // Default constructor: initializes this move as a PASS.
   TicTacToeMove();
   /*
   2-parameter constructor: initializes this move with the given
   row and column.
   */
   TicTacToeMove(int row, int col);

public:
   static int mOnHeap;

   static void* operator new(std::size_t sz){
      mOnHeap++;
      std::cout << "operator new: " << mOnHeap << " TicTacToeMoves on the heap" << std::endl;
      return ::operator new(sz);
   }

   static void operator delete(void* ptr, std::size_t sz) {
      mOnHeap--;
      std::cout << "operator delete: " << mOnHeap << " TicTacToeMoves on the heap" << std::endl;
      ::operator delete(ptr);
   }

   /*
   This assignment operator takes a string representation of an TicTacToeMove
   and uses it to initialize the move. The string is in the format
   (r, c);
   */
   virtual GameMove& operator=(const std::string &);

   /*
   Compares two TicTacToeMove objects for equality.
   */
   virtual bool Equals(const GameMove &other) const;

   // Converts the TicTacToeMove into a string representation, one that could be
   // used correctly with operator=(string). Returns "pass" if move is a pass.
   virtual operator std::string() const;
};

#endif