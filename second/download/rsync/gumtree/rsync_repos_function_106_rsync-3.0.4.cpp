static void msg_flush(void)
{
	if (am_generator) {
		while (msg_queue.head && io_multiplexing_out)
			stats.total_written += flush_a_msg(sock_f_out) + 4;
	} else {
		while (msg_queue.head)
			(void)flush_a_msg(msg_fd_out);
	}
}