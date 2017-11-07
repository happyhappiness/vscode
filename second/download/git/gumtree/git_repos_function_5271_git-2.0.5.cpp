static pid_t mingw_spawnve(const char *cmd, const char **argv, char **env,
			   int prepend_cmd)
{
	return mingw_spawnve_fd(cmd, argv, env, NULL, prepend_cmd, 0, 1, 2);
}