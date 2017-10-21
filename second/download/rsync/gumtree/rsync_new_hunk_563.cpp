static int io_buffer_count;

void io_start_buffering(int fd)
{
	if (io_buffer) return;
	multiplex_out_fd = fd;
	io_buffer = (char *)malloc(IO_BUFFER_SIZE);
	if (!io_buffer) out_of_memory("writefd");
	io_buffer_count = 0;
}

/* write an message to a multiplexed stream. If this fails then rsync
   exits */
static void mplex_write(int fd, enum logcode code, char *buf, int len)
{
	char buffer[4096];
	int n = len;

	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);

	if (n > (sizeof(buffer)-4)) {
		n = sizeof(buffer)-4;
	}

	memcpy(&buffer[4], buf, n);
	writefd_unbuffered(fd, buffer, n+4);

	len -= n;
	buf += n;

	if (len) {
		writefd_unbuffered(fd, buf, len);
	}
}


void io_flush(void)
{
	int fd = multiplex_out_fd;
	if (!io_buffer_count || no_flush) return;

	if (io_multiplexing_out) {
