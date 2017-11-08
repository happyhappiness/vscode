static struct line_log_data *line_log_data_copy_one(struct line_log_data *r)
{
	struct line_log_data *ret = xmalloc(sizeof(*ret));

	assert(r);
	line_log_data_init(ret);
	range_set_copy(&ret->ranges, &r->ranges);

	ret->path = xstrdup(r->path);

	return ret;
}