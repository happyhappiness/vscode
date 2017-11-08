static int git_tag_config(const char *var, const char *value, void *cb)
{
	int status;

	if (!strcmp(var, "tag.sort")) {
		if (!value)
			return config_error_nonbool(var);
		parse_sort_string(var, value, &tag_sort);
		return 0;
	}

	status = git_gpg_config(var, value, cb);
	if (status)
		return status;
	if (starts_with(var, "column."))
		return git_column_config(var, value, "tag", &colopts);
	return git_default_config(var, value, cb);
}