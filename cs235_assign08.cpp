/***********************************************************************
* Program:
*    Assignment 08, Polynomials
*    Brother Ercanbrack, CS 235
* Author:
*    Sangseok Doe
* Summary: 
*    This program reads two polynomials from a file, displays them,
*    adds them together, evaluates the result for a given value of x and
*    displays the result.
***********************************************************************/

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/******************************************************************************
* Term
* a term class which has coefficient and exponent. 
******************************************************************************/
class Term
{
   private:
      float coeff;
      int expon;
 
   public:
      Term();                  // --- Creates empty Term
      Term(float c, int e);    // --- Creates Term object with coeff. c 
                               //and expon. e
      float getCoeff(void);    // --- returns coeff of term
      int getExpon(void);      // --- returns expon of term
      void setCoeff(float c);  // --- sets term's coeff. to c
      void setExpon(int c);    // --- sets term's expon to c
};

/***********************************************************************
* Poly
* Class containing an array of Terms and the functions to operate on them
***********************************************************************/
class Poly
{
   private:
      int numTerms;            // number of terms in polynomial
      int maxItems;            // array capacity
      Term *terms;             // dynamically allocated array of terms

   public:
      Poly();                  // creates empty polynomial
      Poly(const Poly &poly);  // copy constructor
      ~Poly();                 // destructor free dynamically allocate ptrs.
      void insertTerm(Term t); // inserts Term t into polynomial
      int getNumTerms(void);   // returns number of terms in array
      Term getTerm(int index); // returns term at index
      Poly& operator = (const Poly& rightSide);//overloaded assignment operator
      float operator () (float x);
};

ostream& operator << (ostream& outFile, Poly& op1);
istream& operator >> (istream& inFile, Poly& op1);
Poly operator + (Poly& op1, Poly& op2);


/***********************************************************************
* Main reads the file, outputs the polynomials, adds them together and
* displays the results.  Don't modify this function!!!!!
***********************************************************************/
int main(int argc, char* argv[])
{
   ifstream inFile;
   inFile.open(argv[argc - 1]);
   if (inFile.fail())
   {
      cout << "open file error " << argv[argc - 1] << endl;
      exit(1);
   }
   
   Poly f;
   Poly g;
   Poly p;

   int value (0); // value of x for evaluation
   inFile >> f;
   inFile >> g;

   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   // make copies of the polynomials
   Poly temp1(f);
   Poly temp2(g);

   // add polynomials f and g
   p = f + g;
   cout << "\nP(x) = (F + G)(x) = " << p << endl;

   // read in a value for X
   inFile >> value;

   // evaluate the polynomial
   cout << "P(" << value << ") = " << p(value) << endl << endl;

   // swap temp1 and temp2 - shouldn't change f & g
   Poly temp3(temp2);
   temp2 = temp1;
   temp1 = temp3;

   // Insert a new term 8x^6
   temp1.insertTerm(Term(8,6));

   cout << "temp1(x) is same as 8x^6 + G(x) or " << temp1 << endl;
   cout << "temp2(x) is same as F(x) or " << temp2 << endl;
   cout << "temp3(x) is same as G(x) or " << temp3 << endl << endl;

   cout << "Original functions were:" << endl;
   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   inFile.close();
   return 0;
}

/*****************************************************************************
*
*  Function: Term
*
*  Parameters - none
*  Return Value - none
*
*  Purpose - Constructor function for Term class.  Creates empty Term.
****************************************************************************/
Term::Term(void)
{
   coeff = 0.0;
   expon = -1;  // --- guarantees insert will occur
}

/*****************************************************************************
*
*  Function: Term
*
*  Parameters - a float that is the coefficient and a int that is the expon.
*  Return Value - None
*
*  Purpose: Creates a Term object set to coefficient and expon.
****************************************************************************/
Term::Term(float c, int e)
{
   coeff = c;
   expon = e;
}

/*****************************************************************************
*
*  Function: getCoeff
*
*  Parameters: None
*  Return Value - an integer representing coeff.
*
*  Purpose: Returns the coefficient data member of Term class
****************************************************************************/
float Term::getCoeff(void)
{
   return (coeff);
}

/***************************************************************************
*  Function: getExpon
*  Purpose: Returns the expon data member of Term class
*
*  Parameters - none
*  Return value - integer, representing expon.
***************************************************************************/
int Term::getExpon(void)
{
   return (expon);
}

/***************************************************************************
*  Function: setCoeff
*  Purpose: sets c to data member coeff in Term class
*
*  Parameters - float representing coeff
*  Return value - none
**************************************************************************/
void Term::setCoeff(float c)
{
   coeff = c;
}

/***************************************************************************
*  Function: setExpon
*  Purpose: sets e to data member expon in Term class
*
*  Parameters - int representing expon
*  Return value - none
**************************************************************************/
void Term::setExpon(int e)
{
   expon = e;
}

/***************************************************************************
*
*  Function: Poly
*  Purpose:  Poly class constructor to create an empty Poly object of 50 
*            term.
*
*  Parameters - none
*  Return value - none
**************************************************************************/
Poly::Poly()
{
   numTerms = 0;
   terms = new Term [50];
   maxItems = 50;
}

/********************************************
 * Destructor
 *********************************************/
Poly::~Poly()
{
   delete [] terms;
}

