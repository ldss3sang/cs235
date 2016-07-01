/***********************************************************************
* Program:
*    Assignment 09, Node Class
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    Write a program that creates a linked list of 100 nodes and sort them
*    in ascending order. Each node will contain a single integer. The integers
*    will be read from a file. 
***********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/*******************************************************************
 * Node class
 * Contains the class definition of a Node and a List
 *******************************************************************/
class Node
{
   private:
      int data;                // --- data in each node
      Node* next;              // --- pointer to next node

   public:
      Node();                  // --- Creates empty node
      Node* getNext();         // --- returns next pointer of a node
      int getData();           // --- returns data of a node
      void setData(int item); // --- stores item in data member of current node
      void setNext(Node* node);// --- sets next to point to node
};

/**********************************************************************
 * default constructor
 * initialize data and next.
 ***********************************************************************/
Node::Node()
{
   data = 0;
   next = NULL;
}

/**********************************************************************
 * getNext
 * get next node
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
 * set pointer in next node
 ***********************************************************************/
void Node::setNext(Node* node)
{
   next = node;
}

/**********************************************************************
 * main
 * read the data from a file and sort the data using linked list.
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

   Node* head = new Node; // head node
   Node* pCurr = head; // current node which moves until null.
   int value;
             
   while ( fin >> value )
   {
      Node* pPrev = NULL;
      Node* pNew = new Node;
      
      pNew->setData(value);// set value into data of new node

      if (!head->getNext())// check if head node is null
         head->setNext(pNew);
      else
      {
         pCurr = head->getNext();
         pPrev = head; // previous node which move with current node
         
         while (pCurr)
         {
            //the case that value from file is greater than node data
            if (pCurr->getData() >= value)
            {
               // insert new node before current node.
               pPrev->setNext(pNew);
               pNew->setNext(pCurr);
               break;
            }
            // the case that value from file is less than node data
            // and current node is the end of linked list.
            else if (!pCurr->getNext())
            {
               // insert new node after the end of linked list
               pCurr->setNext(pNew);
               pCurr = pNew;
            }
            // move previous pointer and current pointer to each next node
            pPrev = pCurr;
            pCurr = pCurr->getNext();
         }
      }
   }

   pCurr = head->getNext();
   int count = 0;

   // display the linked list
   while (pCurr)
   {
      cout << setw(3) << pCurr->getData();
      pCurr = pCurr->getNext();
      count++;
      if (count == 20)
      {
         cout << endl;
         count = 0;
      }
   }

   fin.close();
   
   return 0;
}


