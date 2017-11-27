static int daemonize (void)
{
	struct rlimit rl;

	pid_t pid = 0;
	int   i   = 0;

	if (0 != chdir ("/")) {
		fprintf (stderr, "Error: chdir() failed: %s\n", strerror (errno));
		return -1;
	}

	if (0 != getrlimit (RLIMIT_NOFILE, &rl)) {
		fprintf (stderr, "Error: getrlimit() failed: %s\n", strerror (errno));
		return -1;
	}

	if (0 > (pid = fork ())) {
		fprintf (stderr, "Error: fork() failed: %s\n", strerror (errno));
		return -1;
	}
	else if (pid != 0) {
		exit (0);
	}

	if (0 != pidfile_create ())
		return -1;

	setsid ();

	if (RLIM_INFINITY == rl.rlim_max)
		rl.rlim_max = 1024;

	for (i = 0; i < (int)rl.rlim_max; ++i)
		close (i);

	errno = 0;
	if (open ("/dev/null", O_RDWR) != 0) {
		syslog (LOG_ERR, "Error: couldn't connect STDIN to /dev/null: %s",
				strerror (errno));
		return -1;
	}

	errno = 0;
	if (dup (0) != 1) {
		syslog (LOG_ERR, "Error: couldn't connect STDOUT to /dev/null: %s",
				strerror (errno));
		return -1;
	}

	errno = 0;
	if (dup (0) != 2) {
		syslog (LOG_ERR, "Error: couldn't connect STDERR to /dev/null: %s",
				strerror (errno));
		return -1;
	}
	return 0;
}