static int get_secret(int module, const char *user, char *secret, int len)
{
	const char *fname = lp_secrets_file(module);
	STRUCT_STAT st;
	int fd, ok = 1;
	const char *p;
	char ch, *s;

	if (!fname || !*fname)
		return 0;

	if ((fd = open(fname, O_RDONLY)) < 0)
		return 0;

	if (do_stat(fname, &st) == -1) {
		rsyserr(FLOG, errno, "stat(%s)", fname);
		ok = 0;
	} else if (lp_strict_modes(module)) {
		if ((st.st_mode & 06) != 0) {
			rprintf(FLOG, "secrets file must not be other-accessible (see strict modes option)\n");
			ok = 0;
		} else if (MY_UID() == 0 && st.st_uid != 0) {
			rprintf(FLOG, "secrets file must be owned by root when running as root (see strict modes)\n");
			ok = 0;
		}
	}
	if (!ok) {
		rprintf(FLOG, "continuing without secrets file\n");
		close(fd);
		return 0;
	}

	if (*user == '#') {
		/* Reject attempt to match a comment. */
		close(fd);
		return 0;
	}

	/* Try to find a line that starts with the user name and a ':'. */
	p = user;
	while (1) {
		if (read(fd, &ch, 1) != 1) {
			close(fd);
			return 0;
		}
		if (ch == '\n')
			p = user;
		else if (p) {
			if (*p == ch)
				p++;
			else if (!*p && ch == ':')
				break;
			else
				p = NULL;
		}
	}

	/* Slurp the secret into the "secret" buffer. */
	s = secret;
	while (len > 0) {
		if (read(fd, s, 1) != 1 || *s == '\n')
			break;
		if (*s == '\r')
			continue;
		s++;
		len--;
	}
	*s = '\0';
	close(fd);

	return 1;
}