void io_set_sock_fds(int f_in, int f_out)
{
	sock_f_in = f_in;
	sock_f_out = f_out;
}

/** Setup the fd used to receive MSG_* messages.  Only needed when
 * we're the generator because the sender and receiver both use the
 * multiplexed I/O setup. */
void set_msg_fd_in(int fd)
{
	msg_fd_in = fd;
}

/** Setup the fd used to send our MSG_* messages.  Only needed when
 * we're the receiver because the generator and the sender both use
 * the multiplexed I/O setup. */
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
		exit_cleanup(RERR_MALLOC);
	ml->next = NULL;
	if (!(ml->buf = new_array(char, len+4)))
		exit_cleanup(RERR_MALLOC);
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
	msg_list_add(code, buf, len);
	msg_list_push(NORMAL_FLUSH);
}

/** Read a message from the MSG_* fd and dispatch it.  This is only
 * called by the generator. */
static void read_msg_fd(void)
{
	char buf[2048];
	size_t n;
	int fd = msg_fd_in;
	int tag, len;

	/* Temporarily disable msg_fd_in.  This is needed to avoid looping back
	 * to this routine from read_timeout() and writefd_unbuffered(). */
	msg_fd_in = -1;

	read_loop(fd, buf, 4);
	tag = IVAL(buf, 0);

	len = tag & 0xFFFFFF;
	tag = (tag >> 24) - MPLEX_BASE;

	switch (tag) {
	case MSG_DONE:
		if (len != 0) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		redo_list_add(-1);
		break;
	case MSG_REDO:
		if (len != 4) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, 4);
		redo_list_add(IVAL(buf,0));
		break;
	case MSG_INFO:
	case MSG_ERROR:
	case MSG_LOG:
		while (len) {
			n = len;
