/***********************************************************************
* Program:
*    Assignment 15, Huffman Code
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    write program to implement an huffman code using a binary tree. Read 
*    frequencies from a file and create the huffman binary tree and then
*    encode to huffman code(Left branches in the tree are 1 and right
*    branches are 0)
***********************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

/*********************************************************************
 * BTree class
 * class has frequency and letter and pointers of left and right child and
 * parent in node of tree.
 **********************************************************************/
class BTree
{
   private:
      int data;          // --- frequency stored in node of tree
      char letter;       // --- letter stored in node of tree
      BTree* left;       // --- pointer to left subtree
      BTree* right;      // --- pointer to right subtree
      BTree* parent;     // --- pointer to the parent node

   public:
      BTree(int = 0, char letter = '0');  
      ~BTree(void);
      void insertLeft(int item);     // insert node to left
      void insertRight(int item);    // insert node to right
      BTree* getLeftChild(void);     // return the ptr to the left child
      BTree* getRightChild(void);    // return the ptr to the right child
      BTree* getParent(void);        // return parent
      int getData(void);
      char getLetter(void);
      void setData(int item);
      void setLetter(char l);
      void setLeft(BTree* tree);    
      void setRight(BTree* tree);
      void infix(void);              // do infix traversal
      void prefix(void);             // do prefix traversal
      void postfix(void);            // do postfix traversal
      void level(void);              // do level order traversal
};

/**********************************************************************
 * constructor
 * initialize the data, letter, and pointers.
 **********************************************************************/
BTree::BTree(int data, char letter)
{
   this->data = data;
   this->letter = letter;
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
 * return the pointer to the left child
 **********************************************************************/
BTree* BTree::getLeftChild(void)   
{
   return left;
}

/**********************************************************************
 * getRightChild
 * return the pointer to the right child
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
 * getLetter
 * return letter
 **********************************************************************/
char BTree::getLetter(void)
{
   return letter;
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
 * setData
 * set item into data
 **********************************************************************/
void BTree::setLetter(char l)
{
   letter = l;
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

/***************************************************************************
 * compare 
 * compare the data items in first and last binary tree. 
 ***************************************************************************/
bool compare(BTree* first, BTree* last)
{
   if (first->getData() < last->getData())
      return true;
   return false;
}

/***************************************************************************
 * encodingHuffman
 * this function will encode letter to huffman code.(left: 1, right: 0)
 ***************************************************************************/
void encodingHuffman(BTree* tree, string arrayCode[], string code)
{
   if (tree->getLeftChild() == NULL && tree->getRightChild() == NULL)
   {
      arrayCode[(int)tree->getLetter() - 'a'] = code;
   }
   else
   {
      encodingHuffman(tree->getRightChild(), arrayCode, code + "0");
      encodingHuffman(tree->getLeftChild(), arrayCode, code + "1");
   }  
}

/***************************************************************************
 * main
 * get the data items from file and create binary tree of frequency and
 * encode to huffman code and display it.
 ***************************************************************************/
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

   int freq;
   char l = 'a';
   vector < BTree * > huffCode;

   // set a frequency and a letter in node
   // put node in array of huffCode
   while (fin >> freq)
   {
      BTree* newNode = new BTree(freq, l);
      huffCode.push_back(newNode);
      l++;
   }

   // sort by frequency
   sort(huffCode.begin(), huffCode.end(), compare);

   // make a huffman binary tree of frequency
   while (huffCode.size() > 1)
   {
      int sum = 0;
      BTree* smallest = huffCode[0];
      BTree* nextSmall = huffCode[1];
      
      huffCode.erase(huffCode.begin(), huffCode.begin() + 2);

      sum = smallest->getData() + nextSmall->getData();

      // create parent of smallest and nextSmall
      BTree* newNode = new BTree(sum, '0');
      newNode->setLeft(smallest);
      newNode->setRight(nextSmall);

      // put newNode in array and sort again.
      huffCode.push_back(newNode);
      sort(huffCode.begin(), huffCode.end(), compare);
   }
 
   string arrayCode[26];
   string code;

   // encoding to huffman code
   encodingHuffman(huffCode[0], arrayCode, code); 

   // display
   for (int i = 0; i < 26; i++)
   {
      cout << (char)('a' + i) << " = " << arrayCode[i] << endl;
   }
}
