static int create_reflock(const char *path, void *cb)
{
	struct lock_file *lk = cb;

	return hold_lock_file_for_update(lk, path, LOCK_NO_DEREF) < 0 ? -1 : 0;
}