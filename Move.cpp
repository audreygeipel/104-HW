/* The Move class family encodes a move made by one player, including its type
   (PASS, EXCHANGE, PLACE), the tiles used (and use for blanks),
   start square, and direction (if needed).
   Call Move::parseMove() to turn an entered string into its subclass of
   Move, then call apply() on that returned move to have it execute.*/

#include <vector>
#include <string>
#include "Move.h"
#include "Tile.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Square.h"
#include "Board.h"
#include <iostream>
#include <sstream>

	/* Parses the given move m, and constructs the corresponding move subclass.
	   m is assumed to be in the format described on the assignment sheet for a move command.
	   The player passed in is used to verify that the proposed tiles are
	   in fact in the player's hand.
	   It can handle all three types of move (PASS, EXCHANGE, PLACE).
	   Coordinates start with 1.
	*/
	Move::Move(Player * player){
		_player = player;
	}

	Move* Move::parseMove(std::string moveString, Player &p){
		std::string space = " ";
		std::string movename;
		std::string row;
		std::string column;
		std::string direction;
		std::string tiles;
		size_t x;
		size_t y;
		bool horiz;

		std::string m;

	for(unsigned int i = 0; i<moveString.size();i++){
			moveString[i] = tolower(moveString[i]);
		}

	std::stringstream ss(moveString);

		ss >> movename;
		

		if(movename == "pass"){
			Move * newmove = new PassMove(&p);
			return newmove;
		}
		else if (movename == "exchange"){
			ss >> tiles;
			std::cout << tiles << std::endl;
			Move * newmove = new ExchangeMove(tiles,&p);
			return newmove;
		}
		else if(movename == "place"){
			ss >> direction;
				if(direction == "-"){
					horiz = true;
				}else{
					horiz = false;
				}
			
				ss >> x;
				
				ss >> y;

				ss >> tiles;

			Move * newmove = new PlaceMove(x,y,horiz,tiles,&p);
			return newmove;
		}
		else{
			std::cout << "lol you messed up" << std::endl;
		}

	return 0;

	}	

	Move::~Move(){}


// Represents a pass move, where the player takes no action
//class PassMove : public Move


	/* Constructs a pass move. */
	PassMove::PassMove(Player * player):Move(player){

	}
	
	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void PassMove::execute(Board & board, Bag & bag, Dictionary & dictionary){

	}

// represents an exchange move, were a player replaces certain tiles
//class ExchangeMove : public Move
	/* Creates an EXCHANGE move, exchanging the tiles listed in the
	   string (formatted according to the EXCHANGE command description)
	   with new tiles from the bag.
	   */
	ExchangeMove::ExchangeMove(std::string tileString, Player * p):Move(p){
		exchangetiles = tileString;
	}


	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void ExchangeMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
		int length = exchangetiles.size();

		//if(_player->hasTiles(exchangetiles, false) == true){
			_player->takeTiles(exchangetiles,false);
			_player->addTiles(bag.drawTiles(length));
		//}
	}





// represents a place move, where a player places one or more tiles onto the board.
//class PlaceMove : public Move

	/* Creates a PLACE move, starting at row y, column x, placing the tiles
	   described by the string tileString. If "horizontal" is true, then the tiles
	   are placed horizontally, otherwise vertically.
	   Coordinates start with 1.
	   The string m is in the format described in HW4; in particular, a '?'
	   must be followed by the letter it is to be used as.
	*/
	PlaceMove::PlaceMove (size_t x, size_t y, bool horizontal, std::string tileString, Player * p):Move(p){
		r = x;
		c = y;
		h = horizontal;
		word = tileString;
	}

	/* Returns the vector of tiles associated with a PLACE/EXCHANGE move.
	   Return value could be arbitrary for PASS moves. */
	//std::vector<Tile*> const & PlaceMove::tileVector () const{


	/* Executes this move, whichever type it is.
	   This may throw exceptions; students: it's up to you to
	   decide (and document) what exactly it throws*/
	void PlaceMove::execute(Board & board, Bag & bag, Dictionary & dictionary){
		
		int wordmult = 1;
		int newscore = 0;
		int oldscore = _player->getScore();
		
int blankcount = 0;

for(unsigned int i = 0; i<word.size(); i++){
	if(word[i] == '?'){
		blankcount++;
	}
}


bool go = true;

if(_player->getStart() == true){

	go = false;
	_player->setStart(false);

	if(h == true){
		for(unsigned int i = 0; i<word.size(); i++){
			if((r + i) == board.getSY() &&  c == board.getSX()){
				go = true;
			}
		}
	}else if(h == false){
		for(unsigned int i = 0; i<word.size(); i++){
			if((c + i) == board.getSX() && r == board.getSY()){
				go = true;
			}
		}
	}
}

if(!go){
	std::cout <<  "You have to play on the start" << std::endl;
	return;
}
if(!_player->hasTiles(word,true)){
	std::cout << "You don't have the tiles" << std::endl;
	return;
}

		std::vector<Tile*> wordtiles;
		wordtiles = _player->takeTiles(word, true);


for(unsigned int i = 0; i<word.size(); i++){
	if(word[i] == '?'){
		word.erase(i);
	}
}


if(dictionary.isLegalWord(word) == false){
	std::cout << "Please put an actual word" << std::endl;
}

if(go == true){

			if(dictionary.isLegalWord(word) == true){

				if (h == true){

					for(size_t i = 0; i <wordtiles.size(); i++){
						placesquare = board.getSquare(r+i, c);
						
						newscore = newscore + (wordtiles[i]->getPoints() * placesquare->getLMult());
							if(placesquare->getWMult() > 1){
								wordmult = placesquare->getWMult();
							}

						placesquare->placeTile(wordtiles[i]);

					}
			}
				else if(h == false){
					for(size_t i = 0; i < wordtiles.size(); i++){
						placesquare = board.getSquare(r, c+i);

						newscore = newscore + (wordtiles[i]->getPoints() * placesquare->getLMult());
							if(placesquare->getWMult() > 1){
								wordmult = placesquare->getWMult();
							}

						placesquare->placeTile(wordtiles[i]); 
					}
			}

		}
	}

	newscore = newscore * wordmult;

	_player->setScore(newscore + oldscore);

	int length = wordtiles.size();
	_player->addTiles(bag.drawTiles(length));

}

	//Add more public/protected/private functions/variables here.
//				_player.addScore(wordtiles[i].getPoints(),getLMult()); 
