
	va_start(ap, format);
	len = vsnprintf(buf, sizeof buf, format, ap);
	va_end(ap);

	if (len < 0)
		exit_cleanup(RERR_STREAMIO);

	if (len > (int)sizeof buf) {
		rprintf(FERROR, "io_printf() was too long for the buffer.\n");
		exit_cleanup(RERR_STREAMIO);
	}

	write_sbuf(fd, buf);
}

/** Setup for multiplexing a MSG_* stream with the data stream. */
void io_start_multiplex_out(void)
{
	io_flush(NORMAL_FLUSH);
	io_start_buffering_out(sock_f_out);
	io_multiplexing_out = 1;
}

/** Setup for multiplexing a MSG_* stream with the data stream. */
void io_start_multiplex_in(void)
{
	io_flush(NORMAL_FLUSH);
	io_start_buffering_in(sock_f_in);
	io_multiplexing_in = 1;
}

/** Write an message to the multiplexed data stream. */
int io_multiplex_write(enum msgcode code, const char *buf, size_t len, int convert)
{
	if (!io_multiplexing_out)
		return 0;
	io_flush(NORMAL_FLUSH);
	stats.total_written += (len+4);
	mplex_write(sock_f_out, code, buf, len, convert);
	return 1;
}

void io_end_multiplex_in(void)
{
	io_multiplexing_in = 0;
	io_end_buffering_in();
}

/** Stop output multiplexing. */
void io_end_multiplex_out(void)
{
	io_multiplexing_out = 0;
	io_end_buffering_out();
}

void start_write_batch(int fd)
{
	/* Some communication has already taken place, but we don't
	 * enable batch writing until here so that we can write a
