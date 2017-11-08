void sort_and_merge_range_set(struct range_set *rs)
{
	int i;
	int o = 0; /* output cursor */

	QSORT(rs->ranges, rs->nr, range_cmp);

	for (i = 0; i < rs->nr; i++) {
		if (rs->ranges[i].start == rs->ranges[i].end)
			continue;
		if (o > 0 && rs->ranges[i].start <= rs->ranges[o-1].end) {
			if (rs->ranges[o-1].end < rs->ranges[i].end)
				rs->ranges[o-1].end = rs->ranges[i].end;
		} else {
			rs->ranges[o].start = rs->ranges[i].start;
			rs->ranges[o].end = rs->ranges[i].end;
			o++;
		}
	}
	assert(o <= rs->nr);
	rs->nr = o;

	range_set_check_invariants(rs);
}