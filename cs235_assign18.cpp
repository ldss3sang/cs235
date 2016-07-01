/***********************************************************************
* Program:
*    Assignment 18, Merge Sort
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    write a program to implements the natural merge sort as a linked 
*    list. You must use the external sort algorithm. The program reads
*    the numbers from a file. The numbers will be between 1 and 50.
***********************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;

/***********************************************************************
 * split
 * Split the original list 'f' into sublists 'f1' and 'f2' by copying
 * natural sorted sublists of 'f' alternately to 'f1' and 'f2'
 **********************************************************************/
int split(list < int > f, list < int > &f1, list < int > &f2)
{
   list < int > ::iterator it = f.begin();
   // pointer that points to sublist 'f1' or 'f2'
   list < int > *ptr = &f1;

   // previous value of 'f1' or 'f2'
   int prev = *it;
   
   f1.push_back(*it);
   it++;

   // number of sublist
   int numSub = 1;

   // while loop until the end of 'f' has not been reached
   while (it != f.end())
   {
      // check the end of sublist
      if (*it < prev)
      {
         // change the pointer of 'f1' or 'f2'
         if (ptr == &f1)
            ptr = &f2;
         else
            ptr = &f1;
         numSub++;
      }
      ptr->push_back(*it);
      prev = *it;
      it++;
   }

   return numSub;
}

/***********************************************************************
 * merge
 * Merge corresponding sorted sublists from 'f1' and 'f2' to produce
 * the output into 'f'
 **********************************************************************/
list < int > merge(list < int > f1, list < int > f2)
{
   // 'f' for output
   list < int > f;
   list < int > ::iterator it1 = f1.begin();
   list < int > ::iterator it2 = f2.begin();
   int numSub = 0;

   // previous values for 'f1' and 'f2'
   int prev1 = 0;
   int prev2 = 0;

   // while neither the end of 'f1' nor the end of 'f2' has been reached 
   while ((it1 != f1.end()) && (it2 != f2.end()))
   {
      prev1 = 0;
      prev2 = 0;

      // loop until no end of sublist in 'f1' or in 'f2' has been reached
      do
      {
         
         if (*it1 < *it2)
         {
            f.push_back(*it1);
            prev1 = *it1;
            it1++;
         }
         else
         {
            f.push_back(*it2);
            prev2 = *it2;
            it2++;
         }
      }
      while (((prev1 < *it1) && (prev2 < *it2)) &&
             ((it1 != f1.end()) && (it2 != f2.end())));

      // copy the rest of corresponding sublist in 'f1' or 'f2' to 'f'
      if (prev1 > *it1)
      {
         while ((prev2 < *it2) && (it2 != f2.end()))
         {
            f.push_back(*it2);
            prev2 = *it2;
            it2++;
         }
      }
      if (prev2 > *it2)
      {
         while ((prev1 < *it1) && (it1 != f1.end()))
         {
            f.push_back(*it1);
            prev1 = *it1;
            it1++;
         }
      }     
   }

   // copy any sublists remaining in 'f1' or 'f2' to 'f'
   while ((it1 != f1.end()) || (it2 != f2.end()))
   {
      if (it1 == f1.end())
      {
         f.push_back(*it2);
         it2++;
      }
      else
      {
         f.push_back(*it1);
         it1++;
      }
   }
   
   return f;
}

/***********************************************************************
 * mergeSort
 * use natural mergesort to sort the original list 'f'.
 * call split and merge functions. 
 **********************************************************************/
void mergeSort(list < int > &f)
{
   // 'f1' and 'f2' for sublists
   list < int > f1;
   list < int > f2;

   // the number of sublists
   int numSub = 0;

   // loop until the number of sublists is equal to 1
   while (numSub != 1)
   {
      // split 'f' into sublists 'f1' and 'f2'
      numSub = split(f, f1, f2);
      if (numSub == 1)
         return;
      // merge corresponding sublists in 'f1' and 'f2' back into f
      f = merge(f1, f2);
      f1.clear();
      f2.clear();
   }

   
}

/***********************************************************************
 * main
 * reads the number from a file and makes list of numbers, and then call
 * mergeSort function and display the sorted numbers.
 **********************************************************************/
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

   // 'f' for an original list of numbers
   int num;
   list < int > f;

   while (fin >> num)
   {
      f.push_back(num);
   }

   // natural merge sort
   mergeSort(f);

   list < int > ::iterator it = f.begin();

   // display sorted number
   while (it != f.end())
   {
      cout << *it << " ";
      it++;
   }

   cout << endl;

   return 0;
}
