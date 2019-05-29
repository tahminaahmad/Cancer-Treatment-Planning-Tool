#include <fstream>
#include <iostream>

using namespace std;
//priorityqueue for storing airfare data.  Cheapest airfare values are prioritized and sent to the front of the queue.
class AirfarePQ
{
	public:
	AirfarePQ(int sizeheap); //constructor
	~AirfarePQ(); //destructor
	void printPQ(); //print queue
	void addtoPQ (int value); //add value
	int removeFromPQ(); //remove value
	int peekValue(); //check cheapest flight
	bool isFull(); //make sure PQ isn't full
	bool isEmpty(); //make sure PQ isn't empty

	private: //functions to reference for easier function implementation
	int parent(int nodeIndex); //standard heap implementation for parents, lc, rc, repairupwards and downwards
	int leftChild(int nodeIndex);
	int rightChild(int nodeIndex);
	void repairUpward(int nodeIndex);
	void repairDownward(int nodeIndex);
	int* airfare; //pointer to the PQ array
	int currentSize;
	int heapSize; //max size of PQ
};

AirfarePQ::AirfarePQ(int sizeheap) //sizeheap will be obtained by the user (how many flights they want to see)
{
  airfare = new int[sizeheap];
  currentSize = 0;
  heapSize = sizeheap;
}

AirfarePQ::~AirfarePQ()
{
  delete [] airfare;
}


void AirfarePQ::printPQ()
{
  int i = 0;
  while(i < currentSize)
  {
    cout << airfare[i] << " ";
    i = i + 1;
  }
  cout << endl;
}


void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}


void AirfarePQ::addtoPQ (int value)
{
  if(isFull() == 1)
  {
    cout << "Maximum priority queue size reached. Cannot insert anymore" << endl;
    return;
  }

  currentSize = currentSize + 1;
  int index = currentSize -1;
  airfare[index] = value;
    repairUpward(index);
}

int AirfarePQ::peekValue()
{

  return airfare[0];
}




bool AirfarePQ::isFull()
{
  if(currentSize == heapSize)
  {
    return true;
  }


  else
  {
    return false;
  }
}


bool AirfarePQ::isEmpty()
{
  if (currentSize == 0)
  {
    return true;
  }


  else
  {
    return false;
  }
}


int AirfarePQ::parent(int nodeIndex)
{
  return (nodeIndex-1)/2;
}




int AirfarePQ::leftChild(int nodeIndex)
{
  return ((2*nodeIndex) + 1);
}


int AirfarePQ::rightChild(int nodeIndex)
{
  return ((2*nodeIndex) + 2);
}

int AirfarePQ::removeFromPQ(){
    if (isEmpty() ==1)
    {
        cout<<"Empty, can't dequeue"<<endl;
    }
    else
    {
        if (currentSize>0)
        {
            for (int j= 0; j<currentSize-1; j++){
                airfare[j] = airfare[j+1];
            }
            currentSize--;
            repairDownward(0);
        }
    }
}
void AirfarePQ::repairUpward(int nodeIndex){
int i = nodeIndex;
while (i>0){
    if (airfare[i] < airfare[i-1])
    {
        int temp = airfare[i];
        airfare[i] = airfare[i-1];
        airfare[i-1] = temp;
    }
    i = i-1;
}
}

void AirfarePQ::repairDownward(int nodeIndex){
int i = 0;
while (i<currentSize-1){
    if (airfare[i] > airfare[i+1] ){
        int temp = airfare[i+1];
        airfare[i+1] = airfare[i];
        airfare[i] = temp;
    }
    i = i+1;
}
}
