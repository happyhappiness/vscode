int read_filesfrom_line(int fd, char *fname)
{
	char ch, *s, *eob = fname + MAXPATHLEN - 1;
	int cnt;
	int reading_remotely = filesfrom_host != NULL;
	int nulls = eol_nulls || reading_remotely;

  start:
	s = fname;
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
			if (FD_ISSET(fd, &e_fds)) {
				rsyserr(FINFO, errno,
					"select exception on fd %d", fd);
			}
			continue;
		}
		if (cnt != 1)
			break;
		if (nulls? !ch : (ch == '\r' || ch == '\n')) {
			/* Skip empty lines if reading locally. */
			if (!reading_remotely && s == fname)
				continue;
			break;
		}
		if (s < eob)
			*s++ = ch;
	}
	*s = '\0';

	/* Dump comments. */
	if (*fname == '#' || *fname == ';')
		goto start;

	return s - fname;
}