}

static void write_buf_to_worktree(const unsigned char *obj,
				  const char *buf, unsigned long size)
{
	int fd;
	const char *path = git_path(NOTES_MERGE_WORKTREE "/%s", sha1_to_hex(obj));
	if (safe_create_leading_directories_const(path))
		die_errno("unable to create directory for '%s'", path);
	if (file_exists(path))
		die("found existing file at '%s'", path);

	fd = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
