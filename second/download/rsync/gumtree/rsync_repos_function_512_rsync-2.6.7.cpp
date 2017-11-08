void
pool_destroy(alloc_pool_t p)
{
	struct alloc_pool *pool = (struct alloc_pool *) p;
	struct pool_extent	*cur, *next;

	if (!pool)
		return;

	if (pool->live) {
		cur = pool->live;
		free(cur->start);
		if (!(pool->flags & POOL_APPEND))
			free(cur);
	}
	for (cur = pool->free; cur; cur = next) {
		next = cur->next;
		free(cur->start);
		if (!(pool->flags & POOL_APPEND))
			free(cur);
	}
	free(pool);
}