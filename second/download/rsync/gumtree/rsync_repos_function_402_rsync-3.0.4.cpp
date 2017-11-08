static const char *getpassf(const char *filename)
{
	STRUCT_STAT st;
	char buffer[512], *p;
	int fd, n, ok = 1;
	const char *envpw = getenv("RSYNC_PASSWORD");

	if (!filename)
		return NULL;

	if ((fd = open(filename,O_RDONLY)) < 0) {
		rsyserr(FWARNING, errno, "could not open password file \"%s\"",
			filename);
		if (envpw)
			rprintf(FINFO, "falling back to RSYNC_PASSWORD environment variable.\n");
		return NULL;
	}

	if (do_stat(filename, &st) == -1) {
		rsyserr(FWARNING, errno, "stat(%s)", filename);
		ok = 0;
	} else if ((st.st_mode & 06) != 0) {
		rprintf(FWARNING, "password file must not be other-accessible\n");
		ok = 0;
	} else if (MY_UID() == 0 && st.st_uid != 0) {
		rprintf(FWARNING, "password file must be owned by root when running as root\n");
		ok = 0;
	}
	if (!ok) {
		close(fd);
		rprintf(FWARNING, "continuing without password file\n");
		if (envpw)
			rprintf(FINFO, "falling back to RSYNC_PASSWORD environment variable.\n");
		return NULL;
	}

	n = read(fd, buffer, sizeof buffer - 1);
	close(fd);
	if (n > 0) {
		buffer[n] = '\0';
		if ((p = strtok(buffer, "\n\r")) != NULL)
			return strdup(p);
	}

	return NULL;
}