#ifndef INTERFACE_H
#define INTERFACE_H

#include "Move.h"
#include "Position.h"
#include "Board.h"
#include "Player.h"
#include <vector>

using namespace std;

class Interface
{
public:
   Interface(Board * board, Player * players[2]) : board(board) 
   {
      this->players[0] = players[0];
      this->players[1] = players[1];
   }
   ~Interface() {}
   string getInput(Player * player) 
   {
      cout << "(" << player->getName() << "): ";
      return getInput();
   }
   string getInput() 
   {
      string input;
      cin >> input;
      return input;
   }
   bool validateInput(const string & input) 
   {
      if (input.length() <= 5)
         return true;
      else
         return false;
   }
   void beginMenuCapture();
   void saveFileOnQuit()
   {
     //Display save if you want to message here, with keyboard capture
     cout << "To save a game, please specify the filename.\n    To quit without saving a file, just press <enter>\n";
     string input = getInput();
     if (input.compare("") != 0)
     {
      saveFile(input);
     }
   }
   void saveFile(string filename);
   Move parseToMove(string & input) throw (string);
   void displayMenu()
   {
      cout << "Options:" << endl;
      cout << " ?\tDisplay these options\n";
      cout << " b2b4\tSpecify a move using the Smith Notation\n";
      cout << " read\tRead a saved game from a file\n";
      cout << " test\tSimple display for test purposes\n";
      cout << " quit\tLeave the game. You will be prompted to save\n";
   }
   void read()throw(string);
private:
   int playerTurn;
   Board * board;
   Player * players[2];
   vector<string> moves;
};


#endif
