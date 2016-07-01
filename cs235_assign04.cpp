/***********************************************************************
* Program:
*    Assignment 04, Airport Simulation
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    create a program that simulate airport runway using queue class.
*    airport has one runway. This program needs two queues, called landing
*    and takeoff. It displays the result of simulation.
***********************************************************************/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <math.h>
#include <time.h>

using namespace std;

#define MAXQUEUE 5

/********************************************************************
 * Random
 * a class that generate random numbers.
 ********************************************************************/
class Random
{
   public:
      Random();

  /* --- Get next Poisson random --- */
      int poissonRandom(double expected);

};

/***********************************************************************
 * Default Constructor
 * initialize class
 ***********************************************************************/
Random::Random()
{
   // srand((int)time(NULL));   // variable seed for real simulation
   srand(2500);                 // fixed seed for debug and grading
}

/******************************************************************
 * poissonRandom
 * generate random numbers using poisson
 *******************************************************************/
int Random::poissonRandom(double expected)
{
   int n = 0;
   double limit;
   double x;
   
   limit = exp(-expected);
   x = rand() / ((double)RAND_MAX + 1);
   while (x > limit)
   {
      n++;
      x *= rand() / ((double)RAND_MAX + 1);
   }
   return n;
}

/****************************************************************
 * Queue
 * a class has member variables and member functions for queue 
 ****************************************************************/
template < class T >
class Queue
{
   private:
      int front;                  // --- index of front of queue
      int back;                   // --- index of back of queue
      int maxSize;                // --- max storage capacity of array
      int numItems;               // --- number of items currently in queue
      T *queueItems;              // --- array containing queue items
  
   public:
      Queue(int = 5);             // --- constructor
      Queue(const Queue &aQueue); //  copy constructor
      ~Queue(void);               // --- destructor
      void insert(T item);        // --- insert item into back of queue
      T remove(void);         // --- remove item from front of queue
      int empty(void);        // --- returns 1 if queue is empty, 0 otherwise
      int full(void);         // --- returns 1 if queue is full, 0 otherwise
      Queue < T > &operator = (const Queue &rtSide); // overloaded assignment operator
      int getNumItems();          // --- return number of items in queue
};

/**********************************************************************
 * default constructor
 * initialize variables.
 **********************************************************************/
template < class T >
Queue < T > ::Queue(int s)    
{
   if (s > MAXQUEUE)
   {
      maxSize = MAXQUEUE;
      cout << "Error: queue size too big, setting to " << MAXQUEUE << endl;
   }
   maxSize = s > 0 ? s : 100;
   numItems = 0;
   back = front = maxSize - 1;
   queueItems = new T[maxSize];
}

/**********************************************************************
 * destructor
 * make memories free.
 **********************************************************************/
template < class T >
Queue < T > ::~Queue(void)
{
   delete [] queueItems;
}

/***********************************************************************
 * Queue Copy Constructor
 * copy object.
 ***********************************************************************/
template < class T >
Queue < T > ::Queue(const Queue &aQueue)
{
   maxSize = aQueue.maxSize;
   numItems = aQueue.numItems;
   front = aQueue.front;
   back = aQueue.back;
   queueItems = new T[maxSize];
   for (int i = 0; i < numItems; i++)
   {
      queueItems[i] = aQueue.queueItems[i];
   }
}

/*******************************************************************
 * Overloaded assignment operator.
 * make overloaded assignment operator.
 ******************************************************************/
template < class T >
Queue < T > &Queue < T > ::operator = (const Queue &rtSide)
{
   if (this != &rtSide)
   {
   
      if ( maxSize != rtSide.maxSize)
      {
         delete [] queueItems;
         queueItems = new T[rtSide.maxSize];
      }
   
      for (int i = 0; i < rtSide.numItems; i++)
      {
         queueItems[i] = rtSide.queueItems[i];
      }
      maxSize = rtSide.maxSize;   //max size of queue
      numItems = rtSide.numItems; //number of items in queue
      back = rtSide.back;
      front = rtSide.front;
   }
   return *this;
}


/**********************************************************************
 * empty
 * returns true if queue is empty
 **********************************************************************/
template < class T >
int Queue < T > ::empty(void)
{
   return (numItems == 0);
}

/**********************************************************************
 * full
 * returns true if queue is full
 **********************************************************************/
template < class T >
int Queue < T > ::full(void)
{
   return (numItems == maxSize);
}

/**********************************************************************
 * insert
 * inserts item into back of queue, then increments number of items
 * in queue
 **********************************************************************/
template < class T >
void Queue < T > ::insert(T item)
{
   // --- check for overflow
   if (full())
   {
      cout << "Queue overflow" << endl;
      exit(1);
   }
   queueItems[back] = item;
   back = (back + 1) % maxSize;
   numItems++;
}

