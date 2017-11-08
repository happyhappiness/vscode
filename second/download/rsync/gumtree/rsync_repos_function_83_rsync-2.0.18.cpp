int io_multiplex_write(int f, char *buf, int len)
{
	if (!io_multiplexing_out) return 0;

	io_flush();

	SIVAL(io_buffer-4, 0, ((MPLEX_BASE + f)<<24) + len);
	memcpy(io_buffer, buf, len);

	writefd_unbuffered(multiplex_out_fd, io_buffer-4, len+4);
	return 1;
}