static int read_timeout(int fd, char *buf, size_t len)
{
	int n, ret=0;

	io_flush();

	while (ret == 0) {
		/* until we manage to read *something* */
		fd_set r_fds, w_fds;
		struct timeval tv;
		int fd_count = fd+1;
		int count;

		FD_ZERO(&r_fds);
		FD_SET(fd, &r_fds);
		if (io_error_fd != -1) {
			FD_SET(io_error_fd, &r_fds);
			if (io_error_fd >= fd_count) fd_count = io_error_fd+1;
		}
		if (io_filesfrom_f_out != -1) {
			int new_fd;
			if (io_filesfrom_buflen == 0) {
				if (io_filesfrom_f_in != -1) {
					FD_SET(io_filesfrom_f_in, &r_fds);
					new_fd = io_filesfrom_f_in;
				} else {
					io_filesfrom_f_out = -1;
					new_fd = -1;
				}
			} else {
				FD_ZERO(&w_fds);
				FD_SET(io_filesfrom_f_out, &w_fds);
				new_fd = io_filesfrom_f_out;
			}
			if (new_fd >= fd_count) fd_count = new_fd+1;
		}

		tv.tv_sec = io_timeout?io_timeout:SELECT_TIMEOUT;
		tv.tv_usec = 0;

		errno = 0;

		count = select(fd_count, &r_fds,
			       io_filesfrom_buflen? &w_fds : NULL,
			       NULL, &tv);

		if (count == 0) {
			check_timeout();
		}

		if (count <= 0) {
			if (errno == EBADF) {
				exit_cleanup(RERR_SOCKETIO);
			}
			continue;
		}

		if (io_error_fd != -1 && FD_ISSET(io_error_fd, &r_fds)) {
			read_error_fd();
		}

		if (io_filesfrom_f_out != -1) {
			if (io_filesfrom_buflen) {
				if (FD_ISSET(io_filesfrom_f_out, &w_fds)) {
					int l = write(io_filesfrom_f_out,
						      io_filesfrom_bp,
						      io_filesfrom_buflen);
					if (l > 0) {
						if (!(io_filesfrom_buflen -= l))
							io_filesfrom_bp = io_filesfrom_buf;
						else
							io_filesfrom_bp += l;
					} else {
						/* XXX should we complain? */
						io_filesfrom_f_out = -1;
					}
				}
			} else if (io_filesfrom_f_in != -1) {
				if (FD_ISSET(io_filesfrom_f_in, &r_fds)) {
					int l = read(io_filesfrom_f_in,
						     io_filesfrom_buf,
						     sizeof io_filesfrom_buf);
					if (l <= 0) {
						/* Send end-of-file marker */
						io_filesfrom_buf[0] = '\0';
						io_filesfrom_buf[1] = '\0';
						io_filesfrom_buflen = io_filesfrom_lastchar? 2 : 1;
						io_filesfrom_f_in = -1;
					} else {
						extern int eol_nulls;
						if (!eol_nulls) {
							char *s = io_filesfrom_buf + l;
							/* Transform CR and/or LF into '\0' */
							while (s-- > io_filesfrom_buf) {
								if (*s == '\n' || *s == '\r')
									*s = '\0';
							}
						}
						if (!io_filesfrom_lastchar) {
							/* Last buf ended with a '\0', so don't
							 * let this buf start with one. */
							while (l && !*io_filesfrom_bp)
								io_filesfrom_bp++, l--;
						}
						if (!l)
							io_filesfrom_bp = io_filesfrom_buf;
						else {
							char *f = io_filesfrom_bp;
							char *t = f;
							char *eob = f + l;
							/* Eliminate any multi-'\0' runs. */
							while (f != eob) {
								if (!(*t++ = *f++)) {
									while (f != eob && !*f)
										f++, l--;
								}
							}
							io_filesfrom_lastchar = f[-1];
						}
						io_filesfrom_buflen = l;
					}
				}
			}
		}

		if (!FD_ISSET(fd, &r_fds)) continue;

		n = read(fd, buf, len);

		if (n > 0) {
			buf += n;
			len -= n;
			ret += n;
			if (io_timeout)
				last_io = time(NULL);
			continue;
		} else if (n == 0) {
			whine_about_eof();
			return -1; /* doesn't return */
		} else if (n == -1) {
			if (errno == EINTR || errno == EWOULDBLOCK ||
			    errno == EAGAIN) 
				continue;
			die_from_readerr(errno);
		}
	}

	return ret;
}