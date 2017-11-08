static void range_set_grow(struct range_set *rs, size_t extra)
{
	ALLOC_GROW(rs->ranges, rs->nr + extra, rs->alloc);
}