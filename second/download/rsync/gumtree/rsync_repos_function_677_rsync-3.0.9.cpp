void *
pool_alloc(alloc_pool_t p, size_t len, const char *bomb_msg)
{
	struct alloc_pool *pool = (struct alloc_pool *) p;
	if (!pool)
		return NULL;

	if (!len)
		len = pool->quantum;
	else if (pool->quantum > 1 && len % pool->quantum)
		len += pool->quantum - len % pool->quantum;

	if (len > pool->size)
		goto bomb_out;

	if (!pool->extents || len > pool->extents->free) {
		void	*start;
		size_t	free;
		size_t	bound;
		size_t	skew;
		size_t	asize;
		struct pool_extent *ext;

		free = pool->size;
		bound = 0;

		asize = pool->size;
		if (pool->flags & POOL_APPEND)
			asize += sizeof (struct pool_extent);

		if (!(start = new_array(char, asize)))
			goto bomb_out;

		if (pool->flags & POOL_CLEAR)
			memset(start, 0, free);

		if (pool->flags & POOL_APPEND)
			ext = PTR_ADD(start, free);
		else if (!(ext = new(struct pool_extent)))
			goto bomb_out;
		if (pool->flags & POOL_QALIGN && pool->quantum > 1
		    && (skew = (size_t)PTR_ADD(start, free) % pool->quantum)) {
			bound  += skew;
			free -= skew;
		}
		ext->start = start;
		ext->free = free;
		ext->bound = bound;
		ext->next = pool->extents;
		pool->extents = ext;

		pool->e_created++;
	}

	pool->n_allocated++;
	pool->b_allocated += len;

	pool->extents->free -= len;

	return PTR_ADD(pool->extents->start, pool->extents->free);

  bomb_out:
	if (pool->bomb)
		(*pool->bomb)(bomb_msg);
	return NULL;
}