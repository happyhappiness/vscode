void start_accept_loop(int port, int (*fn)(int, int))
{
	fd_set deffds;
	int *sp, maxfd, i, j;
	extern char *bind_address;
	extern int default_af_hint;

	/* open an incoming socket */
	sp = open_socket_in(SOCK_STREAM, port, bind_address, default_af_hint);
	if (sp == NULL)
		exit_cleanup(RERR_SOCKETIO);

	/* ready to listen */
	FD_ZERO(&deffds);
	maxfd = -1;
	for (i = 1; i <= *sp; i++) {
		if (listen(sp[i], 5) == -1) {
			for (j = 1; j <= i; j++)
				close(sp[j]);
			free(sp);
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
		log_close();

#ifdef FD_COPY
		FD_COPY(&deffds, &fds);
#else
		fds = deffds;
#endif

		if (select(maxfd + 1, &fds, NULL, NULL, NULL) != 1)
			continue;

		fd = -1;
		for (i = 1; i <= *sp; i++) {
			if (FD_ISSET(sp[i], &fds)) {
				fd = accept(sp[i], (struct sockaddr *)&addr,
					    &addrlen);
				break;
			}
		}

		if (fd < 0)
			continue;

		signal(SIGCHLD, sigchld_handler);

		if ((pid = fork()) == 0) {
			int ret;
			close(sp[i]);
			/* open log file in child before possibly giving
			 * up privileges  */
			log_open();
			ret = fn(fd, fd);
			close_all();
			_exit(ret);
		} else if (pid < 0) {
			rprintf(FERROR,
				RSYNC_NAME
				": could not create child server process: %s\n",
				strerror(errno));
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
	free(sp);
}