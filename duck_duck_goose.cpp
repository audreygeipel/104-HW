#include "circular_list_int.h"
#include "duck_duck_goose.h"
using namespace std;
#include <iostream>
#include <fstream>

void simulateDDGRound(GameData * gameData, std::ostream & output){
	
	//randomly generate m, then go through the list and declare the mth player a Goose
	int m = rand() % (4*(gameData->playerList.size())-1);

	for(int j = 0; j<m; j++){
		output << gameData->playerList.get(j) << " is a Duck" << endl;
	}
	output << gameData->playerList.get(m) << " is a Goose!" << endl;

//both the goose and "it" chose a random number between 1 and 49 inclusive

//randomly generate numbers
	int goosenumber = (rand() % 49) + 1;
	int itnumber = (rand() % 49) + 1;

//if they're the same number, go again
	if(goosenumber == itnumber){
		goosenumber = rand() % 50;
		itnumber = rand() % 50;
	}
//if "it" has a higher number, then "it" takes the goose's spot and the goose becomes it
	if(itnumber > goosenumber){
		output << gameData->itPlayerID << " took " << gameData->playerList.get(m) << "'s spot!" << endl;

		int temp = gameData->playerList.get(m);
		//set the spot where goose was to "it"
		gameData->playerList.set(m, gameData->itPlayerID);
		
		//set "it" to goose's ID
		gameData->itPlayerID = temp;

	}

//if the goose has a higher number, then goose stays in the list, and it player is out
	if(goosenumber > itnumber){
		output << gameData->itPlayerID << " is out!" << endl;
		size_t newit = rand() % gameData->playerList.size();
		gameData->itPlayerID = gameData->playerList.get(newit);
		gameData->playerList.remove(newit);
	}
	

}

int main(int argc, char *argv[]){

if(argc <2){
		cout << "put stuff in command line" << endl;
	}

GameData * gamedata = new GameData();

CircularListInt players;

//get stuff from the file
char* filename;
ifstream myfile;
filename = argv[1];
myfile.open(filename);
	unsigned int seed;
		myfile >> seed;
		srand(seed);
	int n;
		myfile >> n;
	int it;
		myfile >> it;
	for(int i = 0; i<n; i++){
		int id;
		myfile >> id;
		players.push_back(id);
	}

//assign to gamedata
gamedata->playerList = players;
gamedata->itPlayerID = it;


ofstream outfile;
outfile.open(argv[2]);


while(gamedata->playerList.size() > 1){
	simulateDDGRound(gamedata, outfile);
}

outfile << "Winner is " << gamedata->itPlayerID << "!" << endl;

delete gamedata;

	return 0;
}