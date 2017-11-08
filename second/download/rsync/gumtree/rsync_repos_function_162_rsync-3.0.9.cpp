int io_multiplex_write(enum msgcode code, const char *buf, size_t len, int convert)
{
	if (!io_multiplexing_out)
		return 0;
	io_flush(NORMAL_FLUSH);
	stats.total_written += (len+4);
	mplex_write(sock_f_out, code, buf, len, convert);
	return 1;
}