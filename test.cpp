#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct wordItem
{
  string word;
  int count;
};

void getStopWords(const char *ignoreWordFileName, string ignoreWords[])
{
  string line = "";
  int i = 0;
  ifstream inputFile (ignoreWordFileName);

  if (inputFile.is_open())
  {
    while (getline(inputFile, line, '\n'))
    {

         ignoreWords[i] = line;
         i++;

    }
    inputFile.close();
  }

  else
  {
    cout << "Failed to open " << ignoreWordFileName << endl;
  }
}

//changes made

bool isStopWord(string word, string ignoreWords[])
{
  for(int x = 0; x < 50; x++)
  {
    if (ignoreWords[x] == word)
    {
      return true;
    }
  }
  return false;
}

int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
int count = 0;
for(int x = 0; x < length; x++)
{
    uniqueWords[x];
    count = count + uniqueWords[x].count;
}
return count;
}

void arraySort(wordItem uniqueWords[], int length)
{
     for (int i = 0; i < length - 1; i++)
     {
         int low = i;

         for (int j = length -1; j > i; j--)
         {
             if (uniqueWords[j].count > uniqueWords[j-1].count)
             {
               wordItem temp = uniqueWords[j];
               uniqueWords[j] = uniqueWords[j-1];
               uniqueWords[j-1] = temp;
             }
         }
     }
}


void printTopN(wordItem uniqueWords[], int topN, int totalNumWords)
{
 float probability;

   for(int ind = 0; ind < topN; ind++)
   {
     probability = ((float) uniqueWords[ind].count) / totalNumWords;
     cout << fixed << setprecision(4) << probability << " - " << uniqueWords[ind].word << endl;
   }
}


void doubleArray (struct wordItem* &tempArr, int counter, int size)
{
    wordItem* newArray = new wordItem[size];

    for (int i = 0; i < counter; i++)
    {
      newArray[i] = tempArr[i];
    }

    size*=2;
    delete [] tempArr;
    tempArr = newArray;
}

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    cout << "Usage: ";
    cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>";
    cout << endl;
    return 0;
  }

  int size = 100;
  string ignoreWords[50];
  wordItem *tempArr = new wordItem [size];
  int wordsToPrint = stoi(argv[1]);
  string wordsToReadFile = argv[2];
  getStopWords(argv[3], ignoreWords);
  string word;
  int total_wordCount = 0;
  int unique_wordCount = 0;
  int timesDoubled = 0;
  bool a = isStopWord(word, ignoreWords);
  bool oldUniqueWord;

  ifstream file;
  file.open(wordsToReadFile);
  if(file.is_open())
  {
    while(file >> word)
    {
      a = isStopWord(word, ignoreWords);
      if(a == false)
      {
        total_wordCount++;

        for(int p = 0; p < unique_wordCount; p++)
        {
           oldUniqueWord = false;
          if(word == tempArr[p].word)  // if there is not a stop word
          {
            oldUniqueWord = true;
            tempArr[p].count = tempArr[p].count + 1;
            break;
          }
        }
        if (oldUniqueWord == false)
        {
            //unique_wordCount++;
            if (unique_wordCount == size)
            {
              size = size * 2;
              timesDoubled++;
              doubleArray(tempArr, unique_wordCount, size);
            }
            tempArr[unique_wordCount].word = word;

            tempArr[unique_wordCount].count = tempArr[unique_wordCount].count + 1;
            unique_wordCount++;
          }
        }
      }
    }


cout << "Array doubled: " << timesDoubled <<endl;
cout << "#" << endl;
cout << "Unique non-common words: "<< unique_wordCount << endl;
cout << "#" << endl;
cout << "Total non-common words: " << total_wordCount << endl;
cout << "#" << endl;
cout << "Probabilities of top "<< wordsToPrint << " most frequent words" << endl;
cout << "---------------------------------------" << endl;
arraySort(tempArr, unique_wordCount);
printTopN(tempArr, wordsToPrint, total_wordCount);

file.close();
delete[] tempArr;
}
