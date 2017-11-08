void range_set_append(struct range_set *rs, long a, long b)
{
	assert(rs->nr == 0 || rs->ranges[rs->nr-1].end <= a);
	range_set_append_unsafe(rs, a, b);
}