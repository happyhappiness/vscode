// #include <stdio.h>
// int add(int i, int j)
// {
// 	return i + j;
// }
// int mul(int i, int j)
// {
// 	return i*j;
// }
// int eval(int& i)
// {
// 	return i > 10;
// }
// double eval(double i)
// {
// 	return i > 10;
// }
// int ptr(int* i)
// {
// 	return *i;
// }
int main()
{
	int a = 10;
	int b = 10;
	int *i = add(a, b);
	int j = mul(a, b);
	int* m;
	int n;
	double k = 0;
	if(i * j < 100)
	{ 
		if(i + eval(i + j + k) + j) { i = ptr(m);
			printf("%d * %d < 100, m:%p, n:%d, eval:%d.\n", *i, j
				, m, n, eval(&i));
			j = eval(n);
		}
		eval(k);
		// i = 5;
	}
	else
	{
		printf("%d * %d >= 100\n", i, j);
		// j = 5;
	}

	switch(i)
	{
	case 1:
		printf("hello");
	case 2:
		{
			printf("nihao");
			break;
		}
	}

	for(i = 0; i < n; i++)
	{
		printf("for");
	}
	return 0;
}
