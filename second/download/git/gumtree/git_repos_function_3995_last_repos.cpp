static inline int is_lock_file_locked(struct lock_file *lk)
{
	return is_tempfile_active(&lk->tempfile);
}