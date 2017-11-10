static void diff_ranges_release(struct diff_ranges *diff)
{
	range_set_release(&diff->parent);
	range_set_release(&diff->target);
}