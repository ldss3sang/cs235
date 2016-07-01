/***********************************************************************
* Program:
*    Assignment 10, List Class
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    write a program to implement a list using dynamic memory and
*    pointers and write the member functions for the List class.
***********************************************************************/
#include "list.h"

/**********************************************************************
 * default constructor of Node class
 * initialize data and next.
 ***********************************************************************/
Node::Node()
{
   data = 0;
   next = NULL;
}

/**********************************************************************
 * getNext
 * get the next node
 ***********************************************************************/
Node* Node::getNext()
{
   return next;
}

/**********************************************************************
 * getData 
 * get data in a node
 ***********************************************************************/
int Node::getData()
{
   return data;
}

/**********************************************************************
 * setData
 * set data into a node
 ***********************************************************************/
void Node::setData(int item)
{
   data = item;
}

/**********************************************************************
 * setNext
 * set pointer in the next node
 ***********************************************************************/
void Node::setNext(Node* node)
{
   next = node;
}

/**********************************************************************
 * default constructor of List class
 * initializes number of items and firstNode. 
 ***********************************************************************/
List::List()
{
   numItems = 0;
   firstNode = NULL;
}

/**********************************************************************
 * destructor
 * free memories in the list
 ***********************************************************************/
List::~List()
{
   Node* pCurr = firstNode;
   Node* pNext = NULL;

   for (int i = 0; i < numItems; i++)
   {
      pNext = pCurr->getNext();
      delete pCurr;
      pCurr = pNext;
   }
}

/**********************************************************************
 * copy constructor
 * copy an object
 ***********************************************************************/
List::List(const List &listToCopy)   // copy constructor
{
   numItems = 0;
   for (int i = 0; i < listToCopy.getNumItems(); i++)
   {
      insert(listToCopy.getData(i),i);
   }  
}

/**********************************************************************
 * operator =
 * overloaded assignment operator 
 ***********************************************************************/
List& List::operator = (const List &rightSide)
{
   Node* pCurr = firstNode;
   Node* pNext = NULL;

   // delete all data in the list of left side
   for (int i = 0; i < numItems; i++)
   {
      pNext = pCurr->getNext();
      delete pCurr;
      pCurr = pNext;
   }

   // reinsert new data of right side in the list of left side
   numItems = 0;
   for (int i = 0; i < rightSide.getNumItems(); i++)
   {
      insert(rightSide.getData(i),i);
   }  
}

/**********************************************************************
 * insert
 * insert item at specified position
 ***********************************************************************/
void List::insert(int item, int pos) 
{
   Node* pCurr = firstNode;
   Node* pPrev = NULL;
   Node* pNew = new Node;
   
   pNew->setData(item);
   
   // if position is 0, add new node before first node
   if (pos == 0 || numItems == 0)
   {
      firstNode = pNew;
      pNew->setNext(pCurr);
   }
   else
   {
      for (int i = 0; i < pos && i < numItems; i++)
      {
         pPrev = pCurr;
         pCurr = pCurr->getNext();
      }
      
      pPrev->setNext(pNew);// prev -> new
      pNew->setNext(pCurr);// prev -> new -> current
   }
   numItems++;
}

/**********************************************************************
 * remove
 * remove item at specified position
 ***********************************************************************/
void List::remove(int pos)
{
   Node* pCurr = firstNode;
   Node* pPrev = NULL;
   
   if (pos == 0)
      firstNode = pCurr->getNext();
   else
   {
      for (int i = 0; i < pos && pCurr->getNext(); i++)
      {
         pPrev = pCurr;
         pCurr = pCurr->getNext();
      }
      
      pPrev->setNext(pCurr->getNext());
   }
   
   delete pCurr;
   numItems--;
}

/**********************************************************************
 * lookup
 * returns position in linked list(zero relative)
 ***********************************************************************/
int List::lookup(int item) const 
{
   Node* pCurr = firstNode;
   int pos = 0;

   while (pCurr != NULL && pCurr->getData() != item)
   {
      pCurr = pCurr->getNext();
      pos++;
   }
   
   if (pCurr == NULL)
      pos = -1;

   return pos;
}

/**********************************************************************
 * getData
 * returns data located at the specified position
 ***********************************************************************/
int List::getData(int pos) const 
{
   Node* pCurr = firstNode;
   
   for (int i = 0; i < pos; i++)
   {
      pCurr = pCurr->getNext();
   }
   
   return pCurr->getData();
}

/**********************************************************************
 * empty
 * check if number of item in the list is empty. 
 ***********************************************************************/
int List::empty(void) const
{
   if (numItems == 0)
      return 1;
   else
      return 0;
}

/**********************************************************************
 * getNumItems
 * get number of item in the list
 ***********************************************************************/
int List::getNumItems(void) const
{
   return numItems;
}
