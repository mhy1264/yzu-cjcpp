#include<iostream>
using namespace std;
int main()
{
	int a,b,c,d,l;
	while(cin>>a>>b>>c>>d>>l and a+b+c+d+l)
	{
		int i;
		int sum=0;
		int each=0;
		for(i=0;i<=l;i++)
		{
			each=a*i*i+b*i+c;
			if(each%d==0)
				sum++;
		}
		cout<<sum<<endl;
	}
}
