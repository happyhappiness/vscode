pid_t waitpid(pid_t pid, int *statptr, int options)
{
	return wait4(pid, statptr, options, NULL);
}