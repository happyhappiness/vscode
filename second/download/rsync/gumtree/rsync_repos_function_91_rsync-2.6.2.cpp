static void writefd(int fd,char *buf,size_t len)
{
	stats.total_written += len;

	msg_list_push(NORMAL_FLUSH);

	if (!io_buffer || fd != multiplex_out_fd) {
		writefd_unbuffered(fd, buf, len);
		return;
	}

	while (len) {
		int n = MIN((int) len, IO_BUFFER_SIZE-io_buffer_count);
		if (n > 0) {
			memcpy(io_buffer+io_buffer_count, buf, n);
			buf += n;
			len -= n;
			io_buffer_count += n;
		}

		if (io_buffer_count == IO_BUFFER_SIZE)
			io_flush(NORMAL_FLUSH);
	}
}