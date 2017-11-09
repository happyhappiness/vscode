static inline int reopen_lock_file(struct lock_file *lk)
{
	return reopen_tempfile(&lk->tempfile);
}