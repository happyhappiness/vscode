int pager_in_use(void)
{
	return git_env_bool("GIT_PAGER_IN_USE", 0);
}