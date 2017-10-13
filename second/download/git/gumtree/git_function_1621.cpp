int commit_lock_file_to(struct lock_file *lk, const char *path)
{
	if (!lk->active)
		die("BUG: attempt to commit unlocked object to \"%s\"", path);

	if (close_lock_file(lk))
		return -1;

	if (rename(lk->filename.buf, path)) {
		int save_errno = errno;
		rollback_lock_file(lk);
		errno = save_errno;
		return -1;
	}

	lk->active = 0;
	strbuf_reset(&lk->filename);
	return 0;
}