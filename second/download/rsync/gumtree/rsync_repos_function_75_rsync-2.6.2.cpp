int read_filesfrom_line(int fd, char *fname)
{
	char ch, *s, *eob = fname + MAXPATHLEN - 1;
	int cnt;
	extern int io_timeout;
	extern int eol_nulls;
	extern char *remote_filesfrom_file;
	int reading_remotely = remote_filesfrom_file != NULL;
	int nulls = eol_nulls || reading_remotely;

  start:
	s = fname;
	while (1) {
		cnt = read(fd, &ch, 1);
		if (cnt < 0 && (errno == EWOULDBLOCK
		  || errno == EINTR || errno == EAGAIN)) {
			struct timeval tv;
			fd_set fds;
			FD_ZERO(&fds);
			FD_SET(fd, &fds);
			tv.tv_sec = io_timeout? io_timeout : SELECT_TIMEOUT;
			tv.tv_usec = 0;
			if (!select(fd+1, &fds, NULL, NULL, &tv))
				check_timeout();
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