int daemon_main(void)
{
	extern char *config_file;
	char *pid_file;

	/* this ensures that we don't call getcwd after the chroot,
           which doesn't work on platforms that use popen("pwd","r")
           for getcwd */
	push_dir("/", 0);

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
		FILE *f;
		int pid = (int) getpid();
		cleanup_set_pid(pid);
		if ((f = fopen(lp_pid_file(), "w")) == NULL) {
		    cleanup_set_pid(0);
		    fprintf(stderr,"failed to create pid file %s\n", pid_file);
		    exit_cleanup(RERR_FILEIO);
		}
		fprintf(f, "%d\n", pid);
		fclose(f);
	}

	start_accept_loop(rsync_port, start_daemon);
	return -1;
}