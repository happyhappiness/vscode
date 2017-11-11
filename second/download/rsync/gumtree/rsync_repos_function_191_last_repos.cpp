int io_end_multiplex_in(int mode)
{
	int ret = iobuf.in_multiplexed ? iobuf.in_fd : -1;

	if (msgs2stderr && DEBUG_GTE(IO, 2))
		rprintf(FINFO, "[%s] io_end_multiplex_in(mode=%d)\n", who_am_i(), mode);

	iobuf.in_multiplexed = 0;
	if (mode == MPLX_SWITCHING)
		iobuf.raw_input_ends_before = 0;
	else
		assert(iobuf.raw_input_ends_before == 0);
	if (mode != MPLX_TO_BUFFERED)
		io_end_buffering_in(mode);

	return ret;
}