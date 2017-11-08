void io_start_multiplex_out(void)
{
	io_flush(NORMAL_FLUSH);
	io_start_buffering_out(sock_f_out);
	io_multiplexing_out = 1;
}