coloring notes

for(int i = 0; i <rows; i++){
	for(int j = 0; j <columns; j++){
			/*if(contains(countrymap, array[i][j]) == true){
				int x = find(countrymap, array[i][j]);
				countrymap[x].second = 1;
			}*/
			if(i <rows-1 && array[i][j] != array[i+1][j]){
				int x = find(countrymap, array[i][j]);			
				int y = find(countrymap, array[i+1][j]);
				if(countrymap[x].second == countrymap[y].second){
					countrymap[y].second++;
					}
			}
			if(i >= 1 && array[i][j] != array[i-1][j]){
				int x = find(countrymap, array[i][j]);			
				int y = find(countrymap, array[i-1][j]);
				if(countrymap[x].second == countrymap[y].second){
					countrymap[y].second++;
					}
			}
			if( j<columns-1 && array[i][j] != array[i][j+1]){
				int x = find(countrymap, array[i][j]);			
				int y = find(countrymap, array[i][j+1]);
				if(countrymap[x].second == countrymap[y].second){
					countrymap[y].second++;
					}
			}
			if(j>= 1 && array[i][j] != array[i][j-1]){
				int x = find(countrymap, array[i][j]);			
				int y = find(countrymap, array[i][j-1]);
				if(countrymap[x].second == countrymap[y].second){
					countrymap[y].second++;
					}
			}
			

	}//end of j for

}//end of i for