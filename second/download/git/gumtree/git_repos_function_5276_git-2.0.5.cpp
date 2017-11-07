int mingw_execv(const char *cmd, char *const *argv)
{
	mingw_execve(cmd, argv, environ);
	return -1;
}