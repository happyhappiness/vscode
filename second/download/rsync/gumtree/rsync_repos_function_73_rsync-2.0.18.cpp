static void writefd(int fd,char *buf,int len)
{
	if (!io_buffer) {
		writefd_unbuffered(fd, buf, len);
		return;
	}

	while (len) {
		int n = MIN(len, IO_BUFFER_SIZE-io_buffer_count);
		if (n > 0) {
			memcpy(io_buffer+io_buffer_count, buf, n);
			buf += n;
			len -= n;
			io_buffer_count += n;
		}
		
		if (io_buffer_count == IO_BUFFER_SIZE) io_flush();
	}
}