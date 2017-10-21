int daemon_main(void)
{
	extern char *config_file;
	extern int orig_umask;
	char *pid_file;

	if (is_a_socket(STDIN_FILENO)) {
		int i;

		/* we are running via inetd - close off stdout and
		   stderr so that library functions (and getopt) don't
		   try to use them. Redirect them to /dev/null */
		for (i=1;i<3;i++) {
			close(i); 
			open("/dev/null", O_RDWR);
		}

		set_nonblocking(STDIN_FILENO);

		return start_daemon(STDIN_FILENO);
	}

	become_daemon();

	if (!lp_load(config_file, 1)) {
		fprintf(stderr,"failed to load config file %s\n", config_file);
		exit_cleanup(RERR_SYNTAX);
	}

	log_open();

	rprintf(FINFO,"rsyncd version %s starting\n",VERSION);

	if (((pid_file = lp_pid_file()) != NULL) && (*pid_file != '\0')) {
		char pidbuf[16];
		int fd;
		int pid = (int) getpid();
		cleanup_set_pid(pid);
		if ((fd = do_open(lp_pid_file(), O_WRONLY|O_CREAT|O_TRUNC,
					0666 & ~orig_umask)) == -1) {
		    cleanup_set_pid(0);
		    fprintf(stderr,"failed to create pid file %s\n", pid_file);
		    exit_cleanup(RERR_FILEIO);
		}
		slprintf(pidbuf, sizeof(pidbuf), "%d\n", pid);
		write(fd, pidbuf, strlen(pidbuf));
		close(fd);
	}

	start_accept_loop(rsync_port, start_daemon);
	return -1;
}