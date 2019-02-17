#include<iostream>

using namespace std;

class Heap;

/*
	THIS IS MIN HEAP
	
	and this program also shows the implementation of heap sort;
	in this code i havnt used swapping instead it is implemented using assignment,
	its kinda confusing, but if you go through the code, you'll see that whenever im
	"heapifying" or "adding" an element im just assigning. This is important to understand
	as swapping takes 3 assigment. So if there are n swapping we need "3n" assignment
	whereas if we assign, we can do this in "n + 1" assignment!
*/

//im usign the below  function only for heap sort
//declaration
void heapSort(int, int); 

//Heap class
//all the function concerning heap are declared in this class
class Heap{
	int *arr;
	int maxLength;
	int length;
	public:
		Heap(int);
		~Heap(){
			//release the memory allocated to the heap
			delete [] arr;
		}
		bool isEmpty()const{
			return length == 0;
		}
		bool isFull()const{
			return length == maxLength; 
		}
		int getParent(int i)const{
			return (i - 1) / 2;
		}
		int getLeftChild(int i){
			return (2*i + 1);
		}
		int getRightChild(int i){
			return (2*i + 2);
		}
		//function declarations
		Heap* add(int);//to add an element into the heap
		void displayHeap();//to display current heap
		int getMin();//get the element at the 0th index of the array
		void heapify(int);//restore the heap property
//		void del()
};
//function definitions
Heap::Heap(int maxLength){
	this->maxLength = maxLength;
	try{
		arr = new int[maxLength];	//dynamically allocating memory
	}catch(bad_alloc xa){
		cout<<"Insufficient memory";
		exit(1);
	}
	length = 0;
}
//definition for add()
Heap* Heap::add(int data){
	if(isFull()){
		cout<<"Cannot insert. Length exceeded specified size";
		exit(1);
	}
	arr[length++] = data;
	int i = length - 1, temp = arr[i];
	while(i > 0){
		if(arr[getParent(i)] > temp){
			arr[i] = arr[getParent(i)];
			i = getParent(i);
		}
		else break;
	}
	arr[i] = temp;
	return this;
}
//definition for displayHeap()
void Heap::displayHeap(){
	cout<<"Heap contents : ";
	for(int i = 0 ; i < length ; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
//definition for getMin();
int Heap::getMin(){
	if(isEmpty()){
		cout<<"No data in Heap";
		exit(1);
	}	
	else if(length == 1){
		return arr[--length];
	}
	else{
		int temp = arr[0];
		arr[0] = arr[--length];
		heapify(0);
		return temp;
	}
}
//definition for heapify
void Heap::heapify(int index){
	int left = getLeftChild(index);
	int right = getRightChild(index);
	int smallest = index;
	if(arr[left] < arr[index] && left < length)
		smallest = left;
	if(arr[right] < arr[smallest] && right < length)
		smallest = right;
	int temp = arr[smallest];
	if(smallest != index){
		arr[smallest] = arr[index];
		heapify(smallest);
	}
	arr[index] = temp;
}

//definition heapSort()
void heapSort(int arr[], int length){
	Heap temp(length);
	for(int i = 0 ; i < length ; i++)
		temp.add(arr[i]);
	cout<<"Heap Sorted array : ";
	/*
		as we can see, using heaps , sorting becomes very simple, just keep removing
		removing the minimum element (aka the element at 0th index). the time complexity
		for heap sort is O(n*log(n));
	*/
	for(int i = 0 ; i < length; i++)
		cout<<temp.getMin()<<" ";
	cout<<endl;
}

//here comes main()
int main(void){
	Heap *heap = new Heap(6);
	heap->add(100)->add(12)->add(34)->add(0)->add(35)->add(1);
	heap->displayHeap();
	cout<<"minimum elements : ";
	cout<<heap->getMin()<<" "<<heap->getMin()<<" "<<heap->getMin()<<endl;
	heap->displayHeap();
	delete heap;
	
	//here comes heap sort
	//declare an array
	int arr[20] = {45,100,10,9,8,90,23,7,99,87,6,5,33,4,0,3,66,2,12,1};
	heapSort(arr, 20); //the second parameter is the size of the array to be sorted
	return 0;
}
