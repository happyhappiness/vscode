void io_flush(void)
{
	int fd = multiplex_out_fd;
	if (!io_buffer_count || no_flush) return;

	if (io_multiplexing_out) {
		SIVAL(io_buffer-4, 0, (MPLEX_BASE<<24) + io_buffer_count);
		writefd_unbuffered(fd, io_buffer-4, io_buffer_count+4);
	} else {
		writefd_unbuffered(fd, io_buffer, io_buffer_count);
	}
	io_buffer_count = 0;
}