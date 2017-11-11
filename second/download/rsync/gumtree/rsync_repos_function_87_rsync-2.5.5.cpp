void io_start_multiplex_out(int fd)
{
	multiplex_out_fd = fd;
	io_flush();
	io_start_buffering(fd);
	io_multiplexing_out = 1;
}