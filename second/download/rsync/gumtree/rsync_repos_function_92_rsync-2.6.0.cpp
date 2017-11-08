int io_multiplex_write(enum logcode code, char *buf, size_t len)
{
	if (!io_multiplexing_out) return 0;

	io_flush();
	stats.total_written += (len+4);
	mplex_write(multiplex_out_fd, code, buf, len);
	return 1;
}