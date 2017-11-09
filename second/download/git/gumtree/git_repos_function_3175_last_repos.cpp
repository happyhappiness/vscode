int is_null_stream_filter(struct stream_filter *filter)
{
	return filter == &null_filter_singleton;
}