void io_start_multiplex_in(int fd)
{
	if (msgs2stderr && DEBUG_GTE(IO, 2))
		rprintf(FINFO, "[%s] io_start_multiplex_in(%d)\n", who_am_i(), fd);

	iobuf.in_multiplexed = 1; /* See also IN_MULTIPLEXED */
	io_start_buffering_in(fd);
}