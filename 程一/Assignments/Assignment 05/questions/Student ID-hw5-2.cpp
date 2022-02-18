#include <iostream>
using namespace std;

// returns a power p of 2 such that p <= number < 2 * p,
// for example, if number is in [ 8, 15 ], then returns 8
int computePower( int number );

// prints the binary representation of number,
// for example, if number is 10, then prints 1010
void displayBinary( int number, int power );

// returns the sum of all bits of the binary representation of number,
// or equivalently the number of 1s in the binary representation of number,
// for example, if number is 10, then returns 2
int sumBits( int number, int power );

int main()
{
   int number;
   cin >> number;
   while( number > 0 )
   {
      int power = computePower( number );

      cout << "The parity of ";
      displayBinary( number, power );

      cout << " is " << sumBits( number, power ) << " (mod 2).\n";

      cin >> number;
   }

   system( "pause" );
}

int computePower( int number )
{


}

void displayBinary( int number, int power )
{


}

int sumBits( int number, int power )
{


}