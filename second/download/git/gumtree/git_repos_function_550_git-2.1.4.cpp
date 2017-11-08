int parse_opt_tertiary(const struct option *opt, const char *arg, int unset)
{
	int *target = opt->value;
	*target = unset ? 2 : 1;
	return 0;
}