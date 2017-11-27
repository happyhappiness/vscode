static pinghost_t *ping_host_search (pinghost_t *ph, const char *host)
{
	while (ph != NULL)
	{
		if (strcasecmp (ph->hostname, host) == 0)
			break;

		ph = ph->next;
	}

	return (ph);
}