#include "circular_list_int.h"


// standard no-argument constructor
	CircularListInt::CircularListInt(){}

	// Destructor. Should delete all data allocated by the list. 
	CircularListInt::~CircularListInt(){
			
		}

	// Gets item at an index.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.
	// If there are no elements in the list, returns 0.
	int CircularListInt::get(size_t index) const{
	
		//size_t newindex = index % count;
	Item * inditem = head;

	while(index !=0){
		inditem = inditem->next;
		index = index-1;
	}

		return inditem->value;
	}

	// get length of list.
	size_t CircularListInt::size() const{
		
		if(head == nullptr){
			return 0;
		}

		Item * scan = head->next;
		size_t size = 1;

		while(scan != head){
			size++;
			scan = scan->next;
		}

		return size;
	}

	// returns true iff the list is empty.
	bool CircularListInt::empty() const{
		if(head == nullptr){
			return true;
		}
		return false;
	}

	// Inserts (a copy of) the given item at the end of list.
	void CircularListInt::push_back(int value){
		
		Item * newitem = new Item();
		newitem->value = value;
		if(head == nullptr){
			head = newitem;
			newitem->next = newitem;
			newitem->prev = newitem;
			//delete newitem;
			return;
		}

		Item * hold = head->prev;

		head->prev = newitem;

		newitem->prev = hold;

		newitem->next = head;

		hold->next = newitem;

		//delete newitem;
		//delete hold;
		//these deletes passed and fixed the valgrind errors when run throguh valgrind
		//but when just put into the test, it created a segfault?

	}

	// Sets the item at the given index to have the given value.
	// If an index is passed that is >= the number of items in the list, it should "wrap around" back to the first element.
	void CircularListInt::set(size_t index, int value){
		Item * inditem = head;

		while(index !=0){
			inditem = inditem->next;
			index = index-1;
		}

		inditem->value = value;
	}

	// Removes the item at the given index from the list.
	// List elements after the removed element are pulled forward, so their indicies decrease by one.
	// If an index is passed that is larger then the number of items in the list, it should "wrap around" back to the first element.
	void CircularListInt::remove(size_t index){
	
	if(head == nullptr){
		return;
	}
	if(size() == 1){
		head = nullptr;
		return;
	}

	
	Item * inditem = head;

	while(index !=0){
		inditem = inditem->next;
		index = index-1;
	}
	

	Item * ptr = inditem->prev;

	head = inditem->next;

	head->prev = ptr;

	ptr->next = head;


	}
