int reopen_lock_file(struct lock_file *lk)
{
	if (0 <= lk->fd)
		die(_("BUG: reopen a lockfile that is still open"));
	if (!lk->active)
		die(_("BUG: reopen a lockfile that has been committed"));
	lk->fd = open(lk->filename.buf, O_WRONLY);
	return lk->fd;
}