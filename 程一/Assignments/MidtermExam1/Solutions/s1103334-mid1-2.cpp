// Huge integer division
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<cmath>
using std::log10;

// returns true if and only if the specified huge integer is zero
bool isZero(int hugeInt[], int size);

// returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int size1, int size2);

// --hugeInt
void decrement(int hugeInt[], int& size);

// multiplicand *= multiplier
void multiAssign(int multiplicand[], int multiplier[], int& multiplicandSize, int multiplierSize);

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
	int dividendSize, int divisorSize, int& quotientSize, int& remainderSize);

// product = multiplicand * multiplier * ( 10 ^ multiplierPos )
void multiplication(int multiplicand[], int multiplier, int product[],
	int multiplicandSize, int multiplierPos, int& productSize);

// minuend -= subtrahend
void subtraAssign(int minuend[], int subtrahend[], int& minuendSize, int subtrahendSize);

const int arraySize = 200;

int main()
{
	int t, a, b;
	while (cin >> t >> a >> b)
	{
		cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

		if (t == 1)
			cout << "is not an integer with less than 100 digits.\n";
		else if (a == b)
			cout << "1\n";
		else if (a < b)
			cout << "is not an integer with less than 100 digits.\n";
		else if (a % b != 0)
			cout << "is not an integer with less than 100 digits.\n";
		else if ((a - b) * static_cast<int>(log10(t)) > 95)
			cout << "is not an integer with less than 100 digits.\n";
		else
		{
			int dividend[arraySize] = {};
			int divisor[arraySize] = {};
			int quotient[arraySize] = {};
			int remainder[arraySize] = {};

			int dividendSize = 1;
			int divisorSize = 1;
			int quotientSize = 1;
			int remainderSize = 1;

			// put all digits of t into base
			int base[arraySize] = {};
			int baseSize = 0;
			for (int i = t; i > 0; i /= 10)
				base[baseSize++] = i % 10;

			// dividend = pow( t, a )
			dividend[0] = 1;
			for (int i = 0; i < a; ++i)
			{
				multiAssign(dividend, base, dividendSize, baseSize);
				if (dividendSize > arraySize)
					break;
			}

			if (dividendSize > arraySize)
				cout << "is not an integer with less than 100 digits.\n";
			else
			{
				// divisor = pow( t, b )
				divisor[0] = 1;
				for (int i = 0; i < b; ++i)
					multiAssign(divisor, base, divisorSize, baseSize);

				decrement(dividend, dividendSize); // --dividend
				decrement(divisor, divisorSize);   // --divisor

				division(dividend, divisor, quotient, remainder,
					dividendSize, divisorSize, quotientSize, remainderSize);

				// quotient is an integer with less than 100 digits
				if (quotientSize < 100 && isZero(remainder, remainderSize))
					for (int i = quotientSize - 1; i >= 0; i--)
						cout << quotient[i];
				else
					cout << "is not an integer with less than 100 digits.";
				cout << endl;
			}
		}
	}
}

// returns true if and only if the specified huge integer is zero
bool isZero(int hugeInt[], int size)
{
	for (int i = 0; i < size; i++)
		if (hugeInt[i] != 0)
			return false;
	return true;
}

// #33559337
// returns true if and only if hugeInt1 < hugeInt2
bool less(int hugeInt1[], int hugeInt2[], int size1, int size2)  
{
	int check = 0;
	if (size1 > size2)
		check = 0;
	else if (size1 < size2)
		check = 1;
	else
	{
		for (int i = size1 - 1; i >= 0; i--)
		{
			if (hugeInt1[i] < hugeInt2[i]) 
				return true;  //mod
			else if (hugeInt1[i] > hugeInt2[i]) //add
				return false; //add
		}
	}
	return check;
} 

//#33560286
// --hugeInt
void decrement(int hugeInt[], int& size)
{
	int i;
	hugeInt[0]--;
	for (i = 0; i < size; i++) //mod
		if (hugeInt[i] < 0)
		{
			hugeInt[i] += 10;
			hugeInt[i + 1] -= 1;
		}
	//for (i = size - 1; i > 0; i--)  //del
	//	if (hugeInt[i])  //del
	//		break; //del
	//size = i; //del
}
//# 26927805
// multiplicand *= multiplier
void multiAssign(int multiplicand[], int multiplier[], int& multiplicandSize, int multiplierSize)
{
	int productSize = multiplicandSize + multiplierSize;
	int product[arraySize] = {};//mod
	int i, j;

	//for (i = 0; i < productSize; i++) //del
	//	product[i] = 0; //del

	for (i = 0; i < multiplicandSize; i++)
		for (j = 0; j < multiplierSize; j++)
			product[i + j] += multiplicand[i] * multiplier[j];

	for (int i = 0; i < productSize; i++) //mod
	{
		if (product[i] >= 10)
		{
			product[i + 1] += (product[i] / 10);
			product[i] %= 10;
		}
	}

	//for (i = productSize - 1; i >= 0; i--) //del
	//	if (product[i]) //del
	//		break;//del
	//multiplicandSize = i;//del

	while (product[productSize - 1] == 0 && productSize > 1) //add
		productSize--; //add

	multiplicandSize = productSize; //add

	for (i = 0; i <= multiplicandSize; i++)
		multiplicand[i] = product[i];

	//delete[]product;  //del
}

