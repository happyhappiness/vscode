void io_start_multiplex_in(int fd)
{
	multiplex_in_fd = fd;
	io_flush();
	io_multiplexing_in = 1;
}