static int commit_locked_index(struct lock_file *lk)
{
	if (alternate_index_output) {
		if (lk->fd >= 0 && close_lock_file(lk))
			return -1;
		if (rename(lk->filename, alternate_index_output))
			return -1;
		lk->filename[0] = 0;
		return 0;
	} else {
		return commit_lock_file(lk);
	}
}