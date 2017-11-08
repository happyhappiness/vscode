int git_color_default_config(const char *var, const char *value, void *cb)
{
	if (git_color_config(var, value, cb) < 0)
		return -1;

	return git_default_config(var, value, cb);
}