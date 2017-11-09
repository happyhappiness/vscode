static int hash_callback(const struct option *opt, const char *arg, int unset)
{
	hash_only = 1;
	/* Use full length SHA1 if no argument */
	if (!arg)
		return 0;
	return parse_opt_abbrev_cb(opt, arg, unset);
}