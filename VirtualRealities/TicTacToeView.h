#ifndef __TICTACTOEVIEW_H
#define __TICTACTOEVIEW_H
#include "TicTacToeBoard.h"
#include "GameView.h"
#include <iostream>

// Same code as before; but now you just implement PrintBoard, and not
// operator<<.
class TicTacToeView : public GameView {
private:
   TicTacToeBoard *mTicTacToeBoard;
   virtual void PrintBoard(std::ostream &s) const;

public:
   TicTacToeView(GameBoard *b) : mTicTacToeBoard(dynamic_cast<TicTacToeBoard*>(b)) {}
};
#endif