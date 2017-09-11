	p = q;
	sz = tsz;

	r = JEMALLOC_P(rallocm)(&q, &tsz, pagesize*4, 0, 0);
	if (r != ALLOCM_SUCCESS)
		fprintf(stderr, "Unexpected rallocm() error\n");
	if (tsz == sz) {
