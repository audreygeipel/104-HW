#include <string>
#include <set>
#include <vector>

#include "Player.h"

#include <iostream>

	/* Constructor giving the player the given name, and setting their points to 0.
	   Does not give the player any tiles.
	*/
	Player::Player (std::string const & name, size_t maxTiles){
		maximumTiles = maxTiles;
		score = 0;
		playername = name;
		isstart = false;
	}

	/* Destructor for a player. Deletes all the tiles the player still has. */
	Player::~Player (){
		std::set<Tile*>::iterator it;
		
		for(it = hand.begin(); it!=hand.end(); ++it){
			//hand.erase(it--);
			std::set<Tile*>::iterator it2 = it;
			delete[] *it;
			it = ++it2;
		}

		delete *it;
		
	}

	void Player::setStart(bool start){
		isstart = start;
	}

	bool Player::getStart(){
		return isstart;
	}

	/* Returns the set of tiles the player currently holds. */
	std::set<Tile*> Player::getHandTiles() const{
		return hand;
	}

	size_t Player::getMaxTiles() const{
		return maximumTiles;
	}

	std::string Player::getName() {
		return playername;
	}
	int Player::getScore() {
		return score;
	}

	void Player::setScore(int newscore){
		score = newscore;
	}


	/* Reads a move string and confirms that the player has the tiles necessary to
	   execute this move.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as.

	   By definition, if this function returns true, then takeTiles() would
	   succeed.
	 */

	bool Player::hasTiles(std::string const & move, bool resolveBlanks) const{
		//int length = move.size();

		//std::string check = move;
		unsigned int count = 0;
		std::set<Tile*>::iterator it;


if(resolveBlanks == false){
	for(size_t i = 0; i < move.size(); i++){
		for(it = hand.begin(); it!=hand.end(); ++it){
			if((**it).getLetter() == move[i]){
				count++;
				break;
				}
			}
	}

	
	if(count == move.size()){
		return true;
		
	}
}//end of exchange if
int blankcount = 0;
if(resolveBlanks == true){
	for(size_t i = 0; i < move.size(); i++){
		for(it = hand.begin(); it!=hand.end(); ++it){
			if((**it).getLetter() == move[i] && (**it).getLetter() == '?'){
				it++;
				count++;
				blankcount++;
				break;
				}
			else if((**it).getLetter() == move[i]){
				count++;
				break;
				}
			}

	}

	if(count == (move.size() - blankcount)){
		return true;
	}
}

return false;
	}


	/* Reads a move string, finds the corresponding tiles in the player's hand, and
	   removes and returns those tiles in the order they appear in the move string.

	   The move string is case-insensitive.

	   The boolean resolveBlanks states whether this is a PLACE or EXCHANGE move.
	   If resolveBlanks is true, then when the string contains a '?',
	   the next letter is interpreted as the letter to use the blank as,
	   and the "use" field of the tile is set accordingly.

	   The move string is assumed to have correct syntax.
	*/
	std::vector<Tile*> Player::takeTiles (std::string const & move, bool resolveBlanks){
			
		std::vector<Tile*> movetiles;
		std::set<Tile*>::iterator it;

	
if(resolveBlanks == false){
	
	for(size_t i = 0; i < move.size(); i++){
		for(it = hand.begin(); it!=hand.end(); ++it){

			if((*it)->getLetter() == move[i]){
				Tile* temp = *it;
				std::set<Tile*>::iterator it2;
				it2 = it;

				hand.erase(it);
				
				movetiles.push_back(temp);
				it = it2;
				break;
				}
			}
	}
}//end of exchange if


else if(resolveBlanks == true){
	
	for(size_t i = 0; i < move.size(); i++){
		for(it = hand.begin(); it!=hand.end(); ++it){

			if((*it)->getLetter() == move[i] && move[i] == '?'){
				Tile* blank = *it;
				std::set<Tile*>::iterator it2;
				it2 = it;
				
				blank->useAs(move[i+1]); 
				movetiles.push_back(blank);

				i++;
				hand.erase(it);

				it = it2;
				break;
				}

			else if((*it)->getLetter() == move[i]){
				Tile* temp = *it;
				std::set<Tile*>::iterator it2;
				it2 = it;

				hand.erase(it);
				
				movetiles.push_back(temp);
				it = it2;
				break;
				}
			}
	}
}//end of placemove if

	return movetiles;

	}

	


	// Adds all the tiles in the vector to the player's hand.
	void Player::addTiles (std::vector<Tile*> const & tilesToAdd){
	
	for(size_t i = 0; i<tilesToAdd.size(); i++){
		hand.insert(tilesToAdd[i]);
		}

	}


