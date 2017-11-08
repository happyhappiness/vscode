void range_set_append_unsafe(struct range_set *rs, long a, long b)
{
	assert(a <= b);
	range_set_grow(rs, 1);
	rs->ranges[rs->nr].start = a;
	rs->ranges[rs->nr].end = b;
	rs->nr++;
}