ssize_t swrite (int fd, const void *buf, size_t count)
{
	const char *ptr;
	size_t      nleft;
	ssize_t     status;
	struct      pollfd pfd;

	ptr   = (const char *) buf;
	nleft = count;
	
	/* checking for closed peer connection */
	pfd.fd = fd;
	pfd.events = POLLIN | POLLHUP;
	pfd.revents = 0;
	if (poll(&pfd, 1, 0) > 0) {
		char buffer[32];
		if (recv(fd, buffer, sizeof(buffer), MSG_PEEK | MSG_DONTWAIT) == 0) {
			// if recv returns zero (even though poll() said there is data to be read),
			// that means the connection has been closed
			return -1;
		}
	}

	while (nleft > 0)
	{
		status = write (fd, (const void *) ptr, nleft);

		if ((status < 0) && ((errno == EAGAIN) || (errno == EINTR)))
			continue;

		if (status < 0)
			return (status);

		nleft = nleft - status;
		ptr   = ptr   + status;
	}

	return (0);
}