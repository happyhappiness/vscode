void io_start_multiplex_in(int fd)
{
	multiplex_in_fd = fd;
	io_flush();
	if (read_buffer_len) {
		fprintf(stderr,"ERROR: data in read buffer at mplx start\n");
		exit_cleanup(1);
	}

	io_multiplexing_in = 1;
}