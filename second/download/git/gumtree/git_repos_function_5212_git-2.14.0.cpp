static int parse_wrap_args(const struct option *opt, const char *arg, int unset)
{
	struct shortlog *log = opt->value;

	log->wrap_lines = !unset;
	if (unset)
		return 0;
	if (!arg) {
		log->wrap = DEFAULT_WRAPLEN;
		log->in1 = DEFAULT_INDENT1;
		log->in2 = DEFAULT_INDENT2;
		return 0;
	}

	log->wrap = parse_uint(&arg, ',', DEFAULT_WRAPLEN);
	log->in1 = parse_uint(&arg, ',', DEFAULT_INDENT1);
	log->in2 = parse_uint(&arg, '\0', DEFAULT_INDENT2);
	if (log->wrap < 0 || log->in1 < 0 || log->in2 < 0)
		return error(wrap_arg_usage);
	if (log->wrap &&
	    ((log->in1 && log->wrap <= log->in1) ||
	     (log->in2 && log->wrap <= log->in2)))
		return error(wrap_arg_usage);
	return 0;
}