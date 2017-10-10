	struct dirent *de;
	int r = 0;

	if (!dir) {
		if (errno == ENOENT)
			return 0;
		return error_errno("unable to open %s", path->buf);
	}

	while ((de = readdir(dir))) {
		if (is_dot_or_dotdot(de->d_name))
			continue;

