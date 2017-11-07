static int git_rerere_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "rerere.enabled"))
		rerere_enabled = git_config_bool(var, value);
	else if (!strcmp(var, "rerere.autoupdate"))
		rerere_autoupdate = git_config_bool(var, value);
	else
		return git_default_config(var, value, cb);
	return 0;
}