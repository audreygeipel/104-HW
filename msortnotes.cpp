
// for(int y = 0; y < size-1; y++){

//   for(int x = 0; x < k; x++){

//     if(!comp(a[x*size+y],a[x*size+y+1])){
//       T temp = a[x*size+y];
//       a[x*size+y] = a[x*size+y+1];
//       a[x*size+y+1] = temp;
//     }

//   }

// }


in mergesort

	/*
  if(myArray.size() <= (unsigned int)k){
  	merge(myArray,k, comp);
  	return;
  }

//int n = myArray.size()/k;

std::vector<T> temp;
std::vector<T> temp2;

//put the first k elements of the vector into a temp 
for(int i = 0; i<k; i++){
	temp.push_back(myArray[i]);
	
	if(temp.size() > 2){
		mergeSort(temp,k,comp);
	}
}
for(unsigned int x = k; x<myArray.size(); x++){
	temp2.push_back(myArray[x]);
	mergeSort(temp2,k,comp);
}

merge(temp,k,comp);

for(unsigned int x = 0; x<temp.size(); x++){
		myArray[x] = temp[x];
	}
*/





/*	while(i<=m || j<=r){
  		
  		if( i <= m  && ( r<=j || comp(a[i],a[j])))
  		{
  			temp.push_back(a[i]);
  			i = i+1;
  		}
  		else{
  			temp.push_back(a[j]);
  			j = j+1;
  		}
  	}//end of while
*/