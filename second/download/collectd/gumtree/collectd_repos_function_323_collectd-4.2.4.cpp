static char *read_line (conn_t *src)
{
	int i = 0;

	assert ((BUFSIZE >= src->idx) && (src->idx >= 0));
	assert ((src->idx > src->length) || (src->length == 0));

	if (src->length > 0) { /* remove old line */
		src->idx -= (src->length + 1);
		memmove (src->buffer, src->buffer + src->length + 1, src->idx);
		src->length = 0;
	}

	for (i = 0; i < src->idx; ++i) {
		if ('\n' == src->buffer[i])
			break;
	}

	if (i == src->idx) {
		fd_set fdset;

		ssize_t len = 0;

		FD_ZERO (&fdset);
		FD_SET (src->socket, &fdset);

		if (-1 == select (src->socket + 1, &fdset, NULL, NULL, NULL)) {
			char errbuf[1024];
			log_err ("select() failed: %s",
					sstrerror (errno, errbuf, sizeof (errbuf)));
			return NULL;
		}

		assert (FD_ISSET (src->socket, &fdset));

		do {
			errno = 0;
			if (0 > (len = read (src->socket,
							(void *)(src->buffer + src->idx),
							BUFSIZE - src->idx))) {
				if (EINTR != errno) {
					char errbuf[1024];
					log_err ("read() failed: %s",
							sstrerror (errno, errbuf, sizeof (errbuf)));
					return NULL;
				}
			}

			if (0 == len)
				return NULL;
		} while (EINTR == errno);

		src->idx += len;

		for (i = src->idx - len; i < src->idx; ++i) {
			if ('\n' == src->buffer[i])
				break;
		}

		if (i == src->idx) {
			src->length = 0;

			if (BUFSIZE == src->idx) { /* no space left in buffer */
				while ('\n' != read_char (src))
					/* ignore complete line */;

				src->idx = 0;
			}
			return read_line (src);
		}
	}

	src->buffer[i] = '\0';
	src->length    = i;

	return src->buffer;
}