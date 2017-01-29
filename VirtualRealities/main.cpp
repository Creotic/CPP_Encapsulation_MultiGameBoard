#include<iostream>
#include "GameExceptions.h"
#include "GameBoard.h"
#include "GameView.h"
#include "GameMove.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include "TicTacToeBoard.h"
#include "TicTacToeView.h"
#include "TicTacToeMove.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;


// main - 96 lines
int main(int argc, char* argv[]) {
   // Initialization
   GameBoard *board; // the state of the game board
   GameView *v; // a View for outputting the board via operator<<
   string userInput; // a string to hold the user's command choice
   char ans = ' ';
   vector<GameMove *> possMoves; // a holder for possible move
   int winner = 0, undo = 0, turns = 0;

Loop:
   while (ans != '3') {
      cout << "\nWhat game do you want to play? 1) Othello; 2) Tic Tac Toe; 3) Exit: ";
      cin >> ans;
      cin.ignore();

      if (ans == '1') {
         board = new OthelloBoard();
         v = new OthelloView(board);
      }
      else if (ans == '2') {
         board = new TicTacToeBoard();
         v = new TicTacToeView(board);
      }
      else if (ans == '3') {
         cout << "\nProgram terminated.\n\n";
         break;
      }
      else {
         cout << "\nPlease input a correct option!\n";
         goto Loop;
      }

      // Main loop
      do {
         // Print the game board using the OthelloView object
         cout << *v << endl;

         // Player's move
         cout << board->GetPlayerString(board->GetNextPlayer()) << "'s move\n\n";

         // Print all possible moves
         board->GetPossibleMoves(&possMoves);
         cout << "\nPossible moves: " << endl;
         vector<GameMove*>::const_iterator moves;
         for (moves = possMoves.begin(); moves != possMoves.end(); moves++)
            cout << (string)**moves << " ";
         cout << endl;

         // Ask to input a command
         cout << "\nEnter a command " <<
            "(move (r,c) undo #, showValue, showHistory, quit) ";
         getline(cin, userInput);
         cout << endl;

         // Command loop:
         // move (r,c)
         // Erase "move" to remove fluff input
         if (userInput.substr(0, 4) == "move") {
            userInput.erase(0, 4);
            // OthelloMove object pointer that points to a new OthelloMove object
            GameMove *m = board->CreateMove();
            // Bool checks for possible moves
            bool isValid = false;

            // Try block
            try {
               // Pointer assigned to user input
               *m = userInput;

               // Searches the vector for possible moves.
               for (moves = possMoves.begin(); moves != possMoves.end(); moves++){
                  auto poss = *moves;

                  // If any of the moves around the space is valid, show it.
                  if (*m == *poss) {
                     board->ApplyMove(m);
                     isValid = true;
                  }
                  // Also show if the player needs to pass
                  else if (userInput == " pass") {
                     board->ApplyMove(m);
                     isValid = true;
                     break;
                  }
               }

               // If the userInput is out of range, throw exception.
               if (!isValid) {
                  throw GameException("Invalid move! Try again.\n");
               }
            }
            // Catches the exception and output's the error.
            catch (const GameException &ex) {
               delete m;
               cout << ex.what() << endl;
            }
         }

         // undo n
         else if (userInput.substr(0, 4) == "undo") {
            istringstream(userInput.substr(4)) >> undo;

            if (undo > board->GetMoveCount())
               undo = board->GetMoveCount();

            // Undo's # of moves inputted
            for (int i = 0; i < undo; i++) {
               board->UndoLastMove();
            }
         }

         // showValue
         else if (userInput == "showValue")
            cout << "Score: " << board->GetValue() << endl;

         // showHistory
         else if (userInput == "showHistory") {
            // Object pointer to history
            const vector<GameMove*> *history = board->GetMoveHistory();
            // Declares a OthelloMove vector in REVERSE per guidelines
            vector<GameMove*>::const_reverse_iterator f;

            cout << "History: " << endl;
            int currentPlayer = board->GetNextPlayer();

            // for loop to search from the reversed vector
            // starting from the "beginning"
            for (f = (history->rbegin()); f != (history->rend()); f++) {
               if (currentPlayer == -1)
                  cout << board->GetPlayerString(1) << ": ";
               else if (currentPlayer == 1)
                  cout << board->GetPlayerString(0) << ": ";
               cout << (string)**f << endl;
               currentPlayer *= -1;
            }
            cout << endl;
         }

         // quit
         else if (userInput == "quit") {
            break;
         }

         // Delete's the pointers and clears them out
         for (int i = 0; i < possMoves.size(); i++)
            delete possMoves[i];
         possMoves.clear();

      } while (!board->IsFinished());

      cout << *v;

      // Delete's the pointers and clears them out AFTER
      // the board is finished
      for (int i = 0; i < possMoves.size(); i++)
         delete possMoves[i];
      possMoves.clear();

      // Determine's the score
      winner = board->GetValue();
      cout << "\nScore: " << winner;

      if (winner > 0)
         cout << "\n\n" << board->GetPlayerString(1) << " wins!\n\n";
      else if (winner < 0)
         cout << "\n\n" << board->GetPlayerString(0) << " wins!\n\n";
      else
         cout << "\n\nIt's a tie!\n\n";

      delete board;
      delete v;
   }
}