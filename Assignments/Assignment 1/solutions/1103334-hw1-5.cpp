#include <iostream>
using namespace std;
int leap(int year)
{
	if( year%400==0 or ( year%4==0 and year%100!=0 ) )
		return 1;
	else
		return 0;
} 
int main()
{
	int year;
	cout << "Enter a year ( 1583-3000 ): ";
	cin >> year;
   
	if(leap(year))
	{
		cout<<"Year "<<year<<" is a leap year"<<endl;
	}
	else
	{
		cout<<"Year "<<year<<" is a common year"<<endl;
	}

	system( "pause" );
}
