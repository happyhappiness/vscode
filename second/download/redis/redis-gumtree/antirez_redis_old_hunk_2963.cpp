	}
	sz = tsz;

	r = JEMALLOC_P(rallocm)(&q, &tsz, 16384, 0, ALLOCM_NO_MOVE);
	if (r != ALLOCM_SUCCESS)
		fprintf(stderr, "Unexpected rallocm() error\n");
	if (q != p)
