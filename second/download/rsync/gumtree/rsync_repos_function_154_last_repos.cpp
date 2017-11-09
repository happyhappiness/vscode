void io_end_buffering_out(BOOL free_buffers)
{
	if (msgs2stderr && DEBUG_GTE(IO, 2)) {
		rprintf(FINFO, "[%s] io_end_buffering_out(IOBUF_%s_BUFS)\n",
			who_am_i(), free_buffers ? "FREE" : "KEEP");
	}

	io_flush(FULL_FLUSH);

	if (free_buffers) {
		free_xbuf(&iobuf.out);
		free_xbuf(&iobuf.msg);
	}

	iobuf.out_fd = -1;
}