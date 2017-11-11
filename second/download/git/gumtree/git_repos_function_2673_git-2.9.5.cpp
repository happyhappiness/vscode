static void cascade_free_fn(struct stream_filter *filter)
{
	struct cascade_filter *cas = (struct cascade_filter *)filter;
	free_stream_filter(cas->one);
	free_stream_filter(cas->two);
	free(filter);
}