static int io_buffer_count;

void io_start_buffering(int fd)
{
	if (io_buffer) return;
	multiplex_out_fd = fd;
	io_buffer = new_array(char, IO_BUFFER_SIZE);
	if (!io_buffer) out_of_memory("writefd");
	io_buffer_count = 0;
}

/**
 * Write an message to a multiplexed stream. If this fails then rsync
