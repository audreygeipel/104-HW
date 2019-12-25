
all: scrabble

scrabble: scrabble.cpp ConsolePrinter.cpp Board.cpp player.cpp Square.h Bag.h Tile.h Dictionary.cpp Move.cpp
	g++ -Wall -g -std=c++11 scrabble.cpp ConsolePrinter.cpp Board.cpp player.cpp Square.h Bag.h Tile.h Dictionary.cpp Move.cpp -o scrabble
