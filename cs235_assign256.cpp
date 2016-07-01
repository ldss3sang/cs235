/***********************************************************************
* Program:
*    Assignment 256, Final Project
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    open up a GEDCOM file named "cameron.ged". parse the file in order to
*    find each individual, their given name, lastname, birthdate and ID 
*    number. And insert the individual in alphabetical order into a linked
*    list. The list is sorted by last name, then by given name, then by
*    birthdate. Print the list of sorted individual to a file "sorted.dat"
*    After that, build family tree and display level order traversal.
***********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

/**********************************************************************
 * Node
 * node class that have data, next pointer, and previous pointer. 
 **********************************************************************/
template < class T >
class Node
{
   private:
      T data;                  // --- data in each node
      Node < T > * next;       // --- pointer to next node
      Node < T > * prev;
   
   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      Node* getPrev();
      T getData();              // --- returns data of a node
      void setData(T item);   // --- stores item in data member of current node
      void setNext(Node* node); // --- sets next to point to node
      void setPrev(Node* node);
};

/***********************************************************************
 * List
 * class that can implement the doubly-linked list.
 ************************************************************************/
template < class T >
class List
{
   private:
      int numItems;
      Node < T > * firstNode;
      Node < T > * lastNode;
  
   public:
      List();
      ~List();
      List(const List &listToCopy);   // copy constructor
      List& operator = (const List &rightSide);
      void insert(T item, int pos);
      void remove(int pos);
      int lookup(T item) const;
      T getData(int pos) const;
      T idSearch(int idNum);
      int empty(void) const;
      int getNumItems(void) const;
};

/**************************************************************
 * BTree
 * class that can implement binary tree. 
 *************************************************************/
template < class T >
class BTree
{
   private:
      T data;          // --- data stored in node of tree
      BTree* left;       // --- pointer to left subtree
      BTree* right;      // --- pointer to right subtree
      BTree* parent;     // --- pointer to the parent node;

   public:
      BTree();
      BTree(T data);  
      ~BTree(void);
      void insertLeft(T item); // creates a new node and inserts node to left
      void insertRight(T item);// creates a new node and inserts node to right
      BTree* getLeftChild(void);     // return the ptr to the left child
      BTree* getRightChild(void);    // return the ptr to the right child
      BTree* getParent(void);        // return parent
      T getData(void);
      void setData(T item);
      void setLeft(BTree* tree);     
      void setRight(BTree* tree);
      void infix(void);              // do infix traversal
      void prefix(void);             // do prefix traversal
      void buildTree(int childId, int husId, int wifeId, List < T > &family); 
      void postfix(void);            // do postfix traversal
      void level(void);              // do level order traversal
};

/******************************************************************
 * Date
 * this class contains day, month, and year of birthday of person.
 ******************************************************************/
class Date
{
   private:
      int day;
      int month;
      int year;
   
   public:
      Date() { day = 0; month = 0; year = 0; }
      const int getDay() const { return day; }
      const int getMonth() const { return month; }
      const int getYear() const { return year; }

      void setDay(int aDay) { day = aDay; }
      void setMonth(int aMonth) { month = aMonth; }
      void setYear(int aYear) { year = aYear; }

      bool operator < (const Date& rSide);
      bool operator > (const Date& rSide);

      void display(ostream& out) const;
};

/****************************************************************
 * operator <<
 * this function is an overloved operator << of Date class
 ****************************************************************/
ostream& operator << (ostream& out, const Date& rSide)
{
   rSide.display(out);

   return out;
}

/****************************************************************
 * Person
 * class that contains name, id number, birthday of the person and
 * member functions to implement this class
 ****************************************************************/
class Person
{
   private:
      string firstName;
      string lastName;
      int idNum;
      Date birthDate;
      int secondYear;
   
   public:
      Person() { idNum = 0; secondYear = 0; }
      string getFirstName() { return firstName; }
      string getLastName() {return lastName; }
      int getIdNum() { return idNum; }
      Date getBirthDate() { return birthDate; }
      int getSecondYear(){ return secondYear; }
      void setFirstName(string first) { firstName = first; }
      void setLastName(string last) { lastName = last; }
      void setIdNum(int id) { idNum = id; }
      void setBirthDate(Date birth) { birthDate = birth; }
      void setSecondYear(int year) { secondYear = year; }

