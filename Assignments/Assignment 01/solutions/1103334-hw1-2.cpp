#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
	int number; // integer read from user

	cout << "Enter a five-digit integer: "; // prompt
	cin >> number; // read integer from user
   
	int arr[5],i=-1;
	while(number)
	{
   		arr[++i]=number%10;
   		number/=10;
	}
   	
   	for(i=4;i>0;i--)
   		cout<<arr[i]<<" ";

	cout<<arr[0]<<endl; 
   	system( "pause" );
} // end main
