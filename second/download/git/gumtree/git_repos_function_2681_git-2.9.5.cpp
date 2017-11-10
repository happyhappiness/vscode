void free_stream_filter(struct stream_filter *filter)
{
	filter->vtbl->free(filter);
}