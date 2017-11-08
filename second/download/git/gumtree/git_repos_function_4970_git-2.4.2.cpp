static int opt_parse_reference(const struct option *opt, const char *arg, int unset)
{
	struct string_list *option_reference = opt->value;
	if (!arg)
		return -1;
	string_list_append(option_reference, arg);
	return 0;
}