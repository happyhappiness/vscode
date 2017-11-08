void send_msg(enum msgcode code, char *buf, int len)
{
	msg_list_add(code, buf, len);
	msg_list_push(NORMAL_FLUSH);
}