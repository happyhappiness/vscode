				  const char *buf, unsigned long size)
{
	int fd;
	char *path = git_pathdup(NOTES_MERGE_WORKTREE "/%s", sha1_to_hex(obj));
	if (safe_create_leading_directories_const(path))
		die_errno("unable to create directory for '%s'", path);
	if (file_exists(path))
		die("found existing file at '%s'", path);

	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		die_errno("failed to open '%s'", path);

	while (size > 0) {
		long ret = write_in_full(fd, buf, size);
		if (ret < 0) {
			/* Ignore epipe */
			if (errno == EPIPE)
