#include <iostream>
using namespace std;

// prints the binary representation of number,
// for example, if number is 10, then prints 1010
void displayBinary(int number);

// returns the sum of all bits of the binary representation of number,
// or equivalently the number of 1s in the binary representation of number,
// for example, if number is 10, then returns 2
int sumBits(int number);

int main()
{
	int number;
	cin >> number;
	while (number > 0)
	{
		cout << "The parity of ";
		displayBinary(number);

		cout << " is " << sumBits(number) << " (mod 2).\n";

		cin >> number;
	}

	system("pause");
}

void displayBinary(int number)
{
	if (number > 1)
	{
		displayBinary(number / 2);      //簡單函式的遞迴，從遞迴的最裡面開始輸出，即可實現餘數的逆序輸出
	}
	cout << number % 2;
}

int sumBits(int number)
{
	if (number > 1)
	{
		return number%2 + sumBits(number/2);
	}
	else
		return number % 2;
}