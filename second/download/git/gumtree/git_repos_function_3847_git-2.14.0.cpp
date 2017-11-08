static int core_pager_config(const char *var, const char *value, void *data)
{
	if (!strcmp(var, "core.pager"))
		return git_config_string(&pager_program, var, value);
	return 0;
}