int io_end_multiplex_out(int mode)
{
	int ret = iobuf.out_empty_len ? iobuf.out_fd : -1;

	if (msgs2stderr && DEBUG_GTE(IO, 2))
		rprintf(FINFO, "[%s] io_end_multiplex_out(mode=%d)\n", who_am_i(), mode);

	if (mode != MPLX_TO_BUFFERED)
		io_end_buffering_out(mode);
	else
		io_flush(FULL_FLUSH);

	iobuf.out.len = 0;
	iobuf.out_empty_len = 0;
	if (got_kill_signal > 0) /* Just in case... */
		handle_kill_signal(False);
	got_kill_signal = -1;

	return ret;
}