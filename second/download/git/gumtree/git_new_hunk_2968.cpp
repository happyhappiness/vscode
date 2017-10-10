		   const struct option *options)
{
	fprintf(stderr, "%s\n\n", msg);
	usage_with_options(usagestr, options);
}

#undef opterror
int opterror(const struct option *opt, const char *reason, int flags)
{
	if (flags & OPT_SHORT)
		return error("switch `%c' %s", opt->short_name, reason);
	if (flags & OPT_UNSET)