/**********************************************************************
 * remove
 * removes item from front of queue, then decrements number of items
 * in queue
 **********************************************************************/
template < class T >
T Queue < T > ::remove(void)
{
   T temp;
   
   if (empty())
   {
      cout << "queue underflow" << endl;
      exit(1);
   }
   temp = queueItems[front];
   front = (front + 1) % maxSize;
   numItems--;
   return (temp);
   
}

/*****************************************************************
 * getNumItems
 * get number of items in queue.
 ******************************************************************/
template < class T >
int Queue < T > ::getNumItems()
{
   return numItems;
}

/*****************************************************************
 * Plane
 * a class has id and time for plane.
 ******************************************************************/
class Plane
{
   public:
      Plane() {};
      int getId() { return id; };
      int getTime() { return time; };
      void setId(int sId) { id = sId;};
      void setTime(int sTime) { time = sTime; };
    
   private:
      int id;
      int time;
};

/*****************************************************************
 * Runway
 * a class has functions and variables for airport simulation.
 ******************************************************************/
class Runway
{
   public:
      Runway();
      // run simulation. 
      void simulation();
      void result();
   
   private:
      Queue < Plane > landing;
      Queue < Plane > takeoff;
      int endTime;
      int curTime;
      double expectArrival;
      double expectTakeoff;
      int idleTime;
      int landingWait;
      int takeoffWait;
      int nPlanes;
      int nLanding;
      int nTakeoff;
      int nRefuse;
      Plane* newPlane(Plane& p);
};

/*********************************************************************
 * default constructor
 * it prompts endTime, expectArrival, and expectTakeoff for user and
 * initialize member variables.
 *********************************************************************/
Runway::Runway()
{
   cout << "Units of time the simulation will run: ";
   cin >> endTime;
   cout << "Expected number of arrivals per time unit: ";
   cin >> expectArrival;
   cout << "Expected number of take offs per time unit: ";
   cin >> expectTakeoff;

   idleTime = 0;
   landingWait = 0;
   takeoffWait = 0;
   nPlanes = 0;
   nLanding = 0;
   nTakeoff = 0;
   nRefuse = 0;
}

/******************************************************************
 * simulation
 * run airport simulation.
 *****************************************************************/
void Runway::simulation()
{
   Random randNum;
   Plane p;

   int wait;

   for (curTime = 1; curTime <= endTime; curTime++)
   {
      int randnumber1 = randNum.poissonRandom(expectArrival);
      for (int i = 0; i < randnumber1; i++)
      {
         p = *newPlane(p);
         if (landing.full())
            nRefuse++;
         else
            landing.insert(p);
      }
      int randnumber2 = randNum.poissonRandom(expectTakeoff);
      for (int i = 0; i < randnumber2; i++)
      {
         p = *newPlane(p);
         if (takeoff.full())
            nRefuse++;
         else
            takeoff.insert(p);
      }
      if (!landing.empty())
      {
         p = landing.remove();
         nLanding++;
         wait = curTime - p.getTime();
         landingWait += wait;
      }
      else if (!takeoff.empty())
      {
         p = takeoff.remove();
         nTakeoff++;
         wait = curTime - p.getTime();
         takeoffWait += wait;
      }
      else
      {
         idleTime++;
      }
   }
   result();
}

/************************************************************
 * newPlane
 * create new airplane.
 ************************************************************/
Plane* Runway::newPlane(Plane& p)
{
   nPlanes++;
   p.setId(nPlanes);
   p.setTime(curTime);

   return &p;   
}

/******************************************************************
 * result
 * show the result of airport simulation
 ******************************************************************/
void Runway::result()
{
   cout << "\nTotal number of planes processed: "
        << nPlanes << endl;
   cout << "Number of planes landed: "
        << nLanding << endl;
   cout << "Number of planes taken off: "
        << nTakeoff << endl;
   cout << "Number left ready to land: "
        << landing.getNumItems() << endl;
   cout << "Number left ready to take off: "
        << takeoff.getNumItems() << endl;
   cout << "Number of planes refused use: "
        << nRefuse << endl;
   cout << fixed;
   cout << "Percentage of time runway idle: "
        << setprecision(2) << ((double)idleTime / endTime) * 100.0 << "%\n";
   cout << "Average wait time to land: "
        << setprecision(2) << (double)landingWait / nLanding << endl;
   cout << "Average wait time to take off: "
        << setprecision(2) << (double)takeoffWait / nTakeoff << endl;
}

/******************************************************************
 * main
 * create a object and call simulation member function.
 ****************************************************************/
int main()
{
   Runway airport;

   airport.simulation();

   return 0;
}

