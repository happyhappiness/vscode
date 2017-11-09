static int ignore_removal_cb(const struct option *opt, const char *arg, int unset)
{
	/* if we are told to ignore, we are not adding removals */
	*(int *)opt->value = !unset ? 0 : 1;
	return 0;
}