      bool operator < (const Person& rSide);
      bool operator > (const Person& rSide);

      void display(ostream& out) const;
};

/*********************************************************
 * operator <<
 * this function is an overloaded operator of Person class
 *********************************************************/
ostream& operator << (ostream& out, const Person& rSide)
{
   rSide.display(out);

   return out;
}

/**********************************************************
 *                     Date Class
 **********************************************************/
/**********************************************************
 * operator <
 * an overloaded operator < to compare birthdays of two persons
 **********************************************************/
bool Date::operator < (const Date& rSide)
{
   if (year > rSide.year)
      return false;

   if (year < rSide.year)
      return true;

   if (month > rSide.month)
      return false;

   if (month < rSide.month)
      return true;

   if (day >= rSide.day)
      return false;

   return true;  
}

/***********************************************************
 * operator >
 * an overloaded operator > to compare birthdays of two persons
 ***********************************************************/
bool Date::operator > (const Date& rSide)
{
   if (year < rSide.year)
      return false;

   if (year > rSide.year)
      return true;

   if (month < rSide.month)
      return false;

   if (month > rSide.month)
      return true;

   if (day <= rSide.day)
      return false;

   return true;  
}

/****************************************************************
 * display
 * display the birthday of the person(ex. 2 FEB 1984)
 ****************************************************************/
void Date::display(ostream& out) const
{
   string monthChar[13] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                           "JUL", "AUG", "SEP", "OCT", "NOV", "DEC", "ABT"};

   out << "b. ";
   
   if (day > 0)
      out << day << " ";

   if (month > 0)
      out << monthChar[month - 1] << " ";
   
   out << year;

   return;
}

/********************************************************************
 *                          Person Class
 ********************************************************************/
/********************************************************************
 * operator <
 * an overloaded operator < to compare the name of two people and compare
 * last name first and then first name
 *********************************************************************/
bool Person::operator < (const Person& rSide)
{
   string lSideLast = lastName;
   string rSideLast = rSide.lastName;
   if (lSideLast.size() && rSideLast.size())
   {
      if (islower(lSideLast[0]))
      {
         lSideLast[0] = toupper(lSideLast[0]);
      }
      if (islower(rSideLast[0]))
      {
         rSideLast[0] = toupper(rSideLast[0]);
      }
   }
   
   
   if (lSideLast > rSideLast)
      return false;
   if (lSideLast < rSideLast)
      return true;
   
   if (firstName > rSide.firstName)
      return false;
   if (firstName < rSide.firstName)
      return true;

   if (birthDate > rSide.birthDate)
      return false;

   return true;
}

/********************************************************************
 * operator >
 * an overloaded operator > to compare the name of two people and compare
 * last name first and then first name
 *********************************************************************/
bool Person::operator > (const Person& rSide)
{
   if (lastName < rSide.lastName)
      return false;
   if (lastName > rSide.lastName)
      return true;
   
   if (firstName < rSide.firstName)
      return false;
   if (firstName > rSide.firstName)
      return true;

   if (birthDate < rSide.birthDate)
      return false;

   return true;
}

/*********************************************************************
 * display
 * display the first name, the last name, and birthday of the person 
 *********************************************************************/
void Person::display(ostream& out) const
{
   if (firstName.size() > 0)
      if (lastName.size() > 0)
         out << firstName << " ";
      else
         out << firstName;
   if (lastName.size() > 0)
      out << lastName;
   
   if (birthDate.getYear() > 0)
      out << ", " << birthDate;
   // if there are two years 
   if (secondYear > 0)
      out << "/" << secondYear;

   return;
}

/**********************************************************************
 *                        Node Class
 **********************************************************************/
/**********************************************************************
 * default constructor of Node class
 * initialize data and next.
 ***********************************************************************/
