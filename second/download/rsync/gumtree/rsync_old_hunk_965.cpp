	}

	if (!load_config(1)) {
		fprintf(stderr, "Failed to parse config file: %s\n", config_file);
		exit_cleanup(RERR_SYNTAX);
	}

	if (no_detach)
		create_pid_file();
	else
		become_daemon();

