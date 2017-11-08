void add_exclude_file(struct exclude_struct ***listp, const char *fname,
		      int fatal, int include)
{
	int fd;
	char line[MAXPATHLEN];
	char *eob = line + MAXPATHLEN - 1;
	extern int eol_nulls;

	if (!fname || !*fname)
		return;

	if (*fname != '-' || fname[1])
		fd = open(fname, O_RDONLY|O_BINARY);
	else
		fd = 0;
	if (fd < 0) {
		if (fatal) {
			rsyserr(FERROR, errno,
				"failed to open %s file %s",
				include ? "include" : "exclude",
				fname);
			exit_cleanup(RERR_FILEIO);
		}
		return;
	}

	while (1) {
		char ch, *s = line;
		int cnt;
		while (1) {
			if ((cnt = read(fd, &ch, 1)) <= 0) {
				if (cnt < 0 && errno == EINTR)
					continue;
				break;
			}
			if (eol_nulls? !ch : (ch == '\n' || ch == '\r'))
				break;
			if (s < eob)
				*s++ = ch;
		}
		*s = '\0';
		if (*line && *line != ';' && *line != '#') {
			/* Skip lines starting with semicolon or pound.
			 * It probably wouldn't cause any harm to not skip
			 * them but there's no need to save them. */
			add_exclude(listp, line, include);
		}
		if (cnt <= 0)
			break;
	}
	close(fd);
}