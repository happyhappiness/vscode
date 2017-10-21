static int read_unbuffered(int fd, char *buf, size_t len)
{
	static size_t remaining;
	int tag, ret = 0;
	char line[1024];
	static char *buffer;
	static size_t bufferIdx = 0;
	static size_t bufferSz;

	if (fd != multiplex_in_fd)
		return read_timeout(fd, buf, len);

	if (!io_multiplexing_in && remaining == 0) {
		if (!buffer) {
			bufferSz = 2 * IO_BUFFER_SIZE;
			buffer   = new_array(char, bufferSz);
			if (!buffer) out_of_memory("read_unbuffered");
		}
		remaining = read_timeout(fd, buffer, bufferSz);
		bufferIdx = 0;
	}

	while (ret == 0) {
		if (remaining) {
			len = MIN(len, remaining);
			memcpy(buf, buffer + bufferIdx, len);
			bufferIdx += len;
			remaining -= len;
			ret = len;
			break;
		}

		read_loop(fd, line, 4);
		tag = IVAL(line, 0);

		remaining = tag & 0xFFFFFF;
		tag = (tag >> 24) - MPLEX_BASE;

		switch (tag) {
		case MSG_DATA:
			if (!buffer || remaining > bufferSz) {
				buffer = realloc_array(buffer, char, remaining);
				if (!buffer) out_of_memory("read_unbuffered");
				bufferSz = remaining;
			}
			read_loop(fd, buffer, remaining);
			bufferIdx = 0;
			break;
		case MSG_INFO:
		case MSG_ERROR:
			if (remaining >= sizeof line) {
				rprintf(FERROR, "multiplexing overflow %d:%ld\n\n",
					tag, (long)remaining);
				exit_cleanup(RERR_STREAMIO);
			}
			read_loop(fd, line, remaining);
			rwrite((enum logcode)tag, line, remaining);
			remaining = 0;
			break;
		default:
			rprintf(FERROR, "unexpected tag %d\n", tag);
			exit_cleanup(RERR_STREAMIO);
		}
	}

	if (remaining == 0)
		io_flush(NORMAL_FLUSH);

	return ret;
}