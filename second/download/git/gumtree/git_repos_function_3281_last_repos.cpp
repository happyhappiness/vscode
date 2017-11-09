static void diff_ranges_filter_touched(struct diff_ranges *out,
				       struct diff_ranges *diff,
				       struct range_set *rs)
{
	int i, j = 0;

	assert(out->target.nr == 0);

	for (i = 0; i < diff->target.nr; i++) {
		while (diff->target.ranges[i].start > rs->ranges[j].end) {
			j++;
			if (j == rs->nr)
				return;
		}
		if (ranges_overlap(&diff->target.ranges[i], &rs->ranges[j])) {
			range_set_append(&out->parent,
					 diff->parent.ranges[i].start,
					 diff->parent.ranges[i].end);
			range_set_append(&out->target,
					 diff->target.ranges[i].start,
					 diff->target.ranges[i].end);
		}
	}
}