int claim_connection(char *fname, int max_connections)
{
	int fd, i;

	if (max_connections == 0)
		return 1;

	if ((fd = open(fname, O_RDWR|O_CREAT, 0600)) < 0)
		return 0;

	/* Find a free spot. */
	for (i = 0; i < max_connections; i++) {
		if (lock_range(fd, i*4, 4))
			return 1;
	}

	close(fd);

	/* A lock failure needs to return an errno of 0. */
	errno = 0;
	return 0;
}