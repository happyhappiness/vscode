static int option_parse_exclude(const struct option *opt,
				const char *arg, int unset)
{
	add_name_limit(arg, 1);
	return 0;
}