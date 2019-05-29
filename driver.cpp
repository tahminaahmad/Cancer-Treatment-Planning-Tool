#include "Airfare_PQ.hpp"
#include "Costs_stack.hpp"
#include "SavedTreatment_LL.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;

//call main with executable, hospitals.csv, cancerCost.csv, airFare.csv
int main(int argc, char* argv[])
{

  int airFareCost;
  int totalCost;
  AirfarePQ airfareObject = AirfarePQ(1000);//fix peek function
  SavedTreatment_LL savedTreatmentObject;
  //Initialize basic data for each state in static arrays
  int treatmentIndex = 0;
  ifstream in_file1;
  ifstream in_file2;
  ifstream in_file3;
  string states[50];
  string hospitals[50];
  string successRate[50];
  string mortalityRate[50];
  string stateCodes[50] = {" AL"," AK"," AZ"," AR"," CA"," CO"," CT"," DE"," FL"," GA"," HI"," ID"," IL"," IN"," IA"," KS"," KY"," LA"," ME"," MD"," MA"," MI"," MN"," MS"," MO"," MT"," NE"," NV"," NH"," NJ"," NM"," NY"," NC"," ND"," OH"," OK"," OR"," PA"," RI"," SC"," SD"," TN"," TX", "UT"," VT"," VA"," WA"," WV"," WI"," WY"};
  string treatmentCode = "";
  in_file1.open(argv[1]);
  //read in hospitals file
  if(in_file1.is_open())
  {
    string state;
    string hospital;
    string success;
    string mortality;
    int i = 0;
    string line = "";
    while(getline(in_file1, line))
    {
      stringstream ss(line);
      getline(ss, state, ',');
      getline(ss, hospital, ',');
      getline(ss, success, ',');
      getline(ss, mortality, ',');
      states[i] = state;
      hospitals[i] = hospital;
      successRate[i] = success;
      mortalityRate[i] = mortality;
      i++;
    }
  }
  else
  {
    cout << "Failed" << endl;
  }
  //initialize new variables
  int costForMultiple = 0;
  string stateResidency;
  string newState;
  string insuranceOption;
  string option;
  string userStateCode;
  costStack newCost = costStack();
  //get users state and insurance
  cout << "Please enter your state of residency: ";
  getline(cin, stateResidency);
  int val;
  string destinationState = stateResidency;
  for(int i = 0; i < 50; i++)
  {
    if(stateResidency == states[i])
    {
      val = i;
      userStateCode = stateCodes[i];
      treatmentIndex = i;
    }
  }
  int check = 0;
  for(int i = 0; i < 50; i++)
  {
    if(stateResidency == states[i])
    {
      check = 1;
    }
  }
  if(check == 0)
  {
    cout << "Invalid option, please include capitalization." << endl;
    return 0;
  }
  //make sure that state is valid
  cout << "What is your insurance type? " << endl;
  cout << "Enter '1' for Medicare" << endl;
  cout << "Enter '2' for Medicaid" << endl;
  cout << "Enter '3' for Private Insurance" << endl;
  cin >> insuranceOption;
  cout << endl;
  string medicare[50];
  string medicaid[50];
  string privInsurance[50];
  int tracker = 0;
  in_file2.open(argv[2]);
  if(in_file2.is_open())
  {
    int x = 0;
    string care;
    string caid;
    string priv;
    string ignore;
    string line = "";
    while(getline(in_file2, line))
    {
      stringstream ss(line);
      getline(ss, ignore, ',');
      getline(ss, care, ',');
      getline(ss, caid, ',');
      getline(ss, priv, ',');
      medicare[x] = care;
      medicaid[x] = caid;
      privInsurance[x] = priv;
      x++;
    }
  }
  else
  {
    cout << "Failed in_file2" << endl;
  }
  costStack temp = costStack();
  for(int i = 0; i < 50; i++)
  {
    int care = stoi(medicare[i]);
    int caid = stoi(medicaid[i]);
    int priv = stoi(privInsurance[i]);
    if(insuranceOption == "1")
    {
      temp.push(care, states[i]);
    }
    else if(insuranceOption == "2")
    {
      temp.push(caid, states[i]);
    }
    else
    {
      temp.push(priv, states[i]);
    }
  }
  if(insuranceOption == "1")
  {
    insuranceOption = "Medicare";
  }
  else if(insuranceOption == "2")
  {
    insuranceOption = "Medicaid";
  }
  else if(insuranceOption == "3")
  {
    insuranceOption = "Private Insurance";
  }
  else
  {
    cout << "Invalid option" << endl;
    return 0;
  }
  int tempCostTreatment;
  //find cost of treatment in new state
  for(int i = 0; i < 50; i++)
  {
    if(temp.peek()->state == stateResidency)
    {
      tempCostTreatment = temp.peek()->costTreatment;
    }
    else
    {
      temp.pop();
    }
  }
  //set state code so it can be compared
  for(int i = 0; i < 50; i++)
  {
    if(temp.peek()->state == states[i])
    {
      treatmentCode = stateCodes[i];
    }
  }
  in_file3.open(argv[3]);
  if(in_file3.is_open())
  {
    int tracker = 0;
    string stateCode;
    string ignore;
    string ignore2;
    string destination;
    string ticketCost;
    int info;
    string line = "";
    while(getline(in_file3, line))
    {
      stringstream ss(line);
      getline(ss, ignore, ',');
      getline(ss, stateCode, ',');
      getline(ss, ignore2, ',');
      getline(ss, destination, ',');
      getline(ss, ticketCost, ',');
      destination.pop_back();
      stateCode.pop_back();
      if(userStateCode == stateCode && treatmentCode == destination)
      {
        airfareObject.addtoPQ(stoi(ticketCost));
      }
      tracker++;
    }
  }
  in_file3.close();
  //Now display information of new state
  cout << "The treatment cost in " << stateResidency << " with " << insuranceOption << " insurance is $" << tempCostTreatment << ".00" << endl;
  cout << "Would you like to find a cheaper option for treatment?" << endl;
  cout << "Enter '1' for yes" << endl;
  cout << "Enter '2' to see further details for this treatment" << endl;
  cin >> option;
  //get choice from user
  while(option == "1")
  {
    airfareObject.~AirfarePQ();
    temp.pop();
    //empty the priority queue and refill it with the state they are going to next
    if(temp.isEmpty())
    {
      cout << "This is the most expensive treatment center in the United States" << endl;
      return 0;
    }
    cout << "Your next cheapest treatment option is in ";
    //reset variables
    for(int i = 0; i < 50; i++)
    {
      if(temp.peek()->state == states[i])
      {
        treatmentCode = stateCodes[i];
      }
    }
    in_file3.open(argv[3]);
    if(in_file3.is_open())
    {
      string stateCode2;
      string ignore4;
      string ignore5;
      string destination2;
      string ticketCost2;
      int info2;
      string line2 = "";
      while(getline(in_file3, line2))
      {
        stringstream ss(line2);
        getline(ss, ignore4, ',');
        getline(ss, stateCode2, ',');
        getline(ss, ignore5, ',');
        getline(ss, destination2, ',');
        getline(ss, ticketCost2, ',');
        destination2.pop_back();
        stateCode2.pop_back();
        if(userStateCode == stateCode2 && treatmentCode == destination2)
        {
          airfareObject.addtoPQ(stoi(ticketCost2));
        }
        else
        {
          cout << "";
        }
      }
    }
    in_file3.close();
    //new state info is now stored properly
    cout << temp.peek()->state;
    cout << " and would cost an estimated $";
    cout << temp.peek()->costTreatment << ".00 for treatment.";
    cout << "." << endl << "Would you like to view another option?" << endl;
    cout << "1. See another option" << endl;
    cout << "2. See further details for this treatment" << endl;
    cin >> option;
  }
  for(int i = 0; i < 50; i++)
  {
    if(temp.peek()->state == states[i]);
    tracker = i;
    treatmentCode = stateCodes[i];
  }
  //set val tracker to new state
  for(int i = 0; i < 50; i++)
  {
    if(temp.peek()->state == states[i])
    {
      val = i;
    }
  }
  if(option == "2")
  {
    cout << "Viewing further details for: " << temp.peek()->state << ", $" << temp.peek()->costTreatment << ".00" << endl << endl;
    cout << "Your treatment would take place at " << hospitals[val]  << "." << endl << endl;
    cout << hospitals[val] << " has a success rate of " << successRate[val] << "% with cancer treatments." << endl << endl;
    cout << "The mortality rate for cancer in " << temp.peek()->state << " is " << mortalityRate[val] << " per 100,000 citizens per year." << endl << endl;
    if(stateResidency != temp.peek()->state)
    {
      string numberOfPeople;
      int airFareCost = airfareObject.peekValue();
      if(airFareCost == 0 || airFareCost > 5000)
      {
        cout << "We are unable to find any available direct flights" << endl;
      }
      else
      {
        cout << "The airfare for one person to travel from " << stateResidency << " to " << temp.peek()->state << " would cost $" << airFareCost << ".00" << endl << endl;

        cout << "How many people need a one way ticket to the treatment center?" << endl;
        cin >> numberOfPeople;
        costForMultiple = stoi(numberOfPeople);
        //calculate the total cost of the treatment
        totalCost = (airFareCost * costForMultiple) + temp.peek()->costTreatment;
      }
      cout << "Including airfare, your total cost of treatment and travel would cost $" << totalCost << ".00" << endl << endl;
    }
    cout << "Enter '1' to save this option" << endl << endl;
    cout << "Enter '2' to continue without saving" << endl << endl;
    cin >> option;
    //get users preference to save or not
    if(option == "1")
    {
      //call save option by using function call below
      savedTreatmentObject.addTreatment(NULL, temp.peek()->state, hospitals[val], successRate[val], mortalityRate[val], totalCost);
    }
    cout << "Would you like to view other options for treatment?" << endl;
    cout << "Enter '1' for yes" << endl;
    cout << "Enter '2' for no" << endl;
    cin >> option;
  }
  while(option == "1")
  {
    while(option == "1")
    {
      cout << "Your next cheapest treatment option is in ";
      temp.pop();
      cout << temp.peek()->state;
      cout << " and would cost an estimated $";
      cout << temp.peek()->costTreatment << ".00 for treatment.";
      cout << "." << endl << "Would you like to view another option?" << endl;
      cout << "Enter '1' to see another option" << endl;
      cout << "Enter '2' to see further details for this treatment" << endl;
      cin >> option;
      for(int i = 0; i < 50; i++)
      {
        if(temp.peek()->state == states[i])
        {
          val = i;
        }
      }
    }
    //viewing new info for specific treatment
    if(option == "2")
    {
      cout << "Viewing further details for: " << temp.peek()->state << ", $" << temp.peek()->costTreatment << ".00" << endl << endl;
      cout << "Your treatment would take place at " << hospitals[val] << "." << endl << endl;
      cout << hospitals[val] << " has a success rate of " << successRate[val] << "% with cancer treatments." << endl << endl;
      cout << "The mortality rate for cancer in " << temp.peek()->state << " is " << mortalityRate[val] << " per 100,000 citizens per year." << endl << endl;
      //make sure that a flight is available
      if(newState != temp.peek()->state)
      {
        airFareCost = airfareObject.peekValue();
        if(airFareCost == 0 || airFareCost > 5000)
        {
          cout << "We are unable to find any available direct flights" << endl;
        }
        else
        //repeat from here on
        {
          for(int i = 0; i < 50; i++)
          {
            if(temp.peek()->state == states[i])
            {
              treatmentCode = stateCodes[i];
            }
          }
          in_file3.open(argv[3]);
          if(in_file3.is_open())
          {
            string stateCode3;
            string ignore6;
            string ignore7;
            string destination3;
            string ticketCost3;
            int info3;
            string line3 = "";
            while(getline(in_file3, line3))
            {
              stringstream ss(line3);
              getline(ss, ignore6, ',');
              getline(ss, stateCode3, ',');
              getline(ss, ignore7, ',');
              getline(ss, destination3, ',');
              getline(ss, ticketCost3, ',');
              destination3.pop_back();
              stateCode3.pop_back();
              if(userStateCode == stateCode3 && treatmentCode == destination3)
              {
                airfareObject.addtoPQ(stoi(ticketCost3));
              }
              else
              {
                cout << "";
              }
            }
          }
          in_file3.close();
          cout << "The airfare for one person to travel from " << stateResidency << " to " << temp.peek()->state << " would cost $" << airFareCost << ".00" << endl << endl;
          cout << "How many people need a one way ticket to the treatment center?" << endl;
          cin >> option;
          costForMultiple = stoi(option);
          totalCost = (airFareCost * costForMultiple) + temp.peek()->costTreatment;
        }
        cout << "Including airfare, your total cost of treatment and travel would cost $" << totalCost << ".00" << endl << endl;
      }

    }
    cout << "Would you like to save this option to compare with other options later?"  << endl;
    cout << "Enter '1' to save." << endl;
    cout << "Enter '2' to continue" << endl;
    cin >> option;

    if(option == "1")
    {
      savedTreatmentObject.addTreatment(NULL, temp.peek()->state, hospitals[val], successRate[val], mortalityRate[val], totalCost);
    }
    cout << "Would you like to view other options for treatment?" << endl;
    cout << "Enter '1' for yes." << endl;
    cout << "Enter '2' for no" << endl;
    cin >> option;
  }
  int value = 1;
  while(value == 1)
  {
    cout << "Would you like to sort your saved treatment plans by treatment cost, success rate, OR mortality rate?" << endl << endl;
    cout << "1. Sort cheapest to most expensive treatment costs" << endl << endl;
    cout << "2. Sort success rate of treatments, highest to lowest" << endl << endl;
    cout << "3. Sort mortality rates in the states of your saved treatment centers, lowest to highest" << endl << endl;
    cin >> option;
    //sort saved plans by mortality rate, success rate, or total cost based on users preference
    if(option == "1")
    {
      if(savedTreatmentObject.isEmpty())//check if any plans were saved
      {
        cout << "You did not save any plans!" << endl << endl;
      }
      else
      {
        cout << "Here are your saved treatment plans sorted by lowest to highest cost:" << endl;
        savedTreatmentObject.sortLowestCost();
        savedTreatmentObject.printSaved();
      }
    }
    else if(option == "2")
    {
      if(savedTreatmentObject.isEmpty())
      {
        cout << "You did not save any plans!" << endl << endl;
      }
      else
      {
        cout << "Here are your saved treatment plans sorted by highest to lowest success rate:" << endl;
        savedTreatmentObject.sortHighestSucess();
        savedTreatmentObject.printSaved();
      }
    }
    else if(option == "3")
    {
      if(savedTreatmentObject.isEmpty())
      {
        cout << "You did not save any plans!" << endl << endl;
      }
      else
      {
        cout << "Here are your saved treatment plans sorted by lowest to highest mortality rates:" << endl;
        savedTreatmentObject.sortLowestMort();
        savedTreatmentObject.printSaved();
      }
    }
    if(savedTreatmentObject.isEmpty())
    {
      break;
    }
    else
    {
      cout << "Enter '1' to sort again" << endl;
      cout << "Enter '2' to end program" << endl;
      cin >> value;
    }
  }
  //end program
  cout << "Thank you for using the Cancer Treatment Planning Tool" << endl << endl;
  return 0;
}
