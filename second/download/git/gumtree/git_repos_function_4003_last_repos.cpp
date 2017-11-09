static inline void rollback_lock_file(struct lock_file *lk)
{
	delete_tempfile(&lk->tempfile);
}