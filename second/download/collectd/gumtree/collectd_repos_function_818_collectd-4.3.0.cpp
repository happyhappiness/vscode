static int ping_receive_all (pingobj_t *obj)
{
	fd_set readfds;
	int num_readfds;
	int max_readfds;

	pinghost_t *ph;
	pinghost_t *ptr;

	struct timeval endtime;
	struct timeval nowtime;
	struct timeval timeout;
	int status;

	int ret;

	ph = obj->head;
	ret = 0;

	for (ptr = ph; ptr != NULL; ptr = ptr->next)
		ptr->latency = -1.0;

	if (gettimeofday (&nowtime, NULL) == -1)
	{
		ping_set_error (obj, "gettimeofday", strerror (errno));
		return (-1);
	}

	/* Set up timeout */
	timeout.tv_sec = (time_t) obj->timeout;
	timeout.tv_usec = (suseconds_t) (1000000 * (obj->timeout - ((double) timeout.tv_sec)));

	dprintf ("Set timeout to %i.%06i seconds\n",
			(int) timeout.tv_sec,
			(int) timeout.tv_usec);

	ping_timeval_add (&nowtime, &timeout, &endtime);

	while (1)
	{
		FD_ZERO (&readfds);
		num_readfds =  0;
		max_readfds = -1;

		for (ptr = ph; ptr != NULL; ptr = ptr->next)
		{
			if (!timerisset (ptr->timer))
				continue;

			FD_SET (ptr->fd, &readfds);
			num_readfds++;

			if (max_readfds < ptr->fd)
				max_readfds = ptr->fd;
		}

		if (num_readfds == 0)
			break;

		if (gettimeofday (&nowtime, NULL) == -1)
		{
			ping_set_error (obj, "gettimeofday", strerror (errno));
			return (-1);
		}

		if (ping_timeval_sub (&endtime, &nowtime, &timeout) == -1)
			break;

		dprintf ("Waiting on %i sockets for %i.%06i seconds\n", num_readfds,
				(int) timeout.tv_sec,
				(int) timeout.tv_usec);

		status = select (max_readfds + 1, &readfds, NULL, NULL, &timeout);

		if (gettimeofday (&nowtime, NULL) == -1)
		{
			ping_set_error (obj, "gettimeofday", strerror (errno));
			return (-1);
		}
		
		if ((status == -1) && (errno == EINTR))
		{
			dprintf ("select was interrupted by signal..\n");
			continue;
		}
		else if (status < 0)
		{
			dprintf ("select: %s\n", strerror (errno));
			break;
		}
		else if (status == 0)
		{
			dprintf ("select timed out\n");
			break;
		}

		for (ptr = ph; ptr != NULL; ptr = ptr->next)
		{
			if (FD_ISSET (ptr->fd, &readfds))
				if (ping_receive_one (ptr->fd, ph, &nowtime) == 0)
					ret++;
		}
	} /* while (1) */
	
	return (ret);
}