static void lf_to_crlf_free_fn(struct stream_filter *filter)
{
	free(filter);
}