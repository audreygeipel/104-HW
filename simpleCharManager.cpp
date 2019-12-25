#include <cstddef>
#include "simpleCharManager.h"



simpleCharManager::simpleCharManager(){

}

simpleCharManager::~simpleCharManager(){}
             
char* simpleCharManager::alloc_chars(int n){
//this function will return a pointer to a memory that can hold n 
//characters. If there is not enough space left in the buffer, return NULL

for(int i = 0; i<BUF_SIZE; i++){
	
	if(buffer[i] == false){
		//int a = i;
		if((i+n) > BUF_SIZE){
			return NULL;
		}
		if((i+n)<BUF_SIZE){
			free_place = &buffer[i];
			return free_place;
		}
	}
}
        return NULL;

}

void simpleCharManager::free_chars(char* p){
//this function given a pointer in the buffer will free all memory addressed 
//from that address in the buffer until the end of the buffer. This is not
//the ideal way to free memory for obvious reasons, but it is a LOT easier.

int i = 0;

while(p[i] != false){
	p[i] = '\0';
	i++;
}

}         




