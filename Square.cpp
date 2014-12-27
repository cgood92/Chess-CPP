#include<string>
#include "Square.h"
#include "Board.h"

using namespace std;


void Square::setColor(string color)
{
   if (color.compare("red") == 0)
   {
      bgPre = "47m";
   }
   else //white
   {
      bgPre = "41m";
   }
}

string Square::printSquare(Square * rhs)
{
   string outString = "";
   if (!rhs->board->isTestStyle())
   {
      //There is a piece there
      if (rhs->piece != NULL)
      {
         //If piece is from player white
         if (rhs->piece->getPlayer() == 2)
         {
            //The background is also white
            if(rhs->bgPre == "47m")
            {
               outString = "\E[31;";
            }
            else
            {
               outString = "\E[37;";
            }
         }
         //Piece is black
         else
         {
            outString = "\E[30;";
         }
      }
      //No piece, so doesn't really matter what we say the piece color is due to space
      else
      {
         outString = "\E[30;";
      }
         //Square color
         outString += rhs->bgPre + " ";
   }
   //space+symbol+space
   outString += ((rhs->piece != NULL) ? (char)rhs->piece->displayableSymbol() : ' ');
   //End style
   if (!rhs->board->isTestStyle())
      outString += " \E[0m";
   return outString;
}
