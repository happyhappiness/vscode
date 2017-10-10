{
	struct strbuf path = STRBUF_INIT;
	struct stat st;

	strbuf_addf(&path, "%s/gitdir", gitdir);
	if (stat(path.buf, &st) || st.st_mtime + 24 * 3600 < time(NULL))
		write_file(path.buf, 1, "%s\n", gitfile);
	strbuf_release(&path);
}

/*
 * Try to read the location of the git directory from the .git file,
 * return path to git directory if found.
 */
const char *read_gitfile(const char *path)
{
	char *buf;
	char *dir;
	const char *slash;
	struct stat st;
	int fd;
	ssize_t len;

	if (stat(path, &st))
		return NULL;
	if (!S_ISREG(st.st_mode))
		return NULL;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		die_errno("Error opening '%s'", path);
	buf = xmalloc(st.st_size + 1);
	len = read_in_full(fd, buf, st.st_size);
	close(fd);
	if (len != st.st_size)
		die("Error reading %s", path);
	buf[len] = '\0';
	if (!starts_with(buf, "gitdir: "))
		die("Invalid gitfile format: %s", path);
	while (buf[len - 1] == '\n' || buf[len - 1] == '\r')
		len--;
	if (len < 9)
		die("No path in gitfile: %s", path);
	buf[len] = '\0';
	dir = buf + 8;

	if (!is_absolute_path(dir) && (slash = strrchr(path, '/'))) {
		size_t pathlen = slash+1 - path;
		size_t dirlen = pathlen + len - 8;
