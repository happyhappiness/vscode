void start_accept_loop(int port, int (*fn)(int, int))
{
	fd_set deffds;
	int *sp, maxfd, i;

#ifdef HAVE_SIGACTION
	sigact.sa_flags = SA_NOCLDSTOP;
#endif

	/* open an incoming socket */
	sp = open_socket_in(SOCK_STREAM, port, bind_address, default_af_hint);
	if (sp == NULL)
		exit_cleanup(RERR_SOCKETIO);

	/* ready to listen */
	FD_ZERO(&deffds);
	for (i = 0, maxfd = -1; sp[i] >= 0; i++) {
		if (listen(sp[i], lp_listen_backlog()) < 0) {
			rsyserr(FERROR, errno, "listen() on socket failed");
#ifdef INET6
			if (errno == EADDRINUSE && i > 0) {
				rprintf(FINFO,
				    "Try using --ipv4 or --ipv6 to avoid this listen() error.\n");
			}
#endif
			exit_cleanup(RERR_SOCKETIO);
		}
		FD_SET(sp[i], &deffds);
		if (maxfd < sp[i])
			maxfd = sp[i];
	}

	/* now accept incoming connections - forking a new process
	 * for each incoming connection */
	while (1) {
		fd_set fds;
		pid_t pid;
		int fd;
		struct sockaddr_storage addr;
		socklen_t addrlen = sizeof addr;

		/* close log file before the potentially very long select so
		 * file can be trimmed by another process instead of growing
		 * forever */
		logfile_close();

#ifdef FD_COPY
		FD_COPY(&deffds, &fds);
#else
		fds = deffds;
#endif

		if (select(maxfd + 1, &fds, NULL, NULL, NULL) < 1)
			continue;

		for (i = 0, fd = -1; sp[i] >= 0; i++) {
			if (FD_ISSET(sp[i], &fds)) {
				fd = accept(sp[i], (struct sockaddr *)&addr,
					    &addrlen);
				break;
			}
		}

		if (fd < 0)
			continue;

		SIGACTION(SIGCHLD, sigchld_handler);

		if ((pid = fork()) == 0) {
			int ret;
			for (i = 0; sp[i] >= 0; i++)
				close(sp[i]);
			/* Re-open log file in child before possibly giving
			 * up privileges (see logfile_close() above). */
			logfile_reopen();
			ret = fn(fd, fd);
			close_all();
			_exit(ret);
		} else if (pid < 0) {
			rsyserr(FERROR, errno,
				"could not create child server process");
			close(fd);
			/* This might have happened because we're
			 * overloaded.  Sleep briefly before trying to
			 * accept again. */
			sleep(2);
		} else {
			/* Parent doesn't need this fd anymore. */
			close(fd);
		}
	}
}