static char read_char (conn_t *src)
{
	char ret = '\0';

	fd_set fdset;

	FD_ZERO (&fdset);
	FD_SET (src->socket, &fdset);

	if (-1 == select (src->socket + 1, &fdset, NULL, NULL, NULL)) {
		char errbuf[1024];
		log_err ("select() failed: %s",
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return '\0';
	}

	assert (FD_ISSET (src->socket, &fdset));

	do {
		ssize_t len = 0;

		errno = 0;
		if (0 > (len = read (src->socket, (void *)&ret, 1))) {
			if (EINTR != errno) {
				char errbuf[1024];
				log_err ("read() failed: %s",
						sstrerror (errno, errbuf, sizeof (errbuf)));
				return '\0';
			}
		}

		if (0 == len)
			return '\0';
	} while (EINTR == errno);
	return ret;
}