int claim_connection(char *fname,int max_connections)
{
	int fd, i;

	if (max_connections <= 0)
		return 1;

	fd = open(fname,O_RDWR|O_CREAT, 0600);

	if (fd == -1) {
		return 0;
	}

	/* find a free spot */
	for (i=0;i<max_connections;i++) {
		if (lock_range(fd, i*4, 4)) return 1;
	}

	/* only interested in open failures */
	errno = 0;

	close(fd);
	return 0;
}