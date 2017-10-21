	set_nonblocking(msg_fd_out);
}

/* Add a message to the pending MSG_* list. */
static void msg_list_add(int code, char *buf, int len)
{
	struct msg_list *ml;

	if (!(ml = new(struct msg_list)))
		out_of_memory("msg_list_add");
	ml->next = NULL;
	if (!(ml->buf = new_array(char, len+4)))
		out_of_memory("msg_list_add");
	SIVAL(ml->buf, 0, ((code+MPLEX_BASE)<<24) | len);
	memcpy(ml->buf+4, buf, len);
	ml->len = len+4;
	if (msg_list_tail)
		msg_list_tail->next = ml;
	else
		msg_list_head = ml;
	msg_list_tail = ml;
}

void send_msg(enum msgcode code, char *buf, int len)
{
	if (msg_fd_out < 0) {
		io_multiplex_write(code, buf, len);
		return;
	}
	msg_list_add(code, buf, len);
	msg_list_push(NORMAL_FLUSH);
}

/* Read a message from the MSG_* fd and handle it.  This is called either
 * during the early stages of being a local sender (up through the sending
 * of the file list) or when we're the generator (to fetch the messages
 * from the receiver). */
