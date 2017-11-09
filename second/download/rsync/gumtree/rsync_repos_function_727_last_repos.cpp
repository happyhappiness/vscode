alloc_pool_t
pool_create(size_t size, size_t quantum, void (*bomb)(const char *), int flags)
{
	struct alloc_pool *pool;

	if (!(pool = new0(struct alloc_pool)))
		return NULL;

	if ((MINALIGN & (MINALIGN - 1)) != 0) {
		if (bomb)
			(*bomb)("Compiler error: MINALIGN is not a power of 2\n");
		return NULL;
	}

	if (!size)
		size = POOL_DEF_EXTENT;
	if (!quantum)
		quantum = MINALIGN;

	if (flags & POOL_INTERN) {
		if (size <= sizeof (struct pool_extent))
			size = quantum;
		else
			size -= sizeof (struct pool_extent);
		flags |= POOL_PREPEND;
	}

	if (quantum <= 1)
		flags = (flags | POOL_NO_QALIGN) & ~POOL_QALIGN_P2;
	else if (!(flags & POOL_NO_QALIGN)) {
		if (size % quantum)
			size += quantum - size % quantum;
		/* If quantum is a power of 2, we'll avoid using modulus. */
		if (!(quantum & (quantum - 1)))
			flags |= POOL_QALIGN_P2;
	}

	pool->size = size;
	pool->quantum = quantum;
	pool->bomb = bomb;
	pool->flags = flags;

	return pool;
}