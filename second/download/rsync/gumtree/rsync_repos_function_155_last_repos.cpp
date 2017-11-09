void maybe_flush_socket(int important)
{
	if (flist_eof && iobuf.out.buf && iobuf.out.len > iobuf.out_empty_len
	 && (important || time(NULL) - last_io_out >= 5))
		io_flush(NORMAL_FLUSH);
}