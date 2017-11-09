int
pool_stats(alloc_pool_t p, int fd, int summarize)
{
	struct alloc_pool *pool = (struct alloc_pool *) p;
	struct pool_extent *cur;
	char buf[BUFSIZ];
	int ret = 0;

	if (!pool)
		return ret;

	FDPRINT("  Extent size:       %12ld\n",	(long)	pool->size);
	FDPRINT("  Alloc quantum:     %12ld\n",	(long)	pool->quantum);
	FDPRINT("  Extents created:   %12ld\n",		pool->e_created);
	FDPRINT("  Extents freed:     %12ld\n",		pool->e_freed);
	FDPRINT("  Alloc count:       %12.0f\n", (double) pool->n_allocated);
	FDPRINT("  Free Count:        %12.0f\n", (double) pool->n_freed);
	FDPRINT("  Bytes allocated:   %12.0f\n", (double) pool->b_allocated);
	FDPRINT("  Bytes freed:       %12.0f\n", (double) pool->b_freed);

	if (summarize)
		return ret;

	if (!pool->extents)
		return ret;

	if (write(fd, "\n", 1) != 1)
		ret = -1;

	for (cur = pool->extents; cur; cur = cur->next)
		FDEXTSTAT(cur);

	return ret;
}