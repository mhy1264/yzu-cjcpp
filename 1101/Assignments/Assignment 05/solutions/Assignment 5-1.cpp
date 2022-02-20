#include <iostream>
#include <cstring>
using namespace std;

// puts the binary representation of number into bits, and
// puts the the number of bits of the binary representation of number into numBits
// for example, if number is 10, then numBits == 4, and
// bits[ 3 ] = 1, bits[ 2 ] = 0, bits[ 1 ] = 1 and bits[ 0 ] = 0
void decimalToBinary(int number);

// prints bits[ last ], bits[ last - 1 ], . . ., bits[ 0 ]
void displayBinary(int last);

// returns bits[ 0 ] + bits[ 1 ] + . . . + bits[ last ],
// or equivalently the number of 1s in the binary representation of number,
// for example, if number is 10, then returns 2
int sumBits(int last);

int bits[32];
int numBits;

int main()
{
	int number;
	cin >> number;
	while (number > 0)
	{
		memset(bits, 0, sizeof(bits));
		numBits = 0;

		decimalToBinary(number);

		cout << "The parity of ";
		displayBinary(numBits - 1);

		cout << " is " << sumBits(numBits - 1) << " (mod 2).\n";

		cin >> number;
	}

	system("pause");
}

void decimalToBinary(int number)
{

	if (number)
	{

		if (number == 1)
		{
			bits[numBits] = 1;
			numBits++;
			number = 0;
		}
		else
		{
			bits[numBits] = number % 2;
			numBits++;
			number /= 2;
			return decimalToBinary(number);
		}
	}
	numBits++;

}

void displayBinary(int last)
{
	if (last != 1)
	{
		cout << bits[last - 1];
		return displayBinary(last - 1);
	}
	else
		cout << bits[0];

}

int sumBits(int last)
{
	int sum = 0;
	if (last)
		return bits[last] + sumBits(last - 1);
	else
		return bits[0];
}