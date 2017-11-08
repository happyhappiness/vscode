static void writefd_unbuffered(int fd,char *buf,size_t len)
{
	size_t n, total = 0;
	fd_set w_fds, r_fds;
	int maxfd, count, cnt, using_r_fds;
	struct timeval tv;

	no_flush++;

	while (total < len) {
		FD_ZERO(&w_fds);
		FD_SET(fd,&w_fds);
		maxfd = fd;

		if (msg_fd_in >= 0 && len-total >= contiguous_write_len) {
			FD_ZERO(&r_fds);
			FD_SET(msg_fd_in,&r_fds);
			if (msg_fd_in > maxfd)
				maxfd = msg_fd_in;
			using_r_fds = 1;
		} else
			using_r_fds = 0;

		tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		errno = 0;
		count = select(maxfd + 1, using_r_fds ? &r_fds : NULL,
			       &w_fds, NULL, &tv);

		if (count <= 0) {
			if (count < 0 && errno == EBADF)
				exit_cleanup(RERR_SOCKETIO);
			check_timeout();
			continue;
		}

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
				close_multiplexing_out();
			rsyserr(FERROR, errno,
				"writefd_unbuffered failed to write %ld bytes: phase \"%s\" [%s]",
				(long)len, io_write_phase, who_am_i());
			/* If the other side is sending us error messages, try
			 * to grab any messages they sent before they died. */
			while (fd == sock_f_out && io_multiplexing_in) {
				set_io_timeout(30);
				ignore_timeout = 0;
				readfd_unbuffered(sock_f_in, io_filesfrom_buf,
						  sizeof io_filesfrom_buf);
			}
			exit_cleanup(RERR_STREAMIO);
		}

		total += cnt;

		if (fd == sock_f_out) {
			if (io_timeout || am_generator)
				last_io_out = time(NULL);
			sleep_for_bwlimit(cnt);
		}
	}

	no_flush--;
}