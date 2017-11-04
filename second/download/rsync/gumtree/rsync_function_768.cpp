static void become_daemon(void)
{
	int i;
	pid_t pid = fork();

	if (pid) {
		if (pid < 0) {
			fprintf(stderr, "failed to fork: %s\n", strerror(errno));
			exit_cleanup(RERR_FILEIO);
		}
		_exit(0);
	}

	create_pid_file();

	/* detach from the terminal */
#ifdef HAVE_SETSID
	setsid();
#elif defined TIOCNOTTY
	i = open("/dev/tty", O_RDWR);
	if (i >= 0) {
		ioctl(i, (int)TIOCNOTTY, (char *)0);
		close(i);
	}
#endif
	/* make sure that stdin, stdout an stderr don't stuff things
	 * up (library functions, for example) */
	for (i = 0; i < 3; i++) {
		close(i);
		open("/dev/null", O_RDWR);
	}
}