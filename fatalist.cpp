#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "functor.h"

bool FatalistHypothesis(std::vector<std::pair<int,int> > grades){

//first, sort the grade vector by the first element of each pair
pairComp comp;
//unsigned int l = grades.size();

std::sort(grades.begin(), grades.end(), comp);
//std::sort(grades[0].first, grades[l].first, comp);

//then, go through and make sure that the second grades are also sorted in ascending order
//if someone has a second grade higher than the person above them, then check to make sure
//that their first grades are not equal
//otherwise, the pessimist is wrong and return false
for(unsigned int i = 0; i<grades.size(); i++){
	if(grades[i].second > grades[i+1].second){
		if(grades[i].first < grades[i+1].first){
			return false;
		}
	}
}

/*if the function reaches here, it means that the pessimist was right, 
and for any two students A and B, 
if A got a strictly higher grade than B in 170, 
then A will have a grade greater or equal to B's in 104. 

In addition, if A got a strictly higher grade than B in 104,
then A will have a grade greater or equal to B's in 170.*/

	return true;
}