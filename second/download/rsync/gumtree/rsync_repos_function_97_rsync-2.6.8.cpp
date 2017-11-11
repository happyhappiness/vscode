void maybe_flush_socket(void)
{
	if (iobuf_out && iobuf_out_cnt && time(NULL) - last_io_out >= 5)
		io_flush(NORMAL_FLUSH);
}