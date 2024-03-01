#include<bits/stdc++.h>
using namespace std;
void Hoanvi(int &a,int &b)
{
	a = a+b;
	b = a-b;
	a = a-b;
}
int main()
{
	int a[50][50],m,n;
	cin>>m>>n;
	for (int i = 0; i < m; i++)
	 {
	 	for (int j = 0; j < n; j++)
	 	 {
	 	 	cin>>a[i][j];
		  }
	 }
	 int x;   cin>>x;
	 for (int i = 0; i < n - 1; i++)
	 {
	 	for (int j = 0; j < n; j++)
	 	 {
	 	    Hoanvi(a[x][i],a[x][j]);	
		  }
	 }
	for (int i = 0; i < m; i++)
	 {
	 	for (int j = 0; j < n; j++)
	 	 {
	 	 	cout<<a[i][j]<<"  ";
		  }
		  cout<<endl;
	 } 
}
