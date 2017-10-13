tatic int parse_sort_string(const char *var, const char *arg, int *sort)
{
	int type = 0, flags = 0;

	if (skip_prefix(arg, "-", &arg))
		flags |= REVERSE_SORT;

	if (skip_prefix(arg, "version:", &arg) || skip_prefix(arg, "v:", &arg))
		type = VERCMP_SORT;
	else
		type = STRCMP_SORT;

	if (strcmp(arg, "refname")) {
		if (!var)
			return error(_("unsupported sort specification '%s'"), arg);
		else {
			warning(_("unsupported sort specification '%s' in variable '%s'"),
				var, arg);
			return -1;
		}
	}

	*sort = (type | flags);

	return 0;
}