static ssize_t ping_sendto (pingobj_t *obj, pinghost_t *ph,
		const void *buf, size_t buflen)
{
	ssize_t ret;

	if (gettimeofday (ph->timer, NULL) == -1)
	{
		timerclear (ph->timer);
		return (-1);
	}

	ret = sendto (ph->fd, buf, buflen, 0,
			(struct sockaddr *) ph->addr, ph->addrlen);

	if (ret < 0)
	{
#if defined(EHOSTUNREACH)
		if (errno == EHOSTUNREACH)
			return (0);
#endif
#if defined(ENETUNREACH)
		if (errno == ENETUNREACH)
			return (0);
#endif
		ping_set_error (obj, "sendto", strerror (errno));
	}

	return (ret);
}