/*******************************************
 * copy constructor
 ********************************************/
Poly::Poly(const Poly &poly)
{
   numTerms = poly.numTerms;
   maxItems = poly.maxItems;
   terms = new Term [maxItems];
   
   for (int i = 0; i < numTerms; i++)
      terms[i] = poly.terms[i];
}

/*******************************************
 * overloaded Assignment operator
 ********************************************/
Poly& Poly::operator = (const Poly &rightSide)
{
   
   numTerms = rightSide.numTerms;
   maxItems = rightSide.maxItems;
   delete [] terms;
   terms = new Term [maxItems];
   
   for (int i = 0; i < numTerms; i++)
      terms[i] = rightSide.terms[i];
   
   return *this;
}

/***********************************************************************
* Inserts a term into a polynomial in the proper location.  If a term
* is inserted with a duplicate exponent, the terms are combined.  If any
* coefficient goes to zero that term is removed from the polynomial.
***********************************************************************/
void Poly::insertTerm(Term t)
{
   // if there is no term in poly
   // or the exponent of inserting term is less the exponent of last term
   // in poly, add inserting term in the end of poly.
   if ((numTerms == 0) ||  (t.getExpon() < terms[numTerms - 1].getExpon()))
   {
      terms[numTerms] = t;
      numTerms++;
   }
   else
   {
      // the case of not adding inserting term to the end of poly.
      for (int i = 0; i < numTerms; i++)
      {
         // if exponent of both is same, add both of coefficients 
         if (t.getExpon() == terms[i].getExpon())
         {
            float addCoeff = t.getCoeff() + terms[i].getCoeff();

            // if added coefficient is 0, remove the term.
            if (addCoeff != 0)
            {
               terms[i].setCoeff(addCoeff);
               terms[i].setExpon(t.getExpon());
            }
            else
            {
               for (int k = i; k < numTerms; k++)
                  terms[k] = terms[ k + 1 ];
               numTerms--;
            }
            i = numTerms;// this breaks for loop.
         }
         // if inserting term is the highest exponent,
         // every term move back and add inserting term
         // in the front of poly.
         else if (t.getExpon() > terms[i].getExpon())
         {
            Term inTemp = t;
            Term outTemp;
            numTerms++;
            
            for (int j = i; j < numTerms; j++)
            {
               outTemp = terms[j];
               terms[j] = inTemp;
               inTemp = outTemp;
            }
            i = numTerms;// this breaks for loop. 
         }
      }   
   }
}

/***********************************************************************
* Accessor function that returns the number of Terms in the array
***********************************************************************/
int Poly::getNumTerms()
{
   return (numTerms);
}

/***********************************************************************
* Accessor function that returns the Term at a given index
***********************************************************************/
Term Poly::getTerm(int index)
{
   return (terms[index]);
}

/***********************************************************************
* overloaded () operator that evaluates the polynomial for the value
* within the parentheses
***********************************************************************/
float Poly::operator () (float x)
{
   float eval;
   for (int i = 0; i < numTerms; i++)
      eval += terms[i].getCoeff() * pow(x,terms[i].getExpon());
   return eval;
}

/***********************************************************************
* overloaded + operator that combines two polynomials and returns the
* result as a polynomial
***********************************************************************/
Poly operator + (Poly& op1, Poly& op2)
{
   Poly add = op2;
   for (int i = 0; i < op1.getNumTerms(); i++)
      add.insertTerm(op1.getTerm(i));
   return add;
}

/***********************************************************************
* overloaded << operator that outputs the polynomial in the proper format
***********************************************************************/
ostream& operator << (ostream& outFile, Poly& op1)
{
   for ( int i = 0; i < op1.getNumTerms(); i++)
   {
      float c = op1.getTerm(i).getCoeff();
      int e = op1.getTerm(i).getExpon();

      // if coefficient is 1 or -1, do not display coefficient.
      // or if exponent is 0, only display coefficient.
      if ( abs((int)c) != 1 || e == 0)
      {
         // if the exponent of the term in a poly is the highest,
         // just display coefficient.
         if (i == 0)
            outFile << c;
         else
         {
            // after the highest exponent,display operator with space.
            if (c < 0)
               outFile << " - " << c * ( - 1 );
            else
               outFile << " + " << c;
         }
      }
      else
      {
         //if term is not the highest exponent,
         //display an operator(+ or -) with space.
         if (i != 0)
         {
            if (c < 0)
               outFile << " - ";
            else
               outFile << " + ";
         }
         //if term is the highest exponent
         //and the coefficient is negative,
         //display an operator without space.
         else if (c < 0)
            outFile << "-";
            
      }
      //if coefficient is 1 or -1,
      //display without coefficient.
      if (e > 1)
         outFile << "x^" << e;
      else if (e == 1)
         outFile << "x";
   }
   
   return outFile;
}

/***********************************************************************
* overloaded >> operator that reads an entire polynomial into an array
* of Terms in the proper order.
***********************************************************************/
istream& operator >> (istream& inFile, Poly& op1)
{
   int numTerm;
   
   inFile >> numTerm;

   for (int i = 0; i < numTerm; i++)
   {
      float coeff;
      int expon;
      inFile >> coeff >> expon;

      Term temp(coeff, expon);
      op1.insertTerm(temp);
   }

   return inFile;
}
