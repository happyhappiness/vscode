struct stream_filter *get_stream_filter(const char *path, const unsigned char *sha1)
{
	struct conv_attrs ca;
	enum crlf_action crlf_action;
	struct stream_filter *filter = NULL;

	convert_attrs(&ca, path);

	if (ca.drv && (ca.drv->smudge || ca.drv->clean))
		return filter;

	if (ca.ident)
		filter = ident_filter(sha1);

	crlf_action = input_crlf_action(ca.crlf_action, ca.eol_attr);

	if ((crlf_action == CRLF_BINARY) || (crlf_action == CRLF_INPUT) ||
	    (crlf_action == CRLF_GUESS && auto_crlf == AUTO_CRLF_FALSE))
		filter = cascade_filter(filter, &null_filter_singleton);

	else if (output_eol(crlf_action) == EOL_CRLF &&
		 !(crlf_action == CRLF_AUTO || crlf_action == CRLF_GUESS))
		filter = cascade_filter(filter, lf_to_crlf_filter());

	return filter;
}