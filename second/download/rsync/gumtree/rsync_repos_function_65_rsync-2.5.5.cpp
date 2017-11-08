static int read_timeout (int fd, char *buf, size_t len)
{
	int n, ret=0;

	io_flush();

	while (ret == 0) {
		/* until we manage to read *something* */
		fd_set fds;
		struct timeval tv;
		int fd_count = fd+1;
		int count;

		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		if (io_error_fd != -1) {
			FD_SET(io_error_fd, &fds);
			if (io_error_fd > fd) fd_count = io_error_fd+1;
		}

		tv.tv_sec = io_timeout?io_timeout:SELECT_TIMEOUT;
		tv.tv_usec = 0;

		errno = 0;

		count = select(fd_count, &fds, NULL, NULL, &tv);

		if (count == 0) {
			check_timeout();
		}

		if (count <= 0) {
			if (errno == EBADF) {
				exit_cleanup(RERR_SOCKETIO);
			}
			continue;
		}

		if (io_error_fd != -1 && FD_ISSET(io_error_fd, &fds)) {
			read_error_fd();
		}

		if (!FD_ISSET(fd, &fds)) continue;

		n = read(fd, buf, len);

		if (n > 0) {
			buf += n;
			len -= n;
			ret += n;
			if (io_timeout)
				last_io = time(NULL);
			continue;
		} else if (n == 0) {
			whine_about_eof ();
			return -1; /* doesn't return */
		} else if (n == -1) {
			if (errno == EINTR || errno == EWOULDBLOCK ||
			    errno == EAGAIN) 
				continue;
			else
				die_from_readerr (errno);
		}
	}

	return ret;
}