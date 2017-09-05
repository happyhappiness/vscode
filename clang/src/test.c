#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{

	uint64_t a, b = NULL;
	scanf("%lld %lld", &a, &b);
	printf("64-bit division is %lld. \n", a / b);
	return 0;
}