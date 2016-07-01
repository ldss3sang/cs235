/***********************************************************************
* Program:
*    Assignment 01, Set Program
*    Brother Ercanbrack, CS235
* Author:
*    Sangseok Doe
* Summary: 
*    Create a class definition for a set of integers. A set is a collection
*    of data without repetition or ordering. the class should need only
*    two or three private data members. Also, I create the overloaded
*    operators for intersection, union, and difference of the set.
***********************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

/****************************************************************
 * Class Name: Set
 * Summary: This class contains methods for the creation,
 * manipulation of set objects.
 ****************************************************************/
class Set
{
   public:
      Set();
      Set(const Set &aSet);
      ~Set();

      void setSize(int aSize);
      void setCapacity(int aCapacity);
      void setSet(int* aSet);

      int getSize();
      int getCapacity();
      int* getSet();

      // add element in a set
      void add(int element);
      // check for duplicates of the element in a set
      bool isDuplicate(int element);
      // display set object.
      void display(string setName);
      // sort the element in the set
      void sort();

      // overloaded operator of intersection
      Set operator && (Set& rSide);
      // overloaded operator of union
      Set operator || (Set& rSide);
      // overloaded operator of difference
      Set operator - (Set& rSide);
      // overloaded operator of assignment
      Set& operator = (const Set& rSide);
   
   private:
      int size;// the real size of a set
      int capacity;//the maximum size of a set
      int *set;
};

/***********************************************************
 * Default constructor - initializes the member variables.
 **********************************************************/
Set::Set()
{
   size = 0;
   capacity = 0;
   set = new int;
}

/**********************************************************
 * Copy constructor - Create set object
 *********************************************************/
Set::Set(const Set &aSet)
{
   size = aSet.size;
   capacity = aSet.capacity;
   set = new int[capacity];
   for (int i = 0; i < size;i++)
      set[i] = aSet.set[i];
}

/*********************************************************
 * Destructor - release the data of the array in set class
 ********************************************************/
Set::~Set()
{
   delete [] set;
}

/*********************************************************
 * setCapacity
 * set capacity
 ********************************************************/
void Set::setCapacity(int aCapacity)
{
   capacity = aCapacity;
   delete [] set;
   set = new int[capacity]; 
}

/**********************************************************
 * setSize
 * set Size
 **********************************************************/
void Set::setSize(int aSize)
{
   size = aSize;
}

/**********************************************************
 * setSet
 * set set
 **********************************************************/
void Set::setSet(int *aSet)
{
   set = aSet;
}

/***********************************************************
 * getSize
 * return size
 ***********************************************************/
int Set::getSize()
{
   return size;
}

/***********************************************************
 * getCapacity
 * get capacity
 **********************************************************/
int Set::getCapacity()
{
   return capacity;
}

/***********************************************************
 * getSet
 * return set
 ***********************************************************/
int* Set::getSet()
{
   return set;
}

/**********************************************************
 * add
 * add an element to the set and check for duplicates
 *********************************************************/
void Set::add(int element)
{
   if (!isDuplicate(element))
   {
      set[size] = element;
      size++;
   }
}

/*********************************************************
 * display
 * display the set
 ********************************************************/
void Set::display(string setName)
{
   cout << setName << endl;
   // sort the elements of the set.
   sort();
   
   int count = 0;
   
   for (int i = 0; i < size; i++)
   {
      cout << setw(4) << set[i];
      // display ten number in a row. 
      count++;
      if (count > 9)
      {
         cout << endl;
         count = 0;
      }
   }
   cout << endl;
   if (count != 0 || size == 0)
      cout << endl;
}

/***********************************************************
 * isDuplicate
 * check duplicates of elements in the set
 ************************************************************/
bool Set::isDuplicate(int num)
{
   int count = 0;
   for (int i = 0; i < size; i++)
      // count the number of duplicates
      if (set[i] == num)
         count++;
   if (count >= 1)
      return true;
   else
      return false;
}

/**********************************************************************
 * sort
 * sort the elements of the set
 *********************************************************************/
void Set::sort()
{
   int temp;
   for (int i = 0; i < size - 1; i++)
   {
      for (int j = (i + 1); j < size; j++)
      {
         if (set[i] > set[j])
         {
            temp = set[i];
            set[i] = set[j];
            set[j] = temp;
         }
      }
   }   
}

