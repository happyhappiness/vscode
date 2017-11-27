static char *ps_get_cmdline (pid_t pid, char *name, char *buf, size_t buf_len)
{
	char  *buf_ptr;
	size_t len;

	char file[PATH_MAX];
	int  fd;

	size_t n;

	if ((pid < 1) || (NULL == buf) || (buf_len < 2))
		return NULL;

	ssnprintf (file, sizeof (file), "/proc/%u/cmdline", pid);

	fd = open (file, O_RDONLY);
	if (fd < 0) {
		char errbuf[4096];
		WARNING ("processes plugin: Failed to open `%s': %s.", file,
				sstrerror (errno, errbuf, sizeof (errbuf)));
		return NULL;
	}

	buf_ptr = buf;
	len     = buf_len;

	n = 0;

	while (42) {
		ssize_t status;

		status = read (fd, (void *)buf_ptr, len);

		if (status < 0) {
			char errbuf[4096];

			if ((EAGAIN == errno) || (EINTR == errno))
				continue;

			WARNING ("processes plugin: Failed to read from `%s': %s.", file,
					sstrerror (errno, errbuf, sizeof (errbuf)));
			close (fd);
			return NULL;
		}

		n += status;

		if (status == 0)
			break;

		buf_ptr += status;
		len     -= status;

		if (len <= 0)
			break;
	}

	close (fd);

	if (0 == n) {
		/* cmdline not available; e.g. kernel thread, zombie */
		if (NULL == name)
			return NULL;

		ssnprintf (buf, buf_len, "[%s]", name);
		return buf;
	}

	assert (n <= buf_len);

	if (n == buf_len)
		--n;
	buf[n] = '\0';

	--n;
	/* remove trailing whitespace */
	while ((n > 0) && (isspace (buf[n]) || ('\0' == buf[n]))) {
		buf[n] = '\0';
		--n;
	}

	/* arguments are separated by '\0' in /proc/<pid>/cmdline */
	while (n > 0) {
		if ('\0' == buf[n])
			buf[n] = ' ';
		--n;
	}
	return buf;
}