#include<iostream>
using namespace std;
int getnum(long long num)
{
	long long sum=0;
	while(num)
	{
		sum+=(num%10);
		num/=10;
	}
	return sum;
}

int main()
{
	long long num;
	while(cin>>num and num)
	{
		while(num>=10)
		{
			num=getnum(num);
		}
		cout<<num<<endl; 
	}
}


