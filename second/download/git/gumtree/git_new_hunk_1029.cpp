	commit_list_insert(commit, opt->value);
	return 0;
}

int parse_opt_object_name(const struct option *opt, const char *arg, int unset)
{
	struct object_id oid;

	if (unset) {
		oid_array_clear(opt->value);
		return 0;
	}
	if (!arg)
		return -1;
	if (get_oid(arg, &oid))
		return error(_("malformed object name '%s'"), arg);
	oid_array_append(opt->value, &oid);
	return 0;
}

int parse_opt_tertiary(const struct option *opt, const char *arg, int unset)
{
	int *target = opt->value;
