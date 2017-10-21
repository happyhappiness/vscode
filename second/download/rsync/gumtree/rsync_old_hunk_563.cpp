static int io_buffer_count;

void io_start_buffering(int fd)
{
	if (io_buffer) return;
	multiplex_out_fd = fd;
	io_buffer = (char *)malloc(IO_BUFFER_SIZE+4);
	if (!io_buffer) out_of_memory("writefd");
	io_buffer_count = 0;

	/* leave room for the multiplex header in case it's needed */
	io_buffer += 4;
}

void io_flush(void)
{
	int fd = multiplex_out_fd;
	if (!io_buffer_count || no_flush) return;

	if (io_multiplexing_out) {
