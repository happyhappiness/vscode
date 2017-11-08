static int lock_file(struct lock_file *lk, const char *path, int flags)
{
	int fd;
	struct strbuf filename = STRBUF_INIT;

	strbuf_addstr(&filename, path);
	if (!(flags & LOCK_NO_DEREF))
		resolve_symlink(&filename);

	strbuf_addstr(&filename, LOCK_SUFFIX);
	fd = create_tempfile(&lk->tempfile, filename.buf);
	strbuf_release(&filename);
	return fd;
}