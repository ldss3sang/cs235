/***********************************************************************
* Program:
*    Assignment 16, BoM word count
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    write a program that uses an associative array(STL map) to count the
*    number of occurrences of words from a data file.
***********************************************************************/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

/************************************************************************
 * removePunc
 * remove the punctuations from a word in the Book of Mormon except hyphens.
 ***********************************************************************/
void removePunc(string &word)
{
   string::iterator it = word.begin();
   
   while (it != word.end())
   {
      // check if each letter of word is alphabet
      if (isalpha(*it))
      {
         // change letters in a word to the lower case
         *it = tolower(*it);
         it++;
      }
      else if ( (*it) == '-')
      {
         it++;
      }
      else
      {
         // remove the punctuations
         word.erase(it);
      }   
   }
}

/******************************************************************************
 * main
 * create map for the words in the Book of Mormon and the number of occurrences
 * of that word. and display 100 most common words in the Book of Mormon.
 *****************************************************************************/
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

   // map for words and number of occurrences of words in the BOM.
   map < string, int, less < string > > bom;
   
   string word;
   int nWord = 0;

   // insert keys and values in map 
   while (fin >> word)
   {
      removePunc(word);

      if (bom[word])
         bom[word]++;
      else
         bom[word] = 1;

      nWord++;// count number of words processed
   }
   
   cout << endl << "Number of words processed: " << nWord << endl;
   cout << "100 most common words found and their frequencies:" << endl;

   // create new map
   // key: number of occurrences of word, value: word
   multimap < int, string, less < int > > bCount;
   map < string, int > ::reverse_iterator iter;

   // exchanges keys and values in map for bom.
   // insert new keys and new values in map for bCount
   for (iter = bom.rbegin(); iter != bom.rend(); iter++)
   {
      bCount.insert(pair < int, string > (iter->second,iter->first));
   }
   
   multimap < int, string > ::reverse_iterator it = bCount.rbegin();
   
   for (int j = 0;j < 100; j++)
   {
      //second: word, first: number of occurrences of word 
      cout << setw(23) << it->second << " - " << it->first << endl;
      it++;
   }
   
   return 0;
}




