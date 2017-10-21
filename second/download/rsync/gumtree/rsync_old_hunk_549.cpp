
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

