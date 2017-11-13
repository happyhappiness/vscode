static int lock_file(struct lock_file *lk, const char *path, int flags)
{
	size_t pathlen = strlen(path);

	if (!lock_file_list) {
		/* One-time initialization */
		sigchain_push_common(remove_lock_files_on_signal);
		atexit(remove_lock_files_on_exit);
	}

	if (lk->active)
		die("BUG: cannot lock_file(\"%s\") using active struct lock_file",
		    path);
	if (!lk->on_list) {
		/* Initialize *lk and add it to lock_file_list: */
		lk->fd = -1;
		lk->fp = NULL;
		lk->active = 0;
		lk->owner = 0;
		strbuf_init(&lk->filename, pathlen + LOCK_SUFFIX_LEN);
		lk->next = lock_file_list;
		lock_file_list = lk;
		lk->on_list = 1;
	} else if (lk->filename.len) {
		/* This shouldn't happen, but better safe than sorry. */
		die("BUG: lock_file(\"%s\") called with improperly-reset lock_file object",
		    path);
	}

	strbuf_add(&lk->filename, path, pathlen);
	if (!(flags & LOCK_NO_DEREF))
		resolve_symlink(&lk->filename);
	strbuf_addstr(&lk->filename, LOCK_SUFFIX);
	lk->fd = open(lk->filename.buf, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (lk->fd < 0) {
		strbuf_reset(&lk->filename);
		return -1;
	}
	lk->owner = getpid();
	lk->active = 1;
	if (adjust_shared_perm(lk->filename.buf)) {
		int save_errno = errno;
		error("cannot fix permission bits on %s", lk->filename.buf);
		rollback_lock_file(lk);
		errno = save_errno;
		return -1;
	}
	return lk->fd;
}