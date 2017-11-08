static uint32_t *paint_alloc(struct paint_info *info)
{
	unsigned nr = (info->nr_bits + 31) / 32;
	unsigned size = nr * sizeof(uint32_t);
	void *p;
	if (!info->slab_count || info->free + size > info->end) {
		info->slab_count++;
		REALLOC_ARRAY(info->slab, info->slab_count);
		info->free = xmalloc(COMMIT_SLAB_SIZE);
		info->slab[info->slab_count - 1] = info->free;
		info->end = info->free + COMMIT_SLAB_SIZE;
	}
	p = info->free;
	info->free += size;
	return p;
}