static int column_config(const char *var, const char *value, void *cb)
{
	return git_column_config(var, value, cb, &colopts);
}