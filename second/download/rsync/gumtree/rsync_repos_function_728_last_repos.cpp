void
pool_destroy(alloc_pool_t p)
{
	struct alloc_pool *pool = (struct alloc_pool *) p;
	struct pool_extent *cur, *next;

	if (!pool)
		return;

	for (cur = pool->extents; cur; cur = next) {
		next = cur->next;
		if (pool->flags & POOL_PREPEND)
			free(PTR_ADD(cur->start, -sizeof (struct pool_extent)));
		else {
			free(cur->start);
			free(cur);
		}
	}

	free(pool);
}