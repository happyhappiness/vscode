int git_qsort_s(void *b, size_t n, size_t s,
		int (*cmp)(const void *, const void *, void *), void *ctx)
{
	const size_t size = st_mult(n, s);
	char buf[1024];

	if (!n)
		return 0;
	if (!b || !cmp)
		return -1;

	if (size < sizeof(buf)) {
		/* The temporary array fits on the small on-stack buffer. */
		msort_with_tmp(b, n, s, cmp, buf, ctx);
	} else {
		/* It's somewhat large, so malloc it.  */
		char *tmp = xmalloc(size);
		msort_with_tmp(b, n, s, cmp, tmp, ctx);
		free(tmp);
	}
	return 0;
}