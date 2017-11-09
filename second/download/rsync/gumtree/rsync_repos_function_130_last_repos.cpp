static void safe_write(int fd, const char *buf, size_t len)
{
	int n;

	assert(fd != iobuf.out_fd);

	n = write(fd, buf, len);
	if ((size_t)n == len)
		return;
	if (n < 0) {
		if (errno != EINTR && errno != EWOULDBLOCK && errno != EAGAIN) {
		  write_failed:
			rsyserr(FERROR, errno,
				"safe_write failed to write %ld bytes to %s [%s]",
				(long)len, what_fd_is(fd), who_am_i());
			exit_cleanup(RERR_STREAMIO);
		}
	} else {
		buf += n;
		len -= n;
	}

	while (len) {
		struct timeval tv;
		fd_set w_fds;
		int cnt;

		FD_ZERO(&w_fds);
		FD_SET(fd, &w_fds);
		tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		cnt = select(fd + 1, NULL, &w_fds, NULL, &tv);
		if (cnt <= 0) {
			if (cnt < 0 && errno == EBADF) {
				rsyserr(FERROR, errno, "safe_write select failed on %s [%s]",
					what_fd_is(fd), who_am_i());
				exit_cleanup(RERR_FILEIO);
			}
			if (io_timeout)
				maybe_send_keepalive(time(NULL), MSK_ALLOW_FLUSH);
			continue;
		}

		if (FD_ISSET(fd, &w_fds)) {
			n = write(fd, buf, len);
			if (n < 0) {
				if (errno == EINTR)
					continue;
				goto write_failed;
			}
			buf += n;
			len -= n;
		}
	}
}