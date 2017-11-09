void *
pool_alloc(alloc_pool_t p, size_t len, const char *bomb_msg)
{
	struct alloc_pool *pool = (struct alloc_pool *) p;
	if (!pool)
		return NULL;

	if (!len)
		len = pool->quantum;
	else if (pool->flags & POOL_QALIGN_P2) {
		if (len & (pool->quantum - 1))
			len += pool->quantum - (len & (pool->quantum - 1));
	} else if (!(pool->flags & POOL_NO_QALIGN)) {
		if (len % pool->quantum)
			len += pool->quantum - len % pool->quantum;
	}

	if (len > pool->size)
		goto bomb_out;

	if (!pool->extents || len > pool->extents->free) {
		void *start;
		size_t asize;
		struct pool_extent *ext;

		asize = pool->size;
		if (pool->flags & POOL_PREPEND)
			asize += sizeof (struct pool_extent);

		if (!(start = new_array(char, asize)))
			goto bomb_out;

		if (pool->flags & POOL_CLEAR)
			memset(start, 0, asize);

		if (pool->flags & POOL_PREPEND) {
			ext = start;
			start = PTR_ADD(start, sizeof (struct pool_extent));
		} else if (!(ext = new(struct pool_extent)))
			goto bomb_out;
		ext->start = start;
		ext->free = pool->size;
		ext->bound = 0;
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