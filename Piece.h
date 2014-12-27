#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include "Move.h"
#include <iostream>

class Board;

using namespace std;

enum PIECE_TYPE {BLANK, KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN};

class Piece
{
public:
   Piece(Board * board, int player) : board(board), player(player), iterationsAllowed(0), moved(false) {}
   ~Piece() {}
   void setPlayer(int player) { this->player = player; }
   virtual char getSymbol() {return ' ';}
   char displayableSymbol();
   virtual bool canJump() {return false;}
   bool validMove(const Move & move);
   bool pathLegal(const Move & move, const int & iterationsAllowed, Position * movesAllowed[], int movesAllowedCount);
   int getPlayer() { return player; }
   bool hasMoved() { return moved; }
   void setHasMoved() { moved = true; }
   virtual bool specialCaseMove(const Move & move) {}
protected:
   int player;
   int iterationsAllowed; //= 1 (knight), 2 (pawn), unlimited (rook, queen)
   Position * movesAllowed[8];
   Board * board;
   bool moved;
   virtual void removeSpecialCases() {}
};

class King : public Piece
{
public:
   King(Board * board, int player) : Piece(board, player)
   {
      this->iterationsAllowed = 1;

      this->movesAllowed[0] = new Position;
      this->movesAllowed[0]->row = 1;
      this->movesAllowed[0]->col = 1;

      this->movesAllowed[1] = new Position;
      this->movesAllowed[1]->row = 1;
      this->movesAllowed[1]->col = 0;

      this->movesAllowed[2] = new Position;
      this->movesAllowed[2]->row = 0;
      this->movesAllowed[2]->col = 1;

      this->movesAllowed[3] = new Position;
      this->movesAllowed[3]->row = -1;
      this->movesAllowed[3]->col = -1;

      this->movesAllowed[4] = new Position;
      this->movesAllowed[4]->row = -1;
      this->movesAllowed[4]->col = 0;

      this->movesAllowed[5] = new Position;
      this->movesAllowed[5]->row = 0;
      this->movesAllowed[5]->col = -1;

      this->movesAllowed[6] = new Position;
      this->movesAllowed[6]->row = 1;
      this->movesAllowed[6]->col = -1;
      
      this->movesAllowed[7] = new Position;
      this->movesAllowed[7]->row = -1;
      this->movesAllowed[7]->col = 1;

   }
   ~King() {}
   char getSymbol() {return 'K';}
   bool canJump() {return false;}
};

class Queen : public Piece
{
public:
   Queen(Board * board, int player) : Piece(board, player)
   {
      this->iterationsAllowed = 8;

      this->movesAllowed[0] = new Position;
      this->movesAllowed[0]->row = 1;
      this->movesAllowed[0]->col = 1;

      this->movesAllowed[1] = new Position;
      this->movesAllowed[1]->row = 1;
      this->movesAllowed[1]->col = 0;

      this->movesAllowed[2] = new Position;
      this->movesAllowed[2]->row = 0;
      this->movesAllowed[2]->col = 1;

      this->movesAllowed[3] = new Position;
      this->movesAllowed[3]->row = -1;
      this->movesAllowed[3]->col = -1;

      this->movesAllowed[4] = new Position;
      this->movesAllowed[4]->row = -1;
      this->movesAllowed[4]->col = 0;

      this->movesAllowed[5] = new Position;
      this->movesAllowed[5]->row = 0;
      this->movesAllowed[5]->col = -1;

      this->movesAllowed[6] = new Position;
      this->movesAllowed[6]->row = 1;
      this->movesAllowed[6]->col = -1;
      
      this->movesAllowed[7] = new Position;
      this->movesAllowed[7]->row = -1;
      this->movesAllowed[7]->col = 1;

   }
   ~Queen() {}
   char getSymbol() {return 'Q';}
   bool canJump() {return false;}
};

class Bishop : public Piece
{
public:
   Bishop(Board * board, int player) : Piece(board, player)
   {
      this->iterationsAllowed = 8;

      this->movesAllowed[0] = new Position;
      this->movesAllowed[0]->row = 1;
      this->movesAllowed[0]->col = 1;

      this->movesAllowed[1] = new Position;
      this->movesAllowed[1]->row = -1;
      this->movesAllowed[1]->col = -1;

      this->movesAllowed[2] = new Position;
      this->movesAllowed[2]->row = 1;
      this->movesAllowed[2]->col = -1;
      
      this->movesAllowed[3] = new Position;
      this->movesAllowed[3]->row = -1;
      this->movesAllowed[3]->col = 1;

   }
   ~Bishop() {}
   char getSymbol() {return 'R';}
   bool canJump() {return false;}
};

class Rook : public Piece
{
public:
   Rook(Board * board, int player) : Piece(board, player)
   {
      this->iterationsAllowed = 8;

      this->movesAllowed[0] = new Position;
      this->movesAllowed[0]->row = 1;
      this->movesAllowed[0]->col = 0;

      this->movesAllowed[1] = new Position;
      this->movesAllowed[1]->row = 0;
      this->movesAllowed[1]->col = 1;

      this->movesAllowed[2] = new Position;
      this->movesAllowed[2]->row = -1;
      this->movesAllowed[2]->col = 0;

      this->movesAllowed[3] = new Position;
      this->movesAllowed[3]->row = 0;
      this->movesAllowed[3]->col = -1;

   }
   ~Rook() {}
   char getSymbol() {return 'B';}
   bool canJump() {return false;}
};

class Knight : public Piece
{
public:
   Knight(Board * board, int player) : Piece(board, player)
   {
      this->iterationsAllowed = 1;

      this->movesAllowed[0] = new Position;
      this->movesAllowed[0]->row = 2;
      this->movesAllowed[0]->col = 1;

      this->movesAllowed[1] = new Position;
      this->movesAllowed[1]->row = 2;
      this->movesAllowed[1]->col = -1;

      this->movesAllowed[2] = new Position;
      this->movesAllowed[2]->row = -2;
      this->movesAllowed[2]->col = 1;

      this->movesAllowed[3] = new Position;
      this->movesAllowed[3]->row = -2;
      this->movesAllowed[3]->col = -1;

      this->movesAllowed[4] = new Position;
      this->movesAllowed[4]->row = 1;
      this->movesAllowed[4]->col = -2;

      this->movesAllowed[5] = new Position;
      this->movesAllowed[5]->row = 1;
      this->movesAllowed[5]->col = 2;

      this->movesAllowed[6] = new Position;
      this->movesAllowed[6]->row = -1;
      this->movesAllowed[6]->col = -2;

      this->movesAllowed[7] = new Position;
      this->movesAllowed[7]->row = -1;
      this->movesAllowed[7]->col = 2;
   }
   ~Knight() {}
   char getSymbol() {return 'N';}
   bool canJump() {return true;}
};

class Pawn : public Piece
{
public:
   Pawn(Board * board, int player) : Piece(board, player)
   {
      this->iterationsAllowed = 1;

      this->movesAllowed[0] = new Position;
      this->movesAllowed[0]->row = 1;
      this->movesAllowed[0]->col = 0;
   }
   ~Pawn() {}
   char getSymbol();
   bool canJump() {return false;}
   virtual bool specialCaseMove(const Move & move);
};

#endif
