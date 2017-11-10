static uint32_t *paint_alloc(struct paint_info *info)
{
	unsigned nr = (info->nr_bits + 31) / 32;
	unsigned size = nr * sizeof(uint32_t);
	void *p;
	if (!info->pool_count || size > info->end - info->free) {
		if (size > POOL_SIZE)
			die("BUG: pool size too small for %d in paint_alloc()",
			    size);
		info->pool_count++;
		REALLOC_ARRAY(info->pools, info->pool_count);
		info->free = xmalloc(POOL_SIZE);
		info->pools[info->pool_count - 1] = info->free;
		info->end = info->free + POOL_SIZE;
	}
	p = info->free;
	info->free += size;
	return p;
}