static int git_tag_config(const char *var, const char *value, void *cb)
{
	int status = git_gpg_config(var, value, cb);
	if (status)
		return status;
	if (starts_with(var, "column."))
		return git_column_config(var, value, "tag", &colopts);
	return git_default_config(var, value, cb);
}