void io_set_sock_fds(int f_in, int f_out)
{
	sock_f_in = f_in;
	sock_f_out = f_out;
}

/* Setup the fd used to receive MSG_* messages.  Only needed during the
 * early stages of being a local sender (up through the sending of the
 * file list) or when we're the generator (to fetch the messages from
 * the receiver). */
void set_msg_fd_in(int fd)
{
	msg_fd_in = fd;
}

/* Setup the fd used to send our MSG_* messages.  Only needed when
 * we're the receiver (to send our messages to the generator). */
void set_msg_fd_out(int fd)
{
	msg_fd_out = fd;
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
static void read_msg_fd(void)
{
	char buf[2048];
	size_t n;
	int fd = msg_fd_in;
	int tag, len;

	/* Temporarily disable msg_fd_in.  This is needed to avoid looping back
	 * to this routine from writefd_unbuffered(). */
	msg_fd_in = -1;

	read_loop(fd, buf, 4);
	tag = IVAL(buf, 0);

	len = tag & 0xFFFFFF;
	tag = (tag >> 24) - MPLEX_BASE;

	switch (tag) {
	case MSG_DONE:
		if (len != 0 || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		flist_ndx_push(&redo_list, -1);
		break;
	case MSG_REDO:
		if (len != 4 || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, 4);
		flist_ndx_push(&redo_list, IVAL(buf,0));
		break;
	case MSG_DELETED:
		if (len >= (int)sizeof buf || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, len);
		io_multiplex_write(MSG_DELETED, buf, len);
		break;
	case MSG_SUCCESS:
		if (len != 4 || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, len);
		if (remove_sent_files)
			io_multiplex_write(MSG_SUCCESS, buf, len);
		if (preserve_hard_links)
			flist_ndx_push(&hlink_list, IVAL(buf,0));
		break;
	case MSG_INFO:
	case MSG_ERROR:
	case MSG_LOG:
		while (len) {
			n = len;
