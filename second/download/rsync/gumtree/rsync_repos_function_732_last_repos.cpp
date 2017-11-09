void *
pool_boundary(alloc_pool_t p, size_t len)
{
	struct alloc_pool *pool = (struct alloc_pool *)p;
	struct pool_extent *cur;

	if (!pool || !pool->extents)
		return NULL;

	cur = pool->extents;

	if (cur->free < len) {
		cur->bound += cur->free;
		cur->free = 0;
	}

	return PTR_ADD(cur->start, cur->free);
}