template < class T >
Node < T > ::Node()
{
   next = NULL;
   prev = NULL;
}

/**********************************************************************
 * getNext
 * get the next node
 ***********************************************************************/
template < class T >
Node < T > * Node < T > ::getNext()
{
   return next;
}

/**********************************************************************
 * getPrev
 * get the previous node
 ***********************************************************************/
template < class T >
Node < T > * Node < T > ::getPrev()
{
   return prev;
}

/**********************************************************************
 * getData 
 * get data in a node
 ***********************************************************************/
template < class T >
T Node < T > ::getData()
{
   return data;
}

/**********************************************************************
 * setData
 * set data into a node
 ***********************************************************************/
template < class T >
void Node < T > ::setData(T item)
{
   data = item;
}

/**********************************************************************
 * setNext
 * set pointer in the next node
 ***********************************************************************/
template < class T >
void Node < T > ::setNext(Node < T > * node)
{
   next = node;
}

/**********************************************************************
 * setPrev
 * set pointer in the previous node
 ***********************************************************************/
template < class T >
void Node < T > ::setPrev(Node < T > * node)
{
   prev = node;
}

/**********************************************************************
 * default constructor of List class
 * initializes number of items and firstNode. 
 ***********************************************************************/
template < class T >
List < T > ::List()
{
   numItems = 0;
   firstNode = NULL;
   lastNode = NULL;
}

/**********************************************************************
 * destructor
 * free memories in the list
 ***********************************************************************/
template < class T >
List < T > ::~List()
{
   Node < T > * pCurr = firstNode;
   Node < T > * pNext = NULL;

   for (int i = 0; i < numItems; i++)
   {
      pNext = pCurr->getNext();
      delete pCurr;
      pCurr = pNext;
   }
}

/**********************************************************************
 * copy constructor
 * copy an template
 ***********************************************************************/
