/***********************************************************************
* Program:
*    Assignment 14, Binary Search Tree
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    Write a program to implement a binary search tree using binary tree
*    class. 
***********************************************************************/
#include "bst.h"

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
 * do level order traversal
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
            cout << " Parent = NULL! " << endl;
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

/**********************************************************************
 * default constructor
 * initialize root pointer
 **********************************************************************/
BST::BST()
{
   root = NULL;
}

/**********************************************************************
 * empty
 * check if tree is empty
 **********************************************************************/
int BST::empty(void)
{
   if (root == NULL)
      return 1;
   return 0;
}

/**********************************************************************
 * search
 * search the any item in binary tree
 **********************************************************************/
BTree* BST::search(int item)
{
   BTree* temp = root;
   
   while (temp != NULL)
   {
      if (temp->getData() == item)
         return temp;
      else if (temp->getData() > item)
         temp = temp->getLeftChild();
      else
         temp = temp->getRightChild();
   }
}

/**********************************************************************
 * insert
 * insert an item in binary tree
 **********************************************************************/
void BST::insert(int item)
{
   if (empty())
   {
      root = new BTree(item);
      return;
   }
   
   BTree* temp = root;

   while (temp != NULL)
   {
      if (temp->getData() > item)
      {
         if (temp->getLeftChild() == NULL)
         {
            temp->insertLeft(item);
            return;
         }
         temp = temp->getLeftChild();
      }
      else
      {
         if (temp->getRightChild() == NULL)
         {   
            temp->insertRight(item);
            return;
         }
         temp = temp->getRightChild();
      }
   }
}

/**********************************************************************
 * remove
 * remove an item in binary tree
 **********************************************************************/
void BST::remove(int item)
{
   // points to node to be deleted
   BTree* x = search(item);
   // points to parent of x and xSucc
   BTree* parent = x->getParent();
   
   if (x == NULL)
   {
      cout << "Item not in the BST\n";
      return;
   }

   // get left child and right child of x
   BTree* left = x->getLeftChild();
   BTree* right = x->getRightChild();

   // node has 2 children
   if (left != NULL && right != NULL)
   {
      // find x's inorder successor and its parent
      BTree* xSucc = right;
      parent = x;
      while ( xSucc->getLeftChild() != NULL) // descend left
      {
         parent = xSucc;
         xSucc = xSucc->getLeftChild();
      }

      // move contents of xSucc to x and change x
      // to point to successor, which will be removed
      x->setData(xSucc->getData());
      x = xSucc;
   }

   // node has 0 or 1 children
   BTree* subtree = x->getLeftChild(); // pointer to a subtree of x
      
   if (subtree == NULL)
      subtree = x->getRightChild();
   if (parent == NULL)  // root being deleted
      root = subtree;
   else if (parent->getLeftChild() == x) // left child of parent
      parent->setLeft(subtree);
   else // right child of parent                                   
      parent->setRight(subtree); 
   
   delete x;
}

/**********************************************************************
 * BSTInfix
 * do infix traversal
 **********************************************************************/
void BST::BSTInfix(void)
{
   if (root != NULL)
      root->infix();
}

