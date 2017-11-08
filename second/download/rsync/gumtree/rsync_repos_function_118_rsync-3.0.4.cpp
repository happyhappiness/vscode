static int read_timeout(int fd, char *buf, size_t len)
{
	int n, cnt = 0;

	io_flush(FULL_FLUSH);

	while (cnt == 0) {
		/* until we manage to read *something* */
		fd_set r_fds, w_fds;
		struct timeval tv;
		int maxfd = fd;
		int count;

		FD_ZERO(&r_fds);
		FD_ZERO(&w_fds);
		FD_SET(fd, &r_fds);
		if (io_filesfrom_f_out >= 0) {
			int new_fd;
			if (ff_buf.len == 0) {
				if (io_filesfrom_f_in >= 0) {
					FD_SET(io_filesfrom_f_in, &r_fds);
					new_fd = io_filesfrom_f_in;
				} else {
					io_filesfrom_f_out = -1;
					new_fd = -1;
				}
			} else {
				FD_SET(io_filesfrom_f_out, &w_fds);
				new_fd = io_filesfrom_f_out;
			}
			if (new_fd > maxfd)
				maxfd = new_fd;
		}

		tv.tv_sec = select_timeout;
		tv.tv_usec = 0;

		errno = 0;

		count = select(maxfd + 1, &r_fds, &w_fds, NULL, &tv);

		if (count <= 0) {
			if (errno == EBADF) {
				defer_forwarding_messages = 0;
				exit_cleanup(RERR_SOCKETIO);
			}
			check_timeout();
			continue;
		}

		if (io_filesfrom_f_out >= 0) {
			if (ff_buf.len) {
				if (FD_ISSET(io_filesfrom_f_out, &w_fds)) {
					int l = write(io_filesfrom_f_out,
						      ff_buf.buf + ff_buf.pos,
						      ff_buf.len);
					if (l > 0) {
						if (!(ff_buf.len -= l))
							ff_buf.pos = 0;
						else
							ff_buf.pos += l;
					} else if (errno != EINTR) {
						/* XXX should we complain? */
						io_filesfrom_f_out = -1;
					}
				}
			} else if (io_filesfrom_f_in >= 0) {
				if (FD_ISSET(io_filesfrom_f_in, &r_fds)) {
#ifdef ICONV_OPTION
					xbuf *ibuf = filesfrom_convert ? &iconv_buf : &ff_buf;
#else
					xbuf *ibuf = &ff_buf;
#endif
					int l = read(io_filesfrom_f_in, ibuf->buf, ibuf->size);
					if (l <= 0) {
						if (l == 0 || errno != EINTR) {
							/* Send end-of-file marker */
							memcpy(ff_buf.buf, "\0\0", 2);
							ff_buf.len = ff_lastchar? 2 : 1;
							ff_buf.pos = 0;
							io_filesfrom_f_in = -1;
						}
					} else {
#ifdef ICONV_OPTION
						if (filesfrom_convert) {
							iconv_buf.pos = 0;
							iconv_buf.len = l;
							iconvbufs(ic_send, &iconv_buf, &ff_buf,
							    ICB_EXPAND_OUT|ICB_INCLUDE_BAD|ICB_INCLUDE_INCOMPLETE);
							l = ff_buf.len;
						}
#endif
						if (!eol_nulls) {
							char *s = ff_buf.buf + l;
							/* Transform CR and/or LF into '\0' */
							while (s-- > ff_buf.buf) {
								if (*s == '\n' || *s == '\r')
									*s = '\0';
							}
						}
						if (!ff_lastchar) {
							/* Last buf ended with a '\0', so don't
							 * let this buf start with one. */
							while (l && ff_buf.buf[ff_buf.pos] == '\0')
								ff_buf.pos++, l--;
						}
						if (!l)
							ff_buf.pos = 0;
						else {
							char *f = ff_buf.buf + ff_buf.pos;
							char *t = f;
							char *eob = f + l;
							/* Eliminate any multi-'\0' runs. */
							while (f != eob) {
								if (!(*t++ = *f++)) {
									while (f != eob && !*f)
										f++, l--;
								}
							}
							ff_lastchar = f[-1];
						}
						ff_buf.len = l;
					}
				}
			}
		}

		if (!FD_ISSET(fd, &r_fds))
			continue;

		n = read(fd, buf, len);

		if (n <= 0) {
			if (n == 0)
				whine_about_eof(fd); /* Doesn't return. */
			if (errno == EINTR || errno == EWOULDBLOCK
			    || errno == EAGAIN)
				continue;

			/* Don't write errors on a dead socket. */
			if (fd == sock_f_in) {
				io_end_multiplex_out();
				rsyserr(FERROR_SOCKET, errno, "read error");
			} else
				rsyserr(FERROR, errno, "read error");
			exit_cleanup(RERR_STREAMIO);
		}

		buf += n;
		len -= n;
		cnt += n;

		if (fd == sock_f_in && io_timeout)
			last_io_in = time(NULL);
	}

	return cnt;
}