alloc_pool_t
pool_create(size_t size, size_t quantum, void (*bomb)(const char *), int flags)
{
	struct alloc_pool	*pool;

	if (!(pool = new(struct alloc_pool)))
		return pool;
	memset(pool, 0, sizeof (struct alloc_pool));

	pool->size = size	/* round extent size to min alignment reqs */
	    ? (size + MINALIGN - 1) & ~(MINALIGN - 1)
	    : POOL_DEF_EXTENT;
	if (flags & POOL_INTERN) {
		pool->size -= sizeof (struct pool_extent);
		flags |= POOL_APPEND;
	}
	pool->quantum = quantum ? quantum : MINALIGN;
	pool->bomb = bomb;
	pool->flags = flags;

	return pool;
}