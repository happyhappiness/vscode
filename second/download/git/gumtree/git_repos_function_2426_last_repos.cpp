const char *git_exec_path(void)
{
	static char *cached_exec_path;

	if (argv_exec_path)
		return argv_exec_path;

	if (!cached_exec_path) {
		const char *env = getenv(EXEC_PATH_ENVIRONMENT);
		if (env && *env)
			cached_exec_path = xstrdup(env);
		else
			cached_exec_path = system_path(GIT_EXEC_PATH);
	}
	return cached_exec_path;
}