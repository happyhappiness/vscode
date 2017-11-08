void send_msg(enum msgcode code, char *buf, int len)
{
	if (msg_fd_out < 0) {
		io_multiplex_write(code, buf, len);
		return;
	}
	msg_list_add(&msg2genr, code, buf, len);
	msg2genr_flush(NORMAL_FLUSH);
}