static int keep_callback(const struct option *opt, const char *arg, int unset)
{
	((struct rev_info *)opt->value)->total = -1;
	keep_subject = 1;
	return 0;
}