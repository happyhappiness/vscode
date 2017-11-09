static inline int get_noglob_global(void)
{
	static int noglob = -1;

	if (noglob < 0)
		noglob = git_env_bool(GIT_NOGLOB_PATHSPECS_ENVIRONMENT, 0);

	return noglob;
}