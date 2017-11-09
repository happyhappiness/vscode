void range_set_init(struct range_set *rs, size_t prealloc)
{
	rs->alloc = rs->nr = 0;
	rs->ranges = NULL;
	if (prealloc)
		range_set_grow(rs, prealloc);
}