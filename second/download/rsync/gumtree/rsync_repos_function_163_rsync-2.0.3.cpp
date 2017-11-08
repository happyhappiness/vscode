static int get_secret(int module, char *user, char *secret, int len)
{
	char *fname = lp_secrets_file(module);
	int fd, found=0;
	char line[1024];
	char *p, *pass;

	if (!fname || !*fname) return 0;

	fd = open(fname,O_RDONLY);
	if (fd == -1) return 0;

	while (!found) {
		int i = 0;
		memset(line, 0, sizeof(line));
		while (i<(sizeof(line)-1)) {
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

	if (strlen(pass) > len-1) {
		memset(line, 0, sizeof(line));
		return 0;
	}

	strcpy(secret, pass);
	return 1;
}