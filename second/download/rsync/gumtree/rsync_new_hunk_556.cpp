		   try to use them. Redirect them to /dev/null */
		for (i=1;i<3;i++) {
			close(i); 
			open("/dev/null", O_RDWR);
		}

		return start_daemon(STDIN_FILENO);
	}

	become_daemon();

	if (!lp_load(config_file, 1)) {
		exit_cleanup(RERR_SYNTAX);
	}

	log_open();

	rprintf(FINFO,"rsyncd version %s starting\n",VERSION);
