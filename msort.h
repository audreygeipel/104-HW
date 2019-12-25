//array, left, right, middle
#include <vector>
#include <iostream>
template <class T, class Comparator>
void merge(std::vector<T>& a, int k, Comparator comp){
	
int * indices;
indices = new int[k];

int size = a.size()/k;

for(int x = 0; x<k; x++){
	indices[x] = size*x;
}

std::vector<T> temp;

int f = 0;
int s = 0;

//go through each k-size part of the array, starting at the starting index and going through it
//compare it to the other k-size parts of the array, and push back onto a temp vector, in order
for(int x = 0; x<k-1; x++){
  //for(int f = 0; f<size;f++){
  //  for(int s = 0; s<size;s++){

	
  if( f<=size && (comp(a[indices[x] + f] , a[indices[x+1] + s])))
		{
			temp.push_back(a[indices[x] + f]);
			f++;
		}
	else
		{
			temp.push_back(a[indices[x+1] + s]);
			s++;
		}
  }
 // }
//}

//assign a[] the temp values, which are now sorted
  	 for(unsigned int x = 0; x<temp.size(); x++){
  		a[x] = temp[x];
  	 }

  }// end of 




template <class T, class Comparator>
  void mergeSort (std::vector<T>& myArray, int k, Comparator comp){
  
  if(myArray.size() == 1){
  	return;
  	}

  	merge(myArray,k,comp);

  
}
