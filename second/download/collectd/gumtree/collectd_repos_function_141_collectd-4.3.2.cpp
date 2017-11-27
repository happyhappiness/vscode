static int ping_read (void)
{
	pingobj_iter_t *iter;

	char   host[512];
	double latency;
	size_t buf_len;
	int    number_of_hosts;

	if (pingobj == NULL)
		return (-1);

	if (hosts != NULL)
		add_hosts ();

	if (ping_send (pingobj) < 0)
	{
		ERROR ("ping plugin: `ping_send' failed: %s",
				ping_get_error (pingobj));
		return (-1);
	}

	number_of_hosts = 0;
	for (iter = ping_iterator_get (pingobj);
			iter != NULL;
			iter = ping_iterator_next (iter))
	{
		buf_len = sizeof (host);
		if (ping_iterator_get_info (iter, PING_INFO_HOSTNAME,
					host, &buf_len))
		{
			WARNING ("ping plugin: ping_iterator_get_info "
					"(PING_INFO_HOSTNAME) failed.");
			continue;
		}

		buf_len = sizeof (latency);
		if (ping_iterator_get_info (iter, PING_INFO_LATENCY,
					&latency, &buf_len))
		{
			WARNING ("ping plugin: ping_iterator_get_info (%s, "
					"PING_INFO_LATENCY) failed.", host);
			continue;
		}

		DEBUG ("ping plugin: host = %s, latency = %f", host, latency);
		ping_submit (host, latency);
		number_of_hosts++;
	}

	if ((number_of_hosts == 0) && (getuid () != 0))
	{
		ERROR ("ping plugin: All hosts failed. Try starting collectd as root.");
	}

	return (number_of_hosts == 0 ? -1 : 0);
}