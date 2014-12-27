#ifndef BOARD_H
#define BOARD_H

#include "Square.h"
#include "Move.h"
#include "Position.h"
#include <iostream>

using namespace std;

class Board
{
public:
   Board () : testStyle(false) {}
   ~Board() {}
   bool checkIfGameIsOver();
   void display();
   void display(bool clearScreen);
   void reset();
   Square * getSquare(Position pos)
   {
      if (pos.row >= 0 && pos.row < 8 && pos.col >= 0 && pos.col < 8)
      {
         return squares[pos.row][pos.col];
      }
      else
      {
         return NULL;
      }
   }
   void move(Move move) throw(string);
   Piece * getPieceAtMove(const Move & move, const int & row, const int & col);
   bool isTestStyle() { return this->testStyle; }
   void setTestStyle(bool test) { this->testStyle = test; }
private:
   Square * squares[8][8];
   bool testStyle;
};


#endif
