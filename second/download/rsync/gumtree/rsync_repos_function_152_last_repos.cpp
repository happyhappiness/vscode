BOOL io_start_buffering_in(int f_in)
{
	if (msgs2stderr && DEBUG_GTE(IO, 2))
		rprintf(FINFO, "[%s] io_start_buffering_in(%d)\n", who_am_i(), f_in);

	if (iobuf.in.buf) {
		if (iobuf.in_fd == -1)
			iobuf.in_fd = f_in;
		else
			assert(f_in == iobuf.in_fd);
		return False;
	}

	alloc_xbuf(&iobuf.in, ROUND_UP_1024(IO_BUFFER_SIZE));
	iobuf.in_fd = f_in;

	return True;
}