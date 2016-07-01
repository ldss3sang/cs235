/***********************************************************************
* Program:
*    Assignment 13, Binary Tree
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    Write a program to implement a binary tree ADT using pointers and
*    dynamic memory
***********************************************************************/
#include "tree.h"

/**********************************************************************
 * constructor
 * initialize the data and pointers.
 **********************************************************************/
BTree::BTree(int data)
{
   this->data = data;
   left = NULL;
   right = NULL;
   parent = NULL;
}

/**********************************************************************
 * destructor
 **********************************************************************/
BTree::~BTree(void)
{
   
}

/**********************************************************************
 * insertLeft
 * creates a new node and inserts node to left
 **********************************************************************/
void BTree::insertLeft(int item) 
{
   left = new BTree(item);
   left->parent = this;
}

/**********************************************************************
 * insertRight
 * creates a new node and inserts node to right
 **********************************************************************/
void BTree::insertRight(int item)   
{
   right = new BTree(item);
   right->parent = this;
}

/**********************************************************************
 * getLeftChild
 * return the ptr to the left child
 **********************************************************************/
BTree* BTree::getLeftChild(void)   
{
   return left;
}

/**********************************************************************
 * getRightChild
 * return the ptr to the right child
 **********************************************************************/
BTree* BTree::getRightChild(void) 
{
   return right;
}

/**********************************************************************
 * getParent
 * return parent
 **********************************************************************/
BTree* BTree::getParent(void)  
{
   return parent;
}

/**********************************************************************
 * getData
 * return data
 **********************************************************************/
int BTree::getData(void)
{
   return data;
}

/**********************************************************************
 * setData
 * set item into data
 **********************************************************************/
void BTree::setData(int item)
{
   data = item;
}

/**********************************************************************
 * setLeft
 * set left pointer and parent pointer
 **********************************************************************/
void BTree::setLeft(BTree* tree)     
{
   left = tree;
   if ( tree != NULL)
      tree->parent = this;
}

/**********************************************************************
 * setRight
 * set right pointer and parent pointer
 **********************************************************************/
void BTree::setRight(BTree* tree)
{
   right = tree;
   if (tree != NULL)
      tree->parent = this;
}

/**********************************************************************
 * infix
 * do infix traversal  
 **********************************************************************/  
void BTree::infix()
{
   if (left != NULL)
      left->infix();
   
   cout << data << " ";
   
   if (right != NULL)
      right->infix();
}

/**********************************************************************
 * prefix
 * do prefix traversal 
 **********************************************************************/
void BTree::prefix(void)
{
   cout << data << " ";

   if (left != NULL)
      left->prefix();
   if (right != NULL)
      right->prefix();
}

/**********************************************************************
 * postfix
 * do postfix traversal 
 **********************************************************************/
void BTree::postfix(void)
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
void BTree::level()
{
   const int MAX = 50;
   BTree *queue[MAX];
   BTree *temp;
   int front = 0;
   int back = 0;
   
   queue[ back++ ] = this;
   
   while (front != back)
   {
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         // visit
         cout.width(4);
         cout << temp->data << " ";
         if (temp->parent == NULL)
            cout << "      Parent = NULL! " << endl;
         else
            cout << " Parent = " << temp->parent->data << "   " << endl;
         // end Visit        
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;
         
      }
   }
}
