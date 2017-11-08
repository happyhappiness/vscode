static int do_write_locked_index(struct index_state *istate, struct lock_file *lock,
				 unsigned flags)
{
	int ret = do_write_index(istate, &lock->tempfile, 0);
	if (ret)
		return ret;
	assert((flags & (COMMIT_LOCK | CLOSE_LOCK)) !=
	       (COMMIT_LOCK | CLOSE_LOCK));
	if (flags & COMMIT_LOCK)
		return commit_locked_index(lock);
	else if (flags & CLOSE_LOCK)
		return close_lock_file(lock);
	else
		return ret;
}