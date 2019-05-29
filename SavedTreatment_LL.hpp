#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
using namespace std;

//LL implemented to save treatments w/ details for further viewing

struct SavedTreatment //struct to save various pieces of info regading saved treatments
{
    string state;
    string hospital;
    string successRate;
    string mortalityRate;
    int cost;
    SavedTreatment *next;
};


class SavedTreatment_LL
{
    private:
        SavedTreatment* head; //ptr to head of LL

    public:
        SavedTreatment_LL(); //constructor
        bool isEmpty(); //check if LL empty
        void addTreatment(SavedTreatment* previous, string stateName, string hopsital, string successRate, string mortalityRate, int cost); //add in treatment w/state, hospital, success rate, mortality rate, and cost;
        // SavedTreatment* searchNetwork(string stateName); //search LL for treatment
        void printSaved(); //print ALL saved treatments
        void sortLowestCost(); //sort LL in terms of lowest cost at top
        void sortHighestSucess(); //sort LL in terms of highest sucess at top
        void sortLowestMort();  //sort LL in terms of lowest mortality rate at top
};


SavedTreatment_LL::SavedTreatment_LL()
{
  head = NULL;
}

bool SavedTreatment_LL::isEmpty()
{
  if(head == NULL)
  {
    return true;
  }
  return false;
}

void SavedTreatment_LL::addTreatment(SavedTreatment* previous, string stateName, string hospit, string sucRate, string mortRate, int cost1)
    //add treatment w/ statename, hospital name, success rate, mortality rate, and cost
{
SavedTreatment *newnode1 = new SavedTreatment();
newnode1->state = stateName;
newnode1->hospital = hospit;
newnode1->successRate = sucRate;
newnode1->mortalityRate = mortRate;
newnode1->cost = cost1;

if (previous==NULL){
    newnode1->next = head;
    head = newnode1;
}
else{
    newnode1->next = previous->next;
    previous->next = newnode1;

}
}

// SavedTreatment* SavedTreatment_LL::searchNetwork(string stateName) //return node of treatment searched for for further analysis
// {
//   SavedTreatment *temp = head;
//
//   while(temp != NULL && temp->state != stateName)
//   {
//     temp = temp->next;
//   }
//
//   if(head != NULL && head->state == stateName)
//   {
//     temp = head;
//   }
//   return temp;
// }

void SavedTreatment_LL:: printSaved() //print all, UNSORTED, nodes of LL
{
SavedTreatment *current = head;
while(current != NULL){
    cout<<"State: " << current->state<<endl;
    cout<<"Hospital: "<<current->hospital<<endl;
    cout<<"Success Rate: "<<current->successRate<<endl;
    cout<<"Mortality Rate: " << current->mortalityRate<<endl;
    cout<<"Cost: $"<<current->cost<<endl;
    cout<<"--------------------------------------"<<endl;
    current= current->next;
}
}

void SavedTreatment_LL::sortLowestCost(){ //standard swap sort for cost, success, and mort rate
SavedTreatment *current = head;
 while (current != NULL && current->next !=NULL){
     if (current->cost > (current->next)->cost){
         swap(current->cost, (current->next)->cost);
         swap(current->state, (current->next)->state);
         swap(current->hospital, (current->next)->hospital);
         swap(current->successRate, (current->next)->successRate);
         swap(current->mortalityRate, (current->next)->mortalityRate);
     }
     current = current->next;
 }
}

void SavedTreatment_LL::sortHighestSucess(){
for (int i=0; i<10; i++){
SavedTreatment *current = head;
 while (current != NULL && current->next !=NULL){
     if (stof(current->successRate) < stof((current->next)->successRate)){
         swap(current->cost, (current->next)->cost);
         swap(current->state, (current->next)->state);
         swap(current->hospital, (current->next)->hospital);
         swap(current->successRate, (current->next)->successRate);
         swap(current->mortalityRate, (current->next)->mortalityRate);
     }
     current = current->next;
 }
}
}

void SavedTreatment_LL::sortLowestMort(){
for (int t=0; t<10; t++){
SavedTreatment *current = head;
 while (current != NULL && current->next !=NULL){
     if (stof(current->mortalityRate) > stof((current->next)->mortalityRate)){
         swap(current->cost, (current->next)->cost);
         swap(current->state, (current->next)->state);
         swap(current->hospital, (current->next)->hospital);
         swap(current->successRate, (current->next)->successRate);
         swap(current->mortalityRate, (current->next)->mortalityRate);
     }
     current = current->next;
 }
}
}
