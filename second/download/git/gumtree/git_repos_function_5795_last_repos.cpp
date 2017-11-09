static int git_cat_file_config(const char *var, const char *value, void *cb)
{
	if (userdiff_config(var, value) < 0)
		return -1;

	return git_default_config(var, value, cb);
}