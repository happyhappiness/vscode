void *
pool_alloc(alloc_pool_t p, size_t len, char *bomb)
{
	struct alloc_pool *pool = (struct alloc_pool *) p;
	if (!pool)
		return NULL;

	if (!len)
		len = pool->quantum;
	else if (pool->quantum > 1 && len % pool->quantum)
		len += pool->quantum - len % pool->quantum;

	if (len > pool->size)
		goto bomb;

	if (!pool->live || len > pool->live->free)
	{
		void	*start;
		size_t	free;
		size_t	bound;
		size_t	sqew;
		size_t	asize;

		if (pool->live)
		{
			pool->live->next = pool->free;
			pool->free = pool->live;
		}

		free = pool->size;
		bound = 0;

		asize = pool->size;
		if (pool->flags & POOL_APPEND)
			asize += sizeof (struct pool_extent);

		if (!(start = (void *) malloc(asize)))
			goto bomb;

		if (pool->flags & POOL_CLEAR)
			memset(start, 0, pool->size);

		if (pool->flags & POOL_APPEND)
		{
			pool->live = PTR_ADD(start, free);
		}
		else if (!(pool->live = (struct pool_extent *) malloc(sizeof (struct pool_extent))))
		{
			goto bomb;
		}
		if (pool->flags & POOL_QALIGN && pool->quantum > 1
		    && (sqew = (size_t)PTR_ADD(start, free) % pool->quantum))
		{
			bound  += sqew;
			free -= sqew;
		}
		pool->live->start = start;
		pool->live->free = free;
		pool->live->bound = bound;
		pool->live->next = NULL;

		pool->e_created++;
	}

	pool->n_allocated++;
	pool->b_allocated += len;

	pool->live->free -= len;

	return PTR_ADD(pool->live->start, pool->live->free);

bomb:
	if (pool->bomb)
		(*pool->bomb)(bomb);
	return NULL;
}