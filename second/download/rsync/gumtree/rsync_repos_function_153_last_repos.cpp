void io_end_buffering_in(BOOL free_buffers)
{
	if (msgs2stderr && DEBUG_GTE(IO, 2)) {
		rprintf(FINFO, "[%s] io_end_buffering_in(IOBUF_%s_BUFS)\n",
			who_am_i(), free_buffers ? "FREE" : "KEEP");
	}

	if (free_buffers)
		free_xbuf(&iobuf.in);
	else
		iobuf.in.pos = iobuf.in.len = 0;

	iobuf.in_fd = -1;
}