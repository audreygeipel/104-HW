#include <vector>
#include <exception>
#include <stdexcept>
#include <cassert>
/*
class logic_error: public exception{
  public:
    explicit logic_error(const std::string&);
};

*/
template <class T>
  class MinHeap {
     public:
      /* Constructor that builds a d-ary Min Heap
          This should work for any d >= 2,
          but doesn't have to do anything for smaller d.*/
      MinHeap (int d);

       ~MinHeap ();

       void add (T item, int priority);
         /* adds the item to the heap, with the given priority. */

       const T & peek () const;
         /* returns the element with smallest priority.  
            Break ties however you wish.  
            Throws an exception if the heap is empty. */

       void remove ();
         /* removes the element with smallest priority.
            Break ties however you wish.
            Throws an exception if the heap is empty. */

       bool isEmpty ();
         /* returns true iff there are no elements on the heap. */

   private:
      // whatever you need to naturally store things.
      // You may also add helper functions here.
      
      std::vector<std::pair<T, int>> heap;
      int degree;
  };

template <class T>
    MinHeap<T>::MinHeap (int d){
        degree = d;
      }
       
template <class T>
    MinHeap<T>::~MinHeap (){}

template <class T>
   void MinHeap<T>::add(T item, int priority){
//the existence predates the essence
//at size -1
//index- 1/degree = parent
//priority of child must be less than parent
//and index has to be greater than 0
std::pair<T, int> a;// = (item, priority);

a = std::make_pair(item, priority);
heap.push_back(a);

unsigned int index = heap.size()-1;
unsigned int parentindex = (index - 1)/degree;
//unsigned int i = index;

//while(i >=0 && parentindex >=0 && index >=0){
for(unsigned int i = index; i>=0; i = i-1){

if(i == index){
      if(heap[index].second >= heap[parentindex].second){
          heap[index] = heap[parentindex];
      }else{
        break;
      }
    index = parentindex;
    parentindex = (index - 1) /degree;
  }

  //i = i-1;
}

heap[index] = a;

    }

template <class T>
   const T& MinHeap<T>::peek () const{
      if(heap.empty() == true){
        throw std::logic_error("nothing_in_heap");
      }
      return heap[0].first;

   }

template <class T>
  void MinHeap<T>::remove (){
//at size -1
//index- 1/degree = parent
//priority of child must be less than parent
//and index has to be greater than 0

//std::pair<T, int> r = <item, priority>;
//set the root node to be the last node
if(heap.empty() == true){
    throw std::logic_error("nothing_in_heap");
    return;
}


heap[0] = heap[heap.size()-1];
heap.pop_back();
//trickle that shit down 

unsigned int index = 0;
unsigned int childindex = (index * degree) + 1;

for(unsigned int i = 0; i< heap.size(); i++){
    
    if(i == index){
      for(int c = 0; c <degree; c++){
        if(heap[childindex + c].second < heap[childindex].second){
          childindex = childindex +c;
          }
        }
      heap[i] = heap[childindex];
    }
      index = childindex;
      childindex = (index * degree) + 1;
    }

}

template <class T>
  bool MinHeap<T>::isEmpty (){
      if(heap.size() == 0){
        return true;
      }
      return false;
  }


/*
In order to build it, you may use internally the vector container (you are not required to do so). You should of course not use the STL priority_queue class or make_heap, push, pop algorithms.

In order to guide you to the right solution, think first about the following questions. We strongly recommend that you start your array indexing at 0 (that will make the following calculations easier). In order to figure out the answers, we suggest that you create some examples and find a pattern.

If you put a complete d-ary tree in an array, what is the index of the parent of the node at position i?
In the same scenario as above, what are the indices of the children of the node at position i?
What changes in the heap functions you learned in class when you move to d-ary arrays?

start at index 0
d is number of tree things


draw it out with extra variable to see what changes

root is at index 0

left child = i + d
right child = i + d + d-1


*/