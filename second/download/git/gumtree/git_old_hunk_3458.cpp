	struct dirent *de;
	int r = 0;

	if (!dir) {
		if (errno == ENOENT)
			return 0;
		return error("unable to open %s: %s", path->buf, strerror(errno));
	}

	while ((de = readdir(dir))) {
		if (is_dot_or_dotdot(de->d_name))
			continue;

