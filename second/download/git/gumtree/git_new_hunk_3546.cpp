	if (inetd_mode || serve_mode)
		return execute();

	if (detach) {
		if (daemonize())
			die("--detach not supported on this platform");
	}

	if (pid_file)
		write_file(pid_file, "%"PRIuMAX, (uintmax_t) getpid());

	/* prepare argv for serving-processes */
	argv_array_push(&cld_argv, argv[0]); /* git-daemon */
