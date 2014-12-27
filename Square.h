#ifndef SQUARE_H
#define SQUARE_H

#include <string>
#include "Piece.h"

using namespace std;

class Board;

class Square
{
public:
   Square(Board * board) : piece(NULL), board(board) {}
   ~Square() {}
   static string printSquare(Square * rhs);
   friend ostream & operator << (ostream & out, Square * rhs)
   {
      string test = printSquare(rhs);
      out << test;
      return out;
   }
   void setColor(string color);
   void setPiece(Piece * piece) //pointer to a piece owned by the board
   {
      this->piece = piece;
   }
   void setPiece(Piece * piece, bool inactive) //pointer to a piece owned by the board
   {
      this->piece = piece;
   }
   void removePiece() 
   {
      this->piece = NULL;
   }
   Piece * getPiece()
   {
      return this->piece;
   }
private:
   Piece * piece;
   string squareColor;
   string bgPre;
   string pieceColor;
   Board * board;
};

#endif
