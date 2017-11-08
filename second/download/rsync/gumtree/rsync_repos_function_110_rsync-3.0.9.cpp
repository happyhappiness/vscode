int send_msg(enum msgcode code, const char *buf, int len, int convert)
{
	if (msg_fd_out < 0) {
		if (!defer_forwarding_messages)
			return io_multiplex_write(code, buf, len, convert);
		if (!io_multiplexing_out)
			return 0;
		msg_list_add(&msg_queue, code, buf, len, convert);
		return 1;
	}
	if (flist_forward_from >= 0)
		msg_list_add(&msg_queue, code, buf, len, convert);
	else
		mplex_write(msg_fd_out, code, buf, len, convert);
	return 1;
}