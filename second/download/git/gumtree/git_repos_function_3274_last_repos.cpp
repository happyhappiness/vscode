static void line_log_data_clear(struct line_log_data *r)
{
	range_set_release(&r->ranges);
	if (r->pair)
		diff_free_filepair(r->pair);
}