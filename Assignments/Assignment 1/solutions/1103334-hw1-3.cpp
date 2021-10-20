// Determine whether a number is a palindrome.
#include <bits/stdc++.h>
using namespace std; 

int check(int number)
{
	int rev=0,num=number;
	while(number)
	{
		rev+=(number%10);
		rev*=10;
		number/=10;
	}
	rev/=10;
	return rev-num; 
}
int main()
{
	int number; // user input number

	cout << "Enter a 5-digit number: "; // prompt for a number
	cin >> number; // get number
	if(check(number))
	{
		cout<<number<<" is not a palindrome."<<endl;
	}
	else
	{
		cout<<number<<" is a palindrome!!!"<<endl;
	}



	system( "pause" );
} // end main
