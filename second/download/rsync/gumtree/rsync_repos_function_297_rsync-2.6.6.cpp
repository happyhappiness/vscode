static char *getpassf(char *filename)
{
	STRUCT_STAT st;
	char buffer[512], *p;
	int fd, n, ok = 1;
	char *envpw = getenv("RSYNC_PASSWORD");

	if (!filename)
		return NULL;

	if ((fd = open(filename,O_RDONLY)) < 0) {
		rsyserr(FERROR, errno, "could not open password file \"%s\"",
			safe_fname(filename));
		if (envpw)
			rprintf(FERROR, "falling back to RSYNC_PASSWORD environment variable.\n");
		return NULL;
	}

	if (do_stat(filename, &st) == -1) {
		rsyserr(FERROR, errno, "stat(%s)", safe_fname(filename));
		ok = 0;
	} else if ((st.st_mode & 06) != 0) {
		rprintf(FERROR,"password file must not be other-accessible\n");
		ok = 0;
	} else if (am_root && st.st_uid != 0) {
		rprintf(FERROR,"password file must be owned by root when running as root\n");
		ok = 0;
	}
	if (!ok) {
		rprintf(FERROR,"continuing without password file\n");
		if (envpw)
			rprintf(FERROR, "using RSYNC_PASSWORD environment variable.\n");
		close(fd);
		return NULL;
	}

	if (envpw)
		rprintf(FERROR, "RSYNC_PASSWORD environment variable ignored\n");

	n = read(fd, buffer, sizeof buffer - 1);
	close(fd);
	if (n > 0) {
		buffer[n] = '\0';
		if ((p = strtok(buffer, "\n\r")) != NULL)
			return strdup(p);
	}

	return NULL;
}