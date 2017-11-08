static int option_parse_exclude_from(const struct option *opt,
				     const char *arg, int unset)
{
	struct dir_struct *dir = opt->value;

	exc_given = 1;
	add_excludes_from_file(dir, arg);

	return 0;
}