/*********************************************************
 * operator &&
 * overload operator && and find the intersection of the two sets
 *********************************************************/
Set Set::operator && (Set& rSide)
{
   Set temp;
   temp.setCapacity(capacity + rSide.capacity);
   
   for (int i = 0; i < size; i++)
   {
      if (rSide.isDuplicate(set[i]))
      {
         temp.add(set[i]);
      }
   }
   
   return temp;
}

/*************************************************************
 * operator ||
 * overload operator || and find the union of the two sets
 *************************************************************/
Set Set::operator || (Set& rSide)
{
   Set temp;
   
   temp.setCapacity(capacity + rSide.capacity);
 
   for (int i = 0; i < size; i++)
      temp.add(set[i]);
   for (int i = 0; i < rSide.size; i++)
      temp.add(rSide.set[i]);  
   
   return temp;
   
}

/**************************************************************
 * operator -
 * overload operator - and find the difference of the two sets
 **************************************************************/
Set Set::operator - (Set& rSide)
{
   Set temp;

   temp.setCapacity(capacity + rSide.capacity);
   
   for (int i = 0; i < size; i++)
   {
      if (!rSide.isDuplicate(set[i]))
      {
         temp.add(set[i]);
      }
   }
   
   return temp;
}

/***************************************************************
 * operator =
 * overload operator = and assign the data of the right side to
 * the left side
 ***************************************************************/
Set& Set::operator = (const Set& rSide)
{
   if (this == &rSide)
      return *this;
   else
   {
      if (rSide.capacity > capacity)
      {
         delete [] set;
         set = new int[rSide.capacity];
         capacity = rSide.capacity;
      }
      for (int i = 0;i < rSide.size; i++)
         set[i] = rSide.set[i];
      size = rSide.size;
   }
   return *this;
}
  
void intersections(Set setA, Set setB);
void unions(Set setA, Set setB);
void differences(Set setA, Set setB, string setName);

/***********************************************************
 * main
 * create set objects and find the intersection, the union, and
 * the difference of the two sets.
 **************************************************************/
main(int argc, char *argv[])
{
   char *inFileName;

   // get the file name
   if (argc > 1)
      inFileName = argv[1];
   else
   {
      cout << "Enter input filename: ";
      inFileName = new char[80];
      cin >> inFileName;
   }
   
   Set setA;
   Set setB;
   int element;
   int capacity;//the size of the data from input file
   
   ifstream fin(inFileName);
   if (fin.fail())
   {
      cout << " File open failed!" << endl;
      exit(1);
   }
   
   fin >> capacity;
   
   setA.setCapacity(capacity);

   // add the elements in the set A
   for (int i = 0; i < capacity; i++)
   {
      fin >> element;
      setA.add(element);
   }
   
   setA.display("Set A:");
   
   fin >> capacity;
   
   setB.setCapacity(capacity);

   // add the elements in the set B
   for (int i = 0; i < capacity; i++)
   {
      fin >> element;
      setB.add(element);
   }
   
   setB.display("Set B:");
   
   intersections(setA, setB);
   
   unions(setA, setB);
   
   differences(setA, setB, "A and B:");
   
   differences(setB, setA, "B and A:");
   
   return 0;
}

/*********************************************************************
 * intersections
 * find the intersection of the two sets using overloaded operator &&.
 *********************************************************************/
void intersections(Set setA, Set setB)
{
   Set intersection;
   intersection = setA && setB;
   intersection.display("Intersection of A and B:");
}

/******************************************************************
 * unions
 * find the union of the two sets using overloaded operator ||.
 *****************************************************************/
void unions(Set setA, Set setB)
{
   Set unions;
   int capacity = setA.getCapacity() + setB.getCapacity();
   unions.setCapacity(capacity);
   unions = setA || setB;
   unions.display("Union of A and B:");
}

/******************************************************************
 * differences
 * find the difference of the two sets using overloaded operator -
 *****************************************************************/
void differences(Set setA, Set setB, string setName)
{
   Set differences;
   differences = setA - setB;
   cout << "Difference of ";
   differences.display(setName);
}
