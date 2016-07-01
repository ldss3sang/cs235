/***********************************************************************
* Program:
*    Assignment 11, Hashing
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    Write a program to implement an appropriate hashing function for
*    inserting all of reserved words of C++ into a hash table of size 67.   
*    The hash table will be an array of STL list containers.
***********************************************************************/
#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

#define SIZE 67

int h(string);
void display(list < string > hashTable[SIZE]);

/**********************************************************************
 * main
 * read the data from a file and call hash function and insert the items
 * at the end of the linked list. And call display function to display
 * the items in the hash table. 
 ***********************************************************************/
int main(int argc, char* argv[])
{
   char* inFileName;
   
   //get the file name
   if (argc > 1)
      inFileName = argv[1];
   else
   {
      cout << "Enter input filename: ";
      inFileName = new char[80];
      cin >> inFileName;
   }
   
   ifstream fin(inFileName);
   if (fin.fail())
   {
      cout << "\n  Error - \"" << inFileName
           << "\" not found! Check your file name.\n\n";
      exit(1);
   }

   string word;
   list < string > hashTable[SIZE];

   // insert the items into the hash table
   // use chaining as the collision resolution
   while (fin >> word)
   {
      hashTable[h(word)].push_back(word);
   }

   display(hashTable);
   
}

/*********************************************************************
 * h
 * Hash function to return the index of each item 
 **********************************************************************/
int h(string word)
{
   int sum = 0;

   // adds up the ASCII values of each character in the word
   for (int i = 0; i < word.size(); i++)
   {
      sum += (int)word[i];
   }
   
   return (sum % 67);
}

/************************************************************************
 * display
 * Display the hash table in proper format output 
 ************************************************************************/
void display(list < string > hashTable[SIZE])
{
   list < string > ::iterator it;
  
   for (int i = 0; i < SIZE; i++)
   {
      cout << "table[" << i << "]";
      if (i < 10)
         cout << " ";
      cout << "-> ";
      
      if (hashTable[i].empty())
         cout << "(empty)";

      int j = 0;

      // display the items of each linked list in hash table. 
      for (it = hashTable[i].begin(); it != hashTable[i].end(); it++)
      {
         if (j > 0)
            cout << ", ";
         cout << *it;
         j++;
      }
      
      cout << endl;
   }
}
