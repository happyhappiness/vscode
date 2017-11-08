void start_accept_loop(int port, int (*fn)(int ))
{
	int s;

	signal(SIGCHLD, SIG_IGN);

	/* open an incoming socket */
	s = open_socket_in(SOCK_STREAM, port);
	if (s == -1)
		exit_cleanup(1);

	/* ready to listen */
	if (listen(s, 5) == -1) {
		close(s);
		exit_cleanup(1);
	}


	/* now accept incoming connections - forking a new process
	   for each incoming connection */
	while (1) {
		fd_set fds;
		int fd;
		struct sockaddr addr;
		int in_addrlen = sizeof(addr);

		FD_ZERO(&fds);
		FD_SET(s, &fds);

		if (select(s+1, &fds, NULL, NULL, NULL) != 1) {
			continue;
		}

		if(!FD_ISSET(s, &fds)) continue;

		fd = accept(s,&addr,&in_addrlen);

		if (fd == -1) continue;

		if (fork()==0) {
			close(s);

			_exit(fn(fd));
		}

		close(fd);
	}
}