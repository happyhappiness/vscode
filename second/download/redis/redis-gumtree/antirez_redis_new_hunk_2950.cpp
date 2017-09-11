#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define	JEMALLOC_MANGLE
#include "jemalloc_test.h"

int
main(void)
{
	size_t pagesize;
	void *p, *q;
	size_t sz, tsz;
	int r;

	fprintf(stderr, "Test begin\n");

	/* Get page size. */
	{
		long result = sysconf(_SC_PAGESIZE);
		assert(result != -1);
		pagesize = (size_t)result;
	}

	r = JEMALLOC_P(allocm)(&p, &sz, 42, 0);
	if (r != ALLOCM_SUCCESS) {
		fprintf(stderr, "Unexpected allocm() error\n");
