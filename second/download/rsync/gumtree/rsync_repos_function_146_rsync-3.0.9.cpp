static void writefd(int fd, const char *buf, size_t len)
{
	if (fd == sock_f_out)
		stats.total_written += len;

	if (fd == write_batch_monitor_out)
		writefd_unbuffered(batch_fd, buf, len);

	if (!iobuf_out || fd != iobuf_f_out) {
		writefd_unbuffered(fd, buf, len);
		return;
	}

	while (len) {
		int n = MIN((int)len, IO_BUFFER_SIZE - iobuf_out_cnt);
		if (n > 0) {
			memcpy(iobuf_out+iobuf_out_cnt, buf, n);
			buf += n;
			len -= n;
			iobuf_out_cnt += n;
		}

		if (iobuf_out_cnt == IO_BUFFER_SIZE)
			io_flush(NORMAL_FLUSH);
	}
}