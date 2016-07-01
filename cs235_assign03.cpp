/***********************************************************************
* Program:
*    Assignment 03, Assembly
*    Brother Ercanbrack, CS235
* Author:
*    Sangseok Doe
* Summary: 
*    This program is an application of a stack. Read an infix expression
*    from a file and convert the infix expression to postfix expression
*    using a stack. After converting postfix, display the assembly language
*    equivalent of postfix expression using a stack.
*    My program also works with "harder.in" file.
***********************************************************************/
#include <fstream>
#include <string>
#include <cassert>
#include <cctype>
#include <iostream>
#include <cstdlib>

using namespace std;

/*********************************************************************
 * Stack
 * Stack class has member variables and member functions.
 ********************************************************************/
template < class T >
class Stack
{
   private:
      int myTop;                  // index of top of stack
      int maxSize;                // maximum size of stack  
      T *stackItems;            // pointer for dynamic array
   public:
      Stack(int size = 100);      // default constructor (stack size 100)
      Stack(const Stack < T > &aStack); // copy constructor 
      T top(void);              // returns the value of top item in the stack
      void push(T item);        // store item on the stack
      void pop(void);             // remove/delete top item off stack
      bool empty(void);           // is stack empty
      bool full(void);            // is stack full
      ~Stack();                   // default destructor
      // overloaded assignment operator
      Stack < T > &operator = (const Stack < T > &rtSide);
};

/***********************************************************
 * Default constructor
 * Initialize values (stack size 100)
 ************************************************************/
template < class T >
Stack < T > ::Stack(int size)
{
   myTop = -1;
   maxSize = size;
   stackItems = new T[size];
}

/**********************************************************
 * copy constructor
 * copy object
 ************************************************************/
template < class T >
Stack < T > ::Stack(const Stack < T > &aStack)
{
   myTop = aStack.myTop;
   maxSize = aStack.maxSize;
   stackItems = new T[maxSize];
   for (int i = 0; i < maxSize; i++)
      stackItems[i] = aStack.stackItems[i];
}

/***************************************************************
 * top
 * returns the value of top item in the stack
 *************************************************************/
template < class T >
T Stack < T > ::top(void)
{
   if (empty())
   {
      cout << "ERROR: Stack Empty\n";
      exit(1);
   }
   return stackItems[myTop];
}

/***********************************************************
 * push
 * store item on the stack
 **************************************************************/
template < class T >
void Stack < T > ::push(T item)   
{
   if (full())
   {
      cout << "ERROR: Stack Overflow\n";
      exit(1);
   }
   stackItems[ ++myTop ] = item;
}

/**************************************************************
 * pop
 * remove/delete top item off stack
 ****************************************************************/
template < class T >
void Stack < T > ::pop(void)
{
   if (empty())
   {
      cout << "ERROR: Stack Underflow\n";
      exit(1);
   }
   --myTop;
}

/***************************************************************
 * empty
 * check if stack is empty
 ****************************************************************/
template < class T >
bool Stack < T > ::empty(void)         
{
   return (myTop < 0);
}

/*******************************************************************
 * full
 * check if stack is full
 *******************************************************************/
template < class T >
bool Stack < T > ::full(void)          
{
   return (myTop == (maxSize - 1));
}

/************************************************************
 * destructor
 * free memories
 **********************************************************/
template < class T >
Stack < T > ::~Stack()                
{
   if (stackItems)
      delete [] stackItems;
}

/************************************************************
 * operator =
 * overloaded assignment operator
 ************************************************************/
template < class T >
Stack < T > &Stack < T > ::operator = (const Stack < T > &rtSide)
{
   if (this == &rtSide)
      return *this;
   else
   {
      delete [] stackItems;
      myTop = rtSide.myTop;
      maxSize = rtSide.maxSize;
      stackItems = new T[maxSize];
      
      for (int i = 0; i < maxSize; i++)
         stackItems[i] = rtSide.stackItems[i];
      return *this;
   }
}

