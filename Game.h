#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Interface.h"

using namespace std;

class Game
{
public:
   Game() : board(new Board())
   {
      this->players[0] = new Player("Black");
      this->players[1] = new Player("White");
      this->interface = new Interface(this->board, this->players);
   }
   ~Game() {}
   void createGame(){
      board->reset();
      interface->beginMenuCapture();
   }
private:
   Board * board;
   Player * players[2];
   Interface * interface;
};

#endif
