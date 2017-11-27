ssize_t swrite (int fd, const void *buf, size_t count)
{
	const char *ptr;
	size_t      nleft;
	ssize_t     status;

	ptr   = (const char *) buf;
	nleft = count;

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