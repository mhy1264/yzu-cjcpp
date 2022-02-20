#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n, i, j, sum,a,b;
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		sum = 0;
		cin >> a >> b;
		if(a>b)
		{
			int t=a;
			a=b;
			b=t;
		} 
		for (j = a ; j <= b ; j++)
			if (j%2==1)
				sum += j;
		cout << "Case " << i+1 << ": " << sum << endl;
	}
}
