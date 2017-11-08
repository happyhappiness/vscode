void git_qsort(void *b, size_t n, size_t s,
	       int (*cmp)(const void *, const void *))
{
	const size_t size = st_mult(n, s);
	char buf[1024];

	if (size < sizeof(buf)) {
		/* The temporary array fits on the small on-stack buffer. */
		msort_with_tmp(b, n, s, cmp, buf);
	} else {
		/* It's somewhat large, so malloc it.  */
		char *tmp = xmalloc(size);
		msort_with_tmp(b, n, s, cmp, tmp);
		free(tmp);
	}
}