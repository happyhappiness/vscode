
	argv_array_pushv(out, argv);
	return out->argv;
}

#ifndef GIT_WINDOWS_NATIVE
static int execv_shell_cmd(const char **argv)
{
	struct argv_array nargv = ARGV_ARRAY_INIT;
	prepare_shell_cmd(&nargv, argv);
	trace_argv_printf(nargv.argv, "trace: exec:");
	sane_execvp(nargv.argv[0], (char **)nargv.argv);
	argv_array_clear(&nargv);
	return -1;
}
#endif

#ifndef GIT_WINDOWS_NATIVE
static int child_notifier = -1;

static void notify_parent(void)
{
	/*
	 * execvp failed.  If possible, we'd like to let start_command
	 * know, so failures like ENOENT can be handled right away; but
	 * otherwise, finish_command will still report the error.
	 */
	xwrite(child_notifier, "", 1);
}
#endif

static inline void set_cloexec(int fd)
{
	int flags = fcntl(fd, F_GETFD);
	if (flags >= 0)
		fcntl(fd, F_SETFD, flags | FD_CLOEXEC);
