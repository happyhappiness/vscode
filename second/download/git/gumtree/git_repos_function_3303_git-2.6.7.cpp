static inline int get_lock_file_fd(struct lock_file *lk)
{
	return get_tempfile_fd(&lk->tempfile);
}