}


static char *io_buffer;
static int io_buffer_count;

void io_start_buffering_out(int fd)
{
	if (io_buffer) return;
	multiplex_out_fd = fd;
	io_buffer = new_array(char, IO_BUFFER_SIZE);
	if (!io_buffer) out_of_memory("writefd");
	io_buffer_count = 0;
}

void io_start_buffering_in(int fd)
{
	multiplex_in_fd = fd;
}

/**
 * Write an message to a multiplexed stream. If this fails then rsync
 * exits.
 **/
static void mplex_write(int fd, enum msgcode code, char *buf, size_t len)
{
	char buffer[4096];
	size_t n = len;

	SIVAL(buffer, 0, ((MPLEX_BASE + (int)code)<<24) + len);

