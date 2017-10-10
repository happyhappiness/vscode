	int fd = lock_file_timeout(lk, path, flags, timeout_ms);
	if (fd < 0 && (flags & LOCK_DIE_ON_ERROR))
		unable_to_lock_die(path, errno);
	return fd;
}

int hold_lock_file_for_append(struct lock_file *lk, const char *path, int flags)
{
	int fd, orig_fd;

	fd = lock_file(lk, path, flags);
	if (fd < 0) {
		if (flags & LOCK_DIE_ON_ERROR)
			unable_to_lock_die(path, errno);
		return fd;
	}

	orig_fd = open(path, O_RDONLY);
	if (orig_fd < 0) {
		if (errno != ENOENT) {
			int save_errno = errno;

			if (flags & LOCK_DIE_ON_ERROR)
				die("cannot open '%s' for copying", path);
			rollback_lock_file(lk);
			error("cannot open '%s' for copying", path);
			errno = save_errno;
			return -1;
		}
	} else if (copy_fd(orig_fd, fd)) {
		int save_errno = errno;

		if (flags & LOCK_DIE_ON_ERROR)
			die("failed to prepare '%s' for appending", path);
		close(orig_fd);
		rollback_lock_file(lk);
		errno = save_errno;
		return -1;
	} else {
		close(orig_fd);
	}
	return fd;
}

FILE *fdopen_lock_file(struct lock_file *lk, const char *mode)
{
	if (!lk->active)
		die("BUG: fdopen_lock_file() called for unlocked object");
	if (lk->fp)
		die("BUG: fdopen_lock_file() called twice for file '%s'", lk->filename.buf);

	lk->fp = fdopen(lk->fd, mode);
	return lk->fp;
}

char *get_locked_file_path(struct lock_file *lk)
{
	if (!lk->active)
		die("BUG: get_locked_file_path() called for unlocked object");
	if (lk->filename.len <= LOCK_SUFFIX_LEN)
		die("BUG: get_locked_file_path() called for malformed lock object");
	return xmemdupz(lk->filename.buf, lk->filename.len - LOCK_SUFFIX_LEN);
}

int close_lock_file(struct lock_file *lk)
{
	int fd = lk->fd;
	FILE *fp = lk->fp;
	int err;

	if (fd < 0)
		return 0;

	lk->fd = -1;
	if (fp) {
		lk->fp = NULL;

		/*
		 * Note: no short-circuiting here; we want to fclose()
		 * in any case!
		 */
		err = ferror(fp) | fclose(fp);
	} else {
		err = close(fd);
	}

	if (err) {
		int save_errno = errno;
		rollback_lock_file(lk);
		errno = save_errno;
		return -1;
	}

	return 0;
}

int reopen_lock_file(struct lock_file *lk)
{
	if (0 <= lk->fd)
		die(_("BUG: reopen a lockfile that is still open"));
	if (!lk->active)
		die(_("BUG: reopen a lockfile that has been committed"));
	lk->fd = open(lk->filename.buf, O_WRONLY);
	return lk->fd;
}

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

int commit_lock_file(struct lock_file *lk)
{
	static struct strbuf result_file = STRBUF_INIT;
	int err;

	if (!lk->active)
		die("BUG: attempt to commit unlocked object");

	if (lk->filename.len <= LOCK_SUFFIX_LEN ||
	    strcmp(lk->filename.buf + lk->filename.len - LOCK_SUFFIX_LEN, LOCK_SUFFIX))
		die("BUG: lockfile filename corrupt");

	/* remove ".lock": */
	strbuf_add(&result_file, lk->filename.buf,
		   lk->filename.len - LOCK_SUFFIX_LEN);
	err = commit_lock_file_to(lk, result_file.buf);
	strbuf_reset(&result_file);
	return err;
}

void rollback_lock_file(struct lock_file *lk)
{
	if (!lk->active)
		return;

	if (!close_lock_file(lk)) {
		unlink_or_warn(lk->filename.buf);
		lk->active = 0;
		strbuf_reset(&lk->filename);
	}
}
