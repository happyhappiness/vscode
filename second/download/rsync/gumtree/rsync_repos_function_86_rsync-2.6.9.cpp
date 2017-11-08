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