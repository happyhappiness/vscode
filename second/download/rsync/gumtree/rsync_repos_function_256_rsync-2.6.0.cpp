static int get_secret(int module, char *user, char *secret, int len)
{
	char *fname = lp_secrets_file(module);
	int fd, found=0;
	char line[MAXPATHLEN];
	char *p, *pass=NULL;
	STRUCT_STAT st;
	int ok = 1;
	extern int am_root;

	if (!fname || !*fname) return 0;

	fd = open(fname,O_RDONLY);
	if (fd == -1) return 0;

	if (do_stat(fname, &st) == -1) {
		rsyserr(FERROR, errno, "stat(%s)", fname);
		ok = 0;
	} else if (lp_strict_modes(module)) {
		if ((st.st_mode & 06) != 0) {
			rprintf(FERROR,"secrets file must not be other-accessible (see strict modes option)\n");
			ok = 0;
		} else if (am_root && (st.st_uid != 0)) {
			rprintf(FERROR,"secrets file must be owned by root when running as root (see strict modes)\n");
			ok = 0;
		}
	}
	if (!ok) {
		rprintf(FERROR,"continuing without secrets file\n");
		close(fd);
		return 0;
	}

	while (!found) {
		int i = 0;
		memset(line, 0, sizeof line);
		while ((size_t) i < (sizeof(line)-1)) {
			if (read(fd, &line[i], 1) != 1) {
				memset(line, 0, sizeof(line));
				close(fd);
				return 0;
			}
			if (line[i] == '\r') continue;
			if (line[i] == '\n') break;
			i++;
		}
		line[i] = 0;
		if (line[0] == '#') continue;
		p = strchr(line,':');
		if (!p) continue;
		*p = 0;
		if (strcmp(user, line)) continue;
		pass = p+1;
		found = 1;
	}

	close(fd);
	if (!found) return 0;

	strlcpy(secret, pass, len);
	return 1;
}