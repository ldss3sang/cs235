/***********************************************************************
* Program:
*    Assignment 02, Stack Library
*    Brother Ercanbrack, CS235
* Author:
*    Sangseok Doe
* Summary: 
*    create a program to implement a stack using an array.
***********************************************************************/
#include "stack.h"

/**********************************************************************
 * Default constructor
 * Initialize values (stack size 100)
 *********************************************************************/
Stack::Stack(int size)
{
   myTop = -1;
   maxSize = size;
   stackItems = new int[size];
}

/**********************************************************************
 * copy constructor
 * copy object
 **********************************************************************/
Stack::Stack(const Stack &aStack)
{
   myTop = aStack.myTop;
   maxSize = aStack.maxSize;
   stackItems = new int[maxSize];
   for (int i = 0; i < maxSize; i++)
      stackItems[i] = aStack.stackItems[i];
}

/***********************************************************************
 * top
 * returns the value of top item in the stack
 ***********************************************************************/
int Stack::top(void)
{
   if (empty())
   {
      cout << "ERROR: Stack Empty\n";
      exit(1);
   }
   return stackItems[myTop];
}

/***********************************************************************
 * push
 * store item on the stack
 ***********************************************************************/
void Stack::push(int item)   
{
   if (full())
   {
      cout << "ERROR: Stack Overflow\n";
      exit(1);
   }
   stackItems[ ++myTop ] = item;
}

/*************************************************************************
 * pop
 * remove/delete top item off stack
 *************************************************************************/
void Stack::pop(void)
{
   if (empty())
   {
      cout << "ERROR: Stack Underflow\n";
      exit(1);
   }
   --myTop;
}

/*************************************************************************
 * empty
 * check if stack is empty
 ************************************************************************/
bool Stack::empty(void)         
{
   return (myTop < 0);
}

/**************************************************************************
 * full
 * check if stack is full
 **************************************************************************/
bool Stack::full(void)          
{
   return (myTop == (maxSize - 1));
}

/***************************************************************************
 * destructor
 * free memories
 ***************************************************************************/
Stack::~Stack()                
{
   if (stackItems)
      delete [] stackItems;
}

/****************************************************************************
 * operator =
 * overloaded assignment operator
 ****************************************************************************/
Stack& Stack::operator = (const Stack &rtSide)
{
   if (this == &rtSide)
      return *this;
   else
   {
      delete [] stackItems;
      myTop = rtSide.myTop;
      maxSize = rtSide.maxSize;
      stackItems = new int[maxSize];
      
      for (int i = 0; i < maxSize; i++)
         stackItems[i] = rtSide.stackItems[i];
      return *this;
   }
}

