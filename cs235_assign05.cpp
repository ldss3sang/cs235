/***********************************************************************
* Program:
*    Assignment 05, Stock
*    Brother Ercanbrack, cs235 
* Author:
*    Sangseok Doe
* Summary:
*    Create a program that calculate the profit when stock is sold and
*    display transactions of buying and selling stock.
***********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <deque>
#include <cmath>

using namespace std;

/*********************************************************************
 * Stock
 * a class has functions for selling and buying stock.
 *********************************************************************/
class Stock
{
   public:
      Stock();
      Stock(string trans, int numShares, double stockPrice);
   
      void setTrans(string sTrans);
      void setShares(int sShares);
      void setPrice(double sPrice);
      string getTrans();
      int getShares();
      double getPrice();
      void buy();
      double sell(deque < Stock > &market);
   
   private:
      string transaction;
      int shares;
      double price;
      double profit;
};

/**********************************************************************
 * default constructor
 * initialize member variables.
 *********************************************************************/
Stock::Stock()
{
   transaction = '\0';
   shares = 0;
   price = 0;
   profit = 0;
}

/********************************************************************
 * constructor
 * set variables.
 ********************************************************************/
Stock::Stock(string trans, int numShares, double stockPrice)
{
   transaction = trans;
   shares = numShares;
   price = stockPrice;
   profit = 0;
}

/********************************************************************
 * setTrans
 * set transaction.
 ********************************************************************/
void Stock::setTrans(string sTrans)
{
   transaction = sTrans;
}

/********************************************************************
 * setShares
 * set shares
 ********************************************************************/
void Stock::setShares(int sShares)
{
   shares = sShares;
}

/********************************************************************
 * setPrice
 * set price
 ********************************************************************/
void Stock::setPrice(double sPrice)
{
   price = sPrice;
}

/********************************************************************
 * getTrans
 * get transaction
 ********************************************************************/
string Stock::getTrans()
{
   return transaction;
}

/********************************************************************
 * getShares
 * get shares
 ********************************************************************/
int Stock::getShares()
{
   return shares;
}

/********************************************************************
 * getPrice
 * get price
 ********************************************************************/
double Stock::getPrice()
{
   return price;
}

/********************************************************************
 * buy
 * display buy transaction.
 ********************************************************************/
void Stock:: buy()
{
   cout << "Bought " << shares << " shares at $"
        << fixed << setprecision(2) << price << endl; 
}

/********************************************************************
 * sell
 * calculate profit and display sell transaction.
 ********************************************************************/
double Stock::sell(deque < Stock > &market)
{
   cout << "Sold " << shares << " shares at $" << price
        << " for a profit of $";

   Stock temp;

   temp = market.front();
   market.pop_front();

   //loop until selling shares less than stock shares in market.
   while ( shares > temp.shares)
   {
      profit += ((temp.shares * price) - (temp.shares * temp.price));
      shares = shares - temp.shares;
      temp = market.front();
      market.pop_front();
   }
   
   // check if selling shares is negative. 
   if (shares > 0)
   {
      profit += (shares * price) - (shares * temp.price);
      temp.setShares(temp.shares - shares);
      if (temp.shares > 0)
         market.push_front(temp); 
   }
   
   if (profit < 0)
      cout << "(" << abs(profit) << ")\n";
   else
      cout << profit << endl;
   
   return profit;
}

/********************************************************************
 * main
 * call functions and display result of selling and buying stock. 
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

   string transaction;
   int numShare = 0;
   double price = 0.0;
   double totalProfit = 0.0;
   deque < Stock > market;
      
   while (fin >> transaction >> numShare >> price)
   {
      Stock stock(transaction, numShare, price);
      
      if (transaction == "SELL")
      {
         totalProfit += stock.sell(market);
      }
      else
      {
         market.push_back(stock);
         stock.buy();
      }
   }

   cout << "\nTotal Profit: $" << totalProfit << endl << endl;

   cout << "Unsold Shares\n";

   while ( !market.empty())
   {
      cout << "   " << market.front().getShares() << " shares bought for $"
           << market.front().getPrice() << endl;
      market.pop_front();
   }
   
   return 0;
}

