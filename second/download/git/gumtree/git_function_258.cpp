static int read_old_data(struct stat *st, const char *path, struct strbuf *buf)
{
	switch (st->st_mode & S_IFMT) {
	case S_IFLNK:
		if (strbuf_readlink(buf, path, st->st_size) < 0)
			return error(_("unable to read symlink %s"), path);
		return 0;
	case S_IFREG:
		if (strbuf_read_file(buf, path, st->st_size) != st->st_size)
			return error(_("unable to open or read %s"), path);
		convert_to_git(path, buf->buf, buf->len, buf, 0);
		return 0;
	default:
		return -1;
	}
}