// quotient = dividend / divisor; remainder = dividend % divisor
void division(int dividend[], int divisor[], int quotient[], int remainder[],
	int dividendSize, int divisorSize, int& quotientSize, int& remainderSize)
{
	int i;
	if (isZero(dividend, dividendSize))
	{
		quotient[0] = 0;
		quotientSize = 1;
		remainder[0] = 0;
		remainderSize = 1;
		return;
	}
	remainderSize = dividendSize;//add
	for (i = 0; i < dividendSize; i++)
		remainder[i] = dividend[i];

	if (less(dividend, divisor, dividendSize, divisorSize))
	{
		quotient[0] = 0;
		quotientSize = 1;
		return;
	}

	int n = dividendSize - divisorSize;
	// quotientSize = n; //del
	//buffer = divisor shift left by n positions
	int buffSize = dividendSize; //mod
	int buff[arraySize] = { 0 };

	//for (i = 0; i < n; i++) //del
	//	buff[i] = 0; //del

	//for (i = n; i < divisorSize; i++) //del
	//	buff[i] = divisor[i - n]; //del 
	for (int i = 0; i < divisorSize; i++) //add
		buff[i + n] = divisor[i];//add
	quotientSize = n;

	if (!(less(dividend, buff, dividendSize, buffSize)))
		quotientSize++;

	//for (i = 0; i < quotientSize; i++) //del
	//	quotient[i] = 0; //del

	int a = divisor[divisorSize - 1];
	int j = dividendSize - 1;

	for (i = dividendSize - divisorSize; i >= 0; i--, j--)
	{
		int b = 10 * remainder[j + 1] + remainder[j];
		if (a <= b)
		{
			quotient[i] = b / a;
			multiplication(divisor, quotient[i], buff, divisorSize, i, buffSize);
			while (less(remainder, buff, remainderSize, buffSize))
			{
				quotient[i]--;
				multiplication(divisor, quotient[i], buff, divisorSize, i, buffSize);
			}
			subtraAssign(remainder, buff, remainderSize, buffSize);
		}
	}
	//delete[]buff; //del

}

//#
// product = multiplicand * multiplier * ( 10 ^ multiplierPos )
void multiplication(int multiplicand[], int multiplier, int product[],
	int multiplicandSize, int multiplierPos, int& productSize)
{
	int i;
	productSize = multiplicandSize;//mod

	for (i = 0;i < productSize; i++) //mod
		product[i] = multiplicand[i]; //mod

	int mul[arraySize] = {}; //add
	int mulSize = multiplierPos + 1;//add
	mul[multiplierPos] = multiplier;//add

	while (mul[mulSize - 1] > 9)//add
	{
		mul[mulSize] = mul[mulSize - 1] / 10;//add
		mul[mulSize - 1] %= 10; //add
		mulSize++;//add
	}

	multiAssign(product, mul, productSize, mulSize);//mod

}

//#33559337 
// minuend -= subtrahend
void subtraAssign(int minuend[], int subtrahend[], int& minuendSize, int subtrahendSize)
{
	int difference[arraySize] = {};
	for (int i = 0; i < minuendSize; i++)//modify
	{
		if (minuend[i] > subtrahend[i])
		{
			difference[i] += minuend[i] - subtrahend[i];
		}
		else if (minuend[i] < subtrahend[i])
		{
			difference[i + 1] -= 1;
			difference[i] += minuend[i] - subtrahend[i] + 10;
		}
		else //mhy-add
			difference[i] = 0; //mhy-add
	}

	int zero = 0;
	for (int i = minuendSize-1; difference[i] != 0; i++) //mhy-modify
		zero++;
	minuendSize -= zero;
	for (int i = 0; i < minuendSize; i++)//modify
		minuend[i] = difference[i];
}
