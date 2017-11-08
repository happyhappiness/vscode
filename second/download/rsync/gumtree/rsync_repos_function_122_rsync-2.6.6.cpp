int io_multiplex_write(enum msgcode code, char *buf, size_t len)
{
	if (!io_multiplexing_out)
		return 0;

	io_flush(NORMAL_FLUSH);
	stats.total_written += (len+4);
	mplex_write(code, buf, len);
	return 1;
}