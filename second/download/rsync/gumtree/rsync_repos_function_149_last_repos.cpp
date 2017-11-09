int read_line(int fd, char *buf, size_t bufsiz, int flags)
{
	char ch, *s, *eob;

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
		/* We avoid read_byte() for files because files can return an EOF. */
		if (fd == iobuf.in_fd)
			ch = read_byte(fd);
		else if (safe_read(fd, &ch, 1) == 0)
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
			  ICB_INCLUDE_BAD | ICB_INCLUDE_INCOMPLETE | ICB_INIT);
		outbuf.buf[outbuf.len] = '\0';
		return outbuf.len;
	}
#endif

	return s - buf;
}