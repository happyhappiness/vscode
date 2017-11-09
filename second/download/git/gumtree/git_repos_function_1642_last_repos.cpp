static int parse_ws_error_highlight_opt(struct diff_options *opt, const char *arg)
{
	int val = parse_ws_error_highlight(arg);

	if (val < 0) {
		error("unknown value after ws-error-highlight=%.*s",
		      -1 - val, arg);
		return 0;
	}
	opt->ws_error_highlight = val;
	return 1;
}