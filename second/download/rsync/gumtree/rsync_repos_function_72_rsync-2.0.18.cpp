void io_end_buffering(int fd)
{
	io_flush();
	if (!io_multiplexing_out) {
		free(io_buffer-4);
		io_buffer = NULL;
	}
}