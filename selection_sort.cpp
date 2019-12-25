#include "selection_sort.h"
using namespace std;
#include <iostream>

Item* findMin(Item * head){
	
	if(head == nullptr){
		return nullptr;
	}

	Item * ptr = head;
	Item * minplace = head;
	int min = ptr->getValue();


	while(ptr->next != nullptr){

		if((ptr->next->getValue()) < min){
			minplace = ptr->next;
			min = (minplace->getValue());
		}

		ptr = ptr->next;

	}//end of while

return minplace;

}

Item* LLSelectionSort(Item * head){

	if(head == nullptr){
		return nullptr;
	}
	
	Item * ptr = head;

	Item * min = findMin(ptr);

	Item mintemp = *min;
		Item * minnext = min->next;
		Item * minprev = min->prev;

	Item ptrtemp = *ptr;
		Item * ptrnext = ptr->next;
		Item * ptrprev = ptr->prev;

	*min = ptrtemp;
	min->next = minnext;
	min->prev = minprev;

	*ptr = mintemp;
	ptr->next = ptrnext;
	ptr->prev = ptrprev;


	LLSelectionSort(ptr->next);

	return head;
}

