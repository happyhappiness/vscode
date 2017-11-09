static int git_pull_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "rebase.autostash")) {
		config_autostash = git_config_bool(var, value);
		return 0;
	}
	return git_default_config(var, value, cb);
}