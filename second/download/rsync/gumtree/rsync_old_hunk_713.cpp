 */
static int read_unbuffered(int fd, char *buf, size_t len)
{
	static size_t remaining;
	int tag, ret = 0;
	char line[1024];

	if (!io_multiplexing_in || fd != multiplex_in_fd)
		return read_timeout(fd, buf, len);

	while (ret == 0) {
		if (remaining) {
			len = MIN(len, remaining);
			read_loop(fd, buf, len);
			remaining -= len;
			ret = len;
			continue;
		}

		read_loop(fd, line, 4);
		tag = IVAL(line, 0);

		remaining = tag & 0xFFFFFF;
		tag = tag >> 24;

		if (tag == MPLEX_BASE)
			continue;

		tag -= MPLEX_BASE;

		if (tag != FERROR && tag != FINFO) {
			rprintf(FERROR, "unexpected tag %d\n", tag);
			exit_cleanup(RERR_STREAMIO);
		}

		if (remaining > sizeof line - 1) {
			rprintf(FERROR, "multiplexing overflow %ld\n\n",
				(long)remaining);
			exit_cleanup(RERR_STREAMIO);
		}

		read_loop(fd, line, remaining);
		line[remaining] = 0;

		rprintf((enum logcode) tag, "%s", line);
		remaining = 0;
	}

	return ret;
}



/**
