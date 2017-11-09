static int context_callback(const struct option *opt, const char *arg,
			    int unset)
{
	struct grep_opt *grep_opt = opt->value;
	int value;
	const char *endp;

	if (unset) {
		grep_opt->pre_context = grep_opt->post_context = 0;
		return 0;
	}
	value = strtol(arg, (char **)&endp, 10);
	if (*endp) {
		return error(_("switch `%c' expects a numerical value"),
			     opt->short_name);
	}
	grep_opt->pre_context = grep_opt->post_context = value;
	return 0;
}