void
pool_free(alloc_pool_t p, size_t len, void *addr)
{
	struct alloc_pool *pool = (struct alloc_pool *) p;
	struct pool_extent	*cur;
	struct pool_extent	*prev;

	if (!pool)
		return;

	if (!len)
		len = pool->quantum;
	else if (pool->quantum > 1 && len % pool->quantum)
		len += pool->quantum - len % pool->quantum;

	if (!addr && pool->live) {
		pool->live->next = pool->free;
		pool->free = pool->live;
		pool->live = NULL;
		return;
	}
	pool->n_freed++;
	pool->b_freed += len;

	cur = pool->live;
	if (cur && addr >= cur->start
	    && addr < PTR_ADD(cur->start, pool->size)) {
		if (addr == PTR_ADD(cur->start, cur->free)) {
			if (pool->flags & POOL_CLEAR)
				memset(addr, 0, len);
			pool->b_freed += len;
		} else
			cur->bound += len;
		if (cur->free + cur->bound >= pool->size) {
			size_t sqew;

			cur->free = pool->size;
			cur->bound = 0;
			if (pool->flags & POOL_QALIGN && pool->quantum > 1
			    && (sqew = (size_t)PTR_ADD(cur->start, cur->free) % pool->quantum)) {
				cur->bound += sqew;
				cur->free -= sqew;
			}
		}
		return;
	}
	for (prev = NULL, cur = pool->free; cur; prev = cur, cur = cur->next) {
		if (addr >= cur->start
		    && addr < PTR_ADD(cur->start, pool->size))
			break;
	}
	if (!cur)
		return;

	if (prev) {
		prev->next = cur->next;
		cur->next = pool->free;
		pool->free = cur;
	}
	cur->bound += len;

	if (cur->free + cur->bound >= pool->size) {
		pool->free = cur->next;

		free(cur->start);
		if (!(pool->flags & POOL_APPEND))
			free(cur);
		pool->e_freed++;
	}
	return;
}