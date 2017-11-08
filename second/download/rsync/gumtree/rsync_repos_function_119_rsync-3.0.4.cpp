int read_line(int fd, char *buf, size_t bufsiz, int flags)
{
	char ch, *s, *eob;
	int cnt;

#ifdef ICONV_OPTION
	if (flags & RL_CONVERT && iconv_buf.size < bufsiz)
		realloc_xbuf(&iconv_buf, bufsiz + 1024);
#endif

  start:
#ifdef ICONV_OPTION
	s = flags & RL_CONVERT ? iconv_buf.buf : buf;
#else
	s = buf;
#endif
	eob = s + bufsiz - 1;
	while (1) {
		cnt = read(fd, &ch, 1);
		if (cnt < 0 && (errno == EWOULDBLOCK
		  || errno == EINTR || errno == EAGAIN)) {
			struct timeval tv;
			fd_set r_fds, e_fds;
			FD_ZERO(&r_fds);
			FD_SET(fd, &r_fds);
			FD_ZERO(&e_fds);
			FD_SET(fd, &e_fds);
			tv.tv_sec = select_timeout;
			tv.tv_usec = 0;
			if (!select(fd+1, &r_fds, NULL, &e_fds, &tv))
				check_timeout();
			/*if (FD_ISSET(fd, &e_fds))
				rprintf(FINFO, "select exception on fd %d\n", fd); */
			continue;
		}
		if (cnt != 1)
			break;
		if (flags & RL_EOL_NULLS ? ch == '\0' : (ch == '\r' || ch == '\n')) {
			/* Skip empty lines if dumping comments. */
			if (flags & RL_DUMP_COMMENTS && s == buf)
				continue;
			break;
		}
		if (s < eob)
			*s++ = ch;
	}
	*s = '\0';

	if (flags & RL_DUMP_COMMENTS && (*buf == '#' || *buf == ';'))
		goto start;

#ifdef ICONV_OPTION
	if (flags & RL_CONVERT) {
		xbuf outbuf;
		INIT_XBUF(outbuf, buf, 0, bufsiz);
		iconv_buf.pos = 0;
		iconv_buf.len = s - iconv_buf.buf;
		iconvbufs(ic_recv, &iconv_buf, &outbuf,
			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE);
		outbuf.buf[outbuf.len] = '\0';
		return outbuf.len;
	}
#endif

	return s - buf;
}