int pager_in_use(void)
{
	const char *env;
	env = getenv("GIT_PAGER_IN_USE");
	return env ? git_config_bool("GIT_PAGER_IN_USE", env) : 0;
}