#include "Move.h"
#include "Position.h"
#include "Board.h"
#include "Square.h"
#include "Interface.h"
#include <iostream>    // for CIN and COUT
#include <fstream>
#include <vector>

void Interface::saveFile(string filename)
{
   ofstream myfile(filename.c_str());
   if (myfile.is_open())
   {
      for (int i = 0; i < this->moves.size(); i++)
      {
         myfile << this->moves.at(i);
         if ((i - 1) % 2 == 0 && i > 0)
         {
            myfile << endl;
         }
         else
         {
            myfile << " ";
         }
      }
   }
   else
   {
      cout << "ERROR in write: Could not open file " << filename << endl;
   }
}

void Interface::beginMenuCapture()
{
   this->board->display(false);
   string input;
  // forever
  for (playerTurn = 1;;playerTurn++)
  {
    Player * playerThisTurn;
    if (playerTurn % 2 == 0)
    {
      playerThisTurn = this->players[0];
    }
    else
    {
      playerThisTurn = this->players[1];
    }
    input = getInput(playerThisTurn);
    if (input.compare("quit") == 0)
    {
      break;
    }
    else if (input.compare("?") == 0 || input.compare("help") == 0)
    {
      this->displayMenu();
      playerTurn--;
    }
    else if (input.compare("read") == 0)
    {
      try
      {
         this->read();
         this->board->display();
      }
      catch(string msg)
      {
         cout << msg << endl;
         playerTurn--;
      }
    }
    else if (input.compare("test") == 0)
    {
      this->board->setTestStyle(true);
      this->board->display();
      playerTurn--;
    }
    else if (validateInput(input))
    {
      try
      {
         Move move = this->parseToMove(input);
         Piece * piece = this->board->getPieceAtMove(move, 0, 0);
         if (piece != NULL)
         {
            if(piece->getPlayer() == playerThisTurn->getId())
            {
               this->board->move(move);
               this->moves.push_back(input);
               this->board->display();
            }
            else
            {
               throw string("You do not own that piece, so you cannot move it.");
            }
         }
         else
         {
            throw string("That is a blank square");
         }
      }
      catch(string msg)
      {
         cout << msg << endl;
         playerTurn--;
      }
    }
    else
    {
       cout << "ERROR MESSAGE\n";
       playerTurn--;
    }
  }
  this->saveFileOnQuit();
}

void Interface::read()throw(string)
{
   //Get filename input
   cout << "Filename:";
   string filename;
   cin >> filename;

   //Set-up variables to be used while reading
   string line;
   string playerOneMove;
   string playerTwoMove;
   size_t spaceT;

   Board * newBoard = new Board();
   newBoard->reset();
   try
   {
      ifstream myfile(filename.c_str());
      if (myfile.is_open())
      {
         int turn = 0;
         while ( getline (myfile,line) )
         {
            //Split up line by spaces
            spaceT = line.find(" ");
            playerOneMove = line.substr(0, spaceT);
            playerTwoMove = line.substr(spaceT + 1);
            if (playerOneMove.compare("") != 0)
            {
               newBoard->move(this->parseToMove(playerOneMove));
               turn++;
            }
            //Check to see if move is blank, or if it the same as playerOneMove (meaning,
            //there is no space in the string, and the split is invalid.
            if (playerTwoMove.compare("") != 0 && playerTwoMove.compare(playerOneMove) != 0)
            {
               Move move = this->parseToMove(playerTwoMove);
               newBoard->move(move);
               turn++;
            }
         }
         myfile.close();
         newBoard->setTestStyle(this->board->isTestStyle());
         delete this->board;
         this->board = newBoard;
         this->playerTurn = turn;
      }
      else
      {
         throw string("Error while reading file");
      }
   }
   catch(string msg)
   {
      throw string(msg);
   }
}

Move Interface::parseToMove(string & input) throw (string)
{
   // e1g1
   int srcRow;
   int srcCol;
   int destRow;
   int destCol;
   Position coord[2];
   Move move;
   //Validate ranges
   for (int i = 0, j = 0; i <= 3; i += 2, j++)
   {
      if (input[i] >= 'a' && input[i] <= 'h')
      {
         srcCol = input[i] - 'a';
      }
      else if (input[i] >= 'A' && input[i] <= 'H')
      {
         srcCol = input[i] - 'A';
      }
      else 
      {
         throw string("Invalid format of ") + string((i >= 2 ? "destination" : "source")) + string(" coordinates");
      }
      if (input[i + 1] >= '1' && input[i + 1] <= '8')
      {
         //Since board is 8 through 1, need to reverse the row thinking
         srcRow = 7 - (input[i + 1] - '1');
      }
       else 
      {
         throw string("Invalid format of ") + string((i >= 2 ? "destination" : "source")) + string(" coordinates");
      }

      //Check to validate the 5th letter command
      if (!(input[4] == 'p'
         || input[4] == 'n'
         || input[4] == 'b'
         || input[4] == 'r'
         || input[4] == 'q'
         || input[4] == 'k'
         || input[4] == 'c'
         || input[4] == 'C'
         || input[4] == 'E'
         || input[4] == 'N'
         || input[4] == 'B'
         || input[4] == 'R'
         || input[4] == 'Q'
         || !input[4]
         ))
      {
         throw string("Unknown promotion piece specification");
      }
      coord[j].col = srcCol;
      coord[j].row = srcRow;
   }
   move.src = coord[0];
   move.dest = coord[1];
   return move;
}
