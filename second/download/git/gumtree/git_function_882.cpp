const char *read_gitfile_gently(const char *path, int *return_error_code)
{
	const int max_file_size = 1 << 20;  /* 1MB */
	int error_code = 0;
	char *buf = NULL;
	char *dir = NULL;
	const char *slash;
	struct stat st;
	int fd;
	ssize_t len;

	if (stat(path, &st)) {
		error_code = READ_GITFILE_ERR_STAT_FAILED;
		goto cleanup_return;
	}
	if (!S_ISREG(st.st_mode)) {
		error_code = READ_GITFILE_ERR_NOT_A_FILE;
		goto cleanup_return;
	}
	if (st.st_size > max_file_size) {
		error_code = READ_GITFILE_ERR_TOO_LARGE;
		goto cleanup_return;
	}
	fd = open(path, O_RDONLY);
	if (fd < 0) {
		error_code = READ_GITFILE_ERR_OPEN_FAILED;
		goto cleanup_return;
	}
	buf = xmallocz(st.st_size);
	len = read_in_full(fd, buf, st.st_size);
	close(fd);
	if (len != st.st_size) {
		error_code = READ_GITFILE_ERR_READ_FAILED;
		goto cleanup_return;
	}
	if (!starts_with(buf, "gitdir: ")) {
		error_code = READ_GITFILE_ERR_INVALID_FORMAT;
		goto cleanup_return;
	}
	while (buf[len - 1] == '\n' || buf[len - 1] == '\r')
		len--;
	if (len < 9) {
		error_code = READ_GITFILE_ERR_NO_PATH;
		goto cleanup_return;
	}
	buf[len] = '\0';
	dir = buf + 8;

	if (!is_absolute_path(dir) && (slash = strrchr(path, '/'))) {
		size_t pathlen = slash+1 - path;
		dir = xstrfmt("%.*s%.*s", (int)pathlen, path,
			      (int)(len - 8), buf + 8);
		free(buf);
		buf = dir;
	}
	if (!is_git_directory(dir)) {
		error_code = READ_GITFILE_ERR_NOT_A_REPO;
		goto cleanup_return;
	}
	path = real_path(dir);

cleanup_return:
	if (return_error_code)
		*return_error_code = error_code;
	else if (error_code) {
		switch (error_code) {
		case READ_GITFILE_ERR_STAT_FAILED:
		case READ_GITFILE_ERR_NOT_A_FILE:
			/* non-fatal; follow return path */
			break;
		case READ_GITFILE_ERR_OPEN_FAILED:
			die_errno("Error opening '%s'", path);
		case READ_GITFILE_ERR_TOO_LARGE:
			die("Too large to be a .git file: '%s'", path);
		case READ_GITFILE_ERR_READ_FAILED:
			die("Error reading %s", path);
		case READ_GITFILE_ERR_INVALID_FORMAT:
			die("Invalid gitfile format: %s", path);
		case READ_GITFILE_ERR_NO_PATH:
			die("No path in gitfile: %s", path);
		case READ_GITFILE_ERR_NOT_A_REPO:
			die("Not a git repository: %s", dir);
		default:
			assert(0);
		}
	}

	free(buf);
	return error_code ? NULL : path;
}