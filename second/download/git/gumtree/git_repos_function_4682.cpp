static int option_parse_include(const struct option *opt,
				const char *arg, int unset)
{
	add_name_limit(arg, 0);
	has_include = 1;
	return 0;
}