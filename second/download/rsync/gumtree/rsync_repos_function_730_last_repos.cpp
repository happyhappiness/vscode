void
pool_free(alloc_pool_t p, size_t len, void *addr)
{
	struct alloc_pool *pool = (struct alloc_pool *)p;
	struct pool_extent *cur, *prev;

	if (!pool)
		return;

	if (!addr) {
		/* A NULL addr starts a fresh extent for new allocations. */
		if ((cur = pool->extents) != NULL && cur->free != pool->size) {
			cur->bound += cur->free;
			cur->free = 0;
		}
		return;
	}

	if (!len)
		len = pool->quantum;
	else if (pool->flags & POOL_QALIGN_P2) {
		if (len & (pool->quantum - 1))
			len += pool->quantum - (len & (pool->quantum - 1));
	} else if (!(pool->flags & POOL_NO_QALIGN)) {
		if (len % pool->quantum)
			len += pool->quantum - len % pool->quantum;
	}

	pool->n_freed++;
	pool->b_freed += len;

	for (prev = NULL, cur = pool->extents; cur; prev = cur, cur = cur->next) {
		if (addr >= cur->start
		    && addr < PTR_ADD(cur->start, pool->size))
			break;
	}
	if (!cur)
		return;

	if (!prev) {
		/* The "live" extent is kept ready for more allocations. */
		if (cur->free + cur->bound + len >= pool->size) {
			if (pool->flags & POOL_CLEAR) {
				memset(PTR_ADD(cur->start, cur->free), 0,
				       pool->size - cur->free);
			}
			cur->free = pool->size;
			cur->bound = 0;
		} else if (addr == PTR_ADD(cur->start, cur->free)) {
			if (pool->flags & POOL_CLEAR)
				memset(addr, 0, len);
			cur->free += len;
		} else
			cur->bound += len;
	} else {
		cur->bound += len;

		if (cur->free + cur->bound >= pool->size) {
			prev->next = cur->next;
			if (pool->flags & POOL_PREPEND)
				free(PTR_ADD(cur->start, -sizeof (struct pool_extent)));
			else {
				free(cur->start);
				free(cur);
			}
			pool->e_freed++;
		} else if (prev != pool->extents) {
			/* Move the extent to be the first non-live extent. */
			prev->next = cur->next;
			cur->next = pool->extents->next;
			pool->extents->next = cur;
		}
	}
}