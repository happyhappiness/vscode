static inline int get_glob_global(void)
{
	static int glob = -1;

	if (glob < 0)
		glob = git_env_bool(GIT_GLOB_PATHSPECS_ENVIRONMENT, 0);

	return glob;
}