#include <stdio.h>
int add(int i, int j)
{
	return i + j;
}
int mul(int i, int j)
{
	return i*j;
}
int eval(int i)
{
	return i > 10;
}
double eval(double i)
{
	return i > 10;
}
int main()
{
	int a = 10;
	int b = 10;
	int i = add(a, b);
	int j = mul(a, b);
	double k = 0;
	if(i * j < 100)
	{ 
		if(i + eval(i + j + k) + j)
			printf("%d * %d < 100\n", i, j);
		eval(k);
		// i = 5;
	}
	else
	{
		printf("%d * %d >= 100\n", i, j);
		// j = 5;
	}

	return 0;
}
