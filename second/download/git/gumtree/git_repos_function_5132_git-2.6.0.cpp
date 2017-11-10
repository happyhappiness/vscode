static int parse_refmap_arg(const struct option *opt, const char *arg, int unset)
{
	ALLOC_GROW(refmap_array, refmap_nr + 1, refmap_alloc);

	/*
	 * "git fetch --refmap='' origin foo"
	 * can be used to tell the command not to store anywhere
	 */
	if (*arg)
		refmap_array[refmap_nr++] = arg;
	return 0;
}