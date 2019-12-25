#include "flexCharManager.h"

flexCharManager::flexCharManager(){
 used_mem_size = 2;
 active_requests = 0;
 used_memory = new  Mem_Block*[2];

}

flexCharManager::~flexCharManager(){

for(int i = 0; i<used_mem_size; i++){
	delete[] used_memory[i];
}
delete[] used_memory;

}
             
char* flexCharManager::alloc_chars(int n){

int size = n;

//number of active requests goes up
active_requests = active_requests + 1;

//if there are more active requests than used memory, then double the used_mem_size
if(used_mem_size < active_requests){

	Mem_Block ** temp = new Mem_Block*[used_mem_size];
	
	//make a temporary array to hold all of the memory blocks
	for(int y = 0; y<used_mem_size; y++)
		{
		Mem_Block * tmem = new Mem_Block((*used_memory[y]).size, (*used_memory[y]).physical_location);
		temp[y] = tmem;
		}

//delete used memory
	for(int i = 0; i<= used_mem_size; i++){
		delete[] used_memory[i];
		}
	delete[] used_memory;


used_mem_size = used_mem_size*2;

//dynamically allocate a new used memory of the new size
used_memory = new  Mem_Block*[used_mem_size];

//then, assign used_memory the same values
for (int i = 0; i < active_requests-1; i++){
	Mem_Block * newmem = new Mem_Block((*temp[i]).size, (*temp[i]).physical_location);	
	used_memory[i] = newmem;
}

//then delete the temporary array
for(int i = 0; i< active_requests; i++){
	delete[] temp[i];
	}
	delete[] temp;
//end if statement
}


for(int i = 0; i<BUF_SIZE; i++){

	if(buffer[i] == false){
		for(int a = 0; a <n; a++){
			if(buffer[i+a] == false){
				if((i+n) > BUF_SIZE){
					return NULL;
				}
				if((i+n)<BUF_SIZE){
					free_place = &buffer[i];
					Mem_Block * mem = new Mem_Block(size, free_place);	
					used_memory[active_requests-1] = mem;
					return free_place;	
				}
			}
		}//end of inner for loop to check if n spaces are available
	
	}//end if buffer is null loop
}//end of outer for loop


       return NULL;
}

void flexCharManager::free_chars(char* p){
//this function given a pointer in the buffer will free all memory addressed 
//from that address in the buffer until the end of the buffer.

Mem_Block ** temp = new Mem_Block*[used_mem_size];

active_requests = active_requests - 1;

int spot = 0;
//go through the used memory and find the memory block at the right location
//store the spot it's at
for (int j = 0; j <= active_requests; j++){
	if((*used_memory[j]).physical_location == p){
		spot = j;
	}
}
//delete the buffer for the right size at that spot


for(int x = 0; x<(*used_memory[spot]).size; x++){
			p[x] = '\0';
		}


//then, go through used memory and store every memory block that hasn't been deleted 
//in a temporary array
for(int y = 0; y<spot; y++){
	Mem_Block * tempmem = new Mem_Block((*used_memory[y]).size, (*used_memory[y]).physical_location);	
	temp[y] = tempmem;
}
//when it reaches the spot where the memory block was deleted, skip it and move them all over
for(int i = spot; i<active_requests; i++){
	Mem_Block * tempmem = new Mem_Block((*used_memory[i+1]).size, (*used_memory[i+1]).physical_location);	
	temp[i] = tempmem;
}


//then, delete used_memory to free it
for(int i = 0; i< used_mem_size; i++){
	delete[] used_memory[i];
}
	//delete[] used_memory; --->> THIS CAUSES CRAZY THINGS TO HAPPEN

//then, assign used_memory the same values, but without the deleted block
for (int i = 0; i < active_requests; i++){
	Mem_Block * newmem = new Mem_Block((*temp[i]).size, (*temp[i]).physical_location);	
	used_memory[i] = newmem;
}

for(int i = 0; i< used_mem_size; i++){
	delete[] temp[i];
}
delete[] temp;

}         


