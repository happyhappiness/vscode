static int option_parse_strategy(const struct option *opt,
				 const char *name, int unset)
{
	if (unset)
		return 0;

	append_strategy(get_strategy(name));
	return 0;
}