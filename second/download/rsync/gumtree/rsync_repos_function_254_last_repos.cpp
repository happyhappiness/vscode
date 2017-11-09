static int socketpair_tcp(int fd[2])
{
	int listener;
	struct sockaddr_in sock;
	struct sockaddr_in sock2;
	socklen_t socklen = sizeof sock;
	int connect_done = 0;

	fd[0] = fd[1] = listener = -1;

	memset(&sock, 0, sizeof sock);

	if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		goto failed;

	memset(&sock2, 0, sizeof sock2);
#ifdef HAVE_SOCKADDR_IN_LEN
	sock2.sin_len = sizeof sock2;
#endif
	sock2.sin_family = PF_INET;
	sock2.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (bind(listener, (struct sockaddr *)&sock2, sizeof sock2) != 0
	 || listen(listener, 1) != 0
	 || getsockname(listener, (struct sockaddr *)&sock, &socklen) != 0
	 || (fd[1] = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		goto failed;

	set_nonblocking(fd[1]);

	sock.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (connect(fd[1], (struct sockaddr *)&sock, sizeof sock) == -1) {
		if (errno != EINPROGRESS)
			goto failed;
	} else
		connect_done = 1;

	if ((fd[0] = accept(listener, (struct sockaddr *)&sock2, &socklen)) == -1)
		goto failed;

	close(listener);
	listener = -1;

	set_blocking(fd[1]);

	if (connect_done == 0) {
		if (connect(fd[1], (struct sockaddr *)&sock, sizeof sock) != 0
		    && errno != EISCONN)
			goto failed;
	}

	/* all OK! */
	return 0;

 failed:
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (listener != -1)
		close(listener);
	return -1;
}