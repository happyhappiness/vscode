void io_start_multiplex_out(int fd)
{
	multiplex_out_fd = fd;
	io_flush(NORMAL_FLUSH);
	io_start_buffering_out(fd);
	io_multiplexing_out = 1;
}