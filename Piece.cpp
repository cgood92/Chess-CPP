#include "Board.h"
#include "Square.h"

#include <iostream>
#include <cmath>

using namespace std;
bool Piece::pathLegal(const Move & move, const int & iterationsAllowed, Position * movesAllowed[], int movesAllowedCount)
{
   int rowDiff = move.src.row - move.dest.row;
   int colDiff = move.dest.col - move.src.col;
   int ittCounter = 0;
   int moveAllowedIndex = 0;
   bool objectsInWay[8] = {false};
   //cout << "rowDiff=" << rowDiff << " & colDiff=" << colDiff << endl;
   //cout << "move.src.row=" << move.src.row << " & move.src.col = " << move.src.col << " & moves.dest.row= " << move.dest.row << " & move.dest.col=" << move.dest.col << endl;
   for (ittCounter = 1; ittCounter <= iterationsAllowed; ittCounter++)
   {
      for (moveAllowedIndex = 0; moveAllowedIndex < movesAllowedCount; moveAllowedIndex++)
      {
         if (movesAllowed[moveAllowedIndex] != NULL)
         {
            int rowItt = (movesAllowed[moveAllowedIndex]->row * pow(-1, this->board->getPieceAtMove(move, 0, 0)->getPlayer()+1)) * ittCounter;
            int colItt = (movesAllowed[moveAllowedIndex]->col) * ittCounter;
            //cout << "=============" << endl;
            //cout << "Trying: row" << rowItt << ":" << colItt << endl;
            //Still in the board
            if (move.src.row + rowItt >= 0 && move.src.row + rowItt < 8 && move.src.col + colItt >= 0 && move.src.col + colItt < 8)
            {
               if (rowDiff + (rowItt) == 0 && colDiff - (colItt) == 0)
               {
                  //cout << "HERE" << endl;
                  //This is an allowed move.  Now let's see if there is a piece that is in the path that would get in the way
                  if (objectsInWay[moveAllowedIndex] != true || this->canJump())
                  {
                     //cout << "allgood";
                     Piece * piece = this->board->getPieceAtMove(move, rowItt, colItt);
                     // There is no piece there, or the piece is the opponent, which is fine
                     if (piece == NULL || piece->getPlayer() != this->getPlayer())
                     {
                        return true;
                     }
                  }
                  else
                  {
                     //cout << "inway: " << objectsInWay[moveAllowedIndex] << endl;
                  }
               }
               //If object is in this square
               Position pos = {move.src.row + rowItt, move.src.col + colItt};
               Board * board = this->board;
               Square * square = this->board->getSquare(pos);
               if(square->getPiece() != NULL)
               {
                  //cout << "Piece[" << moveAllowedIndex << "] on " << pos.col << "," << pos.row << "->" << square->getPiece()->getSymbol() << endl;
                  objectsInWay[moveAllowedIndex] = true;
               }
               else
               {
                  //cout << "NO Piece[" << moveAllowedIndex << "] on " << pos.col << "," << pos.row << "->" << endl;
               }
            }
            else
            {
               //cout << "Not on board: row" << rowItt << ":" << colItt << endl;
            }
         }
         else
         {
            //cout << "moveALlowed is null" << endl;
         }
      }
   }
   //cout << myReturn << endl;
   return false;
}

bool Piece::validMove(const Move & move)
{
   if (specialCaseMove(move) || pathLegal(move, this->iterationsAllowed, this->movesAllowed, 8))
   {
      return true;
   }
   return false;
}

bool Pawn::specialCaseMove(const Move & move)
{
   //Check for double space allowed at beginning move
   if (!this->hasMoved())
   {
      Position * specialMovesAllowed[1];
      specialMovesAllowed[0] = new Position;
      specialMovesAllowed[0]->row = 2;
      specialMovesAllowed[0]->col = 0;
      if (pathLegal(move, 1, specialMovesAllowed, 1))
      {
         return true;
      }
   }

   //Corner pieces
   Position * specialMovesAllowed[1];
   specialMovesAllowed[0] = new Position;
   specialMovesAllowed[0]->row = 1;
   specialMovesAllowed[0]->col = 1;
   specialMovesAllowed[1] = new Position;
   specialMovesAllowed[1]->row = 1;
   specialMovesAllowed[1]->col = -1;
   bool pathIsLegal = pathLegal(move, 1, specialMovesAllowed, 2);
   if (pathIsLegal)
   {
      //Corner pieces
      Piece * pieces[2];
      pieces[0] = this->board->getPieceAtMove(move, 1 * pow(-1, this->board->getPieceAtMove(move, 0, 0)->getPlayer()+1), 1);
      pieces[1] = this->board->getPieceAtMove(move, 1 * pow(-1, this->board->getPieceAtMove(move, 0, 0)->getPlayer()+1), -1);
      for (int i = 0; i < 2; i++)
      {
         if (pieces[i] != NULL && pieces[i]->getPlayer() != this->getPlayer())
         {
            return true;
         }
      }
   }
   return false;
}

char Pawn::getSymbol()
{
   if (board->isTestStyle() && this->player == 1)
   {
      return 'P';
   }
   {
      return 'p';
   }
}

char Piece::displayableSymbol()
{
   if (this->board->isTestStyle() && this->player == 2 && getSymbol() != 'p')
   {
      return getSymbol() + 32;
   }
   else
   {
      return getSymbol();
   }
}
