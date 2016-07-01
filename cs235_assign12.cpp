/***********************************************************************
* Program:
*    Assignment 12, Fibonacci Program
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    write a program to generate the Fibonacci numbers using doubly-linked
*    list. Each node of the linked list will contain 9 digits of the number.
***********************************************************************/
#include<iostream>
#include<iomanip>
#include<cstdlib>

#define MAX 1000000000
using namespace std;

/**********************************************************************
 * Node
 * node class that have data, next pointer, and previous pointer. 
 **********************************************************************/
class Node
{
   private:
      int data;                 // --- data in each node
      Node* next;               // --- pointer to next node
      Node* prev;
   
   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      Node* getPrev();
      int getData();            // --- returns data of a node
      void setData(int item);   // --- stores item in data member of current node
      void setNext(Node* node); // --- sets next to point to node
      void setPrev(Node* node);
};

/***********************************************************************
 * List
 * class that can implement the doubly-linked list.
 ************************************************************************/
class List
{
   private:
      int numItems;
      Node* firstNode;
      Node* lastNode;
  
   public:
      List();
      ~List();
      List(const List &listToCopy);   // copy constructor
      List& operator = (const List &rightSide);
      void insert(int item, int pos);
      void remove(int pos);
      int lookup(int item) const;
      int getData(int pos) const;
      int empty(void) const;
      int getNumItems(void) const;
};

/************************************************************************
 * BigInt
 * a class that can handle the big integer of fibonacci number
 ************************************************************************/
class BigInt
{
   private:
      List bigInt;
      int fibNum;
      void calculate();
   
   public:
      BigInt() {fibNum = 0;};
      BigInt(int num) { fibNum = num; calculate(); };
      int getFibNum() { return fibNum; };
      void setFibNum(int num) { fibNum = num; };
      void display(ostream& out ) const;
      BigInt operator +(BigInt addend2);
};

/*****************************************************************
 * operator <<
 * overloaded operator << that display the output of the fibonacci
 * number
 *****************************************************************/
inline ostream & operator << (ostream & out, const BigInt & number)
{
   number.display(out);
   return out;
}

/**********************************************************************
 * default constructor of Node class
 * initialize data and next.
 ***********************************************************************/
