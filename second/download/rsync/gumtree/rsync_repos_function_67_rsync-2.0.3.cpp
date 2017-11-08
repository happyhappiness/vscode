static int writefd(int fd,char *buf,int len1)
{
	int len = len1;

	if (!io_buffer) return writefd_unbuffered(fd, buf, len);

	while (len) {
		int n = MIN(len, IO_BUFFER_SIZE-io_buffer_count);
		if (n > 0) {
			memcpy(io_buffer+io_buffer_count, buf, n);
			buf += n;
			len -= n;
			io_buffer_count += n;
		}
		
		if (io_buffer_count == IO_BUFFER_SIZE) {
			if (writefd_unbuffered(fd, io_buffer, 
					       io_buffer_count) != 
			    io_buffer_count) {
				return -1;
			}
			io_buffer_count = 0;
		}
	}

	return len1;
}