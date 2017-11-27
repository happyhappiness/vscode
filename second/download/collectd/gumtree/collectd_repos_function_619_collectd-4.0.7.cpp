static int ping_receive_one (int fd, pinghost_t *ph, struct timeval *now)
{
	char   buffer[4096];
	size_t buffer_len;

	struct timeval diff;

	pinghost_t *host = NULL;

	struct sockaddr_storage sa;
	socklen_t               sa_len;

	sa_len = sizeof (sa);

	buffer_len = recvfrom (fd, buffer, sizeof (buffer), 0,
			(struct sockaddr *) &sa, &sa_len);
	if (buffer_len == -1)
	{
		dprintf ("recvfrom: %s\n", strerror (errno));
		return (-1);
	}

	dprintf ("Read %u bytes from fd = %i\n", (unsigned int) buffer_len, fd);

	if (sa.ss_family == AF_INET)
	{
		if ((host = ping_receive_ipv4 (ph, buffer, buffer_len)) == NULL)
			return (-1);
	}
	else if (sa.ss_family == AF_INET6)
	{
		if ((host = ping_receive_ipv6 (ph, buffer, buffer_len)) == NULL)
			return (-1);
	}

	dprintf ("rcvd: %12i.%06i\n",
			(int) now->tv_sec,
			(int) now->tv_usec);
	dprintf ("sent: %12i.%06i\n",
			(int) host->timer->tv_sec,
			(int) host->timer->tv_usec);

	if (ping_timeval_sub (now, host->timer, &diff) < 0)
	{
		timerclear (host->timer);
		return (-1);
	}

	dprintf ("diff: %12i.%06i\n",
			(int) diff.tv_sec,
			(int) diff.tv_usec);

	host->latency  = ((double) diff.tv_usec) / 1000.0;
	host->latency += ((double) diff.tv_sec)  * 1000.0;

	timerclear (host->timer);

	return (0);
}