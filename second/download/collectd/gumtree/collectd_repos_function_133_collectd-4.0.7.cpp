static int ping_config (const char *key, const char *value)
{
	if (pingobj == NULL)
	{
		if ((pingobj = ping_construct ()) == NULL)
		{
			ERROR ("ping plugin: `ping_construct' failed.");
			return (1);
		}
	}

	if (strcasecmp (key, "host") == 0)
	{
		hostlist_t *hl;
		char *host;

		if ((hl = (hostlist_t *) malloc (sizeof (hostlist_t))) == NULL)
		{
			char errbuf[1024];
			ERROR ("ping plugin: malloc failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (1);
		}
		if ((host = strdup (value)) == NULL)
		{
			char errbuf[1024];
			free (hl);
			ERROR ("ping plugin: strdup failed: %s",
					sstrerror (errno, errbuf,
						sizeof (errbuf)));
			return (1);
		}

		hl->host = host;
		hl->wait_time = 2 * interval_g;
		hl->wait_left = 0;
		hl->next = hosts;
		hosts = hl;
	}
	else if (strcasecmp (key, "ttl") == 0)
	{
		int ttl = atoi (value);
		if (ping_setopt (pingobj, PING_DEF_TIMEOUT, (void *) &ttl))
		{
			WARNING ("ping: liboping did not accept the TTL value %i", ttl);
			return (1);
		}
	}
	else
	{
		return (-1);
	}

	return (0);
}