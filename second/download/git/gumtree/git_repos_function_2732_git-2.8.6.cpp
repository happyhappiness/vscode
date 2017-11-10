static void range_set_check_invariants(struct range_set *rs)
{
	int i;

	if (!rs)
		return;

	if (rs->nr)
		assert(rs->ranges[0].start < rs->ranges[0].end);

	for (i = 1; i < rs->nr; i++) {
		assert(rs->ranges[i-1].end < rs->ranges[i].start);
		assert(rs->ranges[i].start < rs->ranges[i].end);
	}
}