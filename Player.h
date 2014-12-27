#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player
{
public:
   Player(string name) : name(name)
   {
      static int count = 1;
      this->id = count++;
   }
   ~Player() {}
   string getName() {return this->name;}
   int getId() {return this->id;}
private:
   string name;
   int id;
};

#endif