Node::Node()
{
   data = 0;
   next = NULL;
   prev = NULL;
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
 * getPrev
 * get the previous node
 ***********************************************************************/
Node* Node::getPrev()
{
   return prev;
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
 * setPrev
 * set pointer in the previous node
 ***********************************************************************/
void Node::setPrev(Node* node)
{
   prev = node;
}

/**********************************************************************
 * default constructor of List class
 * initializes number of items and firstNode. 
 ***********************************************************************/
List::List()
{
   numItems = 0;
   firstNode = NULL;
   lastNode = NULL;
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
   Node* temp = listToCopy.firstNode;
   
   for (int i = 0; i < listToCopy.getNumItems(); i++)
   {
      insert(temp->getData(),i);
      temp = temp->getNext();
   }  
}

/**********************************************************************
 * operator =
 * overloaded assignment operator 
 ***********************************************************************/
List& List::operator = (const List &rightSide)
{
   // delete all data in the list of left side
   this->~List();

   // reinsert new data of right side in the list of left side
   numItems = 0;
   Node* temp = rightSide.firstNode;
   
   for (int i = 0; i < rightSide.getNumItems(); i++)
   {
      insert(temp->getData(),i);
      temp = temp->getNext();
   }  
}

/**********************************************************************
 * insert
 * insert item at specified position
 ***********************************************************************/
void List::insert(int item, int pos) 
{
   Node* pCurr = firstNode;
   Node* pNew = new Node;
   
   pNew->setData(item);
   
   // if position is 0, add new node before first node
   if (pos == 0 || numItems == 0)
   {
      firstNode = pNew;
      pNew->setNext(pCurr);
      if (numItems != 0)
         pCurr->setPrev(pNew);
      else
         lastNode = pNew;
   }
   else if ((numItems - 1) <= pos)
   {
      pCurr = lastNode;
      lastNode = pNew; 
      pNew->setPrev(pCurr);
      pCurr->setNext(pNew);
   }
   else
   {
      for (int i = 0; i < pos; i++)
      {
         pCurr = pCurr->getNext();
      }
      
      pCurr->getPrev()->setNext(pNew);//prev -> new
      pNew->setNext(pCurr);// new -> next
      pNew->setPrev(pCurr->getPrev());// prev <- new
      pCurr->setPrev(pNew);// new <- next  
   }
   numItems++;
}

/**********************************************************************
 * remove
 * remove item at specified position
 ***********************************************************************/
void List::remove(int pos)
{
   if (numItems == 0)
      return;
   
   Node* pCurr = firstNode;
         
   if (numItems == 1)
   {
      firstNode = NULL;
      lastNode = NULL;
   }
   else if (pos == 0)
   {
      pCurr->getNext()->setPrev(NULL);
      firstNode = pCurr->getNext();
   }
   else if ( (numItems - 1) <= pos)
   {
      pCurr = lastNode;
      lastNode = pCurr->getPrev();
      pCurr->getPrev()->setNext(NULL);
   }
   else
   {
      for (int i = 0; i < pos; i++)
      {
         pCurr = pCurr->getNext();
      }
      
      pCurr->getPrev()->setNext(pCurr->getNext());
      pCurr->getNext()->setPrev(pCurr->getPrev());
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
   
   for (int i = 0; i < pos && i < numItems; i++)
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

/*********************************************************************
 * calculate
 * calcuate the fibonacci number
 *********************************************************************/
void BigInt::calculate()
{
   BigInt f1;
   BigInt f2;

   if (fibNum == 0)
      f1.bigInt.insert(0,0);
   else
      f1.bigInt.insert(1,0);

   if (fibNum > 1)
      f2.bigInt = f1.bigInt;
   else
   {
      bigInt = f1.bigInt;
      return;
   }

   BigInt temp;
   for (int i = 2; i < fibNum; i++)
   {
      temp = f1 + f2;
      f1.bigInt = f2.bigInt;
      f2.bigInt = temp.bigInt;
   }

   bigInt = f2.bigInt;
}

/*************************************************************************
 * display
 * display the result of the fibonacci number.
 *************************************************************************/
void BigInt::display(ostream& out) const
{
   bool zero = false;
   for(int i = 0; i < bigInt.getNumItems(); i++)
   {
      if (zero)
         out << setfill('0') << setw(9);
      else
         zero = true;

      out << bigInt.getData(i);
   }
}

/**************************************************************************
 * operator +
 * overloaded operator + that can add two big integers.
 **************************************************************************/
BigInt BigInt::operator +(BigInt rtSide)
{
   BigInt sum;
   int first;
   int second;
   int result;
   int carry = 0;
   int i = bigInt.getNumItems() - 1;
   int j = rtSide.bigInt.getNumItems() - 1;

   while (i >= 0 || j >= 0)
   {
      if (i >= 0)
      {
         first = bigInt.getData(i);
         i--;
      }
      else
         first = 0;
      
      if (j >= 0)
      {
         second = rtSide.bigInt.getData(j);
         j--;
      }
      else
         second = 0;

      int temp = first + second + carry;
      result = temp % MAX;
      carry = temp / MAX;
      sum.bigInt.insert(result, 0);
   }
   
   if ( carry > 0)
      sum.bigInt.insert(carry, 0);
   
   return sum;
}
/**********************************************************************
 * main
 * Prompt the number for a user and calculate the fibonacci number
 * and display the number.
 ***********************************************************************/
int main(int argc, char* argv[])
{
   int number;
   // get the number from an user
   if (argc > 1)
      number = atoi(argv[1]);
   else
   {
      cout << "\nEnter number: ";
      cin >> number;
   }

   BigInt fibo(number);

   cout << fibo << endl << endl;
   
   return 0;
}

