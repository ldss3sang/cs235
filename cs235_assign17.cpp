/***********************************************************************
* Program:
*    Assignment 17, Heap Sort
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    Write a program to implement the heap sort using the STL vector.  
*    create the functions using the algorithms of the heap sort, heapify,
*    and the percolate_down. 
***********************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/*********************************************************************
 * Heap
 * a class that has constructors, insert(insert items in heap array),
 * , sort(sort items using heap sort algorithm), and percolateDown and
 * heapify to help heap sort.
 *********************************************************************/
class Heap
{
   private:
      vector < int > heap;
      void percolateDown(int root, int end);
      void heapify(int end);
   
   public:
      Heap() { };
      Heap(vector < int > v) { heap = v; };
      void insert(int num) { heap.push_back(num); };
      vector < int > getHeap(void) { return heap; }; 
      void sort(void);
};

/********************************************************************
 * main
 * read the data from file and sort the items using heap sort algorithm
 ********************************************************************/
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

   int num;
   Heap h;

   // array starts with index 1.
   // not using index 0.
   h.insert(-1);

   // put items in heap array.
   while (fin >> num)
   {
      h.insert(num);
   }

   // sort items using heap sort. 
   h.sort();

   vector < int > heapDisplay = h.getHeap();

   // display
   for (int i = 1; i < heapDisplay.size(); i++)
   {
      cout << heapDisplay[i] << " ";
   }

   cout << endl;

   return 0;
}

/**********************************************************************
 * percolateDown
 * At each node, percolate down the item to its proper place in this part
 * of the subtree.
 ***********************************************************************/
void Heap::percolateDown(int root, int end)
{
   int child = root * 2; // location of left child

   while (child <= end)
   {
      // If child has two children and right child is the larger,
      if ((child < end) && (heap[child] < heap[child + 1]))
         child++; // make child the right child
      
      // Swap node and largest child if necessary, and
      // move down to the next subtree
      if (heap[root] < heap[child])
      {
         int temp = heap[root];
         heap[root] = heap[child];
         heap[child] = temp;
         root = child;
         child = child * 2;
      }
      else
         break;
   }
   
   return;
}

/**********************************************************************
 * heapify
 * Convert a complete binary tree into a heap
 ***********************************************************************/
void Heap::heapify(int end)
{
   for (int i = (end / 2); i >= 1; i--) // start at last nonleaf
   {
      percolateDown(i,end);
   }

   return;
}

/**********************************************************************
 * sort 
 * sort the items into ascending order using heap sort
 ***********************************************************************/
void Heap::sort()
{
   int end = heap.size() - 1;

   // convert a complete binary tree to a heap
   heapify(end);
   
   for (int i = end; i >= 2; i--)
   {
      // do a root-leaf exchange
      int temp = heap[1];
      heap[1] = heap[i];
      heap[i] = temp;

      // prune the leaf and percolate down
      percolateDown(1, i - 1);
   }

   return;
}
