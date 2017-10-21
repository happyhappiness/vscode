{
	msg_fd_out = fd;
	set_nonblocking(msg_fd_out);
}

/* Add a message to the pending MSG_* list. */
static void msg_list_add(struct msg_list *lst, int code, char *buf, int len)
{
	struct msg_list_item *m;
	int sz = len + 4 + sizeof m[0] - 1;

	if (!(m = (struct msg_list_item *)new_array(char, sz)))
		out_of_memory("msg_list_add");
	m->next = NULL;
	m->len = len + 4;
	SIVAL(m->buf, 0, ((code+MPLEX_BASE)<<24) | len);
	memcpy(m->buf + 4, buf, len);
	if (lst->tail)
		lst->tail->next = m;
	else
		lst->head = m;
	lst->tail = m;
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
		if (remove_source_files)
			decrement_active_files(IVAL(buf,0));
		flist_ndx_push(&redo_list, IVAL(buf,0));
		break;
	case MSG_DELETED:
		if (len >= (int)sizeof buf || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, len);
		send_msg(MSG_DELETED, buf, len);
		break;
	case MSG_SUCCESS:
		if (len != 4 || !am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		read_loop(fd, buf, len);
		if (remove_source_files) {
			decrement_active_files(IVAL(buf,0));
			send_msg(MSG_SUCCESS, buf, len);
		}
		if (preserve_hard_links)
			flist_ndx_push(&hlink_list, IVAL(buf,0));
		break;
	case MSG_SOCKERR:
		if (!am_generator) {
			rprintf(FERROR, "invalid message %d:%d\n", tag, len);
			exit_cleanup(RERR_STREAMIO);
		}
		close_multiplexing_out();
		/* FALL THROUGH */
	case MSG_INFO:
	case MSG_ERROR:
	case MSG_LOG:
		while (len) {
			n = len;
			if (n >= sizeof buf)
				n = sizeof buf - 1;
			read_loop(fd, buf, n);
			rwrite(tag, buf, n);
			len -= n;
		}
		break;
	default:
		rprintf(FERROR, "unknown message %d:%d [%s]\n",
			tag, len, who_am_i());
		exit_cleanup(RERR_STREAMIO);
	}

	msg_fd_in = fd;
}

/* This is used by the generator to limit how many file transfers can
 * be active at once when --remove-source-files is specified.  Without
 * this, sender-side deletions were mostly happening at the end. */
void increment_active_files(int ndx, int itemizing, enum logcode code)
{
	/* TODO: tune these limits? */
	while (active_filecnt >= (active_bytecnt >= 128*1024 ? 10 : 50)) {
		if (hlink_list.head)
			check_for_finished_hlinks(itemizing, code);
		read_msg_fd();
	}

	active_filecnt++;
	active_bytecnt += the_file_list->files[ndx]->length;
}

void decrement_active_files(int ndx)
{
	active_filecnt--;
	active_bytecnt -= the_file_list->files[ndx]->length;
}

/* Try to push messages off the list onto the wire.  If we leave with more
 * to do, return 0.  On error, return -1.  If everything flushed, return 1.
 * This is only active in the receiver. */
static int msg2genr_flush(int flush_it_all)
{
	static int written = 0;
	struct timeval tv;
	fd_set fds;

	if (msg_fd_out < 0)
		return -1;

	while (msg2genr.head) {
		struct msg_list_item *m = msg2genr.head;
		int n = write(msg_fd_out, m->buf + written, m->len - written);
		if (n < 0) {
			if (errno == EINTR)
				continue;
			if (errno != EWOULDBLOCK && errno != EAGAIN)
				return -1;
			if (!flush_it_all)
				return 0;
			FD_ZERO(&fds);
			FD_SET(msg_fd_out, &fds);
			tv.tv_sec = select_timeout;
			tv.tv_usec = 0;
			if (!select(msg_fd_out+1, NULL, &fds, NULL, &tv))
				check_timeout();
		} else if ((written += n) == m->len) {
			msg2genr.head = m->next;
			if (!msg2genr.head)
				msg2genr.tail = NULL;
			free(m);
			written = 0;
		}
	}
	return 1;
}

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

int get_redo_num(int itemizing, enum logcode code)
{
	while (1) {
		if (hlink_list.head)
			check_for_finished_hlinks(itemizing, code);
		if (redo_list.head)
			break;
		read_msg_fd();
	}

	return flist_ndx_pop(&redo_list);
}

int get_hlink_num(void)
{
	return flist_ndx_pop(&hlink_list);
