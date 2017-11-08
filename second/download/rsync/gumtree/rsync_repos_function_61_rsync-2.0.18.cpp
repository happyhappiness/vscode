static int read_unbuffered(int fd, char *buf, int len)
{
	static int remaining;
	char ibuf[4];
	int tag, ret=0;
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

		read_loop(fd, ibuf, 4);
		tag = IVAL(ibuf, 0);

		remaining = tag & 0xFFFFFF;
		tag = tag >> 24;

		if (tag == MPLEX_BASE) continue;

		tag -= MPLEX_BASE;

		if (tag != FERROR && tag != FINFO) {
			rprintf(FERROR,"unexpected tag %d\n", tag);
			exit_cleanup(1);
		}

		if (remaining > sizeof(line)-1) {
			rprintf(FERROR,"multiplexing overflow %d\n\n", 
				remaining);
			exit_cleanup(1);
		}

		read_loop(fd, line, remaining);
		line[remaining] = 0;

		rprintf(tag,"%s", line);
		remaining = 0;
	}

	return ret;
}