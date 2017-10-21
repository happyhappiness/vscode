
/* setup for multiplexing an error stream with the data stream */
void io_start_multiplex_in(int fd)
{
	multiplex_in_fd = fd;
	io_flush();
	if (read_buffer_len) {
		fprintf(stderr,"ERROR: data in read buffer at mplx start\n");
		exit_cleanup(RERR_STREAMIO);
	}

	io_multiplexing_in = 1;
}

/* write an message to the error stream */
int io_multiplex_write(int f, char *buf, size_t len)
{
	if (!io_multiplexing_out) return 0;

	io_flush();

	SIVAL(io_buffer-4, 0, ((MPLEX_BASE + f)<<24) + len);
	memcpy(io_buffer, buf, len);

	stats.total_written += (len+4);

	writefd_unbuffered(multiplex_out_fd, io_buffer-4, len+4);
	return 1;
}

void io_close_input(int fd)
{
	buffer_f_in = -1;
}
