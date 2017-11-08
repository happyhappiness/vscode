static inline int close_lock_file(struct lock_file *lk)
{
	return close_tempfile(&lk->tempfile);
}