static size_t safe_read(int fd, char *buf, size_t len)
{
	size_t got = 0;

	assert(fd != iobuf.in_fd);

	while (1) {
		struct timeval tv;
		fd_set r_fds, e_fds;
		int cnt;

		FD_ZERO(&r_fds);
		FD_SET(fd, &r_fds);
		FD_ZERO(&e_fds);
		FD_SET(fd, &e_fds);
		tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		cnt = select(fd+1, &r_fds, NULL, &e_fds, &tv);
		if (cnt <= 0) {
			if (cnt < 0 && errno == EBADF) {
				rsyserr(FERROR, errno, "safe_read select failed [%s]",
					who_am_i());
				exit_cleanup(RERR_FILEIO);
			}
			check_timeout(1, MSK_ALLOW_FLUSH);
			continue;
		}

		/*if (FD_ISSET(fd, &e_fds))
			rprintf(FINFO, "select exception on fd %d\n", fd); */

		if (FD_ISSET(fd, &r_fds)) {
			int n = read(fd, buf + got, len - got);
			if (DEBUG_GTE(IO, 2))
				rprintf(FINFO, "[%s] safe_read(%d)=%ld\n", who_am_i(), fd, (long)n);
			if (n == 0)
				break;
			if (n < 0) {
				if (errno == EINTR)
					continue;
				rsyserr(FERROR, errno, "safe_read failed to read %ld bytes [%s]",
					(long)len, who_am_i());
				exit_cleanup(RERR_STREAMIO);
			}
			if ((got += (size_t)n) == len)
				break;
		}
	}

	return got;
}