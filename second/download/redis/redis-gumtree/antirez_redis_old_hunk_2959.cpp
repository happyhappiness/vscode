#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	JEMALLOC_MANGLE
#include "jemalloc_test.h"

int
main(void)
{
	void *p, *q;
	size_t sz, tsz;
	int r;

	fprintf(stderr, "Test begin\n");

	r = JEMALLOC_P(allocm)(&p, &sz, 42, 0);
	if (r != ALLOCM_SUCCESS) {
		fprintf(stderr, "Unexpected allocm() error\n");
