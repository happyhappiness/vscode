static void line_log_data_init(struct line_log_data *r)
{
	memset(r, 0, sizeof(struct line_log_data));
	range_set_init(&r->ranges, 0);
}