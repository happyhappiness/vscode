static int git_apply_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "apply.whitespace"))
		return git_config_string(&apply_default_whitespace, var, value);
	else if (!strcmp(var, "apply.ignorewhitespace"))
		return git_config_string(&apply_default_ignorewhitespace, var, value);
	return git_default_config(var, value, cb);
}