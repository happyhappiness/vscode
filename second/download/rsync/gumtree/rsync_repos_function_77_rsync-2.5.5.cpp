void io_flush(void)
{
	int fd = multiplex_out_fd;

	err_list_push();

	if (!io_buffer_count || no_flush) return;

	if (io_multiplexing_out) {
		mplex_write(fd, FNONE, io_buffer, io_buffer_count);
	} else {
		writefd_unbuffered(fd, io_buffer, io_buffer_count);
	}
	io_buffer_count = 0;
}