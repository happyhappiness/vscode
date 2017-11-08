void io_flush(int flush_it_all)
{
	int fd = multiplex_out_fd;
	
	msg_list_push(flush_it_all);

	if (!io_buffer_count || no_flush)
		return;

	if (io_multiplexing_out)
		mplex_write(fd, MSG_DATA, io_buffer, io_buffer_count);
	else
		writefd_unbuffered(fd, io_buffer, io_buffer_count);
	io_buffer_count = 0;
}