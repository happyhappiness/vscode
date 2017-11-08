void io_start_multiplex_in(void)
{
	io_flush(NORMAL_FLUSH);
	io_start_buffering_in(sock_f_in);
	io_multiplexing_in = 1;
}