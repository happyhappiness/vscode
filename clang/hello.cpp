#include <iostream>
#include <string>
using namespace std;

int main()
{
	int a, n;
	int sum = 0;
	cin >> sum;
	int i = 0;
	while(i < n)
	{
		// int a = 3;
		cin >> a;
		// sum positive value
		if(a > 0)
		{
			sum += a;
		}
	}
	cout << "sum is " << sum << endl;

	return 0;
}