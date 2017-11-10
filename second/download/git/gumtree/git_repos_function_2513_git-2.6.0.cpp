static struct stream_filter *lf_to_crlf_filter(void)
{
	struct lf_to_crlf_filter *lf_to_crlf = xcalloc(1, sizeof(*lf_to_crlf));

	lf_to_crlf->filter.vtbl = &lf_to_crlf_vtbl;
	return (struct stream_filter *)lf_to_crlf;
}