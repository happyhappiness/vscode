void io_start_multiplex_in(int fd)
{
	multiplex_in_fd = fd;
	io_flush(NORMAL_FLUSH);
	io_multiplexing_in = 1;
}