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