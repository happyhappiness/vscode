int msg_list_push(int flush_it_all)
{
	static int written = 0;
	struct timeval tv;
	fd_set fds;

	if (msg_fd_out < 0)
		return -1;

	while (msg_list_head) {
		struct msg_list *ml = msg_list_head;
		int n = write(msg_fd_out, ml->buf + written, ml->len - written);
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
		} else if ((written += n) == ml->len) {
			free(ml->buf);
			msg_list_head = ml->next;
			if (!msg_list_head)
				msg_list_tail = NULL;
			free(ml);
			written = 0;
		}
	}
	return 1;
}