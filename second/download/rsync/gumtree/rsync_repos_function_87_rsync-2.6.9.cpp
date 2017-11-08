int send_msg(enum msgcode code, char *buf, int len)
{
	if (msg_fd_out < 0) {
		if (!defer_forwarding_messages)
			return io_multiplex_write(code, buf, len);
		if (!io_multiplexing_out)
			return 0;
		msg_list_add(&msg2sndr, code, buf, len);
		return 1;
	}
	msg_list_add(&msg2genr, code, buf, len);
	msg2genr_flush(NORMAL_FLUSH);
	return 1;
}