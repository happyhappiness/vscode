static int read_timeout(int fd, char *buf, int len)
{
	int n, ret=0;

	io_flush();

	while (ret == 0) {
		fd_set fds;
		struct timeval tv;

		FD_ZERO(&fds);
		FD_SET(fd, &fds);
		tv.tv_sec = io_timeout;
		tv.tv_usec = 0;

		if (select(fd+1, &fds, NULL, NULL, 
			   io_timeout?&tv:NULL) != 1) {
			check_timeout();
			continue;
		}

		n = read(fd, buf, len);

		if (n > 0) {
			stats.total_read += n;
			buf += n;
			len -= n;
			ret += n;
			if (io_timeout)
				last_io = time(NULL);
			continue;
		}

		if (n == -1 && errno == EINTR) {
			continue;
		}

		if (n == -1 && 
		    (errno == EAGAIN || errno == EWOULDBLOCK)) {
			/* this shouldn't happen, if it does then
			   sleep for a short time to prevent us
			   chewing too much CPU */
			u_sleep(100);
			continue;
		}

		if (n == 0) {
			if (eof_error) {
				rprintf(FERROR,"EOF in read_timeout\n");
			}
			exit_cleanup(1);
		}

		rprintf(FERROR,"read error: %s\n", strerror(errno));
		exit_cleanup(1);
	}

	return ret;
}