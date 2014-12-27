a.out: Game.o Board.o Player.o Interface.o Square.o Piece.o
	g++ -o a.out Game.o Board.o Player.o Interface.o Square.o Piece.o
	tar -cf Chess.tar *.cpp *.h makefile

Game.o : Game.cpp Game.h
	g++ -c Game.cpp

Board.o : Board.cpp Board.h
	g++ -c Board.cpp

Player.o : Player.cpp Board.h
	g++ -c Player.cpp

Interface.o : Interface.cpp Interface.h
	g++ -c Interface.cpp

Square.o : Square.cpp Square.h
	g++ -c Square.cpp

Piece.o : Piece.cpp Piece.h
	g++ -c Piece.cpp

clean : rm *.*~

# Clint Goodman
# Bro Comeau, CS 165