template < class T >
List < T > ::List(const List &listToCopy)   // copy constructor
{
   numItems = 0;
   Node < T > * temp = listToCopy.firstNode;
   
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
template < class T >
List < T > &List < T > ::operator = (const List &rightSide)
{
   // delete all data in the list of left side
   this->~List();

   // reinsert new data of right side in the list of left side
   numItems = 0;
   Node < T > * temp = rightSide.firstNode;
   
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
template < class T >
void List < T > ::insert(T item, int pos) 
{
   Node < T > * pCurr = firstNode;
   Node < T > * pNew = new Node < T > ;
   
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
   else if ((numItems - 1) < pos)
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
template < class T >
void List < T > ::remove(int pos)
{
   if (numItems == 0)
      return;
   
   Node < T > * pCurr = firstNode;
         
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
template < class T >
int List < T > ::lookup(T item) const 
{
   Node < T > * pCurr = firstNode;
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
template < class T >
T List < T > ::getData(int pos) const 
{
   Node < T > * pCurr = firstNode;
   
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
template < class T >
int List < T > ::empty(void) const
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
template < class T >
int List < T > ::getNumItems(void) const
{
   return numItems;
}

/***********************************************************************
 * idSearch
 * find the person who have the same id number(parameter) in the list
 * and return person object.
 **********************************************************************/
template < class T >
T List < T > ::idSearch(int idNum)
{
   int size = numItems;

   // search the person
   for (int i = 0; i < size; i++)
   {
      if (idNum == this->getData(i).getIdNum())
      {
         return this->getData(i);
      }
   }
}

/**********************************************************************
 *                         BTree Class
 **********************************************************************/
/**********************************************************************
 * default constructor
 * initialize the data and pointers.
 **********************************************************************/
template < class T >
BTree < T > ::BTree()
{
   left = NULL;
   right = NULL;
   parent = NULL;
}

/**********************************************************************
 * constructor
 * initialize the data and pointers.
 **********************************************************************/
template < class T >
BTree < T > ::BTree(T data)
{
   this->data = data;
   left = NULL;
   right = NULL;
   parent = NULL;
}

/**********************************************************************
 * destructor
 **********************************************************************/
template < class T >
BTree < T > ::~BTree(void)
{
   
}

/**********************************************************************
 * insertLeft
 * creates a new node and inserts node to left
 **********************************************************************/
template < class T >
void BTree < T > ::insertLeft(T item) 
{
   left = new BTree < T > (item);
   left->parent = this;
}

/**********************************************************************
 * insertRight
 * creates a new node and inserts node to right
 **********************************************************************/
template < class T >
void BTree < T > ::insertRight(T item)   
{
   right = new BTree < T > (item);
   right->parent = this;
}

/**********************************************************************
 * getLeftChild
 * return the ptr to the left child
 **********************************************************************/
template < class T >
BTree < T > * BTree < T > ::getLeftChild(void)   
{
   return left;
}

/**********************************************************************
 * getRightChild
 * return the ptr to the right child
 **********************************************************************/
template < class T >
BTree < T > * BTree < T > ::getRightChild(void) 
{
   return right;
}

/**********************************************************************
 * getParent
 * return parent
 **********************************************************************/
template < class T >
BTree < T > * BTree < T > ::getParent(void)  
{
   return parent;
}

/**********************************************************************
 * getData
 * return data
 **********************************************************************/
template < class T >
T BTree < T > ::getData(void)
{
   return data;
}

/**********************************************************************
 * setData
 * set item into data
 **********************************************************************/
template < class T >
void BTree < T > ::setData(T item)
{
   data = item;
}

/**********************************************************************
 * setLeft
 * set left pointer and parent pointer
 **********************************************************************/
template < class T >
void BTree < T > ::setLeft(BTree < T > * tree)     
{
   left = tree;
   if ( tree != NULL)
      tree->parent = this;
}

/**********************************************************************
 * setRight
 * set right pointer and parent pointer
 **********************************************************************/
template < class T >
void BTree < T > ::setRight(BTree < T > * tree)
{
   right = tree;
   if (tree != NULL)
      tree->parent = this;
}

/**********************************************************************
 * buildTree
 * find the person who has the same child ID using prefix traversal
 * and set father and mother and build family tree  
 **********************************************************************/
template < class T >
void BTree < T > ::buildTree(int childId, int husId, int wifeId,
                           List < T > &family)
{
   if (data.getIdNum() == childId)
   {
      if (husId != 0)
         this->insertLeft(family.idSearch(husId));
      if (wifeId != 0)
         this->insertRight(family.idSearch(wifeId));
   }
   
   if (left != NULL && data.getIdNum() != childId)
      left->buildTree(childId, husId, wifeId, family);
         
   if (right != NULL && data.getIdNum() != childId)
      right->buildTree(childId, husId, wifeId, family);
}

/**********************************************************************
 * infix
 * do infix traversal  
 **********************************************************************/  
template < class T >
void BTree < T > ::infix()
{
   if (left != NULL)
      left->infix();
   
   cout << data << " ";
   
   if (right != NULL)
      right->infix();
}

/**********************************************************************
 * prefix
 * do infix traversal  
 **********************************************************************/  
template < class T >
void BTree < T > ::prefix()
{
   cout << data << " ";
    
   if (left != NULL)
      left->infix();
   
   if (right != NULL)
      right->infix();
}

/**********************************************************************
 * postfix
 * do postfix traversal 
 **********************************************************************/
template < class T >
void BTree < T > ::postfix(void)
{
   if (left != NULL)
      left->postfix();
   if (right != NULL)
      right->postfix();

   cout << data << " ";
}

/**********************************************************************
 * level
 * do level oreder traversal
 **********************************************************************/
template < class T >
void BTree < T > ::level()
{
   const int MAX = 100;
   BTree < T > *queue[ MAX ];
   BTree < T > *temp;
   int front = 0;
   int back = 0;
   int level = 0;
   int numGrParent = 0;  
   bool isNewGen = false;
   queue[ back++ ] = this;
   int prevBack = back;
   
   while (front != back)
   {
      
      temp = queue[front];
      front = (front + 1) % MAX;

      // check level of tree
      if (front == (prevBack + 1))
      {
         prevBack = back;
         isNewGen = true;
         level++;
      }
      else
         isNewGen = false;
      
      if (temp != NULL)
      {
         // visit
         if (temp->parent == NULL)
            cout << "The Ancestors of Gregory Lawrence Cameron:" << endl;
         else
         {
            if (isNewGen)
            {
               if (level == 1)
                  cout << "Parents:" << endl;
               else if (level == 2)
                  cout << "Grandparents:" << endl;
               else if (level == 3)
                  cout << "Great Grandparents:" << endl;
               else if (level == 4)
                  cout << "2nd Great Grandparents:" << endl;
               else if (level == 5)
                  cout << "3rd Great Grandparents:" << endl;
               else
                  cout << level - 2 << "th Great Grandparents:" << endl;
            }

            cout.width(8);
            cout << " " << temp->data << endl;
         }
         
         // end Visit        
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;
      }
   }
}


// non-member function prototype
void parsePerson(ifstream &fin, List < Person > &family, string &next);
void parseName(ifstream &fin, string &next, Person &indi);
void parseDate(ifstream &fin, string &next, Person &indi);
void parseFamily(ifstream &fin, List < Person > &family,
                 BTree < Person > &familyTree, string &next);

/**********************************************************************
 * main
 * read the file and parse the file and display the sorted name in a file
 * and display the level order of family tree
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

   string next;
   List < Person > family;
   BTree < Person > familyTree;
   
   fin >> next;

   // parse the file to find person's information
   // and relationship with each individual
   while (!fin.eof())
   {
      if (next == "0")
      {
         fin >> next;
         if (next[1] == 'I')
            parsePerson(fin, family, next);
         else if (next[1] == 'F')
            parseFamily(fin, family, familyTree, next);
      }

      if (next != "0")
         fin >> next;
   }

   // display sorted person by lastname in a file
   ofstream fout("sorted.dat");

   for (int i = 0; i < family.getNumItems(); i++)
   {
      fout << family.getData(i) << endl;
   }

   // display level order of family tree
   familyTree.level();
   return 0;
}

/******************************************************************
 * parsePerson
 * parse id and name and birthday form a file and insert the person
 * in a list
 ******************************************************************/
void parsePerson(ifstream &fin, List < Person > &family, string &next)
{
   string id = next.substr(2);
   id.erase(id.find('@',1));

   // individual person
   Person indi;
   
   indi.setIdNum(atoi(id.c_str()));
   
   parseName(fin, next, indi);
   parseDate(fin, next, indi);
     
   int size = family.getNumItems();

   if (size != 0)
   {
      // insert the person in the list sorted by last name
      for (int i = 0; i < size; i++)
      {
         if (indi < family.getData(i))
         {
            family.insert(indi, i);
            i = size;
         }
         else if (i == (size - 1))
            family.insert(indi, i + 1);
      }
   }
   else
   {
      family.insert(indi, 0);
   }

   
   return;
}

/******************************************************************
 * parseName
 * parse person's name from file( first name and last name.
 ******************************************************************/
void parseName(ifstream &fin, string &next, Person &indi)
{
   string tempFirst;
   string tempLast;

   int i = 0;

   // get the first name of person
   while (next != "BIRT" && next != "0")
   {
      if (next == "GIVN")
      {
         fin >> next;

         i = 0;

         while (!isdigit(next[0]))
         {
            if (i != 0)
               tempFirst += " ";

            tempFirst += next;
            i++;
            fin >> next;
         }
         indi.setFirstName(tempFirst);
      }
      // get the last name of person
      else if (next == "SURN")
      {
         fin >> next;

         i = 0;
         
         while (!isdigit(next[0]))
         {
            if (i != 0)
               tempLast += " ";

            tempLast += next;
            i++;
            fin >> next;
         }

         indi.setLastName(tempLast);
      }

      fin >> next;
   }

   return;
         
}

/******************************************************************
 * parseDate
 * parse the birthday of the person from the file(day, month, year)
 * set the birthday in Person object.
 ******************************************************************/
void parseDate(ifstream &fin, string &next, Person &indi)
{
   // find the Birth day
   while ( next != "BIRT" && next != "0" && !fin.eof())
   {
      fin >> next;
   }
   
   if (next == "0")
      return;
   
   fin >> next;
   
   if (next == "2")
   {
      fin >> next;
      
      if (next == "DATE")
      {
         Date tempBirth;
         
         fin >> next;
         
         do
         {
            // parse day from file
            if (next.size() <= 2 && isdigit(next[0]))
            {
               tempBirth.setDay(atoi(next.c_str()));
            }
            // parse month from file
            else if (isalpha(next[0]))
            {
               if (next == "JAN")
                  tempBirth.setMonth(1);
               else if (next == "FEB")
                  tempBirth.setMonth(2);
               else if (next == "MAR")
                  tempBirth.setMonth(3);
               else if (next == "APR")
                  tempBirth.setMonth(4);
               else if (next == "MAY")
                  tempBirth.setMonth(5);
               else if (next == "JUN")
                  tempBirth.setMonth(6);
               else if (next == "JUL")
                  tempBirth.setMonth(7);
               else if (next == "AUG")
                  tempBirth.setMonth(8);
               else if (next == "SEP")
                  tempBirth.setMonth(9);
               else if (next == "OCT")
                  tempBirth.setMonth(10);
               else if (next == "NOV")
                  tempBirth.setMonth(11);
               else if (next == "DEC")
                  tempBirth.setMonth(12);
               else if (next == "ABT")
                  tempBirth.setMonth(13);
            }
            // parse year from file
            else if (next.size() == 4 && isdigit(next[0]))
            {
               tempBirth.setYear(atoi(next.c_str()));
            }
            // if there are two years
            else if (next.size() == 9 && isdigit(next[0]))
            {
               string year = next.substr(0, 4);
               tempBirth.setYear(atoi(year.c_str()));
               
               string secYear = next.substr(5, 4);
               indi.setSecondYear(atoi(secYear.c_str()));
            }
            
            fin >> next;

            if (next.size() == 4 && isalpha(next[3]))
            {
               tempBirth.setDay(0);
               next = "2";
            }
         }
         while ( next != "2" && next != "1");

         // set birthday in Person object
         indi.setBirthDate(tempBirth);        
      }
   }
   
   return;
}

/*****************************************************************
 * parseFamily
 * find husband and wife and their child in the list using id and
 * build the family tree
 ******************************************************************/
void parseFamily(ifstream &fin, List < Person > &family,
                 BTree < Person > &familyTree, string &next)
{
   string id;
   int husId = 0;
   int wifeId = 0;
   int childId = 0;
   
   // find husband's ID
   while (next != "HUSB")
   {
      fin >> next;
      
      // if husband doesn't exist,
      // find wife
      if (next == "WIFE")
         break;
   }
   
   if (next == "HUSB")
   {
      fin >> next;
      
      id = next.substr(2);
      id.erase(id.find('@',1));
      
      husId = atoi(id.c_str());
   }
   
   // find wife's ID
   while ( next != "WIFE")
   {
      fin >> next;

      // if wife doesn't exist,
      // find child
      if (next == "CHIL")
         break;
   }
   
   if (next == "WIFE")
   {
      fin >> next;
      
      id = next.substr(2);
      id.erase(id.find('@',1));
      
      wifeId = atoi(id.c_str());
   }
   
   // find child's ID
   while (next != "CHIL")
   {
      fin >> next;
   }
   
   if (next == "CHIL")
   {
      fin >> next;
      
      id = next.substr(2);
      id.erase(id.find('@',1));
      
      childId = atoi(id.c_str());
   }
   
   // if child's id is 1, this will be the root of
   // family tree
   if (childId == 1)
   {
      familyTree.setData(family.idSearch(childId));
      familyTree.insertLeft(family.idSearch(husId));
      familyTree.insertRight(family.idSearch(wifeId));
   }
   else
   {
      // build the family tree.
      familyTree.buildTree(childId, husId, wifeId, family);
   }
   
   return;
}
