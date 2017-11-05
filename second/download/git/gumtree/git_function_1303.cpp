FILE *fdopen_lock_file(struct lock_file *lk, const char *mode)
{
	if (!lk->active)
		die("BUG: fdopen_lock_file() called for unlocked object");
	if (lk->fp)
		die("BUG: fdopen_lock_file() called twice for file '%s'", lk->filename.buf);

	lk->fp = fdopen(lk->fd, mode);
	return lk->fp;
}