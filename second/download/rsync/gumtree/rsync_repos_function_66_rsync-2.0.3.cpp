void io_end_buffering(int fd)
{
	if (io_buffer_count) {
		if (writefd_unbuffered(fd, io_buffer, 
				       io_buffer_count) != 
		    io_buffer_count) {
			rprintf(FERROR,"write failed\n");
			exit_cleanup(1);
		}
		io_buffer_count = 0;
	}
	free(io_buffer);
	io_buffer = NULL;
}