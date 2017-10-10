
#define OPT_SHORT 1
#define OPT_UNSET 2

int optbug(const struct option *opt, const char *reason)
{
	if (opt->long_name) {
		if (opt->short_name)
			return error("BUG: switch '%c' (--%s) %s",
				     opt->short_name, opt->long_name, reason);
		return error("BUG: option '%s' %s", opt->long_name, reason);
	}
	return error("BUG: switch '%c' %s", opt->short_name, reason);
}

static int get_arg(struct parse_opt_ctx_t *p, const struct option *opt,
		   int flags, const char **arg)
{
