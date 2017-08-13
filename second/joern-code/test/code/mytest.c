#include <iostream>
#include <string>
using namespace std;
int d = hello();
int main(int a, int b)
{

	a = foo(); 
	e = myfunc(2, 4);
	f = func1(3) + func2(4) + 5 + 6;
	char g = 'c';
	h = 'd';
	m = "hello" + "\n %d world";
	n = MAX_INT;
	int c = 4;
	if(a + b > 3  && a + b % c / d < 5 && (c < e || c < abs(a)) && !a)
	{
		a = a + 1;
		if(a -b < 0 && c <= 5)
		{
			a = a + 1;
			c = a + b;
			printf("helo world%d, %d, %d",
					 a, b, c, d,e, f, g + h, m, n, foo3());
		}
	}
	return 0;
}

int myfunc(int a, int b)
{

	a = 1; 
	b = 2;
	int c = 4;
	c = a + b;
	c = 2;
	if(a + b > 3  && a + b < 5 || c < abs(a) && !a)
	{
		a = a + 1;
		if(a -b < 0 && c <= 5)
		{
			cout << "ni hao" << endl;
			cout << "hello world" << endl;
		}
	}
	return 0;
}
}