int optbug(const struct option *opt, const char *reason)
{
	if (opt->long_name)
		return error("BUG: option '%s' %s", opt->long_name, reason);
	return error("BUG: switch '%c' %s", opt->short_name, reason);
}