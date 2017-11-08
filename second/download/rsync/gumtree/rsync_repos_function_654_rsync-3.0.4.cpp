void
pool_free_old(alloc_pool_t p, void *addr)
{
	struct alloc_pool *pool = (struct alloc_pool *)p;
	struct pool_extent *cur, *prev, *next;

	if (!pool || !addr)
		return;

	for (prev = NULL, cur = pool->extents; cur; prev = cur, cur = cur->next) {
		if (addr >= cur->start
		    && addr < PTR_ADD(cur->start, pool->size))
			break;
	}
	if (!cur)
		return;

	if (addr == PTR_ADD(cur->start, cur->free)) {
		if (prev) {
			prev->next = NULL;
			next = cur;
		} else {
			size_t skew;

			/* The most recent live extent can just be reset. */
			if (pool->flags & POOL_CLEAR)
				memset(addr, 0, pool->size - cur->free);
			cur->free = pool->size;
			cur->bound = 0;
			if (pool->flags & POOL_QALIGN && pool->quantum > 1
			    && (skew = (size_t)PTR_ADD(cur->start, cur->free) % pool->quantum)) {
				cur->bound += skew;
				cur->free -= skew;
			}
			next = cur->next;
			cur->next = NULL;
		}
	} else {
		next = cur->next;
		cur->next = NULL;
	}

	while ((cur = next) != NULL) {
		next = cur->next;
		free(cur->start);
		if (!(pool->flags & POOL_APPEND))
			free(cur);
		pool->e_freed++;
	}
}