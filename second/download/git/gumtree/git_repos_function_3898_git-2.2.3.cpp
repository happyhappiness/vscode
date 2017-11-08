static int parse_opt_sort(const struct option *opt, const char *arg, int unset)
{
	int *sort = opt->value;

	return parse_sort_string(NULL, arg, sort);
}