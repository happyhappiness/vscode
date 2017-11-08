void start_accept_loop(int port, int (*fn)(int ))
{
	int s;
	extern char *bind_address;
	extern int default_af_hint;

	/* open an incoming socket */
	s = open_socket_in(SOCK_STREAM, port, bind_address, default_af_hint);
	if (s == -1)
		exit_cleanup(RERR_SOCKETIO);

	/* ready to listen */
	if (listen(s, 5) == -1) {
		close(s);
		exit_cleanup(RERR_SOCKETIO);
	}


	/* now accept incoming connections - forking a new process
	   for each incoming connection */
	while (1) {
		fd_set fds;
		pid_t pid;
		int fd;
		struct sockaddr_storage addr;
		socklen_t addrlen = sizeof addr;

		/* close log file before the potentially very long select so
		   file can be trimmed by another process instead of growing
		   forever */
		log_close();

		FD_ZERO(&fds);
		FD_SET(s, &fds);

		if (select(s+1, &fds, NULL, NULL, NULL) != 1) {
			continue;
		}

		if(!FD_ISSET(s, &fds)) continue;

		fd = accept(s,(struct sockaddr *)&addr,&addrlen);

		if (fd == -1) continue;

		signal(SIGCHLD, SIG_IGN);

		/* we shouldn't have any children left hanging around
		   but I have had reports that on Digital Unix zombies
		   are produced, so this ensures that they are reaped */
#ifdef WNOHANG
                while (waitpid(-1, NULL, WNOHANG) > 0);
#endif

		if ((pid = fork()) == 0) {
			close(s);
			/* open log file in child before possibly giving
			   up privileges  */
			log_open();
			_exit(fn(fd));
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
}