void io_end_buffering(void)
{
	io_flush();
	if (!io_multiplexing_out) {
		free(io_buffer);
		io_buffer = NULL;
	}
}