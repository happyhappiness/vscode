static int option_parse_whitespace(const struct option *opt,
				   const char *arg, int unset)
{
	const char **whitespace_option = opt->value;

	*whitespace_option = arg;
	parse_whitespace_option(arg);
	return 0;
}