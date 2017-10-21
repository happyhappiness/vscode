	}

	become_daemon();

	if (!lp_load(config_file, 1)) {
		fprintf(stderr,"failed to load config file %s\n", config_file);
		exit_cleanup(1);
	}

	log_open();

	rprintf(FINFO,"rsyncd version %s starting\n",VERSION);

	start_accept_loop(rsync_port, start_daemon);
	return -1;
}

