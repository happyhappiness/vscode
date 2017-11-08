void send_msg(enum msgcode code, char *buf, int len)
{
	if (msg_fd_out < 0) {
		io_multiplex_write(code, buf, len);
		return;
	}
	msg_list_add(code, buf, len);
	msg_list_flush(NORMAL_FLUSH);
}