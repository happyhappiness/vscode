static void diff_ranges_init(struct diff_ranges *diff)
{
	range_set_init(&diff->parent, 0);
	range_set_init(&diff->target, 0);
}