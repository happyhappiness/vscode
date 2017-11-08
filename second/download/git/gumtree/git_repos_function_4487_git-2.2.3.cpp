static int option_parse_exclude(const struct option *opt,
				const char *arg, int unset)
{
	struct string_list *exclude_list = opt->value;

	exc_given = 1;
	string_list_append(exclude_list, arg);

	return 0;
}