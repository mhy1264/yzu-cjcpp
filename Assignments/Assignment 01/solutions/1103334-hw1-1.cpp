#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
	int number; // integer read from user
	
	cout << "Enter an integer: "; // prompt
	cin >> number; // read integer from user
	
	cout<<"The integer "<<number<<" is ";
	
	if(number%2)
		cout<<"odd."<<endl;
	else
		cout<<"even."<<endl;
	

	system( "pause" );
} // end main
