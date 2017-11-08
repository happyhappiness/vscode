const char *diff_line_prefix(struct diff_options *opt)
{
	struct strbuf *msgbuf;
	if (!opt->output_prefix)
		return "";

	msgbuf = opt->output_prefix(opt, opt->output_prefix_data);
	return msgbuf->buf;
}