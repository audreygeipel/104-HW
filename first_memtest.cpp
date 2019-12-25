#include <iostream>
#include <stdlib.h>
#include "simpleCharManager.h"
using namespace std;

int main(int argc, char *argv[])
{
  simpleCharManager simplest_mem_manager;

  /*write driver code as described in the assignment to replace this */
  char* c1 = simplest_mem_manager.alloc_chars(13);
  c1[0] = 'H';
  c1[1] = 'e';
  c1[2] = 'l';
  c1[3] = 'l';
  c1[4] = 'o';
  c1[5] = ' ';
  c1[6] = 'W';
  c1[7] = 'o';
  c1[8] = 'r';
  c1[9] = 'l';
  c1[10] = 'd';
  c1[11] = '!';
  c1[12] = '\0';

for(int i = 0; i<13; i++){
	cout << c1[i];
}
cout << endl;

simplest_mem_manager.free_chars(&c1[6]);

char* d1 = simplest_mem_manager.alloc_chars(11);
  d1[0] = 'm';
  d1[1] = 'o';
  d1[2] = 'o';
  d1[3] = 'n';
  d1[4] = '!';
  d1[5] = ' ';
  d1[6] = 'B';
  d1[7] = 'y';
  d1[8] = 'e';
  d1[9] = '.';
  d1[10] = '\0';

for(int i = 0; i<17; i++){
	cout << c1[i];
}
cout << endl;

  //std::cout << "Hello world!\n" ;
  
  return 0;
}

