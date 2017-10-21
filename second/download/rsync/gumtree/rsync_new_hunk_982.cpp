
	va_start(ap, format);
	len = vsnprintf(buf, sizeof buf, format, ap);
	va_end(ap);

	if (len < 0)
		exit_cleanup(RERR_PROTOCOL);

	if (len > (int)sizeof buf) {
		rprintf(FERROR, "io_printf() was too long for the buffer.\n");
		exit_cleanup(RERR_PROTOCOL);
	}

	write_sbuf(fd, buf);
}

/* Setup for multiplexing a MSG_* stream with the data stream. */
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

/* Setup for multiplexing a MSG_* stream with the data stream. */
void io_start_multiplex_in(int fd)
{
	if (msgs2stderr && DEBUG_GTE(IO, 2))
		rprintf(FINFO, "[%s] io_start_multiplex_in(%d)\n", who_am_i(), fd);

	iobuf.in_multiplexed = 1; /* See also IN_MULTIPLEXED */
	io_start_buffering_in(fd);
}

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

void start_write_batch(int fd)
{
	/* Some communication has already taken place, but we don't
	 * enable batch writing until here so that we can write a
