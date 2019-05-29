#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <stack>

using namespace std;

struct cost
{
    int costTreatment; //cost data;
    string state;
    cost* next; //ptr to next element
};

class costStack
{
public:
  costStack(); //constructor
  ~costStack(); //destructor
  bool isEmpty(); //check if stack is empty
  void push(int costTreatment, string name); //add item to top of stack
  void pop(); //take off top item of stack
  cost* peek(); //check top element of stack
  void sortStack(); //sort stack so top element is always lowest cost
private:
  cost* stackHead; // pointer to the top of the stack
};


costStack::costStack(){
       stackHead= NULL;
}

costStack::~costStack(){
  while (!isEmpty())
  {
    pop();
  }
  stackHead =NULL;
}

bool costStack::isEmpty(){
  if (stackHead ==NULL){
    return 1;
  }
  else{
    return 0;
  }
}

void costStack::push(int costTreatment, string name){
    cost *ptr = new cost();
    ptr->costTreatment = costTreatment;
    ptr->state = name;
    ptr ->next = stackHead;
    stackHead = ptr;
    sortStack();
}

void costStack::pop(){
  if (!isEmpty()){
    cost* newitem = stackHead;
    stackHead = stackHead->next;
  }
  else
  {
    cout<<"Stack empty, cannot pop an item."<<endl;
  }
}

cost* costStack::peek(){
  if (stackHead !=NULL){
    return stackHead;
  }
  else{
    cout << "..." << endl << "Unfortunately there are no cheaper options remaining" << endl;
    return NULL;
  }
}

void costStack::sortStack(){
    if(stackHead != NULL &&stackHead->next !=NULL){
    if (stackHead->costTreatment > (stackHead->next)->costTreatment){
        cost* greater = stackHead;
        cost* lesser = stackHead->next;
        pop();
        pop();
        push(greater->costTreatment, greater->state);
        push(lesser->costTreatment, lesser->state);
    }
    }
}
