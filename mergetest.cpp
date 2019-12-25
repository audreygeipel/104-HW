#include "msort.h"
#include "functor.h"
#include <iostream>
#include <vector>
using namespace std;

int main(){

vector<string> test = {"b","a", "c", "d", "f", "e"};

AlphaStrComp comp;

mergeSort(test,2,comp);

for(int i = 0; i<6; i++){
cout << test[i] << endl;
}
	return 0;
}