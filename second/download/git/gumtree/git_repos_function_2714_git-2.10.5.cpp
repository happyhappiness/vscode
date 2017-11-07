struct stream_filter *get_stream_filter(const char *path, const unsigned char *sha1)
{
	struct conv_attrs ca;
	struct stream_filter *filter = NULL;

	convert_attrs(&ca, path);
	if (ca.drv && (ca.drv->smudge || ca.drv->clean))
		return NULL;

	if (ca.crlf_action == CRLF_AUTO || ca.crlf_action == CRLF_AUTO_CRLF)
		return NULL;

	if (ca.ident)
		filter = ident_filter(sha1);

	if (output_eol(ca.crlf_action) == EOL_CRLF)
		filter = cascade_filter(filter, lf_to_crlf_filter());
	else
		filter = cascade_filter(filter, &null_filter_singleton);

	return filter;
}