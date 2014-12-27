#ifndef MOVE_H
#define MOVE_H

using namespace std;

#include "Position.h"
#include <string>

struct Move
{
   Position src;
   Position dest;
   string special;
};

#endif
