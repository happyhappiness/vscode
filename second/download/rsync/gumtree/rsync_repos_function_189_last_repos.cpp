void io_start_multiplex_out(int fd)
{
	io_flush(FULL_FLUSH);

	if (msgs2stderr && DEBUG_GTE(IO, 2))
		rprintf(FINFO, "[%s] io_start_multiplex_out(%d)\n", who_am_i(), fd);

	if (!iobuf.msg.buf)
		alloc_xbuf(&iobuf.msg, ROUND_UP_1024(IO_BUFFER_SIZE));

	iobuf.out_empty_len = 4; /* See also OUT_MULTIPLEXED */
	io_start_buffering_out(fd);
	got_kill_signal = 0;

	iobuf.raw_data_header_pos = iobuf.out.pos + iobuf.out.len;
	iobuf.out.len += 4;
}