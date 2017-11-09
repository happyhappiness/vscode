BOOL io_start_buffering_out(int f_out)
{
	if (msgs2stderr && DEBUG_GTE(IO, 2))
		rprintf(FINFO, "[%s] io_start_buffering_out(%d)\n", who_am_i(), f_out);

	if (iobuf.out.buf) {
		if (iobuf.out_fd == -1)
			iobuf.out_fd = f_out;
		else
			assert(f_out == iobuf.out_fd);
		return False;
	}

	alloc_xbuf(&iobuf.out, ROUND_UP_1024(IO_BUFFER_SIZE * 2));
	iobuf.out_fd = f_out;

	return True;
}