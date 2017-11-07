void rollback_lock_file(struct lock_file *lk)
{
	if (lk->filename[0]) {
		if (lk->fd >= 0)
			close(lk->fd);
		unlink_or_warn(lk->filename);
	}
	lk->filename[0] = 0;
}