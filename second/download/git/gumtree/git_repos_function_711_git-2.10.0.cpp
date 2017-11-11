int parse_opt_verbosity_cb(const struct option *opt, const char *arg,
			   int unset)
{
	int *target = opt->value;

	if (unset)
		/* --no-quiet, --no-verbose */
		*target = 0;
	else if (opt->short_name == 'v') {
		if (*target >= 0)
			(*target)++;
		else
			*target = 1;
	} else {
		if (*target <= 0)
			(*target)--;
		else
			*target = -1;
	}
	return 0;
}