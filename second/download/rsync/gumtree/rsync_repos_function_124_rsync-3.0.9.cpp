void maybe_flush_socket(int important)
{
	if (iobuf_out && iobuf_out_cnt
	 && (important || time(NULL) - last_io_out >= 5))
		io_flush(NORMAL_FLUSH);
}