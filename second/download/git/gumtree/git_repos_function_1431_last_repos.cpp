static int try_create_file(const char *path, unsigned int mode, const char *buf, unsigned long size)
{
	int fd, res;
	struct strbuf nbuf = STRBUF_INIT;

	if (S_ISGITLINK(mode)) {
		struct stat st;
		if (!lstat(path, &st) && S_ISDIR(st.st_mode))
			return 0;
		return !!mkdir(path, 0777);
	}

	if (has_symlinks && S_ISLNK(mode))
		/* Although buf:size is counted string, it also is NUL
		 * terminated.
		 */
		return !!symlink(buf, path);

	fd = open(path, O_CREAT | O_EXCL | O_WRONLY, (mode & 0100) ? 0777 : 0666);
	if (fd < 0)
		return 1;

	if (convert_to_working_tree(path, buf, size, &nbuf)) {
		size = nbuf.len;
		buf  = nbuf.buf;
	}

	res = write_in_full(fd, buf, size) < 0;
	if (res)
		error_errno(_("failed to write to '%s'"), path);
	strbuf_release(&nbuf);

	if (close(fd) < 0 && !res)
		return error_errno(_("closing file '%s'"), path);

	return res ? -1 : 0;
}