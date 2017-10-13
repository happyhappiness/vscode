int parse_opt_sort(const struct option *opt, const char *arg, int unset)
{
	int *sort = opt->value;
	int flags = 0;

	if (*arg == '-') {
		flags |= REVERSE_SORT;
		arg++;
	}
	if (starts_with(arg, "version:")) {
		*sort = VERCMP_SORT;
		arg += 8;
	} else if (starts_with(arg, "v:")) {
		*sort = VERCMP_SORT;
		arg += 2;
	} else
		*sort = STRCMP_SORT;
	if (strcmp(arg, "refname"))
		die(_("unsupported sort specification %s"), arg);
	*sort |= flags;
	return 0;
}