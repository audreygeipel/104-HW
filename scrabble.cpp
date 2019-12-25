#include "Bag.cpp"
#include "ConsolePrinter.h"
#include "Dictionary.h"
#include "Move.h"
#include "Player.h"
#include "Square.h"
#include "Tile.h"
#include "rang.h"
#include "Exceptions.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <sstream>


int main(int argc, char *argv[]){

if(argc <2){
		std::cout << "put filename in command line" << std::endl;
	}

char* filename;
std::ifstream myfile;
filename = argv[1];
myfile.open(filename);

int handsize;
std::string boardfile;
std::string tilefile;
std::string dictfile;
int seed;
std::string names;


	myfile >> names;
	myfile >> handsize;
	myfile >> names;
	myfile >> boardfile;
	myfile >> names;
	myfile >> tilefile;
	myfile >> names;
	myfile >> dictfile;
	myfile >> names;
	myfile >> seed;


ConsolePrinter printer;
Bag bag= Bag(tilefile, seed);

Board* gameboard = new Board(boardfile);

Dictionary dictionary = Dictionary(dictfile);

std::cout << "Hello! Welcome to Scrabble. How many people are playing?" << std::endl;
int num;
std::cin >> num;

std::vector<Player*> players;


for(int i = 0; i<num; i++){
	std::string name;
	std::cout << "Enter name: ";
	std::cin >> name;
	Player* player1 = new Player(name, 7);
	players.push_back(player1);
}
std::cin.ignore();


std::vector<Tile*> firsthand = bag.drawTiles(handsize);
for(unsigned int i = 0; i<players.size(); i++){
	players[i]->addTiles(bag.drawTiles(handsize));
}

players[0]->setStart(true);

//also if people are not out of letters in their hand
while(bag.tilesRemaining()>0){

for(int i = 0; i<num; i++){ //loop through all players
	printer.printBoard(*gameboard);
	printer.printHand(*players[i]);
	

	std::string move;
	std::cout << "What is your move?" << std::endl;
		
	std::getline(std::cin,move);


	Move * m = Move::parseMove(move, *players[i]);
	
	m->execute(*gameboard, bag, dictionary);

	printer.printBoard(*gameboard);
	printer.printHand(*players[i]);

std::cout <<"Scores:" << std::endl; 
for(int j = 0; j<num; j++){
	std::cout << players[j]->getName() << ": " << players[j]->getScore() << std::endl;
	}

std::cout << "Press Enter to go to next player" << std::endl;
std::cin.ignore();

	}// end of while


}



return 0;

}