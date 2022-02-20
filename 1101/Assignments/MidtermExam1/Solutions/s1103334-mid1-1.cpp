#include <iostream>
using namespace std;

// returns the maximum cycle-length over all integers
// between and including first and last
int maxCycleLength(int first, int last);

int cycleLength(int n); // returns the cycle-length of n

int main()
{
	int i, j;
	while (cin >> i >> j)
	{
		cout << i << ' ' << j << ' ';

		if (i > j)
		{
			int buf = i;
			i = j;
			j = buf;
		}
		cout << maxCycleLength(i, j) << endl;
	}
}

int maxCycleLength(int first, int last)
{
	if (first >= last)  //add
		return cycleLength(first); //add
	int max = maxCycleLength(first + 1, last);  //mod
	if (cycleLength(first) > max) //add
		max = cycleLength(first);//add
	return max; //add 

 
	
}

int cycleLength(int n)
{
	if (n == 1)
	{
		return 1;
	}
	else if (n % 2 == 0)
	{
		return 1 + cycleLength(n / 2);
	}
	else
	{
		return 1 + cycleLength(3 * n + 1);
	}
		
}