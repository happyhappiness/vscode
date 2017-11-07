static int option_parse_u(const struct option *opt,
			      const char *arg, int unset)
{
	int *newfd = opt->value;

	state.refresh_cache = 1;
	if (*newfd < 0)
		*newfd = hold_locked_index(&lock_file, 1);
	return 0;
}