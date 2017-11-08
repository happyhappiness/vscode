void io_end_multiplex_out(void)
{
	io_multiplexing_out = 0;
	io_end_buffering_out();
}