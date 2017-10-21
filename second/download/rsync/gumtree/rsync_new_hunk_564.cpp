
/* setup for multiplexing an error stream with the data stream */
void io_start_multiplex_in(int fd)
{
	multiplex_in_fd = fd;
	io_flush();
	io_multiplexing_in = 1;
}

/* write an message to the multiplexed error stream */
int io_multiplex_write(enum logcode code, char *buf, int len)
{
	if (!io_multiplexing_out) return 0;

	io_flush();
	stats.total_written += (len+4);
	mplex_write(multiplex_out_fd, code, buf, len);
	return 1;
}

/* write a message to the special error fd */
int io_error_write(int f, enum logcode code, char *buf, int len)
{
	if (f == -1) return 0;
	mplex_write(f, code, buf, len);
	return 1;
}

/* stop output multiplexing */
void io_multiplexing_close(void)
{
	io_multiplexing_out = 0;
}

void io_close_input(int fd)
{
	buffer_f_in = -1;
}
