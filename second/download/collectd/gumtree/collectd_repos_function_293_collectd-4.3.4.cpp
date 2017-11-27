ssize_t sread (int fd, void *buf, size_t count)
{
	char    *ptr;
	size_t   nleft;
	ssize_t  status;

	ptr   = (char *) buf;
	nleft = count;

	while (nleft > 0)
	{
		status = read (fd, (void *) ptr, nleft);

		if ((status < 0) && ((errno == EAGAIN) || (errno == EINTR)))
			continue;

		if (status < 0)
			return (status);

		if (status == 0)
		{
			DEBUG ("Received EOF from fd %i. "
					"Closing fd and returning error.",
					fd);
			close (fd);
			return (-1);
		}

		assert ((0 > status) || (nleft >= (size_t)status));

		nleft = nleft - status;
		ptr   = ptr   + status;
	}

	return (0);
}