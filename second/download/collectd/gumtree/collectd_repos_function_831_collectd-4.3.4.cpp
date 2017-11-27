static pinghost_t *ping_alloc (void)
{
	pinghost_t *ph;
	size_t      ph_size;

	ph_size = sizeof (pinghost_t)
		+ sizeof (struct sockaddr_storage)
		+ sizeof (struct timeval);

	ph = (pinghost_t *) malloc (ph_size);
	if (ph == NULL)
		return (NULL);

	memset (ph, '\0', ph_size);

	ph->timer   = (struct timeval *) (ph + 1);
	ph->addr    = (struct sockaddr_storage *) (ph->timer + 1);

	ph->addrlen = sizeof (struct sockaddr_storage);
	ph->latency = -1.0;
	ph->ident   = ping_get_ident () & 0xFFFF;

	return (ph);
}