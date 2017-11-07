static int git_unknown_cmd_config(const char *var, const char *value, void *cb)
{
	if (!strcmp(var, "help.autocorrect"))
		autocorrect = git_config_int(var,value);
	/* Also use aliases for command lookup */
	if (starts_with(var, "alias."))
		add_cmdname(&aliases, var + 6, strlen(var + 6));

	return git_default_config(var, value, cb);
}