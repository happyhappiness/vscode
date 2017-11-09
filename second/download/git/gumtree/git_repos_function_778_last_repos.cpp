static int get_packet_data(int fd, char **src_buf, size_t *src_size,
			   void *dst, unsigned size, int options)
{
	ssize_t ret;

	if (fd >= 0 && src_buf && *src_buf)
		die("BUG: multiple sources given to packet_read");

	/* Read up to "size" bytes from our source, whatever it is. */
	if (src_buf && *src_buf) {
		ret = size < *src_size ? size : *src_size;
		memcpy(dst, *src_buf, ret);
		*src_buf += ret;
		*src_size -= ret;
	} else {
		ret = read_in_full(fd, dst, size);
		if (ret < 0)
			die_errno("read error");
	}

	/* And complain if we didn't get enough bytes to satisfy the read. */
	if (ret < size) {
		if (options & PACKET_READ_GENTLE_ON_EOF)
			return -1;

		die("The remote end hung up unexpectedly");
	}

	return ret;
}