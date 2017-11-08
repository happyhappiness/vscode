static int numbered_callback(const struct option *opt, const char *arg,
			     int unset)
{
	*(int *)opt->value = numbered_cmdline_opt = unset ? 0 : 1;
	if (unset)
		auto_number =  0;
	return 0;
}