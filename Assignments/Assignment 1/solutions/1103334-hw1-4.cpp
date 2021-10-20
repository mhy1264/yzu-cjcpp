// Determine whether three values represent the sides of a right triangle.
#include <iostream>
#include <bits/stdc++.h>
using namespace std; 

int main()
{
   int side1; // length of side 1
   int side2; // length of side 2
   int side3; // length of side 3

   // get values of three sides
   cout << "Enter side 1: ";
   cin >> side1;

   cout << "Enter side 2: ";
   cin >> side2;

   cout << "Enter side 3: ";
   cin >> side3;
   
   int arr[3]={side1*side1,side2*side2,side3*side3};
   
   sort(arr,arr+3);
   
   if(arr[0]+arr[1]==arr[2])
   {
   	cout<<"These are the sides of a right triangle."<<endl;
   }
   else
   {
   	cout<<"These do not form a right triangle."<<endl;
   }

   system( "pause" );
} // end main
