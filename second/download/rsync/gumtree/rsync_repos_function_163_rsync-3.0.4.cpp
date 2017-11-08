void io_end_multiplex_in(void)
{
	io_multiplexing_in = 0;
	io_end_buffering_in();
}