string convertPost(string);
void assembly(string);
string opTemp(Stack < char > &operand);

/***********************************************************
 * main
 * create set objects and find the intersection, the union, and
 * the difference of the two sets.
 **************************************************************/
int main(int argc, char *argv[])
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

   string infix;
   
   ifstream fin(inFileName);

   while (fin >> infix)
   {
      assembly(convertPost(infix));
      cout << endl;
   }
   return 0;
}

/*******************************************************************
 * convertPost
 * Convert infix expression to postfix expression and return postfix
 * expression
 *******************************************************************/
string convertPost(string inFix)
{
   char token, 
        topToken;
   Stack < char > opStack;
   string postFix;
   const string BLANK = " ";
   
   for (int i = 0; i < inFix.length(); i++)
   {
      token = inFix[i];
      switch (token)
      {
         case ' ' : break;
         case '(' : opStack.push(token);
         break;
         case ')' : for (;;)
         {
            assert(!opStack.empty());
            topToken = opStack.top();
            opStack.pop();
            if (topToken == '(') 
               break;
            postFix.append(BLANK + topToken);
         }
         break;
         case '+' : case '-' :
         case '*' : case '/' : case '%' :
            for (;;)
            {
               if (opStack.empty() ||
                   opStack.top() == '(' ||
                   (token == '*' || token == '/' || token == '%') &&
                   (opStack.top() == '+' || opStack.top() == '-'))
               {
                  opStack.push(token);
                  break;
               }
               else
               {
                  topToken = opStack.top();
                  opStack.pop();
                  postFix.append(BLANK + topToken);
               }
            }
            break;
         default : //operand
            postFix.append(BLANK + token);
            for (;;)
            {
               if (!isalnum(inFix[i + 1])) 
                  break;
               i++;
               token = inFix[i];
               postFix.append(1, token);
            }
      }
   }
   for (;;)
   {
      if (opStack.empty()) break;
      topToken = opStack.top();
      opStack.pop();
      if (topToken != '(')
      {
         postFix.append(BLANK + topToken);
      }
      else
      {
         cout << " *** Error in infix expression ***\n";
         break;
      }
   }
   
   return postFix;
}   


/***********************************************************************
 * assembly
 * Convert postfix expression to assembly language and display assembly
 * language
 **********************************************************************/
void assembly(string postfix)
{
   Stack < char > operand;
   char tempNum = '0';
   string op;
   
   for (int i = 0; i < postfix.length(); i++)
   {
      
      if (isalpha(postfix[i]) || postfix[i] == ' ')
      {
         operand.push(postfix[i]);
      }
      else 
      {
         // stores right operand from a stack
         string temp1;
         temp1 = opTemp(operand);

         // store left operand from a stack
         string temp2;
         temp2 = opTemp(operand);         

         // display assembly language
         if (isalpha(temp2[0]))
            cout << "LD  " << temp2 << endl;
         else
            cout << "LD  TEMP" << temp2 << endl;
         switch (postfix[i])
         {
            case '+':
               cout << "AD  ";
               break;
            case '-':
               cout << "SB  ";
               break;
            case '/':
               cout << "DV  ";
               break;
            case '*':
               cout << "ML  ";
               break;
         }
         if (isalpha(temp1[0]))
            cout << temp1 << endl;
         else
            cout << "TEMP" << temp1 << endl;
         // count temporary variables
         tempNum++;
         operand.push(tempNum);
         cout << "ST  TEMP" << operand.top() << endl; 
      } 
   }
   return;
}

/***************************************************************
 * opTemp
 * parse operand from postfix expression and return each operand
 ***************************************************************/
string opTemp( Stack < char > &operand)
{
   string temp;
   string op;
   do
   {
      if (operand.top() != ' ')
         temp += operand.top();
      operand.pop();
      if (operand.empty())
         break;
   } while (operand.top() != ' ');

   //reverse variable name because of order of popping stack 
   for (int i = temp.length() - 1; i >= 0; i--)
      op += temp[i];
   return op;   
}
