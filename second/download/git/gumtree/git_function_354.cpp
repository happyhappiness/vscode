static int parse_ws_error_highlight(struct diff_options *opt, const char *arg)
{
	const char *orig_arg = arg;
	unsigned val = 0;
	while (*arg) {
		if (parse_one_token(&arg, "none"))
			val = 0;
		else if (parse_one_token(&arg, "default"))
			val = WSEH_NEW;
		else if (parse_one_token(&arg, "all"))
			val = WSEH_NEW | WSEH_OLD | WSEH_CONTEXT;
		else if (parse_one_token(&arg, "new"))
			val |= WSEH_NEW;
		else if (parse_one_token(&arg, "old"))
			val |= WSEH_OLD;
		else if (parse_one_token(&arg, "context"))
			val |= WSEH_CONTEXT;
		else {
			error("unknown value after ws-error-highlight=%.*s",
			      (int)(arg - orig_arg), orig_arg);
			return 0;
		}
		if (*arg)
			arg++;
	}
	opt->ws_error_highlight = val;
	return 1;
}