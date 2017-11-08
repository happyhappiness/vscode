static void writefd_unbuffered(int fd, const char *buf, size_t len)
{
	size_t n, total = 0;
	fd_set w_fds, r_fds, e_fds;
	int maxfd, count, cnt, using_r_fds;
	int defer_inc = 0;
	struct timeval tv;

	if (no_flush++)
		defer_forwarding_messages++, defer_inc++;

	while (total < len) {
		FD_ZERO(&w_fds);
		FD_SET(fd, &w_fds);
		FD_ZERO(&e_fds);
		FD_SET(fd, &e_fds);
		maxfd = fd;

		if (msg_fd_in >= 0) {
			FD_ZERO(&r_fds);
			FD_SET(msg_fd_in, &r_fds);
			if (msg_fd_in > maxfd)
				maxfd = msg_fd_in;
			using_r_fds = 1;
		} else
			using_r_fds = 0;

		tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		errno = 0;
		count = select(maxfd + 1, using_r_fds ? &r_fds : NULL,
			       &w_fds, &e_fds, &tv);

		if (count <= 0) {
			if (count < 0 && errno == EBADF)
				exit_cleanup(RERR_SOCKETIO);
			check_timeout();
			continue;
		}

		/*if (FD_ISSET(fd, &e_fds))
			rprintf(FINFO, "select exception on fd %d\n", fd); */

		if (using_r_fds && FD_ISSET(msg_fd_in, &r_fds))
			read_msg_fd();

		if (!FD_ISSET(fd, &w_fds))
			continue;

		n = len - total;
		if (bwlimit_writemax && n > bwlimit_writemax)
			n = bwlimit_writemax;
		cnt = write(fd, buf + total, n);

		if (cnt <= 0) {
			if (cnt < 0) {
				if (errno == EINTR)
					continue;
				if (errno == EWOULDBLOCK || errno == EAGAIN) {
					msleep(1);
					continue;
				}
			}

			/* Don't try to write errors back across the stream. */
			if (fd == sock_f_out)
				io_end_multiplex_out();
			/* Don't try to write errors down a failing msg pipe. */
			if (am_server && fd == msg_fd_out)
				exit_cleanup(RERR_STREAMIO);
			rsyserr(FERROR, errno,
				"writefd_unbuffered failed to write %ld bytes to %s [%s]",
				(long)len, what_fd_is(fd), who_am_i());
			/* If the other side is sending us error messages, try
			 * to grab any messages they sent before they died. */
			while (!am_server && fd == sock_f_out && io_multiplexing_in) {
				char buf[1024];
				set_io_timeout(30);
				ignore_timeout = 0;
				readfd_unbuffered(sock_f_in, buf, sizeof buf);
			}
			exit_cleanup(RERR_STREAMIO);
		}

		total += cnt;
		defer_forwarding_messages++, defer_inc++;

		if (fd == sock_f_out) {
			if (io_timeout || am_generator)
				last_io_out = time(NULL);
			sleep_for_bwlimit(cnt);
		}
	}

	no_flush--;
	if (keep_defer_forwarding)
		defer_inc--;
	if (!(defer_forwarding_messages -= defer_inc) && !no_flush)
		msg_flush();
}