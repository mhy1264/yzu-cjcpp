// OrderDatabase.cpp
// Member-function definitions for class OrderDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "OrderDatabase.h" // OrderDatabase class definition

extern Date computeCurrentDate();
extern bool leapYear( int year );

// OrderDatabase default constructor initializes orders
OrderDatabase::OrderDatabase()
{
   loadOrderDetails();
}

// OrderDatabase destructor
OrderDatabase::~OrderDatabase()
{
   saveOrderDetails();
}

void OrderDatabase::loadOrderDetails()
{
    ifstream inFile("Orders.dat", ios::in | ios::binary);
    Order ord;
    Date today = computeCurrentDate();
    while (inFile.read(reinterpret_cast<char*>(&ord), sizeof(Order)))
    {
        if(ord.getDeliveryDate()<=computeCurrentDate())
            orders.push_back(ord);
    }
    inFile.close();

}

string OrderDatabase::generateOrderNumber() const
{
   srand( static_cast< unsigned int >( time( nullptr ) ) );

   string orderNumber;
   do
   {
      orderNumber.push_back( rand() % 26 + 'A' );
      for( int i = 1; i <= 9; i++ )
         orderNumber.push_back( rand() % 10 + '0' );
   } while( existOrder( orderNumber ) );

   return orderNumber;
}

void OrderDatabase::pushBack( Order &newOrder )
{
   orders.push_back( newOrder );
}

bool OrderDatabase::existOrders( string email ) const
{
   for( size_t i = 0; i < orders.size(); i++ )
      if( orders[ i ].getEmail() == email )
         return true;
   return false;
}

void OrderDatabase::displayOrders( string email, string name ) const
{
   cout << "\nYour order details:";
   for( size_t i = 0; i < orders.size(); i++ )
      if( orders[ i ].getEmail() == email )
      {
         cout << endl << setw( 9 ) << "Item Code" << setw( 44 ) << "Item" << setw( 7 ) << "Price"
              << setw( 10 ) << "Quantity" << setw( 10 ) << "Subtotal" << endl;
         orders[ i ].displayOrderDetails();
      }
}

void OrderDatabase::saveOrderDetails()
{

    ofstream outFile("Orders.dat", ios::out | ios::binary);

    for (int i = 0; i <orders.size(); i++)
    {
       Order temp = orders[i];
       outFile.write(reinterpret_cast<char*>(&temp), sizeof(Order));
    }
    outFile.close();

}

bool OrderDatabase::existOrder( string orderNumber ) const
{
   for( size_t i = 0; i < orders.size(); i++ )
      if( orders[ i ].getOrderNumber() == orderNumber )
         return true;
   return false;
}